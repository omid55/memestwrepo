/*
 * TwitterUrl.h
 *
 *  Created on: Apr 29, 2014
 *      Author: omid55
 */

#ifndef TWITTERURL_H_
#define TWITTERURL_H_
#include "./snap/Snap.h"

class TwitterUrl
{
public:
	TSecTm time;
	TChAV urlsV;

	TwitterUrl();
	TwitterUrl(TSecTm &t, TChAV& u);
	TwitterUrl(TSIn& SIn);
	void Load(TSIn& SIn);
	void Save(TSOut& SOut);
};


#endif /* TWITTERURL_H_ */
