// Omid55
/*
 * create_quotes_news_blogs_justfirst.cpp
 *
 *  Created on: May 11, 2014
 *      Author: omid55
 */
// Omid55
#include "stdafx.h"
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nCreating the quotes with just news and just blogs, creating quotes which just first mentioning exists. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// Create and save news media hashtable
		THash<TStr,TUInt> newsMediaHashtbl;
		if(!Tools::fileExists("NewsMedia.rar"))
		{
			ifstream f("news_media.txt",ios::in);
			while(f)
			{
				string line;
				f >> line;
				newsMediaHashtbl.AddDat(TStr(line.c_str()),TUInt(newsMediaHashtbl.Len()));
			}
			TZipOut newsOut("NewsMedia.rar");
			newsMediaHashtbl.Save(newsOut);
			printf("NewsMedia has %d items.\n",newsMediaHashtbl.Len());
		}
		else
		{
			TZipIn newsIn("NewsMedia.rar");
			newsMediaHashtbl.Load(newsIn);
			printf("Loaded NewsMedia has %d items.\n\n\n",newsMediaHashtbl.Len());
		}

		// ---== Loading Data ==---
	//		THash< TStr , CascadeElementV > fqu;
	//		TZipIn ZquotesIn1("QuotesData.rar");
	//		fqu.Load(ZquotesIn1);
	//		printf("Loaded QuotesData has instances: %d\n\n\n",fqu.Len());

		THash< TStr , CascadeElementV > niftyqu;
		TZipIn ZquotesIn2("QuotesPreprocessedData_NIFTY_FINALFILTERED.rar");
	//		TZipIn ZquotesIn2("QuotesPreprocessedData_NIFTY_SUBSETTED.rar");       // for local in my computer
		niftyqu.Load(ZquotesIn2);
		printf("Loaded QuotesPreprocessedData_NIFTY_FINALFILTERED has instances: %d\n\n\n",niftyqu.Len());

		THash<TChA,TUInt> posts;
		TZipIn ZpostsIn("PostsData.rar");
		posts.Load(ZpostsIn);
		printf("PostsData loading done, it contains %d posts.\n",posts.Len());

		// ---=== Separating news and blogs ===---
	//		// Full
	//		THash< TStr , CascadeElementV > full_newsQuotes;
	//		THash< TStr , CascadeElementV > full_blogsQuotes;
	//		Tools::separateTimestepsOfQuotesInBlogsNews(fqu,newsMediaHashtbl,posts,full_newsQuotes,full_blogsQuotes);
	//
	//		TZipOut zout1("QuotesData_NEWS.rar");
	//		full_newsQuotes.Save(zout1);
	//		printf("QuotesData_NEWS loading done, it contains %d posts.\n",full_newsQuotes.Len());
	//		TZipOut zout2("QuotesData_BLOGS.rar");
	//		full_blogsQuotes.Save(zout2);
	//		printf("QuotesData_BLOGS loading done, it contains %d posts.\n",full_blogsQuotes.Len());

		// NIFTY
		THash< TStr , CascadeElementV > nifty_newsQuotes;
		THash< TStr , CascadeElementV > nifty_blogsQuotes;
		Tools::separateTimestepsOfQuotesInBlogsNews(niftyqu,newsMediaHashtbl,posts,nifty_newsQuotes,nifty_blogsQuotes);
		newsMediaHashtbl.Clr();

		TZipOut zout3("QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS.rar");
		nifty_newsQuotes.Save(zout3);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS saving done, it contains %d posts.\n",nifty_newsQuotes.Len());
		TZipOut zout4("QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS.rar");
		nifty_blogsQuotes.Save(zout4);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS saving done, it contains %d posts.\n",nifty_blogsQuotes.Len());


		// Removing other mentioning and just save the first one
	//		THash< TStr , CascadeElementV > firstMentionsFqu;
	//		Tools::removeOtherTimestepsOfQuotesWithSameDomain(fqu,posts,firstMentionsFqu);
		THash< TStr , CascadeElementV > firstMentionsNiftyqu;
		Tools::removeOtherTimestepsOfQuotesWithSameDomain(niftyqu,posts,firstMentionsNiftyqu);

	//		TZipOut zout5("QuotesData_FIRSTS.rar");
	//		firstMentionsFqu.Save(zout5);
	//		printf("QuotesData_FIRSTS saving done, it contains %d posts.\n",firstMentionsFqu.Len());
		TZipOut zout6("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS.rar");
		firstMentionsNiftyqu.Save(zout6);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS saving done, it contains %d posts.\n",firstMentionsNiftyqu.Len());


		while(true)
		{
			int index;
			cout << "\n\n\nEnter index: ";
			cin >> index;
			if(index < 0) break;

			cout << "Original:\n";
			for(int i=0;i<niftyqu[index].Len();i++)
			{
				cout << posts.GetKey(niftyqu[index][i].post).CStr() << endl;
			}
			cout << "\n\nNews:\n";
			for(int i=0;i<nifty_newsQuotes[index].Len();i++)
			{
				cout << posts.GetKey(nifty_newsQuotes[index][i].post).CStr() << endl;
			}
			cout << "\n\nBlogs:\n";
			for(int i=0;i<nifty_blogsQuotes[index].Len();i++)
			{
				cout << posts.GetKey(nifty_blogsQuotes[index][i].post).CStr() << endl;
			}
		}

		while(true)
		{
			int index;
			cout << "\n\n\nEnter index: ";
			cin >> index;
			if(index < 0) break;

			cout << "Original:\n";
			for(int i=0;i<niftyqu[index].Len();i++)
			{
				cout << posts.GetKey(niftyqu[index][i].post).CStr() << endl;
			}
			cout << "\n\nFirstMentionsFqu:\n";
			for(int i=0;i<firstMentionsNiftyqu[index].Len();i++)
			{
				cout << posts.GetKey(firstMentionsNiftyqu[index][i].post).CStr() << endl;
			}
		}

		posts.Clr();
		printf("\n\nDONE\n\n");
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
