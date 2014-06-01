// Omid55
/*
 * plot_one_quote_cascade.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: omid55
 */

#include "stdafx.h"

void doCompute(	THash< TStr , CascadeElementV > memes, THash< TUInt , TSecTmV > twitter, int quoteIdx, bool normalized, char* name)
{
	int minlen = 10;
	int mincascadelen = 10;
	int minlenhisted = 4;

	int bins,i,c,index,minLen;
	double* vol_me;
	double* vol_tu;
	TFltPrV volumes_memes;
	TFltPrV volumes_twitter_urls;
	uint period = 24 * 3600;   // days
	uint begin = TSecTm(2008,7,31,0,0,0).GetAbsSecs();
	uint end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
	bins = (end - begin) / period;
	int cnt = 0;
	for(i=0;i<memes.Len();i++)
	{
		if(TStrUtil::CountWords(memes.GetKey(i)) >= minlen && memes[i].Len() >= mincascadelen && twitter[i].Len() >= mincascadelen)
		{
			// ---== Computation ==---
			vol_me = Tools::calculateHistOfCascade(memes[i],begin,period,bins,normalized);
			vol_tu = Tools::calculateHistOfCascade(twitter[i],begin,period,bins,normalized);
			if(Tools::countNoneZeros(vol_me,bins) < minlenhisted || Tools::countNoneZeros(vol_tu,bins) < minlenhisted)
			{
				delete[] vol_me;
				delete[] vol_tu;
				continue;
			}

			if(cnt == quoteIdx)
			{
				quoteIdx = i;
				TGnuPlot plot;
				plot.SetXYLabel("Time [days]", "Volume");
				plot.SetTitle(memes.GetKey(quoteIdx).CStr());
				printf("\nQuote(%d): %s\n\n",quoteIdx,memes.GetKey(quoteIdx).CStr());

				TPair<TInt,TInt> r1 = Tools::findRangeWithValues(vol_me,bins);
				TPair<TInt,TInt> r2 = Tools::findRangeWithValues(vol_tu,bins);
				int indexBegin = min(r1.Val1.Val,r2.Val1.Val);
				int indexEnd = max(r1.Val2.Val,r2.Val2.Val);
				TStr xticsMemes = "set xtics (", xticsTw = "set xtics (";;
				for(i=indexBegin;i<=indexEnd;i++)
				{
					if(vol_me[i]>0)
					{
						volumes_memes.Add(TFltPr(i,vol_me[i]));
						TSecTm newDate(begin + i * period);
						xticsMemes += TStr::Fmt("\"%d/%d %d:%d\" %d, ", newDate.GetMonthN(), newDate.GetDayN(), newDate.GetHourN(), newDate.GetMinN(), i);
					}
					if(vol_tu[i]>0)
					{
						volumes_twitter_urls.Add(TFltPr(i,vol_tu[i]));
						TSecTm newDate(begin + i * period);
						xticsTw += TStr::Fmt("\"%d/%d %d:%d\" %d, ", newDate.GetMonthN(), newDate.GetDayN(), newDate.GetHourN(), newDate.GetMinN(), i);
					}
				}
				delete[] vol_me;
				delete[] vol_tu;

				xticsMemes = xticsMemes.GetSubStr(0,xticsMemes.Len()-3) + ")";
				xticsTw = xticsTw.GetSubStr(0,xticsTw.Len()-3) + ")";


				plot.SetTitle(memes.GetKey(quoteIdx));
				plot.AddPlot(volumes_memes,gpwPoints,"Memes");
				plot.AddPlot(volumes_twitter_urls,gpwPoints,"Urls on Twitter");
				plot.AddCmd(xticsMemes);
				plot.SetDataPlotFNm(TStr::Fmt("MyResults/Quote%d-%s.tab",quoteIdx,name), TStr::Fmt("MyResults/Quote%d-%s.plt",quoteIdx,name));
				plot.SaveEps(TStr::Fmt("MyResults/Quote%d-%s.eps",quoteIdx,name),true);

				TGnuPlot pl;
				pl.SetXYLabel("Time [days]", "Volume");
				pl.SetTitle(memes.GetKey(quoteIdx).CStr());
				pl.AddPlot(volumes_memes,gpwLinesPoints,"Memes");
				pl.AddPlot(volumes_twitter_urls,gpwLinesPoints,"Urls on Twitter");
				plot.AddCmd(xticsTw);
				pl.SetDataPlotFNm(TStr::Fmt("MyResults/Quote%d-%s-Original.tab",quoteIdx,name), TStr::Fmt("MyResults/Quote%d-%s-Original.plt",quoteIdx,name));
				pl.SaveEps(TStr::Fmt("MyResults/Quote%d-%s-Original.eps",quoteIdx,name));

				break;
			}
			delete[] vol_me;
			delete[] vol_tu;
			cnt++;
		}
	}
}


int main(int argc, char* argv[])
{
//	Tools::loadQuotes("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED.rar");
//	return 0;

	THash< TStr , CascadeElementV > quotesUrls;
	THash< TStr , CascadeElementV > quotesContents;
	THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
	THash< TUInt , TSecTmV > cascadesOnTwitterContents;
	TExeTm ExeTm;
	int quoteIdx = 0;
	bool normalized = false;

	if(argc==2)
	{
		quoteIdx = atoi(argv[1]);
	}

	printf("<<< Starting Plot ONE cascade CODE >>>\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// ---== Loading Data ==---
//		TZipIn ZquotesIn1("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4URLS.rar");
		TZipIn ZquotesIn1("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS.rar");
		quotesUrls.Load(ZquotesIn1);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS has instances: %d\n\n\n",quotesUrls.Len());

//		TZipIn ZcascadesOnTwitterIn("CascadesFullUrlsOnTwitterData_FILTERED.rar");
		TZipIn ZcascadesOnTwitterIn("/agbs/cluster/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED.rar");
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn);
		printf("Loaded CascadesFullUrlsOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());

		TZipIn ZquotesIn2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents.rar");	//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");      ///("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotesContents.Load(ZquotesIn2);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents has instances: %d\n\n\n",quotesContents.Len());

		TZipIn ZIn("/agbs/cluster/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED.rar");	//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
		cascadesOnTwitterContents.Load(ZIn);
		printf("Loaded CascadesOnTwitterData_FINALFILTERED has instances: %d\n\n\n",cascadesOnTwitterContents.Len());


		// Computing
		while(true)
		{
			doCompute(quotesContents, cascadesOnTwitterContents, quoteIdx, normalized, "Content");
			doCompute(quotesUrls, cascadesOnTwitterUrls, quoteIdx, normalized, "Url");
			cout << "\n\nPlease Enter Next Quote Index: ";
			cin >> quoteIdx;
			if (quoteIdx < 0)
			{
				break;
			}
		}
		printf("\nPlot had been drawn successfully.");
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
