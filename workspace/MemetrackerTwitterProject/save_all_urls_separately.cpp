//Omid55
/*
 * save_all_urls_separately.cpp
 *
 *  Created on: Nov 16, 2013
 *      Author: oaskaris
 */

//Omid55
#include "stdafx.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstdlib>
#include <cmath>

TVec<TwitterUrl> rawUrls;    // for each id rawUrls which it contains
TVec<TwitterUrl> allUrls;    // for each id allUrls which it contains

// THE RESULT IS GOING TO BE:
//RAWS-> Items:  390948593, Urls: 400674301
//REALS-> Items: 390948593, Urls: 638991861


int main(int argc, char* argv[])
{
//	long long real = 0;
//	int leng = 10;
//	int ii,jj,kk;
//	int cnnt = 0;
//	TVec<TwitterUrl> ur;
//	for(ii=1;ii<=leng;ii++)
//	{
//		TZipIn zin1(TStr::Fmt("/NS/twitter-5/work/oaskaris/FINALFULLS/FULLTwitterAllUrlsData%d.rar",ii).CStr());
//		ur.Clr();
//		ur.Load(zin1);
//		for(jj=0;jj<ur.Len();jj++)
//		{
//			real++;
//			for(kk=0;kk<ur[jj].urlsV.Len()-1;kk++)
//			{
//				if(ur[jj].urlsV[kk+1].Len()==0)
//				{
//					continue;
//				}
//
//				if (ur[jj].urlsV[kk].SearchStr(ur[jj].urlsV[kk+1]) == -1)
//				{
//					real++;
//				}
//			}
//		}
//	}
//	ur.Clr();
//	cout << "\nNEW REAL COUNT: " << real << endl;
//	return 0;

//	cout << "Starting ..." << endl;
//	int leng = 10;
//	int ii,jj;
//	long items1 = 0;
//	long long urls1 = 0;
//	long items2 = 0;
//	long long urls2 = 0;
//	TVec<TwitterUrl> rw;
//	for(ii=1;ii<=leng;ii++)
//	{
//		TZipIn zin1(TStr::Fmt("/NS/twitter-5/work/oaskaris/FINALRAWS/TwitterRAWUrlz%d.rar",ii).CStr());
//		rw.Clr();
//		rw.Load(zin1);
//		items1 += rw.Len();
//		for(jj=0;jj<rw.Len();jj++)
//		{
//			urls1 += rw[jj].urlsV.Len();
//		}
//	}
//	rw.Clr();
//
//	TVec<TwitterUrl> re;
//	for(ii=1;ii<=leng;ii++)
//	{
//		TZipIn zin2(TStr::Fmt("/NS/twitter-5/work/oaskaris/FINALFULLS/FULLTwitterAllUrlsData%d.rar",ii).CStr());
//		re.Clr();
//		re.Load(zin2);
//		items2 += re.Len();
//		for(jj=0;jj<re.Len();jj++)
//		{
//			urls2 += re[jj].urlsV.Len();
//		}
//	}
//	re.Clr();
//
//	cout << "\n\n\n\nRAWS-> Items: " << items1 << ", Urls: " << urls1 << endl;
//	cout << "REALS-> Items: " << items2 << ", Urls: " << urls2 << endl;
//	cout << "New Urls Count: " << (urls2-urls1) << endl;
//
//	return 0;

//	TChAV rs;
//	TChA test(argv[1]);
//
//	int ix = test.SearchCh('|',0);
//	if(ix != -1)
//	{
//		test = test.GetSubStr(0,ix-1);
//	}
//	// deleting ;
//	ix = test.SearchCh(';',0);
//	while(ix != -1)
//	{
//		test.Del(ix);
//		ix = test.SearchCh(';',ix);
//	}
//
//	bool fo = getRealUrl(test,rs);
//	if(fo)
//	{
//		for(int r=0;r<rs.Len();r++)
//		{
//			printf("Real: %s\n",rs[r].CStr());
//		}
//	}
//	return 0;


	// JUST FOR CHECKING
	int NUM = atoi(argv[1]);
	int LEN = atoi(argv[2]);
	TZipIn zin1(TStr::Fmt("/NS/twitter-5/work/oaskaris/FINALRAWS/TwitterRAWUrlz%d.rar",NUM).CStr());
	TZipIn zin2(TStr::Fmt("/NS/twitter-5/work/oaskaris/FINALFULLS/FULLTwitterAllUrlsData%d.rar",NUM).CStr());
	rawUrls.Load(zin1);
	allUrls.Load(zin2);
	cout << "RawLen: " << rawUrls.Len() << ", RealLen: " << allUrls.Len() << endl;
	for(int ii=0;ii<LEN;ii++)
	{
		if(rawUrls[ii].time != allUrls[ii].time)
		{
			cout << "Raw["<< ii <<"]: " << rawUrls[ii].time.GetYmdTmStr().CStr()<<", Real["<< ii <<"]: " << allUrls[ii].time.GetYmdTmStr().CStr() << endl;
		}
	}
	cout << "\n\n\nDone" << endl;
	return 0;
	// JUST FOR CHECKING



	TExeTm ExeTm;
	TChAV result;
	bool found;
	TChA s1(";yes");
	TChA s2(";vi");
	TChA s3(";vim");
	TChA s4(";script");
	int i,startIndex,j,idx,ct,indx,end,LENGTH;
	if(argc == 4)
	{
		ct = atoi(argv[1]);
		LENGTH = atoi(argv[2]);
		startIndex = atoi(argv[3]);
		printf("Configuration: {ct=%d,LENGTH=%d,startIndex=%d}\n\n",ct,LENGTH,startIndex);

		indx = startIndex * LENGTH;
		end = indx + LENGTH;
	}
	else if(argc == 5)
	{
		ct = atoi(argv[1]);
		LENGTH = atoi(argv[2]);   // we don't need it here but just for having a difference with the last option we placed it here
		indx = atoi(argv[3]);
		end = atoi(argv[4]);
		printf("Configuration: {ct=%d,LENGTH=%d,start=%d,end=%d}\n\n",ct,LENGTH,indx,end);
	}
	else
	{
		printf("YOU SHOULD SET THE INDICES...\n\n");
		return 1;
	}

	printf(":::::::: Finding Real Urls of Tweets (GOOD OK) ::::::::\n");
	Env = TEnv(argc, argv, TNotify::StdNotify);
	Env.PrepArgs(TStr::Fmt("\nFinding Real Urls from Raw Ones and Save All, build %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
	try
	{
		while(indx < end)
		{
			TStr rawFname = TStr::Fmt("Raw%d/RawUrls%d.rar",ct,indx);
			TStr resultFname = TStr::Fmt("Pack%d/AllUrls%d.rar",ct,indx++);
			rawUrls.Clr();
			allUrls.Clr();

			if(Tools::fileExists(resultFname))
			{
				if(Tools::fileExists(rawFname))
				{
					// removing the raw file
					int resp = system(TStr::Fmt("rm %s",rawFname.CStr()).CStr());
					printf("responce: %d\n",resp);
				}
			}
			else
			{
				if(Tools::fileExists(rawFname))
				{
					TZipIn ZquotesIn(rawFname);
					rawUrls.Load(ZquotesIn);
					printf("%s loading done, it contains %d quotes.\n",rawFname.CStr(),rawUrls.Len());

					for(i=0;i<rawUrls.Len();i++)
					{
						if(i%1000 == 0)
						{
							double percent = 100*(double)i/rawUrls.Len();
							printf("%f percent is processed.\n",percent);
						}

						TChAV v;
						for(j=0;j<rawUrls[i].urlsV.Len();j++)
						{
							// Removing inappropriate forms
							TChA ur = rawUrls[i].urlsV[j];
							idx = ur.SearchCh('|',0);
							if(idx != -1)
							{
								ur = ur.GetSubStr(0,idx-1);
							}
							idx = ur.SearchStr(s1,0);
							if(idx != -1)
							{
								ur = ur.GetSubStr(0,idx-1);
							}
							idx = ur.SearchStr(s2,0);
							if(idx != -1)
							{
								ur = ur.GetSubStr(0,idx-1);
							}
							idx = ur.SearchStr(s3,0);
							if(idx != -1)
							{
								ur = ur.GetSubStr(0,idx-1);
							}
							idx = ur.SearchStr(s4,0);
							if(idx != -1)
							{
								ur = ur.GetSubStr(0,idx-1);
							}

							v.Add(ur);
							TChA base = Tools::getBase(ur);
							if(base == "tinyurl.com" || base == "ow.ly" || base == "bit.ly" || base == "su.pr" || base == "adf.ly" || base == "twurl.nl" || base == "snurl.com" || base == "cli.gs" || base == "is.gd" || base == "doiop.com" || base == "goo.gl" || base == "ustre.am")
							{
//								printf("Raw: %s\n",ur.CStr());
								found = Tools::getRealUrl(ur,result);
								//curl_easy_cleanup(curl);
								if(found)
								{
//									for(int rr=0;rr<result.Len();rr++)
//									{
//										printf("Real: %s\n",result[rr].CStr());
//									}
//									printf("\n\n\n");
									v.AddV(result);
								}
								result.Clr();
							}
						}
						TwitterUrl tt(rawUrls[i].time,v);
						allUrls.Add(tt);
					}

					// save all urls
					TZipOut	outData(resultFname);
					allUrls.Save(outData);

					// removing the raw file
					int resp = system(TStr::Fmt("rm %s",rawFname.CStr()).CStr());
					printf("responce: %d\n",resp);
				}
			}

			// next file
		}
		printf("\n\n ---=== EVERYTHING DONE ===---\n");
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
