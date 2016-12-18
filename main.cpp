/*
Lucy Tran
CPTS 223
PA3: Dictionary Hashing
Main function
	
Description: The dictionary.json file is parsed here. 
			 Words and definitions are added to the hashtable.
			 Then a user is asked to input a word to define.
			 The program ends when the user enters the 
			 END-OF-FILE. 
*/

#include "Dictionary.h"
#include "Word.h"
#include <iostream>
#include <fstream>
#include <ios>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::getline;
using std::ios;

//http://www.cprogramming.com/tutorial/lesson14.html
int main(int argc, char *argv[]) {

	/*If there are at least 2 arguments*/
	if (argc == 2) {
		//Open file using filename
		//ifstream infile("dictionary3.json", ios::in);

		/*Declare file and string for name of file*/
		ifstream infile(argv[1]);

		/*Check if the file is open*/
		if (infile.is_open()) {
			/*Declare Dictionary class*/
			Dictionary dictBook;

			/*Read file: Read strings in between quotes*/
			string skip;
			string word;
			string def;

			/*Add Words to dictionary here*/
			//int i = 0;
			while (infile.good()) {
				
				//http://stackoverflow.com/questions/33072293/reading-quoted-string-in-c
				getline(getline(infile, skip, '"'), word, '"');
				getline(getline(infile, skip, ' '), def, '}'); //Some definitions contain quotations inside

				//http://www.cplusplus.com/forum/beginner/14373/
				/*Get rid of quotations surrounding definitions*/
				def.erase(remove(def.begin(), def.begin() + 1, '"'), def.begin() + 1); //first quotation
				def.erase(remove(def.end() - 1, def.end(), '"'), def.end()); //last quotation

				/*Declare Word*/
				Word newWord(word, def);

				/*Insert the word into the hashtable*/
				dictBook.insert(newWord);
				//i++;
			}

			/*Close file*/
			infile.close();

			/*Testing deletions and insertions*/
			//string whatever = "johnny";
			//Word *deleted = dictBook.deleteWord(whatever);
			//if (deleted != nullptr) {
			//	cout << "Testing delete function: This word, \"" << deleted->getWord() << ",\" has been deleted!" << endl;
			//}
			//else {
			//	cout << "Testing delete function: This word, \"" << deleted->getWord() << ",\" does not exist!" << endl;
			//}
			////Re-insert
			//dictBook.insert(*deleted);
			//cout << "\nBefore overwrite: " << deleted->getWord() << "- " << deleted->getDef() << endl;
			//deleted->setDef("new def here");
			//dictBook.insert(*deleted); //Repeat *overwrite
			//cout << "After overwrite: " << deleted->getWord() << "- " << deleted->getDef() << endl << endl;
			//whatever = "dennis";
			//deleted = dictBook.deleteWord(whatever);
			//if (deleted != nullptr) {
			//	cout << "Testing delete function: This word, \"" << deleted->getWord() << ",\" has been deleted!" << endl;
			//}
			//else {
			//	cout << "Testing delete function: This word does not exist!\n" << endl;
			//}

			/*Print out information*/
			cout << "There are " << dictBook.getN() << " words." << endl;
			cout << "The size of the table is " << dictBook.getTableSize() << "." << endl;
			cout << "The load factor is " << dictBook.getLoadFactor() << "." << endl;;

			/*Input Word*/
			char input_c = '\0';
			string input = "";

			/*Keep on asking user what word to define until ^D*/
			while (input_c != EOF) {

				/*Clear input*/
				input_c = '\0';
				input = "";

				//Prompt
				cout << "\nWord to define: ";

				//while character inputted is not EOF or newline
				while (input_c != '\n' && input_c != EOF) {
					input_c = getchar();
					input += input_c; //append character
				}

				/*Remove \n character in input*/
				input.erase(remove(input.end() - 1, input.end(), '\n'), input.end()); //remove newline

				//User inputted a Word
				if (input_c == '\n') {
					//User wanted this Word
					Word lookUpWord;
					//Word found
					if (dictBook.contains(input)) {
						lookUpWord = dictBook.getWord(input);
						cout << lookUpWord.getWord() << ": " << lookUpWord.getDef() << endl; //Print out def and word
					}

					//Not found
					else {
						cout << "Word not found." << endl;
					}
				}
			}
		}

		else {
			cout << "Could not open file!" << endl;
		}
	}

	/*If there are less*/
	else {
		cout << "usage: " << argv[0] << " <filename>" << endl;
	}
	
	//Testing string comparisons
	//string one = "test";
	//string two = "Test";
	//string three = "TEST";
	//if (one.compare(two)) {
	//	cout << "\nequal" << endl;
	//}
	//if (one == three) {
	//	cout << "equal2" << endl;
	//}

	return 0;
}