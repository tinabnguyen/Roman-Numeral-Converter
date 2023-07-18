#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

// This function checks if the roman numeral is valid. 
bool romanVal(string rNum) {
    // This string contains all of the valid roman numeral characters.
    string valid = "IVXLCDM";
    
    for (long unsigned int i = 0; i < rNum.length(); i++) {
        
        // If the character in the roman numeral is not one of the valid ones, then the roman numeral is invalid.
        if (valid.find(rNum[i]) == string::npos) {
            return false;
        }
    }
    return true;
}

// This function checks if the arabic number is valid.
bool arabicVal(string aNum) {
    
    // This loop iterates through the arabic length and checks to see if the character is a digit or not.
    for (long unsigned int i = 0; i < aNum.length(); i++) {
        if (!isdigit(aNum[i]) && aNum[i] != ' ') {
            return false;
        }
    }
    // This if statement checks if the arabic number is between 1 and 4999.
    int arabic = stoi(aNum);
    if (arabic< 1 || arabic > 4999) {
        return false;
    }
    return true;
}

// This function returns the arabic equivalent of each roman character.
int romanValues(char letter) {
    if (letter == 'I') {
        return 1;
    }
    if (letter == 'V') {
        return 5;
    }
    if (letter == 'X') {
        return 10;
    }
    if (letter == 'L') {
        return 50;
    }
    if (letter == 'C') {
        return 100;
    }
    if (letter == 'D') {
        return 500;
    }
    if (letter == 'M') {
        return 1000;
    }
    else {
        return 0;
    }
    
}

// This function converts the roman numeral to arabic numeral. 
int romanToArabic(string romanNumeral) {
    
    int sum = 0;

    for (long unsigned int i = 0; i < romanNumeral.length(); i++) {

        int num1 = romanValues(romanNumeral[i]);            // value of the first roman letter

        if (i + 1 < romanNumeral.length()) {                
            int num2 = romanValues(romanNumeral[i+1]);      // Get the next roman letter value
            
            if (num1 >= num2) {                         
                sum += num1;                                // This is the normal adding of values
            }
            else {

                sum += (num2 - num1);                       // This does substraction for values like 4s and 9s
                i++;
            }
        }
        else {
            sum += num1;
        }
    }
    return sum;
}

// This function converts the arabic numeral to roman numeral.
string arabicToRoman(int arabicNumeral) {
    
    // These 2 arrays correlate with each other in value.
    string roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int arabic[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string final;
    
    for (int i =0; i < 13; i++) {
        while (arabicNumeral - arabic[i] >= 0) {            // determines the first value of the digit
            final += roman[i];                              // Adds the roman letters to the final string
            arabicNumeral -= arabic[i];                     // Determines the remaining value
        }
    }
    return final;
}

const string database = "numbers.txt";  
//your filestream for the database will connect to this variable

int main()
{
/* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
   string temp;  //variable for database filename
   string batch; //variable for batch filename

   cout << "Enter File Name: ";
   cin >> temp;

   ifstream infile(temp, ios::binary);
   ofstream outfile(database, ios::binary);
   string line;
   if (infile)
        while (infile.good())
        {
            getline(infile, line);
            if (line != "")
                outfile << line << "\n";
        }

   infile.close();
   outfile.close();
/* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */

    fstream file;
    file.open(database, ios::in | ios::out | ios::binary);
    
    if (!file.good()) {                             // check if the file was opened properly, if not, exit the program
        cout << "Error opening the file." << endl;
        return 1;
    }
    
    string roman, arabic;
    long int pos = 0;                // used to determine the current position
    string row;                      // Each row is put into a string
    long unsigned int first = 0;     // index of the first space in each line
    bool firstLine = true;           // Used for determining if the line is the first line in the file.
    int ara = 0;                     // used for the int equivalent of the arabic string

    while (file.good()) {
        while (getline(file, row)) {                  // get each line of the file and put it into the row string
            
            first = row.find(' ');                    // find the first space in the row
            
            if (first == 0) {                         // If the space is at position 0 in the row, then that means we are given an arabic number
                arabic = row.substr(17, 4);           // Get the arabic substring from the row
                
                // if the arabic numeral is valid
                if (arabicVal(arabic)) {              
                
                    //This if-else statement shows up multiple times later, but this helps determine the position of the first character of each row.
                    
                    if (firstLine) {
                        pos = 0;
                        firstLine = false;
                    }
                    else {
                        pos = (pos / 22 + 1) * 22;
                    }
                    
                    ara = stoi(arabic);                                      // convert the arabic string to integer to use in conversion function
                    
                    roman = arabicToRoman(ara);                              // convert from arabic to roman numeral
                    
                    file.seekg(pos, ios::beg);                               // move the pointer back to the beginning of the row
                    file << left << setw(17) << setfill(' ') << roman;       // display the roman numeral to the row
                    file.seekg(pos + 22, ios::beg);                          // Move pointer to the next row.
                }
                
                // if the arabic numeral is invalid
                else {
                    
                    //determine first position of each row
                    if (firstLine) {
                        pos = 0;
                        firstLine = false;
                    }
                    else {
                        pos = (pos / 22 + 1) * 22;
                    }
                    
                    file.seekg(-22, ios::cur);                      // move pointer to the beginning of the row
                    file << setw(21) << setfill(' ') << " ";        // display the whole row with spaces
                    file.seekg(pos + 22, ios::beg);                 // move pointer to the next row
                }
            }
            if (first != 0) {                           // if the first space is not at 0, that means we are given a roman numeral.
                roman = row.substr(0, first);           // get the roman substring from the row
                
                // if the roman numeral is valid
                if (romanVal(roman)) {                  // roman numeral validation true
                    if (firstLine) {                    // determine first position of each row
                        pos = 0;
                        firstLine = false;
                    }
                    else {
                        pos = (pos / 22 + 1) * 22;
                    }
                    
                    ara = romanToArabic(roman);                                                         // convert from roman numeral to arabic
                    file.seekg(static_cast<unsigned int> (file.tellg()) - row.length() - 1 + 17);
                    file << left << setw(4) << setfill(' ') << ara << endl;                             // display the arabic numeral to the row
                }
                // if the roman numeral is invalid
                else {
                    if (firstLine) {                    // determine first position of each row
                        pos = 0;
                        firstLine = false;
                    }
                    else {
                        pos = (pos / 22 + 1) * 22;
                    }
                    
                    file.seekg(-22, ios::cur);                   // move pointer to the beginning of the row
                    file << setw(21) << setfill(' ') << " ";     // display the whole row with spaces
                    file.seekg(1, ios::cur);                     // move the pointer to the next row
                }
            }
        }
        
    }

    file.close();      // close file once finished
    return 0;
}
