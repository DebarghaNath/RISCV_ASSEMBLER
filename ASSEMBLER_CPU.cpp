/*
    AUTHOR: DEBARGHA NATH
*/
#include <bits/stdc++.h>
using namespace std;

int PC= 0;
//------------------------------------ClassForImmediate----------------------------------
class Immediate
{
    private:
        string imm;
        int val;
    public:
        Immediate(const string &immValue)
        {
            imm = immValue;
            val = stoi(imm);
        }
        string immToBinary()
        {
            int num = stoi(imm);
            return bitset<12>(num).to_string();
        }
        int immToInt()
        {
            return val;
        }
        string immToBinary5()
        {
            int num = stoi(imm);
            return bitset<5>(num).to_string();
        }
        string immRet5()
        {
            string cur = immToBinary();
            string ret = "";
            for(int i=cur.size()-5;i<cur.size();i++)
            {
                ret+= cur[i];
            }
            return ret;
        }
        string immRet7()
        {
            string cur = immToBinary();
            string ret = "";
            for(int i= 0 ;i<cur.size()-5;i++)
            {
                ret+= cur[i];
            }
            return ret;
        }
        string immJ()
        {
            int num = stoi(imm);
            return bitset<20>(num).to_string();
        }
        
};

//--------------------------ClassForRegister-------------------------------------
class Register
{
    private:
        string name;
        int number;
    public:
        Register(const string & reg)
        {
            name = reg;
            number = stoi(name.substr(1));
        }
        string toBinary()
        {
            return bitset<5>(number).to_string();
        }
        int toNumber()
        {
            return number;
        }
        
};

//--------------------------------------ClassForTypeConversionToBinary---------------------------------
class typeInstruction
{
    private:
        string opcode;
        string rs1;
        string rs2;
        string rd;
        string imm;
        string func3;
        string func7;
    public:
        typeInstruction(const string &op,const string &r1,const string &r2,const string &d,const string &i,const string &f3,const string &f7)
        {
            opcode = op;
            rs1 = r1;
            rs2 = r2;
            rd = d;
            imm = i;
            func3 = f3;
            func7 = f7;
        }
        string R_TypeConvert()
        {
            Register rdReg(rd);
            Register r1Reg(rs1);
            Register r2Reg(rs2);
            string BinaryInstruction = func7 + r2Reg.toBinary()+ r1Reg.toBinary()+func3+rdReg.toBinary()+opcode;
            return BinaryInstruction;
        }
        string I_TypeConvert()
        {
            Register rdReg(rd);
            Register r1Reg(rs1);
            Immediate Im(imm);
            string BinaryInstruction = Im.immToBinary()+ r1Reg.toBinary()+func3+rdReg.toBinary()+opcode;
            return BinaryInstruction;
        }
        string IL_TypeConvert()
        {
            Register rdReg(rd);
            Register r1Reg(rs1);
            Immediate Im(imm);
            string BinaryInstruction = func7 + Im.immToBinary5()+ r1Reg.toBinary()+func3+rdReg.toBinary()+opcode;
            return BinaryInstruction;
        }
        string IR_TypeConvert()
        {
            Register rdReg(rd);
            Register r1Reg(rs1);
            Immediate Im(imm);
            string BinaryInstruction = func7 + Im.immToBinary5()+ r1Reg.toBinary()+func3+rdReg.toBinary()+opcode;
            return BinaryInstruction;
        }
        string L_TypeConvert()
        {
            Register rdReg(rd);
            Register r1Reg(rs1);
            Immediate Im(imm);
            string BinaryInstruction = Im.immToBinary()+ r1Reg.toBinary()+func3+rdReg.toBinary()+opcode;
            return BinaryInstruction;
        }
        string B_TypeConvert()
        {
            Register r2Reg(rs2);
            Register r1Reg(rs1);
            Immediate Im(imm);
            string s1 = Im.immRet7();
            string s2 = Im.immRet5();
            string BinaryInstruction = s1 + r2Reg.toBinary()+ r1Reg.toBinary() + func3 + s2 + opcode;
            return BinaryInstruction;
        }
        string S_TypeConvert()
        {
            Register r2Reg(rs2);
            Register r1Reg(rs1);
            Immediate Im(imm);
            string BinaryInstruction = Im.immRet7() + r2Reg.toBinary()+ r1Reg.toBinary()+func3+Im.immRet5()+opcode;
            return BinaryInstruction;
        }
        string J_TypeConvert()
        {
            Register rdReg(rd);
            Immediate Im(imm);
            string s = Im.immJ();
            string BinaryInstruction = s + rdReg.toBinary() + opcode;
            return BinaryInstruction;
        }
        string JL_TypeConvert()
        {
            Register rdReg(rd);
            Register r1Reg(rs1);
            Immediate Im(imm);
            string BinaryInstruction = Im.immToBinary()+r1Reg.toBinary()+func3 + rdReg.toBinary()+opcode;
            return BinaryInstruction;
        }
        
};

