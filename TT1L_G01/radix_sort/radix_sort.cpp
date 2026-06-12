// *********************************************************
// Program: radix_sort.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC1L
// Tutorial Class: TT1L
// Trimester: 2620
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
#include <chrono>
#include <cctype>
#include <algorithm>

using namespace std;
using namespace std::chrono;

struct Element {
    long long key;
    string value;
};

// Trim whitespace from a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

// Stable counting sort for a specific digit (0-9)
void countingSort(vector<Element>& arr, long long digitPos) {
    int n = arr.size();
    if (n == 0) return;

    vector<Element> output(n);
    int count[10] = {0};

    // Count occurrences of each digit
    for (int i = 0; i < n; i++) {
        int digit = (arr[i].key / digitPos) % 10;
        count[digit]++;
    }

    // Cumulative count for stable placement
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build output array from right to left (stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i].key / digitPos) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy back
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// LSD Radix Sort for 10-digit numbers (rightmost digit first)
void radixSort(vector<Element>& arr) {
    // Digit positions: 1, 10, 100, ..., 1,000,000,000
    long long digitPos = 1;
    for (int digit = 0; digit < 10; digit++) {
        countingSort(arr, digitPos);
        digitPos *= 10;
    }
}

// Extract dataset size from filename (e.g., dataset_1000.csv -> 1000)
string extractSize(const string& filename) {
    size_t under = filename.find_last_of('_');
    size_t dot = filename.find_last_of('.');
    if (under == string::npos || dot == string::npos || under >= dot)
        return "unknown";
    return filename.substr(under + 1, dot - under - 1);
}

int main(int argc, char* argv[]) {
    string configFilename = "config.txt";
    if (argc >= 2) configFilename = argv[1];

    // Read configuration file (skip comment lines)
    ifstream configFile(configFilename);
    if (!configFile) {
        cerr << "Error: Cannot open config file '" << configFilename << "'" << endl;
        return 1;
    }

    string line, csvFilename;
    bool found = false;
    while (getline(configFile, line)) {
        string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#') continue;
        stringstream ss(trimmed);
        ss >> csvFilename;
        if (!csvFilename.empty()) {
            found = true;
            break;
        }
    }
    configFile.close();

    if (!found || csvFilename.empty()) {
        cerr << "Error: No valid CSV filename found in " << configFilename << endl;
        return 1;
    }

    cout << "Input file: " << csvFilename << endl;

    // Load dataset
    ifstream inFile(csvFilename);
    if (!inFile) {
        cerr << "Error: Cannot open CSV file " << csvFilename << endl;
        return 1;
    }

    vector<Element> data;
    string row;
    int lineNum = 0;
    while (getline(inFile, row)) {
        lineNum++;
        string trimmedRow = trim(row);
        if (trimmedRow.empty()) continue;
        size_t comma = trimmedRow.find(',');
        if (comma == string::npos) {
            cerr << "Warning: Line " << lineNum << " has no comma, skipping" << endl;
            continue;
        }
        string keyStr = trim(trimmedRow.substr(0, comma));
        string valStr = trim(trimmedRow.substr(comma + 1));
        // Validate key is numeric
        bool valid = true;
        for (char c : keyStr) if (!isdigit(c)) { valid = false; break; }
        if (!valid || keyStr.empty()) continue;
        try {
            long long key = stoll(keyStr);
            data.push_back({key, valStr});
        } catch (...) { continue; }
    }
    inFile.close();

    if (data.empty()) {
        cerr << "Error: No valid data loaded from " << csvFilename << endl;
        return 1;
    }

    cout << "Loaded " << data.size() << " elements." << endl;

    // Sort the data (measure only sorting time, exclude I/O)
    auto start = high_resolution_clock::now();
    radixSort(data);
    auto end = high_resolution_clock::now();
    double duration = duration_cast<milliseconds>(end - start).count() / 1000.0;

    // Output sorted CSV
    string sizeStr = extractSize(csvFilename);
    string outCsv = "dataset_" + sizeStr + ".radix_sorted_dataset_" + sizeStr + ".csv";
    ofstream outFile(outCsv);
    if (!outFile) {
        cerr << "Error: Cannot create output file " << outCsv << endl;
        return 1;
    }
    for (const auto& elem : data) {
        outFile << elem.key << "," << elem.value << "\n";
    }
    outFile.close();

    // Write running time to a text file
    string timeFile = "radix_sort_time_" + sizeStr + ".txt";
    ofstream timeOut(timeFile);
    if (timeOut) {
        timeOut << "Dataset size: " << data.size() << "\n";
        timeOut << "Sorting time (seconds): " << duration << "\n";
        timeOut.close();
    }

    // Print to console
    cout << "Sorted data written to " << outCsv << endl;
    cout << "Running time: " << duration << " seconds" << endl;
    cout << "Time also saved to " << timeFile << endl;

    return 0;
}
