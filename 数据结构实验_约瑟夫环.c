#include<stdio.h>

//数据结构实验课：实验一，约瑟夫环（必做题） 
//日期:2020.11.01

//链表初始化 
typedef struct circle_list               
	{
		int data;
		int num;
		struct circle_list *next;
	}list,*linklist;

//创建节点 
list *creat_node()
{
	list *newnode=(linklist)malloc(sizeof(list));
	if(newnode==NULL)
	{
		printf("出错了！创建节点失败！\n");
	}
	else
	{
		newnode->next=NULL;
		return newnode;
	}
}

//数据写入 
int insert_list(list *head,int i)
{
	//创建节点
	int v;
	scanf("%d",&v);
	list *newnode=creat_node();
	newnode->data=v;
	newnode->num=i;
	//判断头结点是否为空
	if(head!=NULL)
	{
		
		//遍历头节点,中间变量P
	    list *p  = head;
		//遍历头节点到，最后一个数据
		while(p->next != head )
		{
			p = p->next;
		}
		//把最后一个节点赋新的节点过去
		p->next = newnode;
		newnode->next = head;
		return 1;
	}
	else
	{
		printf("头结点为空");
		return 0;
	}
}

int main()
{
	//创建头节点
    list *head = creat_node();
    head->next = head;
    int m,n,i=0,j,a[100];
    scanf("%d %d",&m,&n);
    
    //链表初始化 
    for(i=1;i<=n;i++)
    {
    	insert_list(head,i);
	}
	
	//至此，链表创建完毕 
	
	list *p = head;                //p指向头结点 
	list *q = NULL;
	i=0;
	
	/*for(i=0;i<=n;i++)
	{
		printf("%d ",p->data);
		printf("%d",p->num);
		p=p->next;
		printf("\n");
	}*/
	
	while(head->next != head)
	{
		if(p->next==head)
		{
			p->next=head->next;
			
		}
		
		//头指针不存数据，因此跳过头指针 
		
		if(i==m-1)
		{
			q=p->next;
			m=q->data;                 //m的值更新 
			printf("%d ",q->num);
			n=n-1;
			p->next=q->next;           //q指向下一个结点 
			free(q);
			i=0;
		}
		else
		{
			p=p->next;
			i++;
		}
		if(n==0)
		{
			break;
		}
		
	}
	
	return 0;
}
 
