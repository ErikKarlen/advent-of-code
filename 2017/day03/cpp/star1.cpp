#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int xPos = 0, yPos = 0;
        int squareNum = 1;
        int target;
        int dirTimes = 2; /* Two times the number of times to go one direction */
        int currentDir = 0; /* 0 = right, 1 = up, 2 = left, 3 = down */
        int dirCounter = 0; /* Counter to indicate direction change when reaching dirTimes / 2 */

        inFile.open(argv[1]);

        getline(inFile, line);
        target = stoi(line);

        while (squareNum != target) {
                xPos += currentDir == 0 ? 1 : 0;
                yPos += currentDir == 1 ? 1 : 0;
                xPos += currentDir == 2 ? -1 : 0;
                yPos += currentDir == 3 ? -1 : 0;

                if (++dirCounter == dirTimes / 2) {
                        dirCounter = 0;
                        currentDir = (currentDir + 1) % 4;
                        dirTimes++;
                }

                squareNum++;
        }

        cout << "The number of steps required to carry data from the square identified "
                << "to reach the access port is " << abs(xPos) + abs(yPos) << "." << endl;

        return 0;
}
