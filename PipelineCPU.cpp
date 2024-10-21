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
            return "00000000000000000000000000000000";
                    
        }
        return memory[index]; 
    }
    void print_memory() {
        for (int i = 0; i < memory.size(); ++i) {
            cout << "Address " << baseAddress + i * 4 << ": " << memory[i] << std::endl;
        }
    }
    int instsize()
    {
        return memory.size();
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

    int load(int address)
    {
        if (address >= memory.size()) {
            throw out_of_range("Memory access out of range");
        }
        return (memory[address]); 
    }
    void store(int address, int value) 
    {
        if (address >= memory.size()) {
            throw out_of_range("Memory access out of range");
        }
        memory[address] = (value);
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
unordered_map<string, string> OpcodeToType = 
{
    {"0110011", "R"}, {"0010011", "I"}, {"0000011", "L"}, {"1100011", "B"},
    {"0100011", "S"}, {"1101111", "J"}, {"0110111", "U"},
    {"0010111", "UI"},{"1100111","JL"}
};

// ALUOP|ALUSRC|JUMP|BRANCH|MEMRead|MEMwrite|RegWrite|MEM2Reg
    
unordered_map<string, string> CWgenerator = 
{
    {"0110011", "00000000010"}, {"0010011", "00011000010"}, {"0000011", "00101001011"}, {"1100011", "0011001000x"},
    {"0100011", "0010100010x"}, {"1101111", "0101110000x"}, {"0110111", "0110100001x"},
    {"0010111", "0111100001x"},{"1100111","1000110000x"}
};
unordered_map<string, string> Operation = 
{
    {"00000000000000", "ADD"},
    {"00000000100000", "SUB"},
    {"00001110000000", "AND"},
    {"00001100000000", "OR"},
    {"00001000000000", "XOR"},
    {"00000010000000", "SLL"},
    {"00001010100000", "SRL"},
    {"00000100000000", "SLT"},
    {"00000110000000", "SLTU"},
    {"00000000000001", "MUL"},
    {"00010000000000", "ADD"},
    {"00011000000000", "XOR"},
    {"00011100000000", "OR"},
    {"00011110000000", "AND"},
    {"00010010000000", "SLL"},
    {"00010100000000", "SLT"},
    {"00010110000000", "SLTU"},
    {"00011010100000", "SRL"},
    {"00011010000000","SRA"},
    {"00100000000000", "ADD"},
    {"00100010000000", "ADD"},
    {"00100100000000", "ADD"},
    {"00100000000000", "ADD"},
    {"00100010000000", "ADD"},
    {"00100100000000", "ADD"},
    {"00110000000000", "BEQ"},
    {"00110100000000", "BLE"},
    {"00110110000000", "BGT"},
    {"00110010000000", "BNE"},
    {"00111000000000", "BLT"},
    {"00111010000000", "BGE"},
    {"01010000000000","JAL"},
    {"10000000000000","JALR"},
    {"01100000000000", "LUI"},
    {"01110000000000", "AUIPC"}
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
class IFID {
    private:
        string instruction = "00000000000000000000000000000000";
        int npc = 0;
        int dpc = 0;
    public:
        void setIM(const string & inst)
        {
            instruction = inst;
        }
        void setNPC(const int n)
        {
            npc = n;
        }
        void setDPC(const int d)
        {
            dpc = d;
        }
        int giveDPC()
        {
            return dpc;
        }
        int giveNPC()
        {
            return npc;
        }
        string getinstruction()
        {
            return instruction;
        }
        void print_content()
        {
            cout<<"INSTRUCTION: "<<instruction<<endl;
        }
};
class IDEX
{
    private:
        string opcode = "0000000";
        string CW= "0000000000";
        int imm = 0;
        int DPC = 0;
        int NPC = 0;
        int JPC = 0;
        string func3 = "000";
        string func7 = "0000000";
        int no1 = 0;
        int no2 = 0;
        int nod = 0;
        int regd = 0;
        int reg1 = 0;
        int reg2 =0;
    public:
    void setopcode(const string & op)
    {
        opcode = op;
    }
    void setfunc3(const string & f3)
    {
        func3 = f3;
    }
    void setNPC(int npc)
    {
        NPC = npc;
    }
    void setfunc7(const string & f7)
    {
        func7 = f7;
    }
    void setregd(const int rd)
    {
        regd = rd;
    }
    void setreg1(const int r1)
    {
        reg1 = r1;
    }
    void setreg2(const int r2)
    {
        reg2 = r2;
    }
    void setImmediate(int i)
    {
        imm = i;
    }
    void setDPC(int d)
    {
        DPC = d;
    }
    void setJPC(int j)
    {
        JPC = j;
    }
    void calcCW()
    {
        CW = CWgenerator[opcode];
    }
    void setCW(const string & cw)
    {
        CW = cw;
    }
    
    int giveNPC()
    {
        return NPC;
    }
    string giveopcode()
    {
        return opcode;
    }
    string givefunc3()
    {
        return func3;
    }
    string givefunc7()
    {
        return func7;
    }
    int giveregd()
    {
        return regd;
    }
    int givereg1()
    {
        return reg1;
    }
    int givereg2()
    {
        return reg2;
    }
    int giveImmediate()
    {
        return imm;
    }
    int giveDPC()
    {
        return DPC;
    }
    int giveJPC()
    {
        return JPC;
    }
    string giveCW()
    {
        return CW;
    }
    void print_content()
    {
        cout<<"OPCODE: "<<opcode<<endl;
        cout<<"FUNC3: "<<func3<<endl;
        cout<<"FUNC7: "<<func7<<endl;
        cout<<"REG1: "<<reg1<<endl;
        cout<<"REG2: "<<reg2<<endl;
        cout<<"REGd: "<<regd<<endl;
        cout<<"Immediate: "<<imm<<endl;
        cout<<"DPC: "<<DPC<<endl;
        cout<<"CW: "<<CW<<endl;
        cout<<"JPC: "<<JPC<<endl;
    }
    void reset()
    {
        opcode = "0000000";
        CW= "0000000000";
        imm = 0;
        DPC = 0;
        NPC = 0;
        JPC = 0;
        func3 = "000";
        func7 = "0000000";
        regd = 0;
        reg1 = 0;
        reg2 =0;
    }
};
class EXMO
{
    private:
        int ALUOPT = 0;
        string CW = "0000000000";
        int reg2 = 0;
        int exe = 0;
        int regd = 0;
    public:
        void setALUOPT(int val)
        {
            ALUOPT = val;
        }
        void setCW(const string & cw)
        {
            CW = cw;
        }
        void setReg2(const int r2)
        {
            reg2 = r2;
        }
        void setRegd(const int rd)
        {
            regd = rd;
        }
        void setExe(int ex)
        {
            exe = ex;
        }
        int giveALUOPT()
        {
            return ALUOPT;
        }
        string giveCW()
        {
            return CW;
        }
        int giveReg2()
        {
            return reg2;
        }
        int giveRegd()
        {
            return regd;
        }
        int giveExe()
        {
            return exe;
        }
};
string ALUgenerate(string  ALUop,string  func3,string  func7)
{
    return Operation[ALUop+func3+func7];
}
int ALU(string & operation,int operand1,int operand2)
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
class MOWB
{   
    private:
        string CW = "0000000000";
        int LDOUT = 0;
        int ALUOUT = 0;
        int Regd = 0;
    public:
        void setCW(const string & cw)
        {
            CW = cw;
        }
        void setLDOUT(int val)
        {
            LDOUT = val;
        }
        void setALUOUT(int val)
        {
            ALUOUT = val;
        }
        void setRegd(int val)
        {
            Regd = val;
        }
        string giveCW()
        {
            return CW;
        }
        int giveLDOUT()
        {
            return LDOUT;
        }
        int giveALUOUT()
        {
            return ALUOUT;
        }
        int giveregd()
        {
            return Regd;
        }
};
IFID ifid;
IDEX idex;
EXMO exmo;
MOWB mowb;
int val = 0;
int prevB = 0;
void FETCH()
{
    string res = instrMem.load_word(PC);
    ifid.setIM(res);
    ifid.setNPC(PC+4);
    ifid.setDPC(PC);
    PC+=4;
    cout<<"RES=>"<<res<<endl;
    cout<<"PC: "<<PC<<endl;
    if(res=="00000000000000000000000000000000")
    {
        return ;
    }
    
}
void DECODE()
{
    string str = ifid.getinstruction();
    cout<<"DECODESTR"<<ifid.getinstruction()<<endl;
    int n = str.size();
    string opcode = str.substr(n-7, 7); 
    string prevopcode = opcode;
    opcode = OpcodeToType[opcode];
        if (opcode == "R")
        {
            string func7, func3, r1, r2, rd;
            string operation = opcode + func3 + func7;
            //operation = Operation[operation];
            r1 = str.substr(n - 20, 5);
            r2 = str.substr(n - 25, 5);
            rd = str.substr(n - 12, 5);
            int reg1 = stoi(r1, 0, 2);
            int reg2 = stoi(r2, 0, 2);
            int regd = stoi(rd, 0, 2);
            string imm = "0";
            int immediate = sign_extend(imm, 12);  
            

            //---decode--
            idex.setopcode(prevopcode);
            idex.setfunc7(str.substr(0, 7));
            idex.setfunc3(str.substr(n - 15, 3));
            idex.setreg1(reg1);
            idex.setreg2(reg2);
            idex.setregd(regd);
            idex.setNPC(ifid.giveNPC());
            idex.setImmediate(immediate);
            idex.setDPC(ifid.giveDPC());
            idex.calcCW();
            exmo.setExe(1);
        }
        
        else if (opcode == "I")
        {
            string func3, r1, rd, imm, func7;
            func7 = str.substr(0, 7);
            string r2 = "00000";
            if (func7 == "0000000" && (str.substr(n-15, 3) == "001"||str.substr(n-15,3)=="010"||str.substr(n-15,3)=="011"||str.substr(n-15,3)=="101"))
            {   func3 = str.substr(n - 15, 3);
                string operation = opcode + func3+func7;
                //operation = Operation[operation];
                r1 = str.substr(n - 20, 5); 
                imm = str.substr(7, 5);     
                rd = str.substr(n - 12, 5); 
                int shamt = stoi(imm, 0, 2);     
                int reg1 = stoi(r1, 0, 2);   
                int regd = stoi(rd, 0, 2);
                int reg2 = stoi(r2, 0, 2);
                //---decode---  
                idex.setopcode(prevopcode);
                idex.setfunc3(func3);
                idex.setfunc7(func7);
                idex.setreg1(reg1);  
                idex.setregd(regd);
                idex.setreg2(reg2);
                idex.setNPC(ifid.giveNPC());
                idex.setImmediate(shamt);
                idex.setDPC(ifid.giveDPC());
                idex.calcCW();
                exmo.setExe(1);
            }
            else
            {
                
                func3 = str.substr(n - 15, 3);
                string operation = opcode + func3;
                //operation = Operation[operation];
                r1 = str.substr(n - 20, 5);
                string r2 = "00000";
                string func7 = "0000000";
                imm = str.substr(0, 12);  
                rd = str.substr(n - 12, 5);
                operation.pop_back();
                int immediate = sign_extend(imm, 12);  
                int reg1 = stoi(r1, 0, 2);
                int reg2 = stoi(r2, 0, 2);
                int regd = stoi(rd, 0, 2);
                //---decode---
                idex.setopcode(prevopcode);
                idex.setfunc3(func3);
                idex.setfunc7(func7);
                idex.setreg1(reg1);
                idex.setreg2(reg2);
                idex.setregd(regd);
                idex.setNPC(ifid.giveNPC());
                idex.setImmediate(immediate);
                idex.setDPC(ifid.giveDPC());
                idex.calcCW();
                exmo.setExe(1);
            }
        }
        else if(opcode=="L")
        {
            string func3,r1,rd,imm;
            func3 = str.substr(n - 15, 3);
            string operation = opcode + func3;
            //operation = Operation[operation];
            r1 = str.substr(n - 20, 5);
            string r2 = "0";
            string func7 = "0000000";
            imm = str.substr(0, 12);  
            rd = str.substr(n - 12, 5);
            //operation.pop_back();
            int immediate = sign_extend(imm, 12);  
            int reg1 = stoi(r1, 0, 2);
            int reg2 = stoi(r2, 0, 2);
            int regd = stoi(rd, 0, 2);
            //----decode----
            idex.setopcode(prevopcode);
            idex.setfunc3(func3);
            idex.setfunc7(func7);
            idex.setImmediate(immediate);
            idex.setreg1(reg1);
            idex.setreg2(reg2);
            idex.setregd(regd);
            idex.setNPC(ifid.giveNPC());
            idex.setDPC(ifid.giveDPC());
            idex.calcCW();
            exmo.setExe(1);
        }
        else if(opcode=="S")
        {
            string func3,r1,rd,imm7, imm5,imm;
            func3 = str.substr(n - 15, 3);
            string operation = opcode + func3;
            //cout<<operation<<endl;
            //operation = Operation[operation];
            r1 = str.substr(n - 20, 5);
            string r2 = "0";
            imm7 = str.substr(0, 7);  
            imm5 = str.substr(n-12,5);
            rd = str.substr(n - 25, 5);
            string func7 = "0000000";
            imm = imm7+imm5;
            //operation.pop_back();
            int immediate = sign_extend(imm, 12);  
            int reg1 = stoi(r1, 0, 2);
            int reg2 = stoi(r2, 0, 2);
            int regd = stoi(rd, 0, 2);
            //-----decode-----
            idex.setopcode(prevopcode);
            idex.setfunc3(func3);
            idex.setfunc7(func7);
            idex.setreg1(reg1);
            idex.setreg2(reg2);
            idex.setregd(regd);
            idex.setNPC(ifid.giveNPC());
            idex.setImmediate(immediate);
            idex.setDPC(ifid.giveDPC());
            idex.calcCW();
            exmo.setExe(1);
        }
        else if(opcode=="J")
        {
            string rd, imm;
            //string operation = Operation[opcode];
            string r1 = "0";
            string r2 = "0";
            string func7 = "0000000";
            string func3 = "000";
            rd = str.substr(n - 12, 5);
            imm = str.substr(0,20);
            int reg1 = stoi(r1, 0, 2);
            int reg2 = stoi(r2, 0, 2);
            int regd = stoi(rd, 0, 2);
            int Immediate = sign_extend(imm,20);
           //----decode----
            cout<<"-------------------------------------Operation[opcode]"<<endl;
            idex.setopcode(prevopcode);
            idex.setfunc3(func3);
            idex.setfunc7(func7);
            idex.setImmediate(Immediate);
            idex.setreg1(reg1);
            idex.setreg2(reg2);
            idex.setregd(regd);
            idex.setDPC(ifid.giveDPC());
            idex.setJPC(ifid.giveNPC()+Immediate-4);
            idex.setNPC(ifid.giveNPC());
            idex.calcCW();
            exmo.setExe(1);
            GPR[regd]= ifid.giveNPC()+Immediate-4;
            //--------------------------Jump handling---------------------
            cout<<"ID JUMP HANDLING"<<endl;
            cout<<idex.giveCW()[5]<<endl;
            if(idex.giveCW()[5]=='1')
            {
                int JPC = idex.giveJPC();
                PC = JPC;
                idex.setCW("0000000000");
                exmo.setExe(0);
                cout<<"JUMP------------TAKEN"<<JPC<<endl;
            }
        }
        else if(opcode=="JL")
        {
            string rd, imm, rs1;
            //string operation = Operation[opcode];
            rd = str.substr(n - 12, 5);
            rs1 = str.substr(n-20,5);
            imm = str.substr(0,12);
            int regd = stoi(rd, 0, 2);
            int reg1 = stoi(rs1, 0, 2);
            int Immediate = sign_extend(imm,12);
            //-----decode------
            idex.setopcode(prevopcode);
            idex.setregd(regd);
            idex.setreg1(reg1);
            idex.setImmediate(Immediate);
            idex.setDPC(ifid.giveDPC());
            idex.setJPC(ifid.giveNPC()+Immediate+GPR[reg1]-4);
            idex.setNPC(ifid.giveNPC());
            idex.calcCW();
            exmo.setExe(1);
            GPR[regd] = ifid.giveNPC()+Immediate+GPR[reg1]-4;
        }
        else if(opcode=="B")
        {
            cout<<"STR"<<str<<endl;
            string func3,r1,r2,imm5,imm7,imm;
            string func7 = "0000000";
            func3 = str.substr(n - 15, 3);
            string operation = opcode + func3;
            //operation = Operation[operation];
            r1 = str.substr(n - 20, 5);
            r2 = str.substr(n - 25, 5);
            imm5 = str.substr(n - 12, 5);
            imm7 = str.substr(0, 7);
            imm = imm7+imm5;
            int reg1 = stoi(r1, 0, 2);
            int reg2 = stoi(r2, 0, 2);
            int Immediate = sign_extend(imm,12);
            //----decode----
            idex.setopcode(prevopcode);
            idex.setfunc7(func7);
            idex.setfunc3(func3);
            idex.setreg1(reg1);
            idex.setreg2(reg2);
            idex.setImmediate(Immediate);
            idex.setDPC(ifid.giveDPC());
            idex.setNPC(ifid.giveNPC());
            idex.calcCW();
            exmo.setExe(1);    
            //---------------Branch handling-------------------
            int reg1val = GPR[idex.givereg1()];
            int reg2val = GPR[idex.givereg2()]; 
            cout<<"VALUATION: "<<exmo.giveRegd()<<endl;
            cout<<"VALUATION: "<<mowb.giveregd()<<endl;
            cout<<"VALUE OF R1: "<<idex.givereg1()<<endl;
            cout<<"VALUE OF R2: "<<idex.givereg2()<<endl;
            cout<<exmo.giveCW()[9]<<endl;
            cout<<mowb.giveCW()[9]<<endl;
            if((exmo.giveCW()[9]=='1') && (exmo.giveRegd()!=0) && idex.givereg1()==exmo.giveRegd())
            {   
                reg1val = exmo.giveALUOPT();
            }
            else if((exmo.giveCW()[9]=='1') && (exmo.giveRegd()!=0) && idex.givereg2()==exmo.giveRegd())
            {
                reg2val = exmo.giveALUOPT();
            }
            else if((mowb.giveCW()[9]=='1')&& (mowb.giveregd()!=0)&&idex.givereg1()==mowb.giveregd())
            {
                if(mowb.giveCW().back()=='1')
                {
                    reg1val = mowb.giveLDOUT();
                }
                else
                {
                    reg1val = mowb.giveALUOUT();
                }
                cout<<"------------------------"<<endl;
                cout<<reg1val<<endl;
            }
            else if((mowb.giveCW()[9]=='1')&& (mowb.giveregd()!=0)&& idex.givereg2()==mowb.giveregd())
            {
                if(mowb.giveCW().back()=='1')
                {
                    reg2val = mowb.giveLDOUT();
                }
                else
                {
                    reg2val = mowb.giveALUOUT();
                }
            }
            cout<<"ID BARNCH HANDLING"<<endl;
            cout<<idex.givereg1()<<": "<<reg1val<<" "<<idex.givereg2()<<": "<<reg2val<<" CW: "<<idex.giveCW().substr(0,4)+idex.givefunc3()+idex.givefunc7()<<endl;
            string ALUselect = ALUgenerate(idex.giveCW().substr(0,4),idex.givefunc3(),idex.givefunc7());
            cout<<"ALUselect: "<<ALUselect<<endl;
            int ALUres = ALU(ALUselect,reg1val,reg2val);
            cout<<"ALURES: "<<ALUres<<endl;
            int DPC = idex.giveDPC();
            int NPC = idex.giveNPC();
            int FPC = NPC;
            if(idex.giveCW()[6]=='1' && ALUres==1)
            {  
                int BPC = DPC+idex.giveImmediate();
                cout<<"BRANCH-------------TAKEN"<<endl;
                idex.setCW("0000000000");
                PC = BPC;
                exmo.setExe(0);
            }
            else
            {
                PC = NPC;
            }
            idex.setCW("0000000000");
            exmo.setExe(0);
            prevB = 1;
        }
        else if(opcode=="U")
        {
            string rd, imm;
            //string operation = Operation[opcode];
            rd = str.substr(n - 12, 5);
            imm = str.substr(0,20);
            int regd = stoi(rd, 0, 2);
            int Immediate = sign_extend(imm,20);
            //-----decode----
            idex.setopcode(prevopcode);
            idex.setregd(regd);
            idex.setImmediate(Immediate);
            idex.setDPC(ifid.giveDPC());
            idex.setNPC(ifid.giveNPC());
            idex.calcCW();
            exmo.setExe(1);
        }
        else if(opcode=="UI")
        {
            string rd, imm;
            //string operation = Operation[opcode];
            rd = str.substr(n - 12, 5);
            imm = str.substr(0,20);
            int regd = stoi(rd, 0, 2);
            int Immediate = sign_extend(imm,20);
            Immediate = (Immediate<<12);
            //-----decode-----
            idex.setopcode(prevopcode);
            idex.setregd(regd);
            idex.setImmediate(Immediate);
            idex.setDPC(ifid.giveDPC());
            idex.setNPC(ifid.giveNPC());
            idex.calcCW();
            exmo.setExe(1);
        }
        else 
        {
            cout<<"INVALID OPCODE"<<endl;
            idex.reset();
        }
       
        
}
void EXECUTE()
{
    string CW = idex.giveCW();
    exmo.setCW(CW);
    cout<<"CW"<<CW<<endl;
    if(CW[7]=='1' &&((idex.givereg1()==exmo.giveRegd())||(idex.givereg2() == exmo.giveRegd())))
    {
        cout<<"--------------------STALL PIPELINE"<<endl;
        string cw= "00000000000";
        exmo.setCW(cw);
        int npc = idex.giveNPC();
        exmo.setExe(0);
        PC = npc+4;
        
    }
    
    int reg1val = GPR[idex.givereg1()];
    int reg2val = GPR[idex.givereg2()];
    if(CW[4]=='1')
    {
        reg2val = idex.giveImmediate();
    }
    cout<<"MOWB: "<<mowb.giveCW()<<" "<<"EXMO: "<<exmo.giveCW()<<endl;
    cout<<idex.givereg1()<<" "<<idex.givereg2()<<endl;
    cout<<exmo.giveRegd()<<" "<<mowb.giveregd()<<endl;
    cout<<exmo.giveALUOPT()<<endl;
    cout<<"prevB: "<<prevB<<endl;
    if(!prevB)
    {
        if((exmo.giveCW()[9]=='1') && (exmo.giveRegd()!=0) && idex.givereg1()==exmo.giveRegd())
        {
            reg1val = exmo.giveALUOPT();
        }
        else if((exmo.giveCW()[9]=='1') && (exmo.giveRegd()!=0) && idex.givereg2()==exmo.giveRegd())
        {
            reg2val = exmo.giveALUOPT();
        }
        else if((mowb.giveCW()[9]=='1')&& (mowb.giveregd()!=0)&&idex.givereg1()==mowb.giveregd())
        {
            cout<<"val--------------------"<<val<<endl;
            reg1val = val;
        }
        else if((mowb.giveCW()[9]=='1')&& (mowb.giveregd()!=0)&& idex.givereg2()==mowb.giveregd())
        {
            cout<<"val--------------------"<<val<<endl;
            cout<<GPR[idex.givereg2()]<<endl;
            reg2val = val;
        }
    }
    else
    {
        
        if((mowb.giveCW()[9]=='1')&& (mowb.giveregd()!=0)&&idex.givereg1()==mowb.giveregd())
        {
            cout<<"val--------------------"<<val<<endl;
            reg1val = val;
        }
        else if((mowb.giveCW()[9]=='1')&& (mowb.giveregd()!=0)&& idex.givereg2()==mowb.giveregd())
        {
            cout<<"val--------------------"<<val<<endl;
            cout<<GPR[idex.givereg2()]<<endl;
            reg2val = val;
        }
    }
    
    cout<<CW.substr(0,4)<<" "<<idex.givefunc3()<<" "<<idex.givefunc7()<<endl;
    cout<<reg1val<<" "<<reg2val<<endl;
    int DPC = idex.giveDPC();
    int NPC = idex.giveNPC();
    int FPC = NPC;
    string ALUselect = ALUgenerate(CW.substr(0,4),idex.givefunc3(),idex.givefunc7());
    exmo.setReg2(idex.givereg2());
    exmo.setRegd(idex.giveregd());
    int ALUres = ALU(ALUselect,reg1val,reg2val);
    cout<<"ALUSelect: "<<ALUselect<<" "<<"REG1: "<<idex.givereg1()<<" "<<"REG1VAL: "<<reg1val<<" "<<"REG2: "<<idex.givereg2()<<" "<<"REG2VAL: "<<reg2val<<endl;
   
    if(exmo.giveExe()==1)
    {
        cout<<idex.giveNPC()<<" "<<FPC;
        cout<<"-----------------------------HELLO-------------------------------"<<endl;
        PC = FPC+4;
    }
    exmo.setExe(0);
    cout<<"------ALURES: "<<ALUres<<endl;
    exmo.setALUOPT(ALUres);
}
void MEMOP()
{
    string CW = exmo.giveCW();
    mowb.setCW(CW);
    mowb.setRegd(exmo.giveRegd());
    mowb.setALUOUT(exmo.giveALUOPT());
    char MemRead = CW[7];
    char MemWrite = CW[8];
    if(MemRead=='1')
    {
        mowb.setLDOUT(mem.load(exmo.giveALUOPT()));
        cout<<"MEMORY LOAD RES: "<<mem.load(exmo.giveALUOPT())<<endl;
    }
    else if(MemWrite=='1')
    {
        mem.store(exmo.giveALUOPT(),GPR[exmo.giveReg2()]);
    }
}
void WRITEBK()
{
    string CW = mowb.giveCW();
    if(CW.back()=='1')
    {
        val = mowb.giveLDOUT();
    }
    else
    {
        val = mowb.giveALUOUT();
    }
    if(CW[9]=='1')
    {
        cout<<"FINAL--------------------------------"<<mowb.giveregd()<<" "<<val<<endl;
        GPR[mowb.giveregd()] = val;
    }
}

class CPU
{
    public:
    void run()
    {
        while(1)
        {
            if(PC>(instrMem.instsize()+6)*4)
            {
                break;
            }
            //cout<<"PC: "<<PC<<endl;
            WRITEBK();
            cout<<"WRITE:"<<PC<<endl;
            MEMOP();
            cout<<"MEM:"<<PC<<endl;
            EXECUTE();
            cout<<"EXECUTE:"<<PC<<endl;
            DECODE();
            idex.print_content();  
            cout<<"DECODE:"<<PC<<endl;
            FETCH();
            cout<<"FETCH: "<<PC<<endl;
            ifid.print_content();
            sleep(2);
        }
    }
};


//--------------------------------------main---------------------------------
int main()
{
   

    /*
        please enter semicolon ';' for end of line it would signal end of line
        ADDI x1, x1, 5;  |ADDI x1, x0, 1;|ADDI x1, x1, 10;|ADDI x1, x0, 3;|ADDI x1, x1, 8;
        BEQ x1, x0, 12;  |ADDI x2, x0, 5;|SRLI x1, x1, 1; |ADDI x2, x0, 4;|SB x1, 10[x0];
        ADDI x1, x1, -1; |SUB x3, x1, x2;|                |SLT x3, x2, x1;|LB x2, 10[x0];
        JAL x0, -8;      |                                                |ADDI x2, x2, 0;              
        ADDI x2, x2, 3;
        BEQ x2, x0, 100;
        ADD x1, x1, x2;
        ADDI x2, x2, -1;
        JAL x4, -12;
    */
    mem.store(100,100);
    
    string str = R"(
                ADDI x1, x1, 5;
                ADDI x2, x2, 1;
                BEQ x1, x0, 100;
                MUL x2, x1, x2;
                ADDI x1, x1, -1;
                JAL x4, -12;
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
    FinalStr.parse();    
    CPU cpu;
    cpu.run();
    cout<<GPR[1]<<endl;
    cout<<GPR[2]<<endl;
    return 0;
}
