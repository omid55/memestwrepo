// Omid55
/*
 * plot_hist_centered_memes_cascades.cpp
 *
 *  Created on: May 13, 2014
 *      Author: omid55
 */

#include "stdafx.h"

int main(int argc, char* argv[])
{
	TExeTm ExeTm;

	printf("((( Starting The Plot Hist Memes Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

//		THash< TStr , CascadeElementV > quotes;
//		TZipIn z1("lastData/QuotesData.rar");
//		quotes.Load(z1);
//		printf("Loaded QuotesData has instances: %d\n\n\n",quotes.Len());
//
//		THash< TStr , CascadeElementV > nifty;
//		TZipIn z2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED.rar");
//		nifty.Load(z2);
//		printf("Loaded QuotesPreprocessedData_NIFTY_FINALFILTERED has instances: %d\n\n\n",nifty.Len());
//
//		THash< TStr , CascadeElementV > niftyfirsts;
//		TZipIn z3("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS.rar");
//		niftyfirsts.Load(z3);
//		printf("Loaded QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS has instances: %d\n\n\n",niftyfirsts.Len());

		THash< TStr , CascadeElementV > nifty_newsQuotes;
		TZipIn zin2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS.rar");
		nifty_newsQuotes.Load(zin2);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS loading done, it contains %d items.\n",nifty_newsQuotes.Len());

		THash< TStr , CascadeElementV > nifty_blogsQuotes;
		TZipIn zin3("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS.rar");
		nifty_blogsQuotes.Load(zin3);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS loading done, it contains %d items.\n",nifty_blogsQuotes.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu_newsQuotes;
		TZipIn zin5("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS.rar");
		firstMentionsNiftyqu_newsQuotes.Load(zin5);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS loading done, it contains %d items.\n",firstMentionsNiftyqu_newsQuotes.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu_blogsQuotes;
		TZipIn zin6("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS.rar");
		firstMentionsNiftyqu_blogsQuotes.Load(zin6);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS loading done, it contains %d items.\n",firstMentionsNiftyqu_blogsQuotes.Len());


		// Plotting
		uint period = 4 * 3600;     // 4 hours
		char* periodstr = TStr("4 hours").GetCStr();   //char periodstr[] = "4 hours";
		int DesiredCascadesCount = 1000;

//		// Memes
//		Tools::plotOneHistShift(quotes,"Memes-FULL-MEDIAN",period,periodstr,MEDIAN);
//		Tools::plotOneHistShift(quotes,"Memes-TOP1000-MEDIAN",period,periodstr,MEDIAN,DesiredCascadesCount);
//		Tools::plotOneHistShift(quotes,"Memes-FULL-MAX",period,periodstr,MAX);
//		Tools::plotOneHistShift(quotes,"Memes-TOP1000-MAX",period,periodstr,MAX,DesiredCascadesCount);
//		quotes.Clr();
//		Tools::plotOneHistShift(nifty,"Nifty-FULL-MEDIAN",period,periodstr,MEDIAN);
//		Tools::plotOneHistShift(nifty,"Nifty-TOP1000-MEDIAN",period,periodstr,MEDIAN,DesiredCascadesCount);
//		Tools::plotOneHistShift(nifty,"Nifty-FULL-MAX",period,periodstr,MAX);
//		Tools::plotOneHistShift(nifty,"Nifty-TOP1000-MAX",period,periodstr,MAX,DesiredCascadesCount);
//		nifty.Clr();
//		Tools::plotOneHistShift(niftyfirsts,"Firsts-Nifty-FULL-MEDIAN",period,periodstr,MEDIAN);
//		Tools::plotOneHistShift(niftyfirsts,"Firsts-Nifty-TOP1000-MEDIAN",period,periodstr,MEDIAN,DesiredCascadesCount);
//		Tools::plotOneHistShift(niftyfirsts,"Firsts-Nifty-FULL-MAX",period,periodstr,MAX);
//		Tools::plotOneHistShift(niftyfirsts,"Firsts-Nifty-TOP1000-MAX",period,periodstr,MAX,DesiredCascadesCount);
//		niftyfirsts.Clr();

		// News vs Blogs
		period = 3600;
		periodstr = TStr("hours").GetCStr();
		Tools::plotTwoHistShift(nifty_newsQuotes,nifty_blogsQuotes,period,periodstr,"Histed-NewsBlogs-MEDIAN", MEDIAN, "News", "Blogs");
		Tools::plotTwoHistShift(firstMentionsNiftyqu_newsQuotes,firstMentionsNiftyqu_blogsQuotes,period,periodstr,"Histed-FirstsNewsBlogs-MEDIAN", MEDIAN, "News", "Blogs");
		Tools::plotTwoHistShift(nifty_newsQuotes,nifty_blogsQuotes,period,periodstr,"Histed-NewsBlogs-MAX", MAX, "News", "Blogs");
		Tools::plotTwoHistShift(firstMentionsNiftyqu_newsQuotes,firstMentionsNiftyqu_blogsQuotes,period,periodstr,"Histed-FirstsNewsBlogs-MAX", MAX, "News", "Blogs");


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



