/*
    Authon: Debargha Nath
*/
#include <bits/stdc++.h>
using namespace std;

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
            string BinaryInstruction = Im.immRet7() + r2Reg.toBinary()+ r1Reg.toBinary()+func3+Im.immRet5()+opcode;
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
            string BinaryInstruction = Im.immJ() + rdReg.toBinary()+opcode;
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
        {"STL",{"R","010","0000000"}},
        {"SLTU",{"R","011","0000000"}},
        {"MUL",{"R","000","0000001"}},
        {"ADDI",{"I","000",""}},
        {"SLLI",{"IL","001","0000000"}},
        {"SLTI",{"IL","010","0000000"}},
        {"SLLIU",{"IL","011","0000000"}},
        {"XORI",{"I","100",""}},
        {"SRLI",{"IR","101","0100000"}},
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
        {"BEQ",{"B","101",""}},
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
        {"UI","0110111"}
    };
    public:
    string convert( const string & str)
    {
        stringstream ss(str);
        string opcode;
        ss>>opcode;
        if(instruction.find(opcode) == instruction.end())
        {
            return "Invalid Instruction";
        }
        auto [type, func3, func7] = instruction[opcode];
        
        if(type == "R")
        {
            string rd,r1,r2;
            ss>>rd>>r1>>r2;
            rd.pop_back();
            r1.pop_back();
            opcode = typeToOpcode[type];
            typeInstruction I_Type(opcode,r1,r2,rd,"",func3,func7);
            return I_Type.I_TypeConvert();
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
            typeInstruction I_Type(opcode,r2,r1,"",imm,func3,"");
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
                cout<<converter.convert(st)<<endl;
                st = "";
            }
            else
            {
                st+= TempString[i];
            }
        }
    }
};
//--------------------------------------main---------------------------------
int main()
{
    //string str = "ADD x1, x2, x3; ADDI x1, x2, 10; LB x1, 10[x2]; SRAI x1, x2, 5; BNE x1, x2, 5 ; SW x1, 100[x2]; JAL x3, 12; JALR x2, x3, 122;";
    /* 
        some syntax for writing inputs
        indicate an end of line by ;
        follow a space after , 
        use x[r1] for offset
          ADDI x1, x2, 10; SRLI x5, x3, 5; LBU x1, 10[x2]; BEQ x10, x2, 7; SW x7, 10[x3]; JAL x3, 12
    */
    string str = "LB x1, 100[x12];SW x7, 1000[x31];LUI x3, 100;AUIPC x3, 100;";
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
    printf("********************************************************** \n");
    return 0;
}


