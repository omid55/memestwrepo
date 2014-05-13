// Omid55
/*
 * plot_hist_centered_both_cascades.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: omid55
 */
// Omid55
#include "stdafx.h"

int main(int argc, char* argv[])
{
	TExeTm ExeTm;

	printf("((( Starting The Plot Hist BOTH Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// URLS
		THash< TStr , CascadeElementV > quotes1;
		THash< TUInt , TSecTmV > twitter1;
		// ---== Loading Data ==---
		TZipIn ZquotesIn1("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");
//		TZipIn ZquotesIn1("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");
		quotes1.Load(ZquotesIn1);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS has instances: %d\n\n\n",quotes1.Len());

		TZipIn Zcascades1("CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");
//		TZipIn Zcascades1("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");
		twitter1.Load(Zcascades1);
		printf("Loaded CascadesFullUrlsOnTwitterData_FINALFILTERED has instances: %d\n\n\n",twitter1.Len());

//		// CONTENTS
//		THash< TStr , CascadeElementV > quotes2;
//		THash< TUInt , TSecTmV > twitter2;
//		// ---== Loading Data ==---
//		TZipIn ZquotesIn2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");
//		quotes2.Load(ZquotesIn2);
//		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents has instances: %d\n\n\n",quotes2.Len());
//
//		TZipIn Zcascades2("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar");
//		twitter2.Load(Zcascades2);
//		printf("Loaded CascadesOnTwitterData_FINALFILTERED has instances: %d\n\n\n",twitter2.Len());


		// Plotting
		Tools::plotTwoHistShift(quotes1,twitter1,3600,"hours","HistUrlsMedian",MEDIAN,"Memes","urls on Twitter");
//		Tools::plotTwoHistShift(quotes1,twitter1,3600,"hours","HistUrlsMax", MAX,"Memes","urls on Twitter");
//		Tools::plotTwoHistShift(quotes2,twitter2,3600,"hours","HistContentsMedian",MEDIAN,"Memes","contents on Twitter");
//		Tools::plotTwoHistShift(quotes2,twitter2,3600,"hours","HistContentsMax",MAX,"Memes","contents on Twitter");


		printf("\nPlots had been drawn successfully.");
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
