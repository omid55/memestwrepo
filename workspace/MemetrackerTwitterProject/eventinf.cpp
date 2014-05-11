#include "stdafx.h"
#include "eventinf.h"
#include <postgresql/libpq-fe.h>
#include <sqlite3.h>


void TFNBs::LoadFlowNetworkTxt(TSIn& SIn) {
	TStr Line;

	FlowNetwork.Clr(); // clear network (if any)

	// add nodes
	SIn.GetNextLn(Line);
	while (!SIn.Eof() && Line != "") {
		TStrV NIdV; Line.SplitOnAllCh(',', NIdV);
		FlowNetwork.AddNode(NIdV[0].GetInt());
		SIn.GetNextLn(Line);
	}

	// add edges
	while (!SIn.Eof()) {
		SIn.GetNextLn(Line);
		TStrV FieldsV; Line.SplitOnAllCh(',', FieldsV);

		FlowNetwork.AddEdge(FieldsV[0].GetInt(), FieldsV[1].GetInt(), FieldsV[2].GetFlt());
	}

	printf("flow network nodes:%d edges:%d\n", FlowNetwork.GetNodes(), FlowNetwork.GetEdges());
}

void TFNBs::SaveFlowNetworkTxt(const TStr& OutFNm) {
	TFOut FOut(OutFNm);

	// write nodes to file
	for (TFltFltNet::TNodeI NI = FlowNetwork.BegNI(); NI < FlowNetwork.EndNI(); NI++) {
		FOut.PutStr(TStr::Fmt("%d,%d\r\n", NI.GetId(), NI.GetId()));
	}

	FOut.PutStr("\r\n");

	// write edges to file (not allowing self loops in the network)
	for (TFltFltNet::TEdgeI EI = FlowNetwork.BegEI(); EI < FlowNetwork.EndEI(); EI++) {
		TStr Line;
		FOut.PutStr(TStr::Fmt("%d,%d,%f\r\n", EI.GetSrcNId(), EI.GetDstNId(), EI.GetDat().Val));
	}
}

