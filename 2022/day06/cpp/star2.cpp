#include <fstream>
#include <iostream>
#include <string>
#include <set>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int processedCharacters = 0;

        inFile.open(argv[1]);

        getline(inFile, line);
        //getline(inFile, line);
        //getline(inFile, line);
        //getline(inFile, line);
        //getline(inFile, line);

        for (int i = 14; i <= line.size(); i++) {
                set<char> chars;
                for (int j = 1; j <= 14; ++j) {
                        chars.insert(line[i - j]);
                }
                if (chars.size() == 14) {
                        processedCharacters = i;
                        break;
                }
        }

        cout << "A total of " << processedCharacters << " need to be processed "
                << "before the first start-of-message marker is detected. " << endl;

        return 0;
}
