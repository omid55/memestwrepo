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
	t.setDoRemoveSymbols(true);

//	cout << "Loading ..." << endl;
//	TZipIn inModel("Data.rar");
//	t.Load(inModel);


	t.add("hello how are you??????",1);
	t.add("hello how are you doing",2);
	t.add("hello how are you now pal!!!  ",3);
	t.add("hello dude",4);
	t.add("hello how you can see me",5);
	t.add("hello how you can do this",6);
	t.add("hi fellow",7);
	t.add("cheers",8);
	t.add("hello how you can do",9);


	cout << "Saving ..." << endl;
	TZipOut outModel("Data.rar");
	t.Save(outModel);


	cout << "Min Len is: " << t.getMinLen() << endl;

	TIntV foundIds = t.find("dude hello how are you, my man, you cool buddy? let's hello how you can do this ? go grab some lunch fellow cheers");
	cout << "The Length of Found Indices Is: " << foundIds.Len() << endl << "They are:" << endl << endl;
	for(int i=0;i<foundIds.Len();i++)
	{
		cout << foundIds[i] << endl;
	}
	cout << "THE END" << endl;
	return 0;
}
