// Omid55
/*
 * create_quotes_news_blogs_justfirst.cpp
 *
 *  Created on: May 11, 2014
 *      Author: omid55
 */
// Omid55
#include "stdafx.h"

int main(int argc, char* argv[])
{
//	THash< TStr , CascadeElementV > niftyqu;
//	TZipIn ZquotesIn2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED.rar");
//	niftyqu.Load(ZquotesIn2);
//	printf("Loaded QuotesPreprocessedData_NIFTY_FINALFILTERED has instances: %d\n\n\n",niftyqu.Len());
//
//	THash< TStr , CascadeElementV > nifty_newsQuotes;
//	TZipIn zin2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS.rar");
//	nifty_newsQuotes.Load(zin2);
//	printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS loading done, it contains %d posts.\n",nifty_newsQuotes.Len());
//
//	THash< TStr , CascadeElementV > nifty_blogsQuotes;
//	TZipIn zin3("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS.rar");
//	nifty_blogsQuotes.Load(zin3);
//	printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS loading done, it contains %d posts.\n",nifty_blogsQuotes.Len());
//
//	THash< TStr , CascadeElementV > firstMentionsNiftyqu;
//	TZipIn zin4("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS.rar");
//	firstMentionsNiftyqu.Load(zin4);
//	printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS saving done, it contains %d posts.\n",firstMentionsNiftyqu.Len());
//
//	while(true)
//	{
//		int index;
//		cout << "\n\n\nEnter index (0-" << niftyqu.Len()-1 << "): ";
//		cin >> index;
//		if(index < 0) break;
//
//		cout << "Original:\n";
//		for(int i=0;i<niftyqu[index].Len();i++)
//		{
//			cout << niftyqu[index][i].time.GetYmdTmStr().CStr() << endl;
//		}
//		cout << "\n\nNews:\n";
//		for(int i=0;i<nifty_newsQuotes[index].Len();i++)
//		{
//			cout << nifty_newsQuotes[index][i].time.GetYmdTmStr().CStr() << endl;
//		}
//		cout << "\n\nBlogs:\n";
//		for(int i=0;i<nifty_blogsQuotes[index].Len();i++)
//		{
//			cout << nifty_blogsQuotes[index][i].time.GetYmdTmStr().CStr() << endl;
//		}
//	}
//	return 0;

//	THash<TChA,TUInt> posts;
//	TZipIn ZpostsIn("/agbs/cluster/oaskaris/DATA/PostsData.rar");
//	posts.Load(ZpostsIn);
//	printf("PostsData loading done, it contains %d posts.\n",posts.Len());
//
//	while(true)
//	{
//		int index;
//		cout << "\n\n\nEnter index: ";
//		cin >> index;
//		if(index < 0) break;
//
//		cout << "Original:\n";
//		for(int i=0;i<niftyqu[index].Len();i++)
//		{
//			cout << posts.GetKey(niftyqu[index][i].post).CStr() << endl;
//		}
//		cout << "\n\nNews:\n";
//		for(int i=0;i<nifty_newsQuotes[index].Len();i++)
//		{
//			cout << posts.GetKey(nifty_newsQuotes[index][i].post).CStr() << endl;
//		}
//		cout << "\n\nBlogs:\n";
//		for(int i=0;i<nifty_blogsQuotes[index].Len();i++)
//		{
//			cout << posts.GetKey(nifty_blogsQuotes[index][i].post).CStr() << endl;
//		}
//	}
//
//	while(true)
//	{
//		int index;
//		cout << "\n\n\nEnter index: ";
//		cin >> index;
//		if(index < 0) break;
//
//		cout << "Original:\n";
//		for(int i=0;i<niftyqu[index].Len();i++)
//		{
//			cout << posts.GetKey(niftyqu[index][i].post).CStr() << endl;
//		}
//		cout << "\n\nFirstMentionsFqu:\n";
//		for(int i=0;i<firstMentionsNiftyqu[index].Len();i++)
//		{
//			cout << posts.GetKey(firstMentionsNiftyqu[index][i].post).CStr() << endl;
//		}
//	}


	TExeTm ExeTm;
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nCreating the quotes with just news and just blogs, creating quotes which just first mentioning exists. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		// Create and save news media hashtable
		THash<TStr,TUInt> newsMediaHashtbl;
		if(!Tools::fileExists("/agbs/cluster/oaskaris/DATA/NewsMedia.rar"))
		{
			ifstream f("/agbs/cluster/oaskaris/DATA/news_media.txt",ios::in);
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

		THash< TStr , CascadeElementV > niftyqu;
		TZipIn ZquotesIn2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_NIFTY_FINALFILTERED.rar");
	//		TZipIn ZquotesIn2("QuotesPreprocessedData_NIFTY_SUBSETTED.rar");       // for local in my computer
		niftyqu.Load(ZquotesIn2);
		printf("Loaded QuotesPreprocessedData_NIFTY_FINALFILTERED has instances: %d\n\n\n",niftyqu.Len());

		THash<TChA,TUInt> posts;
		TZipIn ZpostsIn("/agbs/cluster/oaskaris/DATA/PostsData.rar");
		posts.Load(ZpostsIn);
		printf("PostsData loading done, it contains %d posts.\n",posts.Len());

		// ---=== Separating news and blogs ===---
		// NIFTY
		THash< TStr , CascadeElementV > nifty_newsQuotes;
		THash< TStr , CascadeElementV > nifty_blogsQuotes;
		Tools::separateTimestepsOfQuotesInBlogsNews(niftyqu,newsMediaHashtbl,posts,nifty_newsQuotes,nifty_blogsQuotes);
		newsMediaHashtbl.Clr();

		TZipOut zout1("QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS.rar");
		nifty_newsQuotes.Save(zout1);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_NEWS saving done, it contains %d posts.\n",nifty_newsQuotes.Len());

		TZipOut zout2("QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS.rar");
		nifty_blogsQuotes.Save(zout2);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_BLOGS saving done, it contains %d posts.\n",nifty_blogsQuotes.Len());

		// Removing other mentioning and just save the first one
		THash< TStr , CascadeElementV > firstMentionsNiftyqu;
		Tools::removeOtherTimestepsOfQuotesWithSameDomain(niftyqu,posts,firstMentionsNiftyqu);
		TZipOut zout3("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS.rar");
		firstMentionsNiftyqu.Save(zout3);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTS saving done, it contains %d posts.\n",firstMentionsNiftyqu.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu_news;
		Tools::removeOtherTimestepsOfQuotesWithSameDomain(nifty_newsQuotes,posts,firstMentionsNiftyqu_news);
		TZipOut zout4("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS.rar");
		firstMentionsNiftyqu_news.Save(zout4);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSNEWS saving done, it contains %d posts.\n",firstMentionsNiftyqu_news.Len());

		THash< TStr , CascadeElementV > firstMentionsNiftyqu_blogs;
		Tools::removeOtherTimestepsOfQuotesWithSameDomain(nifty_blogsQuotes,posts,firstMentionsNiftyqu_blogs);
		TZipOut zout5("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS.rar");
		firstMentionsNiftyqu_blogs.Save(zout5);
		printf("QuotesPreprocessedData_NIFTY_FINALFILTERED_FIRSTSBLOGS saving done, it contains %d posts.\n",firstMentionsNiftyqu_blogs.Len());

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
