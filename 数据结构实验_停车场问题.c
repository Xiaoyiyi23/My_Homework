#include<stdio.h>

#define stack_base_size 10
#define stack_add_size 20
#define stackSize 10

//数据结构实验课：实验二，停车场问题（必做题） 
//日期:2020.11.05

int stopsize;
float money;

//车辆信息
typedef struct
{
	int out_enter;            //出入 
	int num;                  //车牌号 
	int time;                 //时间 
}Car;
 
//栈的定义 
typedef struct stack
{
	int stacksize;
	Car *top;                  //栈顶指针，用以存放数组下标
	Car *base; 
}stack;

//队列结点定义
typedef struct Node
{
	Car c;
	struct Node *next;
}Newnode;

//队列定义 
typedef struct
{
	Newnode *front;        //队列头指针 
	Newnode *rear;         //队列尾指针 
}LinkQueue;

//栈的初始化 
void InitStack(SeqStack *s)
{
    s->top=-1;
}

//初始化队列
int InitQueue(LinkQueue *Q)
{
	Q->front=(Newnode *)malloc(sizeof(Newnode));
	if(Q->front != NULL)
	{
		Q->rear=Q->front;
		Q->front->next=NULL;
		Q->rear->next=NULL;
		return 1;                //队列初始化成功 
	}
	else
	{
		printf("警告：队列初始化失败");
		return 0;
	}
}

//判断栈是否为空
int IsEmpty(stack *s)
{
	if(s->top==-1)
	{
		return 1;            //栈空 
	}
	else
	{
		return 0;            //栈非空 
	}
}

//判断栈是否已满
int IsFull(stack *s)
{
	if(s->top==stackSize-1)
	{
		return 1;          //栈已满 
	}
	else
	{
		return 0;          //栈未满 
	}
} 

//push-压栈
int push(stack *s,Car c)
{
	if(IsFull(s)==1)
	{
		printf("警告：栈已满，无法压入数据");    
		return 0;                        //压栈失败
	}
	else
	{
		s->top++;                 //向上挪一位 
		s->elem[s->top]=c;        //将形参c带进来的数据压入栈中
		return 1;                 //压栈成功 
	}
}

//pop-出栈
int pop(stack *s,Car c)
{
	if(IsEmpty==1)
	{
		printf("警告：栈已空，无法弹出数据");
		return 0;              //出栈失败 
	}
	else
	{
		*c=s->elem[s->top];       //将数据赋值 
		s->top--;                 //向下挪一位 
		return 1;                 //出栈成功 
	}
} 

//查找栈中有无车牌信息，temp代表出栈位置 
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



//入队列
int EnterQueue(LinkQueue *Q,Car c)
{
	//新建节点，并排在队列尾端
	Newnode *node=(Newnode *)malloc(sizeof(Newnode));
	if(Newnode != NULL)
	{
		node->c=c;
		node->next=NULL;
		Q->rear->next=node;
		Q->rear=node;
		return 1;                //入队列成功 
	} 
	else
	{
		printf("警告：入队列失败");
		return 0;
	} 
}

//出队列
int DeleteQueue(LinkQueue *Q,Car c)
{
	Newnode *p;
	if(Q->front == Q->rear)
	{
		printf("警告：栈中无数据")； 
	}
	else
	{
		p=Q->front->next;
		Q->front->next=p->next
		*c=p->c;
		//判断队列是否为空，是的话尾指针相等 
		if(Q->rear==p)
		{
			Q->front=Q->rear;
		}
		//释放指针p 
		free(p);
		return 1;
	} 
} 

//输入车辆信息，入栈入队 
void Input_Car_Data(stack *s,LinkQueue *l,Car c)
{
	scanf("%d",&c->out_enter)    //出or入 
	scanf("%d",&c->num;         //车牌号
	scanf("%d",&c->time);        //时间
	
	//下面判断一下，新来的车应该是入栈还是入队列
	
	if(IsFull(s)==1)           //栈满-入队列 
	{
		EnterQueue(l,c);
	}
	else                      //栈未满，-入栈 
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
		printf("无车辆停靠");
	}
	int i,j;
	//这时m接收的就是出栈的位置--2中情况在栈顶和不在栈顶--让位时进入辅助栈se
	//离开的车在栈顶时
	if(m==s->top)
	{
		Car *c;
		c=(Car*)malloc(sizeof(Car));
		pop(s,c);
	}
	//不在栈顶
	else
	{
		for(i=s->top;i>=m;i--)
		{
			Car *c=(Car*)malloc(sizeof(Car));
			//先入栈，再出栈 
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
	 //判断队列是否有等待车辆--有的话对头入栈
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






