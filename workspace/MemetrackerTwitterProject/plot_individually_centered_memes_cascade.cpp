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
	uint period = 4 * 3600;   // 4 Hours but, I think memetracker paper has 4 hours binning
	char* periodstr = TStr("4 hours").GetCStr();
	int DesiredCascadesCount = 1000;
	printf("((( START individually Plot Memes Cascades CODE )))\n");
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
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS loading done, it contains %d posts.\n",firstMentionsNiftyqu.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu_newsQuotes;
		TZipIn zin5("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS.rar");
		firstMentionsNiftyqu_newsQuotes.Load(zin5);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS loading done, it contains %d posts.\n",firstMentionsNiftyqu_newsQuotes.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu_blogsQuotes;
		TZipIn zin6("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS.rar");
		firstMentionsNiftyqu_blogsQuotes.Load(zin6);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS loading done, it contains %d posts.\n",firstMentionsNiftyqu_blogsQuotes.Len());


		// Plotting
//		// All
//		Tools::plotOneIndividuallyShift(niftyqu,"NIFTY-Individual",period,periodstr);
//		Tools::plotOneIndividuallyShift(niftyqu,"NIFTY-Individual-TOP1000",period,periodstr,DesiredCascadesCount);
//		niftyqu.Clr();
//		Tools::plotOneIndividuallyShift(firstMentionsNiftyqu,"Firsts-Individual-NIFTY",period,periodstr);
//		Tools::plotOneIndividuallyShift(firstMentionsNiftyqu,"Firsts-Individual-NIFTY-TOP1000",period,periodstr,DesiredCascadesCount);
//		firstMentionsNiftyqu.Clr();

//		// News and Blogs
//		Tools::plotOneIndividuallyShift(nifty_newsQuotes,"NIFTY-Memes-Volume-News",period,periodstr);
//		Tools::plotOneIndividuallyShift(nifty_newsQuotes,"NIFTY-Memes-Volume-TopSelected-News",period,periodstr,DesiredCascadesCount);
//		Tools::plotOneIndividuallyShift(nifty_blogsQuotes,"NIFTY-Memes-Volume-Blogs",period,periodstr);
//		Tools::plotOneIndividuallyShift(nifty_blogsQuotes,"NIFTY-Memes-Volume-TopSelected-Blogs",period,periodstr,DesiredCascadesCount);
//
//		// Plotting first mentions of news and blogs
//		Tools::plotOneIndividuallyShift(firstMentionsNiftyqu_newsQuotes,"NIFTY-FirstMentions-Memes-Volume-News",period,periodstr);
//		Tools::plotOneIndividuallyShift(firstMentionsNiftyqu_newsQuotes,"NIFTY-FirstMentions-Memes-Volume-TopSelected-News",period,periodstr,DesiredCascadesCount);
//		Tools::plotOneIndividuallyShift(firstMentionsNiftyqu_blogsQuotes,"NIFTY-FirstMentions-Memes-Volume-Blogs",period,periodstr);
//		Tools::plotOneIndividuallyShift(firstMentionsNiftyqu_blogsQuotes,"NIFTY-FirstMentions-Memes-Volume-TopSelected-Blogs",period,periodstr,DesiredCascadesCount);

		// News and Blogs togehter
		period = 3600;
		periodstr = TStr("hours").GetCStr();
		Tools::plotTwoIndividuallyShift(nifty_newsQuotes,nifty_blogsQuotes,period,periodstr,"IndividualNewsBlogs","News","Blogs");
		Tools::plotTwoIndividuallyShift(firstMentionsNiftyqu_newsQuotes,firstMentionsNiftyqu_blogsQuotes,period,periodstr,"IndividualFirstsNewsBlogs","FirstsNews","FirstsBlogs");


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
