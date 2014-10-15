/*
 * Tools.h
 *
 *  Created on: May 1, 2014
 *      Author: omid55
 */

#ifndef _TOOLS_H
#define _TOOLS_H

#include "stdafx.h"
#include "CascadeElement.h"

enum Mode
{
	MEDIAN,
	MAX
};

enum CorrelationType
{
	Pearson,
	Spearman
};

class SortItem
{
private:
	int index;
	double value;

public:
	SortItem(int index, double value);
	bool operator <(const SortItem& o) const;
	int getIndex() const;
};

class Tools
{
public:
	static int getTheBinIndex(double x, double rbegin, uint rperiod);
	static double* calculateHistOfCascade(TSecTmV& cascade, double rbegin, uint rperiod, bool normalized);
	static double* calculateHistOfCascade(TIntV& cascade, double rbegin, uint rperiod, bool normalized);
	static double* calculateHistOfCascade(CascadeElementV& cascade, double rbegin, uint rperiod, bool normalized);
	static int getMaxIndex(double* d,int len);
//	static int getMedianIndex(double* d,int len);
	static TPair<TInt,TInt> findRangeWithValues(double* d,int len);
	static void separateTimestepsOfQuotesInBlogsNews(THash< TStr,CascadeElementV >& quotes, THash<TStr,TUInt>& newsMedia, THash<TChA,TUInt>& posts, THash<TStr,CascadeElementV>& newsQuotesOutput, THash<TStr,CascadeElementV>& blogsQuotesOutput);
	static void removeOtherTimestepsOfQuotesWithSameDomain(THash<TStr,CascadeElementV>& quotes, THash<TChA,TUInt>& posts, THash<TStr,CascadeElementV>& outputQuotes);
	static int countNoneZeros(double* v, int len);

	static TStr exec(TStr cmd);
	static bool getRealUrl(TChA& url, TChAV& res);
	static TChA getBase(TChA& address);
	static TChA getUrl(TChA& address,TChA& base);
	static bool fileExists(TStr filepath);
	static TChAV getAllUrlsWithPrefix(TStr& text,char* prefix);
	static TChAV getAllUrls(TStr& text);

	// Plotting methods
	// CCDF
private:
	static void myPrivatePlotCCDF_PrintPosNeg(double* arr, int leng, char* name, char* xlabel, bool withCommand=true);
	static TFltPrV getCCDFYAxis(double* arr1, int leng1);

public:
	static void plotSimpleCCDF(double* arr1, int leng1, double* arr2, int leng2, char* legend1, char* legend2, char* xlabel);
	static void plotCCDFPairArray(TFltPrV data, char* name, char* legendname1, char* legendname2);
	static double computeCorrelation(TFltPrV data, CorrelationType type);
	static void plotTwoIndividuallyShiftProportionVolume(THash<TStr,CascadeElementV>& quotes, THash<TUInt,TSecTmV>& twitter, int period, char* periodstr, char* name, char* which, int index);
	static void plotScatter(TFltPrV plotdata, char* name, char* legendname1, char* legendname2);
	static void plotCCDFStartMedianEnd(THash<TStr,CascadeElementV> quotes, THash<TUInt,TSecTmV> twitter, char* name, char* legendname1);
	static void plotCCDFStartMedianEnd(THash<TStr,CascadeElementV> q1, THash<TStr,CascadeElementV> q2, char* name, char* legendname1, char* legendname2);

	// Individually shift centralization
	static void plotOneIndividuallyShift(THash<TStr,CascadeElementV>& quotes, char* name, int period, char* periodstr, int DesiredCascadesCount=0);
	static void plotTwoIndividuallyShift(THash<TStr,CascadeElementV>& quotes, THash<TUInt,TSecTmV>& twitter, int period, char* periodstr, char* name);
	static void plotTwoIndividuallyShift(THash<TStr,CascadeElementV>& q1, THash<TStr,CascadeElementV>& q2, int period, char* periodstr, char* name, char* s1, char* s2, int DesiredCascadesCount=0);
	static void plotTwoIndividuallyShiftLimited(THash<TStr,CascadeElementV>& quotes, THash<TUInt,TSecTmV>& twitter, int period, char* periodstr, char* name, int limitedLeng);

	// Hist shift centralization
	static void plotOneHistShift(THash<TStr,CascadeElementV>& quotes, char* name, int period, char* periodstr, Mode mode, int DesiredCascadesCount=0);
	static void plotTwoHistShift(THash<TStr,CascadeElementV>& quotes, THash<TUInt,TSecTmV>& twitter, int period, char* periodstr, char* name, Mode mode, char* s1, char* s2);
	static void plotTwoHistShift(THash<TStr,CascadeElementV>& q1, THash<TStr,CascadeElementV>& q2, int period, char* periodstr, char* name, Mode mode, char* s1, char* s2);

	static THash<TStr,CascadeElementV> loadQuotes(char* name);
	static THash<TUInt,TSecTmV> loadTwitter(char* name);

	// TEST
	// TEST
	static void printTwitterHasSoonerStart(THash<TStr,CascadeElementV> quotes, THash<TUInt,TSecTmV> twitter, int limit);
	// TEST
	// TEST
};

#endif /* TOOLS_H_ */
