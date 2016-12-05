	#include<iostream>
	#include<fstream>
	#include<string.h>
	#include<stdio.h>
	using namespace std;
	ifstream infile;
	ofstream outfile;
	struct queue
	{
		struct node *front;
		struct node *rear;
	};
	struct queue* createqueue()
	{
		struct queue *temp=new queue;
		temp->front=NULL;
		temp->rear=NULL;
		return temp;
	}
	struct node
	{
		struct node *next;
		string value;
	};
	struct node * createnode(string val)
	{
		struct node *new1=new node;
		new1->next=NULL;
		new1->value=val;
		return new1;
	}
	struct queue *push(string val,struct queue *queue1)
	{
		struct node *new1=createnode(val);
		if(queue1->front==NULL && queue1->rear==NULL)
		{
			queue1->front=queue1->rear=new node;
			queue1->rear=new1;
			queue1->front=new1;
		}
		else
		{
			queue1->rear->next=new node;
			queue1->rear->next=new1;
			queue1->rear=queue1->rear->next;
		}
		return queue1;
	}
	struct queue *pop(struct queue *queue1)
	{
		struct node *temp=new node;
		if(queue1->front==NULL)
			return NULL;
		else if(queue1->front==queue1->rear)
		{
			temp=queue1->front;
			queue1->front=NULL;
			queue1->rear=NULL;
			cout<<"POP: Poping: "<<temp->value<<endl;
			return queue1;
		}
		else
		{
			temp=queue1->front;
			queue1->front=queue1->front->next;
			cout<<"POP: Poping: "<<temp->value<<endl;
			return queue1;
		}
	}
	struct queue *scanitall(struct queue *queue1)		//reads the contents from outputproject.txt and pushes all the contents in a queue
	{
		string line;
		infile.open("outputproject.txt");
		while(getline(infile,line))
		{					 
			char *line1=new char[line.length()+1];
			strcpy(line1,line.c_str());
			queue1=push(line1,queue1);
		}
		infile.close();
		return queue1;
	}
	int search(struct queue* queue1,char *val) 	//returns 1 if val found in queue1 else 0
	{
		//cout<<"SEARCH called\n";
		if(queue1->front==NULL || queue1->rear==NULL)
			return 0;
		struct node *temp=new node;
		temp=queue1->front;
		while(temp)
		{
			if(strcmp(temp->value,val)==0)
				return 1;
			temp=temp->next;
		}
		return 0;
	}
char *findlink(char *abc)
{
	if(abc==NULL)
		return NULL;
	int i=0,flag=0,flag1=0,len=0,count=0;
	string line(abc);
	len=line.length();
	cout<<"Findlink called for : "<<line<<endl;
	/*cout<<"Strlen : "<<strlen(abc)<<endl;
	cout<<"Size of : "<<(sizeof(abc)/sizeof(abc[0]))-1<<endl;
	cout<<"Size of : "<<(sizeof(abc))-1<<endl;*/
	
	for(i=0;i<strlen(abc)-1;i++)
	{
		cout<<" l "<<count++<<" ";
			if(abc[i]=='*' && abc[i+1]=='*' && flag==0)
			{
				flag=1;
				i+=2;
				cout<<"A\n";
			}
		cout<<"-";
			if(abc[i]=='*' && abc[i+1]=='*' && flag==1)
			{
				flag=0;
				flag1=1;
				i+=2;
				cout<<"B\n";
			}
			if(flag==1 && flag1!=1)
				link[len++]=abc[i];
		if(flag1==1)
		{
			link[len++]='\0';
			cout<<"Returning "<<link<<endl;
			return link;
		}
	}
	cout<<"Returning NULL\n";
	return NULL;
}
	struct queue *processit(struct queue *queue1,char *abc)	//identifies link text in inputproject.txt
	{
		//cout<<"PROCESSIT called\n";
		ofstream outfile;
		outfile.open("outputproject.txt",ios::app);
		if(!outfile)
			cout<<"PROCESSIT: Error file not opened!\n";
		char *link;
		link=findlink(abc);
		if(link)
			cout<<"Caught: "<<link<<endl;
		if(link)
			if(search(queue1,link)==0)
				{
					cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
					outfile<<link<<endl;
					queue1=push(link,queue1);
				}
		outfile.close();
		return queue1;
	}
	void openallfiles(struct queue *queue1)
	{
		if(!queue1->rear)
			cout<<"Queue Empty\n";
		else
		{
			struct node *temp=new node;
			temp=queue1->front;
			string line;
			while(temp)
			{
				ifstream infile;
				infile.open(temp->value);
				if(!infile)
				{
					cout<<"openallfiles:File not opened\n";
					return;
				}
				while(getline(infile,line))
				{
					cout<<line<<endl;
				}
				infile.close();
				if(temp)
					temp=temp->next;
			}
		}
	}
	struct queue *findlinks(struct queue *crawl1,ifstream infile)
	{
		struct queue *queue1=createqueue();
		string line;
		while(getline(infile,line))
		{
			crawl1
		}
	}
	/*
	crawl(struct queue *crawl1)
	{
		ifstream infile1,infile2;
		infile1.open("inputproject.txt");
		crawl1=findlinks(crawl1,infile1);
	}*/
	void display(struct queue *queue1)
	{
		if(queue1->front)
		{
			struct node *temp=queue1->front;
			while(temp)
			{
				cout<<"data:"<<temp->value<<endl;
				temp=temp->next;
			}
		}
		else{
			cout<<"Sorry queue empty\n";
		}
	}/*
	struct queue * crawl(struct queue* queue1,struct node *node1)
	{
		ifstream infile2;
		infile2.open(node1->value);
		struct queue *queue0=willaddallunvisitedlinkstoqueue0(queue0,infile2);
		if(queue0->front)
			return NULL;
		else
		{
			struct node *temp=queue0->start;
			while(temp)
				crawl()
		}
	}*/
	int main()
	{
		struct queue *queue1=createqueue();
		//struct queue *crawl1=createqueue();
		queue1=scanitall(queue1);		//push all contents of outputproject.txt in  a queue
		display(queue1);
		//cout<<"Poping:\n";
		/*while(queue1->rear)
			queue1=pop(queue1);*/
		string line;
		char *line1;
		infile.open("inputproject.txt");
		while(getline(infile,line))
		{
			line1=new char[line.length()+1];
			strcpy(line1,line.c_str());
			queue1=processit(queue1,line1);
		}
		infile.close();
		openallfiles(queue1);
		return 0;
	}