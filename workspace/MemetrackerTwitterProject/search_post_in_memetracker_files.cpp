/*
 * search_post_in_memetracker_files.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: omid55
 */
//Omid55
#include "stdafx.h"
#include "snap/memes.h"

int main(int argc, char* argv[])
{
	TExeTm ExeTm;
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nGenerate cascades from memetracker. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

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
			while(loader.LoadNext())
			{
				if(loader.PostUrlStr == "http://elbo.ws/artist/sufjan-stevens")
				{
					cout << "Post: " << loader.PostUrlStr.CStr() << endl;
					cout << "Time: " << loader.PubTm.GetYmdTmStr().CStr() << endl;
					for(int o=0;o<loader.MemeV.Len();o++)
					{
						cout << "Quote" << o << ": " << loader.MemeV[o].CStr() << endl;
					}
					return 0;
				}
			}
		}
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
