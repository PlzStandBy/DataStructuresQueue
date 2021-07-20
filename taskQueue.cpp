#include <stdio.h>
#include <string.h>
#include <windows.h>
struct patient
{
	char name[80];
	char surname[80];
	char patronymic[80];
	int age;
	char diagnosis[80];
};

struct queue
{
	patient x;
	queue *next;	
};

queue *push(queue *end,const patient &x);
queue *pop(queue *beg,patient &x);
queue *silentpop(queue *beg);
int size(queue *beg);
queue *atPosition(queue *beg,int pos);
queue *search(queue *beg,char *diagnosis,int &id);

main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	patient blank;
	int menu,patamount,check,Qsize,position=0,id=0;
	bool mark=false;
	char name_of_file[80],sdiagnosis[80];
	queue *beg=0,*end=0;
	queue *p=beg;
	do{
	printf("Valid operations:\n1 - Read data from file\n2 - Write data to file\n3 - Add patient to queue\n4 - Extract patient from the queue\n5 - View the queue\n6 - Search by position\n7 - Search by diagnosis\n8 - Clean the queue\n0 - EXIT ");
	printf("\nChoose correct operation:");
	scanf("%i",&menu);
	switch(menu)
	{
		case 1:
			{
				printf("\nEnter name of file with data (***.txt) :");
				getchar();
				gets(name_of_file);
				FILE *patfile=fopen(name_of_file,"r");
				if(patfile==NULL)
				{
					printf("\nCan't open file\n");
					break;
				}
				while(check!=EOF)
				{
					check=fscanf(patfile,"Name:%s\nSurname:%s\nPatronymic:%s\nAge:%i\nDiagnosis:%s\n-----------------------\n",&blank.name,&blank.surname,&blank.patronymic,&blank.age,&blank.diagnosis);
					if(check==EOF) 
					{
						fclose(patfile);
						break;
					}
					if(beg==0||end==0)
					{
						beg=end=push(end,blank);
					}
					else 
					{
						end=push(end,blank);
					}
				}
				fclose(patfile);
				printf("\nSuccessfully read!\n");
				break;
			}
		case 2:
			{	
				getchar();
				if(beg==0||end==0)
				{
					printf("\nQueue is empty!\n");
					break;
				}
				printf("\nEnter name of file where to enter data (***.txt) :");
				gets(name_of_file);
				FILE *patfile=fopen(name_of_file,"w");
				if(patfile==NULL)
				{
					printf("\nCan't open file\n");
					while(beg) beg = silentpop(beg);
					fclose(patfile);
					break;
				}
				p=beg;
				while(p)
				{	
					blank=p->x;
					fprintf(patfile,"Name:%s\nSurname:%s\nPatronymic:%s\nAge:%i\nDiagnosis:%s\n-----------------------\n",blank.name,blank.surname,blank.patronymic,blank.age,blank.diagnosis);
					p=p->next;	
				}
				fclose(patfile);
				printf("\nSuccessfully recorded!\n");				
				break;
			}
		case 3:
			{
				getchar();
				printf("Input patients's name:");
				gets(blank.name);
				printf("\nInput patients's surname:");
				gets(blank.surname);
				printf("\nInput patients's patronymic:");
				gets(blank.patronymic);
				printf("\nInput patients's age:");
				scanf("%i",&blank.age);
				getchar();
				printf("\nInput patients's diagnosis:");
				gets(blank.diagnosis);
				if(beg==0||end==0)
				{
					beg=end=push(end,blank);
				}
				else end=push(end,blank);
				printf("\nSuccessfully recorded!\n");
				break;
			}
		case 4:
			{
				if(beg==0||end==0)
				{
					printf("\nQueue is empty!\n");
					break;
				}
				beg = pop(beg,blank);
				printf("Name:%s\nSurname:%s\nPatronymic:%s\nAge:%i\nDiagnosis:%s\n-----------------------\n",blank.name,blank.surname,blank.patronymic,blank.age,blank.diagnosis);
				break;
			}
		case 5:
			{
				if(beg==0||end==0)
				{
					printf("\nQueue is empty!\n");
					break;
				}
				p=beg;
				while(p) 
				{	
					blank=p->x;
					printf("Name:%s\nSurname:%s\nPatronymic:%s\nAge:%i\nDiagnosis:%s\n-----------------------\n",blank.name,blank.surname,blank.patronymic,blank.age,blank.diagnosis);
					p=p->next;	
				}
				break;
			}
		case 6:
			{
				if(beg==0||end==0)
				{
					printf("\nQueue is empty!\n");
					break;
				}
				printf("\nInput needed position:");
				scanf("%i",&position);
				if(0<position&&position<=size(beg))
				{
					blank=atPosition(beg,position)->x;
					printf("Name:%s\nSurname:%s\nPatronymic:%s\nAge:%i\nDiagnosis:%s\n-----------------------\n",blank.name,blank.surname,blank.patronymic,blank.age,blank.diagnosis);
				}
				else printf("\nCannot find such position!\n");
				break;
			}
		case 7:
			{
				id=0;
				getchar();
				if(beg==0||end==0)
				{
					printf("\nQueue is empty!\n");
					break;
				}
				printf("\nInput needed diagnosis:");
				gets(sdiagnosis);
				p=beg;
				do{
				p=search(p,sdiagnosis,id);
				if(p!=0){
				mark=true;
				printf("Position:%i\nName:%s\nSurname:%s\nPatronymic:%s\nAge:%i\nDiagnosis:%s\n-----------------------\n",id,p->x.name,p->x.surname,p->x.patronymic,p->x.age,p->x.diagnosis);
				p=p->next;}
				}while(p!=0);
				if(!mark) printf("\nCannot find such diagnosis!\n");
				mark=false;
				break;
			}
		case 8:
			{
				if(beg==0||end==0)
				{
					printf("\nQueue is empty!\n");
					break;
				}
				else
				{
					while(beg)
					{
						beg = silentpop(beg);
					}
					printf("\nNow queue is empty!\n");
				}
				break;
			}
		case 0:
			{
				if(beg==0||end==0)
				{
					return 1;
				}
				else
				{
					while(beg)
					{
						beg = silentpop(beg);
					}
					return 0;	
				}
				break;
			}
		default: printf("\nIncorrect command.Try again:\n");
			
	}
  }while(menu);
}

queue *push(queue *end,const patient &x)
{
	queue *p=new queue;
	p->x=x;
	p->next=0;
	if(end) end->next=p;
	return p;
}

queue *pop(queue *beg,patient &x)
{
	x=beg->x;
	queue  *p=beg->next;
	delete beg;
	return p;
}

queue *silentpop(queue *beg)
{
	queue  *p=beg->next;
	delete beg;
	return p;	
}

int size(queue *beg)
{
	int i=0;
	while(beg)
	{
		i++;
		beg=beg->next;
	}
	return i;
}

queue *atPosition(queue *beg,int pos)
{
	queue *p=beg;
	int i;
	for(i=1;i<pos&&p->next;p=p->next,i++);
	if(i==pos) return p;
	else return 0;
}

queue *search(queue *beg,char *diagnosis,int &id)
{
	queue *p=beg;
	while(beg)
	{
		id++;
		if(strcmp(diagnosis,p->x.diagnosis)==0) return p;
		beg=beg->next;
		p=p->next;
	}
	return 0;
}





	


