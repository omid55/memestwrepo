// Omid55
/*
 * plot_individually_centered_both_cascades.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: omid55
 */

#include "stdafx.h"

inline THash<TStr,CascadeElementV> loadQuotes(char* name)
{
	THash<TStr,CascadeElementV> qs;
	TZipIn rarinput(name);
	qs.Load(rarinput);
	printf("Quotes: It has %d items.\n\n",qs.Len());
	return qs;
}

inline THash<TUInt,TSecTmV> loadTwitter(char* name)
{
	THash<TUInt,TSecTmV> tw;
	TZipIn rarinput(name);
	tw.Load(rarinput);
	printf("Twitter: It has %d items.\n\n",tw.Len());
	return tw;
}

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
		THash< TStr , CascadeElementV > quotes1 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");
		THash< TUInt , TSecTmV > twitter1 = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");

		// CONTENTS
		THash< TStr , CascadeElementV > quotes2 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");
		THash< TUInt , TSecTmV > twitter2 = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar");

		// News vs Blogs
		THash< TStr , CascadeElementV > q1 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_News.rar");
		THash< TUInt , TSecTmV > t1 	   = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_News.rar");
		THash< TStr , CascadeElementV > q2 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_News.rar");
		THash< TUInt , TSecTmV > t2 	   = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED_News.rar");

		THash< TStr , CascadeElementV > q3 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_Blogs.rar");
		THash< TUInt , TSecTmV > t3 	   = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_Blogs.rar");
		THash< TStr , CascadeElementV > q4 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_Blogs.rar");
		THash< TUInt , TSecTmV > t4 	   = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED_Blogs.rar");

		THash< TStr , CascadeElementV > q5 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_Firsts.rar");
		THash< TUInt , TSecTmV > t5 	   = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_Firsts.rar");
		THash< TStr , CascadeElementV > q6 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_Firsts.rar");
		THash< TUInt , TSecTmV > t6 	   = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED_Firsts.rar");

		THash< TStr , CascadeElementV > q7 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FirstNews.rar");
		THash< TUInt , TSecTmV > t7 	   = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_FirstNews.rar");
		THash< TStr , CascadeElementV > q8 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FirstNews.rar");
		THash< TUInt , TSecTmV > t8 	   = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED_FirstNews.rar");

		THash< TStr , CascadeElementV > q9 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FirstBlogs.rar");
		THash< TUInt , TSecTmV > t9 	   = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_FirstBlogs.rar");
		THash< TStr , CascadeElementV > q10 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FirstBlogs.rar");
		THash< TUInt , TSecTmV > t10 	   = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED_FirstBlogs.rar");


		// Plotting
		Tools::plotTwoIndividuallyShift(quotes1,twitter1,period,periodstr,"IndividualUrls");
		Tools::plotTwoIndividuallyShift(quotes2,twitter2,period,periodstr,"IndividualContents");
		Tools::plotTwoIndividuallyShift(q1,t1,period,periodstr,"IndividualUrls_NEWS");
		Tools::plotTwoIndividuallyShift(q2,t2,period,periodstr,"IndividualContents_NEWS");
		Tools::plotTwoIndividuallyShift(q3,t3,period,periodstr,"IndividualUrls_BLOGS");
		Tools::plotTwoIndividuallyShift(q4,t4,period,periodstr,"IndividualContents_BLOGS");
		Tools::plotTwoIndividuallyShift(q5,t5,period,periodstr,"IndividualUrls_FIRSTS");
		Tools::plotTwoIndividuallyShift(q6,t6,period,periodstr,"IndividualContents_FIRSTS");
		Tools::plotTwoIndividuallyShift(q7,t7,period,periodstr,"IndividualUrls_FIRSTNEWS");
		Tools::plotTwoIndividuallyShift(q8,t8,period,periodstr,"IndividualContents_FIRSTNEWS");
		Tools::plotTwoIndividuallyShift(q9,t9,period,periodstr,"IndividualUrls_FIRSTBLOGS");
		Tools::plotTwoIndividuallyShift(q10,t10,period,periodstr,"IndividualContents_FIRSTBLOGS");


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
