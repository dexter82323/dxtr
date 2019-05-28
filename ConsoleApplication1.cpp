﻿// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <locale.h>

struct Data{
	char c;
	int k;
};
typedef struct Data T; //Тип элементов
#define compEQ(a, b) ((a)==(b))

typedef struct _Node {
	T data; //данные, хранящиеся в узле
	struct _Node *next;//указатель на следующий узел
} Node, *pNode;

pNode p;
Node **hashTable;
int hashTableSize;

int kolchar(char *s);
int myhash(T data);
pNode insertNode(T data);
void deleteNode(T data);
pNode findNode(T data);

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE *out;
	int i, k, maxnum = 224, kol;//kol-фактическое, количество эементо массива a
	T a[224];
	char s[225], *ps;
	for (i = 0; i < maxnum; i++) a[i].k = a[i].c = 0;
	printf("Input size Hash-Table HashTableSize :");
	scanf_s("%d", &hashTableSize);
	hashTable = (Node**)malloc(sizeof(pNode)*hashTableSize);
	scanf_s("%c", &s);
	for (i = 0, ps = s; s[i]; i++, ps++) {
		a[i].c = s[i];
		a[i].k = kolchar(ps);
		printf("%c(%3d) - %d -> %s (%d<=>%c\n", a[i].c, a[i].c, a[i].k, ps, a[i].k, ps[0]);
	}
	kol = i;
	printf("KOL=%d\n", kol);
	for (i = 0; i < hashTableSize; i++)
		hashTable[i] = NULL;
	//вывод в файл результатов анализа строки
	fopen_s(&out,"g:\\List.txt", "w");
	for (i = 0; i < kol; i++)
		fprintf(out, "%c - %d\n", a[i].c, a[i].k);
	fclose(out);
	//Заполнение хеш-таблицы элемнтами массив
	for (i = 0; i < kol; i++)
		insertNode(a[i]);
	//Поиск элементов массива по хеш-таблице
	for (i = 0; i < kol + 2; i++) {
		p = findNode(a[i]);
		if (p)
			printf("i=%d) %d -->%d\n", i, a[i].c, p->data.c);
		else
			printf("i=%d) %d(%c) NOT FIND\n", i, a[i].c, a[i].c);
	}
	//вывод элементов массива в файл List.txt
	//сохранение хеш-таблицы в файл HashTable.txt
	fopen_s(&out,"g:\\HashTable.txt", "w");
	for (i = 0; i < hashTableSize; i++) {
		fprintf(out, "%d:", i);
		pNode Temp = hashTable[i];
		while (Temp) {
			fprintf(out, "->(%c=%d-%d)", Temp->data.c, Temp->data.c, Temp->data.k);
			Temp = Temp->next;
		}
		fprintf(out, "\n");
	}
	fclose(out);
	for (i = kol - 1; i >= 0; i--)
		deleteNode(a[i]);
	//контрольная печать, после очистки хеш-таблицы
	fopen_s(&out,"g:\\HashTable1.txt", "w");
	for (i = 0; i < hashTableSize; i++) {
		fprintf(out, "%d:", i);
		pNode Temp = hashTable[i];
		while (Temp) {
			fprintf(out, "->(%c=%d - %d)", Temp->data.c, Temp -> data.c, Temp->data.k);
			Temp = Temp->next;
		}
		fprintf(out, "\n");
	}
	fclose(out);
	system("pause");
	return 0;
}

// хеш-функция размещения вершины
int myhash(T dat) {
	return (dat.c % hashTableSize);
}
// функция поиска местоположения и вставки вершины в таблицу 
pNode insertNode(T newdata) {
	pNode p, p0	; 
	int bucket;// индекс в хеш-таблице, соответ эл-ту nеwdata
	// вставка вершины в начало списка
	bucket = myhash(newdata);
	if (!(p = (pNode)malloc(sizeof(Node)))) {
		fprintf(stderr, "Нехватка памяти (insertNode) \n");
		exit(1);
	} p0 = hashTable[bucket];
	hashTable[bucket] = p;
	p->next = p0;
	p->data = newdata;
	return p;
}
//функция удаления вершины из таблицы
void deleteNode(T dat) {
	pNode p0, p;
	int bucket;
	p0 = NULL;
	bucket = myhash(dat);
	p = hashTable[bucket];
	while (p && !compEQ(p->data.c, dat.c)) {
		p0 = p;
		p = p->next;
	}
	if (!p) return;
	if (p0) p0->next = p->next;
	else hashTable[bucket] = p->next;
	free(p);
}
// Функция поиска вершины со значением data
pNode findNode(T data) {
	Node *p;
	p = hashTable[myhash(data)];
	while (p && !compEQ(p->data.c, data.c))
		p = p->next;
	return p;
}
int kolchar(char *s) {
	// удаляем все входящие s[0], кроме 1 - го 
	// возвращает кол-во вхожд. s[0] в строку
	int k = 1, i, j;
	for (i = j = 1; s[i]; i++)
		if (s[i] != s[0]) {
			s[i] = s[i]; j++;
		}
		else k++;
	s[j] = 0; return k;
}