//------------------------------------------------ClassForEncodingOfInstruction---------------------------------
class InstructionConvert
{
    private:
    unordered_map<string,tuple<string,string,string>>instruction=
    {
        {"ADD",{"R","000","0000000"}},
        {"SUB",{"R","000","0100000"}},
        {"AND",{"R","111","0000000"}},
        {"OR",{"R","110","0000000"}},
        {"XOR",{"R","100","0000000"}},
        {"SLL",{"R","001","0000000"}},
        {"SRL",{"R","101","0100000"}},
        {"SLT",{"R","010","0000000"}},
        {"SLTU",{"R","011","0000000"}},
        {"MUL",{"R","000","0000001"}},
        {"ADDI",{"I","000",""}},
        {"SLLI",{"IL","001","0000000"}},
        {"SLTI",{"IL","010","0000000"}},
        {"SLTIU",{"IL","011","0000000"}},
        {"XORI",{"I","100",""}},
        {"SRLI",{"IR","101","0000000"}},
        {"SRAI",{"IR","101","0100000"}},
        {"ORI",{"I","110",""}},
        {"ANDI",{"I","111",""}},
        {"LB",{"L","000",""}},
        {"LH",{"L","001",""}},
        {"LW",{"L","010",""}},
        {"LBU",{"L","100",""}},
        {"LHU",{"L","101",""}},
        {"BEQ",{"B","000",""}},
        {"BNE",{"B","001",""}},
        {"BLT",{"B","100",""}},
        {"BGE",{"B","101",""}},
        {"SB",{"S","000",""}},
        {"SH",{"S","001",""}},
        {"SW",{"S","010",""}},
        {"SD",{"s","011",""}},
        {"JAL",{"J","",""}},
        {"JALR",{"JL","000",""}},
        {"LUI",{"U","",""}},
        {"AUIPC",{"UI","",""}}
        
    };
    
