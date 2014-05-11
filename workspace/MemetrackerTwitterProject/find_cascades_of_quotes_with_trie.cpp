// Omid55
// Code for searching quotes over tweets with TStr Trie
//find_cascades_of_quotes_with_trie
#include "TStrTrie.h"
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
/* THash< TStr , CascadeElementV > quotes; */
// input datasets

// output dataset
THash<TUInt,TSecTmV> CascadesOnTwitter;
// output dataset

void SaveAll()
{
	printf("\n<<< SAVING STARTS (PLEASE BE PATIENT!!!) >>> .......\n");
	TZipOut cascadesOnTwitterData("CascadesOnTwitterData.rar");
	CascadesOnTwitter.Save(cascadesOnTwitterData);
	printf("The size of CascadesOnTwitter was: %d\n",CascadesOnTwitter.Len());
	printf("\n<<<<<<<< SAVING DONE >>>>>>>>\n\n");
}


int main(int argc, char* argv[])
{
//	int num;
//	THash<TUInt,TUIntV> cid;
//	TZipIn zin("/home/oaskaris/realus/CascadesOnTwitterData.rar");
//	cid.Load(zin);
//	printf("CascadesOnTwitterData loading done, it contains %d items.\n",cid.Len());
//
//	THash< TStr , CascadeElementV > quo;
//	TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY.rar");
//	quo.Load(ZquotesIn);
//	printf("QuotesPreprocessed loading done, it contains %d quotes.\n",quo.Len());
//
//	while(true)
//	{
//		cout << "\n\nPlease enter num: ";
//		cin >> num;
//		TUInt qid = cid.GetKey(num);
//		cout << "\n\nQuote: " << quo.GetKey(qid.Val).CStr() << endl;
//		int leng = ((cid.GetDat(qid).Len()>10) ? 10 : cid.GetDat(qid).Len());
//		for(int i=0;i<leng;i++)
//		{
//			cout << cid.GetDat(qid)[i].Val << " ";
//		}
//	}
//	//	TZipIn ZquotesIn("CascadesOnTwitterData.rar");
//	//	CascadesOnTwitter.Load(ZquotesIn);
//	//	printf("CascadesOnTwitterData1 loading done, it contains %d items.\n",CascadesOnTwitter.Len());
//
//	return 0;

//	THash<TUInt,TSecTmV> justTen;
//	TZipIn ZquotesIn("CascadesOnTwitterData.rar");
//	CascadesOnTwitter.Load(ZquotesIn);
//	printf("QuotesPreprocessed loading done, it contains %d quotes.\n",CascadesOnTwitter.Len());
//	TZipIn ZIn("CascadesOnTwitterData_JUST10.rar");
//	justTen.Load(ZIn);
//	printf("justTen loading done, it contains %d quotes.\n",justTen.Len());
//	for(int i=0;i<10;i++)
//	{
//		if(CascadesOnTwitter.GetKeyId(i) != -1)
//		{
//			printf("F %d: %d\n",i,CascadesOnTwitter.GetDat(i).Len());
//			printf("S %d: %d\n",i,justTen.GetDat(i).Len());
//		}
//	}
//	printf("\n\nDONE\n");
//	return 0;


	TIntV foundIds;
	TStr qu;
	TStrTrie trie;
	TExeTm ExeTm;
	PGconn *conn;
	PGresult *res;
	int LEN,rec_count,row,q,i,id,total_number_tweets = 0;
	double tweet_date = 0;
	TStr TweetStr("");
	TStr TweetStrLc("");

	printf(":::::::: Find Cascades of Quotes In Twitter WITH TRIE FAST SEARCH (No Symbols and Numbers) ::::::::\n");
	const TStr StartDate = Env.GetIfArgPrefixStr("-sd:", "2008-08-01 00:00:00", "Starting date");
	const TStr EndDate = Env.GetIfArgPrefixStr("-ed:", "2009-10-01 00:00:00", "Ending date");

	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nFinding the cascades of the desired quotes in content and their urls in urls. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		/*
		// -- << Trie Creation and Save >> --
		trie.setDoRemoveSymbols(true);
		TZipIn ZquotesIn("QuotesData.rar");
		quotes.Load(ZquotesIn);
		CascadeElementV dummy;
		printf("QuotesPreprocessed loading done, it contains %d quotes.\n",quotes.Len());
		printf("Creating Quotes TStr Trie ...\n");
		for(q=0;q<quotes.Len();q++)
		{
			qu = quotes.GetKey(q);
			qu = qu.ToLc();
			trie.add(qu,q);
		}
//		quotes.Clr();
		printf("Saving The Trie ...\n");
		TZipOut outModel("QuotesTrieModel.rar");
		trie.Save(outModel);
		printf("TStr Trie Created and Saved Successfully.\n");
		return 0;
		// -- << Trie Creation and Save >> --
		 */


		// Loading trie model
		TZipIn trieModel("QuotesTrieModel.rar");
		trie.Load(trieModel);
		printf("\nMin Len is: %d, Removing Numbers and Symbols: %d\n\n",trie.getMinLen().Val,trie.getDoRemoveSymbols());


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
			res = PQexec(conn, "FETCH 1000000 IN mycursor");    // all of them are: 1684582084
			if (PQresultStatus(res) == PGRES_TUPLES_OK)
			{
				rec_count = PQntuples(res);
				total_number_tweets += rec_count;
				printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

				for (row=0; row<rec_count; row++)
				{
//					if(row>0 && row%(rec_count/100)==0)
//					{
//						printf("Row%d is processing.\n",row);
//					}

					tweet_date = TStr(PQgetvalue(res, row, 1)).GetFlt();
					TweetStrLc = TweetStr.ToLc();

					foundIds = trie.find(TweetStrLc);
					TSecTm td(tweet_date);
					for(i=0;i<foundIds.Len();i++)
					{
						q = foundIds[i];
						id = CascadesOnTwitter.GetKeyId(q);
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

		printf("\n\n\t<<((( ALL DONE )))>>\n\n");
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
