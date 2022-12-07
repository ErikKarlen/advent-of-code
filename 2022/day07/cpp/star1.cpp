#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <set>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int smallDirSizeSum = 0;
        map<string, int> fileSizes;
        map<string, set<string>> fileTree;
        string currentDir;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                if (line.substr(0, 7) == "$ cd ..") {
                        for (const auto & pair : fileTree) {
                                if (pair.second.count(currentDir)) {
                                        currentDir = pair.first;
                                        break;
                                }
                        }
                } else if (line.substr(0, 6) == "$ cd /") {
                        currentDir = "/";
                } else if (line.substr(0, 4) == "$ cd") {
                        currentDir = currentDir + line.substr(5) + "/";
                } else if (line.substr(0, 4) != "$ ls") {
                        int spacePos = line.find(' ');
                        string fileInfo = line.substr(0, spacePos);
                        string name = currentDir + line.substr(spacePos + 1);
                        if (fileInfo.find_first_of("0123456789") != string::npos) {
                                fileSizes[name] = stoi(fileInfo);
                        } else {
                                name += "/";
                        }
                        fileTree[currentDir].insert(name);
                }
        }

        for (const auto & filePair : fileTree) {
                int fileSize = 0;
                deque<string> toCheck(filePair.second.begin(), filePair.second.end());
                set<string> checkedFiles;
                while (!toCheck.empty()) {
                        string file = toCheck.front();
                        toCheck.pop_front();
                        checkedFiles.insert(file);
                        if (fileSizes.count(file)) {
                                fileSize += fileSizes[file];
                        } else if (fileTree.count(file)) {
                                for (const auto & f : fileTree[file]) {
                                        if (!checkedFiles.count(f)) {
                                                toCheck.push_back(f);
                                        }
                                }
                        }
                }
                fileSizes[filePair.first] = fileSize;
                if (fileSize <= 100000) {
                        smallDirSizeSum += fileSize;
                }
        }

        //for (const auto & filePair : fileTree) {
        //        cout << filePair.first << ": [ ";
        //        for (const auto & file : filePair.second) {
        //                cout << file << " ";
        //        }
        //        cout << "]" << endl;
        //}

        //for (const auto & filePair : fileSizes) {
        //        cout << filePair.first << ": " << filePair.second << endl;
        //}

        cout << "For all of the directories with a total size of at most 100000, the sum "
                << "of the total sizes of those directories is " << smallDirSizeSum << endl;

        return 0;
}
