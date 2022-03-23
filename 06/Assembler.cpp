#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<string>
using namespace std;
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
curr_command.erase(find( curr_command.begin(), curr_command.end(), '/' ), curr_command.end() );
curr_command.erase(remove(curr_command.begin(), curr_command.end(), ' '), curr_command.end());
if(curr_command=="")
return "blank line";
if(curr_command[0]=='@')
return "A_Command";
if(curr_command[0]=='(')
return "L_Command";
return "C_Command";
}
string symbol()
{
if(curr_command[0]=='(')
{
string st;
for(int i=1;i<curr_command.length()-1;i++)
{
st.push_back(curr_command[i]);
}
return st;
}
string st;
for(int i=1;i<curr_command.length();i++)
{
st.push_back(curr_command[i]);
}
if(st[0]>=48&&st[0]<=57)
{
int num=stoi(st);
string fin="";
int cnt=0;
while(true)
{
if(cnt==16)
break;
if(num==0&&cnt!=16)
{
fin.push_back('0');
cnt++;
continue;
}
if(num&1)
fin.push_back('1');
else
fin.push_back('0');
cnt++;
num=num/2;
}
reverse(fin.begin(),fin.end());
return fin;
}
else
return st;
}
string dest()
{
int x=0;
string st="";
for(int i=0;i<curr_command.size();i++)
{
if(curr_command[i]=='=')
{
x=1;
break;
}
st.push_back(curr_command[i]);


}
if(x==1)
{
return st;
}
else
return "null";
}
string comp()
{
string st="";
for(int i=0;i<curr_command.size();i++)
{
if(curr_command[i]==';')
break;
st.push_back(curr_command[i]);
if(curr_command[i]=='=')
st="";

}
return st;
}
string jump()
{
string st="";
int e=0;
for(int i=0;i<curr_command.size();i++)
{

st.push_back(curr_command[i]);
if(curr_command[i]==';')
{
e=1;
st="";
}

}
if(e==1)
{
return st;
}
else
return "null";
}
};
class Code
{
public:
string dest(string destination)
{
string s1="000";
for(int i=0;i<destination.size();i++)
{
	if(destination[i]=='M')
		s1[2]='1';
	else if(destination[i]=='D')
		s1[1]='1';
	else if(destination[i]=='A')
		s1[0]='1';
}
return s1;
}
string comp(string computation)
{
if(computation=="0")
	return "0101010";
else if(computation=="1")
	return "0111111";
else if(computation=="-1")
	return "0111010";
else if(computation=="D")
	return "0001100";
else if(computation=="A")
	return "0110000";
else if(computation=="!D")
	return "0001101";
else if(computation=="!A")
	return "0110001";
else if(computation=="-D")
	return "0001111";
else if(computation=="-A")
	return "0110011";
else if(computation=="D+1")
	return "0011111";
else if(computation=="A+1")
	return "0110111";
else if(computation=="D-1")
	return "0001110";
else if(computation=="A-1")
	return "0110010";
else if(computation=="D+A")
	return "0000010";
else if(computation=="D-A")
	return "0010011";
else if(computation=="A-D")
	return "0000111";
else if(computation=="D&A")
	return "0000000";
else if(computation=="D|A")
	return "0010101";
else if(computation=="M")
	return "1110000";
else if(computation=="!M")
	return "1110001";
else if(computation=="-M")
	return "1110011";
else if(computation=="M+1")
	return "1110111";
else if(computation=="M-1")
	return "1110010";
else if(computation=="D+M")
	return "1000010";
else if(computation=="D-M")
	return "1010011";
else if(computation=="M-D")
	return "1000111";
else if(computation=="D&M")
	return "1000000";
else if(computation=="D|M")
	return "1010101";
}
string jump(string jump)
{
	if(jump=="JGT")
	return "001";
	else if(jump==("JEQ"))
	return "010";
	else if(jump==("JGE"))
	return "011";
	else if(jump=="JLT")
	return "100";
	else if(jump=="JNE")
	return "101";
	else if(jump=="JLE")
	return "110";
	else if(jump==("JMP"))
	return "111";
	else
	return "000";
}
};
class SymbolTable
{
map<string,int>mp;
public:
SymbolTable()
{

}
void addEntry(string symbol,int address)
{
	mp[symbol]=address;
}
bool contains(string symbol)
{
	if(mp.find(symbol)!=mp.end())
		return true;
	else
		return false;
}
int GetAddress(string symbol)
{
	return mp[symbol];
}
};


int main()
{
int memc=16;
string filename;
cin>>filename;
string name="";
for(int i=0;i<filename.size();i++)
{
if(filename[i]=='.')
	break;
name.push_back(filename[i]);
}
name+=".hack";
SymbolTable symb;
vector<string>predefined{"SP","LCL","ARG","THIS","THAT","R0","R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15"};
int cnt1=0;
int e=0;
for(int i=0;i<predefined.size();i++)
{
symb.addEntry(predefined[i],cnt1);
cnt1++;
if(cnt1==5&&e==0)
{
	cnt1=0;
	e=1;
}
}

symb.addEntry("SCREEN",16384);
symb.addEntry("KBD",24576);
Parser firstpass(filename);
int cnt=0;
while(firstpass.hasMoreCommands())
{
firstpass.advance();
string type=firstpass.commandType();
if(type=="blank line")
	continue;
else if(type=="A_Command"||type=="C_Command")
{
	cnt++;
}
else
{
	string label=firstpass.symbol();
	symb.addEntry(label,cnt);
}
}
Parser obj(filename);
ofstream fout;
fout.open(name);
while(obj.hasMoreCommands())
{
obj.advance();
string type=obj.commandType();
if(type=="blank line")
continue;
else if(type=="A_Command")
{
	string instruction;
	string s1=obj.symbol();
	if(s1[0]=='0'||s1[0]=='1')
		instruction=s1;
	else
	{
		bool ch=symb.contains(s1);
		if(ch==true)
		{
			int num=symb.GetAddress(s1);
			string fin="";
int cnt=0;
while(true)
{
if(cnt==16)
break;
if(num==0&&cnt!=16)
{
fin.push_back('0');
cnt++;
continue;
}
if(num&1)
fin.push_back('1');
else
fin.push_back('0');
cnt++;
num=num/2;
}
reverse(fin.begin(),fin.end());
instruction=fin;
		}
		else
		{
		symb.addEntry(s1,memc);
		int num=memc;
		string fin="";
int cnt=0;
while(true)
{
if(cnt==16)
break;
if(num==0&&cnt!=16)
{
fin.push_back('0');
cnt++;
continue;
}
if(num&1)
fin.push_back('1');
else
fin.push_back('0');
cnt++;
num=num/2;
}
reverse(fin.begin(),fin.end());
instruction=fin;
		memc++;
		}
	}
	fout<<instruction<<endl;
}
else if(type=="C_Command")
{
	string destination=obj.dest();
	string computation=obj.comp();
	string jump=obj.jump();
	Code object;
	string s1=object.dest(destination);
	string s2=object.comp(computation);
	string s3=object.jump(jump);
    string instruction="111"+s2+s1+s3;
    fout<<instruction<<endl;
}
}
fout.close();



}