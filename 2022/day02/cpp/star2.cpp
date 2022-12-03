#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int score = 0;
        map<char, int> losePoints = { {'A', 3}, {'B', 1}, {'C', 2} };
        map<char, int> drawPoints = { {'A', 1}, {'B', 2}, {'C', 3} };
        map<char, int> winPoints = { {'A', 2}, {'B', 3}, {'C', 1} };

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                if (line.back() == 'X') {
                        score += losePoints[line.front()];
                } else if (line.back() == 'Y') {
                        score += 3 + drawPoints[line.front()];
                } else {
                        score += 6 + winPoints[line.front()];
                }
        }
        
        cout << "My total score if everything goes exactly according to my strategy guide would be "
                << score << "." << endl;

        return 0;
}
