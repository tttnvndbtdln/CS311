#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define SIZE 65
#define MAX 15

const char load_file[] = "test.txt"; 
int load_cards(void);
int is_double(char *word);
void display_table(void);
int check_state(char symbol, int length);

int main() {
	display_table();	
	load_cards();
	
	return 1;
}

int load_cards(void) {
	ifstream fin;
	
	int y = 0;
	
	fin.open(load_file, ios::app);
	
	if(!fin) {
		return 0; //error fail to load
	}
	else {
		
		char* str = new char[SIZE];

		fin.get(str, SIZE, '\r');

		cout << "here1 " << endl << endl;
	
		fin.ignore(100, '\n');
		
		while(fin && !fin.eof()) {	
			y = is_double(str);
//			cout << "state: " << y << endl;
			if(y == 1 || y == 5 || y == 6 || y == 7 || y == 8) {
				cout << "Accept State.\n";
			}
			else { cout << "Non-Accept State.\n";}
			fin.get(str, SIZE, '\r');
			fin.ignore(100, '\n');
		}
	}
	
	fin.close();
}

int is_double(char *word) {
	cout << "string to check: " << word << endl;
	
	int table[10][5];	
	int state = 0;
	int element;
	int value = 0;
	
	//set the dead state for the a-z column 
	for(int i = 0; i <= 9; ++i) {
		table[i][0] = 9;
	}
	
	//set the states for the 0-9 column
	for(int j = 0; j <= 9; ++j) {
		if(j == 0 || j == 1 || j == 2) {
			table[j][1] = 1;
		}
		else if(j == 3 || j == 5) {
			table[j][1] = 5;
		}
		else if(j == 4 || j == 6) {
			table[j][1] = 6;
		}
		else if(j == 7) {
			table[j][1] = 7;
		}
		else if(j == 8) {
			table[j][1] = 8;
		}
		else if(j == 9) {
			table[j][1] = 9;
		}
		else {
			cout << "error.\n";
		}
	}
	
	//set the -,+ column
	for(int j = 0; j <= 9; ++j) {
		if(j == 0) {
			table[j][2] = 2;
		}
		else if(j > 0 && j != 4) {
			table[j][2] = 9;
		}
		else if(j == 4) {
			table[j][2] = 6;
		}
		else {
			cout << "error.\n";
		}
	}
		
	//set the '.' column		
	
	for(int k = 0; k <= 9; ++k) {
		if(k == 0 || k == 2) {
			table[k][3] = 3;
		}
		else if(k == 6) {
			table[k][3] = 7;
		}
		else if(k == 1) {
			table[k][3] = 8;
		}
		else {
			table[k][3] = 9;
		}
	}
	
	//set the e, E column	
	for(int j = 0; j <= 9; ++j) {
		if(j == 1 || j == 2 || j == 5 || j == 8) {
			table[j][4] = 4;
		}
		else {
			table[j][4] = 9;
		}
	}
	
	element = strlen(word);
	cout << "length of word: " << element << endl;	
	
	for(int i = 0; i < element; ++i) {
		value = check_state(word[i], value);
	}
	
	return value;	//return state
}		

