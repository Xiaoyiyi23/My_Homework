#include<stdio.h>

#define stack_base_size 10
#define stack_add_size 20
#define stackSize 10

//���ݽṹʵ��Σ�ʵ�����ͣ�������⣨�����⣩ 
//����:2020.11.05

int stopsize;
float money;

//������Ϣ
typedef struct
{
	int out_enter;            //���� 
	int num;                  //���ƺ� 
	int time;                 //ʱ�� 
}Car;
 
//ջ�Ķ��� 
typedef struct stack
{
	int stacksize;
	Car *top;                  //ջ��ָ�룬���Դ�������±�
	Car *base; 
}stack;

//���н�㶨��
typedef struct Node
{
	Car c;
	struct Node *next;
}Newnode;

//���ж��� 
typedef struct
{
	Newnode *front;        //����ͷָ�� 
	Newnode *rear;         //����βָ�� 
}LinkQueue;

//ջ�ĳ�ʼ�� 
void InitStack(SeqStack *s)
{
    s->top=-1;
}

//��ʼ������
int InitQueue(LinkQueue *Q)
{
	Q->front=(Newnode *)malloc(sizeof(Newnode));
	if(Q->front != NULL)
	{
		Q->rear=Q->front;
		Q->front->next=NULL;
		Q->rear->next=NULL;
		return 1;                //���г�ʼ���ɹ� 
	}
	else
	{
		printf("���棺���г�ʼ��ʧ��");
		return 0;
	}
}

//�ж�ջ�Ƿ�Ϊ��
int IsEmpty(stack *s)
{
	if(s->top==-1)
	{
		return 1;            //ջ�� 
	}
	else
	{
		return 0;            //ջ�ǿ� 
	}
}

//�ж�ջ�Ƿ�����
int IsFull(stack *s)
{
	if(s->top==stackSize-1)
	{
		return 1;          //ջ���� 
	}
	else
	{
		return 0;          //ջδ�� 
	}
} 

//push-ѹջ
int push(stack *s,Car c)
{
	if(IsFull(s)==1)
	{
		printf("���棺ջ�������޷�ѹ������");    
		return 0;                        //ѹջʧ��
	}
	else
	{
		s->top++;                 //����Ųһλ 
		s->elem[s->top]=c;        //���β�c������������ѹ��ջ��
		return 1;                 //ѹջ�ɹ� 
	}
}

//pop-��ջ
int pop(stack *s,Car c)
{
	if(IsEmpty==1)
	{
		printf("���棺ջ�ѿգ��޷���������");
		return 0;              //��ջʧ�� 
	}
	else
	{
		*c=s->elem[s->top];       //�����ݸ�ֵ 
		s->top--;                 //����Ųһλ 
		return 1;                 //��ջ�ɹ� 
	}
} 

//����ջ�����޳�����Ϣ��temp�����ջλ�� 
int search(stack *s,Car c)
{
	stack *p=NULL;
	p=s;
	int temp=p->top;
	while(temp>=0)
	{
		if(p->elem[temp].num==c.num)
		{
			return temp;
		}
		temp--;
	}
	return -2;
}



//�����
int EnterQueue(LinkQueue *Q,Car c)
{
	//�½��ڵ㣬�����ڶ���β��
	Newnode *node=(Newnode *)malloc(sizeof(Newnode));
	if(Newnode != NULL)
	{
		node->c=c;
		node->next=NULL;
		Q->rear->next=node;
		Q->rear=node;
		return 1;                //����гɹ� 
	} 
	else
	{
		printf("���棺�����ʧ��");
		return 0;
	} 
}

//������
int DeleteQueue(LinkQueue *Q,Car c)
{
	Newnode *p;
	if(Q->front == Q->rear)
	{
		printf("���棺ջ��������")�� 
	}
	else
	{
		p=Q->front->next;
		Q->front->next=p->next
		*c=p->c;
		//�ж϶����Ƿ�Ϊ�գ��ǵĻ�βָ����� 
		if(Q->rear==p)
		{
			Q->front=Q->rear;
		}
		//�ͷ�ָ��p 
		free(p);
		return 1;
	} 
} 

//���복����Ϣ����ջ��� 
void Input_Car_Data(stack *s,LinkQueue *l,Car c)
{
	scanf("%d",&c->out_enter)    //��or�� 
	scanf("%d",&c->num;         //���ƺ�
	scanf("%d",&c->time);        //ʱ��
	
	//�����ж�һ�£������ĳ�Ӧ������ջ���������
	
	if(IsFull(s)==1)           //ջ��-����� 
	{
		EnterQueue(l,c);
	}
	else                      //ջδ����-��ջ 
	{
		push(s,c);
	}
	
}

void Car_Leave(stack *s,stack *se,LinkQueue *l)
{
	int m=search(s,c); 
	int leavetime=0;
	if(IsFull(s)==1)
	{
		printf("�޳���ͣ��");
	}
	int i,j;
	//��ʱm���յľ��ǳ�ջ��λ��--2�������ջ���Ͳ���ջ��--��λʱ���븨��ջse
	//�뿪�ĳ���ջ��ʱ
	if(m==s->top)
	{
		Car *c;
		c=(Car*)malloc(sizeof(Car));
		pop(s,c);
	}
	//����ջ��
	else
	{
		for(i=s->top;i>=m;i--)
		{
			Car *c=(Car*)malloc(sizeof(Car));
			//����ջ���ٳ�ջ 
			if(i==m)
			{
				pop(s,c);
			}
			else
			{
				push(se,s->elem[i]);
				pop(s,c);
			}
		}
		
		for(j=se->top;j>=0;j--)
		{
			Car *c=(Car*)malloc(sizeof(Car));
			pop(se,c);
			push(s,*c);
		}
	}
	 //�ж϶����Ƿ��еȴ�����--�еĻ���ͷ��ջ
	 if(l->rear != l->front)
	 {
	 	Car *c = (Car*)malloc(sizeof(Car));
	 	DeleteQueue(l,c);
	 	c->time=leavetime; 
	 	push(s,*c);
	 }
}

int main()
{
	stack p_stack,q_stack;
	LinkQueue p_queue;
	
	InitStack(p_stack);
	InitStack(q_stack);
	InitQueue(p_queue);
	Car c;
	
	
	scanf("%d%f",&maxsize,&money);
	
	while(1)
	{
		
		scanf("%d%d%d",&c);
		if(out_enter==0 && num==0 && time==0)
		{
			break;
		}
		else
		{
			Input_Car_Data();
		}
		
		if()
	}
	
}






