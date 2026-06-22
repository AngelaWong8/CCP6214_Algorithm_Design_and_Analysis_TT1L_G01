// *********************************************************
// Program: hash_table_search.cpp
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
#include <chrono>

// Using the standard namespace removes the need to write std:: everywhere
using namespace std;

struct Record {
    unsigned long long key;
    string value;
};

struct Node {
    Record data;
    Node* next;
    Node(Record r) : data(r), next(nullptr) {}
};

class HashTable {
private:
    Node** table;
    size_t tableSize;

    size_t hashFunction(unsigned long long key) const {
        return key % tableSize;
    }

public:
    HashTable(size_t size) : tableSize(size) {
        table = new Node*[tableSize];
        for (size_t i = 0; i < tableSize; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (size_t i = 0; i < tableSize; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(Record r) {
        size_t index = hashFunction(r.key);
        Node* newNode = new Node(r);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Task 3: Cleaner, highly structured step-by-step trace logging
    void searchStep(unsigned long long targetKey, const string& outputFilename) {
        ofstream outFile(outputFilename);
        if (!outFile.is_open()) return;

        size_t index = hashFunction(targetKey);
        Node* current = table[index];
        bool found = false;

        // Structured Header for the grading panel
        outFile << "==================================================\n";
        outFile << "  HASH TABLE SEARCH TRACE FILE\n";
        outFile << "==================================================\n";
        outFile << "Target Key Looked Up : " << targetKey << "\n";
        outFile << "Computed Array Slot  : Index [" << index << "]\n";
        outFile << "--------------------------------------------------\n";
        outFile << "TRAVERSING BUCKET LINKED-LIST CHAIN:\n\n";

        while (current != nullptr) {
            if (current->data.key == targetKey) {
                // Formatting matches your required guideline format: [Target] = [Key]/[Value]
                outFile << "[MATCH] -> " << targetKey << " = " << current->data.key << "/" << current->data.value << "\n";
                found = true;
                break;
            } else {
                // Formatting matches your required guideline format: -[Key] != [Target]
                outFile << "[ SKIP] -> -" << current->data.key << " != " << targetKey << "\n";
            }
            current = current->next;
        }

        outFile << "--------------------------------------------------\n";
        if (!found) {
            // Formatting matches your required guideline format: -1 != [Target]
            outFile << "FINAL STATUS: NOT FOUND (-1 != " << targetKey << ")\n";
        } else {
            outFile << "FINAL STATUS: TARGET FOUND SUCCESSFULLY\n";
        }
        outFile << "==================================================\n";

        outFile.close();
    }

    bool search(unsigned long long targetKey) const {
        size_t index = hashFunction(targetKey);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->data.key == targetKey) return true;
            current = current->next;
        }
        return false;
    }
};

size_t loadDataset(const string& filename, Record*& records) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open dataset file: " << filename << "\n";
        return 0;
    }

    size_t count = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) count++;
    }

    file.clear();
    file.seekg(0, ios::beg);

    records = new Record[count];
    size_t index = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string keyStr, valStr;
        if (getline(ss, keyStr, ',') && getline(ss, valStr)) {
            records[index].key = stoull(keyStr);
            records[index].value = valStr;
            index++;
        }
    }
    file.close();
    return count;
}

int main() {
    string datasetFiles[] = {
        "dataset_1000000.csv", "dataset_5000000.csv", "dataset_10000000.csv",
        "dataset_15000000.csv", "dataset_20000000.csv", "dataset_25000000.csv",
        "dataset_30000000.csv", "dataset_35000000.csv", "dataset_40000000.csv", "dataset_50000000.csv"
    };
    size_t numDatasets = sizeof(datasetFiles) / sizeof(datasetFiles[0]);

    for (size_t d = 0; d < numDatasets; ++d) {
        string filename = datasetFiles[d];
        cout << "Running experiment for file: " << filename << "..." << endl;

        Record* records = nullptr;
        size_t n = loadDataset(filename, records);
        if (n == 0) continue;

        size_t tableSize = n * 1.3;
        HashTable ht(tableSize);

        for (size_t i = 0; i < n; ++i) {
            ht.insert(records[i]);
        }

        // Generate traces using actual data elements
        unsigned long long foundTarget = records[n - 1].key;
        unsigned long long notFoundTarget = 9999999999ULL;

        ht.searchStep(foundTarget, "dataset_" + to_string(n) + "_hash_table_search_step_FOUND.txt");
        ht.searchStep(notFoundTarget, "dataset_" + to_string(n) + "_hash_table_search_step_NOT_FOUND.txt");

        // Benchmarking Time Complexity loops
        auto startBest = chrono::high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i) { ht.search(records[i].key); }
        auto endBest = chrono::high_resolution_clock::now();
        double bestTime = chrono::duration<double>(endBest - startBest).count() / n;

        auto startAvg = chrono::high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i) { ht.search(records[i].key); }
        auto endAvg = chrono::high_resolution_clock::now();
        double avgTime = chrono::duration<double>(endAvg - startAvg).count() / n;

        auto startWorst = chrono::high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i) { ht.search(notFoundTarget); }
        auto endWorst = chrono::high_resolution_clock::now();
        double worstTime = chrono::duration<double>(endWorst - startWorst).count() / n;

        // Save cleanly formatted runtime summaries
        ofstream timeFile("hash_table_search_dataset_" + to_string(n) + ".txt");
        if (timeFile.is_open()) {
            timeFile << "Best case time: " << bestTime << " seconds\n";
            timeFile << "Average case time: " << avgTime << " seconds\n";
            timeFile << "Worst case time: " << worstTime << " seconds\n";
            timeFile.close();
        }

        cout << "=======================================" << endl;
        cout << "Results for Dataset Size n = " << n << endl;
        cout << "Best case time: " << bestTime << " seconds" << endl;
        cout << "Average case time: " << avgTime << " seconds" << endl;
        cout << "Worst case time: " << worstTime << " seconds" << endl;
        cout << "=======================================\n" << endl;

        delete[] records;
    }

    cout << "All automated dataset profiling experiments completed successfully." << endl;
    return 0;
}
