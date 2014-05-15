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
//	// test with toy example
//	THash< TStr , CascadeElementV > qq1;
//	THash< TUInt , TSecTmV > tt1;
//	TStr emp("");
//	CascadeElementV v;
//	TSecTm t1(2008,5,5,1,10,0);
//	TSecTm t2(2008,8,1,2,2,0);
//	TSecTm t3(2008,8,2,9,1,0);
//	TSecTm t4(2008,8,4,3,0,0);
//	v.Add(CascadeElement(t1));
//	v.Add(CascadeElement(t2));
//	v.Add(CascadeElement(t3));
//	v.Add(CascadeElement(t4));
//	qq1.AddDat(emp,v);
//
//	TSecTmV vv;
//	vv.Add(TSecTm(2008,8,3,0,0,0));
//	vv.Add(TSecTm(2008,8,20,0,0,0));
//	vv.Add(TSecTm(2008,10,28,0,0,0));
//	tt1.AddDat(1,vv);
//	uint per = 24 * 3600;
//	char pst[] = "days";
//	Tools::plotTwoHistShift(qq1,tt1,per,pst,"HistUrlsMedian",MEDIAN,"Memes","Twitter");
//
//	return 0;
//// ----------------------------------------


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
		TZipIn ZquotesIn1("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");
		quotes1.Load(ZquotesIn1);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS has instances: %d\n\n\n",quotes1.Len());

		TZipIn Zcascades1("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");
		twitter1.Load(Zcascades1);
		printf("Loaded CascadesFullUrlsOnTwitterData_FINALFILTERED has instances: %d\n\n\n",twitter1.Len());

		// CONTENTS
		THash< TStr , CascadeElementV > quotes2;
		THash< TUInt , TSecTmV > twitter2;
		TZipIn ZquotesIn2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");
		quotes2.Load(ZquotesIn2);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents has instances: %d\n\n\n",quotes2.Len());

		TZipIn Zcascades2("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar");
		twitter2.Load(Zcascades2);
		printf("Loaded CascadesOnTwitterData_FINALFILTERED has instances: %d\n\n\n",twitter2.Len());


		// Plotting
		Tools::plotTwoIndividuallyShift(quotes1,twitter1,period,periodstr,"IndividualUrls");
		Tools::plotTwoIndividuallyShift(quotes2,twitter2,period,periodstr,"IndividualContents");


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
