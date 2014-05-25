/*
 * Tools.h
 *
 *  Created on: May 1, 2014
 *      Author: omid55
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include "stdafx.h"
#include "CascadeElement.h"

enum Mode
{
	MEDIAN,
	MAX
};

class Tools
{
public:
	static double* calculateHistOfCascade(TIntV& cascade, int rbegin, uint rperiod, int length, bool normalized);
	static double* calculateHistOfCascade(TSecTmV& cascade, int rbegin, uint rperiod, int length, bool normalized);
	static double* calculateHistOfCascade(CascadeElementV& cascade, int rbegin, uint rperiod, int length, bool normalized);
	static int getMaxIndex(double* d,int len);
	static int getMedianIndex(double* d,int len);
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
	static void myPrivatePlotCCDF_PrintPosNeg(double* arr, int leng, char* name, char* xlabel);
public:
	static void plotCCDFStartMedianEnd(THash<TStr,CascadeElementV> quotes, THash<TUInt,TSecTmV> twitter, char* name);

	// Individually shift centralization
	static void plotOneIndividuallyShift(THash<TStr,CascadeElementV>& quotes, char* name, uint period, char* periodstr, int DesiredCascadesCount=0);
	static void plotTwoIndividuallyShift(THash< TStr,CascadeElementV >& quotes, THash<TUInt,TSecTmV>& twitter, uint period, char* periodstr, char* name);
	static void plotTwoIndividuallyShift(THash<TStr,CascadeElementV>& q1, THash<TStr,CascadeElementV>& q2, uint period, char* periodstr, char* name, char* s1, char* s2);

	// Hist shift centralization
	static void plotOneHistShift(THash<TStr,CascadeElementV>& quotes, char* name, uint period, char* periodstr, Mode mode, int DesiredCascadesCount=0);
	static void plotTwoHistShift(THash<TStr,CascadeElementV>& quotes, THash<TUInt,TSecTmV>& twitter, uint period, char* periodstr, char* name, Mode mode, char* s1, char* s2);
	static void plotTwoHistShift(THash<TStr,CascadeElementV>& q1, THash<TStr,CascadeElementV>& q2, uint period, char* periodstr, char* name, Mode mode, char* s1, char* s2);

};

#endif /* TOOLS_H_ */
