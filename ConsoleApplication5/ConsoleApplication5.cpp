#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

int lives;
int length;
int counter;
int lineCounter = 0;
int tipLineCounter = 0;
string wordsTab[1000];
string tipTab[1000];
vector <char> tabCheck;
vector <char> checkedLetters;

void loadFile() {
	fstream wordsFile;
	fstream tipFile;
	string wordsLine;
	string tipLine;

	wordsFile.open("slowa.txt", ios::in);
	if (wordsFile.good() == true)
	{
		while (!wordsFile.eof())
		{
			getline(wordsFile, wordsLine);
	     	wordsTab[lineCounter] = wordsLine;
			lineCounter++;
		}
		wordsFile.close();
	}
	else {
		cout << "error!" << endl << "try again? y/n" << endl;
		char choose;
		cin >> choose;
		if (choose == 'y') {
			loadFile();
		}
		else {
			exit(0);
		}

	}
	tipFile.open("podpowiedzi.txt", ios::in);
	if (tipFile.good() == true)
	{
		while (!tipFile.eof())
		{
			getline(tipFile, tipLine);
			tipTab[tipLineCounter] = tipLine;
	     	tipLineCounter++;
		}
		
		tipFile.close();
	}
	else {
		cout << "error!" << endl << "try again? y/n" << endl;
		char choose;
		cin >> choose;
		if (choose == 'y') {
			loadFile();
		}
		else {
			exit(0);
		}
	}
}

vector<string> rollWord(int num) {
	srand(time(NULL));
	int random = (rand() % num);
	string word = wordsTab[random];
	string tip = tipTab[random];

	vector <string> wordAndTip = { word,tip };

	return wordAndTip;
}

void toTable(vector<string> wordAndTip) {
	string word = wordAndTip.at(0);
	string tip = wordAndTip.at(1);

	length = word.size();
	counter = length;
	for (int i = 0; i < length; i++) {
		checkedLetters.push_back(word[i]);
		tabCheck.push_back('_');
		cout << tabCheck[i] << " ";
	}
	cout << endl << "Tip: ";
	cout << tip << endl;
}

int chooseDifficulty() {
	int difficulty;
	cout << "==============================" << endl;
	cout << "Select difficulty" << endl;
	cout << "Easy [7 lives] insert 1" << endl;
	cout << "Medium [5 lives] insert 2" << endl;
	cout << "Hard [3 lives] insert 3" << endl;
	cout << "==============================" << endl;
	cin >> difficulty;

	switch (difficulty)
	{
	case 1:
		lives = 7;
		cout << endl << "You have 7 lives" << endl;
		break;
    case 2:
		lives = 5;
		cout << endl << "You have 5 lives" << endl;
		break;
	case 3:
		lives = 3;
		cout << endl << "You have 3 lives" << endl;
		break;
	default:
		chooseDifficulty();
		break;
	}
	return lives;
}

void checkLetter() {
	char letter;
	cout << endl << "Choose letter\n";
	cin >> letter;
	int tmp = 0;

	for (int i = 0; i < length; i++) {
		if (checkedLetters[i] == letter) {
			tabCheck[i] = letter;
			checkedLetters[i] = '*';
			tmp++;
		}
	}
	for (int i = 0; i < length; i++) {
		cout << tabCheck[i] << " ";
	}
	if (tmp == 0) {
		lives--;
		if (lives == 0) {
			cout << "YOU LOOSE!!!!" << endl << "try again? y/n" << endl;
			char choose;
			cin >> choose;
			if (choose == 'y') {
				chooseDifficulty();
			}
			else {
				exit(0);
			}
		}
		else {
			cout << endl << "Live left: " << lives << endl;
			checkLetter();
		}
	}
	else {
		counter -= tmp;
		if (counter == 0) {
			cout << "GOODJOB\n" << endl << "try again? y/n" << endl;
			char choose;
			cin >> choose;
			if (choose == 'y') {
				chooseDifficulty();
			}
			else {
				exit(0);
			}
		}
		else {
			checkLetter();
		}
	}
}

int main()
{
	chooseDifficulty();
	loadFile();
	toTable(rollWord(lineCounter));
	checkLetter();
}