// Omid55
/*
 * plot_individually_centered_both_cascades.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: omid55
 */

#include "stdafx.h"

// CalculateHistOfCascade
//double* myCalculateHistOfCascadeWithCenter(TIntV& cascade, double rbegin, uint rperiod, bool normalized)
//{
//	int length = -rbegin * 2 / rperiod;
//	int i,index, centerIndex;
//	double* vols = new double[length];
//	for(i=0;i<length;i++)
//	{
//		vols[i] = 0;
//	}
//	for(i=0;i<cascade.Len();i++)
//	{
//		index = Tools::getTheBinIndex(cascade[i],rbegin,rperiod);
//		if(index >= length || index < 0)
//		{
//			continue;
//		}
//
//		vols[index]++;
//	}
//	if(normalized)
//	{
//		// NORMALAZING BASED ON MAX VALUE OF PEAK
//		//		double max = 0;
//		//		for(i=0;i<length;i++)
//		//		{
//		//			if(vols[i] > max)
//		//			{
//		//				max = vols[i];
//		//			}
//		//		}
//		//		if(max != 0)
//		//		{
//		//			for(i=0;i<length;i++)
//		//			{
//		//				vols[i] /= max;
//		//			}
//		//		}
//
//		// NORMALIZING BASED ON THE NUMBER OF MENTIONS
//		for(i=0;i<length;i++)
//		{
//			vols[i] /= cascade.Len();
//		}
//	}
//	return vols;
//}

//static int myrange = 3;
//static int begin = 3;
//static int end = 12;
// plotTwoIndividuallyShift
//void mytesttt(THash<TStr,TFltV>& quotes, THash<TUInt,TFltV>& twitter, uint period, char* periodstr, char* name)
//{
//	int bins = (end - begin) / period;
//	int lengt = 2 * bins + 1;
//	int center = bins;   //(lengt - 1) / 2;
//	double* memeVolumes = new double[lengt];
//	double* twitterVolumes = new double[lengt];
//	for(int i=0;i<lengt;i++)
//	{
//		memeVolumes[i] = 0;
//		twitterVolumes[i] = 0;
//	}
//
//	for(int q=0;q<quotes.Len();q++)
//	{
//		int leng = quotes[q].Len() + twitter[q].Len();
//		int* integratedTimestamps = new int[leng];
//		for(int i=0;i<quotes[q].Len();i++)
//		{
//			integratedTimestamps[i] = quotes[q][i];
//		}
//		for(int i=0;i<twitter[q].Len();i++)
//		{
//			integratedTimestamps[quotes[q].Len()+i] = twitter[q][i];
//		}
//		sort(integratedTimestamps,integratedTimestamps+leng);
//		int medIndex = (leng-1)/2;
//		int integratedMedianValue = integratedTimestamps[medIndex];
//		delete[] integratedTimestamps;
//
//		TIntV memeCascade;
//		for(int i=0;i<quotes[q].Len();i++)
//		{
//			memeCascade.Add((int)quotes[q][i] - integratedMedianValue);
//		}
//		TIntV twitterCascade;
//		for(int i=0;i<twitter[q].Len();i++)
//		{
//			twitterCascade.Add((int)twitter[q][i] - integratedMedianValue);
//		}
//		double beginShifted = period * (0.5 + floor((end - begin) / period)) * -1.0;
//
//		double* memeVol = Tools::calculateHistOfCascade(memeCascade,beginShifted,period,true);
//		memeCascade.Clr();
//		for(int i=0;i<lengt;i++)
//		{
//			memeVolumes[i] += memeVol[i];
//		}
//		delete[] memeVol;
//
//		double* twitterVol = Tools::calculateHistOfCascade(twitterCascade,beginShifted,period,true);
//		twitterCascade.Clr();
//		for(int i=0;i<lengt;i++)
//		{
//			twitterVolumes[i] += twitterVol[i];
//		}
//		delete[] twitterVol;
//	}
//
//	printf("\n\nPlotting ...\n");
//	TFltPrV memeVolumes4Plot;
//	TFltPrV twitterVolumes4Plot;
//	IAssert(center-myrange>=0 && center+myrange<lengt);
//	for(int i=center-myrange;i<=center+myrange;i++)
////	for(int i=0;i<lengt;i++)
//	{
//		memeVolumes[i] /= quotes.Len();
//		twitterVolumes[i] /= quotes.Len();
//		TFltPr elem1;
//		elem1.Val1 = -center + i;
//		elem1.Val2 = memeVolumes[i];
//		memeVolumes4Plot.Add(elem1);
//		cout << "memeVolumes[" << i << "]: " << memeVolumes[i] << endl;
//
//		TFltPr elem2;
//		elem2.Val1 = -center + i;
//		elem2.Val2 = twitterVolumes[i];
//		twitterVolumes4Plot.Add(elem2);
//		cout << "twitterVolumes[" << i << "]: " << twitterVolumes[i] << endl;
//	}
//	delete[] memeVolumes;
//	delete[] twitterVolumes;
//
//	// Plotting
////	TGnuPlot plot1;
////	plot1.SetXYLabel("Time[hours]", "Volume");
////	plot1.AddPlot(memeVolumes4Plot,gpwLinesPoints,"Memes");
////	plot1.AddPlot(twitterVolumes4Plot,gpwLinesPoints,"Twitter");
////	plot1.SetDataPlotFNm(TStr::Fmt("MyResults/%s-Original.tab",name), TStr::Fmt("MyResults/%s-Original.plt",name));
////	plot1.SaveEps(TStr::Fmt("MyResults/%s-Original.eps",name));
//
//	TGnuPlot plot2;
//	plot2.SetXYLabel(TStr::Fmt("Time[%s]",periodstr), "Volume");
//	plot2.AddPlot(memeVolumes4Plot,gpwPoints,"Memes");
//	plot2.AddPlot(twitterVolumes4Plot,gpwPoints,"Twitter");
//	plot2.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
//	plot2.SaveEps(TStr::Fmt("MyResults/%s.eps",name),true);
//
//	printf("Plot %s is done.\n",name);
//}


