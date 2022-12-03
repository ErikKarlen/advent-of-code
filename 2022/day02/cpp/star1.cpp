#include <algorithm>
#include <fstream>
#include <iostream>
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
        set<string> win = { "A Y", "B Z", "C X"};
        set<string> draw = { "A X", "B Y", "C Z"};
        set<string> loss = { "A Z", "B X", "C Y"};

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                int roundScore;
                if (line.back() == 'X') {
                        roundScore = 1;
                } else if (line.back() == 'Y') {
                        roundScore = 2;
                } else if (line.back() == 'Z') {
                        roundScore = 3;
                }
                if (win.count(line)) {
                        roundScore += 6;
                } else if (draw.count(line)) {
                        roundScore += 3;
                }
                score += roundScore;
        }
        
        cout << "My total score if everything goes exactly according to my strategy guide would be "
                << score << "." << endl;

        return 0;
}
