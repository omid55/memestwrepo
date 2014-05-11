// Omid55

/*
 * plot_cascade_no_centeralized.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: omid55
 */

// Omid55
#include "stdafx.h"

THash< TStr , CascadeElementV > quotes;
THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
//THash< TUInt , TSecTmV > cascadesOnTwitterContents;


int main(int argc, char* argv[])
{
//	TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4URLS.rar");	//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");    //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
//	quotes.Load(ZquotesIn);
//	printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4URLS has instances: %d\n\n\n",quotes.Len());
//
	TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4Contents.rar");	//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");    //("CascadesFullUrlsOnTwitterData_FILTERED.rar");
	quotes.Load(ZquotesIn);
	printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4Contents has instances: %d\n\n\n",quotes.Len());

	for(int q=0;q<quotes.Len();q++)
	{
		cout << q << ": " << quotes.GetKey(q).CStr() << endl;
	}
	return 0;



	TExeTm ExeTm;

	printf("((( Starting The Plot Memes-Twitter Urls Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// ---== Loading Data ==---
		TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4URLS.rar");	//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");    //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4URLS has instances: %d\n\n\n",quotes.Len());

		TZipIn ZcascadesOnTwitterIn("CascadesFullUrlsOnTwitterData_FILTERED.rar");	//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");    //("CascadesFullUrlsOnTwitterData_FILTERED.rar");
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn);
		printf("Loaded CascadesFullUrlsOnTwitterData_FILTERED has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());


//		// ---== Loading Data ==---
//		TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4Contents.rar");	//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");    //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
//		quotes.Load(ZquotesIn);
//		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4URLS has instances: %d\n\n\n",quotes.Len());
//
//		TZipIn ZIn("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
//		cascadesOnTwitterContents.Load(ZIn);
//		printf("Loaded CascadesOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterContents.Len());


		TSecTmV ti;
		int bins,i,c,index,quoteIndex;
		double* vols_memes;
		double* vols_twitter_urls;
		double* vol_me;
		double* vol_tu;
		TFltPrV volumes_memes;
		TFltPrV volumes_twitter_urls;
		uint period = 30 * 24 * 3600;   // Month
		uint begin = TSecTm(2008,7,31,0,0,0).GetAbsSecs();
		uint end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
		TGnuPlot plot;
		plot.SetXYLabel("Time(Hour Bin)", "Volume");
		plot.SetTitle("Hourly Binned Quotes Cascade over Memetracker and its Urls over Twitter");

		// ---== Computation ==---
		bins = (end - begin) / period;
		printf("bins: %d\n\n",bins);
		vols_memes = new double[bins];
		vols_twitter_urls = new double[bins];
		for(i=0;i<bins;i++)
		{
			vols_memes[i] = 0;
			vols_twitter_urls[i] = 0;
		}

		for(c=0;c<cascadesOnTwitterUrls.Len();c++)
		{
			quoteIndex = cascadesOnTwitterUrls.GetKey(c);
			ti.Clr();
			for(i=0;i<quotes[c].Len();i++)   ///for(i=0;i<quotes[quoteIndex].Len();i++)
			{
				ti.Add(quotes[c][i].time);   ///ti.Add(quotes[quoteIndex][i].time);
			}
			vol_me = Tools::calculateHistOfCascade(ti,begin,period,bins,true);
			vol_tu = Tools::calculateHistOfCascade(cascadesOnTwitterUrls.GetDat(quoteIndex),begin,period,bins,true);

			for(i=0;i<bins;i++)
			{
				vols_memes[i] += vol_me[i];
				vols_twitter_urls[i] += vol_tu[i];
			}

			delete[] vol_me;
			delete[] vol_tu;
		}

		for(i=0;i<bins;i++)
		{
			vols_memes[i] /= cascadesOnTwitterUrls.Len();
			volumes_memes.Add(TFltPr(i,vols_memes[i]));

			vols_twitter_urls[i] /= cascadesOnTwitterUrls.Len();
			volumes_twitter_urls.Add(TFltPr(i,vols_twitter_urls[i]));
		}
		plot.AddPlot(volumes_memes,gpwPoints,"Memes");
		plot.AddPlot(volumes_twitter_urls,gpwPoints,"Twitter Urls");
		plot.SetDataPlotFNm("MyResults/Memes-Twitter-Urls-REAL-Volumes.tab", "MyResults/Memes-Twitter-Urls-REAL-Volumes.plt");
		plot.SaveEps("MyResults/Memes-Twitter-Urls-REAL-Volumes.eps",true);
		delete[] vols_memes;
		delete[] vols_twitter_urls;

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
