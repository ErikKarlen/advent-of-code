#include <algorithm>
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

        friend ostream& operator<<(ostream & out, const Packet & obj); 
};

ostream& operator<<(ostream & out, const Packet & obj)
{
        shared_ptr<Packet> p;

        if (obj.intValue >= 0) {
                out << obj.intValue;
                return out;
        }
        if (obj.packets.size() == 0)  {
                return out;
        }

        out << "[";
        for (int i = 0; i < obj.packets.size() - 1; ++i) {
                p = obj.packets[i];
                out << *p << ",";
        }
        p = obj.packets.back();
        out << *p << "]";
        return out;
}

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

struct lessThanKey
{
    inline bool operator() (const shared_ptr<Packet> & left, const shared_ptr<Packet> & right)
    {
        bool res = comparePackets(left, right) > 0;
        return res;
    }
};

shared_ptr<Packet> createPacket(const string & line)
{
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

        return rootPacket;
}

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int orderedIndicesSum = 0;
        vector<shared_ptr<Packet>> allPackets;
        shared_ptr<Packet> dividerPacket1 = createPacket("[[2]]");
        shared_ptr<Packet> dividerPacket2 = createPacket("[[6]]");
        size_t dividerPacket1Index;
        size_t dividerPacket2Index;
        int decoderKey;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                if (line == "") {
                        continue;
                }

                allPackets.push_back(createPacket(line));
        }

        allPackets.push_back(dividerPacket1);
        allPackets.push_back(dividerPacket2);

        //for (int i = 0; i < allPackets.size(); i += 2) {
        //        int index = i / 2 + 1;
        //        int compareResult = comparePackets(allPackets[i], allPackets[i + 1]);
        //        //cout << index << ": " << compareResult << endl;
        //        if (compareResult > 0) {
        //                orderedIndicesSum += index;
        //        }
        //}

        sort(allPackets.begin(), allPackets.end(), lessThanKey());

        for (dividerPacket1Index = 0; dividerPacket1Index < allPackets.size(); ++dividerPacket1Index) {
                shared_ptr<Packet> p = allPackets[dividerPacket1Index];
                //cout << *p << endl;
                int compareResult = comparePackets(p, dividerPacket1);
                if (compareResult == 0) {
                        dividerPacket1Index++;
                        break;
                }
        }

        for (dividerPacket2Index = dividerPacket1Index; dividerPacket2Index < allPackets.size(); ++dividerPacket2Index) {
                shared_ptr<Packet> p = allPackets[dividerPacket2Index];
                //cout << *p << endl;
                int compareResult = comparePackets(p, dividerPacket2);
                if (compareResult == 0) {
                        dividerPacket2Index++;
                        break;
                }
        }

        decoderKey = dividerPacket1Index * dividerPacket2Index;

        cout << "The decoder key for the distress signal is " << decoderKey
                << "." << endl;

        return 0;
}
