//Omid55
/*
 * find_tweet_raw_urls.cpp
 *
 *  Created on: Nov 16, 2013
 *      Author: oaskaris
 */
// MAIN METHOD FOR FINDING RAW URLS

//Omid55
#include "stdafx.h"
#include <postgresql/libpq-fe.h>
#include <sqlite3.h>

TVec<TwitterUrl> rawUrls;   // for each id urls which it contains

unsigned int mycounter = 1;
void SaveAll()
{
	TZipOut zipData(TStr::Fmt("/NS/twitter-5/work/oaskaris/RAWS/TwitterRAWUrlz%d.rar",mycounter));
	rawUrls.Save(zipData);
	printf("The size of Urls %d was: %d\n",mycounter,rawUrls.Len());
	rawUrls.Clr();
	mycounter++;
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		TStr test(argv[1]);
		TChAV urlsss = Tools::getAllUrls(test);
		cout << "\n\n\nResuls are :\n";
		for(int l=0;l<urlsss.Len();l++)
		{
			cout << urlsss[l].CStr() << endl;
		}
	}
	else
	{
		cout << "usage: find_tweet_raw_urls \"your text\"" << endl;
	}
	return 0;


//	TStr textz = "shdlaa da ;ash http://yahoo.com salam khobi www.google.com/ok http://live.com/microsoft?id=55 it's ok buddy https://ebay.com/ bye pal ;)";
//	TChAV rez = getAllUrls(textz);
//	for(int i=0;i<rez.Len();i++)
//	{
//		cout << rez[i].CStr() << endl;
//	}
//	return 0;
//	////////////////////


	TExeTm ExeTm;
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row,i;
	unsigned int q;
	int total_number_tweets = 0;
	double tweet_date = 0;
	TStr tweetStr("");

	printf(":::::::: find raw urls of tweets ::::::::\n");

	const TStr StartDate = Env.GetIfArgPrefixStr("-sd:", "2008-08-01 00:00:00", "Starting date");
	const TStr EndDate = Env.GetIfArgPrefixStr("-ed:", "2009-10-01 00:00:00", "Ending date");

	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nFinding the cascades of the desired quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		// Requesting the database
		printf("\nLoad Tweet Urls function started ...\n");

		conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

		if (PQstatus(conn) == CONNECTION_BAD)
		{
			printf("We were unable to connect to the database");
			return 1;
		}

		// we use cursors/fetch to speed up the process; batch of 10000 tweets
		PQexec(conn, "begin work");
		PQexec(conn,TStr::Fmt("declare mycursor cursor for select extract(epoch from tweettime), tweettext from tweets where tweettime >= timestamp '%s' and tweettime < timestamp '%s'", StartDate.CStr(), EndDate.CStr()).CStr());
		do
		{
			res = PQexec(conn, "FETCH 100000000 IN mycursor");    // all of them are: 1675401026
			if (PQresultStatus(res) == PGRES_TUPLES_OK)
			{
				rec_count = PQntuples(res);
				total_number_tweets += rec_count;
				printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

				for (row=0; row<rec_count; row++)
				{
					tweet_date = TStr(PQgetvalue(res, row, 0)).GetFlt();
					tweetStr = PQgetvalue(res, row, 1);

					TChAV us = Tools::getAllUrls(tweetStr);
					if(us.Len() != 0)
					{
						TSecTm ti(tweet_date);
						TwitterUrl tur(ti,us);
						rawUrls.Add(tur);
						if(rawUrls.Len()==40000000)    // it was 10000
						{
							SaveAll();
						}
					}
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

		SaveAll();

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

