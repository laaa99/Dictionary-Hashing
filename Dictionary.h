/*
Lucy Tran
CPTS 223
PA3: Dictionary Hashing
Dictionary Class

Description: Hash table = (vector) of vectors containing Word
			 TableSize = Starting size of hash table is 101
			 N = # of words in hash table

			 Insert(Word)     //inserts words into hash table
			 contains(string) //tells if the hash table contains the word
			 delete(string) //deletes word from hash table
			 rehash() //doubles, newPrime TableSize and copies old hash table into the new hash table
			 getWord(string) //find word in hash table and returns it
			 newPrime(int) //finds next prime after the num
			 prime(int) //check if the number is prime

*/

#ifndef DICTIONARY_H
#define DICTIONARY_H
#define STARTING_SIZE 101

#include "Word.h"
#include <vector>
//#include <list>
//#include <xutility> //Find

using std::vector;
//using std::list; //Separate chaining
//using std::move;
//using std::find;

//Iterate through list to find position of Word
//for (; itVec != tempVec.end() && (*itVec).getWord() == word; ++itVec) {}
//(find(begin(tempVec), end(tempVec), tempWord) != end(tempVec));

class Dictionary {
public:
	/*Constructor*/
	Dictionary() {
		_N = 0;
		_tableSize = STARTING_SIZE;
		_hashTable.resize(_tableSize);
	}

	/*Setters*/

	/*Getters*/
	int getN() {
		return _N;
	}
	int getTableSize() {
		return _tableSize;
	}
	double getLoadFactor() {
		return _loadFactor;
	}

	/*Public functions*/

	/*Hashes the Word's key() and adds it to the hash table if it is not already there
	Updates (overwrites) old entry if there is already the same Word in the hash table*/
	void insert(Word &newWord) {
		/*Hash to find key of the word*/
		unsigned int key = newWord.hash(newWord.getWord(), _tableSize);

		/*Temp vector containing word*/
		vector<Word> &tempVec = _hashTable[key];
		//copyVector(_hashTable[key], tempVec);

		/*Vector iterator*/
		vector<Word>::iterator itVec = tempVec.begin();

		/*Find position of Word*/
		for (; itVec != tempVec.end() && ((*itVec).getWord().compare(newWord.getWord()) && (*itVec).getDef().compare(newWord.getDef())); ++itVec) {}

		/*If Word already exists, overwrite*/
		if (itVec != end(tempVec)) {
			/*Overwrite old entry*/
			(*itVec).setWord(newWord.getWord());
			(*itVec).setDef(newWord.getDef());
		}

		/*If not, insert Word*/
		else {
			tempVec.insert(tempVec.begin(), newWord); //Insert to the front of the vector
			++_N; //Increase number of words
			_loadFactor = (double)_N / _tableSize; //calculate load factor
			rehash();
		}
	}
	/*Searches the hash table by a string
	Convert the string to a key, then hash it and search the vector of Words to see if it is in the hash table*/
	bool contains(string &word) {
		/*Hash to find key of the word*/
		Word tempWord;
		transform(word.begin(), word.end(), word.begin(), ::toupper); //capitalize characters
		tempWord.setWord(word);
		unsigned int key = tempWord.hash(word, _tableSize);

		/*Temp vector containing word*/
		vector<Word> &tempVec = _hashTable[key];

		/*Vector Iterator*/
		vector<Word>::iterator itVec = tempVec.begin();

		/*Find the word in the dictionary*/
		for (; itVec != tempVec.end() && word.compare((*itVec).getWord()); ++itVec) {}

		//if found, returns true; otherwise returns false
		return !(itVec == end(tempVec));
	}
	/*Finds an entry using the passed in word, erases it (vector.erase()) from the hash table, then returns it
	Returns nullptr if word is not in the table*/
	Word * deleteWord(string &word) {
		/*Hash to find key of the word*/
		Word *tempWordPtr = new Word; //allocate memory
		transform(word.begin(), word.end(), word.begin(), ::toupper); //capitalize characters
		tempWordPtr->setWord(word);
		unsigned int key = tempWordPtr->hash(word, _tableSize);

		/*Temp vector containing word*/
		vector<Word> &tempVec = _hashTable[key];

		/*Vector iterator*/
		vector<Word>::iterator itVec = tempVec.begin();

		/*Find the word in the dictionary*/
		for (; itVec != tempVec.end() && word.compare((*itVec).getWord()); ++itVec) {}

		/*If found, delete the Word*/
		if (itVec != end(tempVec)) {

			/*Word stored before deleted*/
			tempWordPtr->setDef((*itVec).getDef());

			tempVec.erase(itVec); //delete word
			_N--; //decrease number of words
			return tempWordPtr;
		}

		else {
			return nullptr;
		}
	}
	//Return the word requested from the dictionary
	Word & getWord(string &word) {
		/*Hash to find key of the word*/
		Word tempWord;
		transform(word.begin(), word.end(), word.begin(), ::toupper); //capitalize characters
		tempWord.setWord(word);
		unsigned int key = tempWord.hash(word, _tableSize);

		/*Temp vector containing word*/
		vector<Word> &tempVec = _hashTable[key];

		/*Vector Iterator*/
		vector<Word>::iterator itVec = tempVec.begin();

		/*Find the word in the dictionary*/
		for (; itVec != tempVec.end() && word.compare((*itVec).getWord()); ++itVec) {}

		return *itVec;
	}
	
private:
	vector<vector<Word>> _hashTable;
	int _N; //how many words it holds
	int _tableSize; //Size of the table
	double _loadFactor; //N/tableSize

	/*Private Functions*/

	/*Called if the table gets above a load factor (N/Table Size) of 1.0 during an insert of a new Word
	Doubles the table size then finds the next prime number for the new table size*/
	void rehash() {
		/*Rehash only if load factor is above 1.0*/
		if (_loadFactor >= 1.0) {
			/*Copy old table*/
			vector<vector<Word>> oldHashTable = _hashTable; //old table copied

			/*Clear new table*/
			for (vector<Word> & aVec : _hashTable) {
				aVec.clear();
			}
			_N = 0; //clear # of words in hashtable

			/*Create new double-sized table*/
			_tableSize = newPrime(2 * _tableSize); //new table size
			_hashTable.resize(_tableSize); //Double the new table

			/*Copy table*/
			for (vector<Word> &aVec : oldHashTable) {
				for (Word &word : aVec) {
					insert(word); //Copy word over
				}
			}
		}
	}

	//https://gist.github.com/alabombarda/f3944cd68dda390d25cb
	/*Find the next closest prime number above num*/
	int newPrime(int num) {
		int newP = num;
		bool found = false;

		/*Continue incrementing until you find a prime*/
		while (!found) {
			newP++;
			/*Found it!*/
			if (prime(newP)) {
				found = true;
			}
		}
		
		return newP;
	}
	
	/*Figure out if num is prime*/
	bool prime(int num) {
		/*Incrementor*/
		int i = 2;

		/*Check for factors*/
		for (; i <= num / 2; i++) {
			/*Non-prime check*/
			if (num % i == 0) {
				return false;
			}
		}

		return true;
	}
};

#endif