//Omid55
#include "stdafx.h"

THash< TStr , CascadeElementV > quotes;
THash< TStr , CascadeElementV > quotesSubset;

void SaveAll()
{
	TZipOut z1("QuotesSubsetData.rar");
	quotesSubset.Save(z1);
	printf("The size of quotesSubset was: %d\n",quotesSubset.Len());

	printf("\n<<<<< SAVING DONE >>>>>\n\n");
}

class MyItem
{
public:
	int id;
	int val;

	MyItem()
	{}

	MyItem(int i,int v)
	{
		id = i;
		val = v;
	}

	bool operator<(const MyItem& Pt) const {return val<Pt.val;}
	bool operator==(MyItem& Rec){return (id==Rec.id);}
	bool operator!=(MyItem& Rec){return !(id==Rec.id);}
	bool operator>(MyItem& Rec){return Rec.val<val;}
	bool operator<=(MyItem& Rec){return !(Rec.val<val);}
	bool operator>=(MyItem& Rec){return !(val<Rec.val);}

	bool Cmp(int& RelOp, MyItem& Rec1, MyItem& Rec2)
	{
	  switch (RelOp)
	  {
	    case roLs: return Rec1<Rec2;
	    case roLEq: return Rec1<=Rec2;
	    case roEq: return Rec1==Rec2;
	    case roNEq: return Rec1!=Rec2;
	    case roGEq: return Rec1>=Rec2;
	    case roGt: return Rec1>Rec2;
	    default: Fail; return false;
	  }
	}

//	int operator()(const MyItem& x, const MyItem& y) const
//	{
//		if (x.val < y.val){return -1;}
//		else if (x.val > y.val){return 1;}
//		else {return 0;}
//	}
};


int main(int argc, char* argv[])
{
//	TZipIn z("QuotesSubsetData.rar");
//	quotesSubset.Load(z);
//	printf("The size of QuotesSubsetData was: %d\n",quotesSubset.Len());
//
//	return 0;

	int DesiredNumberOfQuotes = 1000;
	printf("Starting subseting the quotes code ...\n");

	TExeTm ExeTm;
	try
	{
		Env = TEnv(argc, argv, TNotify::StdNotify);
		Env.PrepArgs(TStr::Fmt("\nCreating the subset of the quotes. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

		TZipIn z1("QuotesData.rar");
		quotes.Load(z1);
		printf("Loaded quotes has instances: %d\n\n\n",quotes.Len());

		TVec<MyItem> v;
		for(int i=0;i<quotes.Len();i++)
		{
			v.Add(MyItem(i,quotes[i].Len()));
		}
		v.Sort(false);
		for(int i=0;i<DesiredNumberOfQuotes;i++)
		{
			CascadeElementV v2 = quotes[v[i].id];
			TStr v1 = quotes.GetKey(v[i].id);
			quotesSubset.AddDat(v1,v2);;
		}

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

	printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
	return 0;
}
