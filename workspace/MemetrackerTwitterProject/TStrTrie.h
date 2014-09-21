// Omid55
// String Trie Header

/*
 * TStrTrie.h
 *
 *  Created on: Feb 25, 2014
 *      Author: Omid
 */

//#include "./snap/Snap.h"
#include "stdafx.h"

#ifndef TSTRTRIE_H_
#define TSTRTRIE_H_

class TTStrTrieNode
{
private:
	THash<TStr,TTStrTrieNode> DataH;    // string and a pointer to the next TTStrTrieNode (string -> TTStrTrieNode)
	TInt Id;


public:
	// Constructors and Destructor function
	TTStrTrieNode();
	TTStrTrieNode(TSIn& SIn);
	~TTStrTrieNode();

	// Get & Set functions
	TInt GetUId() const;
	void SetUId(TInt Id);
	THash<TStr,TTStrTrieNode> GetDataH() const;
	void SetDataH(THash<TStr,TTStrTrieNode> DataH);

	// Management functions
	void Load(TSIn& SIn);
	void Save(TSOut& SOut) const;
	void Clr(const bool& DoDel=true, const int& NoDelLim=-1, const bool& ResetDat=true);

	// Processing functions
	void AddWord(TStr Word);
	bool HasWord(TStr Word) const;
	TTStrTrieNode& GetNextNodePt(TStr Word);
};


class TStrTrie
{
private:
	TTStrTrieNode* RootPt;    // word -> next TTStrTrieNodes
	TInt MinLen;
	TBool DoRemoveSymbols;


public:
	// Constructors and Destructor function
	TStrTrie();
	TStrTrie(TInt MinLen, TBool DoRemoveSymbols);
	TStrTrie(TSIn& SIn);
	~TStrTrie();

	// Get & Set functions
	bool GetDoRemoveSymbols() const;
	void SetDoRemoveSymbols(bool DoRemoveSymbols);
	TInt GetMinLen() const;

	// Management functions
	void Load(TSIn& SIn);   // static TPt<TStrTrie>
	void Save(TSOut& SOut) const;
	void Clr(const bool& DoDel=true, const int& NoDelLim=-1, const bool& ResetDat=true);

	// Processing functions
	static TStr RemoveSymbols(TStr& Text);
	void AddSentence(TStr& Sentence, TInt ItsId);
	void AddSentence(char* Sentence, TInt ItsId);
	TIntV FindSentence(char* Sentence) const;
	TIntV FindSentence(TStr& Sentence) const;
};

#endif /* TSTRTRIE_H_ */
