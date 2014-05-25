//Omid55
// Code for finding the cascades of quotes(memes) over Memetracker dataset (txt files)
#include "stdafx.h"
#include "snap/memes.h"
#include <string>
// RESULTS
// We have 393118898 quotes in total. 130964205 unique quotes and 88850024 posts in this period.
// RESULTS

THash< TChA , TUInt > posts;  // for each quote what is the cascade times in memetracker dataset
THash< TStr , CascadeElementV > quotes;  // for each quote what is the cascade times in memetracker dataset

void SaveAll()
{
	// Saving Quotes
	TZipOut Zquotes("QuotesData.rar");
	quotes.Save(Zquotes);
	printf("QuotesData is saved and it has %d items.",quotes.Len());

	// Saving Posts
	TZipOut Zposts("PostsData.rar");
	posts.Save(Zposts);
	printf("PostsData is saved and it has %d items.",posts.Len());
}


int main(int argc, char* argv[])
{
//	// For checking quotes in QuotesData
//	int selected = atoi(argv[1]);
//	TZipIn z("lastData/QuotesData.rar");
//	quotes.Load(z);
//	printf("QuotesData is loaded and it has %d items.",quotes.Len());
//
//	TStr selectedQuote = quotes.GetKey(selected);
//	cout << "\n\nQuote: " << selectedQuote.CStr() << endl;
//	cout << "\n\nCascade1:" << endl;
//	for(int i=0;i<quotes[selected].Len();i++)
//	{
//		cout << "t" << i << ": " << quotes[selected][i].time.GetYmdTmStr().CStr() << endl;
//	}
//	quotes.Clr();
//	cout << "\n\n\n";
//
//	TSecTmV casc;
//	for(int year=2008;year<2010;year++)
//	{
//		int month = 8;
//		int end = 13;
//		if(year==2009)
//		{
//			month = 1;
//			end = 10;
//		}
//		for(;month<end;month++)
//		{
//			TStr filefullpath = TStr::Fmt("/agbs/datasets/memetracker/memes2_%d-%02i.txt.rar",year,month);    // like memes2_2009-06.txt.rar
//			TMemesDataLoader loader(filefullpath);
//			while(loader.LoadNext())
//			{
//				for(int i=0;i<loader.MemeV.Len();i++)
//				{
//					TStr quoteLC = loader.MemeV[i].ToLc();
//					if(selectedQuote.EqI(quoteLC))
//					{
//						casc.AddSorted(loader.PubTm);
//					}
//				}
//			}
//		}
//	}
//
//	cout << "\n\nCascade2:" << endl;
//	for(int i=0;i<casc.Len();i++)
//	{
//		cout << "t" << i << ": " << casc[i].GetYmdTmStr().CStr() << endl;
//	}
//	cout << "\n\nDONE" << endl;
//	return 0;

//	// For checking Memetracker loader file
//	int desired = atoi(argv[1]);
//	printf("Check starts ...\n");
//	for(int year=2008;year<2010;year++)
//	{
//		int month = 8;
//		int end = 13;
//		if(year==2009)
//		{
//			month = 1;
//			end = 10;
//		}
//		for(;month<end;month++)
//		{
//			TStr filefullpath = TStr::Fmt("/agbs/datasets/memetracker/memes2_%d-%02i.txt.rar",year,month);
//			printf("File path is: %s\n",filefullpath.CStr());
//		}
//	}
//	printf("Done1\n\n\n\n");
//
//	TStr filefullpath = TStr::Fmt("/agbs/datasets/memetracker/memes2_%d-%02i.txt.rar",2008,10);
//	fstream f("/is/ei/oaskaris/Downloads/memetrackerdata/memes_2008-10.txt",ios::in);
//	string line;
//	int p = 0;
//	while(p <= desired)
//	{
//		getline(f,line);
//		if(line.length()==0 || line[0]=='\n')
//		{
//			p++;
//		}
//		if(p == desired)
//		{
//			printf("%s\n",line.c_str());
//		}
//	}
//
//	TMemesDataLoader loader(filefullpath);
//	p = 0;
//	while(loader.LoadNext())
//	{
//		if(p == desired)
//		{
//			printf("\n\nPost: %s\nDateTime: %s\n",loader.PostUrlStr.CStr(),loader.PubTm.GetYmdTmStr().CStr());
//			for(int i=0;i<loader.MemeV.Len();i++)
//			{
//				printf("Quote: %s\n", loader.MemeV[i].CStr());
//			}
//			for(int i=0;i<loader.LinkV.Len();i++)
//			{
//				printf("Link: %s\n", loader.LinkV[i].CStr());
//			}
//		}
//		else if(p>desired)
//		{
//			break;
//		}
//		p++;
//	}
//	printf("Done3");
//	return 0;

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
		Env.PrepArgs(TStr::Fmt("\n((( Generate Cascades From Memetracker Dataset )))  build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		for(int year=2008;year<2010;year++)
		{
			int month = 8;
			int end = 13;
			if(year==2009)
			{
				month = 1;
				end = 10;
			}
			for(;month<end;month++)
			{
				TStr filefullpath = TStr::Fmt("/agbs/datasets/memetracker/memes2_%d-%02i.txt.rar",year,month);    // like memes2_2009-06.txt.rar
				TMemesDataLoader loader(filefullpath);
				while(loader.LoadNext())
				{
					for(int i=0;i<loader.MemeV.Len();i++)
					{
						TStr quoteLC = loader.MemeV[i].ToLc();
						quotesTotalCount++;
						int iddd = quotes.GetKeyId(quoteLC);
						if(iddd == -1)
						{
							quotes.AddDat(quoteLC).Add(CascadeElement(loader.PostUrlStr,loader.PubTm,posts));
						}
						else
						{
	//						bool notAdded = false;     // this post before added for this quote or not
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
			}
		}

		printf("\n\nQuotesTotalCount: %llu\n", quotesTotalCount);

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
