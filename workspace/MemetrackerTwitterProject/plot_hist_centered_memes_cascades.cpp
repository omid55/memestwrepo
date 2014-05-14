// Omid55
/*
 * plot_hist_centered_memes_cascades.cpp
 *
 *  Created on: May 13, 2014
 *      Author: omid55
 */
// Omid55
#include "stdafx.h"

int main(int argc, char* argv[])
{
	TExeTm ExeTm;

	printf("((( Starting The Plot Hist Memes Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		THash< TStr , CascadeElementV > nifty_newsQuotes;
		TZipIn zin2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS.rar");
		nifty_newsQuotes.Load(zin2);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS loading done, it contains %d posts.\n",nifty_newsQuotes.Len());

		THash< TStr , CascadeElementV > nifty_blogsQuotes;
		TZipIn zin3("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS.rar");
		nifty_blogsQuotes.Load(zin3);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS loading done, it contains %d posts.\n",nifty_blogsQuotes.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu_newsQuotes;
		TZipIn zin5("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS.rar");
		firstMentionsNiftyqu_newsQuotes.Load(zin5);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS loading done, it contains %d posts.\n",firstMentionsNiftyqu_newsQuotes.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu_blogsQuotes;
		TZipIn zin6("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS.rar");
		firstMentionsNiftyqu_blogsQuotes.Load(zin6);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS loading done, it contains %d posts.\n",firstMentionsNiftyqu_blogsQuotes.Len());


		// Plotting News vs Blogs
		uint period = 3600;
		char periodstr[] = "hours";
		Tools::plotTwoHistShift(nifty_newsQuotes,nifty_blogsQuotes,3600,"hours","NewsBlogs-MEDIAN-Volumes", MEDIAN, "News", "Blogs");
		Tools::plotTwoHistShift(firstMentionsNiftyqu_newsQuotes,firstMentionsNiftyqu_blogsQuotes,3600,"hours","FirstsNewsBlogs-MEDIAN-Volumes", MEDIAN, "News", "Blogs");
		Tools::plotTwoHistShift(nifty_newsQuotes,nifty_blogsQuotes,3600,"hours","NewsBlogs-MAX-Volumes", MAX, "News", "Blogs");
		Tools::plotTwoHistShift(firstMentionsNiftyqu_newsQuotes,firstMentionsNiftyqu_blogsQuotes,3600,"hours","FirstsNewsBlogs-MAX-Volumes", MAX, "News", "Blogs");


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



