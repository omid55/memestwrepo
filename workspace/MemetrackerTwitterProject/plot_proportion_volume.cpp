// Omid55
/*
 * plot_proportion_volume.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: omid55
 */
#include "stdafx.h"

int main(int argc, char* argv[])
{
//	//-------------------------
//	// Toy example
//	int ind = atoi(argv[1]);
//	cout << "TESTING...\n\n\n";
//	THash< TStr , CascadeElementV > qq1;
//	THash< TUInt , TSecTmV > tt1;
//	CascadeElementV v1;
//	TSecTm t1(uint(3));
//	TSecTm t2(uint(5));
//	TSecTm t3(uint(6));
//	TSecTm t4(uint(7));
//	TSecTm t5(uint(7));
//	TSecTm t6(uint(8));
//	TSecTm t7(uint(11));
//	v1.Add(CascadeElement(t1));
//	v1.Add(CascadeElement(t2));
//	v1.Add(CascadeElement(t3));
//	v1.Add(CascadeElement(t4));
//	v1.Add(CascadeElement(t5));
//	v1.Add(CascadeElement(t6));
//	v1.Add(CascadeElement(t7));
//	qq1.AddDat("quote1",v1);
//	CascadeElementV v2;
//	TSecTm t12(uint(2));
//	TSecTm t22(uint(3));
//	TSecTm t32(uint(3));
//	TSecTm t42(uint(5));
//	v2.Add(CascadeElement(t12));
//	v2.Add(CascadeElement(t22));
//	v2.Add(CascadeElement(t32));
//	v2.Add(CascadeElement(t42));
//	qq1.AddDat("quote2",v2);
//
//	TSecTmV v3;
//	v3.Add(TSecTm(uint(2)));
//	v3.Add(TSecTm(uint(4)));
//	v3.Add(TSecTm(uint(6)));
//	v3.Add(TSecTm(uint(8)));
//	tt1.AddDat(0,v3);
//	TSecTmV v4;
//	v4.Add(TSecTm(uint(2)));
//	v4.Add(TSecTm(uint(4)));
//	v4.Add(TSecTm(uint(11)));
//	tt1.AddDat(1,v4);
//
//	uint per = 2;
//	printf("\nInputed period: %d\n\n", per);
//	char* pst = TStr::Fmt("%d units",per).CStr();
//
//	myplotTwoIndividuallyShiftProportionVolume(qq1,tt1,per,pst,"ToyProportion",ind);
//	return 0;
//	//-------------------------


	TExeTm ExeTm;
	int period = 3600;   // hour
	int index = atoi(argv[1]);   // index: 0 or 1 which proportion would you like this function to show
	char* periodstr = TStr("hour").GetCStr();
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Individually Memes-Twitter Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// URLS
		THash< TStr , CascadeElementV > quotes = Tools::loadQuotes("DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar");    // QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS
		THash< TUInt , TSecTmV > twitterUrls = Tools::loadTwitter("DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");     // CascadesFullUrlsOnTwitterData_FINALFILTERED

		// CONTENTS
		//THash< TStr , CascadeElementV > quotes2 = Tools::loadQuotes("DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar");    // QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents
		THash< TUInt , TSecTmV > twitterContents = Tools::loadTwitter("DATA/CascadesOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");    // CascadesOnTwitterData_FINALFILTERED

		THash< TUInt , TSecTmV > twitterTotal;
		for(int i=0;i<twitterContents.Len();i++)
		{
			TSecTmV tmp;
			tmp.AddV(twitterContents[i]);
			tmp.AddV(twitterUrls[i]);
			twitterTotal.AddDat(i,tmp);
		}

		// Plotting
		Tools::plotTwoIndividuallyShiftProportionVolume(quotes,twitterUrls,period,periodstr,"PropVolumeUrls","Urls",index);
		Tools::plotTwoIndividuallyShiftProportionVolume(quotes,twitterContents,period,periodstr,"PropVolumeContents","Contents",index);
		Tools::plotTwoIndividuallyShiftProportionVolume(quotes,twitterTotal,period,periodstr,"PropVolumeTotal","Total",index);

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

