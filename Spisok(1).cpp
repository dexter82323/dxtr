#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


typedef struct node{
	char value;		//значение элемента стека
	struct node *next;		//указатель на следующий узел
}NODE, *pNODE;

typedef struct list{	//создание структуры стек
	pNODE top;
	int len;
}LIST, *pLIST;


pLIST createlist(){
	pLIST New=(pLIST)malloc(sizeof(LIST));
	if (New){
		New->len=0;
		New->top=NULL;
	}
	return New;
}

int isEmpty(pLIST pL){
	if (pL->top && pL->len) return 0;
	return 1;
}

pNODE GetPointer(pLIST pL, int date){
	if (isEmpty(pL)) return NULL;
	pNODE temp=pL->top;
	if (temp->value<=date) return temp;
	while (temp->next && temp->next->value>date)
		temp=temp->next;
	return temp;
}

pNODE findNode(pLIST pL, int  date){
	if (isEmpty(pL)) return NULL;
	pNODE temp=pL->top;
	if (temp->value==date) return temp;
	while (temp->next && temp->value!=date)
		temp=temp->next;
	if (temp->next) return temp;
	return NULL;
}

int delNode(pLIST pL, pNODE pN){
	if (!pN) return 0;
	pNODE temp=pN->next;
	pN->next=temp->next;
	free(temp);
	pL->len--;
	return 1;
}

int addNodeAfter(pLIST pL, pNODE pN, int newdate){
	pNODE pnew=(pNODE)malloc(sizeof(NODE));
	if (pnew){
		pnew->value=newdate;
		if(!pN){
			pnew->next=NULL;
			pL->top=pnew;
		}
		else
		if (pN==pL->top && newdate>pL->top->value){
			pnew->next=pL->top;
			pL->top=pnew;
		}
		else{
			pNODE temp=pN->next;
			pnew->next=temp;
			pN->next=pnew;
		}
		pL->len++;
		return 1;
	}
	return 0;
}

void clearLIST(pLIST pL){
	while(pL->top->next) delNode(pL, pL->top);
	free(pL->top);
	pL->len--;
}

void deleteList(pLIST pL){
	if(!isEmpty(pL)) clearLIST(pL);
	free(pL);
}

void showList(pLIST pL){
	if(isEmpty(pL)) printf("List is empty!!!\n");
	else{
		pNODE temp=pL->top;
		printf("Length List:%d\n", pL->len);
		while(temp){
			printf("adres: %p \t value: %d \t next: %p \n", temp, temp->value, temp->next);
			temp=temp->next;
		}
	}
}


int main()
{
	pLIST pL=createlist();
	pNODE p;
	char exit=0;
	int com;
	while(1)
	{
		puts("1 - add element");
		puts("2 - find the value");
		puts("3 - delete the element");
		puts("4 - show list");
		puts("5 - clear list");
		puts("0 - end of work");
		scanf("%d", &com);
		switch(com){
			case 0: exit=1; break;
			case 1: printf("vvedite chislo:");
					scanf("%d", &com);
					addNodeAfter(pL, GetPointer(pL, com), com);
					break;
			case 2: printf("Enter number:");
					scanf("%d", &com);
					p=findNode(pL, com);
					if(p){
						p=(p==pL->top && com==pL->top->value)?p:p->next;
						printf("Value %d in list, address: %p\n", com, p);
					}
					else
						printf("Chislo %d ne neideno in list!\n", com);
					break;
			case 3:	printf("Enter number:");
					scanf("%d", &com);
					p=findNode(pL, com);
					if(p){
						if (p==pL->top && com==pL->top->value){
							pL->top=p->next;
							pL->len--;
							free(p);
							printf("Delete complete!\n\n");
						}
						else if (delNode(pL,p)) printf("Delete complete!\n\n");
					}
					else printf("An integer %d does not contain in list!\n", com);
					break;
			case 4: showList(pL); break;
			case 5: clearLIST(pL); showList(pL);
		}
		if(exit) break;
	}
	deleteList(pL);
	return 0;	
}
