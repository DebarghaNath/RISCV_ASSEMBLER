/*
    Authon: Debargha Nath
*/
#include <bits/stdc++.h>
using namespace std;


//------------------------------------------------------------------CLASS-FOR REGISTER--------------------------------------------------------------------
class Register {
private:
    string name;
    int number;
public:
    Register(const string &reg) {
        name = reg;
        number = stoi(name.substr(1));
    }

    string toBinary() {
        return bitset<5>(number).to_string();
    }

    int toNumber() {
        return number;
    }
};


//----------------------------------------------------------------CLASS-FOR IMMEDIATE VALUE---------------------------------------------------------------
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
    int immtoInt()
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
            ret+=cur[i];
        }
        return ret;
    }
    string immRet7()
    {
        string cur = immToBinary();
        string ret = "";
        for(int i=0;i<cur.size()-5;i++)
        {
            ret+=cur[i];
        }
        return ret;
    }
};



//------------------------------------------------CLASS FOR R-TYPE INSTRUCTION----------------------------------------------------------------------------
class R_TypeInstruction
{
private:
    string opcode;
    string rs1;
    string rs2;
    string rd;
    string func3;
    string func7;
public:
    R_TypeInstruction(const string &op,const string &r1,const string &r2,const string &d,const string &f3,const string &f7)
    {
        opcode = op;
        rs1 = r1;
        rs2 = r2;
        rd = d;
        func3 = f3;
        func7 = f7;
    }
    string R_TypeConvert()
    {
        Register rdReg(rd);
        Register r1Reg(rs1);
        Register r2Reg(rs2);
        string binaryInstruction = func7 + r2Reg.toBinary() + r1Reg.toBinary() + func3 + rdReg.toBinary() + opcode;
        return binaryInstruction;
    }

};




//------------------------------------------------CLASS FOR I-TYPE INSTRUCTION----------------------------------------------------------------------------
class I_TypeInstruction
{
private:
    string opcode;
    string rs1;
    string imm;
    string rd;
    string func3;
    string func7;
public:
    I_TypeInstruction(const string &op,const string &r1,const string &i,const string &d,const string &f3,const string &f7)
    {
        opcode = op;
        rs1 = r1;
        imm = i;
        rd = d;
        func3 = f3;
        func7 = f7;
    }
    string I_TypeConvert()
    {
        Register rdReg(rd);
        Register r1Reg(rs1);
        Immediate Im(imm);
        string binaryInstruction = Im.immToBinary() + r1Reg.toBinary() + func3 + rdReg.toBinary() + opcode;
        return binaryInstruction;
    }
    string IL_TypeConvert()
    {
        Register rdReg(rd);
        Register r1Reg(rs1);
        Immediate Im(imm);
        string binaryInstruction = func7 + Im.immToBinary5() + r1Reg.toBinary() + func3 + rdReg.toBinary() + opcode;
        return binaryInstruction;
    }
    string IR_TypeConvert()
    {
        Register rdReg(rd);
        Register r1Reg(rs1);
        Immediate Im(imm);
        string binaryInstruction = func7 + Im.immToBinary5() + r1Reg.toBinary() + func3 + rdReg.toBinary() + opcode;
        return binaryInstruction;
    }

};




//------------------------------------------------CLASS FOR L-TYPE INSTRUCTION----------------------------------------------------------------------------
class L_TypeInstruction
{
private:
    string opcode;
    string rs1;
    string imm;
    string rd;
    string func3;
public:
    L_TypeInstruction(const string &op,const string &r1,const string &i,const string &d,const string &f3)
    {
        opcode = op;
        rs1 = r1;
        imm = i;
        rd = d;
        func3 = f3;
    }
    string L_TypeConvert()
    {
        Register rdReg(rd);
        Register r1Reg(rs1);
        Immediate Im(imm);
        string binaryInstruction = Im.immToBinary() + r1Reg.toBinary() + func3 + rdReg.toBinary() + opcode;
        return binaryInstruction;
    }

};


//------------------------------------------------CLASS FOR B-TYPE INSTRUCTION----------------------------------------------------------------------------
class B_TypeInstruction
{
private:
    string opcode;
    string rs1;
    string rs2;
    string imm;
    string func3;
public:
    B_TypeInstruction(const string &op,const string &r1,const string &r2,const string &i,const string &f3)
    {
        opcode = op;
        rs1 = r1;
        rs2 = r2;
        imm = i;
        func3 = f3;
    }
    string B_TypeConvert()
    {
        Register r1Reg(rs1);
        Register r2Reg(rs2);
        Immediate Im(imm);

        string binaryInstruction = Im.immRet7() + r2Reg.toBinary() +r1Reg.toBinary() + func3 + Im.immRet5() + opcode;
        return binaryInstruction;
    }

};



//------------------------------------------------CLASS FOR S-TYPE INSTRUCTION----------------------------------------------------------------------------
class S_TypeInstruction
{
private:
    string opcode;
    string rs1;
    string rs2;
    string imm;
    string func3;
public:
    S_TypeInstruction(const string &op,const string &r2,const string &r1,const string &i,const string &f3)
    {
        opcode = op;
        rs1 = r1;
        rs2 = r2;
        imm = i;
        func3 = f3;
    }
    string S_TypeConvert()
    {
        Register r1Reg(rs1);
        Register r2Reg(rs2);
        Immediate Im(imm);
        string binaryInstruction = Im.immRet7() + r2Reg.toBinary() +r1Reg.toBinary() + func3 + Im.immRet5() + opcode;
        return binaryInstruction;
    }

};

