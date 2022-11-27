#include <bitset>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>


/*
 * Constants defined by the MD5 algorithm
 */
//#define A 0x67452301
//#define B 0xefcdab89
//#define C 0x98badcfe
//#define D 0x10325476

static uint32_t S[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                       5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                       4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                       6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static uint32_t K[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                       0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                       0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                       0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                       0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                       0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                       0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                       0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                       0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                       0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                       0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                       0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                       0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                       0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                       0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                       0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

/*
 * Bit-manipulation functions defined by the MD5 algorithm
 */
#define F(X, Y, Z) ((X & Y) | (~X & Z))
#define G(X, Y, Z) ((X & Z) | (Y & ~Z))
#define H(X, Y, Z) (X ^ Y ^ Z)
#define I(X, Y, Z) (Y ^ (X | ~Z))


using namespace std;


void printHex(const vector<unsigned char> & code)
{
        for (int i = 0; i < code.size(); ++i) {
                if (i % 16 == 0) {
                        cout << endl << "0x";
                }
                cout << " " << hex << setfill('0') << setw(2) << right << +code[i];
        }
        cout << dec << endl;
}


unsigned int rotateLeft(uint32_t x, uint32_t n){
	return (x << n) | (x >> (32 - n));
}


string calculateMD5(const string & message)
{
        unsigned int i;

        //unsigned int s[64] = {
        //        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        //        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        //        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        //        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
        //};

        //unsigned int K[64];
        //for (i = 0; i < 64; ++i) {
        //        K[i] = floor(pow(2, 32) * abs(sin(i + 1)));
        //}
        /* Computes to the following
        unsigned int K[64] = {
                0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
        };
        */

        //unsigned int A = 0x01234567;
        //unsigned int B = 0x89abcdef;
        //unsigned int C = 0xfedcba98;
        //unsigned int D = 0x76543210;

        vector<unsigned char> code;
        for (const auto c : message) {
                code.push_back(c);
        }

        code.push_back(1 << 7);

        unsigned int padding = 56 - code.size() % 64;
        for (i = 0; i < padding; ++i) {
                code.push_back(0);
        }

        unsigned long long messageSize = 8 * message.size();
        //messageSize = 0x1234567890abcdef;
        while (messageSize > 0) {
                code.push_back((unsigned char)messageSize);
                messageSize >>= 8;
        }

        padding = 64 - code.size() % 64;
        for (i = 0; i < padding; ++i) {
                code.push_back(0);
        }


        unsigned int AA;
        unsigned int BB;
        unsigned int CC;
        unsigned int DD;


        for (i = 0; i < 64; ++i) {
                unsigned int E;
                unsigned int j;
                if (0 <= i && i <= 15) {
                        E = F(BB, CC, DD);
                        j = i;
                } else if (16 <= i && i <= 31) {
                        E = G(BB, CC, DD);
                        j = ((i * 5) + 1) % 16;
                } else if (32 <= i <= 47) {
                        E = H(BB, CC, DD);
                        j = ((i * 3) + 5) % 16;
                } else {
                        E = I(BB, CC, DD);
                        j = (i * 7) % 16;
                }

                unsigned int temp = DD;
                DD = CC;
                CC = BB;
                BB = BB + rotateLeft(AA + E + K[i] + input[j], S[i])
                AA = temp;
        }

        A += AA;

        printHex(code);


        return message;
}


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        string digest;

        inFile.open(argv[1]);

        getline(inFile, line);
        getline(inFile, line);
        getline(inFile, line);

        digest = calculateMD5(line);

        cout << "The MD5 hash which, in hexadecimal, starts with at least five zeroes is "
                << digest << "." << endl;

        return 0;
}
