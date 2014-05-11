//Omid55
/*
 * separate_raw_urls.cpp
 *
 *  Created on: Nov 16, 2013
 *      Author: oaskaris
 */

//Omid55
#include "stdafx.h"
#include <cstdlib>
#include <cmath>

TVec<TwitterUrl> rawUrls;    // for each id rawUrls which it contains
#define LENGTH 10000

int main(int argc, char* argv[])
{
//	TZipIn zipDat("Raw1/RawUrls0_999999.rar");
//	rawUrls.Load(zipDat);
//	for(int i=0;i<5;i++)
//	{
//		printf("%s,%d\n",rawUrls[i].time.GetYmdTmStr().CStr(),rawUrls[i].urlsV.Len());
//	}
//	return 1;


	TExeTm ExeTm;
	int i,ct,u,indx = 0;

	if(argc > 1)
	{
		ct = atoi(argv[1]);
	}
	else
	{
		printf("YOU SHOULD SET THE INDICES...\n\n");
		return 1;
	}

	Env = TEnv(argc, argv, TNotify::StdNotify);
	printf(":::::::: Separating(GOOD) ::::::::\n");
	Env.PrepArgs(TStr::Fmt("\nSeparating Raw Urls, build %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		TZipIn ZquotesIn(TStr::Fmt("/NS/twitter-5/work/oaskaris/TwitterRAWUrlsData%d.rar",ct));
		rawUrls.Load(ZquotesIn);
		printf("TwitterRAWUrlsData%d loading done, it contains %d quotes.\n",ct,rawUrls.Len());

		TVec<TwitterUrl> res;
		for(u=0;u<rawUrls.Len();u++)
		{
			res.Add(rawUrls[u]);
			if(res.Len()==LENGTH || u==rawUrls.Len()-1)
			{
				TZipOut	zipData(TStr::Fmt("Raw%d/RawUrls%d.rar",ct,indx++));
				res.Save(zipData);
				res.Clr();
			}
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

