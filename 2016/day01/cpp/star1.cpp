#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        size_t pos_string = -1;
        int x_pos = 0, y_pos = 0;
        int x_dir = 0, y_dir = 1;

        inFile.open(argv[1]);

        getline(inFile, line);

        while ((pos_string = line.find_first_of("RL", pos_string + 1)) != string::npos) {
                char direction = line[pos_string];
                int distance = stoi(line.substr(pos_string + 1, line.find(',', pos_string + 1) - pos_string- 1));

                if (x_dir) {
                        if (direction == 'R') {
                                y_dir = -x_dir;
                        } else {
                                y_dir = x_dir;
                        }
                        x_dir = 0;
                } else {
                        if (direction == 'R') {
                                x_dir = y_dir;
                        } else {
                                x_dir = -y_dir;
                        }
                        y_dir = 0;
                }
                x_pos += x_dir * distance;
                y_pos += y_dir * distance;
        }

        cout << "Easter Bunny HQ is " << abs(x_pos) + abs(y_pos) << " blocks away." << endl;

        return 0;
}
