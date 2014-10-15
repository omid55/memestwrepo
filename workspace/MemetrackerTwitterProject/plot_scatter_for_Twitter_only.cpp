// Omid55
/*
 * plot_scatter_for_Twitter_only.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: omid55
 */

#include "stdafx.h"

void plotScatterLengthOfEachCascade(THash<TUInt,TSecTmV>& c1, THash<TUInt,TSecTmV>& c2)
{
	printf("\n\nPlotting ...\n");
	TFltPrV plotdata;
	for(int q=0;q<c1.Len();q++)
	{
		TFltPr elem;
		elem.Val1 = c1[q].Len();
		elem.Val2 = c2[q].Len();
		plotdata.Add(elem);
	}
	Tools::plotScatter(plotdata, "TwitterUrlsOverContents", "Urls on Twitter", "Contents on Twitter");
}

int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Scatter For Twitter Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

//		THash< TUInt , TSecTmV > twitterUrls = Tools::loadTwitter("DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");
//		THash< TUInt , TSecTmV > twitterContents = Tools::loadTwitter("DATA/CascadesOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");
		THash< TUInt , TSecTmV > twitterUrls = Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");     // CascadesFullUrlsOnTwitterData_FINALFILTERED
		THash< TUInt , TSecTmV > twitterContents = Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");    // CascadesOnTwitterData_FINALFILTERED

		THash< TUInt , TSecTmV > full_twitterUrls = Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");
		THash< TUInt , TSecTmV > full_twitterContents = Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar");


		// Scatter plot
		plotScatterLengthOfEachCascade(twitterUrls,twitterContents);

		// Percentage computation
		double cnt = 0;
		for(int i=0;i<full_twitterUrls.Len();i++)
		{
			if(full_twitterContents.GetKeyId(full_twitterUrls.GetKey(i)) != -1)
			{
				cnt++;
			}
		}
		cnt /= full_twitterUrls.Len();    // twitterUrls.Len() / full_twitterUrls.Len()
		printf("The percentage of Urls of quotes which have contents as well: %f\n", 100 * cnt);

		cnt = 0;
		for(int i=0;i<full_twitterContents.Len();i++)
		{
			if(full_twitterUrls.GetKeyId(full_twitterContents.GetKey(i)) != -1)
			{
				cnt++;
			}
		}
		cnt /= full_twitterContents.Len();
		printf("The percentage of Contents of quotes which have urls as well: %f\n", 100 * cnt);

		printf("\nScatter Plot had been drawn successfully.");
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




