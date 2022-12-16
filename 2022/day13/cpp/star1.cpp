#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


using namespace std;


struct Packet
{
        int intValue{-1};
        vector<shared_ptr<Packet>> packets;
};

int comparePackets(const shared_ptr<Packet> left, const shared_ptr<Packet> right)
{
        if (left->intValue >= 0 && right->intValue >= 0) {
                return right->intValue - left->intValue;
        } else if (left->intValue < 0 && right->intValue < 0) {
                for (int i = 0; i < left->packets.size() && i < right->packets.size(); ++i) {
                        int compareResult = comparePackets(left->packets[i], right->packets[i]);
                        if (compareResult != 0) {
                                return compareResult;
                        }
                }
                return right->packets.size() - left->packets.size();
        } else if (left->intValue >= 0 && right->intValue < 0) {
                shared_ptr<Packet> leftList = make_shared<Packet>();
                leftList->packets.push_back(left);
                return comparePackets(leftList, right);
        } else if (left->intValue < 0 && right->intValue >= 0) {
                shared_ptr<Packet> rightList = make_shared<Packet>();
                rightList->packets.push_back(right);
                return comparePackets(left, rightList);
        }

        return 0;
}

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int orderedIndicesSum = 0;
        vector<shared_ptr<Packet>> allPackets;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                if (line == "") {
                        //break;
                        //if (isOrdered(*(allPackets.end() - 2), *(allPackets.end() - 1))) {
                        //        numOrderedPacketPairs++;
                        //}
                        continue;
                }

                deque<shared_ptr<Packet>> stack;
                shared_ptr<Packet> rootPacket = make_shared<Packet>();
                stack.push_front(rootPacket);
                size_t last = 1;
                size_t next = line.find_first_of("[],", last);
                while (next != string::npos) {
                        auto top = stack.front();
                        if (line[next] == '[') {
                                auto newPacket = make_shared<Packet>();
                                top->packets.push_back(newPacket);
                                stack.push_front(newPacket);
                        } else if (line[next] == ',') {
                                if (last - next > 0) {
                                        auto newPacket = make_shared<Packet>();
                                        newPacket->intValue = stoi(line.substr(last, next - last));
                                        top->packets.push_back(newPacket);
                                }
                        } else if (line[next] == ']') {
                                if (last - next > 0) {
                                        auto newPacket = make_shared<Packet>();
                                        newPacket->intValue = stoi(line.substr(last, next - last));
                                        top->packets.push_back(newPacket);
                                }
                                stack.pop_front();
                        }
                        last = next + 1;
                        next = line.find_first_of("[],", last);
                }
                allPackets.push_back(rootPacket);
        }

        for (int i = 0; i < allPackets.size(); i += 2) {
                int index = i / 2 + 1;
                int compareResult = comparePackets(allPackets[i], allPackets[i + 1]);
                //cout << index << ": " << compareResult << endl;
                if (compareResult > 0) {
                        orderedIndicesSum += index;
                }
        }

        //for (const auto & p0 : allPackets) {
        //        //cout << p0->packets.size() << endl;
        //        for (const auto & p1 : p0->packets) {
        //                cout << p1->intValue << endl;
        //        //        for (const auto & p2 : p1->packets) {
        //        //                cout << p2->intValue << endl;
        //        //        }
        //        }
        //}

        cout << "The sum of the indices of the paris of packets that are already "
                << "in the right order is " << orderedIndicesSum<< "." << endl;

        return 0;
}
