// Omid55
/*
 * find_posts_propagated_over_twitter.cpp
 *
 *  Created on: Dec 27, 2013
 *      Author: oaskaris
 */

// Omid55
#include "stdafx.h"
#include <postgresql/libpq-fe.h>
#include <sqlite3.h>

// input datasets
THash< TChA , TUInt > posts;
TVec< TwitterUrl > twUrlsV;
// input datasets


// output dataset
THash< TUInt , TSecTmV > postsPropagatedOverTw;
// output dataset


void SaveAll()
{
	printf("\n<<< SAVING STARTS (PLEASE BE PATIENT!!!) >>> .......\n");
	TZipOut zo("PostsPropagatedOverTwitterFullUrls.rar");
	postsPropagatedOverTw.Save(zo);
	printf("The size of PostsPropagatedOverTwitterFullUrls was: %d\n",postsPropagatedOverTw.Len());

	printf("\n<<<<<<<< SAVING DONE >>>>>>>>\n\n");
}


int main(int argc, char* argv[])
{
//	TZipIn z1("PostsPropagatedOverTwitterRawUrls.rar");
//	postsPropagatedOverTw.Load(z1);
//	printf("PostsPropagatedOverTwitterRawUrls loading done, it contains %d posts.\n",postsPropagatedOverTw.Len());
//	long long l1 = 0;
//	for(int i=0;i<postsPropagatedOverTw.Len();i++)
//	{
//		l1+=postsPropagatedOverTw[i].Len();
//	}
//
//	postsPropagatedOverTw.Clr();
//
//	TZipIn z2("PostsPropagatedOverTwitterFullUrls.rar");
//	postsPropagatedOverTw.Load(z2);
//	printf("PostsPropagatedOverTwitterFullUrls loading done, it contains %d posts.\n",postsPropagatedOverTw.Len());
//	long long l2 = 0;
//	for(int i=0;i<postsPropagatedOverTw.Len();i++)
//	{
//		l2+=postsPropagatedOverTw[i].Len();
//	}
//
//	cout << "\n\n\nRaw All Items: " << l1 << "\n" << "Full All Items: " << l2 << endl;
//	return 0;


//	TZipIn z1("PostsPropagatedOverTwitterData.rar");
//	postsPropagatedOverTw.Load(z1);
//	int len1 = 0;
//	for(int o=0;o<postsPropagatedOverTw.Len();o++)
//	{
//		len1 += postsPropagatedOverTw[o].Len();
//	}
//	postsPropagatedOverTw.Clr();
//
//	TZipIn z2("PostsPropagatedOverTwitterData_FULL.rar");
//	postsPropagatedOverTw.Load(z2);
//	int len2 = 0;
//	for(int o=0;o<postsPropagatedOverTw.Len();o++)
//	{
//		len2 += postsPropagatedOverTw[o].Len();
//	}
//
//	printf("RAW Len:%d\nFULL Len: %d\n",len1,len2);
//	return 0;


//	// FINDING ONE SPECIAL QUOTE'S URLS CASCADE
//	TStr cont =  "he was out there which was good that's better than not being out there"; //"i'm sure there are many more ways to build great freemium applications but one evernote has stood out for me above all the others";
//
//	TZipIn ZquotesIn("QuotesPreprocessedData.rar");
//	THash< TStr , CascadeElementV > preprocessedQuotes;
//	preprocessedQuotes.Load(ZquotesIn);
//	printf("QuotesPreprocessed loading done, it contains %d quotes.\n",preprocessedQuotes.Len());
//
//	int qq = preprocessedQuotes.GetKeyId(cont);
//
//	TZipIn ZpostsIn("PostsData.rar"); 		// <<<<< CHANGE THIS ONE TO ALL URLS OF POST >>>>>
//	posts.Load(ZpostsIn);
//	printf("PostsData loading done, it contains %d posts.\n",posts.Len());
//
////	TUInt pidd = posts.GetDat("http://37signals.com/svn");
////	printf("PostId: %d\n",pidd.Val);
//
//	CascadeElementV ces = preprocessedQuotes.GetDat(cont);
//	for(int i=0;i<ces.Len();i++)
//	{
//		printf("%d: %d,%s,%s\n",i,ces[i].post.Val,ces[i].time.GetDtYmdStr().CStr(),posts.GetKey(ces[i].post).CStr());
//	}
//	printf("\n\n\n");
//
//	TZipIn ZpostsPropIn("PostsPropagatedOverTwitterData.rar");
//	postsPropagatedOverTw.Load(ZpostsPropIn);
//	printf("postsPropagatedOverTw loading done, it contains %d posts.\n",postsPropagatedOverTw.Len());
//	for(int i=0;i<ces.Len();i++)
//	{
//		TUInt p = ces[i].post;
//		if(postsPropagatedOverTw.GetKeyId(p)!=-1)
//		{
//			if(postsPropagatedOverTw.GetDat(p)[0]<preprocessedQuotes[qq][0].time)
//			{
//				TStr postContent = posts.GetKey(p);
//				printf("%s\n",postContent.CStr());
//			}
//		}
//	}
//	return 0;

//	TZipIn twU("/NS/twitter-5/work/oaskaris/FINALFULLS/FULLTwitterAllUrlsData1.rar");    	// "/NS/twitter-5/work/oaskaris/FINALRAWS/TwitterRAWUrlsData%d.rar"
//	twUrlsV.Load(twU);
//	printf("FULLTwitterAllUrlsData1 loading done, it contains %d items.\n",twUrlsV.Len());      ///printf("TwitterRAWUrlsData%d loading done, it contains %d items.\n",ct,twUrlsV.Len());
//	TChA cc = twUrlsV[0].urlsV[0].ToLc();
//	cc.Trunc();
//	TChA ul("http://");
//	ul += cc;
//	ul = ul.ToLc();
//	printf("%s\n\n",ul.CStr());
//	return 0;


//	TZipIn ZpostssIn("PostsData.rar"); 		// <<<<< CHANGE THIS ONE TO ALL URLS OF POST >>>>>
//	posts.Load(ZpostssIn);
//	for(int i=0;i<10;i++)
//	{
//		printf("%s\n", posts.GetKey(i).CStr());
//	}
//	return 0;

//	TZipIn twU1("TwitterRAWUrlsData9.rar");
//	twUrlsV.Load(twU1);
//	int c = 2000;
//	while(c<twUrlsV.Len() && twUrlsV[c].urlsV.Len()==0)
//	{
//		c++;
//	}
//	printf("tw9[%d]: %s\n\n",c,twUrlsV[c].urlsV[0].CStr());
//	twUrlsV.Clr();
//
//	TZipIn twU2("TwitterRAWUrlsData2.rar");
//	twUrlsV.Load(twU2);
//	c = 50;
//	while(c<twUrlsV.Len() && twUrlsV[c].urlsV.Len()==0)
//	{
//		c++;
//	}
//	printf("tw2[%d]: %s\n\n",c,twUrlsV[c].urlsV[0].CStr());
//	twUrlsV.Clr();
//
//	TZipIn twU3("TwitterRAWUrlsData17.rar");
//	twUrlsV.Load(twU3);
//	c = 0;
//	while(c<twUrlsV.Len() && twUrlsV[c].urlsV.Len()==0)
//	{
//		c++;
//	}
//	printf("tw17[%d]: %s\n\n",c,twUrlsV[c].urlsV[0].CStr());
//	twUrlsV.Clr();
//	return 0;


	int id,iddd;
	int LEN = 10;
	TExeTm ExeTm;
	PGconn *conn;
	PGresult *res;
	int rec_count,row,ct,q,total_number_tweets = 0;

	printf(":::::::: Find Posts Urls ::::::::\n");
	//const TStr StartDate = Env.GetIfArgPrefixStr("-sd:", "2008-08-01 00:00:00", "Starting date");
	//const TStr EndDate = Env.GetIfArgPrefixStr("-ed:", "2009-10-01 00:00:00", "Ending date");

	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nFinding the cascades of the desired quotes in content and their urls in urls. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		TZipIn ZpostsIn("/NS/twitter-5/work/oaskaris/PostsData.rar");
		posts.Load(ZpostsIn);
		printf("PostsData loading done, it contains %d posts.\n",posts.Len());

//		TUInt nn1 = posts.AddDat(TChA("http://myloc.me/7obd"));
//		TUInt nn2 = posts.AddDat(TChA("yahoooooo.com"));
//		TUInt nn3 = posts.AddDat(TChA("thisisindexed.com"));
//		TUInt nn4 = posts.AddDat(TChA("http://twitpic.com/1l69o"));
//		printf("THESE: %d,%d,%d,%d",nn1.Val,nn2.Val,nn3.Val,nn4.Val);

		for(ct=1;ct<=LEN;ct++)
		{
			TZipIn twU(TStr::Fmt("/NS/twitter-5/work/oaskaris/FINALFULLS/FULLTwitterAllUrlsData%d.rar",ct));    	//   "/NS/twitter-5/work/oaskaris/FINALRAWS/TwitterRAWUrlz%d.rar"
			twUrlsV.Load(twU);
			printf("FULLTwitterAllUrlsData%d loading done, it contains %d items.\n",ct,twUrlsV.Len());      ///printf("TwitterRAWUrlsData%d loading done, it contains %d items.\n",ct,twUrlsV.Len());

			for(int i=0;i<twUrlsV.Len();i++)
			{
				for(int j=0;j<twUrlsV[i].urlsV.Len();j++)
				{
					TChA cc = twUrlsV[i].urlsV[j].ToLc();
					cc.Trunc();
					TChA ul("http://");
					ul += cc;
					id = posts.GetKeyId(ul);
					if(id == -1)
					{
						TChA ul("https://");
						ul += cc;
						id = posts.GetKeyId(ul);
					}

					if(id != -1)    // if there exists
					{
						iddd = postsPropagatedOverTw.GetKeyId(id);
						if(iddd == -1)
						{
							postsPropagatedOverTw.AddDat(id).Add(twUrlsV[i].time);
						}
						else
						{
							TSecTmV* tv = &postsPropagatedOverTw.GetDat(id);
							tv->AddSorted(twUrlsV[i].time);
						}
					}
				}
			}
		}


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




