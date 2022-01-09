#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma warning(disable:4996)


struct teacher {

	char name[20];//姓名 

	char sex;//性别 

	char birthday[20];//生日 

	int age;//年龄 

	char marriage;//婚姻状况 

	char address[50];//家庭地址 

	char title[20];//职称 

	double wages;//工资 

};


//所有函数的声明 
void quit(int x);//退出函数 

int menu();//菜单函数 

void Input_information();//录入函数 

void Lookup_function();  //查找函数




int main() {

	int choose1;


	while (1) {



		choose1 = menu();


		switch (choose1) {

		case 1: {

			Input_information();//录入函数； 

			break;
		}

		case 2: {




			break;
		}

		case 3: {



			break;
		}

		case 4: {




			break;
		}

		case 5: {

			Lookup_function();

			break;
		}

		case 6: {



			break;
		}

		case 7: {




			break;
		}

		case 8: {



			break;
		}

		case 0: {

			int choose2;

			printf("\n确认退出？\n");
			printf("确认 1||返回主菜单 0\n");

			scanf("%d", &choose2);

			quit(choose2);


			break;
		}

		default: {


			printf("请输入有效数字进行操作\n");

			system("pause");

			break;
		}

		}


		system("cls\n");

	}





	return 0;
}


int menu() {// 菜单函数 


	int n;

	printf("||-------------------------------------------------|| \n");
	printf("||                  教师工资管理系统               || \n");
	printf("||-------------------------------------------------|| \n");
	printf("||                 输入序号选择对应操作            || \n");
	printf("||-------------------------------------------------|| \n");
	printf("||          输入1——录入教师信息(请先进行此操作)  || \n");
	printf("||          输入2——显示教师信息                  || \n");//冯业彭 
	printf("||          输入3——删除教师信息                  || \n");//纪辰昊 
	printf("||          输入4——修改教师信息                  || \n");//葛立欣 
	printf("||          输入5——查找教师信息                  || \n");//李天一 
	printf("||          输入6——平均工资计算                  || \n");//盛恺曦 
	printf("||          输入7——全部工资计算                  || \n");//同上   
	printf("||          输入8——工资进行排序                  || \n");//李小雨 
	printf("||          输入9——同工资等级人员查询            || \n");//钟沐晨 
	printf("||          输入0——退出系统                      || \n");
	printf("||                                                 || \n");
	printf("||-------------------------------------------------|| \n");

	printf("请输入相应数字进行操作\n");

	scanf("%d", &n);

	return n;


}

void quit(int x) {

	if (x == 1) {

		printf("\n\n操作结束，退出系统\n");

		exit(0);
	}

	else if (x == 0) {

		printf("\n\n操作结束，返回主菜单\n");

		system("pause");

	}


}

void Input_information() {

	int n, ch;

	int i, l;

	FILE* fp1;


	struct teacher t[20];

	fp1 = fopen("teacher.txt", "a+");

	printf("\n-----------------------------------------------\n");
	printf("                    1.信息录入                     ");
	printf("\n-----------------------------------------------\n");

	printf("格式：姓名、性别、出生年月、年龄、婚姻状况、家庭住址、职称、工资级别");

	for (i = 0; i < 20; i++) {

		l = i + 1;

		printf("\n现在是%d号老师\n", l);




		printf("输入姓名：");
		scanf("%s", t[i].name);
		getchar();

		printf("输入性别：");
		scanf("%c", &t[i].sex);

		printf("输入出生年月：");
		scanf("%s", t[i].birthday);
		getchar();

		printf("输入年龄：");
		scanf("%d", &t[i].age);
		getchar();

		printf("是否结婚：");
		scanf("%c", &t[i].marriage);

		printf("输入家庭住址：");
		scanf("%s", t[i].address);
		getchar();

		printf("输入职位：");
		scanf("%s", t[i].title);
		getchar();

		printf("输入工资金额：");
		scanf("%lf", &t[i].wages);


		printf("%s %c %s %d %c %s %s %.2lf", t[i].name, t[i].sex, t[i].birthday, t[i].age, t[i].marriage, t[i].address, t[i].title, t[i].wages);


		fprintf(fp1, "%-5s %-2c %-12s %-3d %-2c %-10s %-5s %.2lf", t[i].name, t[i].sex, t[i].birthday, t[i].age, t[i].marriage, t[i].address, t[i].title, t[i].wages);
		fprintf(fp1, "\n");

		printf("\n%d号老师信息录入完成\n", i);

		printf("继续输入 1 ||退出输入 2 \n");

		scanf("%d", &n);

		if (n == 2)break;

	}

}




