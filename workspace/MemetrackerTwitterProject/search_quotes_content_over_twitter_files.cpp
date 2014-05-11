// Omid55

/*
 * search_quotes_content_over_twitter_files.cpp
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


THash< TStr , CascadeElementV > quotes;
TVec< Tweet > tweets;

THash<TUInt,TSecTmV> cascadesOnTwitter;    // index of quote to a vector of times which is the times mentioned in Twitter in content (sorted ascending)

int twpackId = -1;
void SaveAll()
{
	TZipOut outData(TStr::Fmt("cascadesOnTwitter%d",twpackId).CStr());
	cascadesOnTwitter.Save(outData);
	printf("The size of cascades On Twitter was: %d\n",cascadesOnTwitter.Len());
	printf("\n<<<<<<<< SAVING DONE >>>>>>>>\n\n");
}

int main(int argc, char* argv[])
{
	int i, q, id;
	TExeTm ExeTm;
	TZipIn ZquotesIn("QuotesPreprocessedDataSELECTED.rar");

	if(argc>1)
	{
		twpackId = atoi(argv[1]);
	}
	else
	{
		printf("You should set the twpackId ...\n\n");
		return 1;
	}

	TZipIn tweetIn(TStr::Fmt("/is/ei/oaskaris/TWITTER_DATA/Tweets%d.rar",twpackId).CStr());
	printf("--== Start Searching Quote over Contents of Tweets CODE ==-- ...\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nCreating the volumes of the quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		quotes.Load(ZquotesIn);
		printf("Loaded QuotesCascadesData has instances: %d\n\n\n",quotes.Len());
		tweets.Load(tweetIn);
		printf("Loaded cascadesOnTwitter has instances: %d\n\n\n",tweets.Len());

		printf("Search started ...\n\n\n");
		for(q=0;q<quotes.Len();q++)
		{
			//if(q%100 == 0)
			{
				printf("q: %d\n",q);
			}
			for(i=0;i<tweets.Len();i++)
			{
				// Content Search
				// search for its content to be found over current tweet
				if (tweets[i].content.SearchStr(quotes.GetKey(q)) > -1)     // this means that the quote content has been found in tweet
				{
					id = cascadesOnTwitter.GetKeyId(q);
					if(id == -1)
					{
						cascadesOnTwitter.AddDat(q).Add(tweets[i].time);
					}
					else
					{
						cascadesOnTwitter.GetDat(q).AddSorted(tweets[i].time);
					}
				}
			}
		}

		SaveAll();
	}
	catch(exception& ex)
	{
		printf("\nError1 happened, it was: %s\n\n",ex.what());
		SaveAll();
	}
	catch(TPt<TExcept>& ex)
	{
		printf("\nError2 happened: %s\n\n",ex[0].GetStr().CStr());
		SaveAll();
	}
	printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
	return 0;
}




