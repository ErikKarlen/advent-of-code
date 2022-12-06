#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        string topOfStacks;
        map<int, deque<char>> stacks;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                if (line.find('1') != string::npos) {
                        break;
                }
                size_t next = line.find(']');
                int index = next / 4 + 1;
                while (next != string::npos) {
                        //cout << index << endl;
                        stacks[index].push_back(line[next - 1]);
                        next = line.find(']', next + 1);
                        index = next / 4 + 1;
                }
        }

        getline(inFile, line);

        while (getline(inFile, line)) {
                size_t last = 5;
                size_t next = line.find(" ", last);
                int numBoxes = stoi(line.substr(last, next - last));
                last = next + 5;
                next = line.find(" ", last + 1);
                int fromBox = stoi(line.substr(last, next - last));
                int toBox = stoi(line.substr(next + 3));
                //cout << "move " << numBoxes << " from " << fromBox << " to " << toBox<< endl;
                deque<char> stack;
                for (int i = 0; i < numBoxes; ++i) {
                        stack.push_back(stacks[fromBox].front());
                        stacks[fromBox].pop_front();
                }
                for (int i = 0; i < numBoxes; ++i) {
                        stacks[toBox].push_front(stack.back());
                        stack.pop_back();
                }
        }

        for (const auto & pair : stacks) {
                deque<char> stack = pair.second;
                topOfStacks.push_back(stack.front());
                //cout << pair.first << ": (" << stack.size() << ") [";
                //while (!stack.empty()) {
                //        cout << stack.front() << " ";
                //        stack.pop_front();
                //}
                //cout << "]" << endl;
        }
        
        cout << "After the rearrangement procedure completes, the following "
                << "crate ends up on top of each stack: " << topOfStacks << endl;

        return 0;
}
