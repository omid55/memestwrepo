// Omid55
/*
 * plot_individually_centered_both_cascades.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: omid55
 */

#include "stdafx.h"

int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	uint period = 3600;   // Hour
	char* periodstr = TStr("hour").GetCStr();
	printf("((( START individually Plot BOTH Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Individually Memes-Twitter Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// URLS
		THash< TStr , CascadeElementV > quotes1;
		THash< TUInt , TSecTmV > twitter1;
		// ---== Loading Data ==---
		TZipIn ZquotesIn1("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");
//		TZipIn ZquotesIn1("QuotesPreprocessedData_NIFTY_SUBSETTED.rar");
		quotes1.Load(ZquotesIn1);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS has instances: %d\n\n\n",quotes1.Len());

		TZipIn Zcascades1("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");
//		TZipIn ZcascadesOnTwitterIn("CascadesFullUrlsOnTwitterData.rar");
		twitter1.Load(Zcascades1);
		printf("Loaded CascadesFullUrlsOnTwitterData_FINALFILTERED has instances: %d\n\n\n",twitter1.Len());

		Tools::plotTwoIndividuallyShift(quotes1,twitter1,period,periodstr,"IndividualUrls");
		quotes1.Clr();
		twitter1.Clr();


		// CONTENTS
		THash< TStr , CascadeElementV > quotes2;
		THash< TUInt , TSecTmV > twitter2;
		// ---== Loading Data ==---
//		TZipIn ZquotesIn2("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");
		TZipIn ZquotesIn2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");
//		TZipIn ZquotesIn2("QuotesPreprocessedData_NIFTY_SUBSETTED.rar");
		quotes2.Load(ZquotesIn2);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents has instances: %d\n\n\n",quotes2.Len());

		twitter2.Clr();
		TZipIn Zcascades2("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar");
		twitter2.Load(Zcascades2);
		printf("Loaded CascadesOnTwitterData_FINALFILTERED has instances: %d\n\n\n",twitter2.Len());

		Tools::plotTwoIndividuallyShift(quotes2,twitter2,period,periodstr,"IndividualContents");
		quotes2.Clr();
		twitter2.Clr();


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
