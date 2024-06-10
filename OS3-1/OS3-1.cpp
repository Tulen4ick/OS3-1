#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct list
{
	int id;
	int time;
	struct list* next;
};

void add(struct list* head, int a, int t) {
	while ((head->next) != NULL) {
		head = head->next;
	}
	struct list* temp = (struct list*)malloc(sizeof(list*));
	head->next = temp;
	temp->id = a;
	temp->time = t;
	temp->next = NULL;
}

void sort(list* head, int c) {
	list* hi = head;
	list* hj = head;
	for (int i = 0; i < c - 1; i++)
	{
		for (int j = (c - 1); j > i; j--)
		{
			hj = head;
			int k = 0;
			while (k != j) {
				hj = hj->next;
				k++;
			}
			if (hi->time > hj->time)
			{
				int tid = hi->id;
				int ttime = hi->time;
				hi->id = hj->id;
				hi->time = hj->time;
				hj->id = tid;
				hj->time = ttime;
			}
		}
		hi = hi->next;
	}
}

int count(list* head) {
	int c = 0;
	while (head) {
		c++;
		head = head->next;
	}
	return(c);
}

int sum(list* head) {
	int s = 0;
	while (head) {
		s += head->time;
		head = head->next;
	}
	return(s);
}



int main() {
	setlocale(LC_ALL, "Rus");
	int n, i, t, i1, i2;
	struct list* head = NULL;
	printf("Введите количество процессов: \n");
	scanf("%d", &n);
	printf("Введите %d процессов: \n", n);
	for (i = 0; i < n; ++i) {
		if (i == 0) {
			struct list* temp = (struct list*)malloc(sizeof(list*));
			temp->id = i;
			scanf("%d", &temp->time);
			temp->next = head;
			head = temp;
		}
		else {
			scanf("%d", &t);
			add(head, i, t);
		}
	}
	system("cls");
	printf("ID введенных процессов: ");
	struct list* p = head;
	while (p != NULL) {
		printf("%5d ", p->id + 1);
		p = p->next;
	}
	printf("\nВремена обработки:      ");
	p = head;
	while (p != NULL) {
		printf("%5d ", p->time);
		p = p->next;
	}
	printf("\n------------------------------------------------------------------------------------------------\n");
	int c = count(head);
	i1 = sum(head);
	i2 = count(head);
	char** fcfs = (char**)malloc(i1 * sizeof(char*));
	for (int i = 0; i < i1; i++) {
		fcfs[i] = (char*)malloc(i2 * sizeof(char));
	}
	list* f = head;
	int* lis = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		lis[i] = f->time;
		f = f->next;
	}
	f = head;
	int* ids = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		ids[i] = f->id;
		f = f->next;
	}
	int* ti = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		ti[i] = 0;
	}
	int* to = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		to[i] = 0;
	}
    int summa = 0;
	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			if ((lis[i] + summa) > j) {
				if ((j < (lis[i] + summa)) && (j >= summa)) {
					fcfs[ids[i]][j] = 'И';
					ti[ids[i]] = j + 1;
				}
				else {
					fcfs[ids[i]][j] = 'Г';
					to[ids[i]] ++;
				}
			}
			else {
				fcfs[ids[i]][j] = ' ';
			}
		}
		summa += lis[i];
	}
	printf("\nАлгоритм FCFS: \n");
	printf("\n      ");
	for (int i = 0; i < i1; ++i) {
		printf("%5d ", (i + 1));
	}
	printf("\n");
	printf("\n");
	for (int i = 0; i < i2; ++i) {
		printf("%5d ", (i + 1));
		for (int j = 0; j < i1; ++j) {
			printf("%5c ", fcfs[i][j]);
		}
		printf("\n");
	}
	printf("\nВремя, нужное для выполнения всех процессов = %d\n", summa);
	printf("\n\nНомер процессора |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", i+1);
	}
	int summai = 0;
	int summao = 0;
	printf("\nВремя выполнения |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", ti[i]);
		summai += ti[i];
	}
	printf("    Сумма = %d", summai);
	printf("\nВремя ожидания   |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", to[i]);
		summao += to[i];
	}
	printf("    Сумма = %d\n", summao);
	float sr;
	sr = (float)summai/(float)c;
	printf("Среднее время выполнения: %6.2f\n", sr);
	sr = (float)summao / (float)c;
	printf("Среднее время ожидания:   %6.2f\n", sr);
	printf("\n------------------------------------------------------------------------------------------------\n");
	sort(head, c);
	printf("\nАлгоритм SJF: \n");
	f = head;
	for (int i = 0; i < c; ++i) {
		lis[i] = f->time;
		ids[i] = f->id;
		f = f->next;
	}
	char** sjf = (char**)malloc(i1 * sizeof(char*));
	for (int i = 0; i < n; i++) {
		sjf[i] = (char*)malloc(i2 * sizeof(char));
	}
	summa = 0;
	for (int i = 0; i < c; ++i) {
		to[i] = 0;
		ti[i] = 0;
	}
	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			if ((lis[i] + summa) > j) {
				if ((j < (lis[i] + summa)) && (j >= summa)) {
					sjf[ids[i]][j] = 'И';
					ti[ids[i]] = j + 1;
				}
				else {
					sjf[ids[i]][j] = 'Г';
					to[ids[i]] ++;
				}
			}
			else {
				sjf[ids[i]][j] = ' ';
			}
		}
		summa += lis[i];
	}
	printf("\n      ");
	for (int i = 0; i < i1; ++i) {
		printf("%5d ", (i + 1));
	}
	printf("\n");
	for (int i = 0; i < i2; ++i) {
		printf("%5d ", (i+1));
		for (int j = 0; j < i1; ++j) {
			printf("%5c ", sjf[i][j]);
		}
		printf("\n");
	}
	printf("\nВремя, нужное для выполнения всех процессов = %d\n", summa);
	printf("\n\nНомер процессора |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", i + 1);
	}
	summai = 0;
	summao = 0;
	printf("\nВремя выполнения |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", ti[i]);
		summai += ti[i];
	}
	printf("    Сумма = %d", summai);
	printf("\nВремя ожидания   |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", to[i]);
		summao += to[i];
	}
	printf("    Сумма = %d\n", summao);
	sr = (float)summai / (float)c;
	printf("Среднее время выполнения: %6.2f\n", sr);
	sr = (float)summao / (float)c;
	printf("Среднее время ожидания:   %6.2f\n", sr);
}