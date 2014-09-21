/*
 * TestTrieLargely.cpp
 *
 *  Created on: Sep 21, 2014
 *      Author: omid55
 */
#include "TStrTrie.h"

TStrTrie trie;

int main()
{
	TStr qu;
	int q;
	THash< TStr , CascadeElementV > quotes;
	TZipIn ZquotesIn("lastData/QuotesData.rar");

	printf("TestTrieLargely starts ...\n\n");
	trie.SetDoRemoveSymbols(true);
	quotes.Load(ZquotesIn);
	printf("QuotesData loading done, it contains %d quotes.\n",quotes.Len());

	printf("Creating Quotes TStr Trie ...\n");
	for(q=0;q<quotes.Len();q++)
	{
		printf("%d\n",q);
		qu = quotes.GetKey(q);
		qu = qu.ToLc();
		trie.AddSentence(qu,q);
	}
	quotes.Clr();

	printf("Saving The Trie ...\n");
	TZipOut outModel("TESTQuotesTrieModel.rar");
	trie.Save(outModel);
	printf("TStr Trie Created and Saved Successfully.\n");

	return 0;
}

