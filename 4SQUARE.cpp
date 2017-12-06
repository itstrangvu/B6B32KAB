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

vector<vector<char> > defaultTable = {
  {'A', 'B', 'C', 'D', 'E'},
  {'F', 'G', 'H', 'I', 'J'}, 
  {'K', 'L', 'M', 'N', 'O'}, 
  {'P', 'R', 'S', 'T', 'U'}, 
  {'V', 'W', 'X', 'Y', 'Z'}
};


// Generates table for the key 
vector<vector<char> > generateTable(const string& key) {
  string a = "ABCDEFGHIJKLMNOPRSTUVWXYZ";
  string k = move(key);
  char letter;
  int row, col;

  vector<vector<char> > t(5, vector<char>(5, ' '));

  for (row = 0; row < 5; ++row) {
    for (col = 0; col < 5; ++col) {
      if (k.length()) {
        letter = k[0];
        t[row][col] = k[0];
        a.erase(remove(a.begin(), a.end(), letter), a.end());
        k.erase(remove(k.begin(), k.end(), letter), k.end());
      }
      else {
        t[row][col] = a.at(0);
        a.erase(0,1);
      }
    }
  }
  return t;
}

// Prints out given table
void printTable (const vector<vector<char>>& t){
  for (const auto &row : t) {
    for (const auto &c : row) clog << c << ' ';
    clog << endl;
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
  transform(first.begin(), first.end(), first.begin(), ::toupper);
  transform(second.begin(), second.end(), second.begin(), ::toupper);
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
  // Add letter X if the length is odd
  if (s.length() % 2 != 0) s += 'X';
  
  return s;
}

pair<int, int> getPosition(const vector<vector<char> >& t, const char& ch) {
  int row, col;
  for (row = 0; row < 5; ++row) {
    for (col = 0; col < 5; ++col) {
      if (t[row][col] == ch) return {row, col};
    }
  }
  return {0,0};
}

// Squeeze
string squish(const vector<vector<char> >& r, const vector<vector<char> >& l, const string& digram) {
  string output;
  char digram1 = digram[0];
  char digram2 = digram[1];

  pair<int, int> a = getPosition(defaultTable, digram1);
  pair<int, int> b = getPosition(defaultTable, digram2);

  char one = r[a.first][b.second];
  char two = l[b.first][a.second];

  output = one;
  output += two;

  // FIRST LETTER = r [row of first in default][column of second in default]
  // Second letter = l [ row of second in default] [column of first in default]
  return output;
}

// Encrypting function
string encrypt(const pair<string, string>& keys, const string& input ) {
  int i;
  stringstream ss;
  string output, digram;
  vector<vector<char> > r = generateTable(keys.first);
  vector<vector<char> > l = generateTable(keys.second);
  for (i = 0; i < input.length(); i += 2 ) {
    digram = input.substr(i, 2);
    output += squish(r, l, digram);
  }

  for (int i = 1; i < output.length(); i++) {
     if (i%5 == 0) ss << ' ';
     ss << output[i];
   }

  return ss.str();
}

// Squeeze
string desquish(const vector<vector<char> >& r, const vector<vector<char> >& l, const string& digram) {
  string output;
  char digram1 = digram[0];
  char digram2 = digram[1];

  pair<int, int> a = getPosition(r, digram1);
  pair<int, int> b = getPosition(l, digram2);

  // FIRST LETTER = r [row of first in default][column of second in default]
  char one = defaultTable[a.first][b.second];
  // Second letter = l [ row of second in default] [column of first in default]

  char two = defaultTable[b.first][a.second];

  output = one;
  output += two;

  return output;
}

// Decrypting function
string decrypt(const pair<string, string>& keys, const string& input ) {
  int i;
  string output, digram;
  vector<vector<char> > r = generateTable(keys.first);
  vector<vector<char> > l = generateTable(keys.second);
  for (i = 0; i < input.length(); i += 2 ) {
    digram = input.substr(i, 2);
    output += desquish(r, l, digram);
  }
  return output;
}

// Main function
int main(int argc, char **argv) {
  string line, formatted, output;
  // Read line after line
  while (!cin.eof()) {
    getline(cin, line);
    vector<string> divided = parseLine(line);

    if (divided.at(0) == "end") break;
    // Skip wrong input line
    if (divided.size() < 3 || ((divided.at(0) != "e") && (divided.at(0) != "d"))) continue;
    // clog << "------------------------------" << endl;
    // Retrieve keys
    pair<string, string> keys = getKeywords(divided.at(1));
    // clog << keys.first << " is the first key" << endl;
    // clog << keys.second << " is the second key" << endl;
    // // Create squares
    // vector<vector<char> > rightUpper = generateTable(keys.first);
    // vector<vector<char> > leftBottom = generateTable(keys.second);
    // // Format input
    formatted = formatInput(divided);
    // clog << "Formatted input is: " << formatted << endl;
    // clog << "Default table is: " << endl;
    // printTable(defaultTable);
    // clog << "Right upper table is: " << endl;
    // printTable(rightUpper);
    // clog << "Left bottom table is: " << endl;
    // printTable(leftBottom);
    // clog << "------------------------------" << endl;
    //Encrypt or decrypt 
    if (divided.at(0) == "e") {
      output = encrypt(keys, formatted);
      cout << output << endl;
    } else {
      output = decrypt(keys, formatted);
      cout << output << endl;
    }
  }
  return 0;
} 














