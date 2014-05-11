// Omid55
/*
 * pack_twitter_real_urls.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: oaskaris
 */

// Omid55
#include "stdafx.h"
TVec< TwitterUrl > realUrls;    // for each id realUrls which it contains


int main(int argc, char* argv[])
{
//	int ctt = atoi(argv[1]);
//	int id = atoi(argv[2]);
//	TVec< TwitterUrl > rw;
////	TZipIn zin1(TStr::Fmt("/NS/twitter-5/work/oaskaris/FINALRAWS/TwitterRAWUrlsData%d.rar",ctt));
////	rw.Load(zin1);
////	printf("TwitterRAWUrlsData%d loading done, it contains %d quotes.\n",ctt,rw.Len());
//
//	TVec< TwitterUrl > ru;
//	TZipIn zin2(TStr::Fmt("/NS/twitter-5/work/oaskaris/FINALFULLS/FULLTwitterAllUrlsData%d.rar",ctt));
//	ru.Load(zin2);
//	printf("FULLTwitterRealUrlsData%d loading done, it contains %d quotes.\n",ctt,ru.Len());
//
////	printf("RAW:\n");
////	printf("%s: \n",rw[id].time.GetYmdTmStr().CStr());
////	for(int i=0;i<rw[id].urlsV.Len();i++)
////	{
////		printf("%s\n",rw[id].urlsV[i].CStr());
////	}
////	printf("\n\n\n");
//
//	printf("REAL:\n");
//	printf("%s: \n",ru[id].time.GetYmdTmStr().CStr());
//	for(int i=0;i<ru[id].urlsV.Len();i++)
//	{
//		printf("%s\n",ru[id].urlsV[i].CStr());
//	}
//	printf("\n\n");
//	return 0;


	bool cont = true;
	TExeTm ExeTm;
	int c, idx = 12000, ct = 3, Leng = 39095, len = 4000;
	printf(":::::::: Pack Real Urls of Tweets ::::::::\n");
	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nPackaging the real urls obtained from Twitter build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		while(cont && ++ct)
		{
			for(c=0;c<len;c++,idx++)
			{
				if(idx >= Leng)
				{
					cont = false;
					break;
				}

				TVec<TwitterUrl> u;
				TZipIn zin(TStr::Fmt("REAL/AllUrlZ%d.rar",idx));
				u.Load(zin);
				printf("AllUrlZ%d loading done, it contains %d urls.\n", idx,u.Len());
				realUrls.AddV(u);
			}

			printf("\n<<< REAL URLS SAVING STARTS (PLEASE BE PATIENT!!!) >>> .......\n");
			TZipOut cascadesOnTwitterData(TStr::Fmt("/NS/twitter-5/work/oaskaris/FINALFULLS/FULLTwitterAllUrlsData%d.rar",ct));
			realUrls.Save(cascadesOnTwitterData);
			printf("The size of Full Urls %d was: %d\n",ct,realUrls.Len());
			realUrls.Clr();

			//system(TStr::Fmt("mv FULLTwitterAllUrlsData%d.rar /NS/twitter-5/work/oaskaris/FINALFULLS/",ct).CStr());
		}
		printf("\n\n ---=== EVERYTHING DONE ===---\n");
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

