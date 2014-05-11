/*
 * Tools.cpp
 *
 *  Created on: May 1, 2014
 *      Author: omid55
 */
// Omid55
#include "Tools.h"

double* Tools::calculateHistOfCascade(TSecTmV& cascade,int rbegin, uint rperiod, int length, bool normalized)
{
	int i,index;
	double* volz = new double[length];
	for(i=0;i<length;i++)
	{
		volz[i] = 0;
	}
	for(i=0;i<cascade.Len();i++)
	{
		index = floor(((double)cascade[i].GetAbsSecs() - (double)rbegin) / (double)rperiod);
		if(index >= length || index < 0)
		{
			continue;
		}
		volz[index]++;
	}
	if(normalized)
	{
		double max = 0;
		for(i=0;i<length;i++)
		{
			if(volz[i] > max)
			{
				max = volz[i];
			}
		}
		if(max != 0)
		{
			for(i=0;i<length;i++)
			{
				volz[i] /= max;
			}
		}
	}
	return volz;
}

void Tools::separateTimestepsOfQuotesInBlogsNews(THash< TStr,CascadeElementV >& quotes, THash<TStr,TUInt>& newsMedia, THash<TChA,TUInt>& posts, THash<TStr,CascadeElementV>& newsQuotesOutput, THash<TStr,CascadeElementV>& blogsQuotesOutput)
{
	for(int i=0;i<quotes.Len();i++)
	{
		if(i % (int)floor(quotes.Len()/100) == 0)
		{
			int percent = i / floor(quotes.Len()/100);
			printf("Separating: %d percent\n", percent);
		}
		CascadeElementV blogcasc,newscasc;
		for(int j=0;j<quotes[i].Len();j++)
		{
			int found = newsMedia.GetKeyId(TStrUtil::GetWebsiteNm(posts.GetKey(quotes[i][j].post)));
			if(found == -1)
			{
				blogcasc.Add(quotes[i][j]);
			}
			else
			{
				newscasc.Add(quotes[i][j]);
			}
		}
		blogsQuotesOutput.AddDat(quotes.GetKey(i),blogcasc);
		newsQuotesOutput.AddDat(quotes.GetKey(i),newscasc);
	}
}

void Tools::removeOtherTimestepsOfQuotesWithSameDomain(THash<TStr,CascadeElementV>& quotes, THash<TChA,TUInt>& posts, THash<TStr,CascadeElementV>& outputQuotes)
{
	for(int i=0;i<quotes.Len();i++)
	{
		THash<TStr,TUInt> doms;
		CascadeElementV casc;
		for(int j=0;j<quotes[i].Len();j++)
		{
			TStr dom = TStrUtil::GetWebsiteNm(posts.GetKey(quotes[i][j].post));
			if(doms.GetKeyId(dom) == -1)
			{
				doms.AddDat(dom);
				casc.Add(quotes[i][j]);
			}
		}
		outputQuotes.AddDat(quotes.GetKey(i),casc);
	}
}

int Tools::countNoneZeros(double* v, int len)
{
	int cnt = 0;
	for(int i=0;i<len;i++)
	{
		if(v[i] != 0)
		{
			cnt++;
		}
	}
	return cnt;
}

double* Tools::calculateHistOfCascade(TIntV& cascade, int rbegin, uint rperiod, int length, bool normalized)
{
	int i,index;
	double* vols = new double[length];
	for(i=0;i<length;i++)
	{
		vols[i] = 0;
	}
	for(i=0;i<cascade.Len();i++)
	{
		index = floor(((double)cascade[i] - (double)rbegin) / rperiod);
		if(index >= length || index < 0)
		{
			continue;
		}
		vols[index]++;
	}
	if(normalized)
	{
		double max = 0;
		for(i=0;i<length;i++)
		{
			if(vols[i] > max)
			{
				max = vols[i];
			}
		}
		if(max != 0)
		{
			for(i=0;i<length;i++)
			{
				vols[i] /= max;
			}
		}
	}
	return vols;
}

