// Omid55

/*
 * filter_peaks_by_nifty_apply_both.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: omid55
 */

// Omid55

#include "stdafx.h"

void applyFilter(THash< TStr , CascadeElementV >& quotes,THash< TUInt , TSecTmV >& twitter,char* quotesName,char* twName,bool isurls)
{
	// NIFTY Method for Filtering by Peaks
	THash< TStr , CascadeElementV > quotesFiltered;
	THash< TUInt , TSecTmV > twitterFiltered;
	uint begin = TSecTm(2008,7,31,0,0,0).GetAbsSecs();
	uint end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
	uint period = 9 * 3600;   // 9 days because of NIFTY paper

	TSecTmV memesTimes;
	int bins = (end - begin) / period;
	for(int c=0;c<twitter.Len();c++)
	{
		int quoteIndex = twitter.GetKey(c);

		/*
		if (TStrUtil::CountWords(quotes.GetKey(quoteIndex))<8)
		{
			continue;
		}
		*/

		TIntV memesTimes;
		for(int i=0;i<quotes[quoteIndex].Len();i++)
		{
			memesTimes.Add(quotes[quoteIndex][i].time.GetAbsSecs());
		}
		double* vol_me = Tools::calculateHistOfCascade(memesTimes,begin,period,bins,false);
		double* vol_tu = Tools::calculateHistOfCascade(twitter.GetDat(quoteIndex),begin,period,bins,false);

		// calculating mean and standard deviation
		double mean = 0;
		for(int i=0;i<bins;i++)
		{
			mean += vol_me[i];
		}
		mean /= bins;

		double std = 0;
		for(int i=0;i<bins;i++)
		{
			std += pow(vol_me[i]-mean , 2);
		}
		std = sqrt(std / (bins-1));

		// peak definition by NIFTY: a point is a peak if its volume in 9 days binning is 1 standard deviation higher than the average frequency
		double maxVolume = mean + std;
		int peakCnt = 0;
		for(int i=0;i<bins;i++)
		{
			if(vol_me[i] > maxVolume)
			{
				peakCnt++;
			}
		}
		// if there is more than 5 peaks ignore this quote, since it is not a meme
		if(peakCnt > 5)
		{
			delete[] vol_me;
			continue;
		}

//		// To remove those Twitter has sooner start
//		if(isurls==true && twitter.GetDat(quoteIndex)[0].GetAbsSecs() < quotes[quoteIndex][0].time.GetAbsSecs())
//		{
//			delete[] vol_me;
//			delete[] vol_tu;
//			continue;
//		}

		quotesFiltered.AddDat(quotes.GetKey(quoteIndex),quotes[quoteIndex]);
		twitterFiltered.AddDat(quoteIndex,twitter.GetDat(quoteIndex));
		delete[] vol_me;
		delete[] vol_tu;
	}

	TZipOut mout(quotesName);
	quotesFiltered.Save(mout);
	printf("Saved %s has instances: %d\n\n\n",quotesName,quotesFiltered.Len());
	TZipOut tout(twName);
	twitterFiltered.Save(tout);
	printf("Saved %s has instances: %d\n\n\n",twName,twitterFiltered.Len());
}

int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	printf("((((( Starting The Filtering Cascades CODE )))))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nFiltering Memes Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// ---== Loading Data ==---
		TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_RANGEFIXED.rar");		///("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY.rar");
		THash< TStr , CascadeElementV > quotes;
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED has instances: %d\n\n\n",quotes.Len());

		TZipIn ZcascadesOnTwitterIn("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData.rar");
		//TZipIn ZcascadesOnTwitterIn("CascadesFullUrlsOnTwitterData.rar");
		THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn);
		printf("Loaded CascadesFullUrlsOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());

		TZipIn ZIn("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData.rar");
		THash< TUInt , TSecTmV > cascadesOnTwitterContents;
		cascadesOnTwitterContents.Load(ZIn);
		printf("Loaded CascadesOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterContents.Len());


		applyFilter(quotes,cascadesOnTwitterUrls,"QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar","CascadesFullUrlsOnTwitterData_FINALFILTERED.rar",true);
		applyFilter(quotes,cascadesOnTwitterContents,"QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar","CascadesOnTwitterData_FINALFILTERED.rar",false);

		printf("\nFilters had been done successfully.\n");
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


