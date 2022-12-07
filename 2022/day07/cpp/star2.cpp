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
        long long minDirSize = 70000000;
        map<string, long long> fileSizes;
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
                long long fileSize = 0;
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
        }

        //for (const auto & filePair : fileTree) {
        //        cout << filePair.first << ": [ ";
        //        for (const auto & file : filePair.second) {
        //                cout << file << " ";
        //        }
        //        cout << "]" << endl;
        //}

        //for (const auto & filePair : fileSizes) {
        //        //cout << filePair.first << ": " << fileSizes["/"] - filePair.second - 30000000 << endl;
        //        if (70000000 - fileSizes["/"] + filePair.second >= 30000000 && filePair.second < minDirSize) {
        //                //cout << filePair.first << ": " << filePair.second << endl;
        //                minDirSize = filePair.second;
        //        }
        //}

        cout << "The total size of the smallest directory that, if deleted, would free up "
                << "enough space on the filesystem to run the update is "
                << minDirSize << "." << endl;

        return 0;
}
