// Omid55

/*
 * plotccdf_memes_twitter.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: omid55
 */

#include "stdafx.h"

// Omid55

/*
 * plotccdf_memes_twittercontents.cpp
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
//	THash< TChA , TUInt > posts;
//	TZipIn ZpostsIn("PostsData.rar");
//	posts.Load(ZpostsIn);
//	printf("PostsData loading done, it contains %d posts.\n",posts.Len());
//	return 0;


	TExeTm ExeTm;
	int i,quoteIndex;
	double* medianDifference;
	double* startDifference;
	double* endDifference;
	double posRatio,negRatio,mean=0;

	printf("((( Starting The Plot CCDF Meme-Twitter Contents Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nCCDF Plotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// REMOVE IT
		TZipIn ZquotesIn1("Quotes_TEST_4Urls.rar");		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");   //("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotes.Load(ZquotesIn1);
		printf("Loaded Quotes_TEST_4Urls has instances: %d\n\n\n",quotes.Len());

		TZipIn ZcascadesOnTwitterIn2("Cascades_TEST_4Contents.rar"); 		//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
		cascadesOnTwitterContents.Load(ZcascadesOnTwitterIn2);
		printf("Loaded Cascades_TEST_4Contents has instances: %d\n\n\n",cascadesOnTwitterContents.Len());
		// REMOVE IT

		medianDifference = new double[cascadesOnTwitterContents.Len()];
		startDifference = new double[cascadesOnTwitterContents.Len()];
		endDifference = new double[cascadesOnTwitterContents.Len()];
		for(i=0;i<cascadesOnTwitterContents.Len();i++)
		{
			quoteIndex = cascadesOnTwitterContents.GetKey(i);
			CascadeElementV memesCascade = quotes[i]; ///quotes[quoteIndex];
			TSecTmV twCascade = cascadesOnTwitterContents.GetDat(quoteIndex);

			medianDifference[i] = (double)memesCascade[memesCascade.Len()/2].time.GetAbsSecs() - (double)twCascade[twCascade.Len()/2].GetAbsSecs();
			startDifference[i] = (double)memesCascade[0].time.GetAbsSecs() - (double)twCascade[0].GetAbsSecs();
			endDifference[i] = (double)memesCascade[memesCascade.Len()-1].time.GetAbsSecs() - (double)twCascade[twCascade.Len()-1].GetAbsSecs();
		}

		// Plot Drawing
		plotCCDF_PrintPosNeg(medianDifference,cascadesOnTwitterContents.Len(),"ContentsMedianDifferenceCCDF","d [(Memes median - Twitter median) of cascade's times]");
		plotCCDF_PrintPosNeg(startDifference,cascadesOnTwitterContents.Len(),"ContentsStartDifferenceCCDF","d [(Memes start - Twitter start) of cascade's times]");
		plotCCDF_PrintPosNeg(endDifference,cascadesOnTwitterContents.Len(),"ContentsEndDifferenceCCDF","d [(Memes end - Twitter end) of cascade's times]");
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
