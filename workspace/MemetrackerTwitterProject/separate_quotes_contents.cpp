// Omid55
/*
 * separate_quotes_contents.cpp
 *
 *  Created on: Feb 11, 2014
 *      Author: Omid
 */

#include "stdafx.h"

THash< TStr , CascadeElementV > quotes;
#define LENGTH 10   // CHANGE TO 100
int main(int argc, char* argv[])
{
	int i,num=0;
	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nFinding the cascades of the desired quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	TExeTm ExeTm;
	try
	{
		TZipIn ZquotesIn("QuotesCascadesOverTwitterByUrls/NIFTY/QuotesPreprocessedData_NIFTY.rar");
		quotes.Load(ZquotesIn);
		printf("AllQuotes loading done, it contains %d quotes.\n",quotes.Len());

		THash<TStr,TInt> quotesContentsSeparated;    // name with index
		for(i=0;i<quotes.Len();i++)
		{
			quotesContentsSeparated.AddDat(quotes.GetKey(i),i);
			if(quotesContentsSeparated.Len()==LENGTH || i == quotes.Len()-1)
			{
				TStr newname = TStr::Fmt("QuotesData/Q%d.rar",num++);
				TZipOut ZquotesOut(newname);
				quotesContentsSeparated.Save(ZquotesOut);
				printf("%s includes %d quotes.\n",newname.CStr(),quotesContentsSeparated.Len());
				quotesContentsSeparated.Clr();
			}
		}
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

