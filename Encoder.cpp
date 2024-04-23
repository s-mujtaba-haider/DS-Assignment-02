#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;
struct Node{
	char ch;
	int freq;
	Node* left, * right;
	Node()
	{
		left = NULL;
		right = NULL;
	}
};
Node* getNode(char ch, int freq, Node* left, Node* right){
	Node* node = new Node();
	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;
	return node;
}
struct comp{
	bool operator()(Node* l, Node* r){
		return l->freq > r->freq;
	}
};
void encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}
void buildHuffmanTree(string text){
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}
	priority_queue<Node*, vector<Node*>, comp> pq;
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr)); 
	}
	while (pq.size() != 1)
	{
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}
	Node* root = pq.top();
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);
	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair : huffmanCode) {
		cout << pair.first << " : " << pair.second << '\n';
	}
	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}
	cout << "\nEncoded string is :\n\n" << str << '\n';
	cout << endl << endl;
}

int main(){
	cout << "File Read " << endl << endl;
	string text;
	vector<Node*>v;
	ifstream file("input_huff.txt");
	while (getline(file, text))
	{
		cout << text;
	}
	cout << endl;
	file.close();
	int len = text.length();
	for (int i = 0; i < len; i++)
	{
		bool b = false;
		for (int a = 0; a < v.size(); a++)
		{
			if (v[a]->ch == text[i])
			{
				v[a]->freq++;
				b = true;
			}
		}
		if (b == false)
		{
			Node* temp = new Node();
			temp->ch = text[i];
			temp->freq = 1;
			v.push_back(temp);
		}
	}
	cout << endl << "Frequency " << endl;
	for (int a = 0; a < v.size(); a++)
	{
		cout << v[a]->ch << " : ";
		cout << v[a]->freq;
		cout << endl;
	}
	cout << endl;
	buildHuffmanTree(text);
	cout << endl << endl;
	return 0;
}

