#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <chrono>
#include <thread>


#define C0 "\033[1;232m"
#define C1 "\033[234m"
#define C2 "\033[236m"
#define C3 "\033[239m"
#define C4 "\033[241m"
#define C5 "\033[244m"
#define C6 "\033[246m"
#define C7 "\033[249m"
#define C8 "\033[252m"
#define C9 "\033[255m"
#define ENDC "\033[0m"


using namespace std;


class Octopus
{
        private:
                unsigned m_energy;
                bool m_hasFlashed;

        public:
                Octopus(unsigned energy=0, bool hasFlashed=false) :
                        m_energy(energy),
                        m_hasFlashed(hasFlashed)
                {}

                unsigned getEnergy() { return m_energy; }
                unsigned setEnergy(unsigned energy) { return m_energy = energy; }
                bool flash() { return m_hasFlashed = true; }
                unsigned levelUp() { return ++m_energy; }
                bool hasFlashed() { return m_hasFlashed; }
                bool reset() { setEnergy(0); return m_hasFlashed = false; }

                friend ostream & operator<<(ostream & _stream, Octopus const & o) {
                        switch(o.m_energy) {
                                case 0:
                                        _stream << C0 << 'X' << ENDC;
                                        break;
                                case 1:
                                        _stream << C1 << (char)('0' + o.m_energy) << ENDC;
                                        break;
                                case 2:
                                        _stream << C2 << (char)('0' + o.m_energy) << ENDC;
                                        break;
                                case 3:
                                        _stream << C3 << (char)('0' + o.m_energy) << ENDC;
                                        break;
                                case 4:
                                        _stream << C4 << (char)('0' + o.m_energy) << ENDC;
                                        break;
                                case 5:
                                        _stream << C5 << (char)('0' + o.m_energy) << ENDC;
                                        break;
                                case 6:
                                        _stream << C6 << (char)('0' + o.m_energy) << ENDC;
                                        break;
                                case 7:
                                        _stream << C7 << (char)('0' + o.m_energy) << ENDC;
                                        break;
                                case 8:
                                        _stream << C8 << (char)('0' + o.m_energy) << ENDC;
                                        break;
                                case 9:
                                        _stream << C9 << (char)('0' + o.m_energy) << ENDC;
                                        break;
                        }
                        return _stream;
                }
};


class OctopusGrid
{
        private:
                size_t m_numRows = 0, m_numCols = 0;
                unique_ptr<Octopus[]> m_grid;

                size_t index(size_t row, size_t col) const { return col + m_numRows * row; }
                unsigned addOctopus(size_t row, size_t col, unsigned energy)
                {
                        return m_grid[index(row, col)].setEnergy(energy);
                }
                bool levelAll();
        public:
                OctopusGrid(istream & gridStringStream, size_t numRows, size_t numCols);

                unsigned flash(size_t row, size_t col);
                /**
                 * Takes a step and returns if all octopuses are in sync.
                 */
                bool step();

                friend ostream & operator<<(ostream & _stream, OctopusGrid const & og);
};


OctopusGrid::OctopusGrid(istream & gridStream, size_t numRows, size_t numCols) :
        m_numRows(numRows),
        m_numCols(numCols),
        m_grid{new Octopus[numRows * numCols]}
{
        string line;

        for (int row = 0; row < numRows && getline(gridStream, line); ++row) {
                for (int col = 0; col < numCols; ++col) {
                        addOctopus(row, col, line[col] - '0');
                }
        }
}


bool OctopusGrid::levelAll()
{
        /* Level up all octopuses once */
        for (int row = 0; row < m_numRows; ++row) {
                for (int col = 0; col < m_numCols; ++col) {
                        m_grid[index(row, col)].levelUp();
                 }
        }
        return true;
}


unsigned OctopusGrid::flash(size_t row, size_t col)
{
        size_t ind, r, c;
        size_t adjRows[3] = { row - 1, row, row + 1 };
        size_t adjCols[3] = { col - 1, col, col + 1 };

        for (int i = 0; i < 3; ++i) {
                r = adjRows[i];
                for (int j = 0; j < 3; ++j) {
                        c = adjCols[j];
                        ind = index(adjRows[i], adjCols[j]);
                        if (r < 0 || r >= m_numRows || c < 0 || c >= m_numCols || (i == 1 && j == 1)) {
                                continue;
                        }
                        m_grid[ind].levelUp();
                        if (m_grid[ind].getEnergy() > 9 && !m_grid[ind].hasFlashed()) {
                                m_grid[ind].flash();
                                flash(adjRows[i], adjCols[j]);
                        }
                }
        }
        return 0;
}


bool OctopusGrid::step()
{
        size_t ind;
        bool inSync = true;

        /* Level up all octopuses once */
        levelAll();

        for (int row = 0; row < m_numRows; ++row) {
                for (int col = 0; col < m_numCols; ++col) {
                        ind = index(row, col);
                        if (!m_grid[ind].hasFlashed() && m_grid[ind].getEnergy() > 9) {
                                m_grid[ind].flash();
                                flash(row, col);
                        }
                }
        }
        for (int row = 0; row < m_numRows; ++row) {
                for (int col = 0; col < m_numCols; ++col) {
                        ind = index(row, col);
                        if (m_grid[ind].hasFlashed()) {
                                m_grid[index(row, col)].reset();
                        } else {
                                inSync = false;
                        }
                }
        }

        return inSync;
}



ostream & operator<<(ostream & _stream, OctopusGrid const & og)
{
        for (int row = 0; row < og.m_numRows ; ++row) {
                for (int col = 0; col < og.m_numCols; ++col) {
                        _stream << og.m_grid[og.index(row, col)];
                }
                _stream << endl;
        }
        return _stream;
}


int main(int argc, char *argv[])
{
        ifstream inFile;
        stringstream strStream;
        unsigned totalFlashes = 0, step = 0;

        inFile.open(argv[1]);
        strStream << inFile.rdbuf();

        OctopusGrid grid(strStream, 10, 10);

        while (++step < 500 && !grid.step()) {
                printf("\033[2J");
                printf("\033[%d;%dH", 0, 0);
                cout << grid << endl;
                this_thread::sleep_for(chrono::milliseconds(30));
        }

        printf("\033[2J");
        printf("\033[%d;%dH", 0, 0);
        cout << grid << endl;
        cout << step << endl;


        return 0;
}
