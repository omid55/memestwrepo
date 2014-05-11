// Omid55

/*
 * separately_search_quotes_content_over_twitter_files.cpp
 *
 *  Created on: Jan 9, 2014
 *      Author: oaskaris
 */

//Omid55
#include "stdafx.h"
#include "snap/memes.h"

class Tweet
{
public:
	TStr content;
	TSecTm time;

	Tweet()
	{
	}

	Tweet(TStr &c, TSecTm& t)
	{
		content = c;
		time = t;
	}

	Tweet(TSIn& SIn)
	{
		Load(SIn);
	}

	void Load(TSIn& SIn)
	{
		content.Load(SIn);
		time.Load(SIn);
	}

	void Save(TSOut& SOut)
	{
		content.Save(SOut);
		time.Save(SOut);
	}
};

inline bool fileExists(TStr filepath)
{
	fstream f(filepath.CStr(),ios::in);
	if(!f)
	{
		f.close();
		return false;
	}
	f.close();
	return true;
}


#define LENGTH 1
TVec< Tweet > tweets;
THash<TStr,TInt> quotesContent;
THash<TInt,TSecTmV> cascadesOnTwitter;

int main(int argc, char* argv[])
{
	int i, q, id, start, end, indx, twpackId;
	TExeTm ExeTm;
	if(argc > 1)
	{
		start = atoi(argv[1]);
	}
	else
	{
		printf("YOU SHOULD SET THE INDICES...\n\n");
		return 1;
	}
	indx = start * LENGTH;
	end = indx + LENGTH;

	printf("--== Start Searching Quote over Contents of Tweets CODE (FOR QSUB) ==-- ...\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nSearching the quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		while(indx < end)
		{
			cascadesOnTwitter.Clr();
			TStr qContentFname = TStr::Fmt("QuotesData/Q%d.rar",indx);
			TStr resultFname = TStr::Fmt("QuotesCascResult/R%d.rar",indx++);

			if(fileExists(resultFname))
			{
				if(fileExists(qContentFname))
				{
					// removing the quotes' content file
					system(TStr::Fmt("rm %s",qContentFname.CStr()).CStr());
				}
			}
			else
			{
				if(fileExists(qContentFname))
				{
					quotesContent.Clr();
					TZipIn ZquotesIn(qContentFname);
					quotesContent.Load(ZquotesIn);
					printf("Q%d loading done, it contains %d quotes.\n",indx-1,quotesContent.Len());

					for(twpackId=1;twpackId<=17;twpackId++)
					{
						tweets.Clr();
						TZipIn tweetIn(TStr::Fmt("/is/ei/oaskaris/TWITTER_DATA/Tweets%d.rar",twpackId).CStr());
						tweets.Load(tweetIn);
						printf("Loaded Tweets has instances: %d\n\n\n",tweets.Len());
						for(q=0;q<quotesContent.Len();q++)
						{
							for(i=0;i<tweets.Len();i++)
							{
								// Content Search
								// search for its content to be found over current tweet
								if (tweets[i].content.SearchStr(quotesContent.GetKey(q)) > -1)     // this means that the quote content has been found in tweet
								{
									id = cascadesOnTwitter.GetKeyId(quotesContent[q]);
									if(id == -1)
									{
										cascadesOnTwitter.AddDat(quotesContent[q]).Add(tweets[i].time);
									}
									else
									{
										cascadesOnTwitter.GetDat(quotesContent[q]).AddSorted(tweets[i].time);
									}
								}
							}
						}
					}

					// Save the results
					TZipOut zout(resultFname);
					cascadesOnTwitter.Save(zout);

					// Remove the qoutes' content file
					system(TStr::Fmt("rm %s",qContentFname.CStr()).CStr());
				}
			}

			// next file
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




