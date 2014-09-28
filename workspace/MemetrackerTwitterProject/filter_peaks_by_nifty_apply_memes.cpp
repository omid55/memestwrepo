// Omid55

/*
 * filter_peaks_by_nifty_apply_memes.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: omid55
 */

// Omid55
#include "stdafx.h"

int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	THash< TStr , CascadeElementV > quotesFiltered;
	double* vol_me;
	uint period = 9 * 3600;   // 9 days because of NIFTY paper

	printf("((((( Starting The Filtering Cascades CODE )))))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nFiltering Memes Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// ---== Loading Data ==---
		TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY.rar");		///("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");
		THash< TStr , CascadeElementV > quotes;
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY has instances: %d\n\n\n",quotes.Len());

		// NIFTY Method for Filtering by Peaks
		uint begin = TSecTm(2008,7,31,0,0,0).GetAbsSecs();
		uint end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
		TSecTmV memesTimes;
		int bins = (end - begin) / period;
		for(int c=0;c<quotes.Len();c++)
		{
			memesTimes.Clr();
			for(int i=0;i<quotes[c].Len();i++)
			{
				memesTimes.Add(quotes[c][i].time);
			}
			vol_me = Tools::calculateHistOfCascade(memesTimes,begin,period,false);

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

			quotesFiltered.AddDat(quotes.GetKey(c),quotes[c]);
			delete[] vol_me;
		}

		TZipOut mout("QuotesPreprocessedData_NIFTY_FINALFILTERED.rar");
		quotesFiltered.Save(mout);
		printf("Saved QuotesPreprocessedData_NIFTY_FINALFILTERED has instances: %d\n\n\n",quotesFiltered.Len());

		printf("\nThe Meme Filter for plotting had been done successfully.\n");
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


