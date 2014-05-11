//Omid55

/*
 * splitup_quotes.cpp
 *
 *  Created on: Nov 12, 2013
 *      Author: oaskaris
 */

//Omid55
#include "stdafx.h"
#include "snap/memes.h"

inline TStr getWebsite(TStr fulladdress)
{
	TStr left,right,tmp,res;
	if(fulladdress.SearchStr(TStr("http"),0)>=0)
	{
		fulladdress.SplitOnStr(left,TStr("//"),right);
		right.SplitOnCh(res,'/',tmp);
	}
	else
	{
		fulladdress.SplitOnCh(res,'/',tmp);
	}
	return res;
}

THash< TStr , CascadeElementV > quotes;  // for each quote what is the cascade times in memetracker dataset

THash< TStr , TUInt > quotesContent;
TVec< CascadeElementV > quotesCascades;
unsigned int quotesContentCounter = 0;

void SaveAll()
{
	TZipOut z1("QuotesContentData.rar");
	quotesContent.Save(z1);
	printf("The size of quotesContent was: %d\n",quotesContent.Len());

	TZipOut z2("QuotesCascadesData.rar");
	quotesCascades.Save(z2);
	printf("The size of quotesCascades was: %d\n",quotesCascades.Len());

	printf("\n<<<<< SAVING DONE >>>>>\n\n");
}


int main(int argc, char* argv[])
{
	printf("Starting splitting up quotes code ...\n");

	TExeTm ExeTm;
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nCreating the volumes of the quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		TZipIn ZquotesIn("QuotesData.rar");
		quotes.Load(ZquotesIn);
		printf("Loaded Quotes have instances: %d\n\n\n",quotes.Len());

		for(unsigned int i=0;i<quotes.Len();i++)
		{
			quotesContent.AddDat(quotes.GetKey(i),quotesContentCounter++);
			quotesCascades.Add(quotes[i]);
		}

		SaveAll();
	}
	catch(exception& ex)
	{
		SaveAll();
		printf("\nError1 happened, it was: %s\n\n",ex.what());
	}
	catch(TPt<TExcept>& ex)
	{
		SaveAll();
		printf("\nError2 happened: %s\n\n",ex[0].GetStr().CStr());
	}

	printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
	return 0;
}
