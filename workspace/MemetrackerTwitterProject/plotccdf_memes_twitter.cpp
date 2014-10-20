// Omid55

/*
 * plotccdf_memes_twitter.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: omid55
 */

#include "stdafx.h"

TFltPrV mygetCCDFYAxis(double* arr1, int leng1, int LEN)
{
	int i;
	double x,y;
	TFltPrV points1;
	sort(arr1,arr1+leng1);
	double remove = ((LEN-1) * leng1) / (2 * LEN);
	cout << "remove: " << remove << ", leng1: " << leng1 << endl;
	for(i=remove;i<leng1-remove;i++)
	{
		x = arr1[i];
		y = 1.0 - (1.0/leng1)*i;
		points1.Add(TFltPr(x,y));
	}
	return points1;
}

void myplotSimpleCCDF(double* arr1, int leng1, double* arr2, int leng2, char* legend1, char* legend2, char* xlabel, int LEN)
{
	TGnuPlot plot;
	TFltPrV points1 = mygetCCDFYAxis(arr1, leng1, LEN);
	TFltPrV points2 = mygetCCDFYAxis(arr2, leng2, LEN);

	TStr name = TStr::Fmt("CCDF_%s_%s",legend1,legend2);
	printf("%s Drawing:\n",name.CStr());
	plot.SetXYLabel(xlabel, "P(X>d)");
	plot.AddPlot(points1,gpwLines,legend1);
	plot.AddPlot(points2,gpwLines,TStr::Fmt("%s on Twitter",legend2));
	plot.AddCmd("set terminal postscript enhanced eps 30 color");
	plot.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name.CStr()), TStr::Fmt("MyResults/%s.plt",name.CStr()));
	plot.SaveEps(TStr::Fmt("MyResults/%s.eps",name.CStr()));
	printf("%s had been drawn successfully.\n\n",name.CStr());
}

