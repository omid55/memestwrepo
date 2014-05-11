// Omid55
/*
 * plot_centered_memes_twittercontents_cascades.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: omid55
 */

#include "stdafx.h"

THash< TStr , CascadeElementV > quotes;
THash< TUInt , TSecTmV > cascadesOnTwittercontents;

void doCompute(Mode mode)
{
	TSecTmV ti;
	int bins,i,c,index,center,dif,lengt,validCascadesCnt,minLen,myrange,quoteIndex,ind1,ind2;
	double* vols_memes;
	double* vols_twitter_contents;
	double* vol_me;
	double* vol_tu;
	TFltPrV volumes_memes;
	TFltPrV volumes_twitter_contents;
	uint period = 3600;   // Hour
	uint begin = TSecTm(2008,7,31,0,0,0).GetAbsSecs();
	uint end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
	TGnuPlot plot;
	plot.SetXYLabel("Time(Hour Bin)", "Volume");
	plot.SetTitle("Hourly Binned Quotes Cascade over Memetracker and its contents over Twitter");

	// ---== Computation ==---
	bins = (end - begin) / period;
	printf("bins: %d\n\n",bins);
	lengt = 2 * bins + 1;
	center = (lengt-1) / 2;
	vols_memes = new double[lengt];
	vols_twitter_contents = new double[lengt];
	for(i=0;i<lengt;i++)
	{
		vols_memes[i] = 0;
		vols_twitter_contents[i] = 0;
	}

	validCascadesCnt = 0;
	for(c=0;c<cascadesOnTwittercontents.Len();c++)
	{
		quoteIndex = cascadesOnTwittercontents.GetKey(c);
		ti.Clr();
		for(i=0;i<quotes[c].Len();i++) ///for(i=0;i<quotes[quoteIndex].Len();i++)
		{
			ti.Add(quotes[c][i].time); ///ti.Add(quotes[quoteIndex][i].time);
		}
		vol_me = Tools::calculateHistOfCascade(ti,begin,period,bins,true);
		vol_tu = Tools::calculateHistOfCascade(cascadesOnTwittercontents.GetDat(quoteIndex),begin,period,bins,true);

		if(mode == MEDIAN)
		{
			ind1 = Tools::getMedianIndex(vol_me,bins);
			ind2 = Tools::getMedianIndex(vol_tu,bins);
		}
		if(mode == MAX)
		{
			ind1 = Tools::getMaxIndex(vol_me,bins);
			ind2 = Tools::getMaxIndex(vol_tu,bins);
		}
		if(ind1 == -1 || ind2 == -1)
		{
			delete[] vol_me;
			delete[] vol_tu;
			continue;
		}


//		//////////
//		if(validCascadesCnt==2)
//		{
//			break;
//		}
//		cout << ind1 << " , " << ind2 << endl;
//		cout << "center: " << center << endl;
////		if(ind1 < ind2)
////		{
////			delete[] vol_me;
////			delete[] vol_tu;
////			continue;
////		}
//		//////////


		index = (ind1 + ind2) / 2;
		dif = center - index;
		for(i=0;i<bins;i++)
		{
			vols_memes[dif + i] += vol_me[i];
			vols_twitter_contents[dif + i] += vol_tu[i];
		}
		validCascadesCnt++;

		delete[] vol_me;
		delete[] vol_tu;
	}

	myrange = 48;



//	///////
//	// -------------REMOVE IT------------------
//	if(mode == MAX)
//	{
//		double maxInd = -1;
//		double mx = -999;
//		for(i=0;i<lengt;i++)
//		{
//			if(vols_memes[i] > mx)
//			{
//				maxInd = i;
//				mx = vols_memes[i];
//			}
//		}
//		cout << "vols_memes Max Ind: " << maxInd << " , max: " << mx/validCascadesCnt << endl;
//
//		mx = -999;
//		maxInd = -1;
//		for(i=0;i<lengt;i++)
//		{
//			if(vols_twitter_contents[i] > mx)
//			{
//				maxInd = i;
//				mx = vols_twitter_contents[i];
//			}
//		}
//		cout << "vols_twitter_contents Max Ind: " << maxInd << " , max: " << mx/validCascadesCnt << endl;
//	}
//	// ----------REMOVE IT---------------------
//	///////



	printf("\n--===((( Cascades Count is: %d )))===--\n",validCascadesCnt);
//		for(i=0;i<lengt;i++)
	for(i=center-myrange;i<=center+myrange;i++)
	{
		vols_memes[i] /= validCascadesCnt;
		volumes_memes.Add(TFltPr(-center+i,vols_memes[i]));

		vols_twitter_contents[i] /= validCascadesCnt;
		volumes_twitter_contents.Add(TFltPr(-center+i,vols_twitter_contents[i]));
	}
	plot.AddPlot(volumes_memes,gpwPoints,"Memes");
	plot.AddPlot(volumes_twitter_contents,gpwPoints,"Twitter contents");
	if(mode == MEDIAN)
	{
		plot.SetDataPlotFNm("MyResults/Memes-Twitter-contents-MEDIAN-Volumes.tab", "MyResults/Memes-Twitter-contents-MEDIAN-Volumes.plt");
		plot.SaveEps("MyResults/Memes-Twitter-contents-MEDIAN-Volumes.eps",true);
	}
	if(mode == MAX)
	{
		plot.SetDataPlotFNm("MyResults/Memes-Twitter-contents-MAX-Volumes.tab", "MyResults/Memes-Twitter-contents-MAX-Volumes.plt");
		plot.SaveEps("MyResults/Memes-Twitter-contents-MAX-Volumes.eps",true);
	}

	delete[] vols_memes;
	delete[] vols_twitter_contents;
}


int main(int argc, char* argv[])
{
	TExeTm ExeTm;

	printf("((( Starting The Plot Memes-Twitter contents Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Memes-TU Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// ---== Loading Data ==---
		TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4Contents.rar");	//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");      ///("QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED.rar");
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED_FILTERED_4Contents has instances: %d\n\n\n",quotes.Len());

		TZipIn ZIn("CascadesOnTwitterData_FILTERED.rar");	//("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/CascadesOnTwitterData.rar");
		cascadesOnTwittercontents.Load(ZIn);
		printf("Loaded CascadesOnTwitterData_FILTERED has instances: %d\n\n\n",cascadesOnTwittercontents.Len());

		// Computing
		doCompute(MEDIAN);
		doCompute(MAX);

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
