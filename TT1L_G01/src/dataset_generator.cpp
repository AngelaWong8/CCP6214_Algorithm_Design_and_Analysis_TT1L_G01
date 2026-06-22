// *********************************************************
// Program: dataset_generator.cpp
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
#include <string>
#include <cstdlib>
#include <unordered_set>
#include <iomanip>

using namespace std;

unsigned int convertStudentIdToSeed(string id) {
    string result = "";
    for (char c : id) {
        if (c >= '0' && c <= '9') {
            result += c;
        }
        else if (c >= 'A' && c <= 'Z') {
            if (c == 'A' || c == 'K' || c == 'U') result += '1';
            else if (c == 'B' || c == 'L' || c == 'V') result += '2';
            else if (c == 'C' || c == 'M' || c == 'W') result += '3';
            else if (c == 'D' || c == 'N' || c == 'X') result += '4';
            else if (c == 'E' || c == 'O' || c == 'Y') result += '5';
            else if (c == 'F' || c == 'P' || c == 'Z') result += '6';
            else if (c == 'G' || c == 'Q') result += '7';
            else if (c == 'H' || c == 'R') result += '8';
            else if (c == 'I' || c == 'S') result += '9';
            else if (c == 'J' || c == 'T') result += '0';
        }
    }
    return (unsigned int)stoul(result);
}

string randomString() {
    string s = "";
    for (int i = 0; i < 5; i++) {
        s += 'a' + (rand() % 26);
    }
    return s;
}

long long random10Digit() {
    long long r = (long long)rand() * (long long)rand();
    return 1000000000LL + (r % 9000000000LL);
}

void generateDataset(string filename, int n) {
    cout << "  Generating " << n << " unique numbers..." << endl;

    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Error: Cannot create " << filename << endl;
        return;
    }

    unordered_set<long long> used;
    used.reserve(n * 2);

    // Show progress every 5%
    int nextPercent = 5;

    for (int i = 0; i < n; i++) {
        long long num;
        do {
            num = random10Digit();
        } while (used.find(num) != used.end());

        used.insert(num);
        file << num << "," << randomString() << "\n";

        // Progress bar
        int currentPercent = ((i + 1) * 100) / n;
        if (currentPercent >= nextPercent) {
            cout << "\r    [" << setw(3) << currentPercent << "%] ";
            cout << string(currentPercent / 2, '=') << string(50 - currentPercent / 2, ' ') << "]";
            cout.flush();
            nextPercent += 5;
        }
    }

    cout << "\r    [100%] " << string(50, '=') << "]" << endl;
    file.close();
    cout << "  Saved to " << filename << " (" << n << " rows)" << endl;
}

int main() {
    string studentId = "252UC254Q4";
    unsigned int seed = convertStudentIdToSeed(studentId);
    srand(seed);

    cout << "========================================" << endl;
    cout << "Dataset Generator" << endl;
    cout << "========================================" << endl;
    cout << "Student ID: " << studentId << endl;
    cout << "Seed: " << seed << endl;
    cout << endl;

    int sizes[] = {
        1000000,    // 1M
        5000000,    // 5M
        10000000,   // 10M
        15000000,   // 15M
        20000000,   // 20M
        25000000,   // 25M
        30000000,   // 30M
        35000000,   // 35M
        40000000,   // 40M
        50000000    // 50M
    };

    cout << "Generating 10 files:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "  " << (i+1) << ". dataset_" << sizes[i] << ".csv (" << sizes[i] << " rows)" << endl;
    }
    cout << endl;

    for (int i = 0; i < 10; i++) {
        cout << "\n[" << (i+1) << "/10] Creating dataset_" << sizes[i] << ".csv" << endl;
        generateDataset("dataset_" + to_string(sizes[i]) + ".csv", sizes[i]);
    }

    cout << "\n========================================" << endl;
    cout << "ALL DONE! 10 files created." << endl;
    cout << "========================================" << endl;

    return 0;
}
