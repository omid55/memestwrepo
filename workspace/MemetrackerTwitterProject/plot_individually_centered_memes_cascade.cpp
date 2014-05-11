// Omid55
/*
 * plot_individually_centered_memes_cascade.cpp
 *
 *  Created on: May 6, 2014
 *      Author: omid55
 */

#include "stdafx.h"

int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	int DesiredCascadesCount = 1000;
	printf("START individually Plot Memes Cascades CODE ...\n");
	try
	{
		THash< TStr , CascadeElementV > niftyqu;
		TZipIn zin1("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED.rar");
		niftyqu.Load(zin1);
		printf("Loaded QuotesPreprocessedData_NIFTY_FINALFILTERED has instances: %d\n\n\n",niftyqu.Len());

		THash< TStr , CascadeElementV > nifty_newsQuotes;
		TZipIn zin2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS.rar");
		nifty_newsQuotes.Load(zin2);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS loading done, it contains %d posts.\n",nifty_newsQuotes.Len());

		THash< TStr , CascadeElementV > nifty_blogsQuotes;
		TZipIn zin3("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS.rar");
		nifty_blogsQuotes.Load(zin3);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS loading done, it contains %d posts.\n",nifty_blogsQuotes.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu;
		TZipIn zin4("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS.rar");
		firstMentionsNiftyqu.Load(zin4);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS saving done, it contains %d posts.\n",firstMentionsNiftyqu.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu_newsQuotes;
		TZipIn zin5("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS.rar");
		firstMentionsNiftyqu_newsQuotes.Load(zin5);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS loading done, it contains %d posts.\n",firstMentionsNiftyqu_newsQuotes.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu_blogsQuotes;
		TZipIn zin6("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS.rar");
		firstMentionsNiftyqu_blogsQuotes.Load(zin6);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS saving done, it contains %d posts.\n",firstMentionsNiftyqu_blogsQuotes.Len());


		// Plotting All
		// All
		Tools::plotOne(niftyqu,"NIFTY-Memes-Volume-ALL");
		Tools::plotOne(niftyqu,"NIFTY-Memes-Volume-TopSelected-ALL",DesiredCascadesCount);

		// News and Blogs
		Tools::plotOne(nifty_newsQuotes,"NIFTY-Memes-Volume-News");
		Tools::plotOne(nifty_newsQuotes,"NIFTY-Memes-Volume-TopSelected-News",DesiredCascadesCount);
		Tools::plotOne(nifty_blogsQuotes,"NIFTY-Memes-Volume-Blogs");
		Tools::plotOne(nifty_blogsQuotes,"NIFTY-Memes-Volume-TopSelected-Blogs",DesiredCascadesCount);

		// Plotting first mentions
		Tools::plotOne(firstMentionsNiftyqu,"NIFTY-FirstMentions-Memes-Volume-ALL");
		Tools::plotOne(firstMentionsNiftyqu,"NIFTY-FirstMentions-Memes-Volume-TopSelected-ALL",DesiredCascadesCount);
		Tools::plotOne(firstMentionsNiftyqu_newsQuotes,"NIFTY-FirstMentions-Memes-Volume-News");
		Tools::plotOne(firstMentionsNiftyqu_newsQuotes,"NIFTY-FirstMentions-Memes-Volume-TopSelected-News",DesiredCascadesCount);
		Tools::plotOne(firstMentionsNiftyqu_blogsQuotes,"NIFTY-FirstMentions-Memes-Volume-Blogs");
		Tools::plotOne(firstMentionsNiftyqu_blogsQuotes,"NIFTY-FirstMentions-Memes-Volume-TopSelected-Blogs",DesiredCascadesCount);


		printf("Plots had been drawn successfully.");
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