double* Tools::calculateHistOfCascade(CascadeElementV& cascade, int rbegin, uint rperiod, int length, bool normalized)
{
	int i,index;
	double* vols = new double[length];
	for(i=0;i<length;i++)
	{
		vols[i] = 0;
	}
	for(i=0;i<cascade.Len();i++)
	{
		index = floor(((double)cascade[i].time.GetAbsSecs() - (double)rbegin) / rperiod);
		if(index >= length || index < 0)
		{
			continue;
		}
		vols[index]++;
	}
	if(normalized)
	{
		double max = 0;
		for(i=0;i<length;i++)
		{
			if(vols[i] > max)
			{
				max = vols[i];
			}
		}
		if(max != 0)
		{
			for(i=0;i<length;i++)
			{
				vols[i] /= max;
			}
		}
	}
	return vols;
}

int Tools::getMaxIndex(double* d,int len)
{
	double max = -999;
	int i,index = 0;
	for(i=0;i<len;i++)
	{
		if(max < d[i])
		{
			max = d[i];
			index = i;
		}
	}

//	// if there is more than one maximum it returns -1 to remove it
//	for(i=0;i<len;i++)
//	{
//		if(max==d[i] && index!=i)
//		{
//			return -1;
//		}
//	}
//	// if there is more than one maximum it returns -1 to remove it

	if(max <= 0) return -1;
	return index;
}

int Tools::getMedianIndex(double* d,int len)
{
	int i1 = 0;
	int i2 = len - 1;
	while(i1 < len - 1 && d[i1] == 0)
	{
		i1++;
	}
	while(i2 > 0 && d[i2] == 0)
	{
		i2--;
	}
	return (int)floor((i1 + i2) / 2);
}

TPair<TInt,TInt> Tools::findRangeWithValues(double* d,int len)
{
	int i1 = 0;
	int i2 = len - 1;
	while(i1 < len - 1 && d[i1] == 0)
	{
		i1++;
	}
	while(i2 > 0 && d[i2] == 0)
	{
		i2--;
	}
	TPair<TInt,TInt> range(i1,i2);
	return range;
}


