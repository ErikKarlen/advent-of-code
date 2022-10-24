#include <array>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

const int memorySize = 512;

int runIntcodeProgram(array<int, memorySize> memory)
{
        for (size_t i = 0; i < memorySize; i += 4) {
                if (memory[i] == 99) {
                        break;
                } else if (memory[i] == 1) {
                        memory[memory[i+3]] = memory[memory[i+1]] + memory[memory[i+2]];
                } else if (memory[i] == 2) {
                        memory[memory[i+3]] = memory[memory[i+1]] * memory[memory[i+2]];
                }
        }

        return memory[0];
}

int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        array<int, memorySize> initMemory;
        size_t next = 0, last = 0, i = 0;
        int noun, verb;

        inFile.open(argv[1]);

        getline(inFile, line);

        while (next != string::npos) {
                next = line.find(',', last);
                initMemory[i++] = stoi(line.substr(last, next - last));
                last = next + 1;
        }

        for (noun = 0; noun < 100; ++noun) {
                for (verb = 0; verb < 100; ++verb) {
                        auto mem = initMemory;
                        mem[1] = noun;
                        mem[2] = verb;
                        int output = runIntcodeProgram(mem);
                        if (output == 19690720) {
                                goto FINISHED;
                        }
                }
        }

FINISHED:

        cout << "Finding the input noun and verb needed to produce the output "
                "results in 100 * noun + verb equals to " 
                << 100 * noun + verb << "." << endl;

        return 0;
}
