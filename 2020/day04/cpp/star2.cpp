#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <string>


using namespace std;


bool checkPassportValidity(map<string, string> & passport)
{
        for (const auto & pair : passport){
                cout << pair.first << ": " << pair.second << endl;
        }
        cout << endl;
        try {
                if (!(passport.count("byr") > 0
                        && passport.count("iyr") > 0
                        && passport.count("eyr") > 0
                        && passport.count("hgt") > 0
                        && passport.count("hcl") > 0
                        && passport.count("ecl") > 0
                        && passport.count("pid") > 0)) {
                        return false;
                }
                int byr = stoi(passport["byr"]);
                if (!(1920 <= byr && byr <= 2002 )) {
                        return false;
                }
                int iyr = stoi(passport["iyr"]);
                if (!(2010 <= iyr && iyr <= 2020)) {
                        return false;
                }
                int eyr = stoi(passport["eyr"]);
                if (!(2020 <= eyr && eyr <= 2030)) {
                        return false;
                }
                if (passport["hgt"].substr(passport["hgt"].size() - 2) == "cm") {
                        int hgt = stoi(passport["hgt"].substr(0, passport["hgt"].size() - 2));
                        if (!(150 <= hgt && hgt <= 193)) {
                                return false;
                        }
                } else if (passport["hgt"].substr(passport["hgt"].size() - 2) == "in") {
                        int hgt = stoi(passport["hgt"].substr(0, passport["hgt"].size() - 2));
                        if (!(59 <= hgt && hgt <= 76)) {
                                return false;
                        }
                }

                string hcl = passport["hcl"];
                if (!(hcl.size() == 7 && hcl.front() == '#' && hcl.substr(1).find_first_not_of("0123456789abcdef") == string::npos)) {
                        return false;
                }

                set<string> eyeColors = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
                string ecl = passport["ecl"];
                if (eyeColors.count(ecl) == 0) {
                        return false;
                }

                string pid = passport["pid"];
                if (!(pid.size() == 9 && pid.find_first_not_of("0123456789") == string::npos)) {
                        return false;
                }

                return true;
        } catch (exception e) {
                return false;
        }
}

int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int numValidPassports = 0;
        map<string, string> passport;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                if (line == "") {
                        //cout << endl;
                        //for (const auto & field : passport) {
                        //        cout << field << endl;
                        //}
                        if (checkPassportValidity(passport)) {
                                numValidPassports++;
                        }
                        passport.clear();
                        //cout << endl;
                } else {
                        size_t next = line.find(":");
                        while (next != string::npos) {
                                string key = line.substr(next - 3, 3);
                                //cout << key << endl;
                                string value = line.substr(next + 1, line.find(" ", next) - next - 1);
                                //cout << "key: " << key << endl;
                                //cout << "value: " << value << endl << endl;
                                next = line.find(":", next + 1);
                                passport[key] = value;
                        }
                        //cout << endl;
                }
        }

        cout << "In my batch file there is a total of " << numValidPassports
                << " valid passports if we consider cid optional." << endl;

        return 0;
}
