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

		// === FINAL PHASE of NIFTY (REMOVING WITH MULTIPLE PEAKS) ===
		double* vol_me = Tools::calculateHistOfCascade(quotes[quoteIndex],begin,period,bins,false);
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
		if(peakCnt > 5) // if there is more than 5 peaks ignore this quote, since it is not a meme
		{
			delete[] vol_me;
			continue;
		}
		// === FINAL PHASE of NIFTY (REMOVING WITH MULTIPLE PEAKS) ===


//		// To remove those Twitter has sooner start
//		if(isurls==true && twitter.GetDat(quoteIndex)[0].GetAbsSecs() < quotes[quoteIndex][0].time.GetAbsSecs())
//		{
//			delete[] vol_me;
//			delete[] vol_tu;
//			continue;
//		}

		quotesFiltered.AddDat(quotes.GetKey(quoteIndex),quotes[quoteIndex]);
		twitterFiltered.AddDat(quotesFiltered.Len()-1,twitter.GetDat(quoteIndex));  // we do not use the first one since we use the both indices
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

THash< TUInt , TSecTmV > getFiltereds(THash< TStr , CascadeElementV >& quotes,THash< TUInt , TSecTmV >& twitter,bool isurls)
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

		// === FINAL PHASE of NIFTY (REMOVING WITH MULTIPLE PEAKS) ===
		double* vol_me = Tools::calculateHistOfCascade(quotes[quoteIndex],begin,period,bins,false);

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
		if(peakCnt > 5) // if there is more than 5 peaks ignore this quote, since it is not a meme
		{
			delete[] vol_me;
			continue;
		}
		// === FINAL PHASE of NIFTY (REMOVING WITH MULTIPLE PEAKS) ===


//		// To remove those Twitter has sooner start
//		if(isurls==true && twitter.GetDat(quoteIndex)[0].GetAbsSecs() < quotes[quoteIndex][0].time.GetAbsSecs())
//		{
//			delete[] vol_me;
//			continue;
//		}

		twitterFiltered.AddDat(quoteIndex,twitter.GetDat(quoteIndex));    // Due to not having quotesData filtering here, we certainly need quoteIndex
		delete[] vol_me;
	}

	return twitterFiltered;
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
		TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_RANGEFIXED.rar");		///("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY.rar");
		THash< TStr , CascadeElementV > quotes;
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED has instances: %d\n\n\n",quotes.Len());

		TZipIn ZcascadesOnTwitterIn("/NS/twitter-5/work/oaskaris/DATA/CascadesFullUrlsOnTwitterData.rar");
		//TZipIn ZcascadesOnTwitterIn("CascadesFullUrlsOnTwitterData.rar");
		THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn);
		printf("Loaded CascadesFullUrlsOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());

		TZipIn ZIn("/NS/twitter-5/work/oaskaris/DATA/CascadesOnTwitterData.rar");
		THash< TUInt , TSecTmV > cascadesOnTwitterContents;
		cascadesOnTwitterContents.Load(ZIn);
		printf("Loaded CascadesOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterContents.Len());


		// Filtering
		/////applyFilter(quotes,cascadesOnTwitterUrls,"QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar","CascadesFullUrlsOnTwitterData_FINALFILTERED.rar",true);
		/////applyFilter(quotes,cascadesOnTwitterContents,"QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar","CascadesOnTwitterData_FINALFILTERED.rar",false);


		// For BOTH TOGETHER
		int ln = 0;
		THash< TUInt , TSecTmV > twUrl = getFiltereds(quotes,cascadesOnTwitterUrls,true);
		THash< TUInt , TSecTmV > twCon = getFiltereds(quotes,cascadesOnTwitterContents,true);
		THash< TUInt , TSecTmV > twUrlResult;
		THash< TUInt , TSecTmV > twConResult;
		THash< TStr , CascadeElementV > quotesResult;
		for(int i=0;i<twUrl.Len();i++)
		{
			if(twCon.GetKeyId(twUrl.GetKey(i)) != -1)
			{
				ln++;
				quotesResult.AddDat(quotes.GetKey(twUrl.GetKey(i)),quotes[twUrl.GetKey(i)]);
				twUrlResult.AddDat(quotesResult.Len()-1,twUrl[i]);
				twConResult.AddDat(quotesResult.Len()-1,twCon.GetDat(twUrl.GetKey(i)));
			}
		}

		double percentage = 100 * (double)ln/twUrl.Len();
		printf("\n\nPercentage of Urls having Contents cascaded over Twitter as well: %f\n\n",percentage);

		TStr quotesName = "QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar";
		TStr twNameUrl = "CascadesFullUrlsOnTwitterData_FINALFILTERED_HAVINGBOTH.rar";
		TStr twNameCon = "CascadesOnTwitterData_FINALFILTERED_HAVINGBOTH.rar";

		TZipOut mout(quotesName);
		quotesResult.Save(mout);
		printf("Saved %s has instances: %d\n\n\n",quotesName.CStr(),quotesResult.Len());

		TZipOut tout1(twNameUrl);
		twUrlResult.Save(tout1);
		printf("Saved %s has instances: %d\n\n\n",twNameUrl.CStr(),twUrlResult.Len());

		TZipOut tout2(twNameCon);
		twConResult.Save(tout2);
		printf("Saved %s has instances: %d\n\n\n",twNameCon.CStr(),twConResult.Len());
		// For BOTH TOGETHER

		printf("\nFilters has been done successfully.\n");
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


