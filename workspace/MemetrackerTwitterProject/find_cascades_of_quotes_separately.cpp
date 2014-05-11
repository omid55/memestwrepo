// Omid55
// Codes for Twitter data fetching
// find_cascades_of_quotes_separately.cpp
#include "stdafx.h"
#include <postgresql/libpq-fe.h>
#include <sqlite3.h>

inline TStr getWebsite(TStr fulladdress)
{
	TStr left,right,tmp,res;
	if(fulladdress.SearchStr(TStr("http"),0)>=0)
	{
		fulladdress.SplitOnStr(left,TStr("//"),right);
		right.SplitOnCh(res,'/',tmp);
	}
	else
	{
		fulladdress.SplitOnCh(res,'/',tmp);
	}
	return res;
}

inline bool fileExists(TStr filepath)
{
	fstream f(filepath.CStr(),ios::in);
	if(!f)
	{
		f.close();
		return false;
	}
	f.close();
	return true;
}


#define LENGTH 2 // CHANGE TO 10


int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	PGconn *conn;
	PGresult *res;
	int id,start,rec_count,row,indx,end;
	unsigned int q;
	int total_number_tweets = 0;
	double tweet_date = 0;
	TStr TweetStr("");
	TStr TweetStrLc("");

	if(argc > 1)
	{
		start = atoi(argv[1]);
	}
	else
	{
		printf("YOU SHOULD SET THE INDICES...\n\n");
		return 1;
	}
	indx = start * LENGTH;
	end = indx + LENGTH;

	printf(":::::::: Find Cascades of Quotes In Twitter Separately ::::::::\n");
	const TStr StartDate = Env.GetIfArgPrefixStr("-sd:", "2008-08-01 00:00:00", "Starting date");
	const TStr EndDate = Env.GetIfArgPrefixStr("-ed:", "2009-10-01 00:00:00", "Ending date");

	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nFinding the cascades of the desired quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		while(indx < end)
		{
			TStr qContentFname = TStr::Fmt("QuotesData/Q%d.rar",indx);
			TStr resultFname = TStr::Fmt("QuotesCascResult/R%d.rar",indx++);

			if(fileExists(resultFname))
			{
				if(fileExists(qContentFname))
				{
					// removing the quotes' content file
					system(TStr::Fmt("rm %s",qContentFname.CStr()).CStr());
				}
			}
			else
			{
				if(fileExists(qContentFname))
				{
					THash<TStr,TInt> quotesContent;
					THash<TInt,TSecTmV> CascadesOnTwitter;

					TZipIn ZquotesIn(qContentFname);
					quotesContent.Load(ZquotesIn);
					printf("Q%d loading done, it contains %d quotes.\n",indx-1,quotesContent.Len());

					conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

					if (PQstatus(conn) == CONNECTION_BAD)
					{
						printf("We were unable to connect to the database");
						return 1;
					}

					// we use cursors/fetch to speed up the process; batch of 10000 tweets
					PQexec(conn, "begin work");
					PQexec(conn,TStr::Fmt("declare mycursor cursor for select tweettext, extract(epoch from tweettime) from tweets where tweettime >= timestamp '%s' and tweettime < timestamp '%s'", StartDate.CStr(), EndDate.CStr()).CStr());

					do
					{
						res = PQexec(conn, "FETCH 1000000 IN mycursor");    // all of them are: 1675401026
						if (PQresultStatus(res) == PGRES_TUPLES_OK)
						{
							rec_count = PQntuples(res);
							total_number_tweets += rec_count;
							printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

							for (row=0; row<rec_count; row++)
							{
								TweetStr = PQgetvalue(res, row, 0);
								tweet_date = TStr(PQgetvalue(res, row, 1)).GetFlt();
								TweetStrLc = TweetStr.ToLc();
								for(q=0;q<quotesContent.Len();q++)
								{
									if (TweetStrLc.SearchStr(quotesContent.GetKey(q)) > -1)
									{
										TSecTm td(tweet_date);
										id = CascadesOnTwitter.GetKeyId(quotesContent[q]);
										if(id == -1)
										{
											CascadesOnTwitter.AddDat(quotesContent[q]).Add(td);
										}
										else
										{
											CascadesOnTwitter.GetDat(quotesContent[q]).AddSorted(td);
										}
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


					// Save the results
					TZipOut zout(resultFname);
					CascadesOnTwitter.Save(zout);

					// Remove the qoutes' content file
					system(TStr::Fmt("rm %s",qContentFname.CStr()).CStr());
				}
			}
		}

		printf("\n\nD O N E\n\n");
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