    unordered_map<string,string> typeToOpcode = 
    {
        {"R","0110011"},
        {"I","0010011"},
        {"IL","0010011"},
        {"IR","0010011"},
        {"L","0000011"},
        {"B","1100011"},
        {"S","0100011"},
        {"J","1101111"},
        {"JL","1100111"},
        {"U","0110111"},
        {"UI","0010111"}
    };
    public:
    string convert( const string & str)
    {
        stringstream ss(str);
        string opcode;
        ss>>opcode;
        //cout<<opcode<<endl;
        if(instruction.find(opcode) == instruction.end())
        {
            return "Invalid Instruction";
        }
        auto [type, func3, func7] = instruction[opcode];
        
        //cout<<type<<endl;
        if(type == "R")
        {
            string rd,r1,r2;
            ss>>rd>>r1>>r2;
            rd.pop_back();
            r1.pop_back();
            opcode = typeToOpcode[type];
            typeInstruction I_Type(opcode,r1,r2,rd,"",func3,func7);
            return I_Type.R_TypeConvert();
        }
        else if(type == "I")
        {
            string rd,r1,imm;
            ss>>rd>>r1>>imm;
            rd.pop_back();
            r1.pop_back();
            opcode = typeToOpcode[type];
            typeInstruction I_Type(opcode,r1,"",rd,imm,func3,func7);
            return I_Type.I_TypeConvert();
        }
        else if(type == "IR")
        {
            string rd,r1,imm;
            ss>>rd>>r1>>imm;
            rd.pop_back();
            r1.pop_back();
            opcode = typeToOpcode[type];
            typeInstruction I_Type(opcode,r1,"",rd,imm,func3,func7);
            return I_Type.IR_TypeConvert();
        }
        else if(type == "IL")
        {
            string rd,r1,imm;
            ss>>rd>>r1>>imm;
            rd.pop_back();
            r1.pop_back();
            opcode = typeToOpcode[type];
            typeInstruction I_Type(opcode,r1,"",rd,imm,func3,func7);
            return I_Type.IL_TypeConvert();
        }
        else if(type == "L")
        {
            string rd,comb,imm,rs1;
            ss>>rd>>comb;
            rs1 = "";
            imm = "";
            for(int i=0;i<comb.size()-1;i++)
            {
                if(comb[i]=='[')
                {
                    i++;
                    for(;i<comb.size()-1;i++)
                    {
                        rs1+=comb[i];
                    }
                    break;
                }
                else
                {
                    imm+=comb[i];
                }
            }
            
            rd.pop_back();
            opcode = typeToOpcode[type];
            //cout<<comb<<endl;
            //cout<<rd<<" "<<imm<<" "<<rs1<<endl;
            typeInstruction I_Type(opcode,rs1,"",rd,imm,func3,"");
            return I_Type.L_TypeConvert();
        }
        else if(type == "B")
        {
            string r1,r2,imm;
            ss>>r1>>r2>>imm;
            r1.pop_back();
            r2.pop_back();
            opcode = typeToOpcode[type];
            typeInstruction I_Type(opcode,r1,r2,"",imm,func3,"");
            return I_Type.B_TypeConvert();
        }
        else if(type == "S")
        {
            string r2,comb,imm,r1;
            ss>>r2>>comb;
            r1 = "";
            imm = "";
            for(int i=0;i<comb.size()-1;i++)
            {
                if(comb[i]=='[')
                {
                    i++;
                    for(;i<comb.size()-1;i++)
                    {
                        r1+=comb[i];
                    }
                    break;
                }
                else
                {
                    imm+=comb[i];
                }
            }
            r2.pop_back();
            opcode = typeToOpcode[type];
            //cout<<r2<<" "<<imm<<" "<<r1<<endl;
            typeInstruction I_Type(opcode,r1,r2,"",imm,func3,"");
            return I_Type.S_TypeConvert();
        }
        else if(type=="J")
        {
            string rd,imm;
            ss>>rd>>imm;
            rd.pop_back();
            opcode = typeToOpcode[type];
            typeInstruction I_Type(opcode,"","",rd,imm,func3,"");
            return I_Type.J_TypeConvert();
        }
        else if(type=="JL")
        {
            string rd,rs1,imm;
            ss>>rd>>rs1>>imm;
            rd.pop_back();
            rs1.pop_back();
            opcode = typeToOpcode[type];
            typeInstruction I_Type(opcode,rs1,"",rd,imm,func3,"");
            return I_Type.JL_TypeConvert();
        }
        else if(type=="U"||type=="UI")
        {
            string rd,imm;
            ss>>rd>>imm;
            rd.pop_back();
            opcode = typeToOpcode[type];
            typeInstruction I_Type(opcode,"","",rd,imm,"","");
            return I_Type.J_TypeConvert();
        }
        return "INVALID INSTRUCTION TYPE";
    }
};
//---------------------------------Instruction Memory-----------------------------------------
class InstructionMemory {
private:
    vector<string> memory; 
    int baseAddress;          

public:
    InstructionMemory(int baseAddr =0)
    {
        baseAddress = baseAddr;
    }
    void load_instructions(string instructions) 
    {
        memory.push_back(instructions);
    }
    string load_word(int address) {
        int index = (address - baseAddress) / 4;
        if (index < 0 || index >= memory.size()) 
        {
            return "$";
        }
        return memory[index]; 
    }
    void print_memory() {
        for (int i = 0; i < memory.size(); ++i) {
            cout << "Address " << baseAddress + i * 4 << ": " << memory[i] << std::endl;
        }
    }
};
InstructionMemory instrMem;


//-----------------------------------------------------REGISTER-------------------------------------------------------
unordered_map<int, int> GPR = 
{
    {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0},
    {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0},
    {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 0}, {18, 0},
    {19, 0}, {20, 0}, {21, 0}, {22, 0}, {23, 0}, {24, 0},
    {25, 0}, {26, 0}, {27, 0}, {28, 0}, {29, 0}, {30, 0},
    {31, 0},
};
//-----------------------------------------------MEMORY--------------------------------------------
class Memory
{
private:
    vector<int> memory;
public:
    Memory(size_t size) : memory(size) {}

