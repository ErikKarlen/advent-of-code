#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;


bool isValidTriangle(int s1, int s2, int s3)
{
        return 2 * max({s1, s2, s3}) < s1 + s2 + s3;
}

int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int numValidTriangles = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                size_t last = line.find_first_not_of(" ");
                size_t next = line.find(" ", last + 1);
                int s1 = stoi(line.substr(last, next - last));
                last = line.find_first_not_of(" ", next + 1);
                next = line.find(" ", last + 1);
                int s2 = stoi(line.substr(last, next - last));
                last = line.find_first_not_of(" ", next + 1);
                next = line.find(" ", last + 1);
                int s3 = stoi(line.substr(last, next - last));

                numValidTriangles += isValidTriangle(s1, s2, s3) ? 1 : 0;
        }

        cout << "There are " << numValidTriangles << " valid triangles listed." << endl;

        return 0;
}