void TFNBs::LoadNodeNamesFromLiteSQL(const int& NumUsers) {
	sqlite3 *db;
	sqlite3_stmt *statement;
	char *zErrMsg = 0;
	int rc;

	printf("Reading nodes db...\n");

	rc = sqlite3_open("/NS/twitter-2/work/parantapa/curated/profiles09.sqlite3", &db);
	if (rc)	{
		printf("Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}

	if (NumUsers==-1) {
		rc = sqlite3_prepare_v2(db, "select userid, screen_name from profiles09;", -1, &statement, 0);
	} else {
		rc = sqlite3_prepare_v2(db, TStr::Fmt("select userid, screen_name from profiles09 where userid < %d;", NumUsers).CStr(), -1, &statement, 0);
	}

	if (rc == SQLITE_OK) {
		// go through all rows
		while(sqlite3_step(statement) == SQLITE_ROW) {
			NodeNmH.AddDat(TStr((char *)sqlite3_column_text(statement, 1)).ToLc()) = sqlite3_column_int(statement, 0);
		}

		sqlite3_finalize(statement);
	}

	printf("%d nodes added!\n", NodeNmH.Len());
}

void TFNBs::LoadFollowersNetworkFromTxt(const int& NumNodes) {
	TFIn FIn("/scratch/NS/sghosh/logs/TotalData/twitter.edgelist.final.txt");

	TStr Line("");
	while (!FIn.Eof()) {
		FIn.GetNextLn(Line);
		TStrV FieldsV; Line.SplitOnAllCh(' ', FieldsV);

		// u v (implies u follows v)
		int src = FieldsV[1].GetInt();
		int dst = FieldsV[0].GetInt();

		if (NumNodes > -1 && (src > NumNodes || dst > NumNodes) ) { continue; }

		if (!FollowersNetwork.IsNode(src)) { FollowersNetwork.AddNode(src); }
		if (!FollowersNetwork.IsNode(dst)) { FollowersNetwork.AddNode(dst); }

		FollowersNetwork.AddEdge(src, dst);
	}
}

void TFNBs::LoadFollowersNetworkFromPostgreSQL(const int& NumUsers) {
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;

	bool verbose = false;

	int ida = -1;
	int idb = -1;

	conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

	if (PQstatus(conn) == CONNECTION_BAD) {
		printf("We were unable to connect to the database");
		return;
	}

	// we use cursors/fetch to speed up the process; batch of 10000 tweets
	PQexec(conn, "begin work");

	if (NumUsers==-1) {
		PQexec(conn, "declare mycursor cursor for select ida, idb from links");
	} else {
		PQexec(conn, TStr::Fmt("declare mycursor cursor for select ida, idb from links where ida < %d and idb < %d", NumUsers).CStr());
	}

	do {
		res = PQexec(conn, "FETCH 10000000 IN mycursor");
		if (PQresultStatus(res) == PGRES_TUPLES_OK) {
			rec_count = PQntuples(res);

			printf("Adding %d links... (total: %d)\n", rec_count, FollowersNetwork.GetEdges());

			for (row=0; row<rec_count; row++) {
				ida = TStr(PQgetvalue(res, row, 0)).GetInt(); // ida
				idb = TStr(PQgetvalue(res, row, 1)).GetInt(); // idb

				if ( (EventsNetwork.IsNode(idb) && EventsNetwork.IsNode(ida)) ||
					 (FlowNetwork.IsNode(idb) && FlowNetwork.IsNode(ida)) ) {
					// add nodes if they do not exist yet
					if (!FollowersNetwork.IsNode(idb)) { FollowersNetwork.AddNode(idb); }
					if (!FollowersNetwork.IsNode(ida)) { FollowersNetwork.AddNode(ida); }

					// ida is following idb; flow of info is idb -> ida
					FollowersNetwork.AddEdge(idb, ida);
				}
			}
			PQclear(res);
		} else {
			rec_count = 0;
		}
	} while (rec_count);

	PQexec(conn, "close mycursor");
	PQexec(conn, "commit work");

	PQfinish(conn);
}

void TFNBs::LoadEventsNetworkFromPostgreSQL(const int& NumUsers, const TStr& StartDate, const TStr& EndDate) {
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;
	int total_number_tweets = 0;

	bool verbose = false;

	conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

	if (PQstatus(conn) == CONNECTION_BAD) {
		printf("We were unable to connect to the database");
		return;
    }

	// we use cursors/fetch to speed up the process; batch of 10000 tweets
	PQexec(conn, "begin work");

	if (NumUsers==-1) {
		PQexec(conn,
		TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s'", StartDate.CStr(), EndDate.CStr()).CStr());
	} else {
		PQexec(conn,
		TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where userid < %d and useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s'", NumUsers, StartDate.CStr(), EndDate.CStr()).CStr());
	}

	do {
		res = PQexec(conn, "FETCH 1000000 IN mycursor");
		if (PQresultStatus(res) == PGRES_TUPLES_OK) {
			rec_count = PQntuples(res);

			total_number_tweets += rec_count;

			printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

			int user_id = -1;
			double tweet_date = 0;
			TStr TweetStr("");
			TStr TweetStrLc("");

			TStr SourceName("");
			int source_id = -1;

			int rt_idx = -1;
			int min_rt_idx = -1;
			int at_idx = -1;
			int min_at_idx = -1;
			int un_idx = -1;
			int min_un_idx = -1;

			for (row=0; row<rec_count; row++) {
				user_id = TStr(PQgetvalue(res, row, 1)).GetInt();
				TweetStr = PQgetvalue(res, row, 3);
				tweet_date = TStr(PQgetvalue(res, row, 4)).GetFlt();

				TweetStrLc = TweetStr.ToLc();

				// add user to network if we don't have it yet
				if (!EventsNetwork.IsNode(user_id)) { EventsNetwork.AddNode(user_id,TFltV()); }

				// check if a twit is a retweet or own tweet
				rt_idx = -1;
				at_idx = -1;
				un_idx = -1;
				min_at_idx = -1;
				min_rt_idx = -1;
				min_un_idx = -1;

				// we search for the retweet word, and then the closest @username just after the word
				if ( (rt_idx=TweetStrLc.SearchStr("via")) > -1 ) {
					at_idx=TweetStr.SearchCh('@', rt_idx+3);
					if ( (at_idx-rt_idx-3) <= 2) {
						min_rt_idx = rt_idx;
						min_at_idx = at_idx;
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("ht"))>-1 ) {
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+2);
						if ( (at_idx-rt_idx-2) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("retweet")) > -1) {
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+7);
						if ( (at_idx-rt_idx-7) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("retweeting")) > -1) {
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+10);
						if ( (at_idx-rt_idx-10) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("rt")) > -1) {
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+2);
						if ( (at_idx-rt_idx-2) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("r/t")) > -1) {
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+3);
						if ( (at_idx-rt_idx-3) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("recycle symbol")) > -1) { // how do I find recycle icon
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+1);
						if ( (at_idx-rt_idx-1) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if (min_at_idx > -1) { // it is a retweet
					const char* ThisBf=TweetStr.CStr();
					// twitter username is alphanumeric and _
					for (int i=min_at_idx+1; i<TweetStr.Len(); i++) {
						if (!isalnum(ThisBf[i]) && ThisBf[i]!='_') {
							min_un_idx = i;
							break;
						}
					}

					SourceName = TweetStr.GetSubStr(min_at_idx+1, min_un_idx>-1? min_un_idx-1 : TweetStr.Len()-1);

					if (verbose) {
						printf("user:%d, tweet:%s, retweet from:%s\n", user_id, TweetStr.CStr(), SourceName.CStr());
					}

					// look for user id in hashtable of username, user id's
					if (NodeNmH.IsKey(SourceName.ToLc())) {
						source_id = NodeNmH.GetDat(SourceName);
						if (!EventsNetwork.IsNode(source_id)) { EventsNetwork.AddNode(source_id, TFltV()); }
						if (!EventsNetwork.IsEdge(source_id, user_id)) { EventsNetwork.AddEdge(source_id, user_id, TFltV()); }
						EventsNetwork.GetEDat(source_id, user_id).Add(tweet_date);
					}
				} else { // is not a retweet
					EventsNetwork.GetNDat(user_id).Add(tweet_date);
				}
			}
			PQclear(res);
		} else {
			rec_count = 0;
		}
	} while (rec_count);

	PQexec(conn, "close mycursor");
	PQexec(conn, "commit work");

	PQfinish(conn);

	printf("%d retweet flows and %d node tweet flows added from %d tweets!\n", EventsNetwork.GetEdges(), EventsNetwork.GetNodes(), total_number_tweets);
}

