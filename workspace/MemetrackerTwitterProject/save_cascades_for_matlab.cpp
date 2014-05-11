//Omid55

/*
 * save_cascades_for_matlab.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: oaskaris
 */

//Omid55
#include "stdafx.h"
#include "snap/memes.h"

THash< TStr , CascadeElementV > quotes;
THash< TUInt , TSecTmV > cascadesOnTwitterUrls;
THash< TUInt , TSecTmV > cascadesOnTwitterContents;


int main(int argc, char* argv[])
{
	int i,quoteIndex,j,k;
	TExeTm ExeTm;

	printf("Starting The SAVE CODE For Matlab Processing ...\n");
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nCreating the volumes of the quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		TZipIn ZquotesIn("RESULTS/QuotesPreprocessedData_NIFTY.rar");
		quotes.Load(ZquotesIn);
		printf("Loaded QuotesPreprocessedData_NIFTY has instances: %d\n\n\n",quotes.Len());

		TZipIn ZcascadesOnTwitterIn("RESULTS/CascadesFullUrlsOnTwitterData.rar");
		cascadesOnTwitterUrls.Load(ZcascadesOnTwitterIn);
		printf("Loaded CascadesFullUrlsOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterUrls.Len());

		TZipIn ZIn("RESULTS/CascadesOnTwitterData.rar");
		cascadesOnTwitterContents.Load(ZIn);
		printf("Loaded CascadesOnTwitterData has instances: %d\n\n\n",cascadesOnTwitterContents.Len());


		// Quote's Cascades over Memes
		ofstream quotesContent1("MEMES_QuotesContent.csv",ios::out|ios::app);
		ofstream memeWebs1("MEMES_MemesCascadesWebs.csv",ios::out|ios::app);
		ofstream memeTimes1("MEMES_MemesCascadesTimes.csv",ios::out|ios::app);
		ofstream externalLinks1("MEMES_MemesExternalLinks.csv",ios::out|ios::app);
		for(i=0;i<quotes.Len();i++)
		{
			quotesContent1 << quotes.GetKey(i).CStr() << "\r\n";
			for(j=0;j<quotes[i].Len();j++)
			{
				for(k=0;k<quotes[i][j].explicit_links.Len();k++)
				{
					externalLinks1 << quotes[i][j].explicit_links[k].Val << "," << quotes[i][j].post.Val<<"\r\n";
				}
				memeTimes1 << quotes[i][j].time.GetAbsSecs() << ",";
				memeWebs1 << quotes[i][j].post.Val << ",";
			}
			memeTimes1 << "\r\n";
			memeWebs1 << "\r\n";
			externalLinks1 << "-1\r\n";  // this means that the external links for this quote is finished
		}
		quotesContent1.close();
		memeWebs1.close();
		memeTimes1.close();
		externalLinks1.close();


		// TEXTS Cascades Over Memes and Twitter
		ofstream quotesContent2("MEMES_TWITTER_TXT_QuotesContent.csv",ios::out|ios::app);
		ofstream memeWebs2("MEMES_TWITTER_TXT_MemesCascadesWebs.csv",ios::out|ios::app);
		ofstream memeTimes2("MEMES_TWITTER_TXT_MemesCascadesTimes.csv",ios::out|ios::app);
		ofstream externalLinks2("MEMES_TWITTER_TXT_MemesExternalLinks.csv",ios::out|ios::app);
		ofstream twitterContent2("MEMES_TWITTER_TXT_TwitterTextCascades.csv",ios::out|ios::app);
		for(i=0;i<cascadesOnTwitterContents.Len();i++)
		{
			quoteIndex = cascadesOnTwitterContents.GetKey(i);
			quotesContent2 << quotes.GetKey(quoteIndex).CStr() << "\r\n";

			for(j=0;j<quotes[quoteIndex].Len();j++)
			{
				for(k=0;k<quotes[quoteIndex][j].explicit_links.Len();k++)
				{
					externalLinks2 << quotes[quoteIndex][j].explicit_links[k].Val << "," << quotes[quoteIndex][j].post.Val<<"\r\n";   // << CHECK HERE >> CHANGE -> TO SPACE
				}
				memeTimes2 << quotes[quoteIndex][j].time.GetAbsSecs() << ",";
				memeWebs2 << quotes[quoteIndex][j].post.Val << ",";
			}
			memeTimes2 << "\r\n";
			memeWebs2 << "\r\n";
			externalLinks2 << "-1\r\n";  // this means that the external links for this quote is finished

			for(j=0;j<cascadesOnTwitterContents.GetDat(quoteIndex).Len();j++)
			{
				twitterContent2 << cascadesOnTwitterContents.GetDat(quoteIndex)[j] << ",";
			}
			twitterContent2 << "\r\n";
		}
		quotesContent2.close();
		memeWebs2.close();
		memeTimes2.close();
		externalLinks2.close();
		twitterContent2.close();


		// URLS Cascades Over Memes and Twitter
		ofstream quotesContent3("MEMES_TWITTER_URL_QuotesContent.csv",ios::out|ios::app);
		ofstream memeWebs3("MEMES_TWITTER_URL_MemesCascadesWebs.csv",ios::out|ios::app);
		ofstream memeTimes3("MEMES_TWITTER_URL_MemesCascadesTimes.csv",ios::out|ios::app);
		ofstream externalLinks3("MEMES_TWITTER_URL_MemesExternalLinks.csv",ios::out|ios::app);
		ofstream twitter3("MEMES_TWITTER_URL_TwitterUrlCascades.csv",ios::out|ios::app);
		for(i=0;i<cascadesOnTwitterUrls.Len();i++)
		{
			quoteIndex = cascadesOnTwitterUrls.GetKey(i);
			quotesContent3 << quotes.GetKey(quoteIndex).CStr() << "\r\n";

			for(j=0;j<quotes[quoteIndex].Len();j++)
			{
				for(k=0;k<quotes[quoteIndex][j].explicit_links.Len();k++)
				{
					externalLinks3 << quotes[quoteIndex][j].explicit_links[k].Val << "," << quotes[quoteIndex][j].post.Val<<"\r\n";   // << CHECK HERE >> CHANGE -> TO SPACE
				}
				memeTimes3 << quotes[quoteIndex][j].time.GetAbsSecs() << ",";
				memeWebs3 << quotes[quoteIndex][j].post.Val << ",";
			}
			memeTimes3 << "\r\n";
			memeWebs3 << "\r\n";
			externalLinks3 << "-1\r\n";  // this means that the external links for this quote is finished

			for(j=0;j<cascadesOnTwitterUrls.GetDat(quoteIndex).Len();j++)
			{
				twitter3 << cascadesOnTwitterUrls.GetDat(quoteIndex)[j] << ",";
			}
			twitter3 << "\r\n";
		}
		quotesContent3.close();
		memeWebs3.close();
		memeTimes3.close();
		externalLinks3.close();
		twitter3.close();


		// INTERSECT OF URLS OF TEXTS Cascades Over Memes and Twitter
		ofstream quotesContent4("TRIPLE_QuotesContent.csv",ios::out|ios::app);
		ofstream memeWebs4("TRIPLE_MemesCascadesWebs.csv",ios::out|ios::app);
		ofstream memeTimes4("TRIPLE_MemesCascadesTimes.csv",ios::out|ios::app);
		ofstream externalLinks4("TRIPLE_MemesExternalLinks.csv",ios::out|ios::app);
		ofstream twitter4("TRIPLE_TwitterUrlCascades.csv",ios::out|ios::app);
		ofstream twitterContent4("TRIPLE_TwitterTextCascades.csv",ios::out|ios::app);
		for(i=0;i<cascadesOnTwitterUrls.Len();i++)
		{
			quoteIndex = cascadesOnTwitterUrls.GetKey(i);
			if(cascadesOnTwitterContents.GetKeyId(quoteIndex) == -1)
			{
				continue;
			}
			quotesContent4 << quotes.GetKey(quoteIndex).CStr() << "\r\n";

			for(j=0;j<quotes[quoteIndex].Len();j++)
			{
				for(k=0;k<quotes[quoteIndex][j].explicit_links.Len();k++)
				{
					externalLinks4 << quotes[quoteIndex][j].explicit_links[k].Val << "," << quotes[quoteIndex][j].post.Val<<"\r\n";   // << CHECK HERE >> CHANGE -> TO SPACE
				}
				memeTimes4 << quotes[quoteIndex][j].time.GetAbsSecs() << ",";
				memeWebs4 << quotes[quoteIndex][j].post.Val << ",";
			}
			memeTimes4 << "\r\n";
			memeWebs4 << "\r\n";
			externalLinks4 << "-1\r\n";  // this means that the external links for this quote is finished

			for(j=0;j<cascadesOnTwitterContents.GetDat(quoteIndex).Len();j++)
			{
				twitterContent4 << cascadesOnTwitterContents.GetDat(quoteIndex)[j] << ",";
			}

			for(j=0;j<cascadesOnTwitterUrls.GetDat(quoteIndex).Len();j++)
			{
				twitter4 << cascadesOnTwitterUrls.GetDat(quoteIndex)[j] << ",";
			}
			twitter4 << "\r\n";
			twitterContent4 << "\r\n";
		}
		quotesContent4.close();
		memeWebs4.close();
		memeTimes4.close();
		externalLinks4.close();
		twitter4.close();
		twitterContent4.close();
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




