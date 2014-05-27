/*
 * Tools.cpp
 *
 *  Created on: May 1, 2014
 *      Author: omid55
 */
// Omid55
#include "Tools.h"


// Global Variables
static int myrange = 24;
static int begin = TSecTm(2008,7,31,0,0,0).GetAbsSecs();
static int end = TSecTm(2009,10,1,0,0,0).GetAbsSecs();
// Global Variables


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

int Tools::getTheBinIndex(int x, int rbegin, uint rperiod)
{
	return floor(((double)x - (double)rbegin) / (double)rperiod);
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
		index = Tools::getTheBinIndex(cascade[i].time.GetAbsSecs(),rbegin,rperiod);
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

//int Tools::getMedianIndex(double* d,int len)
//{
//	int i1 = 0;
//	int i2 = len - 1;
//	while(i1 < len - 1 && d[i1] == 0)
//	{
//		i1++;
//	}
//	while(i2 > 0 && d[i2] == 0)
//	{
//		i2--;
//	}
//	return (int)floor((i1 + i2) / 2);
//}

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

// CCDF
void Tools::myPrivatePlotCCDF_PrintPosNeg(double* arr, int leng, char* name, char* xlabel)
{
	TGnuPlot plot;
	TFltPrV middle;
	bool firstFound = false;
	double middleY;
	int i,pos=0,neg=0;
	double x1,y1,x2,y2,mean=0,posRatio,negRatio,x,y;
	TFltPrV points;

	printf("%s Drawing:\n",name);
	plot.SetXYLabel(xlabel, "P(X>d)");
	for(i=0;i<leng;i++)
	{
		if(arr[i] > 0)
		{
			pos++;
		}
		if(arr[i] < 0)
		{
			neg++;
		}
		mean += arr[i];
	}
	posRatio = (double)pos/leng;
	negRatio = (double)neg/leng;
	mean /= leng;

	printf("Positive Ratio: %f, Negative Ratio: %f\n",posRatio,negRatio);
	if(posRatio > 0.5)
	{
		printf("{{{Twitter is sooner.}}}\n");
	}
	else if(negRatio > 0.5)
	{
		printf("{{{Memes is sooner.}}}\n");
	}
	else
	{
		printf("{{{They are equal!!!}}}\n");
	}
	printf("Mean: %f\n",mean);

	// Ploting CCDF
	sort(arr,arr+leng);
	for(i=0;i<leng;i++)
	{
		x = arr[i];
		y = 1.0 - (1.0/leng)*i;
		points.Add(TFltPr(x,y));
		if(x > 0 && !firstFound)
		{
			firstFound = true;
			x1 = arr[i-1];
			y1 =  1.0 - (1.0/leng) * (i-1);
			x2 = x;
			y2 = y;
			middleY = -x1*(y2-y1)/(x2-x1)+y1;
			plot.SetTitle(TStr::Fmt("y is %f at x=0",middleY));
		}
	}

	middle.Add(TFltPr(0,middleY));
	plot.AddPlot(points,gpwLines);
	plot.AddPlot(middle,gpwPoints);
	plot.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
	plot.SaveEps(TStr::Fmt("MyResults/%s.eps",name));
	printf("%s had been drawn successfully.\n\n",name);
}

void Tools::plotCCDFStartMedianEnd(THash<TStr,CascadeElementV> quotes, THash<TUInt,TSecTmV> twitter, char* name, char* legendname1)
{
	double posRatio,negRatio,mean=0;
	int len = 0;
	for(int i=0;i<twitter.Len();i++)
	{
		if(quotes[i].Len() > 0 && twitter[i].Len() > 0)
		{
			len++;
		}
	}
	double* medianDifference = new double[len];
	double* startDifference = new double[len];
	double* endDifference = new double[len];
	int c = 0;
	for(int i=0;i<twitter.Len();i++)
	{
		CascadeElementV memesCascade = quotes[i];
		TSecTmV twCascade = twitter[i];

		if(quotes[i].Len() > 0 && twitter[i].Len() > 0)
		{
			medianDifference[c] = (double)memesCascade[memesCascade.Len()/2].time.GetAbsSecs() - (double)twCascade[twCascade.Len()/2].GetAbsSecs();
			startDifference[c] = (double)memesCascade[0].time.GetAbsSecs() - (double)twCascade[0].GetAbsSecs();
			endDifference[c++] = (double)memesCascade[memesCascade.Len()-1].time.GetAbsSecs() - (double)twCascade[twCascade.Len()-1].GetAbsSecs();
		}
	}

	// Plot Drawing
	Tools::myPrivatePlotCCDF_PrintPosNeg(medianDifference,len,TStr::Fmt("%sMedianDifferenceCCDF",name).CStr(),TStr::Fmt("d [(%s median - Twitter median) of cascade's times]",legendname1).CStr());
	Tools::myPrivatePlotCCDF_PrintPosNeg(startDifference,len,TStr::Fmt("%sStartDifferenceCCDF",name).CStr(),TStr::Fmt("d [(%s start - Twitter start) of cascade's times]",legendname1).CStr());
	Tools::myPrivatePlotCCDF_PrintPosNeg(endDifference,len,TStr::Fmt("%sEndDifferenceCCDF",name).CStr(),TStr::Fmt("d [(%s end - Twitter end) of cascade's times]",legendname1).CStr());
}

void Tools::plotCCDFStartMedianEnd(THash<TStr,CascadeElementV> q1, THash<TStr,CascadeElementV> q2, char* name, char* legendname1, char* legendname2)
{
	double posRatio,negRatio,mean=0;
	int len = 0;
	for(int i=0;i<q1.Len();i++)
	{
		if(q1[i].Len() > 0 && q2[i].Len() > 0)
		{
			len++;
		}
	}
	double* medianDifference = new double[len];
	double* startDifference = new double[len];
	double* endDifference = new double[len];
	int c = 0;
	for(int i=0;i<q1.Len();i++)
	{
		CascadeElementV q1Cascade = q1[i];
		CascadeElementV q2Cascade = q2[i];

		if(q1Cascade.Len() > 0 && q2Cascade.Len() > 0)
		{
			medianDifference[c] = (double)q1Cascade[q1Cascade.Len()/2].time.GetAbsSecs() - (double)q2Cascade[q2Cascade.Len()/2].time.GetAbsSecs();
			startDifference[c] = (double)q1Cascade[0].time.GetAbsSecs() - (double)q2Cascade[0].time.GetAbsSecs();
			endDifference[c++] = (double)q1Cascade[q1Cascade.Len()-1].time.GetAbsSecs() - (double)q2Cascade[q2Cascade.Len()-1].time.GetAbsSecs();
		}
	}

	// Plot Drawing
	Tools::myPrivatePlotCCDF_PrintPosNeg(medianDifference,len,TStr::Fmt("%sMedianDifferenceCCDF",name).CStr(),TStr::Fmt("d [%s median - %s median]",legendname1,legendname2).CStr());
	Tools::myPrivatePlotCCDF_PrintPosNeg(startDifference,len,TStr::Fmt("%sStartDifferenceCCDF",name).CStr(),TStr::Fmt("d [%s start - %s start]",legendname1,legendname2).CStr());
	Tools::myPrivatePlotCCDF_PrintPosNeg(endDifference,len,TStr::Fmt("%sEndDifferenceCCDF",name).CStr(),TStr::Fmt("d [%s end - %s end]",legendname1,legendname2).CStr());
}


// Individually
void Tools::plotOneIndividuallyShift(THash<TStr,CascadeElementV>& quotes, char* name, uint period, char* periodstr, int DesiredCascadesCount)
{
	int bins,i,q,index,center,Q,lengt,minLen;
	double* vols;
	double* vol;
	TFltPrV volumes;
	TGnuPlot plot;
	plot.SetXYLabel(TStr::Fmt("Time[%s]",periodstr), "Volume");

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

		if(quotes[q].Len() == 0)
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
	IAssert(center-myrange>0 && center+myrange<lengt);
	for(i=center-myrange;i<=center+myrange;i++)
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

void Tools::plotTwoIndividuallyShift(THash<TStr,CascadeElementV>& quotes, THash<TUInt,TSecTmV>& twitter, uint period, char* periodstr, char* name)
{
	int bins = (end - begin) / period;
	int lengt = 2 * bins + 1;
	int center = (lengt - 1) / 2;
	double* memeVolumes = new double[lengt];
	double* twitterVolumes = new double[lengt];
	for(int i=0;i<lengt;i++)
	{
		memeVolumes[i] = 0;
		twitterVolumes[i] = 0;
	}

	for(int q=0;q<quotes.Len();q++)
	{
		int leng = quotes[q].Len() + twitter[q].Len();
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
	IAssert(center-myrange>0 && center+myrange<lengt);
	for(int i=center-myrange;i<=center+myrange;i++)
//	for(int i=0;i<lengt;i++)
	{
		memeVolumes[i] /= quotes.Len();
		twitterVolumes[i] /= quotes.Len();
		TFltPr elem1;
		elem1.Val1 = -center + i;
		elem1.Val2 = memeVolumes[i];
		memeVolumes4Plot.Add(elem1);

		TFltPr elem2;
		elem2.Val1 = -center + i;
		elem2.Val2 = twitterVolumes[i];
		twitterVolumes4Plot.Add(elem2);
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
	plot2.SetXYLabel(TStr::Fmt("Time[%s]",periodstr), "Volume");
	plot2.AddPlot(memeVolumes4Plot,gpwPoints,"Memes");
	plot2.AddPlot(twitterVolumes4Plot,gpwPoints,"Twitter");
	plot2.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
	plot2.SaveEps(TStr::Fmt("MyResults/%s.eps",name),true);

	printf("Plot %s is done.\n",name);
}

void Tools::plotTwoIndividuallyShift(THash<TStr,CascadeElementV>& q1, THash<TStr,CascadeElementV>& q2, uint period, char* periodstr, char* name, char* s1, char* s2, int DesiredCascadesCount)
{
	int minLen;
	int bins = (end - begin) / period;
	int lengt = 2 * bins + 1;
	int center = (lengt-1) / 2;
	double* q1Volumes = new double[lengt];
	double* q2Volumes = new double[lengt];
	for(int i=0;i<lengt;i++)
	{
		q1Volumes[i] = 0;
		q2Volumes[i] = 0;
	}

	// The quotes cascades with min size DesiredCascadesCount
	if(DesiredCascadesCount!=0)
	{
		IAssert(q1.Len() == q2.Len());
		int* lengs = new int[q1.Len()];
		for(int q=0;q<q1.Len();q++)
		{
			lengs[q] = q1[q].Len() + q2[q].Len();
		}
		sort(lengs,lengs+q1.Len(),std::greater<int>());
		minLen = lengs[DesiredCascadesCount-1];
		delete[] lengs;
	}

	int smalls = 0;
	for(int q=0;q<q1.Len();q++)
	{
		int leng = q1[q].Len() + q2[q].Len();
		if(leng < minLen)
		{
			smalls++;
			continue;
		}

		int* integratedTimestamps = new int[leng];
		for(int i=0;i<q1[q].Len();i++)
		{
			integratedTimestamps[i] = q1[q][i].time.GetAbsSecs();
		}
		for(int i=0;i<q2[q].Len();i++)
		{
			integratedTimestamps[q1[q].Len()+i] = q2[q][i].time.GetAbsSecs();
		}
		sort(integratedTimestamps,integratedTimestamps+leng);
		int integratedMedianValue = integratedTimestamps[leng/2];
		delete[] integratedTimestamps;

		TIntV q1Cascade;
		for(int i=0;i<q1[q].Len();i++)
		{
			q1Cascade.Add((int)q1[q][i].time.GetAbsSecs() - integratedMedianValue);
		}
		TIntV q2Cascade;
		for(int i=0;i<q2[q].Len();i++)
		{
			q2Cascade.Add((int)q2[q][i].time.GetAbsSecs() - integratedMedianValue);
		}
		int beginShifted = begin - end;

		double* q1Vol = Tools::calculateHistOfCascade(q1Cascade,beginShifted,period,lengt,true);
		q1Cascade.Clr();
		for(int i=0;i<lengt;i++)
		{
			q1Volumes[i] += q1Vol[i];
		}
		delete[] q1Vol;

		double* q2Vol = Tools::calculateHistOfCascade(q2Cascade,beginShifted,period,lengt,true);
		q2Cascade.Clr();
		for(int i=0;i<lengt;i++)
		{
			q2Volumes[i] += q2Vol[i];
		}
		delete[] q2Vol;
	}

	printf("Plotting ...\n");
	TFltPrV q1Volumes4Plot;
	TFltPrV q2Volumes4Plot;
	int finalLen = q1.Len()-smalls;
	printf("\tFor %d cascades.\n\n",finalLen);
	IAssert(center-myrange>0 && center+myrange<lengt);
	for(int i=center-myrange;i<=center+myrange;i++)
//	for(int i=0;i<lengt;i++)
	{
		q1Volumes[i] /= finalLen;
		q2Volumes[i] /= finalLen;
		TFltPr elem;
		elem.Val1 = -center + i;

		elem.Val2 = q1Volumes[i];
		q1Volumes4Plot.Add(elem);

		elem.Val2 = q2Volumes[i];
		q2Volumes4Plot.Add(elem);
	}
	delete[] q1Volumes;
	delete[] q2Volumes;

	// Plotting
//	TGnuPlot plot1;
//	plot1.SetXYLabel("Time[hours]", "Volume");
//	plot1.AddPlot(q1Volumes4Plot,gpwLinesPoints,s1);
//	plot1.AddPlot(q2Volumes4Plot,gpwLinesPoints,s2);
//	plot1.SetDataPlotFNm(TStr::Fmt("MyResults/%s-Original.tab",name), TStr::Fmt("MyResults/%s-Original.plt",name));
//	plot1.SaveEps(TStr::Fmt("MyResults/%s-Original.eps",name));

	TGnuPlot plot2;
	plot2.SetXYLabel(TStr::Fmt("Time[%s]",periodstr), "Volume");
	plot2.AddPlot(q1Volumes4Plot,gpwPoints,s1);
	plot2.AddPlot(q2Volumes4Plot,gpwPoints,s2);
	plot2.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
	plot2.SaveEps(TStr::Fmt("MyResults/%s.eps",name),true);

	printf("Plot %s is done.\n",name);
}


// Hists
void Tools::plotOneHistShift(THash<TStr,CascadeElementV>& quotes, char* name, uint period, char* periodstr, Mode mode, int DesiredCascadesCount)
{
	int bins,i,q,index,center,dif,Q,lengt,discards,minLen,smalls;
	double* vols;
	double* vol;
	TFltPrV volumes;
	TGnuPlot plot;
	plot.SetXYLabel(TStr::Fmt("Time[%s]",periodstr), "Volume");
	plot.SetTitle("BinnedVolumes On Memetracker");

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

	int* lengs = new int[Q];
	for(q=0;q<Q;q++)
	{
		lengs[q] = quotes[q].Len();
	}
	sort(lengs,lengs+Q,std::greater<int>());
	minLen = lengs[DesiredCascadesCount-1];
	delete[] lengs;

	smalls = 0;
	discards = 0;
	for(q=0;q<Q;q++)
	{
		if(quotes[q].Len() < minLen)
		{
			smalls++;
			continue;
		}
		vol = Tools::calculateHistOfCascade(quotes[q],begin,period,bins,true);
		if(mode == MAX)
		{
			index = Tools::getMaxIndex(vol,bins);
		}
		if(mode == MEDIAN)
		{
//			index = Tools::getMedianIndex(vol,bins);

			if(quotes[q].Len()==0)
			{
				continue;
			}
			index = Tools::getTheBinIndex(quotes[q][quotes[q].Len()/2].time.GetAbsSecs(),begin,period);
		}
		if(index == -1)    // we have a larger timeseries in meme tracker than twitter then there are some cascades which they have nothing in the desired range (then we will discard them)
		{
			discards++;
			continue;
		}
		dif = center - index;
		for(i=0;i<bins;i++)
		{
			vols[dif + i] += vol[i];
		}

		delete[] vol;
	}
	printf("Discards: %d, smalls: %d\n\n",discards,smalls);
//		for(i=0;i<lengt;i++)
	for(i=center-myrange;i<=center+myrange;i++)
	{
		vols[i] /= (Q-discards-smalls);
		TFltPr elem;
		elem.Val1 = -center + i;
		elem.Val2 = vols[i];
		volumes.Add(elem);
	}
	plot.AddPlot(volumes,gpwPoints);
	plot.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
	plot.SaveEps(TStr::Fmt("MyResults/%s.eps",name),true);
	delete[] vols;
}

void Tools::plotTwoHistShift(THash<TStr,CascadeElementV>& quotes, THash<TUInt,TSecTmV>& twitter, uint period, char* periodstr, char* name, Mode mode, char* s1, char* s2)
{
	int bins,i,c,index,center,dif,lengt,validCascadesCnt,minLen,quoteIndex,ind1,ind2;
	double* vols_memes;
	double* vols_twitter_contents;
	double* vol_me;
	double* vol_tu;
	TFltPrV volumes_memes;
	TFltPrV volumes_twitter_contents;
	TGnuPlot plot;
	plot.SetXYLabel(TStr::Fmt("Time[%s]",periodstr), "Volume");
	plot.SetTitle("Hourly Binned Quotes Cascade over Memetracker and its contents over Twitter");

	// ---== Computation ==---
	bins = (end - begin) / period;
	printf("bins: %d\n\n",bins);
	lengt = 2 * bins + 1;
	center = (lengt-1) / 2;
	vols_memes = new double[lengt];
	vols_twitter_contents = new double[lengt];
	for(i=0;i<lengt;i++)
	{
		vols_memes[i] = 0;
		vols_twitter_contents[i] = 0;
	}

	validCascadesCnt = 0;
	for(c=0;c<twitter.Len();c++)
	{
//		quoteIndex = twitter.GetKey(c);
		vol_me = Tools::calculateHistOfCascade(quotes[c],begin,period,bins,true);
		vol_tu = Tools::calculateHistOfCascade(twitter[c],begin,period,bins,true);   //.GetDat(quoteIndex)

		if(mode == MEDIAN)
		{
//			ind1 = Tools::getMedianIndex(vol_me,bins);
//			ind2 = Tools::getMedianIndex(vol_tu,bins);

			if(quotes[c].Len()==0 || twitter[c].Len()==0)
			{
				continue;
			}
			ind1 = Tools::getTheBinIndex(quotes[c][quotes[c].Len()/2].time.GetAbsSecs(),begin,period);
			ind2 = Tools::getTheBinIndex(twitter[c][twitter[c].Len()/2].GetAbsSecs(),begin,period);
		}
		if(mode == MAX)
		{
			ind1 = Tools::getMaxIndex(vol_me,bins);
			ind2 = Tools::getMaxIndex(vol_tu,bins);
		}
		if(ind1 == -1 || ind2 == -1)
		{
			delete[] vol_me;
			delete[] vol_tu;
			continue;
		}
		index = (ind1 + ind2) / 2;
		dif = center - index;
		for(i=0;i<bins;i++)
		{
			vols_memes[dif + i] += vol_me[i];
			vols_twitter_contents[dif + i] += vol_tu[i];
		}
		validCascadesCnt++;

		delete[] vol_me;
		delete[] vol_tu;
	}

	printf("\n--===((( Cascades Count is: %d )))===--\n",validCascadesCnt);
	for(i=center-myrange;i<=center+myrange;i++)
	{
		vols_memes[i] /= validCascadesCnt;
		volumes_memes.Add(TFltPr(-center+i,vols_memes[i]));

		vols_twitter_contents[i] /= validCascadesCnt;
		volumes_twitter_contents.Add(TFltPr(-center+i,vols_twitter_contents[i]));
	}
	plot.AddPlot(volumes_memes,gpwPoints,s1);
	plot.AddPlot(volumes_twitter_contents,gpwPoints,s2);
	plot.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
	plot.SaveEps(TStr::Fmt("MyResults/%s.eps",name),true);

	delete[] vols_memes;
	delete[] vols_twitter_contents;
}

void Tools::plotTwoHistShift(THash<TStr,CascadeElementV>& q1, THash<TStr,CascadeElementV>& q2, uint period, char* periodstr, char* name, Mode mode, char* s1, char* s2)
{
	int bins,i,c,index,center,dif,lengt,validCascadesCnt,minLen,ind1,ind2;
	double* vols_memes;
	double* vols_twitter_contents;
	double* vol_me;
	double* vol_tu;
	TFltPrV volumes_memes;
	TFltPrV volumes_twitter_contents;
	TGnuPlot plot;
	plot.SetXYLabel(TStr::Fmt("Time[%s]",periodstr), "Volume");
	plot.SetTitle("Binned Quotes Cascade over Memetracker and its contents over Twitter");

	// ---== Computation ==---
	bins = (end - begin) / period;
	printf("bins: %d\n\n",bins);
	lengt = 2 * bins + 1;
	center = (lengt-1) / 2;
	vols_memes = new double[lengt];
	vols_twitter_contents = new double[lengt];
	for(i=0;i<lengt;i++)
	{
		vols_memes[i] = 0;
		vols_twitter_contents[i] = 0;
	}

	validCascadesCnt = 0;
	for(c=0;c<q2.Len();c++)
	{
		vol_me = Tools::calculateHistOfCascade(q1[c],begin,period,bins,true);
		vol_tu = Tools::calculateHistOfCascade(q2[c],begin,period,bins,true);

		if(mode == MEDIAN)
		{
//			ind1 = Tools::getMedianIndex(vol_me,bins);
//			ind2 = Tools::getMedianIndex(vol_tu,bins);

			if(q1[c].Len()==0 || q2[c].Len()==0)
			{
				continue;
			}
			ind1 = Tools::getTheBinIndex(q1[c][q1[c].Len()/2].time.GetAbsSecs(),begin,period);
			ind2 = Tools::getTheBinIndex(q2[c][q2[c].Len()/2].time.GetAbsSecs(),begin,period);
		}
		if(mode == MAX)
		{
			ind1 = Tools::getMaxIndex(vol_me,bins);
			ind2 = Tools::getMaxIndex(vol_tu,bins);
		}
		if(ind1 == -1 || ind2 == -1)
		{
			delete[] vol_me;
			delete[] vol_tu;
			continue;
		}
		index = (ind1 + ind2) / 2;
		dif = center - index;
		for(i=0;i<bins;i++)
		{
			vols_memes[dif + i] += vol_me[i];
			vols_twitter_contents[dif + i] += vol_tu[i];
		}
		validCascadesCnt++;

		delete[] vol_me;
		delete[] vol_tu;
	}

	printf("\n--===((( Cascades Count is: %d )))===--\n",validCascadesCnt);
	for(i=center-myrange;i<=center+myrange;i++)
	{
		vols_memes[i] /= validCascadesCnt;
		volumes_memes.Add(TFltPr(-center+i,vols_memes[i]));

		vols_twitter_contents[i] /= validCascadesCnt;
		volumes_twitter_contents.Add(TFltPr(-center+i,vols_twitter_contents[i]));
	}
	plot.AddPlot(volumes_memes,gpwPoints,s1);
	plot.AddPlot(volumes_twitter_contents,gpwPoints,s2);
	plot.SetDataPlotFNm(TStr::Fmt("MyResults/%s.tab",name), TStr::Fmt("MyResults/%s.plt",name));
	plot.SaveEps(TStr::Fmt("MyResults/%s.eps",name),true);

	delete[] vols_memes;
	delete[] vols_twitter_contents;
}

THash<TStr,CascadeElementV> Tools::loadQuotes(char* name)
{
	THash<TStr,CascadeElementV> qs;
	TZipIn rarinput(name);
	qs.Load(rarinput);
	printf("Quotes: It has %d items.\n\n",qs.Len());
	return qs;
}

THash<TUInt,TSecTmV> Tools::loadTwitter(char* name)
{
	THash<TUInt,TSecTmV> tw;
	TZipIn rarinput(name);
	tw.Load(rarinput);
	printf("Twitter: It has %d items.\n\n",tw.Len());
	return tw;
}

