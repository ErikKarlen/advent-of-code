#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


class Area {
public:
        vector<vector<int>> height_map;

        void add_heights(string heights_s);

        void borderize();

        size_t basin_size(size_t row, size_t col);
};


void Area::add_heights(string heights_s)
{
        vector<int> heights;

        for (char& c : heights_s) {
                heights.push_back(c - '0');
        }

        height_map.push_back(heights);
}


void Area::borderize()
{
        for (auto& v : height_map) {
                for (auto& h : v) {
                        h = h == 9 ? 1 : 0;
                }
        }
}


size_t Area::basin_size(size_t row, size_t col)
{
        size_t size = 1;
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

        height_map[row][col] = 1;

        if (check_t && height_map[row - 1][col] == 0) {
                height_map[row - 1][col] = 1;
                size += basin_size(row - 1, col);
        }
        if (check_b && height_map[row + 1][col] == 0) {
                height_map[row + 1][col] = 1;
                size += basin_size(row + 1, col);
        }
        if (check_l && height_map[row][col - 1] == 0) {
                height_map[row][col - 1] = 1;
                size += basin_size(row, col - 1);
        }
        if (check_r && height_map[row][col + 1] == 0) {
                height_map[row][col + 1] = 1;
                size += basin_size(row, col + 1);
        }

        return size;
}


int main(int argc, char *argv[])
{
        ifstream infile;
        string line;
        Area area;
        vector<size_t> basin_sizes;

        infile.open(argv[1]);

        while (getline(infile, line)) {
                area.add_heights(line);
        }

        area.borderize();

        for (size_t row = 0; row < area.height_map.size(); ++row) {
                for (size_t col = 0; col < area.height_map[0].size(); ++col) {
                        if (area.height_map[row][col] == 0) {
                                size_t size = area.basin_size(row, col);
                                basin_sizes.push_back(size);
                        }
                }
        }

        sort(basin_sizes.begin(), basin_sizes.end());

        /*
        for (auto& size : basin_sizes) {
                cout << size << endl;
        }

        for (auto& v : area.height_map) {
                for (auto& h : v) {
                        cout << h;
                }
                cout << endl;
        }

        cout << basin_sizes.end()[-3] << endl;
        cout << basin_sizes.end()[-2] << endl;
        cout << basin_sizes.end()[-1] << endl;
        */

        cout << basin_sizes.end()[-3] * basin_sizes.end()[-2] * basin_sizes.end()[-1] << endl;

        return 0;
}
