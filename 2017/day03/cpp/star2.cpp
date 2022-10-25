#include <iostream>
#include <fstream>
#include <map>
#include <string>


using namespace std;


int sumOfNeighbours(int xPos, int yPos, const map<pair<int, int>, int> & squareMap)
{
        int sum = 0;
        for (int y = -1; y <= 1; ++y) {
                for (int x = -1; x <= 1; ++x) {
                        if (x == 0 && y == 0) {
                                continue;
                        }
                        pair<int, int> pos = { xPos + x, yPos + y };
                        sum += squareMap.count(pos) > 0 ? squareMap.at(pos) : 0;
                }
        }
        return sum;
}

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
        map<pair<int, int>, int> squareMap;
        squareMap[{ xPos, yPos }] = squareNum;

        inFile.open(argv[1]);

        getline(inFile, line);
        target = stoi(line);

        while (squareNum <= target) {
                xPos += currentDir == 0 ? 1 : 0;
                yPos += currentDir == 1 ? 1 : 0;
                xPos += currentDir == 2 ? -1 : 0;
                yPos += currentDir == 3 ? -1 : 0;

                if (++dirCounter == dirTimes / 2) {
                        dirCounter = 0;
                        currentDir = (currentDir + 1) % 4;
                        dirTimes++;
                }
                squareNum = sumOfNeighbours(xPos, yPos, squareMap);
                squareMap[{ xPos, yPos }] = squareNum;
        }

        cout << "The first value larger than the puzzle input is " << squareNum << "." << endl;

        return 0;
}
