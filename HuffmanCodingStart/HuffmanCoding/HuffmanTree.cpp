#include "stdafx.h"
#include "HuffmanTree.h"
#include <string>
#include <vector>
#include <fstream> 
#include <iostream>
#include <queue>    
#include <algorithm>
#include <iomanip> 
#include <bitset>
#include <map>
#include <sstream>
using namespace std;

inline bool HuffmanTree::getBit(unsigned char byte, int position) const
{

	return (byte  & BITMASK[position]);
}
// Usage
//mybyte = setBit(mybyte,4);
// This sets the bit in position 4
inline unsigned char HuffmanTree::setBit(unsigned char byte, int position) const
{
	return  byte | BITMASK[position];
}

void HuffmanTree::printBits(char binary, std::ostream & out) const
{
	for (size_t i = 0; i < sizeof(char) * 8; i++)
	{
		if (getBit(binary, i))
		{
			out << 1;
		}
		else
		{
			out << 0;
		}
	}
}
void HuffmanTree::printBinary(vector<char> bytes, std::ostream & out) const
{
	for (char byte : bytes) 
	{
		printBits(byte, out);
		out << "-";
	}
}

string HuffmanTree::getCode(char letter) const
{
	//static string temp = "Heyo";
	string code = "";

	/*if (*(temp.c_str()) == letter) {
		return temp;
	}*/

	if (root->element.find(letter) < 256) { //checks if letter is in string

		BinaryNode * temp = root;
		while (temp->left != nullptr && temp->right != nullptr) {
			if (temp->left->element.find(letter) < 256) { // checks if letter is in string and valid
				temp = temp->left;
				code = code + "0"; // adds a 0 if to the left
			}
			else if (temp->right->element.find(letter) < 256) {
				temp = temp->right;
				code = code + "1"; // adds a 1 if to the right
			}
		}
	}

	return code;
}



void HuffmanTree::makeEmpty(BinaryNode * t)
{
//	BinaryNode * temp = t;

	/*if (t->left != nullptr) {
		makeEmpty(t->left);
		t = nullptr;
	}
	else {
		t = nullptr;
	}
	if (t->right != nullptr) {
		makeEmpty(t->right);
		t = nullptr;
	}
	else {
		t = nullptr;
	}
	t = nullptr;*/
}

void HuffmanTree::printTree(BinaryNode *node, std::ostream & out) const
{// complete for lab

	if (node == nullptr) {
		return;
	}
	printTree(node->left, out);
	cout << node->element << " Frequency: " << node->frequency << endl;
	printTree(node->right, out);

}

void HuffmanTree::printCodes(BinaryNode *node, std::ostream & out, string code) const
{ // complete for lab

	if (node == nullptr) {
		return;
	}
	//char temp = node->element;
	printCodes(node->left, out, code + "0" );
	if (node->element.length() == 1) {
		char temp = node->element[0];
		cout << node->element << " Code: " << getCode(temp) << endl;
	}
	//cout << node->element << "Code: " << getCode(node->element) << endl;
	printCodes(node->right, out, code + "1");
	
}

void HuffmanTree::saveTree(BinaryNode * current, map<int, string> &mapOfTree, int index)
{
	
}


void HuffmanTree::saveTree(std::ostream & compressedFileStream)
{
	
	
}

void HuffmanTree::rebuildTree(BinaryNode * node, int index, map<int, string> &mapOfTree)
{
	
		

}

void HuffmanTree::rebuildTree(ifstream & compressedFile)
{

	

}


