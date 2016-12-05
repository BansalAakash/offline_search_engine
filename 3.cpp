#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
int main()
{
	int a[10],b[10],count1=0,count2=0,flag=0,i;
	char ch;
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
	}
	for(i=0;i<count1;i++)
		cout<<"\n"<<a[i]<<"->"<<b[i];
	cout<<endl;
	return 0;
}