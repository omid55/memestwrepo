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
		THash< TStr , CascadeElementV  > quotesurl,quotescont;
		THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
		THash< TUInt , TSecTmV > cascadesOnTwitterContents;
//		TZipIn ZquotesIn1("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
//		quotesurl.Load(ZquotesIn1);
//		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS has instances: %d\n\n\n",quotesurl.Len());
//
//		TZipIn ZcascadesOnTwitterIn1("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");   //("CascadesFullUrlsOnTwitterData_FILTERED.rar");
//		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn1);
//		printf("Loaded CascadesFullUrlsOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());
//
//		TZipIn ZquotesIn2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
//		quotescont.Load(ZquotesIn2);
//		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents has instances: %d\n\n\n",quotescont.Len());
//
//		TZipIn ZcascadesOnTwitterIn2("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar"); 		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
//		cascadesOnTwitterContents.Load(ZcascadesOnTwitterIn2);
//		printf("Loaded CascadesOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterContents.Len());


		// REMOVE IT
		TZipIn ZquotesIn1("Quotes_TEST_4Urls.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotesurl.Load(ZquotesIn1);
		printf("Loaded Quotes_TEST_4Urls has instances: %d\n\n\n",quotesurl.Len());

		TZipIn ZcascadesOnTwitterIn1("Cascades_TEST_4Urls.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");   //("CascadesFullUrlsOnTwitterData_FILTERED.rar");
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn1);
		printf("Loaded Cascades_TEST_4Urls has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());

		TZipIn ZquotesIn2("Quotes_TEST_4Contents.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotescont.Load(ZquotesIn2);
		printf("Loaded Quotes_TEST_4Contents has instances: %d\n\n\n",quotescont.Len());

		TZipIn ZcascadesOnTwitterIn2("Cascades_TEST_4Contents.rar"); 		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
		cascadesOnTwitterContents.Load(ZcascadesOnTwitterIn2);
		printf("Loaded Cascades_TEST_4Contents has instances: %d\n\n\n",cascadesOnTwitterContents.Len());
		// REMOVE IT


		// Plotting
		printf("\n\n\nPlotting...\n");
		Tools::plotCCDFStartMedianEnd(quotesurl,cascadesOnTwitterUrls,"Urls");
		Tools::plotCCDFStartMedianEnd(quotescont,cascadesOnTwitterContents,"Contents");
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


