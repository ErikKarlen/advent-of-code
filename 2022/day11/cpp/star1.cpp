#include <algorithm>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Monkey
{
public:
        deque<int> items;
        function<int(int)> operation;
        function<int(int)> test;
        int inspectCounter = 0;

        int inspectFirstItem()
        {
                int worryLevel = items.front();
                items.pop_front();
                worryLevel = operation(worryLevel) / 3;
                inspectCounter++;
                return worryLevel;
        }
        int nextMonkey(int worryLevel)
        {
                return test(worryLevel);
        }

};

bool operator<(const Monkey& m1, const Monkey& m2)
{
        return m1.inspectCounter < m2.inspectCounter;
}

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int monkeyBusiness = 0;
        vector<Monkey> monkeys;
        int testDivisor = 1;
        int trueMonkey = 1;

        inFile.open(argv[1]);

        Monkey monkey;
        while (getline(inFile, line)) {
                //cout << line << endl;
                if (line.find("Monkey") != string::npos) {
                        monkey = Monkey();
                } else if (line.find("Starting items") != string::npos) {
                        size_t last = 18;
                        size_t next = line.find(',', last + 1);
                        int worryLevel;
                        while (next != string::npos) {
                                worryLevel = stoi(line.substr(last, next - last));
                                monkey.items.push_back(worryLevel);
                                last = next + 1;
                                next = line.find(',', last + 1);
                        }
                        worryLevel = stoi(line.substr(last, next - last));
                        monkey.items.push_back(worryLevel);
                } else if (line.find("Operation") != string::npos) {
                        if (line.substr(line.size() - 5) == "* old") {
                                monkey.operation = [](int old) { return old * old; };
                        } else if (line.substr(line.size() - 5) == "+ old") {
                                monkey.operation = [](int old) { return old + old; };
                        } else if (line[23] == '+') {
                                int num = stoi(line.substr(25));
                                monkey.operation = [num](int old) { return old + num; };
                        } else if (line[23] == '*') {
                                int num = stoi(line.substr(25));
                                monkey.operation = [num](int old) { return old * num; };
                        }
                } else if (line.find("Test") != string::npos) {
                        testDivisor = stoi(line.substr(21));
                } else if (line.find("If true") != string::npos) {
                        trueMonkey = stoi(line.substr(29));
                } else if (line.find("If false") != string::npos) {
                        int falseMonkey = stoi(line.substr(30));
                        monkey.test = [testDivisor, trueMonkey, falseMonkey](int worryLevel)
                        {
                                return worryLevel % testDivisor == 0 ? trueMonkey : falseMonkey;
                        };
                } else {
                        monkeys.push_back(monkey);
                }
        }
        monkeys.push_back(monkey);

        for (int round = 0; round < 20; ++round) {
                for (auto & m : monkeys) {
                        int numItems = m.items.size();
                        for (int item = 0; item < numItems; ++item) {
                                int worryLevel = m.inspectFirstItem();
                                int newMonkey = m.nextMonkey(worryLevel);
                                monkeys[newMonkey].items.push_back(worryLevel);
                        }
                }
        }
        sort(monkeys.begin(), monkeys.end());

        //for (const auto & m : monkeys) {
        //        cout << m.inspectCounter << endl;
        //}

        monkeyBusiness = (*(monkeys.end() - 1)).inspectCounter * (*(monkeys.end() - 2)).inspectCounter;

        cout << "The level of monkey business after 20 rounds of stuff-slinging "
                << "simian shenanigans is " << monkeyBusiness << "." << endl;

        return 0;
}
