#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct wezel {
	struct wezel* left;
	struct wezel* right;
	struct wezel* next;
	char znak;
	int czestosc;
} el_drzewa;



el_drzewa* first;

void dodaj_do_kolejki(el_drzewa* kolejka, char znak, int czestosc, int kolejka_czy_wezel, el_drzewa* pomoc)
{
	el_drzewa* wsk, * nowy;
	wsk = kolejka;
	if (kolejka_czy_wezel == 0) {
		while (wsk->next != NULL)
		{
			wsk = wsk->next;
		}
		nowy = (el_drzewa*)malloc(sizeof(el_drzewa));
		nowy->znak = znak;
		nowy->czestosc = czestosc;
		nowy->next = NULL;
		nowy->left = NULL;
		nowy->right = NULL;
		wsk->next = nowy;
	}
	else {
		wsk = kolejka;
		while (wsk->next != NULL)
		{
			wsk = wsk->next;
		}
		wsk->next = pomoc;
	}
}


void wypisz_liste(el_drzewa* kolejka)
{
	el_drzewa* wsk = kolejka;
	while (wsk != NULL)
	{
		printf("%c\t %d\n", wsk->znak, wsk->czestosc);
		wsk = wsk->next;
	}
}

el_drzewa* extractMin(el_drzewa* kolejka) {
	el_drzewa* wsk = kolejka;
	el_drzewa* min = kolejka;

	int najmniejszy = kolejka->czestosc;
	while (wsk->next != NULL)
	{
		if (wsk->czestosc < najmniejszy) {
			najmniejszy = wsk->czestosc;
			min = wsk;
		}
		wsk = wsk->next;
	}

	wsk = kolejka;

	while (wsk->next != NULL)
	{
		if (wsk->next == min) {
			wsk->next = min->next;
		}
		else if (wsk->next != NULL)
			wsk = wsk->next;
	}

	return min;

}



el_drzewa* Huffman(el_drzewa * kolejka, int ilosc) {
	el_drzewa* wsk = kolejka;

	el_drzewa* x = (el_drzewa*)malloc(sizeof(el_drzewa));
	el_drzewa* y = (el_drzewa*)malloc(sizeof(el_drzewa));
	el_drzewa* z_tree;
	for (int i = 1; i < ilosc; i++) {


		x = extractMin(wsk);
		if (x == wsk) {
			if (wsk->next != NULL)
				wsk = wsk->next;
		}
		y = extractMin(wsk);
		if (y == wsk) {
			if (wsk->next != NULL)
				wsk = wsk->next;
		}

		//printf("\n\nWypisz x->znak= %c, z->czestosc= %d, y->znak= %c, y->czestosc= %d \n\n ", x->znak, x->czestosc, y->znak, y->czestosc);

		//wypisz_liste(wsk);

		z_tree = (el_drzewa*)malloc(sizeof(el_drzewa));
		z_tree->znak = (char)'z';
		z_tree->left = x;
		z_tree->right = y;
		z_tree->czestosc = x->czestosc + y->czestosc;

		//printf("Wypisz z->z= %c, z->cz= %d, z->l->z %c, z->l->cz %d, z->r->z %c, z->r->cz %d, adres z %p, adres z->l %p, adres x %p, adres z->r %p, adres y %p\n\n", z_tree->znak, z_tree->czestosc, z_tree->left->znak, z_tree->left->czestosc, z_tree->right->znak, z_tree->right->czestosc, &z_tree, &z_tree->left, &x, &z_tree->right, &y);

		//if(i==3)
		//printf("Wypisz z->znak= %c, z->czestosc= %d, z->left->znak %c, z->left->czestosc %d, z->right->znak %c, z->right->czestosc %d, z->right->left->znak %c, z->right->left->czestosc %d, z->right->right->znak %c, z->right->right->czestosc %d\n\n,  ", z_tree->znak, z_tree->czestosc, z_tree->left->znak, z_tree->left->czestosc, z_tree->right->znak, z_tree->right->czestosc, z_tree->right->left->znak, z_tree->right->left->czestosc, z_tree->right->right->znak, z_tree->right->right->czestosc );

		dodaj_do_kolejki(wsk, 'z', z_tree->czestosc, 1, z_tree);
		//wypisz_liste(wsk);

	}

	return wsk->next;

}


