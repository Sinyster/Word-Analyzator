#include <cctype>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <string>
using namespace std;

void cls() {
#ifdef _WIN32
  system("cls");
#elif __linux__
  system("clear");
#endif
}

void ps() {
#ifdef _WIN32
  system("pause");
#elif __linux__
  printf("Press Enter to continue...");
  getchar();
#endif
}

// Formats File Path so it will work in the code.
void formatPATH(string &fileName);

// Deletes any signs that we dont want.
void deleteSigns(string &word);

// Transform CAPS letters into small letters.
void toLower(string &word) {
  for (int i = 0; i < word.length(); i++) {
    word[i] = tolower(word[i]);
  }
}

struct Dvojice {
  string key;
  int keyValue;
};

// Bools for sorting a list. For exporting.
bool descending(Dvojice a, Dvojice b) { return a.keyValue < b.keyValue; }
bool ascending(Dvojice a, Dvojice b) { return a.keyValue > b.keyValue; }

class Analyzator {
private:
  map<string, int> wordCount;
  list<Dvojice> dvojice;

public:
  Analyzator(string fileName) {
    // Loading functional file.
    ifstream file(fileName);
    if (!file) {
      cls();
      printf("File does not exist!\n");
      ps();
      exit(1);
    } else {
      string word;
      string signs = "0123456789,?.:!*-+/\\\"\'@&#({[<>]})";
      while (file >> word) {
        while (word.find_first_of(signs) != string::npos) {
          word.erase(word.find_first_of(signs), 1);
        }

        if (!word.empty()) {
          wordCount[word]++;
        }
      }
      file.close();

      for (pair<string, int> w : wordCount) {
        Dvojice d;
        d.key = w.first;
        d.keyValue = w.second;
        dvojice.push_back(d);
      }
    }
  }

  void printALL() {
    cls();
    if (wordCount.empty()) {
      printf("Data are empty.\n");
      ps();
      return;
    }

    for (pair<string, int> w : wordCount) {
      printf("%s - %dx\n", w.first.c_str(), w.second);
    }
    ps();
    return;
  }

  void exportAZ() {
    cls();
    if (wordCount.empty()) {
      printf("Data are empty.\n");
      ps();
      return;
    }

    string filePath = "exportAZ.txt";
    ofstream file(filePath);
    for (pair<string, int> w : wordCount) {
      file << w.first << " - " << w.second << "x" << endl;
    }
    file.close();
    printf("Data exported into '%s'.\n", filePath.c_str());
    ps();
    return;
  }

  void exportZA() {
    cls();
    if (wordCount.empty()) {
      printf("Data are empty.\n");
      ps();
      return;
    }

    string filePath = "exportZA.txt";
    ofstream file(filePath);
    for (map<string, int>::reverse_iterator reit = wordCount.rbegin();
         reit != wordCount.rend(); reit++) {
      file << reit->first << " - " << reit->second << "x" << endl;
    }
    file.close();
    printf("Data exported into '%s'.\n", filePath.c_str());
    ps();
    return;
  }

  void export1N() {
    cls();
    if (wordCount.empty()) {
      printf("Data are empty.\n");
      ps();
      return;
    }

    string filePath = "export1N.txt";
    ofstream file(filePath);
    dvojice.sort(descending);
    for (auto d : dvojice) {
      file << d.keyValue << "x - " << d.key << endl;
    }
    file.close();
    printf("Data exported into '%s'.\n", filePath.c_str());
    ps();
    return;
  }

  void exportN1() {
    cls();
    if (wordCount.empty()) {
      printf("Data are empty.\n");
      ps();
      return;
    }

    string filePath = "exportN1.txt";
    ofstream file(filePath);
    dvojice.sort(ascending);
    for (auto d : dvojice) {
      file << d.keyValue << "x - " << d.key << endl;
    }
    file.close();
    printf("Data exported into '%s'.\n", filePath.c_str());
    ps();
    return;
  }
};

int main(void) {
  string filePath = "";
  bool containsTXT = false;

  // Asks for path until it works.
  while (!containsTXT) {
    cls();
    printf("Enter PATH to your .txt file: ");
    cin >> filePath;
    cin.ignore(1000, '\n');

    containsTXT = filePath.find(".txt") != string::npos;
    if (containsTXT) {
      break;
    }
  }

  // Delete signs.
  deleteSigns(filePath);

  // Format Path for your OS.
  formatPATH(filePath);

  Analyzator a(filePath);
  int choice = 0;
  do {
    cls();
    printf("1. Write Data\n");
    printf("2. Export AZ\n");
    printf("3. Export ZA\n");
    printf("4. Export 1N\n");
    printf("5. Export N1\n");
    printf("0. Exit\n");
    printf("Choice: ");
    cin >> choice;
    cin.ignore(1000, '\n');
    if (cin.fail()) {
      cin.clear();
      continue;
    }

    switch (choice) {
    case 1:
      a.printALL();
      break;
    case 2:
      a.exportAZ();
      break;
    case 3:
      a.exportZA();
      break;
    case 4:
      a.export1N();
      break;
    case 5:
      a.exportN1();
      break;
    }
  } while (choice != 0);

  return 0;
}

void formatPATH(string &fileName) {
  // Needs to check if PATH contains '\'
  size_t pos = 0;
  while ((pos = fileName.find("\\", pos)) != string::npos) {
    fileName.replace(pos, 1, "\\\\");
    pos += 2;
  }
  return;
}

void deleteSigns(string &word) {
  string signs = "\"\'&@#";
  while (word.find_first_of(signs) != word.npos) {
    word.erase(word.find_first_of(signs), 1);
  }
  return;
}
