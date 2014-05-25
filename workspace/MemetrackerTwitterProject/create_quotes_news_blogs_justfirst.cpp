// Omid55
/*
 * create_quotes_news_blogs_justfirst.cpp
 *
 *  Created on: May 11, 2014
 *      Author: omid55
 */
// Omid55
#include "stdafx.h"

void createNewsBlogsFirsts(char* filename, THash<TChA,TUInt> posts, THash<TStr,TUInt> newsMediaHashtbl)
{
	THash< TStr , CascadeElementV > quotes;
	TZipIn ZquotesIn(TStr::Fmt("/agbs/cluster/oaskaris/DATA/%s.rar",filename));
	quotes.Load(ZquotesIn);
	printf("Loaded %s has instances: %d\n\n\n",filename,quotes.Len());

	// ---=== Separating news and blogs ===---
	// NIFTY
	THash< TStr , CascadeElementV > newsQuotes;
	THash< TStr , CascadeElementV > blogsQuotes;
	Tools::separateTimestepsOfQuotesInBlogsNews(quotes,newsMediaHashtbl,posts,newsQuotes,blogsQuotes);

	TZipOut zout1(TStr::Fmt("%s_NEWS.rar",filename));
	newsQuotes.Save(zout1);
	printf("%s_NEWS saving done, it contains %d posts.\n",filename,newsQuotes.Len());

	TZipOut zout2(TStr::Fmt("%s_BLOGS.rar",filename));
	blogsQuotes.Save(zout2);
	printf("%s_BLOGS saving done, it contains %d posts.\n",filename,blogsQuotes.Len());

	// Removing other mentioning and just save the first one
	THash< TStr , CascadeElementV > firstMentionsquotes;
	Tools::removeOtherTimestepsOfQuotesWithSameDomain(quotes,posts,firstMentionsquotes);
	TZipOut zout3(TStr::Fmt("%s_FIRSTS.rar",filename));
	firstMentionsquotes.Save(zout3);
	printf("%s_FIRSTS saving done, it contains %d posts.\n",filename,firstMentionsquotes.Len());

	THash< TStr , CascadeElementV > firstMentionsquotes_news;
	Tools::removeOtherTimestepsOfQuotesWithSameDomain(newsQuotes,posts,firstMentionsquotes_news);
	TZipOut zout4(TStr::Fmt("%s_FIRSTSNEWS.rar",filename));
	firstMentionsquotes_news.Save(zout4);
	printf("%s_FIRSTSNEWS saving done, it contains %d posts.\n",filename,firstMentionsquotes_news.Len());

	THash< TStr , CascadeElementV > firstMentionsquotes_blogs;
	Tools::removeOtherTimestepsOfQuotesWithSameDomain(blogsQuotes,posts,firstMentionsquotes_blogs);
	TZipOut zout5(TStr::Fmt("%s_FIRSTSBLOGS.rar",filename));
	firstMentionsquotes_blogs.Save(zout5);
	printf("%s_FIRSTSBLOGS saving done, it contains %d posts.\n",filename,firstMentionsquotes_blogs.Len());
}

int main(int argc, char* argv[])
{
//	THash< TStr , CascadeElementV > quotes;
//	TZipIn ZquotesIn2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_FINALFILTERED.rar");
//	quotes.Load(ZquotesIn2);
//	printf("Loaded QuotesPreprocessedData_FINALFILTERED has instances: %d\n\n\n",quotes.Len());
//
//	THash< TStr , CascadeElementV > newsQuotes;
//	TZipIn zin2("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_FINALFILTERED_NEWS.rar");
//	newsQuotes.Load(zin2);
//	printf(TStr::Fmt("%s_NEWS loading done, it contains %d posts.\n",newsQuotes.Len());
//
//	THash< TStr , CascadeElementV > blogsQuotes;
//	TZipIn zin3("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_FINALFILTERED_BLOGS.rar");
//	blogsQuotes.Load(zin3);
//	printf(TStr::Fmt("%s_BLOGS loading done, it contains %d posts.\n",blogsQuotes.Len());
//
//	THash< TStr , CascadeElementV > firstMentionsquotes;
//	TZipIn zin4("/agbs/cluster/oaskaris/DATA/QuotesPreprocessedData_FINALFILTERED_FIRSTS.rar");
//	firstMentionsquotes.Load(zin4);
//	printf(TStr::Fmt("%s_FIRSTS saving done, it contains %d posts.\n",firstMentionsquotes.Len());
//
//	while(true)
//	{
//		int index;
//		cout << "\n\n\nEnter index (0-" << quotes.Len()-1 << "): ";
//		cin >> index;
//		if(index < 0) break;
//
//		cout << "Original:\n";
//		for(int i=0;i<quotes[index].Len();i++)
//		{
//			cout << quotes[index][i].time.GetYmdTmStr().CStr() << endl;
//		}
//		cout << "\n\nNews:\n";
//		for(int i=0;i<newsQuotes[index].Len();i++)
//		{
//			cout << newsQuotes[index][i].time.GetYmdTmStr().CStr() << endl;
//		}
//		cout << "\n\nBlogs:\n";
//		for(int i=0;i<blogsQuotes[index].Len();i++)
//		{
//			cout << blogsQuotes[index][i].time.GetYmdTmStr().CStr() << endl;
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
//		for(int i=0;i<quotes[index].Len();i++)
//		{
//			cout << posts.GetKey(quotes[index][i].post).CStr() << endl;
//		}
//		cout << "\n\nNews:\n";
//		for(int i=0;i<newsQuotes[index].Len();i++)
//		{
//			cout << posts.GetKey(newsQuotes[index][i].post).CStr() << endl;
//		}
//		cout << "\n\nBlogs:\n";
//		for(int i=0;i<blogsQuotes[index].Len();i++)
//		{
//			cout << posts.GetKey(blogsQuotes[index][i].post).CStr() << endl;
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
//		for(int i=0;i<quotes[index].Len();i++)
//		{
//			cout << posts.GetKey(quotes[index][i].post).CStr() << endl;
//		}
//		cout << "\n\nFirstMentionsFqu:\n";
//		for(int i=0;i<firstMentionsquotes[index].Len();i++)
//		{
//			cout << posts.GetKey(firstMentionsquotes[index][i].post).CStr() << endl;
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
			TZipIn newsIn("/agbs/cluster/oaskaris/DATA/NewsMedia.rar");
			newsMediaHashtbl.Load(newsIn);
			printf("Loaded NewsMedia has %d items.\n\n\n",newsMediaHashtbl.Len());
		}

		THash<TChA,TUInt> posts;
		TZipIn ZpostsIn("/agbs/cluster/oaskaris/DATA/PostsData.rar");
		posts.Load(ZpostsIn);
		printf("PostsData loading done, it contains %d posts.\n",posts.Len());


		// Create news and blogs and firsts
//		createNewsBlogsFirsts("QuotesPreprocessedData_NIFTY_FINALFILTERED",posts,newsMediaHashtbl);
		createNewsBlogsFirsts("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4URLS",posts,newsMediaHashtbl);
		createNewsBlogsFirsts("QuotesPreprocessedData_NIFTY_RANGEFIXED_FINALFILTERED_4Contents",posts,newsMediaHashtbl);

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
