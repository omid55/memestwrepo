// Omid55
/*
 * select_and_save_quotes_cascaded_both.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: omid55
 */


#include "stdafx.h"

THash< TStr , CascadeElementV > quotes;
THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
//THash< TUInt , TSecTmV > cascadesOnTwitterContents;


int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	int c,quoteIndex;

	printf("((( SELECTING AND SAVING THE QUOTES WHICH THEIR URLS ARE CASCADED OVER TWITTER )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nSelect and save quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// ---== Loading Data ==---
		TZipIn ZquotesIn("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY has instances: %d\n\n\n",quotes.Len());

		TZipIn ZcascadesOnTwitterIn("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn);
		printf("Loaded CascadesFullUrlsOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());

//		TZipIn ZIn("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
//		cascadesOnTwitterContents.Load(ZIn);
//		printf("Loaded CascadesOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterContents.Len());


		THash<TStr,CascadeElementV> result;
		for(c=0;c<cascadesOnTwitterUrls.Len();c++)
		{
			quoteIndex = cascadesOnTwitterUrls.GetKey(c);
			TStr v1 = quotes.GetKey(quoteIndex);
			CascadeElementV v2 = quotes[quoteIndex];
			result.AddDat(v1,v2);
		}
		TZipOut zout("QuotesPreprocessedData_NIFTY_SUBSETTED.rar");
		result.Save(zout);
		printf("The size of QuotesPreprocessedData_NIFTY_SUBSETTED was: %d\n",result.Len());
		printf("\n\nALL DONE\n\n");
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