HuffmanTree::BinaryNode * HuffmanTree::buildTree(string frequencyText) //returns the root of the tree we build
{
	priority_queue<HuffmanTree::BinaryNode *, vector<HuffmanTree::BinaryNode *>, compareBinaryNodes > nodes;

	int frequencies[256] = { 0 };

	for (int i = 0; i < frequencyText.length(); i++) {
		frequencies[frequencyText.at(i)]++; // increment what's in the array
		//cout << frequencyText.at(i) << ": " << frequencies[frequencyText.at(i)] << endl; // testing
	}
	
	// create nodes
	for (int i = 0; i < 256; i++) { 
		if (/*i < frequencyText.size() &&*/ frequencies[i] != 0) {

			BinaryNode * temp = new BinaryNode(string(1, i), frequencies[i]); // string(1,i) from Albert
			nodes.push(temp); //pushes into que
			//cout << temp->element << "  " << temp->frequency << endl; // testing that nodes were made
		}
	}
	
	while (nodes.size() != 1) { // combines 2 lowest frequency nodes until only one node (root) in que 

		BinaryNode * first = nodes.top(); // stores lowest node
		nodes.pop(); //removes lowest
		BinaryNode * second = nodes.top(); //stores second lowest node
		nodes.pop(); //removes second lowest

		int comboFreq = first->frequency + second->frequency;
		string comboElem = first->element + second->element;

		BinaryNode * comboNode = new BinaryNode(comboElem, comboFreq);

 		if ((first->element).size() == 1 && (second->element).size() > 1 && first->frequency < second->frequency) { // highest frequency goes on left

			comboNode->left = first;
			comboNode->right = second;
		}
		else if (first->frequency > second->frequency) {

			comboNode->left = first;
			comboNode->right = second;
		}
		else {

			comboNode->left = second;
			comboNode->right = first;

		}
		//cout << "comboNode: " << comboNode->element << "  " << "frequency: " << comboNode->frequency << endl; //testing
		nodes.push(comboNode);
	}
return nodes.top(); // the root
}



HuffmanTree::HuffmanTree(string frequencyText) //constructor
{

	root = buildTree(frequencyText);

}

HuffmanTree::HuffmanTree(ifstream & frequencyStream)
{


	std::string frequencyText((std::istreambuf_iterator<char>(frequencyStream)), std::istreambuf_iterator<char>());
	frequencyStream.close();
	if (frequencyText.size() > 0)
	{
root = buildTree(frequencyText);
	}


}

HuffmanTree::~HuffmanTree()
{

};
void HuffmanTree::printCodes(std::ostream & out) const
{
	printCodes(root, cout, "");
}


void HuffmanTree::printTree(std::ostream & out) const
{
	printTree(root, cout);

}

void HuffmanTree::makeEmpty()
{
	makeEmpty(root);
}
string HuffmanTree::decode(vector<char> encodedBytes)
{
	string decoded;
	BinaryNode * temp = root;

	for (int i = 0; i < encodedBytes.size(); i++) {
		if (encodedBytes[i] == '0') {
			temp = temp->left;
		}
		else if (encodedBytes[i] == '1') {
			temp = temp->right;
		}

		if (temp->left == nullptr && temp->right == nullptr) {
			decoded = decoded + temp->element;
			temp = root;
		}
	}


	return decoded;
}


vector<char> HuffmanTree::encode(string stringToEncode)
{

	stringToEncode.push_back(EOFCharacter);
	stringToEncode.push_back(EOFCharacter);

	vector<char> encoded;
	string temp = "";

	for (int i = 0; i < stringToEncode.length(); i++) {
		temp = getCode(stringToEncode.at(i));
		for (int j = 0; j < temp.length(); j++) {
			encoded.push_back(temp.at(j));
		}
	}
	for (int i = 0; i < encoded.size(); i++) {
		cout << encoded[i];
	}

	return encoded;
}


void HuffmanTree::uncompressFile(string compressedFileName, string uncompressedToFileName)
{
	ifstream compressedFile(compressedFileName, ios::out | ios::binary);

	ostringstream ss;
	ss << compressedFile.rdbuf();
	const string& s = ss.str();

	vector<char> vec(s.begin(), s.end());

	string decoded = decode(vec);
	cout << decoded;

	ofstream uncompressedFile(uncompressedToFileName);

	uncompressedFile << decoded;

}



void HuffmanTree::compressFile(string compressToFileName, string uncompressedFileName, bool buildNewTree)
{
	ifstream fin;
	fin.open(uncompressedFileName);
	vector<char> uncoded;

	while (fin) {
		uncoded.push_back(fin.get()); // gets each string and pushes back into vector
	}
	string convert = "";

	for (int i = 0; i < uncoded.size(); i++) {
		convert = convert + uncoded[i];
	}

	vector<char> encoded = encode(convert);

	ofstream compressedFile(compressToFileName, ios::out | ios::binary); 

	for (int i = 0; i < encoded.size(); i++){
	compressedFile << encoded[i];// writes vector out to file
}
}


