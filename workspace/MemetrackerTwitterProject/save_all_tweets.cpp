// Omid55

/*
 * save_all_tweets.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: oaskaris
 */

// Omid55
// Codes for Twitter data saving
#include "stdafx.h"

uint LENGT =   100000000;     // maximum 1755925520
uint SAVELEN = 1000000;
uint begin,end;

TPair<TStrV,TSecTmV> Tweets;

int nowIdx = 0;
void SaveAll()
{
	if(Tweets.Val1.Len()!=Tweets.Val2.Len())
	{
		printf("ERROR, DIFFERENT SIZES OF VECTORS ERROR, SAVE IS TERMINATED\n\n\n");
		return;
	}
	TZipOut outData(TStr::Fmt("TweetsData_%d_%d.rar",begin+SAVELEN*nowIdx,min(begin+SAVELEN*nowIdx+Tweets.Val1.Len()-1,end)));

	Tweets.Save(outData);
	printf("The size of Tweets was: %d\n",Tweets.Val1.Len());
	Tweets.Val1.Clr();
	Tweets.Val2.Clr();
	printf("\n<<<<<<<< SAVING DONE >>>>>>>>\n\n");
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


int main(int argc, char* argv[])
{
//	try
//	{
//		TZipIn inData("TweetsData_71343432_81343431.rar");
//		Tweets.Load(inData);
//
//		printf("The size of Tweets was: %d\n",Tweets.Val1.Len());
//		if(Tweets.Val1.Len()!=Tweets.Val2.Len())
//		{
//			printf("ERROR, DIFFERENT SIZES OF VECTORS ERROR, SAVE IS TERMINATED\n\n\n");
//			return 1;
//		}
//		for(int i=0;i<Tweets.Val1.Len();i++)
//		{
//			printf("%s -> %s\n",Tweets.Val1[i].CStr(),Tweets.Val2[i].GetYmdTmStr().CStr());
//		}
//	}
//	catch(TPt<TExcept>& ex)
//	{
//		printf("\nError2 happened: %s\n\n",ex[0].GetStr().CStr());
//	}
//	return 0;


	int myindex = 0;   // set it from 1
	if(argc>1)
	{
		myindex = TStr(argv[1]).GetInt()-1;
	}
	else
	{
		printf("YOU SHOULD SET THE INDEX...\n\n");
		return 1;
	}
	printf("MyIndex-1: %d\n\n",myindex);

	//select max(id) from tweets where tweettime >= timestamp '2008-08-01 00:00:00' and tweettime < timestamp '2009-10-01 00:00:00';
	//select min(id) from tweets where tweettime >= timestamp '2008-08-01 00:00:00' and tweettime < timestamp '2009-10-01 00:00:00';

	TExeTm ExeTm;
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;
	int total_number_tweets = 0;
	TStr tweetStr("");
	begin = 71343432 + LENGT * myindex;
	end = min(begin + LENGT - 1,1755925519);
	if(end-begin<=0)
	{
		printf("\n ==-- THE END PAL --== ;)\n\n");
		return 0;
	}

	printf(":::::::: Save Tweets in Specified Range (WHOLE 71343432 TO 1755925519) ::::::::\n");
	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nFinding the cascades of the desired quotes in content and their urls in urls. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

		if (PQstatus(conn) == CONNECTION_BAD)
		{
			printf("We were unable to connect to the database");
			fstream err(TStr::Fmt("NoDb%d.txt",myindex).CStr(),ios::out);
			err.close();
			return 1;
		}

		// we use cursors/fetch to speed up the process; batch of 10000 tweets
		PQexec(conn, "begin work");
		PQexec(conn, TStr::Fmt("declare mycursor cursor for select tweettext, extract(epoch from tweettime) from tweets where id >= %d and id <= %d",begin,end).CStr());

		while(begin+SAVELEN*nowIdx<=end)
		{
			res = PQexec(conn, TStr::Fmt("FETCH %d IN mycursor",SAVELEN).CStr());    // all of them are: 1684582088

			if(fileExists(TStr::Fmt("TweetsData_%d_%d.rar",begin+SAVELEN*nowIdx,min(begin+SAVELEN*nowIdx+Tweets.Val1.Len()-1,end))))
			{
				printf("WE HAVE IT DUDE ;) (%s)\n\n",TStr::Fmt("TweetsData_%d_%d.rar",begin+SAVELEN*nowIdx,min(begin+SAVELEN*nowIdx+Tweets.Val1.Len()-1,end)).CStr());
				nowIdx++;
				continue;
			}

			if (PQresultStatus(res) == PGRES_TUPLES_OK)
			{
				rec_count = PQntuples(res);
				total_number_tweets += rec_count;
				printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

				for (row=0; row<rec_count; row++)
				{
//					if(row%(rec_count/10) == 0)
//					{
//						printf("Row%d is processing.\n",row);
//					}
					tweetStr = PQgetvalue(res, row, 0);
					Tweets.Val1.Add(tweetStr.ToLc());
					Tweets.Val2.Add(TSecTm(TStr(PQgetvalue(res, row, 1)).GetFlt()));
				}

				PQclear(res);

				SaveAll();
				nowIdx++;
			}
			else
			{
				rec_count = 0;
			}
		}

		PQexec(conn, "close mycursor");
		PQexec(conn, "commit work");

		PQfinish(conn);

		printf("\n\nFINDING THE TWEETS IS DONE\n\n");
		// Requesting the database


		if(Tweets.Val1.Len()!=0)
		{
			printf("\nIT SHOULD NOT BE LIKE THIS ....\n\n");
			SaveAll();
		}
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




