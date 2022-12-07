#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

const int memorySize = 1024;

enum Operation {
        ADD = 1,        /* add */
        MUL,            /* multiply */
        INP,            /* input */
        OUT,            /* output */
        JUT,            /* jump-if-true */
        JUF,            /* jump-if-false */
        LES,            /* less than */
        EQU,            /* equals */
        HAL = 99        /* halt */
};

enum ParameterMode {
        position = 0,
        immediate
};

vector<int> runIntcodeProgram(array<int, memorySize> & memory, const vector<int> input)
{
        vector<int> output;
        auto nextInput = input.begin();
        size_t ip = 0; // instruction pointer
        Operation op = (Operation)(memory[ip] % 100);

        while (op != Operation::HAL) {
                ParameterMode pm1 = (ParameterMode)((memory[ip] / 100) % 10);
                ParameterMode pm2 = (ParameterMode)((memory[ip] / 1000) % 10);
                int numParams = 1;
                int param1;
                int param2;

                if (op == Operation::ADD || op == Operation::MUL || op == Operation::OUT) {
                        if (pm1 == ParameterMode::position) {
                                param1 = memory[memory[ip+1]];
                        } else if (pm1 == ParameterMode::immediate) {
                                param1 = memory[ip+1];
                        }
                        if (pm2 == ParameterMode::position) {
                                param2 = memory[memory[ip+2]];
                        } else if (pm2 == ParameterMode::immediate) {
                                param2 = memory[ip+2];
                        }
                }

                if (op == Operation::ADD || op == Operation::MUL) {
                        numParams = 4;
                } else if (op == Operation::INP || op == Operation::OUT) {
                        numParams = 2;
                }

                if (op == Operation::ADD) {
                        memory[memory[ip + 3]] = param1 + param2;
                } else if (op == Operation::MUL) {
                        memory[memory[ip + 3]] = param1 * param2;
                } else if (op == Operation::INP) {
                        memory[memory[ip + 1]] = *nextInput++;
                } else if (op == Operation::OUT) {
                        output.push_back(param1);
                }

                ip += numParams;
                op = (Operation)(memory[ip] % 100);
        }

        return output;
}

int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        array<int, memorySize> initMemory;
        size_t next = 0, last = 0, i = 0;
        vector<int> inputs, outputs;

        inFile.open(argv[1]);

        getline(inFile, line);
        //getline(inFile, line);

        while (next != string::npos) {
                next = line.find(',', last);
                initMemory[i++] = stoi(line.substr(last, next - last));
                last = next + 1;
        }

        array<int, memorySize> mem(initMemory);
        //for (const auto & m : mem) {
        //        cout << m << endl;
        //}
        //cout << endl;

        inputs.push_back(1);
        outputs = runIntcodeProgram(mem, inputs);
        //for (const auto & m : mem) {
        //        cout << m << endl;
        //}
        //cout << endl;

        for (const auto & output : outputs) {
                cout << output << endl;
        }

FINISHED:

        cout << "After providing 1 to the only input instruction and passing all the tests, "
                << "the diagnostic code the program produces is " << outputs[0] << endl;

        return 0;
}
