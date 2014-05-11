//Omid55
#include "stdafx.h"
#include "snap/memes.h"
#include <dirent.h>
#include <stdlib.h>
#include <mysql++/mysql++.h>
#include <mysql++/connection.h>
#include <mysql++/mystring.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
using namespace mysqlpp;
using namespace std;

#define STRING_MAX_SIZE_FOR_DB 500

THash<TStr,TStr> sites;     //domains
THash<TStr,TStr> quotes;
THash<TStr,TStr> links;
THash<TStr,TStr> urls;
THash<TStr,TInt> processedFiles;
TStr fileName = "";
long long postno = 0;


inline void removeAllBadCharacters(TStr& s)
{
	s = s.ToTrunc();
	s.DelChAll('\'');
	s.DelChAll('\\');
	s.DelChAll('%');
	s.DelChAll('"');
	s.DelChAll(';');
}

inline TStr addPost(Query query,TStr post,TStr time,TStr site)
{
	TStr query_text;
	removeAllBadCharacters(site);
	TStr siteLC = site.ToLc();
	site = site.Slice(0,STRING_MAX_SIZE_FOR_DB);
	int id = sites.GetKeyId(siteLC);
	TStr selected_sid;
	if(id == -1)
	{
		query_text = TStr::Fmt("INSERT INTO SitesTb (sname) VALUES ('%s');",site.CStr());
		query << query_text.CStr();
		query.store();

		query << "SELECT last_insert_id();";
		StoreQueryResult res = query.store();
		selected_sid = TStr((*res.begin())[0].c_str());
		sites.AddDat(siteLC,selected_sid);
	}
	else
	{
		selected_sid = sites.GetDat(siteLC);
	}
	removeAllBadCharacters(post);
	query_text = TStr::Fmt("INSERT INTO PostsTb (pwebsite,ptime,sid) VALUES ('%s','%s',%s);",post.CStr(),time.CStr(),selected_sid.CStr());
	query << query_text.CStr();
	query.store();

	query << "SELECT last_insert_id();";
	StoreQueryResult res = query.store();
	String new_post_id = (*res.begin())[0];
	return TStr(new_post_id.c_str());
}

inline void addQuote(Query query, TStr new_post_id ,TStr quote)
{
	TStr query_text;
	removeAllBadCharacters(quote);
	quote = quote.Slice(0,STRING_MAX_SIZE_FOR_DB);
	TStr quoteLC = quote.ToLc();
	int id = quotes.GetKeyId(quoteLC);
	TStr selected_qid;
	if(id == -1)
	{
		query_text = TStr::Fmt("INSERT INTO QuotesTb (quote) VALUES ('%s');",quote.CStr());
		query << query_text.CStr();
		query.store();

		query << "SELECT last_insert_id();";
		StoreQueryResult res = query.store();
		selected_qid = TStr((*res.begin())[0].c_str());
		quotes.AddDat(quoteLC,selected_qid);
	}
	else
	{
		selected_qid = quotes.GetDat(quoteLC);
	}

	try
	{
		query_text = TStr::Fmt("INSERT INTO PostQuoteTb (pid,qid) VALUES (%s,%s);",new_post_id.CStr(),selected_qid.CStr());
		query << query_text.CStr();
		query.store();
	}
	catch(exception & e)
	{
		// no problem
	}
}

inline void addLink(Query query, TStr new_post_id ,TStr link)
{
	TStr query_text;
	removeAllBadCharacters(link);
	link = link.Slice(0,STRING_MAX_SIZE_FOR_DB);
	TStr linkLC = link.ToLc();
	int id = links.GetKeyId(linkLC);
	TStr selected_lid(TStr::Fmt("%llu",id).CStr());
	if(id == -1)
	{
		query_text = TStr::Fmt("INSERT INTO LinksTb (link) VALUES ('%s');",link.CStr());
		query << query_text.CStr();
		query.store();

		query << "SELECT last_insert_id();";
		StoreQueryResult res = query.store();
		selected_lid = TStr((*res.begin())[0].c_str());
		links.AddDat(linkLC,selected_lid);
	}
	else
	{
		selected_lid = links.GetDat(linkLC);;
	}

	try
	{
		query_text = TStr::Fmt("INSERT INTO PostLinkTb (pid,lid) VALUES (%s,%s);",new_post_id.CStr(),selected_lid.CStr());
		query << query_text.CStr();
		query.store();
	}
	catch(exception & e)
	{
		// no problem
	}
}

inline void addExternalLink(Query query, TStr source_pid ,TStr linker_pid)
{
	TStr query_text;
	try
	{
		query_text = TStr::Fmt("INSERT INTO Post2PostTb (source_pid,linker_pid) VALUES (%s,%s);",source_pid.CStr(),linker_pid.CStr());
		query << query_text.CStr();
		query.store();
	}
	catch(exception & e)
	{
		// no problem
	}
}

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

