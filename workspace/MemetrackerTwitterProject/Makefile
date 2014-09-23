# modified by Omid55

#
# Makefile for non-Microsoft compilers
#

## Linux  (uncomment the 2 lines below for compilation on Linux)
CXXFLAGS += -std=c++98 -Wall
LDFLAGS += 

## CygWin (uncomment the 2 lines below for compilation on CygWin)
#CXXFLAGS += -Wall
#LDFLAGS += 

MAIN = find_all_memes_cascades

omid_opt_linux: CXXFLAGS += -O4
omid_opt_linux: LDFLAGS += -lrt -O4     # -ggdb 	 # for enabling the debugging mode in Eclipse
omid_opt_linux: $(MAIN) plot_hist_centered_memes_cascades create_quotes_news_blogs_justfirst justchecktweettimes add_novisited_real_urls plot_individually_centered_memes_cascade plot_individually_centered_both_cascades filter_peaks_by_nifty_apply_both search_post_in_memetracker_files plot_cascade_no_centeralized plot_one_quote_cascade plot_hist_centered_both_cascades filter_peaks_by_nifty_apply_memes set_range_for_quotes_cascades plotccdf_memes_twittercontents_withhist plotccdf_memes_twitterurls_withhist plotccdf_memes_twitter select_and_save_quotes_cascaded_both plot_centered_memes_cascade save_cascades_for_matlab find_cascades_of_quotes_with_trie TestTrieLargely mytrie_testing find_cascades_of_quotes_in_urls find_posts_propagated_over_twitter pack_twitter_real_urls separate_raw_urls_print_statistics separate_raw_urls save_all_urls_separately find_cascades_of_quotes find_cascades_of_quotes_separately check_tweets_length create_network find_tweet_raw_urls separately_search_quotes_content_over_twitter_files separate_quotes_contents preprocessing_quotes splitup_quotes creating_other_infos find_all_memes_cascades insert_memes_quotes_cascade_intodb subseting_quotes_cascades


sws: CXXFLAGS += -O4
sws: LDFLAGS += -lrt -O4     # -ggdb
sws: $(MAIN) filter_peaks_by_nifty_apply_both create_quotes_news_blogs_justfirst plotccdf_memes_twitter			justchecktweettimes find_cascades_of_quotes add_novisited_real_urls find_cascades_of_quotes_with_trie find_cascades_of_quotes_separately find_tweet_raw_urls find_posts_propagated_over_twitter save_all_urls_separately check_tweets_length create_network


mpi: CXXFLAGS += -O4
mpi: LDFLAGS += -lrt -O4     # -ggdb
mpi: $(MAIN) plot_hist_centered_memes_cascades plot_individually_centered_memes_cascade plot_individually_centered_both_cascades create_quotes_news_blogs_justfirst find_all_memes_cascades filter_peaks_by_nifty_apply_both search_post_in_memetracker_files plot_cascade_no_centeralized plot_one_quote_cascade plot_hist_centered_both_cascades filter_peaks_by_nifty_apply_memes set_range_for_quotes_cascades plotccdf_memes_twittercontents_withhist plotccdf_memes_twitterurls_withhist plotccdf_memes_twitter select_and_save_quotes_cascaded_both plot_centered_memes_cascade save_cascades_for_matlab TestTrieLargely mytrie_testing find_cascades_of_quotes_in_urls pack_twitter_real_urls separate_raw_urls_print_statistics separate_raw_urls separately_search_quotes_content_over_twitter_files separate_quotes_contents preprocessing_quotes splitup_quotes creating_other_infos insert_memes_quotes_cascade_intodb subseting_quotes_cascades 	# create_network

# COMPILE

justchecktweettimes: justchecktweettimes.cpp Snap.o 
	g++ -o justchecktweettimes justchecktweettimes.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu -Wl,-Bsymbolic-functions -Wl,-z,relro -I/usr/include/postgresql -lsqlite3 -lpq -Wno-write-strings $(LDFLAGS)

search_post_in_memetracker_files: search_post_in_memetracker_files.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o search_post_in_memetracker_files search_post_in_memetracker_files.cpp snap/memes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)

