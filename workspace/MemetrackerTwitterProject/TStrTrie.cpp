// Omid55
// String Trie Implementation

/*
 * TStrTrie.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: Omid
 */

#include "TStrTrie.h"

// ----------------------------------------------------
// 				TTStrTrieNode IMPLEMENTATION
// ----------------------------------------------------
TTStrTrieNode::TTStrTrieNode()
{
	Id = TInt(-1);
}

TTStrTrieNode::TTStrTrieNode(TSIn& SIn)
{
	Load(SIn);
}

TTStrTrieNode::~TTStrTrieNode()
{
	DataH.Clr();
}

TInt TTStrTrieNode::GetUId() const
{
	return Id;
}

void TTStrTrieNode::SetUId(TInt id)
{
	this->Id = id;
}

THash<TStr,TTStrTrieNode> TTStrTrieNode::GetDataH() const
{
	return DataH;
}

void TTStrTrieNode::SetDataH(THash<TStr,TTStrTrieNode> DataH)
{
	this->DataH = DataH;
}

void TTStrTrieNode::Load(TSIn &SIn)
{
	this->DataH.Load(SIn);
	this->Id.Load(SIn);
}

void TTStrTrieNode::Save(TSOut& SOut) const
{
	this->DataH.Save(SOut);
	this->Id.Save(SOut);
}

void TTStrTrieNode::Clr(const bool& DoDel, const int& NoDelLim, const bool& ResetDat)
{
	DataH.Clr();
}

void TTStrTrieNode::AddWord(TStr Word)
{
	DataH.AddDat(Word,TTStrTrieNode());
}

bool TTStrTrieNode::HasWord(TStr Word) const
{
	return DataH.GetKeyId(Word) != -1;
}

TTStrTrieNode& TTStrTrieNode::GetNextNodePt(TStr Word)
{
	return DataH.GetDat(Word);
}



// ----------------------------------------------------
// 				TSTR TRIE IMPLEMENTATION
// ----------------------------------------------------
TStrTrie::TStrTrie()
{
	RootPt = new TTStrTrieNode();
	MinLen = 1000;
	DoRemoveSymbols = false;
}

TStrTrie::TStrTrie(TInt MinLen, TBool DoRemoveSymbols)
{
	RootPt = new TTStrTrieNode();
	this->MinLen = MinLen;
	this->DoRemoveSymbols = DoRemoveSymbols;
}

TStrTrie::TStrTrie(TSIn& SIn)
{
	RootPt = new TTStrTrieNode();
	Load(SIn);
}

TStrTrie::~TStrTrie()
{
	delete RootPt;
}

void TStrTrie::Clr(const bool& DoDel, const int& NoDelLim, const bool& ResetDat)
{
	RootPt->Clr();
}

void TStrTrie::Load(TSIn &SIn)
{
	RootPt->Load(SIn);
	MinLen.Load(SIn);
	DoRemoveSymbols.Load(SIn);
}

void TStrTrie::Save(TSOut& SOut) const
{
	RootPt->Save(SOut);
	MinLen.Save(SOut);
	DoRemoveSymbols.Save(SOut);
}


TInt TStrTrie::GetMinLen() const
{
	return MinLen;
}

bool TStrTrie::GetDoRemoveSymbols() const
{
	return DoRemoveSymbols;
}

void TStrTrie::SetDoRemoveSymbols(bool DoRemoveSymbols)
{
	this->DoRemoveSymbols = DoRemoveSymbols;
}

void TStrTrie::AddSentence(char* Sentence,TInt ItsId)
{
	TStr tmp(Sentence);
	AddSentence(tmp,ItsId);
}

void TStrTrie::AddSentence(TStr& Sentence,TInt ItsId)
{
	if(DoRemoveSymbols)
	{
		Sentence = TStrTrie::RemoveSymbols(Sentence);
	}

	int i;
	TStr word;
	TStrV words;
	TTStrTrieNode* current = RootPt;
	Sentence.SplitOnAllCh(' ',words,true);
	MinLen = min(MinLen,TInt(words.Len()));
	for(i=0;i<words.Len();i++)
	{
		word = words[i];
		if(!current->HasWord(word))
		{
			current->AddWord(word);
		}
		current = &current->GetNextNodePt(word);
	}
	current->SetUId(ItsId);
}

TStr TStrTrie::RemoveSymbols(TStr& Text)
{
////	cout << Text.CStr() << endl;
//	TStr res;
//	char ch;
//	int i;
//	for(i=0;i<Text.Len();i++)
//	{
//		ch = Text.GetCh(i);
//
//		if('a'<=ch<='z' || '0'<=ch<='9')
//		{
//			res += TStr(ch);
//		}
//	}
////	cout << res.CStr() << endl;

	// Symbols
	Text.DelChAll('.');
	Text.DelChAll(':');
	Text.DelChAll('@');
	Text.DelChAll('?');
	Text.DelChAll('!');
	Text.DelChAll('(');
	Text.DelChAll(')');
	Text.DelChAll('[');
	Text.DelChAll(']');
	Text.DelChAll('-');
	Text.DelChAll('+');
	Text.DelChAll('*');
	Text.DelChAll('/');
	Text.DelChAll('\\');
	Text.DelChAll('~');
	Text.DelChAll('#');
	Text.DelChAll('$');
	Text.DelChAll('&');
	Text.DelChAll('=');
	Text.DelChAll('{');
	Text.DelChAll('}');
	Text.DelChAll('|');
	Text.DelChAll('"');
	Text.DelChAll('\'');
	Text.DelChAll(',');
	Text.DelChAll('`');
	Text.DelChAll('<');
	Text.DelChAll('>');
	Text.DelChAll('%');
	Text.DelChAll('^');
	Text.DelChAll('_');
	Text.DelChAll(';');

	// Numbers
	Text.DelChAll('0');
	Text.DelChAll('1');
	Text.DelChAll('2');
	Text.DelChAll('3');
	Text.DelChAll('4');
	Text.DelChAll('5');
	Text.DelChAll('6');
	Text.DelChAll('7');
	Text.DelChAll('8');
	Text.DelChAll('9');

	return Text;
}

TIntV TStrTrie::FindSentence(char* Sentence) const
{
	TStr tmp(Sentence);
	return FindSentence(tmp);
}

TIntV TStrTrie::FindSentence(TStr& Sentence) const
{
	if(DoRemoveSymbols)
	{
		Sentence = TStrTrie::RemoveSymbols(Sentence);
	}

	TIntV result;
	int i,j;
	TStrV words;
	TTStrTrieNode* current;
	Sentence.SplitOnAllCh(' ',words,true);
	for(i=0;i<words.Len()-GetMinLen()+1;i++)
	{
		current = RootPt;
		for(j=i;j<words.Len();j++)
		{
			if(current->HasWord(words[j]))
			{
				current = &current->GetNextNodePt(words[j]);
				if(current->GetUId() != -1)
				{
					result.Add(current->GetUId());
				}
			}
			else
			{
				break;
			}
		}
	}

	return result;
}
// ----------------------------------------------------

