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
		TZipIn ZquotesIn1("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotesurl.Load(ZquotesIn1);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS has instances: %d\n\n\n",quotesurl.Len());

		TZipIn ZcascadesOnTwitterIn1("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");   //("CascadesFullUrlsOnTwitterData_FILTERED.rar");
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn1);
		printf("Loaded CascadesFullUrlsOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());

		TZipIn ZquotesIn2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotescont.Load(ZquotesIn2);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents has instances: %d\n\n\n",quotescont.Len());

		TZipIn ZcascadesOnTwitterIn2("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar"); 		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
		cascadesOnTwitterContents.Load(ZcascadesOnTwitterIn2);
		printf("Loaded CascadesOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterContents.Len());

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

		THash< TStr , CascadeElementV > q11 = Tools::loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS.rar");
		THash< TStr , CascadeElementV > q12 = Tools::loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS.rar");
		THash< TStr , CascadeElementV > q13 = Tools::loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS.rar");
		THash< TStr , CascadeElementV > q14 = Tools::loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS.rar");


		Tools::printTwitterHasSoonerStart(quotesurl,cascadesOnTwitterUrls);
		return 0;

		// Plotting
		printf("\n\nPlotting...\n");
		Tools::plotCCDFStartMedianEnd(quotesurl,cascadesOnTwitterUrls,"Urls", "Memes");
		Tools::plotCCDFStartMedianEnd(quotescont,cascadesOnTwitterContents,"Contents", "Memes");
		Tools::plotCCDFStartMedianEnd(q11,q12,"NewsBlogs","News","Blogs");
		Tools::plotCCDFStartMedianEnd(q13,q14,"FirstsNewsBlogs","FirstsNews","FirstsBlogs");
		Tools::plotCCDFStartMedianEnd(q1,cascadesOnTwitterUrls,"News-Urls", "NewsMemes");
		Tools::plotCCDFStartMedianEnd(q2,cascadesOnTwitterContents,"News-Contents", "NewsMemes");
		Tools::plotCCDFStartMedianEnd(q3,cascadesOnTwitterUrls,"Blogs-Urls", "BlogsMemes");
		Tools::plotCCDFStartMedianEnd(q4,cascadesOnTwitterContents,"Blogs-Contents", "BlogsMemes");
		Tools::plotCCDFStartMedianEnd(q5,cascadesOnTwitterUrls,"Firsts-Urls", "FirstsMemes");
		Tools::plotCCDFStartMedianEnd(q6,cascadesOnTwitterContents,"Firsts-Contents", "FirstsMemes");
		Tools::plotCCDFStartMedianEnd(q7,cascadesOnTwitterUrls,"FirstsNews-Urls", "FirstsNewsMemes");
		Tools::plotCCDFStartMedianEnd(q8,cascadesOnTwitterContents,"FirstsNews-Contents", "FirstsNewsMemes");
		Tools::plotCCDFStartMedianEnd(q9,cascadesOnTwitterUrls,"FirstsBlogs-Urls", "FirstsBlogsMemes");
		Tools::plotCCDFStartMedianEnd(q10,cascadesOnTwitterContents,"FirstsBlogs-Contents", "FirstsBlogsMemes");
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