void Lookup_function()
{
	printf("\n-----------------------------------------------\n");
	printf("                 5.查找教师信息                    ");
	printf("\n-----------------------------------------------\n");
	
	FILE* fp;

	int i = 0, len = 0;

	struct teacher t[30];

	fp = fopen("teacher.txt", "r");//要注意teacher.txt需要与该程序在同一个文件夹里 

	while (fscanf(fp, "%s %c %s %d %c %s %s %lf", t[i].name, &t[i].sex, t[i].birthday, t[i].age, &t[i].marriage, t[i].address, t[i].title, t[i].wages) != EOF)
	{
		
		
		fscanf(fp, "%s %c %s %d %c %s %s %lf", t[i].name, &t[i].sex, t[i].birthday, t[i].age, &t[i].marriage, t[i].address, t[i].title, t[i].wages);

		len++;      //用于获取数组长度

		//从teacher.txt中读取所有教师的所有信息，将其储存到teacher结构体数组当中
	}

	//下面是查找功能的实现代码
	//思路如下：
	//首先由于用户需要输入信息，因此要先让用户选择要输入的数据类型，之后进行输入，存储到一个变量里
	//然后在结构体数组中找到相同类型的数据逐一比对，当找到相同的数据时在屏幕上显示数据
	//之后仅需进行比对，直到全部数据都比对之后结束比对

	int n;
	int z;        //用于储存“年龄”
	double f;     //用于储存“工资”
	char zf;      //用于储存“性别”、“婚姻状况”
	char zs[30];  //用于储存“姓名”、“生日”、“家庭住址”、“职称”

	printf("请选择您要输入什么数据");
	printf("输入“年龄”请输入1    输入“工资”请输入2");
	printf("输入“性别”、“婚姻状况”请输入3");
	printf("输入“姓名”、“生日”、“家庭住址”、“职称”请输入4");

	scanf("%d", &n);

	if (n = 1)
	{
		printf("请输入您要查询的信息");

		scanf("%d", &z);

		for (i = 0; i < len; i++)
		{
			if (t[i].age == z)
			{
				printf("%s %c %s %d %c %s %s %lf \n", t[i].name, &t[i].sex, t[i].birthday, t[i].age, &t[i].marriage, t[i].address, t[i].title, t[i].wages);
			}
		}


	}

	if (n = 2)
	{
		printf("请输入您要查询的信息");

		scanf("%lf", &f);

		for (i = 0; i < len; i++)
		{
			if (t[i].wages == f)
			{
				printf("%s %c %s %d %c %s %s %lf \n", t[i].name, &t[i].sex, t[i].birthday, t[i].age, &t[i].marriage, t[i].address, t[i].title, t[i].wages);
			}
		}


	}


	if (n = 3)
	{
		printf("请输入您要查询的信息");

		scanf("%c", &zf);

		for (i = 0; i < len; i++)
		{
			if (t[i].sex == zf)
			{
				printf("%s %c %s %d %c %s %s %lf \n", t[i].name, &t[i].sex, t[i].birthday, t[i].age, &t[i].marriage, t[i].address, t[i].title, t[i].wages);
			}

			else if (t[i].marriage == zf)
			{
				printf("%s %c %s %d %c %s %s %lf \n", t[i].name, &t[i].sex, t[i].birthday, t[i].age, &t[i].marriage, t[i].address, t[i].title, t[i].wages);
			}

		}


	}

	
	if (n = 4)
	{
		printf("请输入您要查询的信息");

		scanf("%s", zs);

		for (i = 0; i < len; i++)
		{
			if (strcmp(zs, t[i].name) == 0)
			{
				printf("%s %c %s %d %c %s %s %lf \n", t[i].name, &t[i].sex, t[i].birthday, t[i].age, &t[i].marriage, t[i].address, t[i].title, t[i].wages);
			}

			else if (strcmp(zs, t[i].birthday) == 0)
			{
				printf("%s %c %s %d %c %s %s %lf \n", t[i].name, &t[i].sex, t[i].birthday, t[i].age, &t[i].marriage, t[i].address, t[i].title, t[i].wages);
			}

			else if (strcmp(zs, t[i].address) == 0)
			{
				printf("%s %c %s %d %c %s %s %lf \n", t[i].name, &t[i].sex, t[i].birthday, t[i].age, &t[i].marriage, t[i].address, t[i].title, t[i].wages);
			}

			else if (strcmp(zs, t[i].title) == 0)
			{
				printf("%s %c %s %d %c %s %s %lf \n", t[i].name, &t[i].sex, t[i].birthday, t[i].age, &t[i].marriage, t[i].address, t[i].title, t[i].wages);
			}

		}


	}

	printf("信息查询完毕");


	

}


