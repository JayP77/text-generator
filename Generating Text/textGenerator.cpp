//  Project 2 - Generating Text
//  Jay Patel
//  Net ID : Jpate260
//  CS 251 data strcutures
//  This project will read in file and make keys and values from words within 
//  file then it will print out the map created after it is built
//  and text can also be generated 

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include "myrandom.h"

using namespace std;
//
//  fileCheck is used to check if the file input is valid
//
int fileCheck(string fileName, int &check) {
	fstream inFile(fileName);
	if(!inFile.is_open()) {
		check = -1;
		return check;
	} else {
		check = 1;
		return check;
	}
}  //  end of fileCheck

//
//  fileRead reads in the file and stores in words for keys and values
//
void fileRead(string fileName, map< vector<string> , vector<string> > &map, int nGram) {
	fstream inFile(fileName);
	vector<string> key;
	vector<string> value;
	vector<string> tempHold;
	int n = nGram;
	int count = 0;
	string word;
	while(inFile >> word) {
		if(count < n-1) {
			key.push_back(word);
			tempHold.push_back(word);
		} else {
			if(map.count(key) != 0) {
				value.push_back(word);
				map[key].push_back(word);
				value.clear();
				key.erase(key.begin(), key.begin()+1);
			} else {
				value.push_back(word);
				map[key] = value;
				key.erase(key.begin(), key.begin()+1);
				value.clear();
			}
			key.push_back(word);
			count++;
		}
		count++;
	}
	//  used for wrapping back around
	for(int i = 0; i < n-1; i++) {
		string tempWord = tempHold[i];
		if(map.count(key) != 0) {
				value.push_back(tempWord);
				map[key].push_back(tempWord);
				value.clear();
				key.erase(key.begin(), key.begin()+1);
			} else {
				value.push_back(tempWord);
				map[key] = value;
				key.erase(key.begin(), key.begin()+1);
				value.clear();
			}
			key.push_back(tempWord);
	}
}  //  end of fileRead

//
//  printMap is used to print out the map using a for-each loop
//
void printMap(map< vector<string> , vector<string> > &map, int &nGram) {
	int n = nGram;
	int count = 0;
	for(auto &e : map) {
	 	cout << "{";
	 	count = 0;
	 	for(auto &t : e.first) {
	 		int k = e.first.size();
	 		if(count == k-1) {
	 			cout << t;
	 		} else if (count <= n) {
				cout << t << " ";
				count++;
	 		}
	 	}
		 count = 0;
		 cout << "} ";
		 cout << "->";
		 cout << " {";
		for (auto &v : e.second) {
			int k = e.second.size();
			if (count == k-1) {
	 			cout << v;
	 		} else if (count <= k) {
				cout << v << " ";
				count++;
	 		}
		}
		cout << "}";
		cout << endl;
	 }
}  //  end of printMap

//
//  textGen is used to generate random text
//
void textGen(map< vector<string> , vector<string> > &map, int &nGram, int &wordGenerate) {
	vector<string> rKey;
	int count = 0;
	string tempWord;
	int k = 0;
	int n = randomInteger(0, map.size()-1);
	for(auto &e : map) {
		if(count == n) {
			rKey = e.first;
			count++;
		} else {
			count++;
		}
		k = rKey.size();
	}
	cout << "\n...";
	for(int i = 0; i < k; i++) {
			cout << rKey[i]+" ";
	}
	for (int j = nGram-1; j < wordGenerate; j++) {
		n = randomInteger(0, map[rKey].size()-1);
		string sentence = map[rKey].at(n);
		rKey.push_back(sentence);
		rKey.erase(rKey.begin(), rKey.begin()+1);
		if(j == wordGenerate-1){
			cout << sentence;
		} else {
		cout << sentence+" ";
		}
	}
	cout << "...";
}  //  end of text generator

int main() {
	string fileName;
	map < vector<string> , vector<string> > map;
	int nGram = 0;
	int wordGenerate = 0;
	int check = 0;  //  checks if file is valid
	cout << "Welcome to the Text Generator." << endl;
	cout << "This program makes random text based on a document." << endl;
	cout << "Input file name?  ";
	cin >> fileName;
	fileCheck(fileName, check);
	if(check == -1) {
		while(check == -1) {
		cout << "Invalid file, try again:  ";
		cin >> fileName;
		fileCheck(fileName, check);
		}
	}
	cout << "Value of N?  ";
	cin >> nGram;
	if(nGram <= 1) {
		cout << "N must be > 1, try again:  ";
		cin >> nGram;
	}
	cout << "Total words you'd like to generate?  ";
	cin >> wordGenerate;
	if(wordGenerate < nGram) {
		while(wordGenerate < nGram) {
			cout << "Total words must be at least N, try again:  ";
			cin >> wordGenerate;
		}
	}
	cout << "Type b-build map, p-print map, g-generate text, s-start over,";
	cout << " x-to exit: " << endl;
	string input;
	bool terminate = false;
	do {
		cin >> input;
		if(input == "x") {
			break;
		}
		if(input == "b") {
			cout << "...Building map: " << fileName << "..." << endl;
			fileRead(fileName, map, nGram);
		}
		if(input == "p") {
			printMap(map, nGram);
		}
		if(input == "g") {
			textGen(map, nGram, wordGenerate);
		}
		if(input == "s") {
			map.clear();
			cout << "Welcome to the Text Generator." << endl;
			cout << "This program makes random text based on a document." << endl;
			cout << "Input file name?  ";
			cin >> fileName;
			fileCheck(fileName, check);
			if(check == -1) {
				while(check == -1) {
				cout << "Invalid file, try again:  ";
				cin >> fileName;
				fileCheck(fileName, check);
				}
			}
			cout << "Value of N?  ";
			cin >> nGram;
			if(nGram <= 1) {
				cout << "N must be > 1, try again:  ";
				cin >> nGram;
			}
			cout << "Total words you'd like to generate?  ";
			cin >> wordGenerate;
			if(wordGenerate < nGram) {
				while(wordGenerate < nGram) {
					cout << "Total words must be at least N, try again:  ";
					cin >> wordGenerate;
				}
			}
		}
		cout << "\nType b-build map, p-print map, g-generate text, s-start";
		cout << " over, x-to exit: ";
	} while (terminate != true);
	return 0;
}  //  end of int main
