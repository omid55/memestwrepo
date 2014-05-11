// Omid55

/*
 * add_novisited_real_urls.cpp
 *
 *  Created on: Jan 5, 2014
 *      Author: oaskaris
 */

//Omid55
#include "stdafx.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstdlib>

int SAVELEN=1000;

TVec<TwitterUrl> rawUrls;
TVec<TwitterUrl> fullUrls;    // for each id fullUrls which it contains
int ct = 0;

void SaveAll()
{
	printf("\n<<< REAL URLS SAVING STARTS (PLEASE BE PATIENT!!!) >>> .......\n");
	TZipOut zipData(TStr::Fmt("FULLTwitterRealUrlsFILLED%d.rar",ct));
	fullUrls.Save(zipData);
	printf("The size of Urls was: %d\n",fullUrls.Len());
	fullUrls.Clr();
	printf("\n<<<<<<<< SAVING part %d is DONE >>>>>>>>\n\n",ct);
}


int main(int argc, char* argv[])
{
//	TChA tmp("bit.ly/1eE6lXL");
//	TChAV resu;
//	bool found = getRealUrl(tmp,resu);
//	if(found)
//	{
//		for(int i=0;i<resu.Len();i++)
//		{
//			printf("Result: %s\n",resu[i].CStr());
//		}
//	}
//	return 0;
//

	TChAV result;
	bool found;
	TExeTm ExeTm;

	if(argc > 1)
	{
		ct = atoi(argv[1]);
	}

	if(ct>=8 && SAVELEN!=100)
	{
		printf("\nSAVELEN SHOULD BE 100\n\n\n");
		return 1;
	}

	printf(":::::::: Packing all and no visited Real Urls of Tweets ::::::::\n");

	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nFinding Real Urls from Raw ones, (we do not save shortenned ones) build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		TZipIn ZquotesIn(TStr::Fmt("TwitterRAWUrlsData%d.rar",ct));
		rawUrls.Load(ZquotesIn);
		printf("TwitterRAWUrlsData%d loading done, it contains %d quotes.\n",ct,rawUrls.Len());

		TZipIn ZqIn(TStr::Fmt("FULLTwitterRealUrlsData%d.rar",ct));
		fullUrls.Load(ZqIn);
		printf("TwitterRAWUrlsData%d loading done, it contains %d quotes.\n",ct,fullUrls.Len());

		printf("CURL starts ...\n\n");
		CURL *curl = curl_easy_init();
		char *res = NULL;
		if (!curl)
		{
			printf("\nERROR in Initiallizing Curl\n\n");
			throw exception();
		}

		fstream f(TStr::Fmt("NoVisited%d.txt",ct).CStr(),ios::in);
		int num = 0;
		while(!f.eof())
		{
			f>>num;
			printf("Num: %d\n",num);
			for(int j=0;j<SAVELEN;j++)
			{
				TChAV v;
				for(int k=0;k<rawUrls[num+j].urlsV.Len();k++)
				{
					TChA ur = rawUrls[num+j].urlsV[k];
					TChA base = Tools::getBase(ur);
					if(base == "tinyurl.com" || base == "ow.ly" || base == "bit.ly" || base == "su.pr" || base == "adf.ly" || base == "twurl.nl" || base == "snurl.com" || base == "cli.gs" || base == "is.gd" || base == "doiop.com" || base == "goo.gl" || base == "ustre.am")
					{
						found = Tools::getRealUrl(ur,result);
						//curl_easy_cleanup(curl);
						if(found)
						{
							v.AddV(result);
						}
					}
					v.Add(ur);
				}
				if(v.Len()!=0)   // this means if v has a value
				{
					TwitterUrl tt(rawUrls[num+j].time,v);
					fullUrls.Add(tt);
				}
			}
		}
		SaveAll();

		printf("\n\n ---=== EVERYTHING DONE ===---\n");
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
