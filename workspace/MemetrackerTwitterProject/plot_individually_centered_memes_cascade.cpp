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
	printf("START The Plot Memes Cascades CODE ...\n");
	try
	{
		THash< TStr , CascadeElementV > niftyqu;
		TZipIn zin1("QuotesPreprocessedData_NIFTY_FINALFILTERED.rar");
	//		TZipIn ZquotesIn2("QuotesPreprocessedData_NIFTY_SUBSETTED.rar");       // for local in my computer
		niftyqu.Load(zin1);
		printf("Loaded QuotesPreprocessedData_NIFTY_FINALFILTERED has instances: %d\n\n\n",niftyqu.Len());

		THash< TStr , CascadeElementV > nifty_newsQuotes;
		THash< TStr , CascadeElementV > nifty_blogsQuotes;
		TZipIn zin2("QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS.rar");
		nifty_newsQuotes.Load(zin2);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS loading done, it contains %d posts.\n",nifty_newsQuotes.Len());
		TZipIn zin3("QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS.rar");
		nifty_blogsQuotes.Load(zin3);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS loading done, it contains %d posts.\n",nifty_blogsQuotes.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu;
		TZipIn zin4("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS.rar");
		firstMentionsNiftyqu.Load(zin4);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS saving done, it contains %d posts.\n",firstMentionsNiftyqu.Len());


		// Plotting All
		// All
//		Tools::plotOne(fqu,"FULL-Memes-Volume-ALL");
//		Tools::plotOne(fqu,"FULL-Memes-Volume-TopSelected-ALL",DesiredCascadesCount);
		Tools::plotOne(niftyqu,"NIFTY-Memes-Volume-ALL");
		Tools::plotOne(niftyqu,"NIFTY-Memes-Volume-TopSelected-ALL",DesiredCascadesCount);

		// News and Blogs
//		Tools::plotOne(full_newsQuotes,"FULL-Memes-Volume-News");
//		Tools::plotOne(full_newsQuotes,"FULL-Memes-Volume-TopSelected-News",DesiredCascadesCount);
//		Tools::plotOne(full_blogsQuotes,"FULL-Memes-Volume-Blogs");
//		Tools::plotOne(full_blogsQuotes,"FULL-Memes-Volume-TopSelected-Blogs",DesiredCascadesCount);
		Tools::plotOne(nifty_newsQuotes,"NIFTY-Memes-Volume-News");
		Tools::plotOne(nifty_newsQuotes,"NIFTY-Memes-Volume-TopSelected-News",DesiredCascadesCount);
		Tools::plotOne(nifty_blogsQuotes,"NIFTY-Memes-Volume-Blogs");
		Tools::plotOne(nifty_blogsQuotes,"NIFTY-Memes-Volume-TopSelected-Blogs",DesiredCascadesCount);

		// Plotting first mentions
		// All
//		Tools::plotOne(firstMentionsFqu,"FirstMentions-FULL-Memes-Volume-ALL");
		Tools::plotOne(firstMentionsNiftyqu,"FirstMentions-FULL-Memes-Volume-TopSelected-ALL",DesiredCascadesCount);
//		Tools::plotOne(firstMentionsFqu,"FirstMentions-NIFTY-Memes-Volume-ALL");
		Tools::plotOne(firstMentionsNiftyqu,"FirstMentions-NIFTY-Memes-Volume-TopSelected-ALL",DesiredCascadesCount);

//		// News and Blogs
//		Tools::plotOne(full_newsQuotes,"FirstMentions-FULL-Memes-Volume-News");
//		Tools::plotOne(full_newsQuotes,"FirstMentions-FULL-Memes-Volume-TopSelected-News",DesiredCascadesCount);
//		Tools::plotOne(full_blogsQuotes,"FirstMentions-FULL-Memes-Volume-Blogs");
//		Tools::plotOne(full_blogsQuotes,"FirstMentions-FULL-Memes-Volume-TopSelected-Blogs",DesiredCascadesCount);
//		Tools::plotOne(nifty_newsQuotes,"FirstMentions-NIFTY-Memes-Volume-News");
//		Tools::plotOne(nifty_newsQuotes,"FirstMentions-NIFTY-Memes-Volume-TopSelected-News",DesiredCascadesCount);
//		Tools::plotOne(nifty_blogsQuotes,"FirstMentions-NIFTY-Memes-Volume-Blogs");
//		Tools::plotOne(nifty_blogsQuotes,"FirstMentions-NIFTY-Memes-Volume-TopSelected-Blogs",DesiredCascadesCount);


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
