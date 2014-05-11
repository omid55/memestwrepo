// Omid55
/*
 * justchecktweettimes.cpp
 *
 *  Created on: May 9, 2014
 *      Author: omid55
 */
// Omid55
#include "stdafx.h"
#include <postgresql/libpq-fe.h>
#include <sqlite3.h>

int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	PGconn *conn;
	PGresult *res;
	int rec_count, row, total_number_tweets = 0;
	char responce;

	const TStr StartDate = Env.GetIfArgPrefixStr("-sd:", "2008-08-01 00:00:00", "Starting date");
	const TStr EndDate = Env.GetIfArgPrefixStr("-ed:", "2009-10-01 00:00:00", "Ending date");

	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nJust check. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		// Requesting the database
		conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

		if (PQstatus(conn) == CONNECTION_BAD)
		{
			printf("We were unable to connect to the database");
			return 1;
		}

		// we use cursors/fetch to speed up the process; batch of 10000 tweets
		PQexec(conn, "begin work");
		PQexec(conn,TStr::Fmt("declare mycursor cursor for select extract(epoch from tweettime), tweettime from tweets where tweettime >= timestamp '%s' and tweettime < timestamp '%s'", StartDate.CStr(), EndDate.CStr()).CStr());
		do
		{
			res = PQexec(conn, "FETCH 10 IN mycursor");    // all of them are: 1675401026
			if (PQresultStatus(res) == PGRES_TUPLES_OK)
			{
				rec_count = PQntuples(res);
				total_number_tweets += rec_count;
				printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

				for (row=0; row<rec_count; row++)
				{
					double tweet_date = TStr(PQgetvalue(res, row, 0)).GetFlt();
					TStr tweet_datestr = PQgetvalue(res, row, 1);
					cout << "Original->\t\t" << (uint)tweet_date << " : " << tweet_datestr.CStr() << endl;
					TSecTm d(tweet_date);
					cout << "In Snap->\t\t" << d.GetAbsSecs() << " : " << d.GetYmdTmStr().CStr() << endl << endl;
				}
				cout << "\n\nDo you want to continue(y/n): ";
				cin >> responce;
				if (responce != 'y' && responce != 'Y')
				{
					break;
				}

				PQclear(res);
			}
			else
			{
				rec_count = 0;
			}
		}
		while (rec_count);

		PQexec(conn, "close mycursor");
		PQexec(conn, "commit work");
		PQfinish(conn);

		printf("\n\n DONE \n\n");
	}
	catch(exception& ex)
	{
		printf("\nError1 happened, it was: %s\n\n",ex.what());
	}
	catch(TPt<TExcept>& ex)
	{
		printf("\nError2 happened: %s\n\n",ex[0].GetStr().CStr());
	}

	printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
	return 0;
}



