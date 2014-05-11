// Omid55
/*
 * plot_centered_memes_cascade.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: omid55
 */

#include "stdafx.h"

THash< TStr , CascadeElementV > quotes;
//THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
//THash< TUInt , TSecTmV > cascadesOnTwitterContents;


int main(int argc, char* argv[])
{
	int bins,i,q,index,center,dif,Q,lengt,discards,minLen,smalls;
	double* vols;
	double* vol;
	TFltPrV volumes;
	uint period = 6 * 3600;   // 6 Hours
//	uint period = 24 * 3600;   // Day
	uint begin = TSecTm(2008,8,1,0,0,0).GetAbsSecs();
	uint end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
	TExeTm ExeTm;
	int DesiredCascadesCount = 1000;
	int* lengs;
	TGnuPlot plot;
	plot.SetXYLabel("Time(Day Bin)", "Volume");
	plot.SetTitle("Dayly Binned Volumes On Memetracker");

	printf("START The Plot Memes Cascades CODE ...\n");
	printf("\nbegin: %d, end: %d, period: %d\n\n",begin,end,period);
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Memes Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// ---== Loading Data ==---
		TZipIn ZquotesIn("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");    // /agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY has instances: %d\n\n\n",quotes.Len());

//		TZipIn ZcascadesOnTwitterIn("RESULTS/CascadesFullUrlsOnTwitterData.rar");
//		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn);
//		printf("Loaded CascadesFullUrlsOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());
//
//		TZipIn ZIn("RESULTS/CascadesOnTwitterData.rar");
//		cascadesOnTwitterContents.Load(ZIn);
//		printf("Loaded CascadesOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterContents.Len());

//		// JUST FOR CHECK 		<< DELETE IT >>
//		CascadeElementV v;
//		TSecTm t1(2008,9,1,0,0,0);
//		TSecTm t2(2008,10,1,0,0,0);
//		TSecTm t22(2008,10,21,12,0,0);
//		TSecTm t3(2008,11,28,12,0,0);
//		v.Add(CascadeElement(t1));
//		v.Add(CascadeElement(t2));
//		v.Add(CascadeElement(t22));
//		v.Add(CascadeElement(t3));
//		quotes.AddDat("1",v);
//
//		v.Clr();
//		TSecTm t4(2008,10,1,0,0,0);
//		TSecTm t5(2008,11,1,0,0,0);
//		TSecTm t55(2008,11,5,4,9,15);
//		TSecTm t6(2008,12,28,12,0,0);
//		v.Add(CascadeElement(t4));
//		v.Add(CascadeElement(t5));
//		v.Add(CascadeElement(t55));
//		v.Add(CascadeElement(t6));
//		quotes.AddDat("2",v);
//
////		v.Clr();
////		TSecTm t7(2008,11,1,0,0,0);
////		TSecTm t8(2009,04,2,2,0,0);
////		v.Add(CascadeElement(t7));
////		v.Add(CascadeElement(t8));
////		quotes.AddDat("3",v);
//		// JUST FOR CHECK 		<< DELETE IT >>


		// DO REMOVING WITH MULTIPLE MAXS
		// INJAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA


		// ---== Computation ==---
		Q = quotes.Len();
		bins = (end - begin) / period;
		lengt = 2 * bins + 1;
		center = (lengt-1) / 2;
		vols = new double[lengt];
		for(i=0;i<lengt;i++)
		{
			vols[i] = 0;
		}

		int* lengs = new int[Q];
		for(q=0;q<Q;q++)
		{
			lengs[q] = quotes[q].Len();
		}
		sort(lengs,lengs+Q,std::greater<int>());
		minLen = lengs[DesiredCascadesCount-1];
//		cout << "first: " << lengs[0] << " , last: " << lengs[Q-1] << endl;
//		cout << "minLen: " << minLen << endl;
		delete[] lengs;

		smalls = 0;
		discards = 0;
		for(q=0;q<Q;q++)
		{
			if(quotes[q].Len() < minLen)
			{
				smalls++;
				continue;
			}
			vol = Tools::calculateHistOfCascade(quotes[q],begin,period,bins,true);
//			index = getMaxIndex(vol,bins);
			index = Tools::getMedianIndex(vol,bins);
			if(index == -1)    // we have a larger timeseries in meme tracker than twitter then there are some cascades which they have nothing in the desired range (then we will discard them)
			{
				discards++;
				continue;
			}
			dif = center - index;
			for(i=0;i<bins;i++)
			{
				vols[dif + i] += vol[i];
			}

			delete[] vol;
		}
		quotes.Clr();
		printf("Discards: %d, smalls: %d\n\n",discards,smalls);
//		for(i=0;i<lengt;i++)
		int myleng = 20;
//		int myleng = 5;
		for(i=center-myleng;i<=center+myleng;i++)
		{
			vols[i] /= (Q-discards-smalls);
			TFltPr elem;
			elem.Val1 = -center + i;
			elem.Val2 = vols[i];
			volumes.Add(elem);
		}
		plot.AddPlot(volumes,gpwPoints);
		plot.SetDataPlotFNm("MyResults/Memes-Volumes.tab", "MyResults/Memes-Volumes.plt");
		plot.SaveEps("MyResults/Memes-Volumes.eps",true);

		printf("Plots had been drawn successfully.");
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
