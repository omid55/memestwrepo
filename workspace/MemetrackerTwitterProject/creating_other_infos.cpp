//Omid55

/*
 * creating_other_infos.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: oaskaris
 */

//Omid55
#include "stdafx.h"
#include "snap/memes.h"
#include <stdlib.h>
#include <cstdlib>
using namespace std;

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

// Datasets
THash< TStr , CascadeElementV > quotes;  // for each quote what is the cascade times in memetracker dataset
THash< TChA , TUInt > posts;  // for each quote what is the cascade times in memetracker dataset
TUInt posts_cnt = 0;
THash< TUInt , TUInt > wordsCount;
THash< TUInt , TStr > sites;
// Datasets

void SaveAll()
{
	// Saving words count
	TZipOut Zwords("WordsCountData.rar");
	wordsCount.Save(Zwords);
	printf("\n\n\nThe size of wordsCount was: %d\n",wordsCount.Len());

	// Saving sites
	TZipOut Zsites("SitesData.rar");
	sites.Save(Zsites);
	printf("The size of sites was: %d\n\n",sites.Len());

	printf("\n\nSAVING DONE.\n");
}


int main(int argc, char* argv[])
{
	printf("Starting plotting memes cascades code...\n");
	TExeTm ExeTm;
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPloting the cascades from propagation the quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		TZipIn ZquotesIn("QuotesData.rar");
		quotes.Load(ZquotesIn);
		printf("\nThe size of Quotes is: %d\n",quotes.Len());

		TZipIn ZpostsIn("PostsData.rar");
		posts.Load(ZpostsIn);
		printf("\nThe size of Posts is: %d\n",posts.Len());


		// Words count saving
		for(int i=0;i<quotes.Len();i++)
		{
			wordsCount.AddDat(i,TStrUtil::CountWords(quotes.GetKey(i)));
			//wordsCount.AddDat(i,quotes.GetKey(i).CountCh(' ',0) + 1);
		}

		// Sites saving
		for(int i=0;i<posts.Len();i++)
		{
			sites.AddDat(i,TStrUtil::GetWebsiteNm(posts.GetKey(i)));
			//sites.AddDat(i,getWebsite(posts.GetKey(i)));
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

