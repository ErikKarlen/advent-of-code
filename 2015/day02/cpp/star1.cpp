#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int wrapping_paper = 0;

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

                int s1 = l*w, s2 = w*h, s3 = h*l;
                int slack = min({s1, s2, s3});

                wrapping_paper += 2*(s1 + s2 + s3) + slack;
        }

        cout << "The elves should order a total of " << wrapping_paper
                << " square feet of wrapping paper." << endl;

        return 0;
}
