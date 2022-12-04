#include <fstream>
#include <iostream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int overlappingPairs = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                size_t last = 0;
                size_t next = line.find('-', last);
                int elf1Start = stoi(line.substr(last, next - last));
                last = next + 1;
                next = line.find(',', last);
                int elf1End = stoi(line.substr(last, next - last));
                last = next + 1;
                next = line.find('-', last);
                int elf2Start = stoi(line.substr(last, next - last));
                int elf2End = stoi(line.substr(next + 1));
                //cout << elf1Start << "-" << elf1End << "," << elf2Start << "-" << elf2End << endl;
                if (elf1Start == elf2Start || elf1Start == elf2End) {
                        overlappingPairs++;
                } else if (elf1End == elf2Start || elf1End == elf2End) {
                        overlappingPairs++;
                } else if (elf1Start < elf2Start && elf1End > elf2Start) {
                        overlappingPairs++;
                } else if (elf2Start < elf1Start && elf2End > elf1Start) {
                        overlappingPairs++;
                }
        }
        
        cout << "In a total of " << overlappingPairs << " assignment pairs "
                << "do the ranges overlap." << endl;

        return 0;
}
