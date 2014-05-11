% Omid55
%% Prepare data from csv files to Cascades Data mat

%path = '/is/ei/oaskaris/Downloads/stochastic-network-inference/';
path = '';


%% All of quotes' cascades over Memes
Quotes = GiveTheMatrix([path 'MEMES_QuotesContent.csv'],0);
MemesWebs = GiveTheMatrix([path 'MEMES_MemesCascadesWebs.csv'],1);
MemesTimes = GiveTheMatrix([path 'MEMES_MemesCascadesTimes.csv'],1);
MemesExternalLinks = cell(length(Quotes),1);
data = importdata([path 'MEMES_MemesExternalLinks.csv']);
cnt = 1; 
for i = 1 : length(data)            
    if data(i,1) == -1
        cnt = cnt + 1;
        continue;
    end
    MemesExternalLinks{cnt} = [MemesExternalLinks{cnt}; data(i,:)];
end
save([num2str(length(Quotes)) 'QuotesOverMemes'],'Quotes','MemesWebs','MemesTimes','MemesExternalLinks');


%% Quotes' cascades over Memes and its content over Twitter 
Quotes = GiveTheMatrix([path 'MEMES_TWITTER_TXT_QuotesContent.csv'],0);
MemesWebs = GiveTheMatrix([path 'MEMES_TWITTER_TXT_MemesCascadesWebs.csv'],1);
MemesTimes = GiveTheMatrix([path 'MEMES_TWITTER_TXT_MemesCascadesTimes.csv'],1);
TwitterTextTimes = GiveTheMatrix([path 'MEMES_TWITTER_TXT_TwitterTextCascades.csv'],1);
MemesExternalLinks = cell(length(Quotes),1);
data = importdata([path 'MEMES_TWITTER_TXT_MemesExternalLinks.csv']);
cnt = 1; 
for i = 1 : length(data)            
    if data(i,1) == -1
        cnt = cnt + 1;
        continue;
    end
    MemesExternalLinks{cnt} = [MemesExternalLinks{cnt}; data(i,:)];
end
save([num2str(length(Quotes)) 'QuotesOverMemesTwitterText'],'Quotes','MemesWebs','MemesTimes','TwitterTextTimes','MemesExternalLinks');


%% Quotes' cascades over Memes and its urls over Twitter 
Quotes = GiveTheMatrix([path 'MEMES_TWITTER_URL_QuotesContent.csv'],0);
MemesWebs = GiveTheMatrix([path 'MEMES_TWITTER_URL_MemesCascadesWebs.csv'],1);
MemesTimes = GiveTheMatrix([path 'MEMES_TWITTER_URL_MemesCascadesTimes.csv'],1);
TwitterUrlTimes = GiveTheMatrix([path 'MEMES_TWITTER_URL_TwitterUrlCascades.csv'],1);
MemesExternalLinks = cell(length(Quotes),1);
data = importdata([path 'MEMES_TWITTER_URL_MemesExternalLinks.csv']);
cnt = 1; 
for i = 1 : length(data)            
    if data(i,1) == -1
        cnt = cnt + 1;
        continue;
    end
    MemesExternalLinks{cnt} = [MemesExternalLinks{cnt}; data(i,:)];
end
save([num2str(length(Quotes)) 'QuotesOverMemesTwitterUrls'],'Quotes','MemesWebs','MemesTimes','TwitterUrlTimes','MemesExternalLinks');


%% Quotes' cascades over Memes and its content and urls (both) over Twitter 
Quotes = GiveTheMatrix([path 'TRIPLE_QuotesContent.csv'],0);
MemesWebs = GiveTheMatrix([path 'TRIPLE_MemesCascadesWebs.csv'],1);
MemesTimes = GiveTheMatrix([path 'TRIPLE_MemesCascadesTimes.csv'],1);
TwitterUrlTimes = GiveTheMatrix([path 'TRIPLE_TwitterUrlCascades.csv'],1);
TwitterTextTimes = GiveTheMatrix([path 'TRIPLE_TwitterTextCascades.csv'],1);
MemesExternalLinks = cell(length(Quotes),1);
data = importdata([path 'TRIPLE_MemesExternalLinks.csv']);
cnt = 1; 
for i = 1 : length(data)            
    if data(i,1) == -1
        cnt = cnt + 1;
        continue;
    end
    MemesExternalLinks{cnt} = [MemesExternalLinks{cnt}; data(i,:)];
end
save([num2str(length(Quotes)) 'QuotesOverTripleTogether'],'Quotes','MemesWebs','MemesTimes','TwitterTextTimes','TwitterUrlTimes','MemesExternalLinks');


print "ALL DONE";


