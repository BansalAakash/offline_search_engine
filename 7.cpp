#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
struct node
{
	struct node *next;
	string value;
};
struct queue
{
	struct node *front;
	struct node *rear;
	int count;
};
struct node *createnode(string val)
{
	struct node *temp=new node;
	temp->next=NULL;
	temp->value=val;
	//cout<<"Node created with val: "<<val<<endl;	
	return temp;
}
struct queue *createqueue()
{
	struct queue *temp=new queue;
	temp->front=NULL;
	temp->rear=NULL;
	temp->count=0;
	return temp;
}
struct queue *pop(struct queue *queue1)
{
	struct node *temp=new node;
	if(queue1->front==NULL)
		return NULL;
	else if(queue1->front==queue1->rear)
	{
		queue1->front=NULL;
		queue1->rear=NULL;
	}
	else
	{
		queue1->front=queue1->front->next;
	}
	return queue1;
}
struct queue *push(string val,struct queue *queue1)
{
	struct node *new1=createnode(val);
	if(queue1->front==NULL && queue1->rear==NULL)
	{
		queue1->front=queue1->rear=new node;
		queue1->rear=new1;
		queue1->front=new1;
		//cout<<"1\n";
	}
	else
	{
		queue1->rear->next=new node;
		queue1->rear->next=new1;
		queue1->rear=queue1->rear->next;
		//cout<<"2\n";
	}
	queue1->count++;
	return queue1;
}
void display(struct queue *queue1)
{
	if(!queue1->front)
	{
		cout<<"Queue empty\n";
		return;
	}
	struct node *temp=queue1->front;
	while(temp)
	{
		cout<<temp->value<<"\n";
		temp=temp->next;
	}
}
int search(struct queue* queue1,string val) 	//returns 1 if val found in queue1 else 0
{
	if(queue1->front==NULL)
		return 0;
	struct node *temp=new node;
	temp=queue1->front;
	while(temp)
	{
		if(val.compare(temp->value)==0)
			return 1;
		temp=temp->next;
	}
	return 0;
}
struct queue *bot(struct queue *crawl,ifstream& infile)
{
	cout<<"BOT_START\n";
	string line;
	while(getline(infile,line))
	{
		string link="";
		int i=0,flag=0,flag1=0;
		for(i=0;i<line.length()-1;i++)
		{
			if(line[i]=='*' && line[i+1]=='*' && flag==0)
			{
				flag=1;
				i+=2;
			}
			if(line[i]=='*' && line[i+1]=='*' && flag==1)
			{
				flag=0;
				flag1=1;
				i+=2;
			}
			if(flag==1 && flag1==0)
			{
				link+=line[i];
			}
			if(flag1==1)
			{
				link+='\0';
				cout<<"\nLink:"<<link<<endl;
				if(search(crawl,link)==0)
				{
					cout<<"Link not found in queue\n";
					crawl=push(link,crawl);
				}
				else
					cout<<"Link found in queue\n";
				link="";
				flag1=0;
			}
		}
	}
	infile.close();
	cout<<"BOT_END\n";
	return crawl;
}
struct queue *merge(struct queue *queue1,struct queue *queue2)
{
	if(queue1->front==NULL)
		return queue2;
	else if(queue2->front==NULL)
		return queue1;
	else
	{
		struct node *temp=queue2->front;
		while(temp)
		{
			if(search(queue1,temp->value)==0)
				queue1=push(temp->value,queue1);
			temp=temp->next;
		}
		/*queue1->rear->next=queue2->front;
		queue1->rear=queue1->rear->next;*/
		return queue1;
	}
}
/*struct queue *checkduplicate(struct queue *queue1,struct queue *queue2)
{
	if(queue1->front==NULL || queue2->front==NULL)
		return NULL;
	struct queue *tempqueue=createqueue();
	struct node *temp=queue1->front;
	while(temp)
	{
		if(search(queue2,temp->value)==0)
		{
			tempqueue=push(temp->value,tempqueue);
		}
		temp=temp->next;
	}
	return tempqueue;
}*/
struct queue *spider(struct queue *crawl,ifstream& infile)
{
	struct queue *queue1=createqueue();
	if(infile==NULL)
		return NULL;
	queue1=bot(queue1,infile);
	if(queue1->front==NULL)
		return crawl;
	cout<<"SPIDER:Linked list returned by bot:\n";
	display(queue1);
	cout<<"\n";
	cout<<"SPIDER:Displaying crawl before merge:\n\n";
	display(crawl);
	crawl=merge(crawl,queue1);
	//queue1=checkduplicate(queue1,crawl);
	cout<<"SPIDER:Displaying crawl after merge:\n\n";
	display(crawl);
	cout<<"\n";
	struct node *temp=queue1->front;
	while(temp)
	{
		ifstream infile1;
		char *link=new char[((temp->value).length())+1];
		strcpy(link,(temp->value).c_str());
		infile1.open(link);
		cout<<"Spider is inside : "<<link<<endl;
		crawl=spider(crawl,infile1);
		temp=temp->next;
	}
	return crawl;
}
int main()
{
	struct queue *crawl=createqueue();
	ifstream infile;
	infile.open("inputproject.txt");
	if(!infile)
	{
		cout<<"inputproject.txt not open\n";
		return 0;
	}
	else
		cout<<"inputproject.txt successfully opened\n";
	crawl=spider(crawl,infile);
	cout<<"Hey\n";
	if(crawl->front==NULL)
		return 1;
	cout<<"main:Displaying crawl\n";
	display(crawl);
	return 1;
}