filter_peaks_by_nifty_apply_memes: filter_peaks_by_nifty_apply_memes.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o
	g++ -o filter_peaks_by_nifty_apply_memes filter_peaks_by_nifty_apply_memes.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)
	
filter_peaks_by_nifty_apply_both: filter_peaks_by_nifty_apply_both.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o
	g++ -o filter_peaks_by_nifty_apply_both filter_peaks_by_nifty_apply_both.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)
		
set_range_for_quotes_cascades: set_range_for_quotes_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o set_range_for_quotes_cascades set_range_for_quotes_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)
	
plotccdf_memes_twittercontents_withhist: plotccdf_memes_twittercontents_withhist.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o plotccdf_memes_twittercontents_withhist plotccdf_memes_twittercontents_withhist.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)
	
plotccdf_memes_twitterurls_withhist: plotccdf_memes_twitterurls_withhist.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o plotccdf_memes_twitterurls_withhist plotccdf_memes_twitterurls_withhist.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)
	
plotccdf_memes_twitter: plotccdf_memes_twitter.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o plotccdf_memes_twitter plotccdf_memes_twitter.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)
	
select_and_save_quotes_cascaded_both: select_and_save_quotes_cascaded_both.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o select_and_save_quotes_cascaded_both select_and_save_quotes_cascaded_both.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

plot_cascade_no_centeralized: plot_cascade_no_centeralized.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o plot_cascade_no_centeralized plot_cascade_no_centeralized.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

plot_individually_centered_both_cascades: plot_individually_centered_both_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o plot_individually_centered_both_cascades plot_individually_centered_both_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

plot_one_quote_cascade: plot_one_quote_cascade.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o plot_one_quote_cascade plot_one_quote_cascade.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)

plot_hist_centered_both_cascades: plot_hist_centered_both_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o plot_hist_centered_both_cascades plot_hist_centered_both_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

plot_hist_centered_memes_cascades: plot_hist_centered_memes_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o plot_hist_centered_memes_cascades plot_hist_centered_memes_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

plot_centered_memes_cascade: plot_centered_memes_cascade.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o plot_centered_memes_cascade plot_centered_memes_cascade.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

plot_individually_centered_memes_cascade: plot_individually_centered_memes_cascade.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o plot_individually_centered_memes_cascade plot_individually_centered_memes_cascade.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

create_quotes_news_blogs_justfirst: create_quotes_news_blogs_justfirst.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o create_quotes_news_blogs_justfirst create_quotes_news_blogs_justfirst.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

save_cascades_for_matlab: save_cascades_for_matlab.cpp TStrTrie.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o save_cascades_for_matlab save_cascades_for_matlab.cpp TStrTrie.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

find_cascades_of_quotes_with_trie: find_cascades_of_quotes_with_trie.cpp TStrTrie.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o
	g++ -o find_cascades_of_quotes_with_trie find_cascades_of_quotes_with_trie.cpp TStrTrie.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -I/usr/include/postgresql -lsqlite3 -lpq -Wno-write-strings $(LDFLAGS)

mytrie_testing: mytrie_testing.cpp TStrTrie.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o mytrie_testing mytrie_testing.cpp TStrTrie.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

TestTrieLargely: TestTrieLargely.cpp TStrTrie.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o TestTrieLargely TestTrieLargely.cpp TStrTrie.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

pack_twitter_real_urls: pack_twitter_real_urls.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o pack_twitter_real_urls pack_twitter_real_urls.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu -Wl,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

separate_raw_urls: separate_raw_urls.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o separate_raw_urls separate_raw_urls.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu -Wl,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

separate_raw_urls_print_statistics: separate_raw_urls_print_statistics.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o separate_raw_urls_print_statistics separate_raw_urls_print_statistics.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu -Wl,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

save_all_urls_separately: save_all_urls_separately.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o save_all_urls_separately save_all_urls_separately.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu -lcurl -Wl,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

add_novisited_real_urls: add_novisited_real_urls.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o add_novisited_real_urls add_novisited_real_urls.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu -lcurl -Wl,-Bsymbolic-functions -Wl,-z,relro -Wno-write-strings $(LDFLAGS)

