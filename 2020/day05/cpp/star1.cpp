#include <bitset>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int highestSeatId = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                //cout << line << ": ";
                bitset<7> rowbit(line, 0, 7, 'F', 'B');
                bitset<3> colbit(line, 7, 3, 'L', 'R');
                int row = rowbit.to_ulong();
                int col = colbit.to_ulong();
                int seatId = row * 8 + col;
                highestSeatId = seatId > highestSeatId ? seatId : highestSeatId;
                //cout << "(row, col): (" << row.to_ulong() << ", " << col.to_ulong() << ")" << endl;
        }

        cout << "The highest seat ID is " << highestSeatId << "." << endl;

        return 0;
}
