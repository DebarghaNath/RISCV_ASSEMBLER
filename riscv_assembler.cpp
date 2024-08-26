#include <bits/stdc++.h>
using namespace std;

unordered_map<string, tuple<string, string, string>> instruction = 
{
    {"ADD", {"R", "000", "0000000"}},
    {"SUB", {"R", "000", "0100000"}},
    {"AND", {"R", "111", "0000000"}},
    {"OR", {"R", "110", "0000000"}},
    {"XOR", {"R", "100", "0000000"}},
    {"SLL", {"R", "001", "0000000"}},
    {"SRL", {"R", "101", "0000000"}},
    {"SRA", {"R", "101", "0100000"}},
    {"STL", {"R", "010", "0000000"}},
    {"SLTU", {"R", "011", "0000000"}},
    {"ADDI", {"I", "000", "0000000"}},
    {"ANDI", {"I", "111", "0000000"}},
    {"JAL", {"J", "", ""}},
};

unordered_map<string, string> type = 
{
    {"R", "0110011"},
    {"I", "0010011"},
    {"J", "1101111"} 
};

string regToBinary(const string& reg)
{
    int regNum = stoi(reg.substr(1));
    return bitset<5>(regNum).to_string();
}

string ImmToBinary(const string& imm)
{
    int num = stoi(imm);
    return bitset<12>(num).to_string();
}

string ImmToBinaryJ(const string& imm)
{
    int num = stoi(imm);
    return bitset<20>(num).to_string();
}

string convert(string& line)
{
    istringstream iss(line);
    string opcode;
    iss >> opcode;

    if (instruction.find(opcode) == instruction.end()) {
        cerr << "Unsupported instruction: " << opcode << endl;
        return "";
    }

    auto [t, funct3, funct7] = instruction[opcode];
    
    if (t == "R")
    {
        string rd, r1, r2;
        iss >> rd >> r1 >> r2;
        string rdBinary = regToBinary(rd);
        string r1Binary = regToBinary(r1);
        string r2Binary = regToBinary(r2);
        string binaryInstruction = funct7 + r2Binary + r1Binary + funct3 + rdBinary + type[t];
        return binaryInstruction;
    }
    else if (t == "I")
    {
        string rd, r1, imm;
        iss >> rd >> r1 >> imm;
        string rdBinary = regToBinary(rd);
        string r1Binary = regToBinary(r1);
        string immBinary = ImmToBinary(imm);
        string binaryInstruction = immBinary + r1Binary + funct3 + rdBinary + type[t];
        return binaryInstruction;
    }
    else if (t == "J")
    {
        string rd, imm;
        iss >> rd >> imm;
        string rdBinary = regToBinary(rd);
        string immBinary = ImmToBinaryJ(imm);
        string binaryInstruction = immBinary + rdBinary + type[t];
        return binaryInstruction;
    }

    return "";
}

void writeBinaryToFile(const string& binaryString, ofstream& binaryFile)
{
    if (binaryString.size() != 32) {
        cerr << "Error: Binary string length is not 32 bits" << endl;
        return;
    }

    uint32_t value = bitset<32>(binaryString).to_ulong();
    binaryFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

int main()
{
    ifstream riscvfile("input.s");
    ofstream binaryfile("output.bin", ios::binary);
    string input;
    while (getline(riscvfile, input))
    {
        string value = convert(input);
        if (!value.empty()) {
            writeBinaryToFile(value, binaryfile);
        }
    }
    return 0;
}
