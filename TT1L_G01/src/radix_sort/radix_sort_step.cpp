// *********************************************************
// Program: radix_sort_step.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC1L
// Tutorial Class: TT1L
// Trimester: 2610
// Member_1: 252UC254PP | ANGELA WONG XIN YI | angelawong877@gmail.com | 01111165515
// Member_2: 252UC254RQ | DAMIA IRDINA BINTI AZZUDDIN RIZAL | dmiaird.23@gmail.com | 0193278464
// Member_3: 252UC254Q5 | NUR AFIA BINTI FAHRUDEAN | afia.fahrudean@gmail.com | 0186645540
// Member_4: 252UC254Q4 | THULASIE A/P GANESAN | thulasie.ganesan3472@gmail.com | 0138985240
// *********************************************************
// Task Distribution
// Member_1: Radix Sort
// Member_2: Hash Table Search
// Member_3: Dataset Generation
// Member_4: Heap Sort
// *********************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>

using namespace std;

struct Element {
    long long key;
    string value;
};

void countingSort(vector<Element>& arr, int digitPos) {
    int n = arr.size();
    if (n == 0) return;
    vector<Element> output(n);
    int count[10] = {0};
    for (int i = 0; i < n; i++) {
        int digit = (arr[i].key / digitPos) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++) count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--) {
        int digit = (arr[i].key / digitPos) % 10;
        output[count[digit]-1] = arr[i];
        count[digit]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

void printArray(const vector<Element>& arr, ostream& out) {
    out << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        out << arr[i].key << "/" << arr[i].value;
        if (i != arr.size()-1) out << ", ";
    }
    out << "]";
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last-first+1);
}

int main(int argc, char* argv[]) {
    string configFilename = "config.txt";   // default config file
    if (argc >= 2) configFilename = argv[1]; // allow overriding via command line

    ifstream configFile(configFilename);
    if (!configFile) {
        cerr << "Error: Cannot open config file '" << configFilename << "'" << endl;
        return 1;
    }

    string line;
    string filename;
    int startRow = 0, endRow = 0;
    bool found = false;

    while (getline(configFile, line)) {
        string trimmed = trim(line);
        if (trimmed.empty()) continue;
        if (trimmed[0] == '#') continue;
        stringstream ss(trimmed);
        ss >> filename >> startRow >> endRow;
        if (!filename.empty()) {
            found = true;
            break;
        }
    }
    configFile.close();

    if (!found || filename.empty()) {
        cerr << "Error: No valid configuration line found in " << configFilename << endl;
        return 1;
    }

    cout << "Using config: " << filename << " " << startRow << " " << endRow << endl;

    // Read CSV
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Cannot open CSV file " << filename << endl;
        return 1;
    }

    vector<Element> allElements;
    string row;
    int lineNum = 0;
    while (getline(inFile, row)) {
        lineNum++;
        string trimmedRow = trim(row);
        if (trimmedRow.empty()) continue;
        size_t comma = trimmedRow.find(',');
        if (comma == string::npos) continue;
        string keyStr = trim(trimmedRow.substr(0, comma));
        string valStr = trim(trimmedRow.substr(comma+1));
        bool valid = true;
        for (char c : keyStr) if (!isdigit(c)) { valid = false; break; }
        if (!valid || keyStr.empty()) continue;
        try {
            long long key = stoll(keyStr);
            allElements.push_back({key, valStr});
        } catch (...) { continue; }
    }
    inFile.close();

    if (allElements.empty()) {
        cerr << "Error: No valid data rows in " << filename << endl;
        return 1;
    }

    if (startRow < 1 || endRow > (int)allElements.size() || startRow > endRow) {
        cerr << "Error: Invalid row range. Total rows: " << allElements.size() << endl;
        return 1;
    }

    vector<Element> subArray(allElements.begin() + (startRow-1), allElements.begin() + endRow);

    // Output filename
    string baseName = filename;
    size_t under = baseName.find_last_of('_');
    size_t dot = baseName.find_last_of('.');
    string sizeStr = baseName.substr(under+1, dot-under-1);
    string outFile = "dataset_" + sizeStr + "_radix_sorted_step_" + to_string(startRow) + "_" + to_string(endRow) + ".txt";

    ofstream outFileStream(outFile);
    if (!outFileStream) {
        cerr << "Error: Cannot create output file" << endl;
        return 1;
    }

    // Radix sort with steps
    printArray(subArray, outFileStream);
    outFileStream << " original\n";

    long long digitPos = 1;
    int step = 10;
    while (digitPos <= 1000000000LL) {
        countingSort(subArray, digitPos);
        printArray(subArray, outFileStream);
        outFileStream << " d=" << step << "\n";
        digitPos *= 10;
        step--;
    }
    outFileStream.close();

    cout << "Step output written to " << outFile << endl;
    return 0;
}
