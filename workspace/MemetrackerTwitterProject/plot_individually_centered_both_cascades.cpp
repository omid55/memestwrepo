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
//	// test with toy example with small numbers
//	THash< TStr , CascadeElementV > qq1;
//	THash< TUInt , TSecTmV > tt1;
//	TStr emp("1");
//	CascadeElementV v;
//
//	TSecTm t1(uint(2));
//	TSecTm t2(uint(5));
//	TSecTm t3(uint(8));
//	TSecTm t4(uint(9));
//	v.Add(CascadeElement(t1));
//	v.Add(CascadeElement(t2));
//	v.Add(CascadeElement(t3));
//	v.Add(CascadeElement(t4));
//	qq1.AddDat(emp,v);
//
//	TStr emp2("2");
//	CascadeElementV v2;
//	TSecTm t5(uint(1));
//	TSecTm t6(uint(10));
//	v2.Add(CascadeElement(t5));
//	v2.Add(CascadeElement(t6));
//	qq1.AddDat(emp2,v2);
//
//
//	TSecTmV vv2;
//	vv2.Add(TSecTm(uint(7)));
//	vv2.Add(TSecTm(uint(8)));
//	tt1.AddDat(2,vv2);
//
//	TSecTmV vv;
//	vv.Add(TSecTm(uint(1)));
//	vv.Add(TSecTm(uint(3)));
//	vv.Add(TSecTm(uint(7)));
//	tt1.AddDat(1,vv);
//
//	uint per = 1;
//	char pst[] = "1 unit";
//
//	Tools::plotTwoIndividuallyShift(qq1,tt1,per,pst,"MY-TOY-TEST");
//	return 0;

//	// test with real toy example   // --->>> FULLY TESTED
//	THash< TStr , CascadeElementV > qq1;
//	THash< TUInt , TSecTmV > tt1;
//	TStr emp("");
//	CascadeElementV v;
//
//	TSecTm t1(2008,9,5,1,10,0);
//	TSecTm t2(2008,10,1,11,2,0);
//	TSecTm t3(2008,10,2,11,1,0);
//	TSecTm t4(2008,10,4,11,0,0);
//	v.Add(CascadeElement(t1));
//	v.Add(CascadeElement(t2));
//	v.Add(CascadeElement(t3));
//	v.Add(CascadeElement(t4));
//	qq1.AddDat(emp,v);
//
//	TSecTmV vv;
//
//	vv.Add(TSecTm(2008,10,3,10,0,0));
//	vv.Add(TSecTm(2008,10,20,10,0,0));
//	vv.Add(TSecTm(2008,11,28,10,0,0));
//	tt1.AddDat(1,vv);
//	uint per = 24 * 3600;
//	char pst[] = "days";
//	Tools::plotTwoHistShift(qq1,tt1,per,pst,"TEST-HIST-MEDIAN",MEDIAN,"Memes","Twitter");
//	Tools::plotTwoHistShift(qq1,tt1,per,pst,"TEST-HIST-MAX",MAX,"Memes","Twitter");
//	Tools::plotTwoIndividuallyShift(qq1,tt1,per,pst,"TEST-INDIV");
//	return 0;
////// ----------------------------------------


	TExeTm ExeTm;
	uint period = 3600;   // Hour
	char* periodstr = TStr("hour").GetCStr();
	printf("((( START individually Plot BOTH Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Individually Memes-Twitter Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// URLS
		THash< TStr , CascadeElementV > quotes1 = Tools::loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");
		THash< TUInt , TSecTmV > twitter1 = Tools::loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");

		// CONTENTS
		THash< TStr , CascadeElementV > quotes2 = Tools::loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");
		THash< TUInt , TSecTmV > twitter2 = Tools::loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar");

		// News vs Blogs
		THash< TStr , CascadeElementV > q1 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_NEWS.rar");
		THash< TStr , CascadeElementV > q2 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_NEWS.rar");

		THash< TStr , CascadeElementV > q3 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_BLOGS.rar");
		THash< TStr , CascadeElementV > q4 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_BLOGS.rar");

		THash< TStr , CascadeElementV > q5 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTS.rar");
		THash< TStr , CascadeElementV > q6 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTS.rar");

		THash< TStr , CascadeElementV > q7 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTSNEWS.rar");
		THash< TStr , CascadeElementV > q8 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTSNEWS.rar");

		THash< TStr , CascadeElementV > q9 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTSBLOGS.rar");
		THash< TStr , CascadeElementV > q10 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTSBLOGS.rar");


		// Plotting
		printf("\n\n\nPlotting ...\n");
		int status = system("mkdir -p MyResults/Individual/Urls/; mkdir -p MyResults/Individual/Contents/");

		Tools::plotTwoIndividuallyShift(quotes1,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_NormWithMentions");
		Tools::plotTwoIndividuallyShift(quotes2,twitter2,period,periodstr,"Individual/Contents/IndividualContents_NormWithMentions");
		Tools::plotTwoIndividuallyShift(q1,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_NEWS_NormWithMentions");
		Tools::plotTwoIndividuallyShift(q2,twitter2,period,periodstr,"Individual/Contents/IndividualContents_NEWS_NormWithMentions");
		Tools::plotTwoIndividuallyShift(q3,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_BLOGS_NormWithMentions");
		Tools::plotTwoIndividuallyShift(q4,twitter2,period,periodstr,"Individual/Contents/IndividualContents_BLOGS_NormWithMentions");
		Tools::plotTwoIndividuallyShift(q5,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_FIRSTS_NormWithMentions");
		Tools::plotTwoIndividuallyShift(q6,twitter2,period,periodstr,"Individual/Contents/IndividualContents_FIRSTS_NormWithMentions");
		Tools::plotTwoIndividuallyShift(q7,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_FIRSTSNEWS_NormWithMentions");
		Tools::plotTwoIndividuallyShift(q8,twitter2,period,periodstr,"Individual/Contents/IndividualContents_FIRSTSNEWS_NormWithMentions");
		Tools::plotTwoIndividuallyShift(q9,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_FIRSTSBLOGS_NormWithMentions");
		Tools::plotTwoIndividuallyShift(q10,twitter2,period,periodstr,"Individual/Contents/IndividualContents_FIRSTSBLOGS_NormWithMentions");


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
