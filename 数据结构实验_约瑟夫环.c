#include<stdio.h>

//���ݽṹʵ��Σ�ʵ��һ��Լɪ�򻷣������⣩ 
//����:2020.11.01

//�����ʼ�� 
typedef struct circle_list               
	{
		int data;
		int num;
		struct circle_list *next;
	}list,*linklist;

//�����ڵ� 
list *creat_node()
{
	list *newnode=(linklist)malloc(sizeof(list));
	if(newnode==NULL)
	{
		printf("�����ˣ������ڵ�ʧ�ܣ�\n");
	}
	else
	{
		newnode->next=NULL;
		return newnode;
	}
}

//����д�� 
int insert_list(list *head,int i)
{
	//�����ڵ�
	int v;
	scanf("%d",&v);
	list *newnode=creat_node();
	newnode->data=v;
	newnode->num=i;
	//�ж�ͷ����Ƿ�Ϊ��
	if(head!=NULL)
	{
		
		//����ͷ�ڵ�,�м����P
	    list *p  = head;
		//����ͷ�ڵ㵽�����һ������
		while(p->next != head )
		{
			p = p->next;
		}
		//�����һ���ڵ㸳�µĽڵ��ȥ
		p->next = newnode;
		newnode->next = head;
		return 1;
	}
	else
	{
		printf("ͷ���Ϊ��");
		return 0;
	}
}

int main()
{
	//����ͷ�ڵ�
    list *head = creat_node();
    head->next = head;
    int m,n,i=0,j,a[100];
    scanf("%d %d",&m,&n);
    
    //�����ʼ�� 
    for(i=1;i<=n;i++)
    {
    	insert_list(head,i);
	}
	
	//���ˣ���������� 
	
	list *p = head;                //pָ��ͷ��� 
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
		
		//ͷָ�벻�����ݣ��������ͷָ�� 
		
		if(i==m-1)
		{
			q=p->next;
			m=q->data;                 //m��ֵ���� 
			printf("%d ",q->num);
			n=n-1;
			p->next=q->next;           //qָ����һ����� 
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
 
