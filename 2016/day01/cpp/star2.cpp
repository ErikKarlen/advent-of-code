#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        size_t pos_string = -1;
        int x_pos = 0, y_pos = 0;
        int x_dir = 0, y_dir = 1;
        set<pair<int, int>> visited;

        inFile.open(argv[1]);

        getline(inFile, line);

        while ((pos_string = line.find_first_of("RL", pos_string + 1)) != string::npos) {
                int x_pos_new, y_pos_new;
                char direction = line[pos_string];
                int distance = stoi(line.substr(pos_string + 1, line.find(',', pos_string + 1) - pos_string- 1));
                bool finished = false;

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

                x_pos_new = x_pos + x_dir * distance;
                y_pos_new = y_pos + y_dir * distance;

                for (int x = x_pos; x != x_pos_new; x += x_dir) {
                        pair<int, int> coord(x, y_pos);
                        if (visited.find(coord) != visited.end()) {
                                x_pos = x;
                                finished = true;
                                break;
                        }
                        visited.insert(coord);
                }

                for (int y = y_pos; y != y_pos_new; y += y_dir) {
                        pair<int, int> coord(x_pos, y);
                        if (visited.find(coord) != visited.end()) {
                                y_pos = y;
                                finished = true;
                                break;
                        }
                        visited.insert(coord);
                }

                if (finished) {
                        break;
                }

                x_pos = x_pos_new;
                y_pos = y_pos_new;
        }

        cout << "The first location you visit twice is " << abs(x_pos) + abs(y_pos) << " blocks away." << endl;

        return 0;
}
