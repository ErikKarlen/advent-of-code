#include <algorithm>
#include <bitset>
#include <iostream>
#include <fstream>
#include <set>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int mySeatId = 0;
        set<int> occupied;
        bool seatFound = false;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                //cout << line << ": ";
                bitset<7> rowbit(line, 0, 7, 'F', 'B');
                bitset<3> colbit(line, 7, 3, 'L', 'R');
                int row = rowbit.to_ulong();
                int col = colbit.to_ulong();
                int seatId = row * 8 + col;
                occupied.insert(seatId);
                //cout << "(row, col): (" << row.to_ulong() << ", " << col.to_ulong() << ")" << endl;
        }

        for (int id = 0; id < *max_element(occupied.begin(), occupied.end()); ++id) {
                if (occupied.count(id - 1) && occupied.count(id + 1) && !occupied.count(id)) {
                        mySeatId = id;
                        cout << id << endl;
                }
        }

        cout << "The ID of my seat is " << mySeatId << "." << endl;

        return 0;
}
