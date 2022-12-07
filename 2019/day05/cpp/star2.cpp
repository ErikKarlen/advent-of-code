#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

const int memorySize = 1024;

enum Operation {
        ADD = 1,        /* add */
        MUL = 2,        /* multiply */
        INP = 3,        /* input */
        OUT = 4,        /* output */
        JUT = 5,        /* jump-if-true */
        JUF = 6,        /* jump-if-false */
        LES = 7,        /* less than */
        EQU = 8,        /* equals */
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
                //cout << "ip: " << ip << endl;
                //for (int i = 0; i < memory.size(); ++i) {
                //        cout << i << ": " << memory[i] << endl;
                //}
                //cout << endl;
                int ipNext = ip + 1;
                ParameterMode pm1 = (ParameterMode)((memory[ip] / 100) % 10);
                ParameterMode pm2 = (ParameterMode)((memory[ip] / 1000) % 10);
                int param1;
                int param2;
                //int & param3 = memory[memory[ip + 3]];

                if (op == Operation::ADD || op == Operation::MUL || op == Operation::OUT
                || op == Operation::LES || op == Operation::EQU || op == Operation::JUT
                || op == Operation::JUF) {
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

                if (op == Operation::INP || op == Operation::OUT || op == Operation::INP || op == Operation::OUT) {
                        ipNext = ip + 2;
                } else if (op == Operation::JUT || op == Operation::JUF) {
                        ipNext = ip + 3;
                } else if (op == Operation::ADD || op == Operation::MUL || op == Operation::LES || op == Operation::EQU) {
                        ipNext = ip + 4;
                }

                if (op == Operation::ADD) {
                        memory[memory[ip + 3]] = param1 + param2;
                } else if (op == Operation::MUL) {
                        memory[memory[ip + 3]] = param1 * param2;
                } else if (op == Operation::INP) {
                        memory[memory[ip + 1]] = *nextInput++;
                } else if (op == Operation::OUT) {
                        output.push_back(param1);
                } else if (op == Operation::JUT) {
                        ipNext = param1 ? param2 : ipNext;
                } else if (op == Operation::JUF) {
                        ipNext = param1 == 0 ? param2 : ipNext;
                } else if (op == Operation::LES) {
                        memory[memory[ip + 3]] = param1 < param2 ? 1 : 0;
                } else if (op == Operation::EQU) {
                        memory[memory[ip + 3]] = param1 == param2 ? 1 : 0;
                }

                ip = ipNext;
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
        //getline(inFile, line);
        //getline(inFile, line);
        //getline(inFile, line);
        //getline(inFile, line);
        //getline(inFile, line);
        //getline(inFile, line);
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

        inputs.push_back(5);
        outputs = runIntcodeProgram(mem, inputs);
        //for (const auto & m : mem) {
        //        cout << m << endl;
        //}
        //cout << endl;

        for (const auto & output : outputs) {
                cout << output << endl;
        }

        cout << "The diagnostic code for system ID 5 is " << outputs[0] << "." << endl;

        return 0;
}