    int8_t load_byte(int32_t address)
    {
        if (address >= memory.size()) {
            throw out_of_range("Memory access out of range");
        }
        return (memory[address]); 
    }

    int16_t load_halfword(int32_t address)
    {
        if (address + 1 >= memory.size()) {
            throw out_of_range("Memory access out of range");
        }
        return (memory[address] | (memory[address + 1] << 8));
    }

    int32_t load_word(int32_t address)
    {
        if (address + 3 >= memory.size()) {
            throw out_of_range("Memory access out of range");
        }
        return static_cast<int32_t>(memory[address] | 
               (memory[address + 1] << 8) | 
               (memory[address + 2] << 16) | 
               (memory[address + 3] << 24));
    }

    void store_byte(int32_t address, int8_t value) 
    {
        if (address >= memory.size()) {
            throw out_of_range("Memory access out of range");
        }
        memory[address] = (value);
    }

    void store_halfword(int32_t address, int16_t value) 
    {
        if (address + 1 >= memory.size()) {
            throw out_of_range("Memory access out of range");
        }
        memory[address] = (value & 0xFF);
        memory[address + 1] = ((value >> 8) & 0xFF);
    }

    void store_word(int32_t address, int32_t value) 
    {
        if (address + 3 >= memory.size()) {
            throw out_of_range("Memory access out of range");
        }
        memory[address] = (value & 0xFF);
        memory[address + 1] = ((value >> 8) & 0xFF);
        memory[address + 2] = ((value >> 16) & 0xFF);
        memory[address + 3] = ((value >> 24) & 0xFF);
    }
};

