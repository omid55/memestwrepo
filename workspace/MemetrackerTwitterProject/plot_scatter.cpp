/*
 * plot_scatter.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: omid55
 */

#include "stdafx.h"

void plotScatterLengthOfEachCascade(THash<TStr,CascadeElementV>& quotes, THash<TUInt,TSecTmV>& twitter, char* name)
{
	printf("\n\nPlotting ...\n");
	TFltPrV plotdata;
	for(int q=0;q<quotes.Len();q++)
	{
		TFltPr elem;
		elem.Val1 = quotes[q].Len();
		elem.Val2 = twitter[q].Len();
		plotdata.Add(elem);
	}
	Tools::plotScatter(plotdata, name, "Blogs/News", TStr::Fmt("%s on Twitter",name).CStr());
}

int main(int argc, char* argv[])
{
//	TFltPrV v;
//	v.Add(TFltPr(1,4));
//	v.Add(TFltPr(5,5));
//	v.Add(TFltPr(9,11));
//	v.Add(TFltPr(20,8));
//	v.Add(TFltPr(21,30));
//	cout << "C: " << Tools::computeCorrelation(v,Pearson) << endl;
//	return 0;


	TExeTm ExeTm;
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

		// Plotting
		THash< TUInt , TSecTmV > twitterTotal;
		for(int i=0;i<twitterContents.Len();i++)
		{
			TSecTmV tmp;
			tmp.AddV(twitterContents[i]);
			tmp.AddV(twitterUrls[i]);
			twitterTotal.AddDat(i,tmp);
		}

		plotScatterLengthOfEachCascade(quotes,twitterUrls,"Urls");
		plotScatterLengthOfEachCascade(quotes,twitterContents,"Contents");
		plotScatterLengthOfEachCascade(quotes,twitterTotal,"Full");

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

