// Omid55
// Codes for Twitter data fetching
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

// input datasets
//THash< TChA , TUInt > posts;
THash< TStr , CascadeElementV > quotes;
// input datasets

// output dataset
THash<TUInt,TSecTmV> CascadesOnTwitter;
// output dataset

void SaveAll()
{
	printf("\n<<< SAVING STARTS (PLEASE BE PATIENT!!!) >>> .......\n");
	TZipOut cascadesOnTwitterData("CascadesOnTwitterData_JUST10.rar");
	CascadesOnTwitter.Save(cascadesOnTwitterData);
	printf("The size of CascadesOnTwitter was: %d\n",CascadesOnTwitter.Len());

	printf("\n<<<<<<<< SAVING DONE >>>>>>>>\n\n");
}


int main(int argc, char* argv[])
{
//	TZipIn ZquotesIn("CascadesOnTwitterData.rar");
//	CascadesOnTwitter.Load(ZquotesIn);
//	printf("QuotesPreprocessed loading done, it contains %d quotes.\n",CascadesOnTwitter.Len());
//	for(int i=0;i<CascadesOnTwitter.Len();i++)
//	{
//		printf("Q%d: %d\n",CascadesOnTwitter.GetKey(i),CascadesOnTwitter[i].Len());
//	}
//	return 0;

//	TZipIn ZquotesIn("QuotesPreprocessedData.rar");
//	quotes.Load(ZquotesIn);
//	printf("QuotesPreprocessed loading done, it contains %d quotes.\n",quotes.Len());
//	for(int i=0;i<quotes.Len();i++)
//	{
//		printf("Q%d: %s\n",i,quotes.GetKey(i).CStr());
//	}
//	return 0;

	TExeTm ExeTm;
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;
	unsigned int q;
	int total_number_tweets = 0;

	printf(":::::::: Find Cascades of Quotes In Twitter ::::::::\n");
	const TStr StartDate = Env.GetIfArgPrefixStr("-sd:", "2008-08-01 00:00:00", "Starting date");
	const TStr EndDate = Env.GetIfArgPrefixStr("-ed:", "2009-10-01 00:00:00", "Ending date");

	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nFinding the cascades of the desired quotes in content and their urls in urls. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		TZipIn ZquotesIn("QuotesPreprocessedData.rar");
		quotes.Load(ZquotesIn);
		printf("QuotesPreprocessed loading done, it contains %d quotes.\n",quotes.Len());

//		TZipIn ZpostsIn("PostsData.rar");
//		posts.Load(ZpostsIn);
//		printf("PostsData loading done, it contains %d quotes.\n",posts.Len());

		// Requesting the database
		printf("\nLoadCascadeOfQuoteFromPostgreSQL function started ...\n");

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
			res = PQexec(conn, "FETCH 10000000 IN mycursor");    // all of them are: 1675401026
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
//					if(row>0 && row%(rec_count/100)==0)
//					{
//						printf("Row%d is processing.\n",row);
//					}

					TweetStr = PQgetvalue(res, row, 0);
					tweet_date = TStr(PQgetvalue(res, row, 1)).GetFlt();
					TweetStrLc = TweetStr.ToLc();
					for(q=0;q<10;q++)     //for(q=0;q<quotes.Len();q++)
					{
//		 				for(int j=0;j<quotes[q].Len();j++)
//		 				{
//		 					TStr postj = TStr(posts[quotes[q][j].post]);
//		 					// INJAAAAA
//		 				}

						if (TweetStrLc.SearchStr(quotes.GetKey(q)) > -1)
						{
							TSecTm td(tweet_date);
							int id = CascadesOnTwitter.GetKeyId(q);
							if(id == -1)
							{
								CascadesOnTwitter.AddDat(q).Add(td);
							}
							else
							{
								CascadesOnTwitter.GetDat(q).AddSorted(td);
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

		printf("\n\nDONE\n\n");
		// Requesting the database


		SaveAll();
	}
	catch(exception& ex)
	{
		SaveAll();
		printf("\nError1 happened, it was: %s\n\n",ex.what());
	}
	catch(TPt<TExcept>& ex)
	{
		SaveAll();
		printf("\nError2 happened: %s\n\n",ex[0].GetStr().CStr());
	}

	printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
	return 0;
}
