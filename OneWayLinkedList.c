#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element {
	struct element *next;
	char val[20];
} el_listy;

el_listy *first;
el_listy *second;
el_listy *third;

char tab_powt[20][20];

void dodaj_do_listy(el_listy *lista, char* slowo)
{
	el_listy *wsk, *nowy;
	wsk = lista;
	while (wsk->next != NULL)
	{
		wsk = wsk->next;
	}
	nowy = (el_listy*)malloc(sizeof(el_listy));
	strcpy(nowy->val,slowo);
	nowy->next = NULL;
	wsk->next = nowy; 
}

void bez_powtorzen(el_listy *lista) {
	el_listy *wsk = lista;
	int licznik = 0;
	int flaga = 0;
	strcpy(tab_powt[licznik++], wsk->val);
	while (wsk->next != NULL)
	{
		flaga = 0;
		for (int i = 0; i < licznik; i++) {
			if (strcmp(wsk->next->val,tab_powt[i]) == 0) {
				flaga = 1;
				break;
			}
			else strcpy(tab_powt[licznik],wsk->next->val);

		}
		if (flaga == 1) 
		{
			el_listy *usuwany = wsk->next; 
			wsk->next = usuwany->next; 
			free(usuwany);            
		}
		else
		{
			wsk = wsk->next;
			licznik++;
		}

	}
}



el_listy * dodaj_na_poczatek(el_listy *lista, char* slowo)
{
	el_listy  *nowy;

	nowy = (el_listy*)malloc(sizeof(el_listy));
	strcpy(nowy->val, slowo);
	nowy->next = lista;
	lista = nowy;
	return lista; 
}

void scal_listy(el_listy *lista1, el_listy *lista2)
{
	el_listy *wsk, *nowy;
	wsk = lista1;
	while (wsk->next != NULL)
	{
		wsk = wsk->next;
	}

	wsk->next = lista2; 
}

void wypisz_liste(el_listy *lista)
{
	el_listy *wsk = lista;
	while (wsk != NULL)
	{
		printf("%s\n", wsk->val);
		wsk = wsk->next;
	}
}

void kasuj(el_listy *lista)
{
	el_listy *wsk1 = lista;
	el_listy *wsk2 = lista->next;

	while (wsk2 != NULL)
	{
		free(wsk1);
		wsk1 = wsk2;
		wsk2 = wsk2->next;
	}

	
}



void usun_z_listy(el_listy *lista, char *slowo)
{
	int flaga = 0;
	el_listy *wsk = lista;
	while (wsk->next != NULL)
	{
		if (strcmp((wsk->next->val),slowo) == 0) 
		{
			el_listy *usuwany = wsk->next; 
			wsk->next = usuwany->next;  
			free(usuwany);
			flaga = 1;
		}
		else
		{
			wsk = wsk->next;        
		}                            
	}
	if (flaga == 0)
		printf("Nie znaleziono takiego elementu;\n");
}

el_listy * znajdz_z_listy(el_listy *lista, char *slowo, el_listy *lista1)
{
	el_listy *wsk = lista;
	while (wsk->next != NULL)
	{
		if (strcmp((wsk->val),slowo) == 0) 
		{
			lista1 = wsk;
			 return lista1;             
		}
		else
		{
			wsk = wsk->next;             
		}                              
	}
	return NULL;
}



int main()
{
	
	first = (el_listy*)malloc(sizeof(el_listy));


	second = (el_listy*)malloc(sizeof(el_listy));


	el_listy *tmp;
	tmp = (el_listy*)malloc(sizeof(el_listy));

	int ilosc;
	char* slowo;
	printf("Stworz pierwsza liste: ");
	printf("\nPodaj liczbe elementow jaka ma miec pierwsza lista: ");
	scanf("%d", &ilosc);
	for (int i = 0; i <ilosc; i++) {
		if (i == 0) {
			printf("\nPodaj %d. slowo: ", i + 1);
			scanf("%s", slowo);
			strcpy(first->val, slowo);
			first->next = NULL;
		}
		else {
			printf("\nPodaj %d. slowo: ", i + 1);
			scanf("%s", slowo);
			dodaj_do_listy(first, slowo);
		}
	}
	wypisz_liste(first);

	printf("\n\nStworz druga liste: ");
	printf("\nPodaj liczbe elementow jaka ma miec druga lista: ");
	scanf("%d", &ilosc);
	for (int i = 0; i <ilosc; i++) {
		if (i == 0) {
			printf("\nPodaj %d. slowo: ", i + 1);
			scanf("%s", slowo);
			strcpy(second->val, slowo);
			second->next = NULL;
		}
		else {
			printf("\nPodaj %d. slowo: ", i + 1);
			scanf("%s", slowo);
			dodaj_do_listy(second, slowo);
		}
	}
	wypisz_liste(second);
	int wybor;
	do {
		printf("\nMenu: ");
		printf("\n1 - wyswietl 1. liste: ");
		printf("\n2 - wyswietl scalona liste: ");
		printf("\n3 - dodaj element na poczatek do 1. listy");
		printf("\n4 - kasuj liste 1");
		printf("\n5 - zlacz listy");
		printf("\n6 - bez powtorzen lista 1");
		printf("\n7 - szukaj elementu w liscie 1 i zwroc wzkaznik: ");
		printf("\n8 - szukaj elementu w liscie 1 i usun ");
		printf("\n9 - koniec");
		printf("\n\nPodaj swoj wybor: ");
		scanf("%d", &wybor);

		switch (wybor) {
		case 1: 
			wypisz_liste(first);
			break;
		case 2:
			wypisz_liste(third);
			break;
		case 3:
			printf("Podaj element do dodania: ");
			
			scanf("%s", slowo);
			first = dodaj_na_poczatek(first, slowo);
			break;
		case 4:
			kasuj(first);
			first = NULL;
			break;
		case 5:
			scal_listy(first, second);
			third = first;
			first = NULL;
			second = NULL;
			break;
		case 6:
			bez_powtorzen(first);
			break;
		case 7:
			printf("Podaj element do znalezienia: ");
			scanf("%s", slowo);
			tmp = znajdz_z_listy(first, slowo, tmp);
			if (tmp != NULL)
				printf("\nZnaleziony element: %s", tmp->val);
			else printf("\nNie znaleziono takiego elementu.");
			break;
		case 8: 
			printf("Podaj element do usuniecia: ");
			scanf("%s", slowo);
			usun_z_listy(first, slowo);
			break;
		case 9:
			printf("\nKoniec\n");
			break;
		default: 
			printf("\nNie ma takiej opcji.");
			break;


		}


	} while (wybor != 9);

	return 0;
}