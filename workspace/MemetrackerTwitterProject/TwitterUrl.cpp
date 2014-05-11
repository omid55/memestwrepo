/*
 * TwitterUrl::TwitterUrl.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: omid55
 */
#include "TwitterUrl.h"


TwitterUrl::TwitterUrl()
{
}

TwitterUrl::TwitterUrl(TSecTm &t, TChAV& u)
{
	time = t;
	urlsV = u;
}

TwitterUrl::TwitterUrl(TSIn& SIn)
{
	Load(SIn);
}

void TwitterUrl::Load(TSIn& SIn)
{
	time.Load(SIn);
	urlsV.Load(SIn);
}

void TwitterUrl::Save(TSOut& SOut)
{
	time.Save(SOut);
	urlsV.Save(SOut);
}

