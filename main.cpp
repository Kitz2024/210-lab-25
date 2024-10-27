//Kit Pollinger
// 210 - Lab - 25 | Data Structure Race

#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// read data into a container (using push_back for vector)
template <typename Container>
void readData(Container& container, ifstream& inFile) {
    string data;
    while (getline(inFile, data)) {
        container.push_back(data);
    }
}

// Overloaded readData for list (also uses push_back for consistency)
template <>
void readData(list<string>& container, ifstream& inFile) {
    string data;
    while (getline(inFile, data)) {
        container.push_back(data);
    }
}

// Specialization for set reading (uses `insert` directly)
template <>
void readData(set<string>& container, ifstream& inFile) {
    string data;
    while (getline(inFile, data)) {
        container.insert(data);
    }
}

// reset and re-read data from the file for each container
template <typename Container>
milliseconds timeRead(Container& container, const string& filename) {
    container.clear();
    ifstream inFile("C:\\210-Coding\\projects\\210-lab-25-starter\\codes.txt");
    if (!inFile.is_open()) {
        cout << "Error opening data file!" << endl;
        return milliseconds(0);
    }
    auto start = high_resolution_clock::now();
    readData(container, inFile);
    auto end = high_resolution_clock::now();
    inFile.close();

    return duration_cast<milliseconds>(end - start);
}

// time sorting operation
template <typename Container>
milliseconds timeSort(Container& container) {
    auto start = high_resolution_clock::now();
    container.sort();
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start);
}

// sorting vector using `std::sort`
template <>
milliseconds timeSort(vector<string>& container) {
    auto start = high_resolution_clock::now();
    sort(container.begin(), container.end());
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start);
}

//time insertion operation
template <typename Container>
milliseconds timeInsert(Container& container) {
    auto start = high_resolution_clock::now();
    auto it = container.begin();
    advance(it, container.size() / 2);
    container.insert(it, "TESTCODE");
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start);
}

// set insertion 
template <>
milliseconds timeInsert(set<string>& container) {
    auto start = high_resolution_clock::now();
    container.insert("TESTCODE"); // Single insertion for consistency
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start);
}

// time deletion operation
template <typename Container>
milliseconds timeDelete(Container& container) {
    auto start = high_resolution_clock::now();
    auto it = container.begin();
    advance(it, container.size() / 2);
    container.erase(it);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start);
}

// Deleting middle-ish element of set
template <>
milliseconds timeDelete(set<string>& container) {
    auto start = high_resolution_clock::now();
    auto it = container.begin();
    advance(it, container.size() / 2); // Move iterator to middle element
    container.erase(it); // Erase the middle element
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start);
}


int main() {
    string filename = "C:\\210-Coding\\projects\\210-lab-25-starter\\codes.txt";

    // Create  vector, list, and set
    vector<string> vec;
    list<string> lst;
    set<string> st;

    // Race 1: Reading 20000 from data file
    auto vecReadTime = timeRead(vec, filename);
    auto lstReadTime = timeRead(lst, filename);
    auto stReadTime = timeRead(st, filename);

    // Verify that containers have correct sizes
    cout << "Vector size after reading: " << vec.size() << endl;
    cout << "List size after reading: " << lst.size() << endl;
    cout << "Set size after reading: " << st.size() << endl;
    cout << endl;
    cout << "Data file outputs" << endl;

    // Race 2: Sorting vector and list
    auto vecSortTime = timeSort(vec);
    auto lstSortTime = timeSort(lst);
    milliseconds setSortTime(-1); // Set is already sorted

    // Race 3: Inserting Value "TESTCODE"
    auto vecInsertTime = timeInsert(vec);
    auto lstInsertTime = timeInsert(lst);
    auto stInsertTime = timeInsert(st);

    // Race 4: Deleting data
    auto vecDeleteTime = timeDelete(vec);
    auto lstDeleteTime = timeDelete(lst);
    auto stDeleteTime = timeDelete(st);

    // Print results
    cout << "Operation\tVector\tList\tSet" << endl;
    cout << "Read\t\t" << vecReadTime.count()
         << "\t" << lstReadTime.count()
         << "\t" << stReadTime.count() << endl;
    cout << "Sort\t\t" << vecSortTime.count()
         << "\t" << lstSortTime.count()
         << "\t" << setSortTime.count() << endl;
    cout << "Insert\t\t" << vecInsertTime.count()
         << "\t" << lstInsertTime.count()
         << "\t" << stInsertTime.count() << endl;
    cout << "Delete\t\t" << vecDeleteTime.count()
         << "\t" << lstDeleteTime.count()
         << "\t" << stDeleteTime.count() << endl;

    return 0;
}
