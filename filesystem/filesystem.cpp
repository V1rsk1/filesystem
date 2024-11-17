#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

void createFrequencyDictionary(const fs::path& inputPath, const fs::path& outputPath) {
    ifstream inputFile(inputPath);
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return;
    }

    map<string, int> frequency;
    string word;
    while (inputFile >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        ++frequency[word];
    }
    inputFile.close();

    string mostFrequentWord;
    int maxCount = 0;
    for (const auto& entry : frequency) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
            mostFrequentWord = entry.first;
        }
    }

    ofstream outputFile(outputPath);
    if (!outputFile) {
        cerr << "Error: Unable to open output file." << endl;
        return;
    }

    for (const auto& entry : frequency)
        outputFile << entry.first << ": " << entry.second << endl;

    if (!mostFrequentWord.empty())
        outputFile << endl << "Most frequent word: " << mostFrequentWord
        << " (" << maxCount << " times)" << endl;
}

int main() {
    fs::path inputPath = "input.txt";
    fs::path outputPath = "output.txt";

    if (!fs::exists(inputPath)) {
        cerr << "Error: Input file does not exist." << endl;
        return 1;
    }

    createFrequencyDictionary(inputPath, outputPath);
    cout << "Results written to " << outputPath << endl;
    return 0;
}
