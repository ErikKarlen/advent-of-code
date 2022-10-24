#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int ribbon = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                int start = 0;
                int end = line.find('x', start);
                int l = stoi(line.substr(start, end));
                start = end + 1;
                end = line.find('x', start);
                int w = stoi(line.substr(start, end));
                start = end + 1;
                end = line.size();
                int h = stoi(line.substr(start, end));

                int longest = max({l, w, h});
                int volume = l*w*h;

                ribbon += 2*(l + w + h - longest) + volume;
        }

        cout << "The elves should order a total of " << ribbon << " feet of ribbon." << endl;

        return 0;
}