void SaveAllThings()
{
	try
	{
		// Saving the hashtables
		TZipOut Zsites("HashSites.rar");
		sites.Save(Zsites);
		TZipOut Zquotes("HashQuotes.rar");
		quotes.Save(Zquotes);
		TZipOut Zlinks("HashLinks.rar");
		links.Save(Zlinks);
		TZipOut Zurls("HashUrls.rar");
		urls.Save(Zurls);
		TZipOut Zfiles("HashProcessedFiles.rar");
		processedFiles.Save(Zfiles);

		// Saving the place of the last file
		ofstream f("FilePlace.txt");
		f<<postno;
		f.close();
	}
	catch(exception& ex)
	{
		printf("Error happened in saving all the things, which is :\n%s\n",ex.what());
	}
}

void LoadAllThings()
{
	try
	{
		// Loading the hashtables
		TZipIn Zsites("HashSites.rar");
		sites.Load(Zsites);
		TZipIn Zquotes("HashQuotes.rar");
		quotes.Load(Zquotes);
		TZipIn Zlinks("HashLinks.rar");
		links.Load(Zlinks);
		TZipIn Zurls("HashUrls.rar");
		urls.Load(Zurls);
		TZipIn Zfiles("HashProcessedFiles.rar");
		processedFiles.Load(Zfiles);

		// Loading the place of the last file
		ifstream f("FilePlace.txt");
		f >> postno;
		f.close();
	}
	catch(TPt<TExcept>& ex)
	{
		printf("Ok\n\n");
	}
	catch(exception& ex)
	{
		printf("Error happened in loading all the things, which is :\n%s\n",ex.what());
	}
}


int main(int argc, char* argv[])
{
	printf("Starting the memes quote cascades code...\n\n");

	TExeTm ExeTm;
	try
	{
		// Database
		Connection conn;
		conn.set_option(new ReconnectOption(true));
		conn.set_option(new ConnectTimeoutOption(5));
		string db = "dbmemetracker0809";
		if(!conn.connect(db.c_str(),"lune.is.localnet","oaskaris","GupViuj7",3306))
		{
			printf("Connection failed to Database ...\n");
			return 1;
		}
		Query query = conn.query();

		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nGenerate cascades from memetracker. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		LoadAllThings();
		long long lastPostNo = postno;
		postno = 0;

		DIR *dp;
		struct dirent *dirp;
		TStr dir = "/agbs/datasets/memetracker";
		if((dp  = opendir(dir.CStr())) == NULL)
		{
			printf("Error happened while openning the directory.");
			return 1;
		}

		while ((dirp = readdir(dp)) != NULL)
		{
			TStr file(dirp->d_name);

			if(file.Len()<=4)
			{
				continue;
			}

			TStr ext = file.GetSubStr(file.Len()-4,file.Len());
			TStr desiredExt = TStr(".rar");
			if(!ext.EqI(desiredExt))
			{
				continue;
			}

			TStr filefullpath = TStr::Fmt("%s/%s",dir.CStr(),file.CStr());
			if(processedFiles.GetKeyId(filefullpath)!=-1)   // if this file is already processed
			{
				continue;
			}
			TMemesDataLoader loader(filefullpath);
			while(loader.LoadNext())
			{
				postno++;
				if(postno>=lastPostNo)
				{
					lastPostNo = 0;
					TStr new_post_id = addPost(query,loader.PostUrlStr,loader.PubTm.GetYmdTmStr(),getWebsite(loader.PostUrlStr));
					urls.AddDat(loader.PostUrlStr.ToLc(),new_post_id);
					for(int i=0;i<loader.MemeV.Len();i++)
					{
						addQuote(query,new_post_id,loader.MemeV[i]);
					}
					for(int i=0;i<loader.LinkV.Len();i++)
					{
						addLink(query,new_post_id,loader.LinkV[i]);
						if(urls.GetKeyId(loader.LinkV[i]) != -1)
						{
						  TStr source = urls.GetDat(loader.LinkV[i]);
						  addExternalLink(query,source,new_post_id);
						}
					}
				}
			}

			processedFiles.AddDat(filefullpath);
		}

		SaveAllThings();

		closedir(dp);
		conn.disconnect();
	}
	catch(std::exception& ex)
	{
		SaveAllThings();
		printf("Error happened, it was: %s\n\n",ex.what());
	}
	catch(TPt<TExcept>& ex)
	{
		SaveAllThings();
		printf("Ok1\n\n");
	}
	catch(mysqlpp::Exception& ex)
	{
		SaveAllThings();
		printf("Ok2\n\n");
	}

	printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
	return 0;
}