int check_state(char symbol, int state) {
	//iterate through string, and save the state	
	if(state == 0) {
		if(symbol == 'e' || symbol == 'E') {	//if symbol is e or E, goto dead state (9)
			return 9;	
		}
		else if(isalpha(symbol)) {	//if symbol is a-z, return 0
			return 0;//dead state
		}
		else if(isdigit(symbol)) {	//if symbol is a digit, goto q1
			return 1;
		}
		else if(symbol == '+' || symbol == '-') {	//if symbol is a + or -, goto q2
			return 2;
		}
		else if(symbol == '.') {	//if symbol is a '.', goto q3
			return 3;
		}
	}
	else if(state == 1) {
		if(symbol == 'e' || symbol == 'E') {	//if symbol is e or E, goto q1 
			return 4;	
		}
		else if(isalpha(symbol)) {	//if symbol is a-z, return 0
			return 0;//dead state
		}
		else if(isdigit(symbol)) {	//if symbol is a digit, goto q1
			return 1;
		}
		else if(symbol == '+' || symbol == '-') {	//if symbol is a + or -, goto dead state 
			return 9;
		}
		else if(symbol == '.') {	//if symbol is a '.', goto q8
			return 8;
		}
	}
	else if(state == 2) {
		if(symbol == 'e' || symbol == 'E') {	//if symbol is e or E, goto q1 
			return 4;	
		}
		else if(isalpha(symbol)) {	//if symbol is a-z, return 0
			return 0;//dead state
		}
		else if(isdigit(symbol)) {	//if symbol is a digit, goto q1
			return 1;
		}
		else if(symbol == '+' || symbol == '-') {	//if symbol is a + or -, goto dead state
			return 9;
		}
		else if(symbol == '.') {	//if symbol is a '.', goto q3
			return 3;
		}
	}			
	else if(state == 3) {
		if(symbol == 'e' || symbol == 'E') {	//if symbol is e or E, goto dead state 
			return 9;	
		}
		else if(isalpha(symbol)) {	//if symbol is a-z, return 0
			return 0;//dead state
		}
		else if(isdigit(symbol)) {	//if symbol is a digit, goto q5
			return 5;
		}
		else if(symbol == '+' || symbol == '-') {	//if symbol is a + or -, goto dead state
			return 9;
		}
		else if(symbol == '.') {	//if symbol is a '.', goto dead state 
			return 9;
		}
	}
	else if(state == 4) {
		if(symbol == 'e' || symbol == 'E') {	//if symbol is e or E, goto dead state 
			return 9;	
		}
		else if(isalpha(symbol)) {	//if symbol is a-z, return 0
			return 0;//dead state
		}
		else if(isdigit(symbol)) {	//if symbol is a digit, goto q6
			return 6;
		}
		else if(symbol == '+' || symbol == '-') {	//if symbol is a + or -, goto q6 
			return 6;
		}
		else if(symbol == '.') {	//if symbol is a '.', goto dead state 
			return 9;
		}
	}
	else if(state == 5) {
		if(symbol == 'e' || symbol == 'E') {	//if symbol is e or E, goto q4 
			return 4;	
		}
		else if(isalpha(symbol)) {	//if symbol is a-z, return 0
			return 0;//dead state
		}
		else if(isdigit(symbol)) {	//if symbol is a digit, goto q5
			return 5;
		}
		else if(symbol == '+' || symbol == '-') {	//if symbol is a + or -, goto dead state 
			return 9;
		}
		else if(symbol == '.') {	//if symbol is a '.', goto dead state 
			return 9;
		}
	}
	else if(state == 6) {
		if(symbol == 'e' || symbol == 'E') {	//if symbol is e or E, goto dead state 
			return 9;	
		}
		else if(isalpha(symbol)) {	//if symbol is a-z, return 0
			return 0;//dead state
		}
		else if(isdigit(symbol)) {	//if symbol is a digit, goto q6
			return 6;
		}
		else if(symbol == '+' || symbol == '-') {	//if symbol is a + or -, goto dead state 
			return 9;
		}
		else if(symbol == '.') {	//if symbol is a '.', goto q9
			return 9; 
		}
	}
	else if(state == 7) {
		if(symbol == 'e' || symbol == 'E') {	//if symbol is e or E, goto dead state 
			return 9;	
		}
		else if(isalpha(symbol)) {	//if symbol is a-z, return 0
			return 0;//dead state
		}
		else if(isdigit(symbol)) {	//if symbol is a digit, goto q7 
			return 7;
		}
		else if(symbol == '+' || symbol == '-') {	//if symbol is a + or -, goto dead state 
			return 9;
		}
		else if(symbol == '.') {	//if symbol is a '.', goto dead state 
			return 9; 
		}
	}
	else if(state == 8) {
		if(symbol == 'e' || symbol == 'E') {	//if symbol is e or E, goto q4 
			return 4;	
		}
		else if(isalpha(symbol)) {	//if symbol is a-z, return 0
			return 0;//dead state
		}
		else if(isdigit(symbol)) {	//if symbol is a digit, goto q8 
			return 8;
		}
		else if(symbol == '+' || symbol == '-') {	//if symbol is a + or -, goto dead state 
			return 9;
		}
		else if(symbol == '.') {	//if symbol is a '.', goto dead state 
			return 9; 
		}
	}
	else if(state == 9) {
		return 9;	
	}
	cout << "error \n";
	return 9;
	
}

void display_table(void) {
		
	int table[10][5];	

	//set the dead state for the a-z column 
	for(int i = 0; i <= 9; ++i) {
		table[i][0] = 9;
	}
	
	//set the states for the 0-9 column
	for(int j = 0; j <= 9; ++j) {
		if(j == 0 || j == 1 || j == 2) {
			table[j][1] = 1;
		}
		else if(j == 3 || j == 5) {
			table[j][1] = 5;
		}
		else if(j == 4 || j == 6) {
			table[j][1] = 6;
		}
		else if(j == 7) {
			table[j][1] = 7;
		}
		else if(j == 8) {
			table[j][1] = 8;
		}
		else if(j == 9) {
			table[j][1] = 9;
		}
		else {
			cout << "error.\n";
		}
	}
	
	//set the -,+ column
	for(int j = 0; j <= 9; ++j) {
		if(j == 0) {
			table[j][2] = 2;
		}
		else if(j > 0 && j != 4) {
			table[j][2] = 9;
		}
		else if(j == 4) {
			table[j][2] = 6;
		}
		else {
			cout << "error.\n";
		}
	}
		
	//set the '.' column		
	
	for(int k = 0; k <= 9; ++k) {
		if(k == 0 || k == 2) {
			table[k][3] = 3;
		}
		else if(k == 6) {
			table[k][3] = 7;
		}
		else if(k == 1) {
			table[k][3] = 8;
		}
		else {
			table[k][3] = 9;
		}
	}
	
	//set the e, E column	
	for(int j = 0; j <= 9; ++j) {
		if(j == 1 || j == 2 || j == 5 || j == 8) {
			table[j][4] = 4;
		}
		else {
			table[j][4] = 9;
		}
	}
	
	
	//print the table	
	for(int k = 0; k <= 9; ++k) {
		for(int l = 0; l <= 4; ++l) {
			cout << table[k][l] << "\t";
		}
		cout << endl;
	}
}
		