void kodowanie(el_drzewa * korzen, char** tabela, char* lokalna_tabela, int glebokosc) {

	int g = glebokosc;

	if ((korzen->left == NULL) & (korzen->right == NULL)) {
		for (int i = 0; i < 26; i++) {
			if (korzen->znak == (char)(i + 97)) {
				strcpy(tabela[i], lokalna_tabela);
				tabela[i][g] = '\0';
				break;
			}
		}
	}
	else {
		char* tabl = (char*)malloc(10 * sizeof(char));
		char* tabr = (char*)malloc(10 * sizeof(char));

		//printf("wchodze rekurencyjnie: poziom = %d\n", g);

		if (g != 0)
			strcpy(tabl, lokalna_tabela);

		tabl[g] = '0';

		//printf("tabL = %s\n", tabl);
		if (g != 0)
			strcpy(tabr, lokalna_tabela);

		tabr[g] = '1';
		//printf("tabR = %s\n", tabr);

		kodowanie(korzen->left, tabela, tabl, g + 1);
		kodowanie(korzen->right, tabela, tabr, g + 1);

	//	printf("wychodze rekurencyjnie\n");
	}


}


int main() {

	first = (el_drzewa*)malloc(sizeof(el_drzewa));

	int czestosc[26];

	for (int i = 0; i < 26; i++)
		czestosc[i] = 0;






	char znak;
	char nazwa[10];
	int licznik = 0;


	printf("Podaj nazwe pliku do wczytania: ");
	scanf("%s", nazwa);
	FILE * file = fopen(nazwa, "r");
	if (file == NULL) {
		printf("blad otwarcia pliku");
		return 1;
	}
	fseek(file, 0, SEEK_END);
	char* tablica;
	long int rozmiar_pliku = ftell(file);
	tablica = (char*)calloc(rozmiar_pliku, sizeof(char));
	fseek(file, 0, SEEK_SET);
	do {
		znak = fgetc(file);
		if (!(isspace(znak))) {
			licznik++;
			if ((int)znak >= 97 & (int)znak <= 122) {
				czestosc[(int)znak - 97]++;
			}

			if ((int)znak >= 65 & (int)znak <= 90)
				czestosc[(int)znak - 65]++;
		}

	} while (znak != EOF);

	fclose(file);

	//for(int i = 0; i<26; i++){
   	//printf("%c czestosc znaku: %d\n", (char)(i+97), czestosc[i] );
	//}


	int ilosc_niezerowych = 0;
	for (int i = 0; i < 26; i++) {
		if (czestosc[i] != 0) ilosc_niezerowych++;
	}





	int czy_pierwszy = 0;
	for (int i = 0; i < 26; i++) {
		if (czestosc[i] != 0) {
			if (czy_pierwszy == 0) {
				czy_pierwszy = 1;
				first->znak = (char)(i + 97);
				first->czestosc = czestosc[i];
				first->next = NULL;
				first->left = NULL;
				first->right = NULL;
			}
			else {
				dodaj_do_kolejki(first, (char)(i + 97), czestosc[i], 0, NULL);
			}
		}
	}



	wypisz_liste(first);

	el_drzewa* korzen = (el_drzewa*)malloc(sizeof(el_drzewa));
	korzen = Huffman(first, ilosc_niezerowych);
	//printf("wyszedlem z Huffmana\n");
	//printf("\n\nKorzen znak: %c, korzen czestosc: %d,  znak lewego %c, czestosc lewego %d, znak prawego %c, czestosc prawego %d, znak lewego lewego %c, czestosc lewego lewego %d, znak lewego prawego %c, czestosc lewego prawego %d", korzen->znak, korzen->czestosc, korzen->left->znak, korzen->left->czestosc, korzen->right->znak, korzen->right->czestosc, korzen->left->left->znak, korzen->left->left->czestosc, korzen->left->right->znak, korzen->left->right->czestosc);

	int flaga1 = 0;
	int flaga2 = 0;

	char** tabela = (char**)malloc(26 * sizeof(char*));

	if (tabela == NULL)
		flaga1 = 1;

	for (int i = 0; i < 26; i++) {
		tabela[i] = (char*)malloc(10 * sizeof(char));
		if (tabela[i] == NULL)
			flaga2 = 1;
	}

	if ((flaga1 == 0) & (flaga2 == 0))
		printf("Udalo sie zaalokowac pamiec\n");
	else {
		printf("nie udalo sie zaalokowac pamieci\n");
		return 0;
	}

	kodowanie(korzen, tabela, NULL, 0);

	int kompresja = 0;
	int suma_czestosc = 0;
	for (int i = 0; i < 26; i++) {
		if (czestosc[i] != 0) {
			int dlugosc = strlen(tabela[i]);
			suma_czestosc += czestosc[i];
			kompresja += dlugosc * czestosc[i];
			printf("Litera %c | czestosc: %d | kodowanie: %s | dlugosc kodowania: %d\n", (char)(i + 97), czestosc[i], tabela[i], dlugosc);
		}
	}

	printf("\nPorownanie dlugosci:\nTekst oryginalny: %d\nTekst zakodowany: %d\n\nKompresja = %d %% \n", suma_czestosc * 4, kompresja, 100*kompresja/(suma_czestosc*4) );


	return 0;

}

