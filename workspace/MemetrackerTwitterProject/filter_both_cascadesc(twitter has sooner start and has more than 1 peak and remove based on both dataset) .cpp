// Omid55

/*
 * filter_both_cascadesc.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: omid55
 */

// Omid55

#include "stdafx.h"

void doFilter(THash< TStr , CascadeElementV >& quotes,THash< TUInt , TSecTmV >& OnTwitter,char* quotesName,char* twUrlsName,bool isurls)
{
	int diff,i1,i2;
	THash< TStr , CascadeElementV > quotesFiltered;
	THash< TUInt , TSecTmV > onTwitterFiltered;

	double* vol_me;
	double* vol_tu;
	uint period = 30 * 24 * 3600;   // Month

	uint begin = TSecTm(2008,7,31,0,0,0).GetAbsSecs();
	uint end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
	TSecTmV ti;
	int quoteIndex,i,c;
	int bins = (end - begin) / period;
	for(c=0;c<OnTwitter.Len();c++)
	{
		quoteIndex = OnTwitter.GetKey(c);

		/*
		if (TStrUtil::CountWords(quotes.GetKey(quoteIndex))<8)
		{
			continue;
		}
		*/

		ti.Clr();
		for(i=0;i<quotes[quoteIndex].Len();i++)
		{
			ti.Add(quotes[quoteIndex][i].time);
		}
		vol_me = Tools::calculateHistOfCascade(ti,begin,period,bins,false);
		vol_tu = Tools::calculateHistOfCascade(OnTwitter.GetDat(quoteIndex),begin,period,bins,false);

		i1 = Tools::getMaxIndex(vol_me,bins);
		i2 = Tools::getMaxIndex(vol_tu,bins);
		if(i1==-1 || i2==-1)
		{
			delete[] vol_me;
			delete[] vol_tu;
			continue;
		}
		diff = abs(i1 - i2);

		if(diff > 1)  // 1 month
		{
			delete[] vol_me;
			delete[] vol_tu;
			continue;
		}


		// To remove those Twitter has sooner start
		if(isurls==true && OnTwitter.GetDat(quoteIndex)[0].GetAbsSecs() < quotes[quoteIndex][0].time.GetAbsSecs())
		{
			delete[] vol_me;
			delete[] vol_tu;
			continue;
		}


		/*
		period = 24 * 3600;   // Day
		bins = (end - begin) / period;
		vol_me = calculateHistOfCascade(ti,begin,period,bins,false);
		vol_tu = calculateHistOfCascade(cascadesOnTwitterUrls.GetDat(quoteIndex),begin,period,bins,false);

		i1 = getMaxIndex(vol_me,bins);
		i2 = getMaxIndex(vol_tu,bins);
		if(i1==-1 || i2==-1)
		{
			continue;
		}
		diff = abs(i1 - i2);

		if(diff > 14)   // 14 days
		{
			continue;
		}
		*/

		quotesFiltered.AddDat(quotes.GetKey(quoteIndex),quotes[quoteIndex]);
		onTwitterFiltered.AddDat(quoteIndex,OnTwitter.GetDat(quoteIndex));
		delete[] vol_me;
		delete[] vol_tu;
	}

	TZipOut mout(quotesName);
	quotesFiltered.Save(mout);
	printf("Saved %s has instances: %d\n\n\n",quotesName,quotesFiltered.Len());
	TZipOut tout(twUrlsName);
	onTwitterFiltered.Save(tout);
	printf("Saved %s has instances: %d\n\n\n",twUrlsName,onTwitterFiltered.Len());
}


int main(int argc, char* argv[])
{
	TExeTm ExeTm;

	printf("((((( Starting The Filtering Cascades CODE )))))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// ---== Loading Data ==---
		TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_RANGEFIXED.rar");		///("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");
		THash< TStr , CascadeElementV > quotes;
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY has instances: %d\n\n\n",quotes.Len());

		TZipIn ZcascadesOnTwitterIn("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesFullUrlsOnTwitterData.rar");
		//TZipIn ZcascadesOnTwitterIn("CascadesFullUrlsOnTwitterData.rar");
		THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn);
		printf("Loaded CascadesFullUrlsOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());

		TZipIn ZIn("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
		THash< TUInt , TSecTmV > cascadesOnTwitterContents;
		cascadesOnTwitterContents.Load(ZIn);
		printf("Loaded CascadesOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterContents.Len());

		doFilter(quotes,cascadesOnTwitterUrls,"QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4URLS.rar","CascadesFullUrlsOnTwitterData_FILTERED.rar",true);
		doFilter(quotes,cascadesOnTwitterContents,"QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4Contents.rar","CascadesOnTwitterData_FILTERED.rar",false);

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


