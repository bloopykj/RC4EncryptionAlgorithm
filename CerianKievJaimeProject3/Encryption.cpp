#include <iostream> 
#include <sstream> 
#include <fstream> 
#include <vector> 
#include <iomanip> 

using namespace std;
string key();
void fillArray(char array[256]);
string readFile(string filename);
void writeFile(string filename, const string ciphertext);
void exchange(char a, char b);
void KSA(char array[256], string key);
unsigned char PRGA(char array[256], char i, char j);
string RC4(string plaintext, string key);

int main() {

	string key1 = key(); // gets key 
	string plaintext = readFile("input.txt"); // reads input.txt 
	string ciphertext = RC4(plaintext, key1); // converts plaintext to ciphertext using RC4 

	cout << ciphertext << endl;
	writeFile("output.txt", ciphertext); // converts to hex and prints 

	return 0;
}
// Gets user input 
string key() {
	string input;
	int min, max;
	min = 5;
	max = 32;

	cout << "Enter a key: ";
	cin >> input;

	while ((input.length() < min) || (input.length() > max)) {

		cout << "The size of the key is not valid" << endl;
		cout << "Enter a key: ";
		cin >> input;

	}
	return input;
}
void fillArray(char array[256]) {

	for (int i = 0; i < 256; i++) {
		array[i] = i;
	}

}

// Reads file 
string readFile(string filename) {
	string input; // text will be stored here 
	char ch;
	ifstream inputfile(filename, ios::binary);

	// If the input is not in, it will say it is not found 
	// If the input is in, it will say it is found 

	if (!inputfile) {
		cout << "File is not found" << endl;
		exit(1);
	}
	else {
		cout << "File is opened" << endl;
	}
	// Reads input file character by character 
	while (inputfile.get(ch)) {
		input += ch;
	}
	// close file 
	inputfile.close();
	return input;
}
// Writes to file and converts to hex 
void writeFile(string filename, const string ciphertext) {

	ofstream file(filename, ios::binary);
	// Code to convert data to hexadecimal 

	for (size_t i = 0; i < ciphertext.length(); i++) {

		char c = ciphertext[i];
		file << hex << setw(2) << (int)(unsigned char)c;
	}
}
void exchange(char a, char b) {
	char w = a;
	a = b;
	b = w;
}

// Initialize array 
void KSA(char array[256], string key) {

	char S[256];
	int j = 0;
	char m = 0, n = 0;

	// fill up array 
	fillArray(array);

	// KSA 
	for (int i = 0; i < 256; i++) {
		j = (j + array[i] + key[i % key.size()]) % 256;
		// use swap code here 
		exchange(array[i], array[j]);
	}
	// discard first 3072 bytes 
	for (int a = 0; a < 3072; a++) {
		m++;
		n += array[m];
		exchange(array[m], array[n]);
	}
}

// Generates pseudo random numbers 
unsigned char PRGA(char array[256], char i, char j) {
	i++;

	// increments j with value of array[i]

	j += array[i];

	// exchange values of array[i] and array[j] to pseudo random 
	swap(array[i], array[j]);
	return array[(array[i] + array[j]) % 256];
}

// Main RC4 function 
string RC4(string plaintext, string key) {
	string cipher;
	char bits[256];
	char i = 0, j = 0;

	// initialize array 
	KSA(bits, key);

	// iterate through plaintext to generate keystream 
	// XOR with the input 
	for (size_t g = 0; g < plaintext.length(); g++) {

		// variable that holds current char 
		char w = plaintext[g];
		cipher += w ^ PRGA(bits, i, j);

	}
	return cipher;
}