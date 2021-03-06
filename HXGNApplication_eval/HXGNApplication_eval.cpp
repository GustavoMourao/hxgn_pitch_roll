// HXGNApplication_eval.cpp : define o ponto de entrada para o aplicativo do console.
//

/*

%%%%% -----      Author: Gustavo L. Mourão
%%%%% -----		 part of code extracted from: http://www.cplusplus.com/

*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "stdlib.h"     /* atof */
#include <math.h>
#include <vector>		/*vector*/
#include <sstream>      /*stringstream*/

using namespace std;

// Global vectors
std::vector<double> theta;						// Vector (dinamic allocation)
std::vector<double> phi;						// Vector (dinamic allocation)
std::vector<double> timems;						// Vector (dinamic allocation)


												// This function storage values of roll and pitch values in .txt file
void storageRollPitch(std::vector<double> timems, std::vector<double> phi, std::vector<double> theta) {

	ofstream outFile;
	outFile.open("output_attitude.txt");
	for (int i = 0; i < phi.size(); i++) {
		outFile << timems[i] << "; " << phi[i] << "; " << theta[i] << "\n";
	}
	outFile.close();

}


// This function get x, y and z values, then compute roll and pitch angle
void rollAndpitch(double time, double x, double y, double z) {

	const double PI = 3.141592653589793238463;		// constant

													// Only get values different than zero
	if ((x != 0) && (y != 0) && (z != 0)) {

		//Storage values on global dinamic vector
		phi.push_back((180 * atan(y / z)) / PI);
		theta.push_back(180 * (-x / (sqrt(y * y + z * z))) / PI);
		timems.push_back(time);

		cout << "Time (ms):        " << time;
		cout << "\n";
		cout << "Roll (degree):    " << (180 * atan(y / z)) / PI;
		cout << "\n";
		cout << "Theta (degree):   " << 180 * (-x / (sqrt(y * y + z * z))) / PI;
		cout << "\n";
	}
}


// This function finds the number of words and characters in a given line
void wordsInFile(string line, int& wordCount, int& charCount)
{
	int n;									 // number of words of each dimension

	int charCountOne;						// counter of time samples
	int charCountTwo;						// counter of x_axis samples
	int charCountThree;						// counter of y_axis samples
	int charCountFour;						// counter of z_axis samples

	string delimiters = " .,?:;!()";         // Sets the delimiters of a word
	char currentChar;                        // Keeps track of the current character
	bool inWord = false;                     // Keeps track of whether you're in a word or not
	char time[5];							 // time ms
	char x_axis[3];							 // x axis
	char y_axis[3];							 // y axis
	char z_axis[5];							 // z axis


											 // Tack a delimiter on a; then end of the line to make word ID easier

	line = line + '.';

	// Initialize the wordCount to zero

	wordCount = 0;

	// For loop to count the characters in the line

	for (charCount = 0; charCount < line.length(); charCount++)
	{
		n = 0;

		// Set the current character
		currentChar = line.at(charCount);

		// If current character is not a delimiter

		if (delimiters.find(currentChar) == string::npos)
		{

			//cout << line;
			//cout << "\n";

			// If we're inside a word
			if (inWord)
			{

				charCount++;

			}

			// If it's the beginning of the word then set inWord to true and increment
			// the character and word counts

			else
			{
				inWord = true;
				//charCount++;
				wordCount++;

				if (wordCount == 1) {

					for (charCountOne = charCount; charCountOne < charCount + 5; charCountOne++) {
						time[n] = line[charCountOne];
						n = n + 1;
					}
				}
				if (wordCount == 2) {

					for (charCountTwo = charCount; charCountTwo < charCount + 3; charCountTwo++) {
						x_axis[n] = line[charCountTwo];
						n = n + 1;
					}
				}
				if (wordCount == 3) {

					for (charCountThree = charCount; charCountThree < charCount + 3; charCountThree++) {
						y_axis[n] = line[charCountThree];
						n = n + 1;
					}
				}
				if (wordCount == 4) {

					for (charCountFour = charCount; charCountFour < charCount + 5; charCountFour++) {
						z_axis[n] = line[charCountFour];
						n = n + 1;
					}
				}

				// Call function responsible to calculates roll and pitch angles
				rollAndpitch(atof(time), atof(x_axis), atof(y_axis), atof(z_axis));

			}
		}

		// else the current character is a delimiter

		else
		{
			if (inWord)
			{
				// Set inWord to false and increment the character counter

				inWord = false;
				//charCount++;
			}

			else {
				//charCount++;

			}
		}
	}

	return;

}



int main()
{
	ifstream inFile;        // .txt file readed
	int countline;          // counter lines variable
	string currentLine;     // file string read 
	int totalWordCount;     // total word counter of entire file
	int totalCharCount;     // total character counter of entire file
	int wordCount;          // word counter of each line
	int charCount;          // character counter of each line

	totalWordCount = 0;
	totalCharCount = 0;

	printf("Get set of data ... ");
	cout << "\n";
	printf(" /... ");
	cout << "\n";

	inFile.open("attitude_exam.txt");

	// Check to make sure the file opened correctly

	if (!inFile)
	{
		cout << "File did not open correctly" << endl;
		return 1;
	}

	// Set the count equal to zero

	countline = 0;

	// Get the first line of the file

	getline(inFile, currentLine);

	// Check the number of lines in the file

	while (inFile)
	{

		// Call the function to find words and characters in the file

		wordsInFile(currentLine, wordCount, charCount);

		// Add the wordCount from the function to the total word count

		totalWordCount += wordCount;

		// Add the charCount from the function to the total character count

		totalCharCount += charCount;

		// Increment the line counter

		countline++;

		// Get the next line

		getline(inFile, currentLine);

	}

	// Call function responsible to storage values on .txt file
	storageRollPitch(timems, phi, theta);

	return 0;

}



