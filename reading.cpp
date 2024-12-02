#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Function to read all lines from the file
vector<string> readAllLines(ifstream& infile) {
    vector<string> lines;
    string line;


    // Read all lines
    while (getline(infile, line)) {
        if (!line.empty()) {
            lines.push_back(line); // Add line to vector
        }
    }

    return lines;
}

int main(int argc, char* argv[]) {

    // Check if the number of arguments is correct?

    string historyFile = argv[2];
    string outputFile = argv[4];

    ifstream infile(historyFile);
    ofstream fout(outputFile);

    if (!infile.is_open() || !fout.is_open()) {
        cerr << "Error: Unable to open input or output file." << endl;
        return 1;
    }

    // Read all lines from the input file
    vector<string> allLines = readAllLines(infile);

    // Count total lines
    size_t lineCount = allLines.size();

    // Determine color based on line count
    string color = (lineCount % 2 == 1) ? "black" : "white";


    fout << "New_move (" << color << ")" << endl;


    infile.close();
    fout.close();
    return 0;
}