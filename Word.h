/*
Lucy Tran
CPTS 223
PA3: Dictionary Hashing
Word Class

Description: Holds a word and its definition.
			 hash(string, int) //returns the key for a word to be inserted into a hash table
*/

#ifndef WORD_H
#define WORD_H

#include <string>
#include <algorithm> //uppercase
using std::string;
using std::transform;

class Word {
public:
	/*Constructors*/
	Word() {
		_word = "";
		_def = "";
	}
	Word(string & newWord, string & newDef) {
		setWord(newWord);
		setDef(newDef);
	}

	/* Hash routine for string objects */
	unsigned int hash(const string &word, int tableSize) {
		unsigned int hashVal = 0;
		/*For each character in a string*/
		for (char ch : word) { //The word = key
			hashVal = 37 * hashVal + ch;
		}
		return hashVal % tableSize;
	}

	/*Getters*/
	string getWord() {
		return _word;
	}
	string getDef() {
		return _def;
	}

	/*Setters*/
	void setWord(const string &newWord) {
		_word = newWord;
	}
	void setDef(const string &newDef) {
		_def = newDef;
	}

private:
	string _word; //THE WORD
	string _def; //THE DEFINITION OF THE WORD
};

#endif