void TFNBs::LoadUrlEventsNetworkFromPostgreSQL(const int& NumUsers, const TStr& StartDate, const TStr& EndDate) {
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;
	int total_number_tweets = 0;

	bool verbose = false;

	// add markers for url
	TStrV UrlPrefix;
	UrlPrefix.Add("http://"); UrlPrefix.Add("www."); UrlPrefix.Add("bit.ly"); UrlPrefix.Add("tinyurl.com"); UrlPrefix.Add("is.gd"); UrlPrefix.Add("twurl.nl"); UrlPrefix.Add("snurl.com"); UrlPrefix.Add("doiop.com");

	conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

	if (PQstatus(conn) == CONNECTION_BAD) {
		printf("We were unable to connect to the database");
		return;
    }

	// we use cursors/fetch to speed up the process; batch of 10000 tweets
	PQexec(conn, "begin work");

	TStr Condition = "((tweettext LIKE '%http://%') OR (tweettext LIKE '%www.%') OR (tweettext LIKE '%bit.ly%') OR (tweettext LIKE '%tinyurl.com%') OR (tweettext LIKE '%is.gd%') OR (tweettext LIKE '%twurl.nl%') OR (tweettext LIKE '%snurl.com%') OR (tweettext LIKE '%doiop.com%'))";

	if (NumUsers==-1) {
		PQexec(conn,
		TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s' and %s", StartDate.CStr(), EndDate.CStr(), Condition.CStr()).CStr());
	} else {
		PQexec(conn,
		TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where userid < %d and useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s' and %s", NumUsers, StartDate.CStr(), EndDate.CStr(), Condition.CStr()).CStr());
	}

	do {
		res = PQexec(conn, "FETCH 10000000 IN mycursor");
		if (PQresultStatus(res) == PGRES_TUPLES_OK) {
			rec_count = PQntuples(res);

			total_number_tweets += rec_count;

			printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

			int user_id = -1;
			double tweet_date = 0;
			TStr TweetStr("");
			TStr TweetStrLc("");

			TStr SourceName("");
			TStr UrlAddr("");
			int source_id = -1;

			int url_start_idx = -1;
			int url_end_idx = -1;

			int rt_idx = -1;
			int min_rt_idx = -1;
			int at_idx = -1;
			int min_at_idx = -1;
			int un_idx = -1;
			int min_un_idx = -1;

			for (row=0; row<rec_count; row++) {
				user_id = TStr(PQgetvalue(res, row, 1)).GetInt();
				TweetStr = PQgetvalue(res, row, 3);
				tweet_date = TStr(PQgetvalue(res, row, 4)).GetFlt();

				TweetStrLc = TweetStr.ToLc();

				// add user to network if we don't have it yet
				if (!EventsUrlNetwork.IsNode(user_id)) { EventsUrlNetwork.AddNode(user_id,TFltIntPrV()); }

				// extract urls from retweet (we consider each url as a different retweet)
				THashSet<TStr> CurrentUrls;

				for (int i=0; i<UrlPrefix.Len(); i++) {
					url_end_idx = -1;
					url_start_idx = -1;

					while ( (url_start_idx=TweetStrLc.SearchStr(UrlPrefix[i], url_end_idx+1)) > -1 ) {
						url_end_idx = TweetStrLc.SearchCh(' ', url_start_idx+UrlPrefix[i].Len());

						if (i==0 || i==1) { url_start_idx += UrlPrefix[i].Len(); }

						if (url_end_idx==-1) {
							UrlAddr = TweetStrLc.GetSubStr(url_start_idx, TweetStrLc.Len()-1); // store url without prefix
							url_end_idx = TweetStrLc.Len()-1;
						} else {
							UrlAddr = TweetStrLc.GetSubStr(url_start_idx, url_end_idx);
						}

						// for http://, we remove www. if any
						if (UrlAddr.IsPrefix("www.")) { UrlAddr = UrlAddr.GetSubStr(4, UrlAddr.Len()-1); }

						// skip url addresses which are less than 2 characters long
						if (UrlAddr.Len() < 2) { continue; }

						// if the url finishes in non alphanumeric character, we remove it
						if (!isalnum(UrlAddr.GetCh(UrlAddr.Len()-1))) { UrlAddr = UrlAddr.GetSubStr(0, UrlAddr.Len()-2); }

						// store addr if we did not do yet
						if (!CurrentUrls.IsKey(UrlAddr)) { CurrentUrls.AddKey(UrlAddr); }
					}
				}

				// check if a twit is a retweet or own tweet
				rt_idx = -1;
				at_idx = -1;
				un_idx = -1;
				min_at_idx = -1;
				min_rt_idx = -1;
				min_un_idx = -1;

				// we search for the retweet word, and then the closest @username just after the word
				if ( (rt_idx=TweetStrLc.SearchStr("via")) > -1 ) {
					at_idx=TweetStr.SearchCh('@', rt_idx+3);
					if ( (at_idx-rt_idx-3) <= 2) {
						min_rt_idx = rt_idx;
						min_at_idx = at_idx;
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("ht"))>-1 ) {
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+2);
						if ( (at_idx-rt_idx-2) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("retweet")) > -1) {
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+7);
						if ( (at_idx-rt_idx-7) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("retweeting")) > -1) {
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+10);
						if ( (at_idx-rt_idx-10) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("rt")) > -1) {
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+2);
						if ( (at_idx-rt_idx-2) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("r/t")) > -1) {
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+3);
						if ( (at_idx-rt_idx-3) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if ( (rt_idx=TweetStrLc.SearchStr("recycle symbol")) > -1) { // how do I find recycle icon
					if (rt_idx < min_rt_idx) {
						at_idx=TweetStr.SearchCh('@', rt_idx+1);
						if ( (at_idx-rt_idx-1) <= 2) {
							min_at_idx = at_idx;
							min_rt_idx = rt_idx;
						}
					}
				}

				if (min_at_idx > -1) { // it is a retweet
					const char* ThisBf=TweetStr.CStr();
					// twitter username is alphanumeric and _
					for (int i=min_at_idx+1; i<TweetStr.Len(); i++) {
						if (!isalnum(ThisBf[i]) && ThisBf[i]!='_') {
							min_un_idx = i;
							break;
						}
					}

					SourceName = TweetStr.GetSubStr(min_at_idx+1, min_un_idx>-1? min_un_idx-1 : TweetStr.Len()-1);

			/*		if (verbose) {
						printf("user:%d, tweet:%s, retweet from:%s\n", user_id, TweetStr.CStr(), SourceName.CStr());
					}
			*/

					// look for user id in hashtable of username, user id's
					if (NodeNmH.IsKey(SourceName.ToLc())) {
						source_id = NodeNmH.GetDat(SourceName);
						if (!EventsUrlNetwork.IsNode(source_id)) { EventsUrlNetwork.AddNode(source_id, TFltIntPrV()); }
						if (!EventsUrlNetwork.IsEdge(source_id, user_id)) { EventsUrlNetwork.AddEdge(source_id, user_id, TFltIntPrV()); }

						// count each url as a retweet
						for (int i=0; i<CurrentUrls.Len(); i++) {
							if (!UrlAddressNmH.IsKey(CurrentUrls[i])) { UrlAddressNmH.AddDat(CurrentUrls[i]) = UrlAddressNmH.Len(); }
							EventsUrlNetwork.GetEDat(source_id, user_id).Add(TFltIntPr(tweet_date, UrlAddressNmH.GetDat(CurrentUrls[i])));
							if (verbose) { printf("user:%d, tweet:%s, url:%s, retweet from:%s\n", user_id, TweetStr.CStr(), CurrentUrls[i].CStr(), SourceName.CStr()); }
						}
					}
				} else { // is not a retweet
					for (int i=0; i<CurrentUrls.Len(); i++) {
						if (!UrlAddressNmH.IsKey(CurrentUrls[i])) { UrlAddressNmH.AddDat(CurrentUrls[i]) = UrlAddressNmH.Len(); }
						EventsUrlNetwork.GetNDat(user_id).Add(TFltIntPr(tweet_date, UrlAddressNmH.GetDat(CurrentUrls[i])));
					//	if (verbose) { printf("user:%d, tweet:%s, url:%s\n", user_id, TweetStr.CStr(), CurrentUrls[i].CStr()); }
					}
				}
			}
			PQclear(res);
		} else {
			rec_count = 0;
		}
	} while (rec_count);

	PQexec(conn, "close mycursor");
	PQexec(conn, "commit work");

	PQfinish(conn);

	printf("%d retweet flows and %d node tweet flows added from %d tweets!\n", EventsUrlNetwork.GetEdges(), EventsUrlNetwork.GetNodes(), total_number_tweets);
}

