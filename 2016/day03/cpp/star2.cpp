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
                int s11 = stoi(line.substr(last, next - last));
                last = line.find_first_not_of(" ", next + 1);
                next = line.find(" ", last + 1);
                int s21 = stoi(line.substr(last, next - last));
                last = line.find_first_not_of(" ", next + 1);
                next = line.find(" ", last + 1);
                int s31 = stoi(line.substr(last, next - last));

                getline(inFile, line);

                last = line.find_first_not_of(" ");
                next = line.find(" ", last + 1);
                int s12 = stoi(line.substr(last, next - last));
                last = line.find_first_not_of(" ", next + 1);
                next = line.find(" ", last + 1);
                int s22 = stoi(line.substr(last, next - last));
                last = line.find_first_not_of(" ", next + 1);
                next = line.find(" ", last + 1);
                int s32 = stoi(line.substr(last, next - last));

                getline(inFile, line);

                last = line.find_first_not_of(" ");
                next = line.find(" ", last + 1);
                int s13 = stoi(line.substr(last, next - last));
                last = line.find_first_not_of(" ", next + 1);
                next = line.find(" ", last + 1);
                int s23 = stoi(line.substr(last, next - last));
                last = line.find_first_not_of(" ", next + 1);
                next = line.find(" ", last + 1);
                int s33 = stoi(line.substr(last, next - last));

                numValidTriangles += isValidTriangle(s11, s12, s13) ? 1 : 0;
                numValidTriangles += isValidTriangle(s21, s22, s23) ? 1 : 0;
                numValidTriangles += isValidTriangle(s31, s32, s33) ? 1 : 0;
        }

        cout << "There are " << numValidTriangles << " valid triangles listed." << endl;

        return 0;
}