TStr Tools::exec(TStr cmd)
{
    FILE* pipe = popen(cmd.CStr(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    TStr result = "";
    while(!feof(pipe))
    {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}

bool Tools::getRealUrl(TChA& url, TChAV& res)
{
	// COMMAND LINE APPROACH
	TStr cmd = TStr::Fmt("curl -s -f -A 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKitHTML, like Gecko) Chrome' --max-redirs 1 -w '%{redirect_url}' -o 'tmp.txt' %s",url.CStr());
	TStr tmp = exec(cmd).GetTrunc();

	// just last url (sometimes they have redirections like::: http://bitly.com/1aDm2eK)
	int index = tmp.SearchStr("http",1);
	if(index!=-1)
	{
		if(tmp.GetTrunc().Len() > 0)
		{
			res.Add(TChA(tmp.GetTrunc().GetCStr()));
		}

		int lastindex;
		while(index!=-1)
		{
			lastindex = index;
			index = tmp.SearchStr("http",index+1);
		}
		index = lastindex;

		tmp = tmp.GetSubStr(index,tmp.Len()-1);
		tmp.ChangeStrAll("%2F","/");
		tmp.ChangeStrAll("%2f","/");
		tmp.ChangeStrAll("%3A",":");
		tmp.ChangeStrAll("%3a",":");
//		tmp.ChangeStrAll("amp;","");

		if(tmp.GetTrunc().Len() > 0)
		{
			res.Add(TChA(tmp.GetTrunc().GetCStr()));
		}
	}
	else
	{
		res.Add(TChA(tmp.GetCStr()));
	}

	return res.Len()!=0;
}

TChA Tools::getBase(TChA& address)
{
	TStr fulladdress = TStr(address);
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
	if(res.GetSubStr(0,3) == "www.")
	{
		res = res.GetSubStr(4,res.Len()-1);
	}
	return res;
}

TChA Tools::getUrl(TChA& address,TChA& base)
{
//	cout << address.CStr() << "," << base.CStr() << endl;
	int idx = address.SearchStr(base,0);
	TChA res = address.GetSubStr(idx,address.Len()-1);
	if(res.GetSubStr(res.Len()-10,res.Len()-1) == "/index.php")
	{
		res = res.GetSubStr(0,res.Len()-11);
	}
	if(res.GetSubStr(res.Len()-11,res.Len()-1) == "/index.html")
	{
		res = res.GetSubStr(0,res.Len()-12);
	}
	if(res.GetSubStr(res.Len()-10,res.Len()-1) == "/index.htm")
	{
		res = res.GetSubStr(0,res.Len()-11);
	}
	while(res.LastCh() == '/')
	{
		res = res.GetSubStr(0,res.Len()-2);
	}
	return res;
}

TChAV Tools::getAllUrlsWithPrefix(TStr& text,char* prefix)
{
	TStr prefixTStr(prefix);
	TChAV us;
	string u;
	int i, idx, foundidx = -1;
	idx = 0;
	while(idx < text.Len())
	{
		foundidx = text.SearchStr(prefixTStr,idx);
		if(foundidx == -1)
		{
			break;
		}

		stringstream ss(text.GetSubStr(foundidx,text.Len()-1).CStr());
		ss >> u;
		TStr st(u.c_str());
		st.DelChAll(']');
		st.DelChAll('[');
		st.DelChAll(')');
		st.DelChAll('(');
		st.DelChAll('\'');
		st.DelChAll('"');

		while(st.LastCh()=='.')
		{
			st = st.GetSubStr(0,st.Len()-2);
		}

		int ixx = st.SearchCh(';',0);
		if(ixx != -1)
		{
			st = st.GetSubStr(0,ixx-1);
		}
		ixx = st.SearchCh('|',0);
		if(ixx != -1)
		{
			st = st.GetSubStr(0,ixx-1);
		}

		TChA ur(st.CStr());
		TChA base = getBase(ur);

		TChA res = getUrl(ur,base);
		us.Add(res);
		idx = foundidx + u.length();
	}

	return us;
}

TChAV Tools::getAllUrls(TStr& text)
{
	TChAV res;
	res.AddV(Tools::getAllUrlsWithPrefix(text,"https://"));
	res.AddV(Tools::getAllUrlsWithPrefix(text,"http://"));
	res.AddV(Tools::getAllUrlsWithPrefix(text," www."));
	return res;
}

bool Tools::fileExists(TStr filepath)
{
	fstream f(filepath.CStr(),ios::in);
	if(!f)
	{
		f.close();
		return false;
	}
	f.close();
	return true;
}

void Tools::plotOne(THash<TStr,CascadeElementV>& quotes, char* name, int DesiredCascadesCount)
{
	int bins,i,q,index,center,Q,lengt,minLen;
	double* vols;
	double* vol;
	TFltPrV volumes;
	uint period = 4 * 3600;   // 6 Hours but, I think memetracker paper has 4 hours binning
//	uint period = 30 * 24 * 3600;   // Month
	uint begin = TSecTm(2008,8,1,0,0,0).GetAbsSecs();
	uint end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();

	TGnuPlot plot;
	plot.SetXYLabel("Time[4 Hours]", "Volume");

	// ---== Computation ==---
	Q = quotes.Len();
	bins = (end - begin) / period;
	lengt = 2 * bins + 1;
	center = (lengt-1) / 2;
	vols = new double[lengt];
	for(i=0;i<lengt;i++)
	{
		vols[i] = 0;
	}

	// The quotes cascades with min size DesiredCascadesCount
	if(DesiredCascadesCount!=0)
	{
		int* lengs = new int[Q];
		for(q=0;q<Q;q++)
		{
			lengs[q] = quotes[q].Len();
		}
		sort(lengs,lengs+Q,std::greater<int>());
		minLen = lengs[DesiredCascadesCount-1];
		delete[] lengs;
	}

	int c = 0;
	int beginShifted = begin - end;
	for(q=0;q<Q;q++)
	{
		if(DesiredCascadesCount!=0 && quotes[q].Len() < minLen)
		{
			continue;
		}

		int medVal = (int)quotes[q][quotes[q].Len()/2].time.GetAbsSecs();
		TIntV casc;
		for(i=0;i<quotes[q].Len();i++)
		{
			casc.Add((int)quotes[q][i].time.GetAbsSecs() - medVal);
		}
		vol = Tools::calculateHistOfCascade(casc, beginShifted, period, lengt, true);
		for(i=0;i<lengt;i++)
		{
			vols[i] += vol[i];
		}
		c++;
		delete[] vol;
	}

	printf("Quotes count: %d\n",c);
	int myleng = 20;
	IAssert(center-myleng>0 && center+myleng<lengt);
	for(i=center-myleng;i<=center+myleng;i++)
//	for(i=0;i<lengt;i++)
	{
		vols[i] /= c;
		TFltPr elem;
		elem.Val1 = -center + i;
		elem.Val2 = vols[i];
		volumes.Add(elem);
	}
//	plot.AddPlot(volumes,gpwLinesPoints);
	plot.AddPlot(volumes,gpwPoints);
	plot.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
//	plot.SaveEps(TStr::Fmt("MyResults/%s.eps",name));
	plot.SaveEps(TStr::Fmt("MyResults/%s.eps",name),true);

	printf("Plot %s is done.\n",name);
}


void Tools::plotTwo(THash< TStr,CascadeElementV > quotes , THash<TUInt,TSecTmV> twitter , char* name)
{
	uint period = 3600;
	int begin = TSecTm(2008,8,1,0,0,0).GetAbsSecs();
	int end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
	int bins = (end - begin) / period;
	int lengt = 2 * bins + 1;
	int center = (lengt-1) / 2;
	double* memeVolumes = new double[lengt];
	double* twitterVolumes = new double[lengt];
	for(int i=0;i<lengt;i++)
	{
		memeVolumes[i] = 0;
		twitterVolumes[i] = 0;
	}

	for(int q=0;q<quotes.Len();q++)
	{
		int leng = quotes[q].Len()+twitter[q].Len();
		int* integratedTimestamps = new int[leng];
		for(int i=0;i<quotes[q].Len();i++)
		{
			integratedTimestamps[i] = quotes[q][i].time.GetAbsSecs();
		}
		for(int i=0;i<twitter[q].Len();i++)
		{
			integratedTimestamps[quotes[q].Len()+i] = twitter[q][i].GetAbsSecs();
		}
		sort(integratedTimestamps,integratedTimestamps+leng);
		int integratedMedianValue = integratedTimestamps[leng/2];
		delete[] integratedTimestamps;

		TIntV memeCascade;
		for(int i=0;i<quotes[q].Len();i++)
		{
			memeCascade.Add((int)quotes[q][i].time.GetAbsSecs() - integratedMedianValue);
		}
		TIntV twitterCascade;
		for(int i=0;i<twitter[q].Len();i++)
		{
			twitterCascade.Add((int)twitter[q][i].GetAbsSecs() - integratedMedianValue);
		}
		int beginShifted = begin - end;

		double* memeVol = Tools::calculateHistOfCascade(memeCascade,beginShifted,period,lengt,true);
		memeCascade.Clr();
		for(int i=0;i<lengt;i++)
		{
			memeVolumes[i] += memeVol[i];
		}
		delete[] memeVol;

		double* twitterVol = Tools::calculateHistOfCascade(twitterCascade,beginShifted,period,lengt,true);
		twitterCascade.Clr();
		for(int i=0;i<lengt;i++)
		{
			twitterVolumes[i] += twitterVol[i];
		}
		delete[] twitterVol;
	}

	printf("Plotting ...\n");
	TFltPrV memeVolumes4Plot;
	TFltPrV twitterVolumes4Plot;
	int myleng = 10;
	IAssert(center-myleng>0 && center+myleng<lengt);
	for(int i=center-myleng;i<=center+myleng;i++)
//	for(int i=0;i<lengt;i++)
	{
		memeVolumes[i] /= quotes.Len();
		twitterVolumes[i] /= quotes.Len();
		TFltPr elem;
		elem.Val1 = -center + i;

		elem.Val2 = memeVolumes[i];
		memeVolumes4Plot.Add(elem);

		elem.Val2 = twitterVolumes[i];
		twitterVolumes4Plot.Add(elem);
	}
	delete[] memeVolumes;
	delete[] twitterVolumes;

	// Plotting
//	TGnuPlot plot1;
//	plot1.SetXYLabel("Time[hours]", "Volume");
//	plot1.AddPlot(memeVolumes4Plot,gpwLinesPoints,"Memes");
//	plot1.AddPlot(twitterVolumes4Plot,gpwLinesPoints,"Twitter");
//	plot1.SetDataPlotFNm(TStr::Fmt("MyResults/%s-Original.tab",name), TStr::Fmt("MyResults/%s-Original.plt",name));
//	plot1.SaveEps(TStr::Fmt("MyResults/%s-Original.eps",name));

	TGnuPlot plot2;
	plot2.SetXYLabel("Time[hours]", "Volume");
	plot2.AddPlot(memeVolumes4Plot,gpwPoints,"Memes");
	plot2.AddPlot(twitterVolumes4Plot,gpwPoints,"Twitter");
	plot2.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
	plot2.SaveEps(TStr::Fmt("MyResults/%s.eps",name),true);

	printf("Plot %s is done.\n",name);
}




