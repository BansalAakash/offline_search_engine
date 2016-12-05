#include<stdio.h>
#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
int main()
{
	int a[100],b[100],count1=0,count2=0,flag=0,i;
	char ch,line1[50];
	string line;
	ifstream infile("abc.dat");
	ofstream outfile("crawl.txt");
	cout<<endl;
	while(!infile.eof())
	{
		infile>>ch;
		if(ch=='*' && flag==0)
		{
			infile>>ch;
			if(ch=='*' && flag==0)
			{
				a[count1++]=(int)(infile.tellg());
				flag=1;
				infile>>ch;
			}
		}
		if(ch=='*' && flag==1)
		{
			infile>>ch;
			if(ch=='*' && flag==1)
			{
				outfile<<endl;
				b[count2++]=(int)(infile.tellg());
				flag=0;
			}
		}
		if(flag==1)
			outfile<<ch;
		if(flag==1 && ch==' ')
			outfile<<' ';
	}
	for(i=0;i<count1;i++)
		cout<<"\n"<<a[i]<<"->"<<b[i];
	cout<<endl;
	infile.close();
	outfile.close();
	infile.open("crawl.txt");
	if(!infile)
		cout<<"Error:File not open\n";
	while(getline(infile,line))
	{
		strncpy(line1, line.c_str(), sizeof(line1));
		line1[sizeof(line1) - 1] = 0;
		cout<<line1<<endl;
	}
	cout<<endl;
	infile.close();
	return 0;
}