//---------------------------------------------------------------CLASS FOR INSTRUCTION CONVERSION---------------------------------------------------------
class InstructionConvert 
{
private:
    unordered_map<string, tuple<string, string, string>> instruction = 
    {
        {"ADD",  {"R", "000", "0000000"}},
        {"SUB",  {"R", "000", "0100000"}},
        {"AND",  {"R", "111", "0000000"}},
        {"OR",   {"R", "110", "0000000"}},
        {"XOR",  {"R", "100", "0000000"}},
        {"SLL",  {"R", "001", "0000000"}},
        {"SRL",  {"R", "101", "0100000"}},
        {"SLT",  {"R", "010", "0000000"}}, 
        {"SLTU", {"R", "011", "0000000"}},
        {"ADDI", {"I", "000", ""}}, 
        {"SLLI", {"IL", "001", "0000000"}},
        {"SLTI", {"IL", "010", "0000000"}},
        {"SLLIU", {"IL", "011", "0000000"}},
        {"XORI", {"I", "100", ""}},
        {"SRLI", {"IR", "101", "0100000"}},
        {"SRAI", {"IR", "101", "0100000"}},
        {"ORI", {"I", "110", ""}},
        {"ANDI", {"I", "111", ""}},
        {"LB", {"L", "000", ""}},
        {"LH", {"L", "001", ""}},
        {"LW", {"L", "010", ""}},
        {"LBU", {"L", "100", ""}},
        {"LHU", {"L", "101", ""}},
        {"BEQ", {"B", "000", ""}},
        {"BNE", {"B", "001", ""}},
        {"BLT", {"B", "100", ""}},
        {"BGE", {"B", "101", ""}},
        {"SB", {"S", "000", ""}},
        {"SH", {"S", "001", ""}},
        {"SW", {"S", "010", ""}},
        {"SD", {"S", "011", ""}}
    };

    unordered_map<string, string> typeToOpcode = 
    {
        {"R", "0110011"},
        {"I", "0010011"},
        {"IL", "0010011"},
        {"IR", "0010011"},
        {"L", "0000011"},
        {"B", "1100011"},
        {"S", "0100011"}
    };


public:
    string convert(const string &str) 
    {
        stringstream ss(str);
        string opcode;
        ss >> opcode;
        //cout<<opcode<<endl;
        if (instruction.find(opcode) == instruction.end()) {
            return "Invalid Instruction";
        }
        auto [type, func3, func7] = instruction[opcode];

        if (type == "R") 
        {
            string rd, r1, r2;
            ss >> rd >> r1 >> r2;
            rd.pop_back(); 
            r1.pop_back();
            opcode = typeToOpcode[type];
            R_TypeInstruction R_Type(opcode,r1,r2,rd,func3,func7);
            return R_Type.R_TypeConvert();

        } 
        else if (type == "I") 
        {
            
            string rd, r1, imm;
            ss >> rd >> r1 >> imm;
            rd.pop_back(); 
            r1.pop_back();
            opcode = typeToOpcode[type];
            I_TypeInstruction I_Type(opcode,r1,imm,rd,func3,func7);
            return I_Type.I_TypeConvert();
        }
        else if(type =="IR")
        {
            string rd, r1, imm;
            ss >> rd >> r1 >> imm;
            rd.pop_back(); 
            r1.pop_back();
            opcode = typeToOpcode[type];
            I_TypeInstruction I_Type(opcode,r1,imm,rd,func3,func7);
            return I_Type.IR_TypeConvert();
        }
        else if( type == "IL")
        {
            string rd, r1, imm;
            ss >> rd >> r1 >> imm;
            rd.pop_back(); 
            r1.pop_back();
            opcode = typeToOpcode[type];
            I_TypeInstruction I_Type(opcode,r1,imm,rd,func3,func7);
            return I_Type.IL_TypeConvert();
        }
        else if(type=="L")
        {
            string rd,comb,imm,rs1;
            ss>>rd>>comb;
            rs1 = comb.substr(comb.size()-3,2);
            imm =  comb.substr(0,comb.size()-4);
            rd.pop_back();
            opcode = typeToOpcode[type];
            L_TypeInstruction L_Type(opcode,rs1,imm,rd,func3);
            return L_Type.L_TypeConvert();
        }
        else if(type=="B")
        {
            string r1,r2,imm;
            ss>>r1>>r2>>imm;
            r1.pop_back();
            r2.pop_back();
            opcode = typeToOpcode[type];
            B_TypeInstruction B_Type(opcode,r1,r2,imm,func3);
            return B_Type.B_TypeConvert();
        }
        else if(type=="S")
        {
            string r2,comb,imm,r1;
            ss>>r2>>comb;
            r1 = comb.substr(comb.size()-3,2);
            imm =  comb.substr(0,comb.size()-4);
            r2.pop_back();
            opcode = typeToOpcode[type];
            S_TypeInstruction S_Type(opcode,r2,r1,imm,func3);
            return S_Type.S_TypeConvert();
        }
        return "Invalid Instruction Type";
    }
};
//-----------------------------------------------------------------STRING PARSER----------------------------------------------------------------------------
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
                cout << converter.convert(st) << endl;
                st = "";
            }
            else
            {
                st += TempString[i];
            }
        }
    }

};



//--------------------------------------------------------------------------MAIN--------------------------------------------------------------------------
int main() {
    string str = "ADD x1, x2, x3; ADDI x1, x2, 10; LB x1, 10[x2]; SRAI x1, x2, 5; BNE x1, x2, 5 ; SW x1, 100[x2];";
    StringParser FinalStr(str);
    FinalStr.parse();
    return 0;
}
