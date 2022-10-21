#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int calculate_fuel(int mass)
{
        return mass / 3 - 2;
}

int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int fuel_sum = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                int mass = stoi(line);
                int fuel = calculate_fuel(mass);
                while (fuel > 0) {
                        fuel_sum += fuel;
                        fuel = calculate_fuel(fuel);
                }
        }

        cout << "The sum of the fuel requirements when also taking into account the mass of the added fuel is " << fuel_sum << "." << endl;

        return 0;
}
