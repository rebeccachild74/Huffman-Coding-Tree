#include "stdafx.h"
#include "HuffmanTreeInterface.h"
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;
class HuffmanTree : HuffmanTreeInterface
{
private:

	
	const int BITMASK[8] = { 1 , 2, 4 , 8,  16,  32,  64,  128 };
	
	class BinaryNode
	{
	public:
		string element; // string in it or below node
		int frequency; // contains the frequency of node
		BinaryNode *left;
		BinaryNode *right;
		
		BinaryNode(const string & theElement, int frequency =0, BinaryNode *left = NULL, BinaryNode *right = NULL)
			: element( theElement ), frequency( frequency ), left( left ), right( right)
		{

		}
		
		const bool operator < (const BinaryNode &r) const {
			return (frequency < r.frequency);
		}
	};

	struct compareBinaryNodes : public binary_function<BinaryNode*, BinaryNode*,bool>
	{
		bool operator() (const BinaryNode* p1, const BinaryNode* p2)
		{
			return p1->frequency > p2->frequency;
		}
	};
	BinaryNode *root = nullptr;
	char EOFCharacter = 0;
		
	void makeEmpty(BinaryNode * t);
	void printTree(BinaryNode *t, std::ostream & out) const;
	void printCodes(BinaryNode *t, std::ostream & out, string code) const;

	void saveTree(BinaryNode * current, map<int, string> & mapOfTree, int index);
	void saveTree(std::ostream & out);
	
	void rebuildTree(BinaryNode * node, int index, map<int, string>& mapOfTree);
	void rebuildTree(ifstream & file);

	BinaryNode * buildTree(string frequencyText);
	bool getBit(unsigned char byte, int position) const;
	unsigned char setBit(unsigned char byte, int position) const;

public:
	
	HuffmanTree(string frequencyText);
	HuffmanTree(ifstream & frequencyStream);
	~HuffmanTree();

	void printTree(std::ostream & out = cout) const;
	void printCodes(std::ostream & out = cout) const;
	void printBinary(vector<char> bytes, std::ostream & out = cout) const;
	void printBits(char binary, std::ostream & out = cout) const;

	string getCode(char letter) const;
	

	void makeEmpty();

	vector<char> encode(string stringToEncode);
	string decode(vector<char> endcodedBytes);
	
		
	void uncompressFile(string compressedFileName, string uncompressedToFileName);
	void compressFile(string compressedFileName, string uncompressedFileName,bool buildTree = true);

	



};