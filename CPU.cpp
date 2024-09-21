#include <bits/stdc++.h>
using namespace std;

//-----------------------------------------------------REGISTER-------------------------------------------------------
unordered_map<int, int> Register = 
        {
            {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0},
            {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0},
            {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 0}, {18, 0},
            {19, 0}, {20, 0}, {21, 0}, {22, 0}, {23, 0}, {24, 0},
            {25, 0}, {26, 0}, {27, 0}, {28, 0}, {29, 0}, {30, 0},
            {31, 0},
        };

//---------------------------------------------------------ALU------------------------------------
class ALU
{
    private:
        string operation;
        int operand1;
        int operand2;

    public: 
        ALU(const string &op, const int &op1, const int &op2)
        {   
            operation = op;
            operand1 = op1;
            operand2 = op2;
        }
        int execute()
        {
            if (operation == "ADD")
            {
                return operand1 + operand2;
            }
            else if (operation == "SUB")
            {
                return operand1 - operand2;
            }
            else if (operation == "AND")
            {
                return operand1 & operand2;
            }
            else if (operation == "MUL")
            {
                return operand1 * operand2;
            }
            else if (operation == "XOR")
            {
                return operand1 ^ operand2;
            }
            else if (operation == "OR")
            {
                return operand1 | operand2;
            }
            else if (operation == "SLL")
            {
                return operand1 << operand2;
            }
            else if (operation == "SRL")
            {
                return (unsigned int)operand1 >> operand2;
            }
            else if (operation == "SRA")
            {
                return operand1 >> operand2;
            }
            else if (operation == "SLT")
            {
                return operand1 < operand2 ? 1 : 0;
            }
            else if (operation == "SLTU")
            {
                return (unsigned int)operand1 < (unsigned int)operand2 ? 1 : 0;
            }
            else
            {
                cout << "Unknown operation: " << operation << endl;
                return 0;
            }
        }
};

//---------------------------------------------------------Helper Function: Sign Extend----------------------
int sign_extend(const string &binary, int bits)
{
    int value = stoi(binary, 0, 2);
    if (binary[0] == '1')
    {
        value -= (1 << bits);
    }
    return value;
}

//---------------------------------------------------------CPU----------------------
class CPU 
{
    private:
        string instruction;
        
        unordered_map<string, string> OpcodeToType = 
        {
            {"0110011", "R"}, {"0010011", "I"}, {"0000011", "L"}, {"1100011", "B"},
            {"0100011", "S"}, {"1101111", "J"}, {"1100111", "JL"}, {"0110111", "U"},
            {"0010111", "UI"}
        };

        unordered_map<string, string> Operation = {
            {"R0000000000", "ADD"},
            {"R0000100000", "SUB"},
            {"R1110000000", "AND"},
            {"R1100000000", "OR"},
            {"R1000000000", "XOR"},
            {"R0010000000", "SLL"},
            {"R1010100000", "SRL"},
            {"R0100000000", "STL"},
            {"R0110000000", "SLTU"},
            {"R0000000001", "MUL"},
            {"I000", "ADDI"},
            {"I100", "XORI"},
            {"I110", "ORI"},
            {"I111", "ANDI"},
            {"I0010000000", "SLLI"},
            {"I0100000000", "SLTI"},
            {"I0110000000", "SLTIU"},
            {"I1010100000", "SRLI"},
            {"I1010000000","SRAI"}
        };
        vector<int8_t> memory;

    public:
        CPU(const string &in) : instruction(in), memory(1024, 0) {} 

        void convert() 
        { 
            int n = instruction.size();
            string opcode = instruction.substr(n-7, 7);     
            opcode = OpcodeToType[opcode];
            cout << "OPCODE=====>" << opcode << endl;

            if (opcode == "R")
            {
                string func7, func3, r1, r2, rd;
                func7 = instruction.substr(0, 7);
                func3 = instruction.substr(n - 15, 3);
                string operation = opcode + func3 + func7;
                operation = Operation[operation];
                r1 = instruction.substr(n - 20, 5);
                r2 = instruction.substr(n - 25, 5);
                rd = instruction.substr(n - 12, 5);
                int reg1 = stoi(r1, 0, 2);
                int reg2 = stoi(r2, 0, 2);
                int regd = stoi(rd, 0, 2);
                cout << "operation: " << operation << endl;
                cout << "R1: " << Register[reg1] << " " << "R2: " << Register[reg2] << " " << "Rd: " << regd << endl;
                ALU alu(operation, Register[reg1], Register[reg2]);
                int result = alu.execute();
                Register[regd] = result;
                cout << "Result: " << result << endl;
            }
            
            else if (opcode == "I")
            {
                string func3, r1, rd, imm, func7;
                func7 = instruction.substr(0, 7);
                if (func7 == "0000000" && (instruction.substr(n-15, 3) == "001"||instruction.substr(n-15,3)=="010"||instruction.substr(n-15,3)=="011"||instruction.substr(n-15,3)=="101"))
                {   func3 = instruction.substr(n - 15, 3);
                    string operation = opcode + func3+func7;
                    operation = Operation[operation];
                    r1 = instruction.substr(n - 20, 5); 
                    imm = instruction.substr(7, 5);     
                    rd = instruction.substr(n - 12, 5); 
                    int shamt = stoi(imm, 0, 2);     
                    int reg1 = stoi(r1, 0, 2);   
                    int regd = stoi(rd, 0, 2);    
                    if(func3=="011")
                    {
                        auto it = operation.end();
                        it--;
                        it--;
                        operation.erase(it);
                    }
                    else
                    {
                        operation.pop_back();    
                    }

                    cout << "Shamt: " << shamt << " R1: " << reg1 << " Rd: " << regd << " Operation: " << operation << endl;
                    ALU alu(operation, Register[reg1], shamt);
                    Register[regd] = alu.execute();
                    cout << "Result: " << Register[regd] << endl;
                }
                else
                {
                   
                    func3 = instruction.substr(n - 15, 3);
                    string operation = opcode + func3;
                    operation = Operation[operation];
                    r1 = instruction.substr(n - 20, 5);
                    imm = instruction.substr(0, 12);  
                    rd = instruction.substr(n - 12, 5);
                    operation.pop_back();
                    int immediate = sign_extend(imm, 12);  
                    int reg1 = stoi(r1, 0, 2);
                    int regd = stoi(rd, 0, 2);
                    cout << "Imm: " << immediate << " R1: " << reg1 << " Rd: " << regd << " Operation: " << operation << endl;
                    ALU alu(operation, Register[reg1], immediate);
                    Register[regd] = alu.execute();

                    cout << "Result: " << Register[regd] << endl;
                }
            }

        }
};  

//---------------------------------------------------------Main----------------------
int main()
{
    /*
    CPU cp2 = CPU("11111111010000010000000100010011");  
    cp2.convert();
    CPU cp1 = CPU("00000000101000001000000010010011"); 
    cp1.convert();
    CPU cp = CPU("00000000001000001000000010110011");
    cp.convert();
    */
   CPU cp1 = CPU("00000000000100001000000010010011");
   cp1.convert();
   CPU cp = CPU("00000000000100001001000010010011");
   cp.convert();
   CPU cp2 = CPU("00000000010100001011000010010011");
   cp2.convert();
   
}
