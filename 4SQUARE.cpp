/*  
* Author: Vu Thien Trang 
* Date created: 22. 11. 2017
* Subject: B6B32KAB
* Faculty: SIT FEL CTU
*/

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#define DELIMITER "**QQQ**"
#define DELIMITER_SIZE 7

using namespace std;

vector<vector<string> > defaultTable = {
  {"A", "B", "C", "D", "E"},
  {"F", "G", "H", "I", "J"}, 
  {"K", "L", "M", "N", "O"}, 
  {"P", "R", "S", "T", "U"}, 
  {"V", "W", "X", "Y", "Z"}
};

// Prints out given table
void printTable (const vector<vector<string>>& t){
  for (const auto &row : t) {
    for (const auto &c : row) clog << c << ' ';
    clog << std::endl;
  }
  return;
}

// Parses line into individual words
vector<string> parseLine(const string& str) {
    vector<string> divided;
    stringstream ss(str);
    string word;
    while (ss >> word) divided.push_back(word);
    return divided;
}

// Splits a string by delimiter and retrieves both keywords
pair<string, string> getKeywords(const string& s) {
  size_t pos;
  string first, second;
  pair<string, string> keywords;
  if ((pos = s.find(DELIMITER)) != string::npos) {
    first = (pos == 0) ? "" : s.substr(0, pos);
    second = ((pos + DELIMITER_SIZE) == s.length()) ? "" : s.substr((pos + DELIMITER_SIZE), string::npos);
  }
  return {first, second};
}

// Formats input for algorithm
string formatInput(const vector<string>& vec) {
  string s; 
  // Concatenate strings from vector
  for (size_t i = 2; i != vec.size(); ++i) s += vec[i];
  // Remove non-alpha 
  s.erase(remove_if(s.begin(), s.end(), [](char c) {return !isalpha(c);}), s.end());
  // Lowercase to uppercase 
  transform(s.begin(), s.end(), s.begin(), ::toupper);
  // Remove Q letter
  s.erase(remove(s.begin(), s.end(), 'Q'), s.end());
  return s;
}

// Main function
int main(int argc, char **argv) {
  string line, formatted;
  // Read line after line
  while (!cin.eof()) {
    getline(cin, line);
    vector<string> divided = parseLine(line);
    // Skip wrong input line
    if (divided.size() < 3 || ((divided.at(0) != "e") && (divided.at(0) != "d"))) continue;
    clog << "------------------------------" << endl;
    // Retrieve keys
    pair<string, string> keys = getKeywords(divided.at(1));
    clog << keys.first << " is the first key" << endl;
    clog << keys.second << " is the second key" << endl;
    // Create squares (TO-DO)
    printTable(defaultTable);
    // Format input
    formatted = formatInput(divided);
    clog << "Formatted input is: " << formatted << endl;
    // Encrypt or decrypt (TO-DO)
    // Print result to output stream (TO-DO)
  }
  return 0;
} 














