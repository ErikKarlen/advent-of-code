#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>


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
                        char c = o.m_energy > 9 ? 'X' : '0' + o.m_energy;
                        _stream << c;
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
                 * Takes a step and returns the number of flashes for that step.
                 */
                unsigned step();

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


unsigned OctopusGrid::step()
{
        size_t ind;
        unsigned flashes = 0;

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
                                flashes++;
                                m_grid[index(row, col)].reset();
                        }
                }
        }

        return flashes;
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
        unsigned totalFlashes = 0;

        inFile.open(argv[1]);
        strStream << inFile.rdbuf();

        OctopusGrid grid(strStream, 10, 10);

        for (int i = 0; i < 100; ++i) {
                totalFlashes += grid.step();
        }

        cout << grid;
        cout << totalFlashes << endl;


        return 0;
}
