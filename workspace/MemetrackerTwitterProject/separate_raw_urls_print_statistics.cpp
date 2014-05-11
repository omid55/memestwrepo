//Omid55
/*
 * separate_raw_urls_print_statistics.cpp
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
	TExeTm ExeTm;
	int num,i,ct,u,indx = 0;

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

		num = ceil( (double)rawUrls.Len() / LENGTH );
		printf("Number of files: %d\n\n",num);
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

