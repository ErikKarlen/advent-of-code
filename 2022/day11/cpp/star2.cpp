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
        deque<long long> items;
        function<long long(long long)> operation;
        function<int(long long)> test;
        long long inspectCounter = 0;
        long long divisor;

        long long inspectFirstItem()
        {
                long long worryLevel = items.front();
                items.pop_front();
                worryLevel = operation(worryLevel);
                inspectCounter++;
                return worryLevel;
        }
        int nextMonkey(long long worryLevel)
        {
                return test(worryLevel);
        }
};

bool operator<(const Monkey &m1, const Monkey &m2)
{
        return m1.inspectCounter < m2.inspectCounter;
}

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        long long monkeyBusiness = 0;
        vector<Monkey> monkeys;
        long long testDivisor = 1;
        int trueMonkey = 1;

        inFile.open(argv[1]);

        Monkey monkey;
        while (getline(inFile, line))
        {
                //cout << line << endl;
                if (line.find("Monkey") != string::npos)
                {
                        monkey = Monkey();
                }
                else if (line.find("Starting items") != string::npos)
                {
                        size_t last = 18;
                        size_t next = line.find(',', last + 1);
                        long long worryLevel;
                        while (next != string::npos)
                        {
                                worryLevel = stoi(line.substr(last, next - last));
                                monkey.items.push_back(worryLevel);
                                last = next + 1;
                                next = line.find(',', last + 1);
                        }
                        worryLevel = stoi(line.substr(last, next - last));
                        monkey.items.push_back(worryLevel);
                }
                else if (line.find("Operation") != string::npos)
                {
                        if (line.substr(line.size() - 5) == "* old")
                        {
                                monkey.operation = [](long long old)
                                { return old * old; };
                        }
                        else if (line.substr(line.size() - 5) == "+ old")
                        {
                                monkey.operation = [](long long old)
                                { return old + old; };
                        }
                        else if (line[23] == '+')
                        {
                                long long num = stoi(line.substr(25));
                                monkey.operation = [num](long long old)
                                { return old + num; };
                        }
                        else if (line[23] == '*')
                        {
                                long long num = stoi(line.substr(25));
                                monkey.operation = [num](long long old)
                                { return old * num; };
                        }
                }
                else if (line.find("Test") != string::npos)
                {
                        monkey.divisor = stoi(line.substr(21));
                        testDivisor *= monkey.divisor;
                }
                else if (line.find("If true") != string::npos)
                {
                        trueMonkey = stoi(line.substr(29));
                }
                else if (line.find("If false") != string::npos)
                {
                        int falseMonkey = stoi(line.substr(30));
                        long long div = monkey.divisor;
                        monkey.test = [div, trueMonkey, falseMonkey](long long worryLevel)
                        {
                                return worryLevel % div == 0 ? trueMonkey : falseMonkey;
                        };
                }
                else
                {
                        monkeys.push_back(monkey);
                }
        }
        monkeys.push_back(monkey);

        for (int round = 0; round < 10000; ++round)
        {
                for (auto & m : monkeys)
                {
                        int numItems = m.items.size();
                        for (int item = 0; item < numItems; ++item)
                        {
                                long long worryLevel = m.inspectFirstItem() % testDivisor;
                                //cout << worryLevel << endl;
                                int newMonkey = m.nextMonkey(worryLevel);
                                monkeys[newMonkey].items.push_back(worryLevel);
                        }
                }
        }
        sort(monkeys.begin(), monkeys.end());

        //for (const auto &m : monkeys)
        //{
        //        cout << m.inspectCounter << endl;
        //}

        monkeyBusiness = (*(monkeys.end() - 1)).inspectCounter * (*(monkeys.end() - 2)).inspectCounter;

        cout << "The level of monkey business after 10000 rounds "
             << "is " << monkeyBusiness << "." << endl;

        return 0;
}
