// HuffmanCoding.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "HuffmanTree.h"
#include <string>
#include <fstream>
#include <streambuf>
using namespace std;

int main()
{

	
	
	//Test 1
	HuffmanTree tree("HHHHEELLLLLLLOO WOOOOORRLLLLLLDP");
	//tree.printTree();
	tree.printCodes();
	//cout << "Code L :" <<tree.getCode('L') << endl;
	vector<char> encoded = tree.encode("HELP");

	
	
	////Test 2
	//vector<char> encoded = tree.encode("HELP");
	//tree.printBinary(ec);
	//cout << endl;
	cout << endl << tree.decode(encoded) << endl;
	//system("pause");

	//test 2
	std::ifstream frequencyStream("Bigo.txt");
	HuffmanTree tree2(frequencyStream);
	tree2.printTree();
	cout << endl;
//	tree2.printCodes();

	tree2.compressFile("BigO.bin", "Bigo.txt");
	cout << endl;
	tree2.makeEmpty();
	tree2.printTree();
	tree2.printCodes();
	tree2.uncompressFile("BigO.bin", "BigORebuilt.txt");
	tree2.printTree();
	tree2.printCodes();

	//Test 3
	/*std::ifstream frequencyStream("20000leagues.txt");
	HuffmanTree tree2(frequencyStream);
	tree2.printTree();
	tree2.printCodes();
	cout << "Code L :" << tree2.getCode('L') << endl;
	tree2.compressFile("20000leaguesComp.bin" ,"20000leagues.txt",true);
	tree2.uncompressFile("20000leaguesComp.bin", "20000leaguesRebuilt.txt");
	tree2.printTree();
	tree2.printCodes();*/

	// Try Other Files
	
	//// read in text file create string - might be useful
	//std::ifstream bigtext("20000leagues.txt");
	//std::string big((std::istreambuf_iterator<char>(bigtext)), std::istreambuf_iterator<char>());




	cout << endl;
	system("pause");
    return 0;
}

