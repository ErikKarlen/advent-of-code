#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


class Area {
public:
        vector<vector<int>> height_map;

        void add_heights(string heights_s);

        int risk_level(size_t row, size_t col);
};


void Area::add_heights(string heights_s)
{
        vector<int> heights;

        for (char& c : heights_s) {
                heights.push_back(c - '0');
        }

        height_map.push_back(heights);
}


int Area::risk_level(size_t row, size_t col)
{
        bool check_t = true;
        bool check_b = true;
        bool check_l = true;
        bool check_r = true;

        if (row == 0) {
                check_t = false;
        } else if (row == height_map.size() - 1) {
                check_b = false;
        }

        if (col == 0) {
                check_l = false;
        } else if (col == height_map.front().size() - 1) {
                check_r = false;
        }

        //cout << "check_t: " << check_t << endl;
        //cout << "check_b: " << check_b << endl;
        //cout << "check_l: " << check_l << endl;
        //cout << "check_r: " << check_r << endl;
        //cout << "row, col: " << height_map[row][col] << endl;
        //cout << "row+1, col: " << height_map[row+1][col] << endl;
        //cout << "row+1, col: " << height_map[row+1][col] << endl;

        if (check_t && height_map[row][col] >= height_map[row - 1][col]) {
                return 0;
        }
        if (check_b && height_map[row][col] >= height_map[row + 1][col]) {
                return 0;
        }
        if (check_l && height_map[row][col] >= height_map[row][col - 1]) {
                return 0;
        }
        if (check_r && height_map[row][col] >= height_map[row][col + 1]) {
                return 0;
        }
        return height_map[row][col] + 1;
}


int main(int argc, char *argv[])
{
        ifstream infile;
        string line;
        Area area;
        int total_risk = 0;

        infile.open(argv[1]);

        while (getline(infile, line)) {
                area.add_heights(line);
        }

        for (size_t row = 0; row < area.height_map.size(); ++row) {
                for (size_t col = 0; col < area.height_map[0].size(); ++col) {
                        //cout << "row: " << row << ", col: " << col << endl;
                        int risk = area.risk_level(row, col);
                        total_risk += risk;
                        //cout << ", risk: " << risk << endl;
                }
        }

        cout << "total risk: " << total_risk << endl;
        //int risk = area.risk_level(0, 1);
        //cout << "risk_level: " << risk << endl;

        /*
        for (auto& row : area.height_map) {
                int line_sum = 0;
                for (auto& h : v) {
                        line_sum += h;
                }
                cout << line_sum << endl;
        }
        */

        return 0;
}
