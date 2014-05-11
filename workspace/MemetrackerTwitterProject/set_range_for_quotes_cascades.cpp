// Omid55
/*
 * set_range_for_quotes_cascades.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: omid55
 */

// Omid55

#include "stdafx.h"

THash< TStr , CascadeElementV > quotes;


int main(int argc, char* argv[])
{
//	TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_SUBSETTED.rar");      //("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");
//	quotes.Load(ZquotesIn);
//	printf("Loaded QuotesPreprocessedData_NIFTY has instances: %d\n\n\n",quotes.Len());
//
//	THash< TStr , CascadeElementV  > quotesFixed;
//	TZipIn ZIn("QuotesPreprocessedData_NIFTY_SUBSETTED_RANGEFIXED.rar");      //("/agbs/cluster/oaskaris/Data_Preparing_Codes/RESULTS/QuotesPreprocessedData_NIFTY.rar");
//	quotesFixed.Load(ZIn);
//	printf("Loaded QuotesPreprocessedData_NIFTY_SUBSETTED_RANGEFIXED has instances: %d\n\n\n",quotesFixed.Len());
//
//	int cnt1 = 0,cnt2=0;
//	for(int l=0;l<quotes.Len();l++)			cnt1 += quotes[l].Len();
//	for(int l=0;l<quotesFixed.Len();l++)	cnt2 += quotesFixed[l].Len();
//	cout << "Cnt1: " << cnt1 << " , Cnt2: " << cnt2 << endl;
//	return 0;


	uint rbegin = TSecTm(2008,7,31,0,0,0).GetAbsSecs();
	uint rend = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
	TExeTm ExeTm;
	int i,j;

	printf("((( Starting Set Range For Quotes Cascades CODE )))\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nSet Range for quotes cascades. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		TZipIn ZquotesIn("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY.rar");
		//TZipIn ZquotesIn("QuotesPreprocessedData_NIFTY_SUBSETTED.rar");
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY has instances: %d\n\n\n",quotes.Len());

		THash< TStr , CascadeElementV > finalQuotes;
		for(i=0;i<quotes.Len();i++)
		{
			CascadeElementV vals;
			for(j=0;j<quotes[i].Len();j++)
			{
				uint v = quotes[i][j].time.GetAbsSecs();
				if(v >= rbegin && v <= rend)
				{
					vals.Add(quotes[i][j]);
				}
			}
			finalQuotes.AddDat(quotes.GetKey(i),vals);
		}
		TZipOut ZquotesOut("QuotesPreprocessedData_NIFTY_RANGEFIXED.rar");
		finalQuotes.Save(ZquotesOut);
		printf("Loaded QuotesPreprocessedData_NIFTY_RANGEFIXED has instances: %d\n\n\n",finalQuotes.Len());
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

