// Omid55
/*
 * mytrie_testing.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: omid
 */

#include "TStrTrie.h"

int main(int argc, char* argv[])
{
	cout << "Start ..." << endl;
	TStrTrie t;
	t.SetDoRemoveSymbols(true);

//	cout << "Loading ..." << endl;
//	TZipIn inModel("Data.rar");
//	t.Load(inModel);


	t.AddSentence("hello how are you??????",1);
	t.AddSentence("hello how are you doing",2);
	t.AddSentence("hello how are you now pal!!!  ",3);
	t.AddSentence("hello dude",4);
	t.AddSentence("hello how you can see me",5);
	t.AddSentence("hello how you can do this",6);
	t.AddSentence("hi fellow",7);
	t.AddSentence("cheers",8);
	t.AddSentence("hello how you can do",9);


	cout << "Saving ..." << endl;
	TZipOut outModel("Data.rar");
	t.Save(outModel);

	cout << "Min Len is: " << t.GetMinLen() << endl;

	TIntV foundIds = t.FindSentence("dude hello how are you, my man, you cool buddy? let's hello how you can do this ? go grab some lunch fellow cheers");
	cout << "The Length of Found Indices Is: " << foundIds.Len() << endl << "They are:" << endl << endl;
	for(int i=0;i<foundIds.Len();i++)
	{
		cout << foundIds[i] << endl;
	}
	cout << "THE END" << endl;

	return 0;
}
