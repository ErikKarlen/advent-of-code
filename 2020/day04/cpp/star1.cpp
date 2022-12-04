#include <iostream>
#include <fstream>
#include <set>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int numValidPassports = 0;
        set<string> passport;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                if (line == "") {
                        //cout << endl;
                        //for (const auto & field : passport) {
                        //        cout << field << endl;
                        //}
                        if (passport.count("byr") > 0
                                && passport.count("iyr") > 0
                                && passport.count("eyr") > 0
                                && passport.count("hgt") > 0
                                && passport.count("hcl") > 0
                                && passport.count("ecl") > 0
                                && passport.count("pid") > 0) {
                                numValidPassports++;
                        }
                        passport.clear();
                        //cout << endl;
                } else {
                        size_t next = line.find(":");
                        while (next != string::npos) {
                                string key = line.substr(next - 3, 3);
                                //cout << key << endl;
                                passport.insert(key);
                                next = line.find(":", next + 1);
                                //string value = line.substr(last, next - last);
                        }
                        //cout << endl;
                }
        }
        if (passport.count("byr") > 0
                && passport.count("iyr") > 0
                && passport.count("eyr") > 0
                && passport.count("hgt") > 0
                && passport.count("hcl") > 0
                && passport.count("ecl") > 0
                && passport.count("pid") > 0) {
                numValidPassports++;
        }

        cout << "In my batch file there is a total of " << numValidPassports
                << " valid passports if we consider cid optional." << endl;

        return 0;
}