Memory mem(1024);
//---------------------------------------------------------ALU------------------------------------------------------
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
            else if (operation == "BEQ")
            {
                if(operand1==operand2)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if (operation == "BNE")
            {
                if(operand1!=operand2)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if (operation == "BLT")
            {
                if(operand1<operand2)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if (operation == "BGE")
            {
                if(operand1>=operand2)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if (operation == "BLE")
            {
                if(operand1<=operand2)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if (operation == "BGT")
            {
                if(operand1>operand2)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                cout << "Unknown operation: " << operation << endl;
                return 0;
            }
        }
};
//-----------------------------------------------------------NEGATIVE NUMBERS-------------------------------------------------------------
int sign_extend(const string &binary, int bits)
{
    int value = stoi(binary, 0, 2); 
    
    if (value & (1 << (bits - 1)))  
    {
        value -= (1 << bits); 
    }
    
    return value;
}

//-----------------------------------------------------------CPU-------------------------------------------------------------------------
class CPU 
{
    private:
        string instruction;
        
        unordered_map<string, string> OpcodeToType = 
        {
            {"0110011", "R"}, {"0010011", "I"}, {"0000011", "L"}, {"1100011", "B"},
            {"0100011", "S"}, {"1101111", "J"}, {"0110111", "U"},
            {"0010111", "UI"},{"1100111","JL"}
        };

        unordered_map<string, string> Operation = {
            {"R0000000000", "ADD"},
            {"R0000100000", "SUB"},
            {"R1110000000", "AND"},
            {"R1100000000", "OR"},
            {"R1000000000", "XOR"},
            {"R0010000000", "SLL"},
            {"R1010100000", "SRL"},
            {"R0100000000", "SLT"},
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
            {"I1010000000","SRAI"},
            {"L000", "LB"},
            {"L001", "LH"},
            {"L010", "LW"},
            {"S000", "SB"},
            {"S001", "SH"},
            {"S010", "SW"},
            {"B000", "BEQ"},
            {"B010", "BLE"},
            {"B011", "BGT"},
            {"B001", "BNE"},
            {"B100", "BLT"},
            {"B101", "BGE"},
            {"J","JAL"},
            {"JL","JALR"},
            {"U", "LUI"},
            {"UI", "AUIPC"}
        };
    public:
        CPU(const string &in) : instruction(in){} 

        void convert() 
        { 
            int n = instruction.size();
            string opcode = instruction.substr(n-7, 7); 
            //cout<<opcode<<endl;    
            opcode = OpcodeToType[opcode];
            //cout << "OPCODE=====>" << opcode << endl;

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
                cout << "R1: " << GPR[reg1] << " " << "R2: " << GPR[reg2] << " " << "Rd: " << regd << endl;
                ALU alu(operation, GPR[reg1], GPR[reg2]);
                int result = alu.execute();
                GPR[regd] = result;
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
                    ALU alu(operation, GPR[reg1], shamt);
                    GPR[regd] = alu.execute();
                    cout << "Result: " << GPR[regd] << endl;
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
                    ALU alu(operation, GPR[reg1], immediate);
                    GPR[regd] = alu.execute();

                    cout << "Result: " << GPR[regd] << endl;
                }
            }
            else if(opcode=="L")
            {
                string func3,r1,rd,imm;
                func3 = instruction.substr(n - 15, 3);
                string operation = opcode + func3;
                operation = Operation[operation];
                r1 = instruction.substr(n - 20, 5);
                imm = instruction.substr(0, 12);  
                rd = instruction.substr(n - 12, 5);
                //operation.pop_back();
                int immediate = sign_extend(imm, 12);  
                int reg1 = stoi(r1, 0, 2);
                int regd = stoi(rd, 0, 2);
                cout << "Imm: " << immediate << " R1: " << reg1 << " Rd: " << regd << " Operation: " << operation << endl;
                if(operation=="LB")
                {
                    GPR[regd] = mem.load_byte(immediate+GPR[reg1]);
                }
                else if(operation=="LW")
                {
                    GPR[regd] = mem.load_word(immediate+GPR[reg1]);
                }
                else if(operation=="LH")
                {
                    GPR[regd] = mem.load_halfword(immediate+GPR[reg1]);
                }
            }
            else if(opcode=="S")
            {
                string func3,r1,rd,imm7, imm5,imm;
                func3 = instruction.substr(n - 15, 3);
                string operation = opcode + func3;
                //cout<<operation<<endl;
                operation = Operation[operation];
                r1 = instruction.substr(n - 20, 5);
                imm7 = instruction.substr(0, 7);  
                imm5 = instruction.substr(n-12,5);
                rd = instruction.substr(n - 25, 5);
                imm = imm7+imm5;
                //operation.pop_back();
                int immediate = sign_extend(imm, 12);  
                int reg1 = stoi(r1, 0, 2);
                int regd = stoi(rd, 0, 2);
                cout << "Imm: " << immediate << " R1: " << reg1 << " Rd: " << regd << " Operation: " << operation << endl;
                if(operation=="SB")
                {
                    cout<<immediate+GPR[reg1]<<endl;
                    mem.store_byte(immediate+GPR[reg1],GPR[regd]);
                }
                else if(operation=="SW")
                {
                    cout<<immediate+GPR[reg1]<<endl;
                    mem.store_word(immediate+GPR[reg1],GPR[regd]);
                }
                else if(operation=="SH")
                {
                    mem.store_halfword(immediate+GPR[reg1],GPR[regd]);
                }
            }
            else if(opcode=="J")
            {
                string rd, imm;
                string operation = Operation[opcode];
                rd = instruction.substr(n - 12, 5);
                imm = instruction.substr(0,20);
                int regd = stoi(rd, 0, 2);
                int Immediate = sign_extend(imm,20);
                cout << "Imm: " << Immediate << " Rd: " << regd << " Operation: " << operation << endl;
                PC+=Immediate-4;
                GPR[regd] = PC;
            }
            else if(opcode=="JL")
            {
                string rd, imm, rs1;
                string operation = Operation[opcode];
                rd = instruction.substr(n - 12, 5);
                rs1 = instruction.substr(n-20,5);
                imm = instruction.substr(0,12);
                int regd = stoi(rd, 0, 2);
                int reg1 = stoi(rs1, 0, 2);
                int Immediate = sign_extend(imm,12);
                cout << "Imm: " << Immediate << " Rd: " << regd <<" R1: "<< reg1 << " Operation: " << operation << endl;
                PC+=Immediate+GPR[reg1]-4;
                GPR[regd] = PC;
            }
            else if(opcode=="B")
            {
                string func3,r1,r2,imm5,imm7,imm;
                func3 = instruction.substr(n - 15, 3);
                string operation = opcode + func3;
                operation = Operation[operation];
                r1 = instruction.substr(n - 20, 5);
                r2 = instruction.substr(n - 25, 5);
                imm5 = instruction.substr(n - 12, 5);
                imm7 = instruction.substr(0, 7);
                imm = imm7+imm5;
                int reg1 = stoi(r1, 0, 2);
                int reg2 = stoi(r2, 0, 2);
                int Immediate = sign_extend(imm,12);
                cout << "Imm: " << Immediate << " R1: " << reg1 << " R2: " << reg2 << " Operation: " << operation << endl;
                ALU alu(operation,GPR[reg1],GPR[reg2]);
                int val = alu.execute();
                if(val==1)
                {
                    PC+=Immediate-4;
                }
            }
            else if(opcode=="U")
            {
                string rd, imm;
                string operation = Operation[opcode];
                rd = instruction.substr(n - 12, 5);
                imm = instruction.substr(0,20);
                int regd = stoi(rd, 0, 2);
                int Immediate = sign_extend(imm,20);
                GPR[regd] = (Immediate<<12);
                cout << "Imm: " << (Immediate<<12) << " Rd: " << regd << " Operation: " << operation << endl;              
            }
            else if(opcode=="UI")
            {
                string rd, imm;
                string operation = Operation[opcode];
                rd = instruction.substr(n - 12, 5);
                imm = instruction.substr(0,20);
                int regd = stoi(rd, 0, 2);
                int Immediate = sign_extend(imm,20);
                Immediate = (Immediate<<12);
                cout << "Imm: " << Immediate << " Rd: " << regd << " Operation: " << operation << endl;
                PC+=Immediate-4;
                GPR[regd] = PC;
            }
            else 
            {
                printf("INVALID OPCODE");
            }

        }
};  


//------------------------------ClassForStringParsing---------------------------------
class StringParser 
{
    private:
        string TempString;
    public:
    StringParser(const string & str)
    {
        TempString = str;
    }
    void parse()
    {
        string st = "";
        for(int i=0;i<TempString.size();i++)
        {
            if(TempString[i]==';')
            {
                InstructionConvert converter;
                //cout<<st<<endl;
                //cout<<converter.convert(st)<<endl;
                instrMem.load_instructions(converter.convert(st));
                st = "";
            }
            else
            {
                st+= TempString[i];
            }
        }
    }
};

void CPU_EXECUTE()
{
    
    while(1)
    {
        string res = instrMem.load_word(PC);
        if(res=="$")
        {
            break;            
        }
        CPU cpu1 = CPU(res);
        cpu1.convert();
        PC+=4;
    }
}

//--------------------------------------main---------------------------------
int main()
{
   

    /*
        please enter semicolon ';' for end of line it would signal end of line
        ADDI x1, x1, 5;  |ADDI x1, x0, 1;|ADDI x1, x1, 10;|ADDI x1, x0, 3;|ADDI x1, x1, 8;
        BEQ x1, x0, 12;  |ADDI x2, x0, 5;|SRLI x1, x1, 1; |ADDI x2, x0, 4;|SB x1, 10[x0];
        ADDI x1, x1, -1; |SUB x3, x1, x2;|                |SLT x3, x2, x1;|LB x2, 10[x0];
        JAL x0, -8;      |                                                |ADDI x2, x2, 0;              
    */
    string str = R"(
            
        )";
    StringParser FinalStr(str);
    printf("********************************************************** \n");
    printf("GIVEN INUPT IN ASSEMBLY CODE IS: \n");
    printf("********************************************************** \n");
    for(int i=0;i<str.size();i++)
    {
        string s ="";
        for(;i<str.size();i++)
        {
            if(str[i]==';')
            {
                cout<<s<<endl;
                s = "";
            }
            else
            {            
                s+=str[i];
            }
        }   
    }
    printf("********************************************************** \n");
    printf("GENERATED BINARY CODE IS : \n");
    printf("********************************************************** \n");
    FinalStr.parse();    
    printf("INSTRUCTION MEMORY\n");
    instrMem.print_memory();
    CPU_EXECUTE();
   
    
    return 0;
}






