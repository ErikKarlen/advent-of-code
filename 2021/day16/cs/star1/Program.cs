using System;
using System.Text;


abstract class Packet
{
        public int version;
        public int type;
}


class Literal : Packet
{
        public int val;

        public Literal(int version, int type, int val)
        {
                this.version = version;
                this.type = type;
                this.val = val;
        }
}


class Operator : Packet
{
        public List<Packet> subPackets;

        public Operator(int version, int type)
        {
                this.version = version;
                this.type = type;
                subPackets = new List<Packet>();
        }

        public void addSubPacket(Packet packet)
        {
                subPackets.Add(packet);
        }
}


class PacketDecoder
{

        private string binaryPacket;
        private int binIndex;
        private List<Packet> packets;
        private int lastLiteralSize;

        public int versionSum;

        public const int versionSize = 3;
        public const int typeSize = 3;

        public PacketDecoder(string hexPacket)
        {
                binaryPacket = hexToBin(hexPacket);
                binIndex = 0;
                packets = new List<Packet>();
                lastLiteralSize = 0;

                versionSum = 0;
        }

				public string hexToBin(string hexString)
				{
								Dictionary<char, string> hexToBinDict = new Dictionary<char, string> {
										{ '0', "0000" },
										{ '1', "0001" },
										{ '2', "0010" },
										{ '3', "0011" },
										{ '4', "0100" },
										{ '5', "0101" },
										{ '6', "0110" },
										{ '7', "0111" },
										{ '8', "1000" },
										{ '9', "1001" },
										{ 'A', "1010" },
										{ 'B', "1011" },
										{ 'C', "1100" },
										{ 'D', "1101" },
										{ 'E', "1110" },
										{ 'F', "1111" }
								};

                StringBuilder sb = new StringBuilder();

                foreach (char c in hexString) {
                        sb.Append(hexToBinDict[c]);
                }
								return sb.ToString();
				}

        private int readBinary(int numberOfDigits)
        {
                binIndex += numberOfDigits;
                return Convert.ToInt32(binaryPacket.Substring(binIndex - numberOfDigits, numberOfDigits), 2);
        }

        private int readVersion()
        {
                return readBinary(versionSize);
        }

        private int readType()
        {
                return readBinary(typeSize);
        }

        private int readLiteral()
        {
                lastLiteralSize = 6;
                int val = 0;
                bool finished = false;
                while (!finished) {
                        if (readBinary(1) == 0) {
                                finished = true;
                        }
                        val = val * 16 + readBinary(4);
                        lastLiteralSize += 5;
                }
                return val;
        } 

        private int readOperator()
        {
                int lengthType = readBinary(1);
                int length = 0;
                int bitsRead = versionSize + typeSize + 1;

                if (lengthType == 0) {
                        length = readBinary(15);
                        bitsRead += 15;
                        int newBitsRead = 0;
                        while (newBitsRead < length) {
                                newBitsRead += readNext();
                                bitsRead += newBitsRead;
                        }
                } else {
                        length = readBinary(11);
                        bitsRead += 11;
                        for (int i = 0; i < length; ++i) {
                                bitsRead += readNext();
                        }
                }

                return bitsRead;
        }

        private int readNext()
        {
                int startIndex = binIndex;
								int version = readVersion();
                versionSum += version;
								int type = readType();

                if (type == 4) {
                        int literalValue = readLiteral();
                } else {
                        readOperator();
                }

                return binIndex - startIndex;
        }

        public int decode()
        {
                return readNext();
        }

}

class Star1
{
        public static int Main(string[] args)
        {
                string hexInput = System.IO.File.ReadAllText(args[0]).Trim();

                PacketDecoder pd = new PacketDecoder(hexInput);

                pd.decode();

                Console.WriteLine(pd.versionSum);

                return 0;
        }
}
