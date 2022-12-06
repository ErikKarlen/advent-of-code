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

        for (int i = 4; i <= line.size(); i++) {
                set<char> chars;
                for (int j = 1; j <= 4; ++j) {
                        chars.insert(line[i - j]);
                }
                if (chars.size() == 4) {
                        processedCharacters = i;
                        break;
                }
        }

        cout << "A total of " << processedCharacters << " need to be processed "
                << "before the first start-of-packet marker is detected. " << endl;

        return 0;
}
