//Omid55
#include "stdafx.h"
#include "snap/memes.h"

THash< TChA , TUInt > posts;  // for each quote what is the cascade times in memetracker dataset
TUInt posts_cnt = 0;

THash< TStr , CascadeElementV > quotes;  // for each quote what is the cascade times in memetracker dataset

void SaveAll()
{
	// Saving Quotes
	TZipOut Zquotes("QuotesData.rar");
	quotes.Save(Zquotes);

	// Saving Posts
	TZipOut Zposts("PostsData.rar");
	posts.Save(Zposts);
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


int main(int argc, char* argv[])
{
	// FOR CHECKING POSTS
//	posts.GetDat(posts.GetKey(id)) == id

//	printf("Starting the Find All Memes Cascades code...\n\n");
//
//	TZipIn ZpostsIn("PostsData.rar");
//	posts.Load(ZpostsIn);
//	printf("posts loading done, it contains %d posts.\n",posts.Len());
//	for(int i=0;i<100;i++)
//	{
//		printf("%s <- %d\n",posts.GetKey(i).CStr(),posts[i]);
//	}
//	return 0;

//	TZipIn ZquotesIn("QuotesHashtable.rar");
//	quotes.Load(ZquotesIn);
//	// printing bunch of stuff just for checking
//	for(int i=0;i<quotes.Len();i++)
//	{
//		if(quotes[i].Len()<2)
//		{
//			continue;
//		}
//		for(int j=0;j<quotes[i].Len();j++)
//		{
//			printf("%d,%d: %s\n",i,j,quotes[i][j].time.GetYmdTmStr().CStr());
//		}
//	}
//	printf("\nSize is: %d\n",quotes.Len());

	TExeTm ExeTm;
	unsigned long long quotesTotalCount = 0;
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nGenerate cascades from memetracker. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

///		int proc = 0;
///		int LEN = 1000;

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
			TMemesDataLoader loader(filefullpath);
			while(loader.LoadNext())     ///while(loader.LoadNext() && proc<LEN)
			{
///				proc++;
				for(int i=0;i<loader.MemeV.Len();i++)
				{
					TStr quoteLC = loader.MemeV[i].ToLc();
					quotesTotalCount++;
					TUInt iddd = quotes.GetKeyId(quoteLC);
					if(iddd == -1)
					{
						quotes.AddDat(quoteLC).Add(CascadeElement(loader.PostUrlStr,loader.PubTm,posts));
					}
					else
					{
						bool notAdded = false;     // this post before added for this quote or not
						CascadeElementV* v = &quotes.GetDat(quoteLC);
						CascadeElement elem = CascadeElement(loader.PostUrlStr,loader.PubTm,posts);

//						// if you want to have all cascades even exactly equal ones, then comment this part
//						for(int j=0;j<(*v).Len();j++)
//						{
//							if((*v)[j].post == elem.post)
//							{
//								notAdded = true;
//								break;
//							}
//						}
//						if(notAdded)
//						{
//							continue;
//						}

						for(int j=0;j<loader.LinkV.Len();j++)
						{
							TUInt id = posts.GetKeyId(loader.LinkV[j]);
							if(id != -1)
							{
								for(int k=0;k<v->Len();k++)
								{
									if(id == (*v)[k].post)
									{
										elem.explicit_links.Add((*v)[k].post);
									}
								}
							}
						}

						v->AddSorted(elem);
					}
				}
			}
///			if(proc>=LEN)
///			{
///				break;
///			}
		}

		printf("\n\nquotesTotalCount: %llu\n", quotesTotalCount);
		cout << "QuotesTotalCount: " << quotesTotalCount << endl << endl;

		SaveAll();
	}
	catch(exception& ex)
	{
		SaveAll();
		printf("\nError1 happened, it was: %s\n\n",ex.what());
	}
	catch(TPt<TExcept>& ex)
	{
		SaveAll();
		printf("\nError2 happened: %s\n\n",ex[0].GetStr().CStr());
	}

///	// printing bunch of stuff just for checking
///	for(int i=0;i<quotes.Len();i++)
///	{
///		if(quotes[i].Len()>2)
///		{
///			for(int j=0;j<quotes[i].Len();j++)
///			{
///				printf("%d,%d: %s\n",i,j,quotes[i][j].time.GetYmdTmStr().CStr());
///			}
///		}
///	}
///	printf("\nSize is: %d\n",quotes.Len());


	printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
	return 0;
}
