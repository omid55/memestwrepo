// Omid55
// String Trie Header

/*
 * TStrTrie.h
 *
 *  Created on: Feb 25, 2014
 *      Author: Omid
 */

#include "stdafx.h"

#ifndef TSTRTRIE_H_
#define TSTRTRIE_H_

class Node
{
private:
	THash<TStr,Node> data;    // word -> next nodes
	TInt id;


public:
	Node();
	Node(TSIn& SIn);
	~Node();
	TInt getId() const;
	void setId(TInt id);
	THash<TStr,Node> getData() const;
	void setData(THash<TStr,Node> data);
	void Load(TSIn& SIn);
	void Save(TSOut& SOut) const;
	void Clr(const bool& DoDel=true, const int& NoDelLim=-1, const bool& ResetDat=true);


	void addWord(TStr word);
	bool hasWord(TStr word) const;
	Node& getNextNode(TStr word);
};


class TStrTrie
{
private:
	Node* root;    // word -> next nodes
	TInt minLen;
	TBool doRemoveSymbols;

public:
	TStrTrie();
	TStrTrie(TSIn& SIn);
	~TStrTrie();
	void Load(TSIn& SIn);   // static TPt<TStrTrie>
	void Save(TSOut& SOut) const;
	void Clr(const bool& DoDel=true, const int& NoDelLim=-1, const bool& ResetDat=true);

	bool getDoRemoveSymbols() const;
	void setDoRemoveSymbols(bool d);
	TInt getMinLen() const;
	void add(TStr& sentence,TInt itsId);
	void add(char* sentence,TInt itsId);
	static TStr RemoveSymbols(TStr& text);
	TIntV find(char* sentence) const;
	TIntV find(TStr& sentence) const;
};

#endif /* TSTRTRIE_H_ */
