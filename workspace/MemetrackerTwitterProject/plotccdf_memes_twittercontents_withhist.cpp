// Omid55

/*
 * plotccdf_memes_twittercontents_withhist.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: omid55
 */


#include "stdafx.h"

void plotCCDF_PrintPosNeg(double* arr, int leng, char* name, char* xlabel)
{
	TGnuPlot plot;
	TFltPrV middle;
	bool firstFound = false;
	double middleY;
	int i,pos=0,neg=0;
	double x1,y1,x2,y2,mean=0,posRatio,negRatio,x,y;
	TFltPrV points;

	printf("%s Drawing:\n",name);
	plot.SetXYLabel(xlabel, "P(X>d)");
	for(i=0;i<leng;i++)
	{
		if(arr[i] > 0)
		{
			pos++;
		}
		if(arr[i] < 0)
		{
			neg++;
		}
		mean += arr[i];
	}
	posRatio = (double)pos/leng;
	negRatio = (double)neg/leng;
	mean /= leng;

	printf("Positive Ratio: %f, Negative Ratio: %f\n",posRatio,negRatio);
	if(posRatio > 0.5)
	{
		printf("Twitter is sooner.\n");
	}
	else if(negRatio > 0.5)
	{
		printf("Memes is sooner.\n");
	}
	else
	{
		printf("They are equal!!!\n");
	}
	printf("Mean: %f\n",mean);

	// Ploting CCDF
	sort(arr,arr+leng);
	for(i=0;i<leng;i++)
	{
		x = arr[i];
		y = 1.0 - (1.0/leng)*i;
		points.Add(TFltPr(x,y));
		if(x > 0 && !firstFound)
		{
			firstFound = true;
			x1 = arr[i-1];
			y1 =  1.0 - (1.0/leng) * (i-1);
			x2 = x;
			y2 = y;
			middleY = -x1*(y2-y1)/(x2-x1)+y1;
			plot.SetTitle(TStr::Fmt("y is %f at x=0",middleY));
		}
	}

	middle.Add(TFltPr(0,middleY));
	plot.AddPlot(points,gpwLines);
	plot.AddPlot(middle,gpwPoints);
	plot.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
	plot.SaveEps(TStr::Fmt("MyResults/%s.eps",name));
	printf("%s had been drawn successfully.\n\n",name);
}

THash< TStr , CascadeElementV  > quotes;
THash< TUInt , TSecTmV > cascadesOnTwitterContents;


int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	double* vol_me;
	double* vol_tc;
	int c,i,quoteIndex,ind1,ind2,pos=0,neg=0,lengmax=0,lengmedian=0;
	double* medianDifference;
	double* maxDifference;
	double posRatio,negRatio,mean=0;
	uint period = 3600;   // Hour
	uint begin = TSecTm(2008,7,31,0,0,0).GetAbsSecs();
	uint end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
	int bins = (end - begin) / period;

	printf("((( Starting The Plot CCDF Meme-Twitter Contents Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nCCDF Plotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// ---== Loading Data ==---
		TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4Contents.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4Contents has instances: %d\n\n\n",quotes.Len());

		TZipIn ZIn("CascadesOnTwitterData_FILTERED.rar");	//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
		cascadesOnTwitterContents.Load(ZIn);
		printf("Loaded CascadesOnTwitterData_FILTERED has instances: %d\n\n\n",cascadesOnTwitterContents.Len());


		lengmax = 0;
		lengmedian = 0;
		maxDifference = new double[cascadesOnTwitterContents.Len()];
		medianDifference = new double[cascadesOnTwitterContents.Len()];
		for(c=0;c<cascadesOnTwitterContents.Len();c++)
		{
//			cout << "q" << c << ": " << quotes.GetKey(c).CStr() << endl;

			quoteIndex = cascadesOnTwitterContents.GetKey(c);
			vol_me = Tools::calculateHistOfCascade(quotes[c],begin,period,bins,true);
			vol_tc = Tools::calculateHistOfCascade(cascadesOnTwitterContents.GetDat(quoteIndex),begin,period,bins,true);

			ind1 = Tools::getMaxIndex(vol_me,bins);
			ind2 = Tools::getMaxIndex(vol_tc,bins);
			if(ind1 == -1 || ind2 == -1)
			{
				delete[] vol_me;
				delete[] vol_tc;
				continue;
			}
			maxDifference[lengmax++] = (double)ind1 - (double)ind2;

//			ind1 = Tools::getMedianIndex(vol_me,bins);
//			ind2 = Tools::getMedianIndex(vol_tc,bins);

			if(quotes[c].Len()==0 || cascadesOnTwitterContents[c].Len()==0)
			{
				continue;
			}
			ind1 = Tools::getTheBinIndex(quotes[c][quotes[c].Len()/2].time.GetAbsSecs(),begin,period);
			ind2 = Tools::getTheBinIndex(cascadesOnTwitterContents[c][cascadesOnTwitterContents[c].Len()/2].GetAbsSecs(),begin,period);

			if(ind1 == -1 || ind2 == -1)
			{
				delete[] vol_me;
				delete[] vol_tc;
				continue;
			}
			medianDifference[lengmedian++] = (double)ind1 - (double)ind2;

			delete[] vol_me;
			delete[] vol_tc;
		}
		printf("lengmax: %d, lengmedian: %d\n\n",lengmax,lengmedian);

		// Plot Drawing
		plotCCDF_PrintPosNeg(maxDifference,lengmax,"ContentsMaxHistDifferenceCCDF","d [(Memes max - Twitter max) of cascade's hist]");
		plotCCDF_PrintPosNeg(medianDifference,lengmedian,"ContentsMedianHistDifferenceCCDF","d [(Memes median - Twitter median) of cascade's hist]");

		delete[] maxDifference;
		delete[] medianDifference;
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


