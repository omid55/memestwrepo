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
// 				NODE IMPLEMENTATION
// ----------------------------------------------------
Node::Node()
{
	id = TInt(-1);
}

Node::Node(TSIn& SIn)
{
	Load(SIn);
}

Node::~Node()
{
	data.Clr();
}

TInt Node::getId() const
{
	return id;
}

void Node::setId(TInt id)
{
	this->id = id;
}

THash<TStr,Node> Node::getData() const
{
	return data;
}

void Node::setData(THash<TStr,Node> data)
{
	this->data = data;
}

void Node::Load(TSIn &SIn)
{
	this->data.Load(SIn);
	this->id.Load(SIn);
}

void Node::Save(TSOut& SOut) const
{
	this->data.Save(SOut);
	this->id.Save(SOut);
}

void Node::Clr(const bool& DoDel, const int& NoDelLim, const bool& ResetDat)
{
	data.Clr();
}

void Node::addWord(TStr word)
{
	data.AddDat(word,Node());
}

bool Node::hasWord(TStr word) const
{
	return data.GetKeyId(word) != -1;
}

Node& Node::getNextNode(TStr word)
{
	return data.GetDat(word);
}

// ----------------------------------------------------
// 				TSTR TRIE IMPLEMENTATION
// ----------------------------------------------------
TStrTrie::TStrTrie()
{
	root = new Node();
	minLen = 1000;
	doRemoveSymbols = false;
}

TStrTrie::TStrTrie(TSIn& SIn)
{
	root = new Node();
	Load(SIn);
}


TStrTrie::~TStrTrie()
{
	delete root;
}

void TStrTrie::Clr(const bool& DoDel, const int& NoDelLim, const bool& ResetDat)
{
	root->Clr();
}

void TStrTrie::Load(TSIn &SIn)
{
	root->Load(SIn);
	minLen.Load(SIn);
	doRemoveSymbols.Load(SIn);
}

void TStrTrie::Save(TSOut& SOut) const
{
	root->Save(SOut);
	minLen.Save(SOut);
	doRemoveSymbols.Save(SOut);
}


TInt TStrTrie::getMinLen() const
{
	return minLen;
}

bool TStrTrie::getDoRemoveSymbols() const
{
	return doRemoveSymbols;
}

void TStrTrie::setDoRemoveSymbols(bool d)
{
	doRemoveSymbols = d;
}

void TStrTrie::add(char* sentence,TInt itsId)
{
	TStr tmp(sentence);
	add(tmp,itsId);
}

void TStrTrie::add(TStr& sentence,TInt itsId)
{
	if(doRemoveSymbols)
	{
		sentence = TStrTrie::RemoveSymbols(sentence);
	}

	int i;
	TStr word;
	TStrV words;
	Node* current = root;
	sentence.SplitOnAllCh(' ',words,true);
	minLen = min(minLen,TInt(words.Len()));
	for(i=0;i<words.Len();i++)
	{
		word = words[i];
		if(!current->hasWord(word))
		{
			current->addWord(word);
		}
		current = &current->getNextNode(word);
	}
	current->setId(itsId);
}

TStr TStrTrie::RemoveSymbols(TStr& text)
{
////	cout << text.CStr() << endl;
//	TStr res;
//	char ch;
//	int i;
//	for(i=0;i<text.Len();i++)
//	{
//		ch = text.GetCh(i);
//
//		if('a'<=ch<='z' || '0'<=ch<='9')
//		{
//			res += TStr(ch);
//		}
//	}
////	cout << res.CStr() << endl;

	// Symbols
	text.DelChAll('.');
	text.DelChAll(':');
	text.DelChAll('@');
	text.DelChAll('?');
	text.DelChAll('!');
	text.DelChAll('(');
	text.DelChAll(')');
	text.DelChAll('[');
	text.DelChAll(']');
	text.DelChAll('-');
	text.DelChAll('+');
	text.DelChAll('*');
	text.DelChAll('/');
	text.DelChAll('\\');
	text.DelChAll('~');
	text.DelChAll('#');
	text.DelChAll('$');
	text.DelChAll('&');
	text.DelChAll('=');
	text.DelChAll('{');
	text.DelChAll('}');
	text.DelChAll('|');
	text.DelChAll('"');
	text.DelChAll('\'');
	text.DelChAll(',');
	text.DelChAll('`');
	text.DelChAll('<');
	text.DelChAll('>');
	text.DelChAll('%');
	text.DelChAll('^');
	text.DelChAll('_');
	text.DelChAll(';');

	// Numbers
	text.DelChAll('0');
	text.DelChAll('1');
	text.DelChAll('2');
	text.DelChAll('3');
	text.DelChAll('4');
	text.DelChAll('5');
	text.DelChAll('6');
	text.DelChAll('7');
	text.DelChAll('8');
	text.DelChAll('9');

	return text;
}

TIntV TStrTrie::find(char* sentence) const
{
	TStr tmp(sentence);
	return find(tmp);
}

TIntV TStrTrie::find(TStr& sentence) const
{
	if(doRemoveSymbols)
	{
		sentence = TStrTrie::RemoveSymbols(sentence);
	}

	TIntV result;
	int i,j;
	TStrV words;
	Node* current;
	sentence.SplitOnAllCh(' ',words,true);
	for(i=0;i<words.Len()-getMinLen()+1;i++)
	{
		current = root;
		for(j=i;j<words.Len();j++)
		{
			if(current->hasWord(words[j]))
			{
				current = &current->getNextNode(words[j]);
				if(current->getId() != -1)
				{
					result.Add(current->getId());
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

