// Omid55

/*
 * plotccdf_memes_twitter.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: omid55
 */

#include "stdafx.h"


int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	printf("((( Starting The Plot CCDF Meme-Twitter Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nCCDF Plotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// ---== Loading Data ==---
		THash< TStr , CascadeElementV  > quotes;
		THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
		THash< TUInt , TSecTmV > cascadesOnTwitterContents;
		TZipIn ZquotesIn("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS has instances: %d\n\n\n",quotes.Len());

		TZipIn ZcascadesOnTwitterIn("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");   //("CascadesFullUrlsOnTwitterData_FILTERED.rar");
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn);
		printf("Loaded CascadesFullUrlsOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());

		TZipIn ZIn("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar"); 		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
		cascadesOnTwitterContents.Load(ZIn);
		printf("Loaded CascadesOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterContents.Len());


		// Plotting
		printf("\n\n\nPlotting...\n");
		Tools::plotCCDFStartMedianEnd(quotes,cascadesOnTwitterUrls,"Urls");
		Tools::plotCCDFStartMedianEnd(quotes,cascadesOnTwitterUrls,"Contents");
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


