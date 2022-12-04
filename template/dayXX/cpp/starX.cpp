#include <iostream>
#include <fstream>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        int answer = 0;
        ifstream inFile;

        inFile.open(argv[1]);

        cout << "Answer is: " << answer << endl;

        return 0;
}