// DELETE IT
static int myrange = 24;
static int begin = TSecTm(2008,7,31,0,0,0).GetAbsSecs();
static int end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
bool myPlotTwoIndividuallyShift(THash<TStr,CascadeElementV>& quotes, THash<TUInt,TSecTmV>& twitter, uint period, char* periodstr, char* name)
{
	int bins = (end - begin) / period;
	///cout << "BINS: " << bins << ", Memetracker Len: " << quotes.Len() << ", Twitter Len: " << twitter.Len() << endl << endl;
	int lengt = 2 * bins + 1;
	int center = bins;   //(lengt - 1) / 2;
	double* memeVolumes = new double[lengt];
	double* twitterVolumes = new double[lengt];
	for(int i=0;i<lengt;i++)
	{
		memeVolumes[i] = 0;
		twitterVolumes[i] = 0;
	}

	for(int q=0;q<quotes.Len();q++)
	{
		int leng = quotes[q].Len() + twitter[q].Len();
		int* integratedTimestamps = new int[leng];
		for(int i=0;i<quotes[q].Len();i++)
		{
			integratedTimestamps[i] = quotes[q][i].time.GetAbsSecs();
		}
		for(int i=0;i<twitter[q].Len();i++)
		{
			integratedTimestamps[quotes[q].Len()+i] = twitter[q][i].GetAbsSecs();
		}
		sort(integratedTimestamps,integratedTimestamps+leng);
		int medIndex = (leng-1)/2;
		int integratedMedianValue = integratedTimestamps[medIndex];
		delete[] integratedTimestamps;

		TIntV memeCascade;
		for(int i=0;i<quotes[q].Len();i++)
		{
			memeCascade.Add((int)quotes[q][i].time.GetAbsSecs() - integratedMedianValue);
		}
		TIntV twitterCascade;
		for(int i=0;i<twitter[q].Len();i++)
		{
			twitterCascade.Add((int)twitter[q][i].GetAbsSecs() - integratedMedianValue);
		}
		double beginShifted = period * (0.5 + floor((end - begin) / period)) * -1.0;

		double* memeVol = Tools::calculateHistOfCascade(memeCascade,beginShifted,period,true);
		memeCascade.Clr();
		for(int i=0;i<lengt;i++)
		{
			memeVolumes[i] += memeVol[i];
		}
		delete[] memeVol;

		double* twitterVol = Tools::calculateHistOfCascade(twitterCascade,beginShifted,period,true);
		twitterCascade.Clr();
		for(int i=0;i<lengt;i++)
		{
			twitterVolumes[i] += twitterVol[i];
		}
		delete[] twitterVol;
	}

	// Finding max indices
	double maxm = 0;
	int memeMaxId = -1;
	for(int i=0;i<lengt;i++)
	{
		if(maxm < memeVolumes[i])
		{
			maxm = memeVolumes[i];
			memeMaxId = i;
		}
	}
	double maxt = 0;
	int twMaxId = -1;
	for(int i=0;i<lengt;i++)
	{
		if(maxt < twitterVolumes[i])
		{
			maxt = twitterVolumes[i];
			twMaxId = i;
		}
	}
	///cout << "\n\nMemeMaxId: " << memeMaxId << ", value: " << maxm << endl;
	///cout << "TwMaxId: " << twMaxId << ", value: " << maxt << endl << endl;

	if(twMaxId == memeMaxId)
	{
		return false;
	}

	cout << "\n\nMemeMaxId: " << memeMaxId << ", value: " << maxm << endl;
	cout << "TwMaxId: " << twMaxId << ", value: " << maxt << endl << endl;

	printf("\n\nPlotting ...\n");
	TFltPrV memeVolumes4Plot;
	TFltPrV twitterVolumes4Plot;
	IAssert(center-myrange>=0 && center+myrange<lengt);
	for(int i=center-myrange;i<=center+myrange;i++)
//	for(int i=0;i<lengt;i++)
	{
		memeVolumes[i] /= quotes.Len();
		twitterVolumes[i] /= quotes.Len();
		TFltPr elem1;
		elem1.Val1 = -center + i;
		elem1.Val2 = memeVolumes[i];
//		cout << "memeVolumes[" << i << "]: " << memeVolumes[i] << endl;
		memeVolumes4Plot.Add(elem1);

		TFltPr elem2;
		elem2.Val1 = -center + i;
		elem2.Val2 = twitterVolumes[i];
//		cout << "twitterVolumes[" << i << "]: " << twitterVolumes[i] << endl;
		twitterVolumes4Plot.Add(elem2);
	}
	delete[] memeVolumes;
	delete[] twitterVolumes;

	// Plotting
//	TGnuPlot plot1;
//	plot1.SetXYLabel("Time[hours]", "Volume");
//	plot1.AddPlot(memeVolumes4Plot,gpwLinesPoints,"Memes");
//	plot1.AddPlot(twitterVolumes4Plot,gpwLinesPoints,"Twitter");
//	plot1.SetDataPlotFNm(TStr::Fmt("MyResults/%s-Original.tab",name), TStr::Fmt("MyResults/%s-Original.plt",name));
//	plot1.SaveEps(TStr::Fmt("MyResults/%s-Original.eps",name));

	TGnuPlot plot2;
	plot2.SetXYLabel(TStr::Fmt("Time[%s]",periodstr), "Volume");
	plot2.AddPlot(memeVolumes4Plot,gpwPoints,"Memes");
	plot2.AddPlot(twitterVolumes4Plot,gpwPoints,"Twitter");
	plot2.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
	plot2.SaveEps(TStr::Fmt("MyResults/%s.eps",name),true);

	printf("Plot %s is done.\n",name);
	return true;
}
// DELETE IT



