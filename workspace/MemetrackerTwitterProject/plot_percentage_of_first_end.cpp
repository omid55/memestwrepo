/*
 * plot_percentage_of_first_end.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: omid55
 */

#include "stdafx.h"

void plotPercentageOfFirstEnd(THash<TStr,CascadeElementV> quotes, THash<TUInt,TSecTmV> twitter, char* legend, char* legendname1, bool isTotalData)
{
	printf("\n---==%s==---\n\n", legend);
	TFltPrV earlyAdoptors, lateAdoptors, earlyAdoptorsForDifferentSizes, lateAdoptorsForDifferentSizes;
	THash<TUInt,TFltV> firstVolumesForDifferentSizes, lastVolumesForDifferentSizes;
	int i, j, len, qc, tc;
	double avg, whole_casc_len, endQuotesPercentage, endTwitterPercentage, firstQuotesPercentage, firstTwitterPercentage, q_early_mean = 0, q_late_mean = 0;
	for(i=0;i<quotes.Len();i++)
	{
		whole_casc_len = quotes[i].Len() + twitter[i].Len();
		len = ceil(0.25 * whole_casc_len);

		// For early adoptors
		qc = 0, tc = 0;
		for(j=0;j<len;j++)
		{
			if(qc >= quotes[i].Len())
			{
				tc += (len-j);
				break;
			}
			if(tc >= twitter[i].Len())
			{
				qc += (len-j);
				break;
			}
			if(quotes[i][qc].time < twitter[i][tc])
			{
				qc++;
			}
			else
			{
				tc++;
			}
		}
		firstQuotesPercentage = (double)qc / (double)len;
		firstTwitterPercentage = (double)tc / (double)len;
		q_early_mean += firstQuotesPercentage;

		if(firstVolumesForDifferentSizes.GetKeyId(whole_casc_len) == -1)
		{
			TFltV temp;
			temp.Add(firstTwitterPercentage);
			firstVolumesForDifferentSizes.AddDat(whole_casc_len,temp);
		}
		else
		{
			firstVolumesForDifferentSizes.GetDat(whole_casc_len).Add(firstTwitterPercentage);
		}

		earlyAdoptors.Add(TFltPr(firstQuotesPercentage*len,firstTwitterPercentage*len));  //earlyAdoptors.Add(TFltPr(qc, tc));

		// For late adoptors
		qc = quotes[i].Len()-1; tc = twitter[i].Len()-1;
		for(j=0;j<len;j++)
		{
			if(qc < 0)
			{
				tc -= (len-j);
				break;
			}
			if(tc < 0)
			{
				qc -= (len-j);
				break;
			}
			if(quotes[i][qc].time < twitter[i][tc])
			{
				tc--;
			}
			else
			{
				qc--;
			}
		}
		endQuotesPercentage = (double)(quotes[i].Len()-1-qc) / (double)len;
		endTwitterPercentage = (double)(twitter[i].Len()-1-tc) / (double)len;
		q_late_mean += endQuotesPercentage;

		if(lastVolumesForDifferentSizes.GetKeyId(whole_casc_len) == -1)
		{
			TFltV temp;
			temp.Add(endQuotesPercentage);
			lastVolumesForDifferentSizes.AddDat(whole_casc_len,temp);
		}
		else
		{
			lastVolumesForDifferentSizes.GetDat(whole_casc_len).Add(endQuotesPercentage);
		}

		lateAdoptors.Add(TFltPr(endQuotesPercentage*len, endTwitterPercentage*len));
	}
	q_early_mean /= quotes.Len();
	q_late_mean /= quotes.Len();

	Tools::plotCCDFPairArray(earlyAdoptors,TStr::Fmt("Early-%s",legend).CStr(),"Blogs/News","Twitter");
	Tools::plotCCDFPairArray(lateAdoptors,TStr::Fmt("Late-%s",legend).CStr(),"Blogs/News","Twitter");

	Tools::plotScatter(earlyAdoptors, TStr::Fmt("EarlyAdoptors%s", legend).CStr(), "Blogs/News", TStr::Fmt("%s on Twitter",legend).CStr());
	Tools::plotScatter(lateAdoptors, TStr::Fmt("LateAdoptors%s", legend).CStr(), "Blogs/News", TStr::Fmt("%s on Twitter",legend).CStr());


	printf("\n%s=> QuotesEarlyMean: %f, QuotesLateMean: %f\n\n", legend, q_early_mean, q_late_mean);

	// Early & Late Adopters' Volumes For Different Sizes
	for(i=0;i<firstVolumesForDifferentSizes.Len();i++)
	{
		avg = 0;
		for(j=0;j<firstVolumesForDifferentSizes[i].Len();j++)
		{
			avg += firstVolumesForDifferentSizes[i][j];
		}
		avg /= firstVolumesForDifferentSizes[i].Len();
		earlyAdoptorsForDifferentSizes.Add(TFltPr(firstVolumesForDifferentSizes.GetKey(i).Val,avg));
	}
	for(i=0;i<lastVolumesForDifferentSizes.Len();i++)
	{
		avg = 0;
		for(j=0;j<lastVolumesForDifferentSizes[i].Len();j++)
		{
			avg += lastVolumesForDifferentSizes[i][j];
		}
		avg /= lastVolumesForDifferentSizes[i].Len();
		lateAdoptorsForDifferentSizes.Add(TFltPr(lastVolumesForDifferentSizes.GetKey(i).Val,avg));
	}

	if(isTotalData == true)
	{
		TGnuPlot plot1;
		plot1.SetXYLabel("Whole Cascade's Size", "Twitter 25% Early Adopters");
		plot1.AddPlot(earlyAdoptorsForDifferentSizes,gpwPoints);
		plot1.SetDataPlotFNm(TStr::Fmt("MyResults/Plot_DifferentSizes_EarlyAdoptors%s.tab",legend), TStr::Fmt("MyResults/Plot_DifferentSizes_EarlyAdoptors%s.plt",legend));
		plot1.SaveEps(TStr::Fmt("MyResults/Plot_DifferentSizes_EarlyAdoptors%s.eps",legend),true);

		TGnuPlot plot2;
		plot2.SetXYLabel("Whole Cascade's Size", "Twitter 25% Late Adopters");
		plot2.AddPlot(lateAdoptorsForDifferentSizes,gpwPoints);
		plot2.SetDataPlotFNm(TStr::Fmt("MyResults/Plot_DifferentSizes_LateAdoptors%s.tab",legend), TStr::Fmt("MyResults/Plot_DifferentSizes_LateAdoptors%s.plt",legend));
		plot2.SaveEps(TStr::Fmt("MyResults/Plot_DifferentSizes_LateAdoptors%s.eps",legend),true);
	}

	printf("Plots are drawn.\n\n");
}

int main(int argc, char* argv[])
{
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

//		// FOR COMPUTING TIME DIFFERENCE IN C++
//		const clock_t begin_time1 = clock();
//		cout << "T1: " << float( clock () - begin_time1 ) /  CLOCKS_PER_SEC << endl;

		plotPercentageOfFirstEnd(quotes,twitterUrls,"Urls", "Blogs/News",false);
		plotPercentageOfFirstEnd(quotes,twitterContents,"Contents", "Blogs/News",false);
		plotPercentageOfFirstEnd(quotes,twitterTotal,"Full", "Blogs/News",true);

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


