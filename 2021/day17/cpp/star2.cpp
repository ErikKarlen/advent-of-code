#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


void print_positions(vector<pair<int, int>> & probe_positions)
{
        for (pair<int, int> probe_pos : probe_positions) {
                cout << "(" << probe_pos.first << ", " << probe_pos.second << ")" << endl;
        }
}


pair<bool, int> calc_probe_positions(
        pair<int, int> & init_vel,
        pair<int, int> & x_target,
        pair<int, int> & y_target,
        vector<pair<int, int>> & probe_positions)
{
        pair<int, int> vel = init_vel;
        pair<int, int> pos = { 0, 0 };
        pair<bool, int> hit_height = { false, 0 };

        while (pos.first <= x_target.second && pos.second >= y_target.first) {
                pos.first += vel.first;
                pos.second += vel.second;
                vel.first = max(0, vel.first - 1);
                vel.second--;
                probe_positions.push_back(pos);
                if (x_target.first <= pos.first && pos.first <= x_target.second &&
                    y_target.first <= pos.second && pos.second <= y_target.second) {
                        hit_height.first = true;
                }
                if (pos.second > hit_height.second) {
                        hit_height.second = pos.second;
                }
        }
        return hit_height;
}


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line, s;
        size_t pos, n;
        pair<int, int> init_vel, x_target, y_target;
        int num_hits = 0;

        inFile.open(argv[1]);
        getline(inFile, line);

        pos = line.find('=') + 1;
        n = line.find('.', pos) - pos;
        x_target.first = stoi(line.substr(pos, n));
        pos += n + 2;
        n = line.find(',', pos) - pos;
        x_target.second = stoi(line.substr(pos, n));

        pos = line.find('=', pos) + 1;
        n = line.find('.', pos) - pos;
        y_target.first = stoi(line.substr(pos, n));
        pos += n + 2;
        n = line.find(',', pos) - pos;
        y_target.second = stoi(line.substr(pos, n));

        for (int x_vel = 1; x_vel <= x_target.second; ++x_vel) {
                for (int y_vel = y_target.first; y_vel <= -y_target.first + 100; y_vel++) {
                        init_vel = { x_vel, y_vel };
                        vector<pair<int, int>> probe_positions;
                        pair<bool, int> hit_height = calc_probe_positions(init_vel, x_target, y_target, probe_positions);
                        if (hit_height.first) {
                                cout << "(" << init_vel.first << ", " << init_vel.second << ")" << endl;
                                num_hits++;
                        }
                }
        }

        cout << num_hits << endl;

        return 0;
}