int main(int argc, char* argv[])
{
//	// test with toy example with small numbers
//	cout << "TESTING:\n\n\n";
//	THash< TStr , CascadeElementV > qq1;
//	THash< TUInt , TSecTmV > tt1;
//	TStr emp("55");
//	CascadeElementV v;
//	TSecTm t1(uint(3));
//	TSecTm t2(uint(5));
//	TSecTm t3(uint(6));
//	TSecTm t4(uint(7));
//	TSecTm t5(uint(7));
//	TSecTm t6(uint(8));
//	TSecTm t7(uint(11));
//	v.Add(CascadeElement(t1));
//	v.Add(CascadeElement(t2));
//	v.Add(CascadeElement(t3));
//	v.Add(CascadeElement(t4));
//	v.Add(CascadeElement(t5));
//	v.Add(CascadeElement(t6));
//	v.Add(CascadeElement(t7));
//	qq1.AddDat(emp,v);
//
//	TSecTmV v2;
//	v2.Add(TSecTm(uint(2)));
//	v2.Add(TSecTm(uint(4)));
//	v2.Add(TSecTm(uint(6)));
//	v2.Add(TSecTm(uint(8)));
//	tt1.AddDat(0,v2);
//
//	uint per = 4;
//	char pst[] = "4 unit";
//
//	Tools::plotTwoIndividuallyShift(qq1,tt1,per,pst,"MY-TOY-TEST");
//	Tools::plotCCDFStartMedianEnd(qq1,tt1,"MemesTOY","Memes");
//	Tools::plotTwoHistShift(qq1,tt1,per,pst,"HistMedian",MEDIAN,"Memes","Twitter");
//	return 0;
//	//// ----------------------------------------

//	// test with toy example with small numbers
//	THash< TStr , CascadeElementV > qq1;
//	THash< TUInt , TSecTmV > tt1;
//	TStr emp("1");
//	CascadeElementV v;
//
//	TSecTm t1(uint(2));
//	TSecTm t2(uint(5));
//	TSecTm t3(uint(8));
//	TSecTm t4(uint(9));
//	v.Add(CascadeElement(t1));
//	v.Add(CascadeElement(t2));
//	v.Add(CascadeElement(t3));
//	v.Add(CascadeElement(t4));
//	qq1.AddDat(emp,v);
//
//	TStr emp2("2");
//	CascadeElementV v2;
//	TSecTm t5(uint(1));
//	TSecTm t6(uint(10));
//	v2.Add(CascadeElement(t5));
//	v2.Add(CascadeElement(t6));
//	qq1.AddDat(emp2,v2);
//
//
//	TSecTmV vv2;
//	vv2.Add(TSecTm(uint(7)));
//	vv2.Add(TSecTm(uint(8)));
//	tt1.AddDat(2,vv2);
//
//	TSecTmV vv;
//	vv.Add(TSecTm(uint(1)));
//	vv.Add(TSecTm(uint(3)));
//	vv.Add(TSecTm(uint(7)));
//	tt1.AddDat(1,vv);
//
//	uint per = 1;
//	char pst[] = "1 unit";
//
//	Tools::plotTwoIndividuallyShift(qq1,tt1,per,pst,"MY-TOY-TEST");
//	return 0;

//	// test with real toy example   // --->>> FULLY TESTED
//	THash< TStr , CascadeElementV > qq1;
//	THash< TUInt , TSecTmV > tt1;
//	TStr emp("");
//	CascadeElementV v;
//
//	TSecTm t1(2008,9,5,1,10,0);
//	TSecTm t2(2008,10,1,11,2,0);
//	TSecTm t3(2008,10,2,11,1,0);
//	TSecTm t4(2008,10,4,11,0,0);
//	v.Add(CascadeElement(t1));
//	v.Add(CascadeElement(t2));
//	v.Add(CascadeElement(t3));
//	v.Add(CascadeElement(t4));
//	qq1.AddDat(emp,v);
//
//	TSecTmV vv;
//
//	vv.Add(TSecTm(2008,10,3,10,0,0));
//	vv.Add(TSecTm(2008,10,20,10,0,0));
//	vv.Add(TSecTm(2008,11,28,10,0,0));
//	tt1.AddDat(1,vv);
//	uint per = 24 * 3600;
//	char pst[] = "days";
//	Tools::plotTwoHistShift(qq1,tt1,per,pst,"TEST-HIST-MEDIAN",MEDIAN,"Memes","Twitter");
//	Tools::plotTwoHistShift(qq1,tt1,per,pst,"TEST-HIST-MAX",MAX,"Memes","Twitter");
//	Tools::plotTwoIndividuallyShift(qq1,tt1,per,pst,"TEST-INDIV");
//	return 0;
//	//// ----------------------------------------

	TExeTm ExeTm;
	uint period = 3600;   // hour
	char* periodstr = TStr("hour").GetCStr();
	printf("((( START individually Plot BOTH Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nPlotting Individually Memes-Twitter Cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// URLS
		THash< TStr , CascadeElementV > quotes1 = Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar");    // QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS
		THash< TUInt , TSecTmV > twitter1 = Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");     // CascadesFullUrlsOnTwitterData_FINALFILTERED

		// CONTENTS
		THash< TStr , CascadeElementV > quotes2 = Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar");    // QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents
		THash< TUInt , TSecTmV > twitter2 = Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");    // CascadesOnTwitterData_FINALFILTERED

//		// News vs Blogs
//		THash< TStr , CascadeElementV > q1 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_NEWS.rar");
//		THash< TStr , CascadeElementV > q2 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_NEWS.rar");
//
//		THash< TStr , CascadeElementV > q3 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_BLOGS.rar");
//		THash< TStr , CascadeElementV > q4 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_BLOGS.rar");
//
//		THash< TStr , CascadeElementV > q5 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTS.rar");
//		THash< TStr , CascadeElementV > q6 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTS.rar");
//
//		THash< TStr , CascadeElementV > q7 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTSNEWS.rar");
//		THash< TStr , CascadeElementV > q8 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTSNEWS.rar");
//
//		THash< TStr , CascadeElementV > q9 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS_FIRSTSBLOGS.rar");
//		THash< TStr , CascadeElementV > q10 = Tools::loadQuotes("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents_FIRSTSBLOGS.rar");


//		/////
//		// URLS
//		THash< TStr , CascadeElementV > quotes1; // = Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar");    // QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS
//		quotes1.AddDat(Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar").GetKey(0),Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar")[0]);    // CascadesOnTwitterData_FINALFILTERED
//		THash< TUInt , TSecTmV > twitter1; // = Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");     // CascadesFullUrlsOnTwitterData_FINALFILTERED
//		twitter1.AddDat(Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_HAVINGBOTH.rar").GetKey(0),Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesFullUrlsOnTwitterData_FINALFILTERED_HAVINGBOTH.rar")[0]);    // CascadesOnTwitterData_FINALFILTERED
//
//
//		// CONTENTS
//		THash< TStr , CascadeElementV > quotes2; // = Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar");    // QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents
//		quotes2.AddDat(Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar").GetKey(0),Tools::loadQuotes("/NS/twitter-5/work/oaskaris/DATA/QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_HAVINGBOTH.rar")[0]);    // CascadesOnTwitterData_FINALFILTERED
//		THash< TUInt , TSecTmV > twitter2;   // = Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED_HAVINGBOTH.rar");
//		twitter2.AddDat(Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED_HAVINGBOTH.rar").GetKey(0),Tools::loadTwitter("/NS/twitter-5/work/oaskaris/DATA/CascadesOnTwitterData_FINALFILTERED_HAVINGBOTH.rar")[0]);    // CascadesOnTwitterData_FINALFILTERED
//		/////


		// Plotting
		printf("\n\n\nGoing for plotting ...\n");
		int status = system("mkdir -p MyResults/Individual/Urls/; mkdir -p MyResults/Individual/Contents/");


		period = 100;
		while(!myPlotTwoIndividuallyShift(quotes2,twitter2,period,periodstr,"Individual/Contents/IndividualContents_NormWithMentions"))
		{
			printf("%d\n",period);
			period++;
		}
		cout << "\n\nDDDDDOOOONNNNEEE" << endl;



		///myPlotTwoIndividuallyShift(quotes1,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_NormWithMentions");
		///myPlotTwoIndividuallyShift(quotes2,twitter2,period,periodstr,"Individual/Contents/IndividualContents_NormWithMentions");
		///Tools::plotCCDFStartMedianEnd(quotes2, twitter2, "MemesContentsBOTH", "MemesBOTH");

//		Tools::plotTwoIndividuallyShift(q1,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_NEWS_NormWithMentions");
//		Tools::plotTwoIndividuallyShift(q2,twitter2,period,periodstr,"Individual/Contents/IndividualContents_NEWS_NormWithMentions");
//		Tools::plotTwoIndividuallyShift(q3,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_BLOGS_NormWithMentions");
//		Tools::plotTwoIndividuallyShift(q4,twitter2,period,periodstr,"Individual/Contents/IndividualContents_BLOGS_NormWithMentions");
//		Tools::plotTwoIndividuallyShift(q5,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_FIRSTS_NormWithMentions");
//		Tools::plotTwoIndividuallyShift(q6,twitter2,period,periodstr,"Individual/Contents/IndividualContents_FIRSTS_NormWithMentions");
//		Tools::plotTwoIndividuallyShift(q7,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_FIRSTSNEWS_NormWithMentions");
//		Tools::plotTwoIndividuallyShift(q8,twitter2,period,periodstr,"Individual/Contents/IndividualContents_FIRSTSNEWS_NormWithMentions");
//		Tools::plotTwoIndividuallyShift(q9,twitter1,period,periodstr,"Individual/Urls/IndividualUrls_FIRSTSBLOGS_NormWithMentions");
//		Tools::plotTwoIndividuallyShift(q10,twitter2,period,periodstr,"Individual/Contents/IndividualContents_FIRSTSBLOGS_NormWithMentions");


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