save_tweets_batchly: save_tweets_batchly.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o save_tweets_batchly save_tweets_batchly.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)

find_cascades_of_quotes: find_cascades_of_quotes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o find_cascades_of_quotes find_cascades_of_quotes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -I/usr/include/postgresql -lsqlite3 -lpq -Wno-write-strings $(LDFLAGS)

separate_quotes_contents: separate_quotes_contents.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o separate_quotes_contents separate_quotes_contents.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)

find_cascades_of_quotes_separately: find_cascades_of_quotes_separately.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o find_cascades_of_quotes_separately find_cascades_of_quotes_separately.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -I/usr/include/postgresql -lsqlite3 -lpq -Wno-write-strings $(LDFLAGS)

find_tweet_raw_urls: find_tweet_raw_urls.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o 
	g++ -o find_tweet_raw_urls find_tweet_raw_urls.cpp TwitterUrl.cpp CascadeElement.cpp Tools.cpp Snap.o -I./glib -I./snap -L/usr/lib/x86_64-linux-gnu -Wl,-Bsymbolic-functions -Wl,-z,relro -I/usr/include/postgresql -lsqlite3 -lpq -Wno-write-strings $(LDFLAGS)

create_network: create_network.cpp snap/kronecker.cpp eventinf.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o create_network create_network.cpp eventinf.cpp snap/kronecker.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap  -I/usr/include/postgresql -lsqlite3 -lpq -Wno-write-strings $(LDFLAGS)

check_tweets_length: check_tweets_length.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o check_tweets_length check_tweets_length.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -I/usr/include/postgresql -lsqlite3 -lpq -Wno-write-strings $(LDFLAGS)

find_posts_propagated_over_twitter: find_posts_propagated_over_twitter.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o find_posts_propagated_over_twitter find_posts_propagated_over_twitter.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -I/usr/include/postgresql -lsqlite3 -lpq -Wno-write-strings $(LDFLAGS)

find_cascades_of_quotes_in_urls: find_cascades_of_quotes_in_urls.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o find_cascades_of_quotes_in_urls find_cascades_of_quotes_in_urls.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)

save_all_tweets: save_all_tweets.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o 
	g++ -o save_all_tweets save_all_tweets.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)

separately_search_quotes_content_over_twitter_files: separately_search_quotes_content_over_twitter_files.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o
	g++ -o separately_search_quotes_content_over_twitter_files separately_search_quotes_content_over_twitter_files.cpp  TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)	
	
insert_memes_quotes_cascade_intodb: insert_memes_quotes_cascade_intodb.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o
	g++ -o insert_memes_quotes_cascade_intodb insert_memes_quotes_cascade_intodb.cpp snap/memes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -I/usr/include/mysql -I/usr/include/mysql++ -lmysqlpp -Wno-write-strings $(LDFLAGS)	
	
find_all_memes_cascades: find_all_memes_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o
	g++ -o find_all_memes_cascades find_all_memes_cascades.cpp snap/memes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)	

creating_other_infos: creating_other_infos.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o
	g++ -o creating_other_infos creating_other_infos.cpp snap/memes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)	
	
creating_volumes_memes: creating_volumes_memes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o
	g++ -o creating_volumes_memes creating_volumes_memes.cpp snap/memes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)	

plotting_memes_cascades: plotting_memes_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o
	g++ -o plotting_memes_cascades plotting_memes_cascades.cpp  TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)	
	
splitup_quotes: splitup_quotes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o
	g++ -o splitup_quotes splitup_quotes.cpp  TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)	
	
preprocessing_quotes: preprocessing_quotes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o
	g++ -o preprocessing_quotes preprocessing_quotes.cpp  TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)	
						
subseting_quotes_cascades: subseting_quotes_cascades.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o
	g++ -o subseting_quotes_cascades subseting_quotes_cascades.cpp  snap/memes.cpp TwitterUrl.cpp CascadeElement.cpp Snap.o -I./glib -I./snap -Wno-write-strings $(LDFLAGS)


Snap.o:
	g++ -c $(CXXFLAGS) ./snap/Snap.cpp -I./glib -I./snap

clean:
	rm -f   $(MAIN) Snap.o  $(MAIN).exe generate_nets.exe
