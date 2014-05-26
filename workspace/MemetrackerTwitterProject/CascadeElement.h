/*
 * CascadeElement.h
 *
 *  Created on: Apr 29, 2014
 *      Author: omid55
 */

#ifndef _CASCADEELEMENT_H
#define _CASCADEELEMENT_H
#include "./snap/Snap.h"

class CascadeElement
{
public:
	TUInt post;
	TSecTm time;
	TVec<TUInt> explicit_links;

	CascadeElement();
	CascadeElement(TSecTm &t);
	CascadeElement(TSIn& SIn);
	CascadeElement(TChA& p,TSecTm &t,THash<TChA,TUInt>& posts);
	CascadeElement(TChA& p,TSecTm &t, TVec<TUInt>& e,THash<TChA,TUInt>& posts);
	//bool operator==(const TPt& Pt);
	//bool operator!=(const TPt& Pt);
	bool operator<(const CascadeElement& Pt) const;
	bool operator==(CascadeElement& Rec) const;
	bool operator!=(CascadeElement& Rec) const;
	//bool operator<(CascadeElement& Rec);
	bool operator>(CascadeElement& Rec) const;
	bool operator<=(CascadeElement& Rec) const;
	bool operator>=(CascadeElement& Rec) const;
	bool Cmp(int& RelOp, CascadeElement& Rec1, CascadeElement& Rec2) const;
	int operator()(const CascadeElement& x, const CascadeElement& y) const;
	void Load(TSIn& SIn);
	void Save(TSOut& SOut);
};

typedef TVec<CascadeElement> CascadeElementV;


#endif /* CASCADEELEMENT_H_ */
