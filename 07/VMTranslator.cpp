#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<dirent.h>
#include<sstream>
#include<string>
#include<cstring>
using namespace std;
string curr;
class Parser
{
private:
ifstream my_input_file;
string line;
string curr_command;
public:
Parser(string filename)
{
my_input_file.open(filename);
}
bool hasMoreCommands()
{
if(my_input_file)
{
getline(my_input_file,line);
return true;
}
else
return false;
}
void advance()
{
curr_command=line;
line="";
}
string commandType()
{
curr_command.erase(find( curr_command.begin(), curr_command.end(), '/' ), curr_command.end());
stringstream iss(curr_command);
string word;
string word1;
int cnt=0;
while(iss>>word)
{
cnt++;
if(cnt==1)
word1=word;
}
if(cnt==0)
return "blank_line";
else if(cnt==1&&word1=="return")
return "C_RETURN";
else if(cnt==1)
return "C_ARITHMETIC";
else if(cnt==2&&word1=="label")
return "C_LABEL";
else if(cnt==2&&word1=="goto")
return "C_GOTO";
else if(cnt==2&&word1=="if-goto")
return "C_IF";
else if(cnt==3&&word1=="push")
return "C_PUSH";
else if(cnt==3&&word1=="pop")
return "C_POP";
else if(cnt==3&&word1=="function")
return "C_FUNCTION";
else if(cnt==3&&word1=="call")
return "C_CALL";
}
string arg1()
{
stringstream iss(curr_command);
vector<string>words;
string word;
while(iss>>word)
words.push_back(word);
if(words.size()==1)
return words[0];
else
return words[1];
}
int arg2()
{
stringstream iss(curr_command);
vector<string>words;
string word;
while(iss>>word)
words.push_back(word);
return stoi(words[2]);
}
};
class CodeWriter
{
public:
ofstream fout;
int cnt;
int cnt2;
string name2;
public:
CodeWriter(string name)
{
int k=name.length();
while(true)
{
if(name[k-1]=='/')
break;
name2.push_back(name[k-1]);
k--;
}
reverse(name2.begin(),name2.end());
fout.open(name);
cnt=0;
cnt2=0;
}
void setFileName(string filename)
{
name2=filename;
}
void writeInit()
{
fout<<"@256"<<endl;
fout<<"D=A"<<endl;
fout<<"@SP"<<endl;
fout<<"M=D"<<endl;
fout<<"@CALL_IN"<<endl;
fout<<"D=A"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@LCL"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@ARG"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@THIS"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@THAT"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@5"<<endl;
fout<<"D=A"<<endl;
fout<<"@SP"<<endl;
fout<<"D=M-D"<<endl;
fout<<"@"<<0<<endl;
fout<<"D=D-A"<<endl;
fout<<"@ARG"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"D=M"<<endl;
fout<<"@LCL"<<endl;
fout<<"M=D"<<endl;
fout<<"@"<<"Sys.init"<<endl;
fout<<"0;JMP"<<endl;
fout<<"(CALL_IN)"<<endl;

}
void writeLabel(string label)
{
fout<<"("<<label<<")"<<endl;
}
void writeGoto(string label)
{
fout<<"@"<<label<<endl;
fout<<"0;JMP"<<endl;
}
void writeIf(string label)
{
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@"<<label<<endl;
fout<<"D;JNE"<<endl;
}
void writeCall(string s1,int v)
{
cnt2++;
fout<<"@END_OF_FUNCTION"<<cnt2<<endl;
fout<<"D=A"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@LCL"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@ARG"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@THIS"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@THAT"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@5"<<endl;
fout<<"D=A"<<endl;
fout<<"@SP"<<endl;
fout<<"D=M-D"<<endl;
fout<<"@"<<v<<endl;
fout<<"D=D-A"<<endl;
fout<<"@ARG"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"D=M"<<endl;
fout<<"@LCL"<<endl;
fout<<"M=D"<<endl;
fout<<"@"<<s1<<endl;
fout<<"0;JMP"<<endl;
fout<<"(END_OF_FUNCTION"<<cnt2<<")"<<endl;
}
void writeFunction(string s1,int v)
{
cnt2++;
fout<<"("<<s1<<")"<<endl;
fout<<"@"<<v<<endl;
fout<<"D=A"<<endl;
fout<<"("<<"LOOP"<<cnt2<<")"<<endl;
fout<<"@END_OF_LOOP"<<cnt2<<endl;
fout<<"D;JEQ"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=0"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"D=D-1"<<endl;
fout<<"@LOOP"<<cnt2<<endl;
fout<<"0;JMP"<<endl;
fout<<"(END_OF_LOOP"<<cnt2<<")"<<endl;
}
void writeReturn()
{
fout<<"@LCL"<<endl;
fout<<"D=M"<<endl;
fout<<"@R13"<<endl;
fout<<"M=D"<<endl;
fout<<"@5"<<endl;
fout<<"D=A"<<endl;
fout<<"@R13"<<endl;
fout<<"D=M-D"<<endl;
fout<<"A=D"<<endl;
fout<<"D=M"<<endl;
fout<<"@R14"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@ARG"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@ARG"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=D"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@1"<<endl;
fout<<"D=A"<<endl;
fout<<"@R13"<<endl;
fout<<"D=M-D"<<endl;
fout<<"A=D"<<endl;
fout<<"D=M"<<endl;
fout<<"@THAT"<<endl;
fout<<"M=D"<<endl;
fout<<"@2"<<endl;
fout<<"D=A"<<endl;
fout<<"@R13"<<endl;
fout<<"D=M-D"<<endl;
fout<<"A=D"<<endl;
fout<<"D=M"<<endl;
fout<<"@THIS"<<endl;
fout<<"M=D"<<endl;
fout<<"@1"<<endl;
fout<<"D=A"<<endl;
fout<<"@R13"<<endl;
fout<<"D=M-D"<<endl;
fout<<"A=D"<<endl;
fout<<"D=M"<<endl;
fout<<"@THAT"<<endl;
fout<<"M=D"<<endl;
fout<<"@3"<<endl;
fout<<"D=A"<<endl;
fout<<"@R13"<<endl;
fout<<"D=M-D"<<endl;
fout<<"A=D"<<endl;
fout<<"D=M"<<endl;
fout<<"@ARG"<<endl;
fout<<"M=D"<<endl;
fout<<"@4"<<endl;
fout<<"D=A"<<endl;
fout<<"@R13"<<endl;
fout<<"D=M-D"<<endl;
fout<<"A=D"<<endl;
fout<<"D=M"<<endl;
fout<<"@LCL"<<endl;
fout<<"M=D"<<endl;
fout<<"@R14"<<endl;
fout<<"D=M"<<endl;
fout<<"A=D"<<endl;
fout<<"0;JMP"<<endl;

}
void writeArithmetic(string command)
{

if(command=="add")
{
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D+M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
}
else if(command=="sub")
{
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"M=M-D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
}
else if(command=="and")
{
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D&M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
}
else if(command=="or")
{
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D|M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
}
else if(command=="not")
{
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"M=!M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
}
else if(command=="neg")
{
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"M=-M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
}
else if(command=="eq")
{
cnt++;
string st=to_string(cnt);
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M-D"<<endl;
fout<<"@EQUAL"+st<<endl;
fout<<"D;JEQ"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=0"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@NOTEQUAL"+st<<endl;
fout<<"0;JMP"<<endl;
fout<<"(EQUAL"<<st<<")"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=-1"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"(NOTEQUAL"<<st<<")"<<endl;



}
else if(command=="gt")
{
cnt++;
string st=to_string(cnt);
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M-D"<<endl;
fout<<"@GT"+st<<endl;
fout<<"D;JGT"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=0"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@NOTGT"+st<<endl;
fout<<"0;JMP"<<endl;
fout<<"(GT"<<st<<")"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=-1"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"(NOTGT"<<st<<")"<<endl;
}
else if(command=="lt")
{
cnt++;
string st=to_string(cnt);
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M-D"<<endl;
fout<<"@LT"+st<<endl;
fout<<"D;JLT"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=0"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@NOTLT"+st<<endl;
fout<<"0;JMP"<<endl;
fout<<"(LT"<<st<<")"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=-1"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"(NOTLT"<<st<<")"<<endl;
}
}
void writePushPop(string command,string segment,int index)
{
if(segment=="constant")
{
string l1="@";
l1+=to_string(index);
fout<<l1<<endl;
fout<<("D=A")<<endl;
fout<<("@SP")<<endl;
fout<<("A=M")<<endl;
fout<<("M=D")<<endl;
fout<<("@SP")<<endl;
fout<<("M=M+1")<<endl;
}
else if(command=="C_PUSH"&&segment=="static")
{
cnt2++;
fout<<"@"<<name2<<"."<<index<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;

}
else if(command=="C_POP"&&segment=="static")
{
cnt2++;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@"<<name2<<"."<<index<<endl;
fout<<"M=D"<<endl;
}
else if(command=="C_PUSH"&&segment=="temp")
{
index=index+5;
fout<<"@"<<index<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
}
else if(command=="C_POP"&&segment=="temp")
{
index=index+5;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@"<<index<<endl;
fout<<"M=D"<<endl;
}
else if(command=="C_PUSH"&&segment=="pointer")
{
cnt2++;
fout<<"D="<<index<<endl;
fout<<"@PLACE"<<cnt2<<endl;
fout<<"D;JEQ"<<endl;
fout<<"@THAT"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"@NOTPLACE"<<cnt2<<endl;
fout<<"0;JMP"<<endl;
fout<<"(PLACE"<<cnt2<<")"<<endl;
fout<<"@THIS"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;
fout<<"(NOTPLACE"<<cnt2<<")"<<endl;

}
else if(command=="C_POP"&&segment=="pointer")
{
cnt2++;
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"D="<<index<<endl;
fout<<"@PLACE"<<cnt2<<endl;
fout<<"D;JEQ"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@THAT"<<endl;
fout<<"M=D"<<endl;
fout<<"@NOTPLACE"<<cnt2<<endl;
fout<<"0;JMP"<<endl;
fout<<"(PLACE"<<cnt2<<")"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@THIS"<<endl;
fout<<"M=D"<<endl;
fout<<"(NOTPLACE"<<cnt2<<")"<<endl;
}
else if(command=="C_PUSH")
{
string segi;
if(segment=="local")
segi="LCL";
else if(segment=="argument")
segi="ARG";
else if(segment=="this")
segi="THIS";
else if(segment=="that")
segi="THAT";
fout<<"@"<<index<<endl;
fout<<"D=A"<<endl;
string seg="@"+segi;
fout<<seg<<endl;
fout<<"D=M+D"<<endl;
fout<<"A=D"<<endl;
fout<<"D=M"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"M=M+1"<<endl;




}
else if(command=="C_POP")
{
string segi;
if(segment=="local")
segi="LCL";
else if(segment=="argument")
segi="ARG";
else if(segment=="this")
segi="THIS";
else if(segment=="that")
segi="THAT";
fout<<"@SP"<<endl;
fout<<"M=M-1"<<endl;
fout<<"@"<<index<<endl;
fout<<"D=A"<<endl;
string seg="@"+segi;
fout<<seg<<endl;
fout<<"A=M+D"<<endl;
fout<<"D=A"<<endl;
fout<<"@R13"<<endl;
fout<<"M=D"<<endl;
fout<<"@SP"<<endl;
fout<<"A=M"<<endl;
fout<<"D=M"<<endl;
fout<<"@R13"<<endl;
fout<<"A=M"<<endl;
fout<<"M=D"<<endl;

}

}
void close()
{
fout.close();
}
};
int main(int argc,char* argv[])
{
for(int i=1;i<argc;i++)
{
string filename=argv[i];
string output_file;
if(find(filename.begin(),filename.end(),'.')!=filename.end())
{
output_file = filename.substr(0, filename.find(".")) + ".asm";
Parser obj(filename.data());
CodeWriter fin(output_file.data());
//fin.writeInit();
while(obj.hasMoreCommands())
{
obj.advance();
string type=obj.commandType();
if(type=="blank_line")
continue;
string arg1;
if(type!="C_RETURN")
arg1=obj.arg1();
int index=-1;
if(type=="C_PUSH"||type=="C_POP"||type=="C_FUNCTION"||type=="C_CALL")
{
index=obj.arg2();
}
if(type=="C_ARITHMETIC")
{
fin.writeArithmetic(arg1);
}
else if(type=="C_PUSH"||type=="C_POP")
{
fin.writePushPop(type,arg1,index);
}
else if(type=="C_LABEL")
{
fin.writeLabel(arg1);
}
else if(type=="C_GOTO")
{
fin.writeGoto(arg1);
}
else if(type=="C_IF")
{
fin.writeIf(arg1);
}
else if(type=="C_FUNCTION")
{
fin.writeFunction(arg1,index);
}
else if(type=="C_RETURN")
{
fin.writeReturn();
}
else if(type=="C_CALL")
{
fin.writeCall(arg1,index);
}

}
fin.close();
}
else
{
string nf=filename;
for(int i=0;i<nf.length();i++)
{
if(nf[i]=='/')
{
nf[i]=92;
}
} 
vector<string>vec;
struct dirent *d;
DIR *dr;
char * cstr = new char [nf.length()+1];
std::strcpy (cstr, nf.c_str());
dr = opendir(cstr);
for(d=readdir(dr); d!=NULL; d=readdir(dr))
{
vec.push_back(d->d_name);
}
closedir(dr);
output_file=filename+'/';
string anme2="";
int k=filename.length()-1;
while(true)
{
if(filename[k]=='/')
break;
anme2.push_back(filename[k]);
k--;
}
reverse(anme2.begin(),anme2.end());
output_file+=anme2;
output_file+=".asm";
CodeWriter fin(output_file.data());
fin.writeInit();
for(auto x:vec)
{
if(x.length()>3&&x[x.length()-3]=='.'&&x[x.length()-2]=='v'&&x[x.length()-1]=='m')
{
string tmp=filename;
tmp+='/';
tmp+=x;
fin.setFileName(x.substr(0,x.length()-3));
Parser obj(tmp);
while(obj.hasMoreCommands())
{
obj.advance();
string type=obj.commandType();
if(type=="blank_line")
continue;
string arg1;
if(type!="C_RETURN")
arg1=obj.arg1();
int index=-1;
if(type=="C_PUSH"||type=="C_POP"||type=="C_FUNCTION"||type=="C_CALL")
{
index=obj.arg2();
}
if(type=="C_ARITHMETIC")
{
fin.writeArithmetic(arg1);
}
else if(type=="C_PUSH"||type=="C_POP")
{
fin.writePushPop(type,arg1,index);
}
else if(type=="C_LABEL")
{
fin.writeLabel(arg1);
}
else if(type=="C_GOTO")
{
fin.writeGoto(arg1);
}
else if(type=="C_IF")
{
fin.writeIf(arg1);
}
else if(type=="C_FUNCTION")
{
fin.writeFunction(arg1,index);
}
else if(type=="C_RETURN")
{
fin.writeReturn();
}
else if(type=="C_CALL")
{
fin.writeCall(arg1,index);
}

}
}

}
fin.close();
}
}
}