void TFNBs::LoadHashtagNetworkFromPostgreSQL(const int& NumUsers, const TStr& StartDate, const TStr& EndDate) {
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;
	int total_number_tweets = 0;

	bool verbose = false;

	conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

	if (PQstatus(conn) == CONNECTION_BAD) {
		printf("We were unable to connect to the database");
		return;
    }

	// we use cursors/fetch to speed up the process; batch of 10000 tweets
	PQexec(conn, "begin work");

	if (NumUsers==-1) {
		PQexec(conn,
		TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s'", StartDate.CStr(), EndDate.CStr()).CStr());
	} else {
		PQexec(conn,
		TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where userid < %d and useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s'", NumUsers, StartDate.CStr(), EndDate.CStr()).CStr());
	}

	do {
		res = PQexec(conn, "FETCH 10000000 IN mycursor");
		if (PQresultStatus(res) == PGRES_TUPLES_OK) {
			rec_count = PQntuples(res);

			total_number_tweets += rec_count;

			printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

			int user_id = -1;
			double tweet_date = 0;
			TStr TweetStr("");
			TStr TweetStrLc("");
			TStr Hashtag("");

			int hashtag_idx_start = 0;
			int hashtag_idx_end = 0;

			for (row=0; row<rec_count; row++) {
				user_id = TStr(PQgetvalue(res, row, 1)).GetInt();
				TweetStr = PQgetvalue(res, row, 3);
				tweet_date = TStr(PQgetvalue(res, row, 4)).GetFlt();

				TweetStrLc = TweetStr.ToLc();

				// add user to network if we don't have it yet
				if (!HashtagsNetwork.IsNode(user_id)) { HashtagsNetwork.AddNode(user_id,TFltIntPrV()); }

				// track hashtags in tweet and add them
				hashtag_idx_start = 0;
				hashtag_idx_end = 0;

				// we search for the retweet word, and then the closest @username just after the word
				while ( (hashtag_idx_start=TweetStrLc.SearchCh('#', hashtag_idx_end)) > -1 ) {
					const char* ThisBf=TweetStrLc.CStr();

					// skip &#, which is asian characters
					if (hashtag_idx_start > 0 && (ThisBf[hashtag_idx_start-1]!=' ')) {
						hashtag_idx_end = hashtag_idx_start+1;
						continue;
					}

					// hashtags are alphanumeric and _
					hashtag_idx_end = -1;
					for (int i=hashtag_idx_start+1; i<TweetStrLc.Len(); i++) {
						if (!isalnum(ThisBf[i]) && ThisBf[i]!='_') {
							hashtag_idx_end = i;
							break;
						}
					}

					Hashtag = TweetStrLc.GetSubStr(hashtag_idx_start+1, hashtag_idx_end>-1? hashtag_idx_end-1 : TweetStrLc.Len()-1);

					if (verbose) {
						printf("user:%d, tweet:%s, hashtag:%s\n", user_id, TweetStr.CStr(), Hashtag.CStr());
					}

					// add hashtag if it is new
					if (!HashtagNmH.IsKey(Hashtag)) { HashtagNmH.AddDat(Hashtag) = HashtagNmH.Len(); }

					// add hashtag event
					HashtagsNetwork.GetNDat(user_id).Add(TFltIntPr(tweet_date, HashtagNmH.GetDat(Hashtag)));

					if (hashtag_idx_end==-1) { break; }
				}
			}
			PQclear(res);
		} else {
			rec_count = 0;
		}
	} while (rec_count);

	PQexec(conn, "close mycursor");
	PQexec(conn, "commit work");

	PQfinish(conn);

	printf("%d hashtags and %d node hashtag flows added from %d tweets!\n", HashtagNmH.Len(), HashtagsNetwork.GetNodes(), total_number_tweets);
}

void TFNBs::LoadUrlRedirectionNetworkFromPostgreSQL(const int& NumUsers, const TStr& StartDate, const TStr& EndDate) {
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;
	int total_number_tweets = 0;

	bool verbose = false;

	conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

	if (PQstatus(conn) == CONNECTION_BAD) {
		printf("We were unable to connect to the database");
		return;
	}

	// we use cursors/fetch to speed up the process; batch of 10000 tweets
	PQexec(conn, "begin work");

	if (NumUsers==-1) {
		PQexec(conn,
				TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s'", StartDate.CStr(), EndDate.CStr()).CStr());
	} else {
		PQexec(conn,
				TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where userid < %d and useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s'", NumUsers, StartDate.CStr(), EndDate.CStr()).CStr());
	}

	do {
		res = PQexec(conn, "FETCH 10000000 IN mycursor");
		if (PQresultStatus(res) == PGRES_TUPLES_OK) {
			rec_count = PQntuples(res);

			total_number_tweets += rec_count;

			printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

			int user_id = -1;
			double tweet_date = 0;
			TStr TweetStr("");
			TStr TweetStrLc("");
			TStr Hashtag("");

			int hashtag_idx_start = 0;
			int hashtag_idx_end = 0;

			for (row=0; row<rec_count; row++) {
				user_id = TStr(PQgetvalue(res, row, 1)).GetInt();
				TweetStr = PQgetvalue(res, row, 3);
				tweet_date = TStr(PQgetvalue(res, row, 4)).GetFlt();

				TweetStrLc = TweetStr.ToLc();

				// track url redirections in tweet and add them (even if the redirection is used several times per tweet, it counts +1)
				for (int i=0; i<UrlRedirectionNmH.Len(); i++) {
					if (TweetStrLc.IsStrIn(UrlRedirectionNmH.GetKey(i))) {
						// add user to network if we don't have it yet
						if (!UrlRedirectionNetwork.IsNode(user_id)) { UrlRedirectionNetwork.AddNode(user_id,TFltIntPrV()); }

						UrlRedirectionNetwork.GetNDat(user_id).Add(TFltIntPr(tweet_date, UrlRedirectionNmH[i]));
					}
				}
			}
			PQclear(res);
		} else {
			rec_count = 0;
		}
	} while (rec_count);

	PQexec(conn, "close mycursor");
	PQexec(conn, "commit work");

	PQfinish(conn);

	printf("%d url redirection services and %d node redirection service flows added from %d tweets!\n", UrlRedirectionNmH.Len(), UrlRedirectionNetwork.GetNodes(), total_number_tweets);
}

void TFNBs::LoadRetweetConventionNetworkFromPostgreSQL(const int& NumUsers, const TStr& StartDate, const TStr& EndDate) {
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;
	int total_number_tweets = 0;

	bool verbose = false;

	conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

	if (PQstatus(conn) == CONNECTION_BAD) {
		printf("We were unable to connect to the database");
		return;
	}

	// we use cursors/fetch to speed up the process; batch of 10000 tweets
	PQexec(conn, "begin work");

	if (NumUsers==-1) {
		PQexec(conn,
				TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s'", StartDate.CStr(), EndDate.CStr()).CStr());
	} else {
		PQexec(conn,
				TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where userid < %d and useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s'", NumUsers, StartDate.CStr(), EndDate.CStr()).CStr());
	}

	do {
		res = PQexec(conn, "FETCH 1000000 IN mycursor");
		if (PQresultStatus(res) == PGRES_TUPLES_OK) {
			rec_count = PQntuples(res);

			total_number_tweets += rec_count;

			printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);

			int user_id = -1;
			double tweet_date = 0;
			TStr TweetStr("");
			TStr TweetStrLc("");

			TStr SourceName("");
			int source_id = -1;

			int rt_idx = -1;
			int min_rt_idx = -1;
			int at_idx = -1;
			int min_at_idx = -1;
			int un_idx = -1;
			int min_un_idx = -1;

			for (row=0; row<rec_count; row++) {
				user_id = TStr(PQgetvalue(res, row, 1)).GetInt();
				TweetStr = PQgetvalue(res, row, 3);
				tweet_date = TStr(PQgetvalue(res, row, 4)).GetFlt();

				TweetStrLc = TweetStr.ToLc();

				// check if a twit is a retweet
				for (int i=0; i<RetweetConventionNmH.Len(); i++) {
					rt_idx = -1;
					at_idx = -1;
					un_idx = -1;
					min_at_idx = -1;
					min_rt_idx = -1;
					min_un_idx = -1;

					const TStr& Convention = RetweetConventionNmH.GetKey(i);

					// we search for the retweet word, and then the closest @username just after the word
					if ( (rt_idx=TweetStrLc.SearchStr(Convention)) > -1 ) {
						at_idx=TweetStr.SearchCh('@', rt_idx+Convention.Len());
						if ( (at_idx-rt_idx-Convention.Len()) <= 2) {
							min_rt_idx = rt_idx;
							min_at_idx = at_idx;
						}
					}

					if (min_at_idx > -1) { // it is a retweet
						// add user to network if we don't have it yet
						if (!RetweetConventionNetwork.IsNode(user_id)) {
							RetweetConventionNetwork.AddNode(user_id,TFltIntPrV());
						}

						// add retweet convention event to node
						RetweetConventionNetwork.GetNDat(user_id).Add(TFltIntPr(tweet_date, RetweetConventionNmH[i]));
					}
				}
			}
			PQclear(res);
		} else {
			rec_count = 0;
		}
	} while (rec_count);

	PQexec(conn, "close mycursor");
	PQexec(conn, "commit work");

	PQfinish(conn);

	printf("%d retweet conventions and %d node retweet convention flows added from %d tweets!\n", RetweetConventionNmH.Len(), RetweetConventionNetwork.GetNodes(), total_number_tweets);
}

void TFNBs::ComputeStationaryFlow(const TStr& StartDate, const TStr& EndDate) {
	double s_time = (double)TSecTm::GetDtTmFromStr(StartDate).GetAbsSecs();
	double e_time = (double)TSecTm::GetDtTmFromStr(EndDate).GetAbsSecs();

	for (TNGraph::TNodeI NI = FollowersNetwork.BegNI(); NI < FollowersNetwork.EndNI(); NI++) {
		if (EventsNetwork.IsNode(NI.GetId())) {
			if (!FlowNetwork.IsNode(NI.GetId())) { FlowNetwork.AddNode(NI.GetId(), 0.0); }
			FlowNetwork.GetNDat(NI.GetId()) = (double)EventsNetwork.GetNDat(NI.GetId()).Len()/(e_time - s_time);
		}

		for (int i=0; i<NI.GetInDeg(); i++) {
			// retweet rate of NI.GetId() from NI.GetInNId(i)
			if (EventsNetwork.IsEdge(NI.GetInNId(i), NI.GetId())) {
				if (!FlowNetwork.IsNode(NI.GetInNId(i))) { FlowNetwork.AddNode(NI.GetInNId(i), 0.0); }
				FlowNetwork.AddEdge(NI.GetInNId(i), NI.GetId(),
									(double)EventsNetwork.GetEDat(NI.GetInNId(i), NI.GetId()).Len()/(e_time - s_time));
				// printf("%d -> %d: %f\n", NI.GetInNId(i), NI.GetId(), (double)EventsNetwork.GetEDat(NI.GetInNId(i), NI.GetId()).Len()/(e_time - s_time));
			}
		}
	}
}


// Omid55

void TFNBs::LoadCascadeOfQuoteFromPostgreSQL(TStr& DesiredQuote)
{
	PGconn *conn;
	PGresult *res;
	int rec_count;
	int row;
	int total_number_tweets = 0;

	bool verbose = false;

	conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");

	if (PQstatus(conn) == CONNECTION_BAD)
	{
		printf("We were unable to connect to the database");
		return;
    }

	// we use cursors/fetch to speed up the process; batch of 10000 tweets
	PQexec(conn, "begin work");

	TStr sql = TStr::Fmt("declare mycursor cursor for select extract(epoch from tweettime) from tweets where tweettext like '%%%s%%' order by tweettime", DesiredQuote.CStr());
	PQexec(conn,sql.CStr());

	do
	{
		res = PQexec(conn, "FETCH 1000000 IN mycursor");
		if (PQresultStatus(res) == PGRES_TUPLES_OK)
		{
			rec_count = PQntuples(res);
			total_number_tweets += rec_count;
			printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);
			double tweet_date = 0;

			for (row=0; row<rec_count; row++)
			{
				tweet_date = TStr(PQgetvalue(res, row, 0)).GetFlt();
				Casc_times.Add(tweet_date);
			}
			PQclear(res);
		}
		else
		{
			rec_count = 0;
		}
	}
	while (rec_count);

	PQexec(conn, "close mycursor");
	PQexec(conn, "commit work");

	PQfinish(conn);

	printf("\n\nDone\n\n");
}

//void TFNBs::LoadCascadeOfQuoteFromPostgreSQL(THash<TUInt,TSecTmV>& result, const THash<TStr,TUInt>& quotesContent, const int &NumUsers, const TStr& StartDate, const TStr& EndDate)
//{
//	printf("\nLoadCascadeOfQuoteFromPostgreSQL function started ...\n\n");
//
//	PGconn *conn;
//	PGresult *res;
//	int rec_count;
//	int row,q;
//	int total_number_tweets = 0;
//
//	conn = PQconnectdb("dbname=twitter host=postgresql01.mpi-sws.org user=twitter password=tweet@84");
//
//	if (PQstatus(conn) == CONNECTION_BAD)
//	{
//		printf("We were unable to connect to the database");
//		return;
//    }
//
//	// we use cursors/fetch to speed up the process; batch of 10000 tweets
//	PQexec(conn, "begin work");
//	if (NumUsers==-1)
//	{
//		PQexec(conn,TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s'", StartDate.CStr(), EndDate.CStr()).CStr());
//	}
//	else
//	{
//		PQexec(conn,TStr::Fmt("declare mycursor cursor for select tweetid, userid, useridreply, tweettext, extract(epoch from tweettime) from tweets where userid < %d and useridreply is null and tweettime >= timestamp '%s' and tweettime < timestamp '%s'", NumUsers, StartDate.CStr(), EndDate.CStr()).CStr());
//	}
//
//	do
//	{
//		res = PQexec(conn, "FETCH 1000000 IN mycursor");
//		if (PQresultStatus(res) == PGRES_TUPLES_OK)
//		{
//			rec_count = PQntuples(res);
//			total_number_tweets += rec_count;
//			printf("Adding %d tweets... (total: %d)\n", rec_count, total_number_tweets);
//
////			int twt_id = -1;
////			int user_id = -1;
//			double tweet_date = 0;
//			TStr TweetStr("");
//			TStr TweetStrLc("");
//			for (row=0; row<rec_count; row++)
//			{
//				printf("Row%d is processing.\n",row);
//
////				twt_id = TStr(PQgetvalue(res, row, 0)).GetInt();
////				user_id = TStr(PQgetvalue(res, row, 1)).GetInt();
//				TweetStr = PQgetvalue(res, row, 3);
//				TweetStrLc = TweetStr.ToLc();
//				tweet_date = TStr(PQgetvalue(res, row, 4)).GetFlt();    // << CHECK HERE >> CHECK IF WE CAN CHANGE IT TO TIME DATE TYPE
//				for(q=0;q<quotesContent.Len();q++)
//				{
//					if (TweetStrLc.SearchStr(quotesContent.GetKey(q)) > -1)
//					{
//						TSecTm td(tweet_date);
//						TUInt id = result.GetKeyId(quotesContent[q]);
//						if(id == -1)
//						{
//							result.AddDat(quotesContent[q]).Add(td);
//						}
//						else
//						{
//							result.GetDat(quotesContent[q]).AddSorted(td);
//						}
//						//Casc_times.Add(tweet_date);
//					}
//				}
//			}
//
//			PQclear(res);
//		}
//		else
//		{
//			rec_count = 0;
//		}
//	}
//	while (rec_count);
//
//	PQexec(conn, "close mycursor");
//	PQexec(conn, "commit work");
//
//	PQfinish(conn);
//
//	printf("\n\nDone\n\n");
//}

// Omid55


// k = 10, s = 8, and gamma = 1
void TFNBs::ComputeBurstLevelEvents(const int& k, const double& s, const double& gamma) {
	int num_nodes_processed = 0;
	bool verbose = false;

	for (TNGraph::TNodeI NI = FollowersNetwork.BegNI(); NI < FollowersNetwork.EndNI(); NI++) {
		TFltV TotalInflowEvents;

		// compute burstiness of own out-flow for NI.GetId()
		if (EventsNetwork.IsNode(NI.GetId())) {
			if (!BurstLevelsEventsNetwork.IsNode(NI.GetId())) { BurstLevelsEventsNetwork.AddNode(NI.GetId(), TFltIntPrV()); }

			EventsNetwork.GetNDat(NI.GetId()).Sort(true);

			TIntV StateLabels;

			LabelBurstAutomaton(EventsNetwork.GetNDat(NI.GetId()), StateLabels, k, s, gamma);

			if (verbose) {
				printf("Out-flow burst levels for node %d computed!\n", NI.GetId());
				TIntH BurstLevelsCount;
				for (int i=0; i<StateLabels.Len(); i++) {
					if (!BurstLevelsCount.IsKey(StateLabels[i])) { BurstLevelsCount.AddDat(StateLabels[i]) = 0; }
					BurstLevelsCount.GetDat(StateLabels[i]) += 1;
				}

				BurstLevelsCount.SortByKey(true);
				for (int i=0; i<BurstLevelsCount.Len(); i++) {
					printf("Level %d: %d events\n", BurstLevelsCount.GetKey(i).Val, BurstLevelsCount[i].Val);
				}
			}

			for (int i=0; i<StateLabels.Len(); i++) {
				BurstLevelsEventsNetwork.GetNDat(NI.GetId()).Add(TFltIntPr(EventsNetwork.GetNDat(NI.GetId())[i], StateLabels[i]));
			}
		}

		// include retweet events in edges, without computing burstiness (too rare events)
		for (int i=0; i<NI.GetInDeg(); i++) {
			// retweet rate of NI.GetId() from NI.GetInNId(i)
			if (BurstLevelsEventsNetwork.IsEdge(NI.GetInNId(i), NI.GetId())) {
				if (!BurstLevelsEventsNetwork.IsNode(NI.GetInNId(i))) { BurstLevelsEventsNetwork.AddNode(NI.GetInNId(i), TFltIntPrV()); }
				BurstLevelsEventsNetwork.AddEdge(NI.GetInNId(i), NI.GetId(), TFltIntPrV());

				for (int j=0; j<EventsNetwork.GetEDat(NI.GetInNId(i), NI.GetId()).Len(); j++) {
					BurstLevelsEventsNetwork.GetEDat(NI.GetInNId(i), NI.GetId()).Add(TFltIntPr(EventsNetwork.GetEDat(NI.GetInNId(i), NI.GetId())[j], 0));
				}
			}
		}

		// compute burstiness of total in-flow for NI.GetId() and store in hash
		BurstLevelsInFlows.AddDat(NI.GetId()) = TFltIntPrV();
		for (int i=0; i<NI.GetInDeg(); i++) {
			for (int j=0; j<EventsNetwork.GetNDat(NI.GetInNId(i)).Len(); j++) {
				TotalInflowEvents.Add(EventsNetwork.GetNDat(NI.GetInNId(i))[j]);
			}
		}
		TotalInflowEvents.Sort(true);

		TIntV StateLabelsInFlow;
		LabelBurstAutomaton(TotalInflowEvents, StateLabelsInFlow, k, s, gamma);

		for (int i=0; i<StateLabelsInFlow.Len(); i++) {
			BurstLevelsInFlows.GetDat(NI.GetId()).Add(TFltIntPr(TotalInflowEvents[i], StateLabelsInFlow[i]));
		}

		if (++num_nodes_processed%(int)1e5==0) {
			printf("%d nodes processed...\n", num_nodes_processed);
		}
	}
}

// I do not know why the first version was recursive; modified to use for (int t=0; t<x.Len(); t++)
void TFNBs::find_C(TFltV &x, TFltVV &C, const int& k, const double& s, const double& gamma, const double& T){
	C = TFltVV(x.Len(), k);

	for (int t=1; t<x.Len(); t++) {
		int n = x.Len() - 1;
		for (int j = 0; j < k; j++){
			double alpha = ( (x.Len() ) / T ) * pow( s, j );
			double term_1 = -log(alpha) + alpha * x[t];
			double term_2 = 0;
			if ( t == 1 ){
				term_2 = j * log(n) * gamma;
			}
			else{
				bool first = false;
				for (int l = 0; l < k; l++){
					double my_val = C(t-1, l);
					if ( j > l ) my_val += (j - l) * log(n) * gamma;
					if ( !first || my_val < term_2 ){
						term_2 = my_val;
						first = true;
					}
				}
			}
			C( t, j ) = term_1 + term_2;
		}
	}
}

void TFNBs::find_min_state(TFltVV &C, TIntV &states, const int& k, const double& s, const double& gamma, const double& T){
	states = TIntV( C.GetRows() );
	states[0] = 0;
	int n = C.GetRows() - 1;
	for (int t = C.GetRows() - 1; t > 0; t --){
		double best_val = 0;
		int best_state = -1;
		for (int j = 0; j < C.GetCols(); j++){
			double c_state = C( t, j );
			if ( t < C.GetRows() - 2 && states[t+1] > j ){
				c_state += ( states[t+1] - j ) * gamma * log(n);
			}
			if ( best_state == -1 || best_val > c_state ){
				best_state = j;
				best_val = c_state;
			}
		}
		states[t] = best_state;
	}
}

// k = 10, s = 8, and gamma = 1
void TFNBs::LabelBurstAutomaton(TFltV& EventTimes, TIntV &state_labels, const int& k, const double& s, const double& gamma){
	if ( EventTimes.Len() < 2 ) return;

	TFltV x;
	x.Add( 0 );
	double T = EventTimes.Last().Val - EventTimes[0].Val;
	for (int i = 1; i < EventTimes.Len(); i++){
		x.Add(EventTimes[i] - EventTimes[i-1]);
	}
	TFltVV Cost_matrix;

	find_C(x, Cost_matrix, k, s, gamma, T);

	find_min_state(Cost_matrix, state_labels, k, s, gamma, T);
}

void TFNBs::GenCascade(TCascade& C, const double& beta, const double& thr, const int& no_time) {
	bool verbose = false;
	TIntFltH InfectedNIdH; TIntH InfectedBy;
	double GlobalTime;
	int StartNId;

	if (FlowNetwork.GetNodes() == 0)
		return;

	// set random seed
	TFlt::Rnd.Randomize();

	// set window if given through argument
	while (C.Len() < 1) {
		C.Clr();
		InfectedNIdH.Clr();
		InfectedBy.Clr();

		GlobalTime = 0.0; // all cascades start at 0.0

		StartNId = FlowNetwork.GetRndNId();

		InfectedNIdH.AddDat(StartNId) = GlobalTime;

		while (true) {
			// sort by time & get the oldest node that did not run infection
			InfectedNIdH.SortByDat(true);
			const int& NId = InfectedNIdH.BegI().GetKey();
			GlobalTime = InfectedNIdH.BegI().GetDat();

			// all the nodes has run infection
			if ( GlobalTime >= TFlt::Mx )
				break;

			// add current oldest node to the network and set its time
			C.Add(NId, GlobalTime);

			if (verbose) { printf("GlobalTime:%f, infected node:%d\n", GlobalTime, NId); }

			// run infection from the current oldest node
			TFltFltNet::TNodeI NI = FlowNetwork.GetNI(NId);
			for (int e = 0; e < NI.GetOutDeg(); e++) {
				const int DstNId = NI.GetOutNId(e);

				// not infecting the parent
				if (InfectedBy.IsKey(NId) && InfectedBy.GetDat(NId).Val == DstNId) { continue; }

				double sigmaT = TFlt::Mx;
				double beta_current = beta;
				double in_flow = InFlowPerNode.GetDat(DstNId);

				// retweet probability based on flow (tweets/hour)
				if (in_flow > thr) { beta_current *= pow(thr/in_flow, 0.65); }

				if (verbose) { printf("Attempt -> Node:%d, in_flow:%f, thr:%f, beta:%f\n", DstNId, in_flow, thr, beta_current); }

				if (TFlt::Rnd.GetUniDev() > beta_current) { continue; }

				// retweet delay based on flow (tweets/hour)
				if (no_time==1) { sigmaT = 1; }
				else {
					int idx = 0;
					while (idx<RetweetDelayCdfInflow.Len() && (double)RetweetDelayCdfInflow.GetKey(idx).Val < in_flow) { idx++; }

					if (idx==RetweetDelayCdfInflow.Len()) { idx--; }

					if (verbose) { printf("Retweet delay in-flow %f < %d\n", in_flow, RetweetDelayCdfInflow.GetKey(idx).Val); }

					int t = 0; double rt = TFlt::Rnd.GetUniDev();
					while (t<RetweetDelayCdfInflow[idx].Len() && rt > RetweetDelayCdfInflow[idx][t].Val2) { t++; }

					if (t==RetweetDelayCdfInflow[idx].Len()) { t--; }

					if (verbose) { printf("Delay %f\n", RetweetDelayCdfInflow[idx][t].Val1.Val); }

					sigmaT = RetweetDelayCdfInflow[idx][t].Val1;
				}

				IAssert(sigmaT >= 0);

				double t1 = GlobalTime + sigmaT;

				if (InfectedNIdH.IsKey(DstNId)) {
					double t2 = InfectedNIdH.GetDat(DstNId);
					if ( t2 > t1 && t2 != TFlt::Mx ) {
						InfectedNIdH.GetDat(DstNId) = t1;
						InfectedBy.GetDat(DstNId) = NId;
					}
				} else {
					InfectedNIdH.AddDat(DstNId) = t1;
					InfectedBy.AddDat(DstNId) = NId;
				}
			}

			// we cannot delete key (otherwise, we cannot sort), so we assign a big time (InitTime + window cut-off)
			InfectedNIdH.GetDat(NId) = TFlt::Mx;
		}
    }

	C.Sort();
}
