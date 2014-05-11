// Omid55
/*
 * check_tweets_length.cpp
 *
 *  Created on: Dec 27, 2013
 *      Author: oaskaris
 */

#include "stdafx.h"
#include <postgresql/libpq-fe.h>
#include <sqlite3.h>

int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;
	int total_number_tweets = 0;

	printf(":::::::: Find Cascades of Quotes In Twitter ::::::::\n");
	const TStr StartDate = Env.GetIfArgPrefixStr("-sd:", "2008-08-01 00:00:00", "Starting date");
	const TStr EndDate = Env.GetIfArgPrefixStr("-ed:", "2009-10-01 00:00:00", "Ending date");

	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nFinding the cascades of the desired quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		// Requesting the database
		printf("\nCheck Tweets Length From PostgreSQL function started ...\n");

		conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

		if (PQstatus(conn) == CONNECTION_BAD)
		{
			printf("We were unable to connect to the database");
			return 1;
		}

		// we use cursors/fetch to speed up the process; batch of 10000 tweets
		PQexec(conn, "begin work");
		PQexec(conn,TStr::Fmt("declare mycursor cursor for select tweettext, extract(epoch from tweettime) from tweets where tweettime >= timestamp '%s' and tweettime < timestamp '%s'", StartDate.CStr(), EndDate.CStr()).CStr());

		int minl=9999;
		int maxl=-9999;
		int minw=9999;
		int maxw=-9999;
		do
		{
			res = PQexec(conn, "FETCH 1000000 IN mycursor");    // all of them are: 1675401026
			if (PQresultStatus(res) == PGRES_TUPLES_OK)
			{
				rec_count = PQntuples(res);
				total_number_tweets += rec_count;
				printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

				double tweet_date = 0;
				TStr TweetStr("");
				TStr TweetStrLc("");
				for (row=0; row<rec_count; row++)
				{
					if(row>0 && row%(rec_count/100)==0)
					{
						printf("Row%d is processing.\n",row);
					}

					TweetStr = PQgetvalue(res, row, 0);
					tweet_date = TStr(PQgetvalue(res, row, 1)).GetFlt();
					TweetStrLc = TweetStr.ToLc();


					// without any urls within
					while(true)
					{
						int index = TweetStrLc.SearchStr("http://");
						if(index > -1)
						{
							int endIndex = index;
							while(endIndex<TweetStrLc.Len() && TweetStrLc[endIndex]!=' ')
							{
								endIndex++;
							}
							TweetStrLc.DelSubStr(index,endIndex);
						}
						else
						{
							break;
						}
					}
					// without any urls within


					int l = TweetStrLc.Len();
					int w = TStrUtil::CountWords(TweetStrLc);
					//printf("Characters: %d, Words: %d\n",l,w);

					if(l>140)
					{
						printf("%s\n\n\n",TweetStrLc.CStr());
					}

					if(l<minl)
					{
						minl=l;
					}
					if(l>maxl)
					{
						maxl=l;
					}
					if(w<minw)
					{
						minw=w;
					}
					if(w>maxw)
					{
						maxw=w;
					}
				}

				PQclear(res);
			}
			else
			{
				rec_count = 0;
			}

			printf("\n\n<<<=== Characters: %d..%d, Words: %d..%d ===>>>\n\n",minl,maxl,minw,maxw);
		}
		while (rec_count);

		PQexec(conn, "close mycursor");
		PQexec(conn, "commit work");

		PQfinish(conn);

		printf("\n\nDone\n\n");
		// Requesting the database
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