int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	printf("((( Starting The Plot CCDF Meme-Twitter Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nCCDF Plotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

//		// ---== Loading Data ==---
//		THash< TStr , CascadeElementV  > quotesurl,quotescont;
//		THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
//		THash< TUInt , TSecTmV > cascadesOnTwitterContents;
//		TZipIn ZquotesIn1("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
//		quotesurl.Load(ZquotesIn1);
//		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS has instances: %d\n\n\n",quotesurl.Len());
//
//		TZipIn ZcascadesOnTwitterIn1("/NS/twitter-5/work/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");   //("CascadesFullUrlsOnTwitterData_FILTERED.rar");
//		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn1);
//		printf("Loaded CascadesFullUrlsOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());
//
//		TZipIn ZquotesIn2("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
//		quotescont.Load(ZquotesIn2);
//		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents has instances: %d\n\n\n",quotescont.Len());
//
//		TZipIn ZcascadesOnTwitterIn2("/NS/twitter-5/work/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar"); 		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
//		cascadesOnTwitterContents.Load(ZcascadesOnTwitterIn2);
//		printf("Loaded CascadesOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterContents.Len());
//
//		// News vs Blogs
//		THash< TStr , CascadeElementV > q1 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_NEWS.rar");
//		THash< TStr , CascadeElementV > q2 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_NEWS.rar");
//
//		THash< TStr , CascadeElementV > q3 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_BLOGS.rar");
//		THash< TStr , CascadeElementV > q4 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_BLOGS.rar");
//
//		THash< TStr , CascadeElementV > q5 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTS.rar");
//		THash< TStr , CascadeElementV > q6 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTS.rar");
//
//		THash< TStr , CascadeElementV > q7 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTSNEWS.rar");
//		THash< TStr , CascadeElementV > q8 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTSNEWS.rar");
//
//		THash< TStr , CascadeElementV > q9 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTSBLOGS.rar");
//		THash< TStr , CascadeElementV > q10 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTSBLOGS.rar");
//
//		THash< TStr , CascadeElementV > q11 = Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS.rar");
//		THash< TStr , CascadeElementV > q12 = Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS.rar");
//		THash< TStr , CascadeElementV > q13 = Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS.rar");
//		THash< TStr , CascadeElementV > q14 = Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS.rar");
//
//
//
//		printf("\n\nPRINTING those quotes which Twitter Has sooner start in:\n");
//		int limit = 100;
//		if(argc>1)
//		{
//			limit = atoi(argv[1]);
//		}
//		Tools::printTwitterHasSoonerStart(quotescont,cascadesOnTwitterContents,limit);
//		return 0;
//
//
//
//		// Plotting
//		printf("\n\nPlotting...\n");
//		Tools::plotCCDFStartMedianEnd(quotesurl,cascadesOnTwitterUrls,"Urls", "Memes");
//		Tools::plotCCDFStartMedianEnd(quotescont,cascadesOnTwitterContents,"Contents", "Memes");
//		Tools::plotCCDFStartMedianEnd(q11,q12,"NewsBlogs","News","Blogs");
//		Tools::plotCCDFStartMedianEnd(q13,q14,"FirstsNewsBlogs","FirstsNews","FirstsBlogs");
//		Tools::plotCCDFStartMedianEnd(q1,cascadesOnTwitterUrls,"News-Urls", "NewsMemes");
//		Tools::plotCCDFStartMedianEnd(q2,cascadesOnTwitterContents,"News-Contents", "NewsMemes");
//		Tools::plotCCDFStartMedianEnd(q3,cascadesOnTwitterUrls,"Blogs-Urls", "BlogsMemes");
//		Tools::plotCCDFStartMedianEnd(q4,cascadesOnTwitterContents,"Blogs-Contents", "BlogsMemes");
//		Tools::plotCCDFStartMedianEnd(q5,cascadesOnTwitterUrls,"Firsts-Urls", "FirstsMemes");
//		Tools::plotCCDFStartMedianEnd(q6,cascadesOnTwitterContents,"Firsts-Contents", "FirstsMemes");
//		Tools::plotCCDFStartMedianEnd(q7,cascadesOnTwitterUrls,"FirstsNews-Urls", "FirstsNewsMemes");
//		Tools::plotCCDFStartMedianEnd(q8,cascadesOnTwitterContents,"FirstsNews-Contents", "FirstsNewsMemes");
//		Tools::plotCCDFStartMedianEnd(q9,cascadesOnTwitterUrls,"FirstsBlogs-Urls", "FirstsBlogsMemes");
//		Tools::plotCCDFStartMedianEnd(q10,cascadesOnTwitterContents,"FirstsBlogs-Contents", "FirstsBlogsMemes");



//		// For BOTH TOGETHER
//		THash< TStr , CascadeElementV > quotesBOTH = Tools::loadQuotes("DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar");
//		THash< TStr , CascadeElementV > quotesBOTHFirst = Tools::loadQuotes("DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH_FIRSTS.rar");
//		THash< TUInt , TSecTmV > cascadesOnTwitterUrlsBOTH;
//		THash< TUInt , TSecTmV > cascadesOnTwitterContentsBOTH;
//
//		TZipIn z1("DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");   //("CascadesFullUrlsOnTwitterData_FILTERED.rar");
//		cascadesOnTwitterUrlsBOTH.Load(z1);
//		printf("Loaded CascadesFullUrlsOnTwitterData_FINALFILTERED_HAVINGBOTH has instances: %d\n\n\n",cascadesOnTwitterUrlsBOTH.Len());
//
//		TZipIn z2("DATA/CascadesOnTwitterData_FINALFILTERED_HAVINGBOTH.rar"); 				//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
//		cascadesOnTwitterContentsBOTH.Load(z2);
//		printf("Loaded CascadesOnTwitterData_FINALFILTERED_HAVINGBOTH has instances: %d\n\n\n",cascadesOnTwitterContentsBOTH.Len());
//
//		Tools::plotCCDFStartMedianEnd(quotesBOTH, cascadesOnTwitterUrlsBOTH, "MemesUrlsBOTH", "Memes");
//		Tools::plotCCDFStartMedianEnd(quotesBOTH, cascadesOnTwitterContentsBOTH, "MemesContentsBOTH", "Memes");
//		Tools::plotCCDFStartMedianEnd(quotesBOTHFirst, cascadesOnTwitterUrlsBOTH, "MemesUrlsBOTH_Firsts", "Memes");
//		Tools::plotCCDFStartMedianEnd(quotesBOTHFirst, cascadesOnTwitterContentsBOTH, "MemesContentsBOTH_Firsts", "Memes");
//		// For BOTH TOGETHER


		// --------------------------------------------------------------------------------------------------------------------------
		// --------------------------------------------------------------------------------------------------------------------------
		// CCDF of cascade sizes for blogs/news media, twitter	mentions and twitter links for the 65,140 quote dataset
		printf("\n\n\nCCDF of cascade sizes for blogs/news media, twitter	mentions and twitter links ...\n");
		THash< TStr , CascadeElementV  > quotesurl, quotescont;
		THash< TUInt , TSecTmV > cascadesOnTwitterUrls, cascadesOnTwitterContents;
		TZipIn ZquotesIn1("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotesurl.Load(ZquotesIn1);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS has instances: %d\n\n\n",quotesurl.Len());

		TZipIn ZcascadesOnTwitterIn1("/NS/twitter-5/work/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");   //("CascadesFullUrlsOnTwitterData_FILTERED.rar");
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn1);
		printf("Loaded CascadesFullUrlsOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());

		TZipIn ZquotesIn2("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotescont.Load(ZquotesIn2);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents has instances: %d\n\n\n",quotescont.Len());

		TZipIn ZcascadesOnTwitterIn2("/NS/twitter-5/work/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar"); 		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
		cascadesOnTwitterContents.Load(ZcascadesOnTwitterIn2);
		printf("Loaded CascadesOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterContents.Len());

		double* c1 = new double[quotesurl.Len()];
		double* c2 = new double[cascadesOnTwitterUrls.Len()];
		for(int i=0;i<quotesurl.Len();i++)
		{
			c1[i] = quotesurl[i].Len();
			c2[i] = cascadesOnTwitterUrls[i].Len();
		}

		double* c3 = new double[quotescont.Len()];
		double* c4 = new double[cascadesOnTwitterContents.Len()];
		for(int i=0;i<quotescont.Len();i++)
		{
			c3[i] = quotescont[i].Len();
			c4[i] = cascadesOnTwitterContents[i].Len();
		}

		// CHANGE THE SCALE ...   << CHECK HERE >>

		int LEN = atoi(argv[1]);
		myplotSimpleCCDF(c1,quotesurl.Len(),c2,cascadesOnTwitterUrls.Len(),"Blogs-News","Urls","Cascade Length", LEN);
		myplotSimpleCCDF(c3,quotescont.Len(),c4,cascadesOnTwitterContents.Len(),"Blogs-News","Contents","Cascade Length", LEN);
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
