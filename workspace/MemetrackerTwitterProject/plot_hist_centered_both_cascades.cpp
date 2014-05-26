// Omid55
/*
 * plot_hist_centered_both_cascades.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: omid55
 */
// Omid55
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
	TExeTm ExeTm;
	uint period = 3600;   // Hour
	char* periodstr = TStr("hours").GetCStr();

	printf("((( Starting The Plot Hist BOTH Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// URLS
		THash< TStr , CascadeElementV > quotes1 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");
		THash< TUInt , TSecTmV > twitter1 = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");

		// CONTENTS
		THash< TStr , CascadeElementV > quotes2 = loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");
		THash< TUInt , TSecTmV > twitter2 = loadTwitter("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar");

		// News vs Blogs
		THash< TStr , CascadeElementV > q1 = loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_NEWS.rar");
		THash< TStr , CascadeElementV > q2 = loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_NEWS.rar");

		THash< TStr , CascadeElementV > q3 = loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_BLOGS.rar");
		THash< TStr , CascadeElementV > q4 = loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_BLOGS.rar");

		THash< TStr , CascadeElementV > q5 = loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTS.rar");
		THash< TStr , CascadeElementV > q6 = loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTS.rar");

		THash< TStr , CascadeElementV > q7 = loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTSNEWS.rar");
		THash< TStr , CascadeElementV > q8 = loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTSNEWS.rar");

		THash< TStr , CascadeElementV > q9 = loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTSBLOGS.rar");
		THash< TStr , CascadeElementV > q10 = loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTSBLOGS.rar");


		// Plotting
		printf("\n\n\nPlotting ...\n");
		int status = system("mkdir -p MyResults/Hist/Urls/; mkdir -p MyResults/Hist/Contents/");

		Tools::plotTwoHistShift(quotes1,twitter1,period,periodstr,"Hist/Urls/HistUrlsMedian",MEDIAN,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(quotes1,twitter1,period,periodstr,"Hist/Urls/HistUrlsMax", MAX,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(quotes2,twitter2,period,periodstr,"Hist/Contents/HistContentsMedian",MEDIAN,"Memes","contents on Twitter");
		Tools::plotTwoHistShift(quotes2,twitter2,period,periodstr,"Hist/Contents/HistContentsMax",MAX,"Memes","contents on Twitter");

		Tools::plotTwoHistShift(q1,twitter1,period,periodstr,"Hist/Urls/HistNEWSUrlsMedian",MEDIAN,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(q1,twitter1,period,periodstr,"Hist/Urls/HistNEWSUrlsMax", MAX,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(q2,twitter2,period,periodstr,"Hist/Contents/HistNEWSContentsMedian",MEDIAN,"Memes","contents on Twitter");
		Tools::plotTwoHistShift(q2,twitter2,period,periodstr,"Hist/Contents/HistNEWSContentsMax",MAX,"Memes","contents on Twitter");

		Tools::plotTwoHistShift(q3,twitter1,period,periodstr,"Hist/Urls/HistBLOGSUrlsMedian",MEDIAN,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(q3,twitter1,period,periodstr,"Hist/Urls/HistBLOGSUrlsMax", MAX,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(q4,twitter2,period,periodstr,"Hist/Contents/HistBLOGSContentsMedian",MEDIAN,"Memes","contents on Twitter");
		Tools::plotTwoHistShift(q4,twitter2,period,periodstr,"Hist/Contents/HistBLOGSContentsMax",MAX,"Memes","contents on Twitter");

		Tools::plotTwoHistShift(q5,twitter1,period,periodstr,"Hist/Urls/HistFIRSTSUrlsMedian",MEDIAN,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(q5,twitter1,period,periodstr,"Hist/Urls/HistFIRSTSUrlsMax", MAX,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(q6,twitter2,period,periodstr,"Hist/Contents/HistFIRSTSContentsMedian",MEDIAN,"Memes","contents on Twitter");
		Tools::plotTwoHistShift(q6,twitter2,period,periodstr,"Hist/Contents/HistFIRSTSContentsMax",MAX,"Memes","contents on Twitter");

		Tools::plotTwoHistShift(q7,twitter1,period,periodstr,"Hist/Urls/HistFIRSTSNEWSUrlsMedian",MEDIAN,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(q7,twitter1,period,periodstr,"Hist/Urls/HistFIRSTSNEWSUrlsMax", MAX,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(q8,twitter2,period,periodstr,"Hist/Contents/HistFIRSTSNEWSContentsMedian",MEDIAN,"Memes","contents on Twitter");
		Tools::plotTwoHistShift(q8,twitter2,period,periodstr,"Hist/Contents/HistFIRSTSNEWSContentsMax",MAX,"Memes","contents on Twitter");

		Tools::plotTwoHistShift(q9,twitter1,period,periodstr,"Hist/Urls/HistFIRSTSBLOGSUrlsMedian",MEDIAN,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(q9,twitter1,period,periodstr,"Hist/Urls/HistFIRSTSBLOGSUrlsMax", MAX,"Memes","urls on Twitter");
		Tools::plotTwoHistShift(q10,twitter2,period,periodstr,"Hist/Contents/HistFIRSTSBLOGSContentsMedian",MEDIAN,"Memes","contents on Twitter");
		Tools::plotTwoHistShift(q10,twitter2,period,periodstr,"Hist/Contents/HistFIRSTSBLOGSContentsMax",MAX,"Memes","contents on Twitter");


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
