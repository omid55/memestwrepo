// Omid55

/*
 * find_cascades_of_quotes_in_urls.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: oaskaris
 */

// Omid55
#include "stdafx.h"


// input datasets
THash< TStr , CascadeElementV > preprocessedQuotes;
THash< TUInt , TSecTmV > postsPropagatedOverTw;
// input datasets

// output dataset
THash<TUInt , TSecTmV> cascadesInUrlsOnTwitter;   // index of quote to a vector of times which is the times mentioned in Twitter in urls (sorted ascending)
// output dataset


void SaveAll()
{
	printf("\n<<< SAVING STARTS (PLEASE BE PATIENT!!!) >>> .......\n");
	TZipOut resOut("CascadesFullUrlsOnTwitterData.rar");
	cascadesInUrlsOnTwitter.Save(resOut);
	printf("The size of CascadesFullUrlsOnTwitterData was: %d\n",cascadesInUrlsOnTwitter.Len());

	printf("\n<<<<<<<< SAVING DONE >>>>>>>>\n\n");
}


int main(int argc, char* argv[])
{
	cout << "START...\n";
	THash< TChA , TUInt > posts;
	TZipIn ZpostsIn("/NS/twitter-5/work/oaskaris/PostsData.rar");
	posts.Load(ZpostsIn);
	printf("PostsData loading done, it contains %d posts.\n",posts.Len());

	TZipIn z2("CascadesFullUrlsOnTwitterData.rar");
	cascadesInUrlsOnTwitter.Load(z2);
	printf("CascadesFullUrlsOnTwitterData loading done, it contains %d items.\n",cascadesInUrlsOnTwitter.Len());

	TZipIn ZquotesIn("/NS/twitter-5/work/oaskaris/QuotesPreprocessedData_NIFTY.rar");
	preprocessedQuotes.Load(ZquotesIn);
	printf("QuotesPreprocessedData_NIFTY loading done, it contains %d quotes.\n",preprocessedQuotes.Len());

	int qoId = 1337058;
	cout << "\n\nQUOTE: " << preprocessedQuotes.GetKey(qoId).CStr() << endl << endl;
	for(int l=0;l<preprocessedQuotes[qoId].Len();l++)
	{
		cout << posts.GetKey(preprocessedQuotes[qoId][l].post).CStr() << " : " << preprocessedQuotes[qoId][l].time.GetYmdTmStr().CStr() << endl;
	}
	return 0;


	int cnt = 3;
	bool printed = false;
	while(!printed)
	{
		cnt++;
		for(int l=0;l<cascadesInUrlsOnTwitter.Len();l++)
		{
			int qID = cascadesInUrlsOnTwitter.GetKey(l);
			if(cascadesInUrlsOnTwitter[l][0].GetAbsSecs() < preprocessedQuotes[qID][0].time.GetAbsSecs())
			{
				if(preprocessedQuotes[qID].Len() > cnt)
				{
					continue;
				}
				printed = true;
				cout << "Twitter time: " << cascadesInUrlsOnTwitter[l][0].GetYmdTmStr().CStr() << endl;
				cout << "Memes time: " << preprocessedQuotes[qID][0].time.GetYmdTmStr().CStr() << endl;
				cout << "QID: " << qID << endl;
				cout << "\n\n\n";
			}
		}
	}
	return 0;



//	TZipIn z1("CascadesRawUrlsOnTwitterData.rar");
//	cascadesInUrlsOnTwitter.Load(z1);
//	printf("CascadesRawUrlsOnTwitterData loading done, it contains %d items.\n",cascadesInUrlsOnTwitter.Len());
//	long long l1 = 0;
//	for(int i=0;i<cascadesInUrlsOnTwitter.Len();i++)
//	{
//		l1+=cascadesInUrlsOnTwitter[i].Len();
//	}
//	cascadesInUrlsOnTwitter.Clr();
//
//	TZipIn z2("CascadesFullUrlsOnTwitterData.rar");
//	cascadesInUrlsOnTwitter.Load(z2);
//	printf("CascadesFullUrlsOnTwitterData loading done, it contains %d items.\n",cascadesInUrlsOnTwitter.Len());
//	long long l2 = 0;
//	for(int i=0;i<cascadesInUrlsOnTwitter.Len();i++)
//	{
//		l2+=cascadesInUrlsOnTwitter[i].Len();
//	}
//
//	cout << "\n\n\nRaw All Items: " << l1 << "\n" << "Full All Items: " << l2 << endl;
//	return 0;


//	TZipIn resIn("CascadesUrlsOnTwitterData.rar");
//	cascadesInUrlsOnTwitter.Load(resIn);
//	printf("The size of CascadesUrlsOnTwitter was: %d\n",cascadesInUrlsOnTwitter.Len());
//	for(int l=0;l<5;l++)
//	{
//		printf("\n\n\nQ%d:\n\n",l);
//		for(int o=0;o<cascadesInUrlsOnTwitter[l].Len();o++)
//		{
//			printf("%d. %s\n",o,cascadesInUrlsOnTwitter[l][o].GetYmdTmStr().CStr());
//		}
//	}
//	return 0;


	TExeTm ExeTm;
	unsigned int q,p;
	int id,i;
	TSecTmV* cascade;
	TSecTmV* res;
	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\n***(((Finding the cascades of the desired quotes in their urls)))***. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		TZipIn ZquotesIn("/NS/twitter-5/work/oaskaris/QuotesPreprocessedData_NIFTY.rar");
		preprocessedQuotes.Load(ZquotesIn);
		printf("QuotesPreprocessed loading done, it contains %d quotes.\n",preprocessedQuotes.Len());

		TZipIn ZpostsPropIn("PostsPropagatedOverTwitterFullUrls.rar");
		postsPropagatedOverTw.Load(ZpostsPropIn);
		printf("PostsPropagatedOverTwitterFullUrls loading done, it contains %d items.\n",postsPropagatedOverTw.Len());


		for(q=0;q<preprocessedQuotes.Len();q++)
		{
			for(p=0;p<preprocessedQuotes[q].Len();p++)
			{
				TUInt postId = preprocessedQuotes[q][p].post;
				if(postsPropagatedOverTw.GetKeyId(postId) != -1)
				{
					cascade = &postsPropagatedOverTw.GetDat(postId);
					id = cascadesInUrlsOnTwitter.GetKeyId(q);
					if(id == -1)
					{
						res = &cascadesInUrlsOnTwitter.AddDat(q);
						for(i=0;i<cascade->Len();i++)
						{
							res->AddSorted((*cascade)[i]);
						}
					}
					else
					{
						res = &cascadesInUrlsOnTwitter.GetDat(q);
						for(i=0;i<cascade->Len();i++)
						{
							res->AddSorted((*cascade)[i]);
						}
					}
				}
			}
		}

		printf("\n\nFINDING THE CASCADES OF QUOTES WITH URLS OVER TWITTER IS DONE\n\n");

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
