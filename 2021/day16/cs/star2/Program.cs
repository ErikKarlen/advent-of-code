using System;
using System.Text;


class Packet
{
        public int version;
        public int type;
        public ulong val;
        public List<Packet> subPackets;

        public Packet(int version, int type)
        {
                this.version = version;
                this.type = type;
                this.val = 0;
                subPackets = new List<Packet>();
        }
}


class PacketDecoder
{

        private string binaryPacket;
        private int binIndex;
        private Packet rootPacket;
        private int lastLiteralSize;

        public int versionSum;

        public const int versionSize = 3;
        public const int typeSize = 3;

        public PacketDecoder(string hexPacket)
        {
                binaryPacket = hexToBin(hexPacket);
                binIndex = 0;
                rootPacket = new Packet(0, -1);
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

        private ulong readBinary(int numberOfDigits)
        {
                binIndex += numberOfDigits;
                return Convert.ToUInt64(binaryPacket.Substring(binIndex - numberOfDigits, numberOfDigits), 2);
        }

        private int readVersion()
        {
                return (int)readBinary(versionSize);
        }

        private int readType()
        {
                return (int)readBinary(typeSize);
        }

        private ulong readLiteral()
        {
                lastLiteralSize = 6;
                ulong val = 0;
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

        private int readOperator(Packet parent)
        {
                int lengthType = (int)readBinary(1);
                int length = 0;
                int bitsRead = versionSize + typeSize + 1;

                if (lengthType == 0) {
                        length = (int)readBinary(15);
                        bitsRead += 15;
                        int newBitsRead = 0;
                        while (newBitsRead < length) {
                                newBitsRead += readNext(parent);
                                bitsRead += newBitsRead;
                        }
                } else {
                        length = (int)readBinary(11);
                        bitsRead += 11;
                        for (int i = 0; i < length; ++i) {
                                bitsRead += readNext(parent);
                        }
                }

                return bitsRead;
        }

        private int readNext(Packet parent)
        {
                int startIndex = binIndex;
                int version = readVersion();
                int type = readType();
                Packet p = new Packet(version, type);

                if (type == 4) {
                        p.val = readLiteral();
                } else {
                        readOperator(p);
                }
                parent.subPackets.Add(p);

                return binIndex - startIndex;
        }

        public int read()
        {
                return readNext(rootPacket);
        }

        public ulong decode(Packet packet)
        {
                ulong val = 0;
                if (packet.type == 4) {
                        val = packet.val;
                } else if (packet.type == 0) {
                        ulong sum = 0;
                        foreach (Packet p in packet.subPackets) {
                                sum += decode(p);
                        }
                        val = sum;
                } else if (packet.type == 1) {
                        ulong product = 1;
                        foreach (Packet p in packet.subPackets) {
                                product *= decode(p);
                        }
                        val = product;
                } else if (packet.type == 2) {
                        ulong minValue = Int32.MaxValue;
                        foreach (Packet p in packet.subPackets) {
                                ulong newVal = decode(p);
                                if (newVal < minValue) {
                                        minValue = newVal;
                                }
                        }
                        val = minValue;
                } else if (packet.type == 3) {
                        ulong maxValue = 0;
                        foreach (Packet p in packet.subPackets) {
                                ulong newVal = decode(p);
                                if (newVal > maxValue) {
                                        maxValue = newVal;
                                }
                        }
                        val = maxValue;
                } else if (packet.type == 5) {
                        val = (ulong) (decode(packet.subPackets[0]) > decode(packet.subPackets[1]) ? 1 : 0);
                } else if (packet.type == 6) {
                        val = (ulong) (decode(packet.subPackets[0]) < decode(packet.subPackets[1]) ? 1 : 0);
                } else if (packet.type == 7) {
                        val = (ulong) (decode(packet.subPackets[0]) == decode(packet.subPackets[1]) ? 1 : 0);
                }
                return val;
        }

        public ulong decode()
        {
                return decode(rootPacket.subPackets[0]);
        }

}

class Star1
{
        public static int Main(string[] args)
        {
                string hexInput = System.IO.File.ReadAllText(args[0]).Trim();

                PacketDecoder pd = new PacketDecoder(hexInput);

                pd.read();

                Console.WriteLine(pd.decode());

                return 0;
        }
}
