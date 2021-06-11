#include<bits/stdc++.h>
using namespace std;
inline bool match(string s)
{
	if(s.size()<5||s=="__build.cpp")
		return false;
	int len=s.size();
	return s[len-1]=='p'&&s[len-2]=='p'&&s[len-3]=='c'&&s[len-4]=='.';
}
vector<string>wait;
inline string toO(string x)
{
	string s;
	for(int i=0;i<x.size()-4;++i)
		s+=x[i];
	return s;
}
inline void buildDeclaration()
{
	ofstream p("declaration.h");
	p<<"#ifndef DECLARATION_H"<<endl;
	p<<"#define DECLARATION_H"<<endl; 
	p<<"const int AI_LEN="<<wait.size()+1<<";"<<endl;
	p<<"char AI_NAMES["<<wait.size()+1<<"][128]="<<endl;
	p<<"{"<<endl;
	p<<"\t\"Human\","<<endl;
	for(int i=0;i<wait.size();++i)
	{
		if(i!=wait.size()-1)
			p<<"\t\""<<toO(wait[i])<<"\","<<endl;
		else
			p<<"\t\""<<toO(wait[i])<<"\""<<endl;
	}
	p<<"};"<<endl;
	p<<"#endif"<<endl;
	p.close();
}
inline void buildInit()
{
	ofstream p("initAIs.h");
	p<<"#ifndef INIT_AIS_H"<<endl;
	p<<"#define INIT_AIS_H"<<endl;

	p<<"#include \"../../basic/BasicDef.h\""<<endl;
	p<<"#include \"../EntityControl.h\""<<endl;
 
	for(auto q:wait)
		p<<"#include \""<<toO(q)<<".h\""<<endl;
	
	p<<"void initAIs(EntityControl::Player&a,int x)"<<endl;
	p<<"{"<<endl;
	p<<"\tswitch(x)"<<endl;
	p<<"\t{"<<endl;
	p<<"\t\tcase 0:break;"<<endl;
	for(int i=0;i<wait.size();++i)
		p<<"\t\tcase "<<i+1<<":"<<toO(wait[i])<<"::entity_input(a);break;"<<endl;
	p<<"\t\tdefault:assert(0);"<<endl;
	p<<"\t}"<<endl;
	p<<"}"<<endl;
	p<<"#endif"<<endl; 
	p.close();
}
inline void buildTable()
{
	ofstream p("table.txt");
	p<<"File\t\tNumber"<<endl;
	for(int i=0;i<wait.size();++i)
		p<<toO(wait[i])<<"\t\t"<<i+1<<endl;
	p.close();
}
inline char*stc(string x)
{
	int len=x.size();
	char*c=new char[len+1];
	for(int i=0;i<len;++i)
		c[i]=x[i];
	c[len]=0;
	return c;
}
inline void buildMakefile()
{
	string s="ar crv libAIs.a ";
	for(auto q:wait)
	{
		system(stc("g++ -c "+q+" -std=c++14 -Ofast"));
		s+=toO(q)+".o ";
		cout<<q<<" DONE"<<endl;
	}
	system(stc(s));
}
int main()
{
	ios::sync_with_stdio(false);
	system("dir > AIs.txt");
	ifstream p("AIs.txt");
	while(true)
	{
		if(p.eof())
			break;
		string s;
		p>>s;
		if(match(s))
			wait.push_back(s);
	}
	sort(wait.begin(), wait.end());
	p.close();
	buildDeclaration();
	buildInit();
	buildMakefile();
	buildTable();
	return 0;
}

