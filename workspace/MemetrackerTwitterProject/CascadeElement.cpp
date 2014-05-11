/*
 * CascadeElement.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: omid55
 */
#include "CascadeElement.h"


CascadeElement::CascadeElement()
{
}

CascadeElement::CascadeElement(TSecTm &t)
{
	time = t;
}

CascadeElement::CascadeElement(TSIn& SIn)
{
	Load(SIn);
}

CascadeElement::CascadeElement(TChA& p,TSecTm &t,THash< TChA , TUInt >& posts)
{
	TUInt id = posts.GetKeyId(p);
	if(id == -1)
	{
		id = posts.Len();
		posts.AddDat(p,id);
	}

	post = id;
	time = t;
}

CascadeElement::CascadeElement(TChA& p,TSecTm &t, TVec<TUInt>& e,THash< TChA , TUInt >& posts)
{
	TUInt id = posts.GetKeyId(p);
	if(id == -1)
	{
		id = posts.Len();
		posts.AddDat(p,id);
	}

	post = id;
	time = t;
	explicit_links = e;
}

//bool CascadeElement::operator==(const TPt& Pt) const {return *Addr==*Pt.Addr;}
//bool CascadeElement::operator!=(const TPt& Pt) const {return *Addr!=*Pt.Addr;}
bool CascadeElement::operator<(const CascadeElement& Pt) const {return time<Pt.time;}
bool CascadeElement::operator==(CascadeElement& Rec) const {return (time==Rec.time && post==Rec.post);}
bool CascadeElement::operator!=(CascadeElement& Rec) const {return !(time==Rec.time && post==Rec.post);}
//bool CascadeElement::operator<(CascadeElement& Rec){return Rec.time>time;}
bool CascadeElement::operator>(CascadeElement& Rec) const {return Rec.time<time;}
bool CascadeElement::operator<=(CascadeElement& Rec) const {return !(Rec.time<time);}
bool CascadeElement::operator>=(CascadeElement& Rec) const {return !(time<Rec.time);}

bool CascadeElement::Cmp(int& RelOp, CascadeElement& Rec1, CascadeElement& Rec2) const
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

int CascadeElement::operator()(const CascadeElement& x, const CascadeElement& y) const
{
	if (x.time < y.time){return -1;}
	else if (x.time > y.time){return 1;}
	else {return 0;}
}

void CascadeElement::Load(TSIn& SIn)
{
	post.Load(SIn);
	time.Load(SIn);
	explicit_links.Load(SIn);
}

void CascadeElement::Save(TSOut& SOut)
{
	post.Save(SOut);
	time.Save(SOut);
	explicit_links.Save(SOut);
}


