// wskazowka do sortowania pozycyjnego
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MDN 254 // maks. dlugosc napisu
#define MN 10 // maks il napisow

int ilosc;
int MaxDlugosc;


char **A, **T, **B;
int Rozmiar[10];
int RozmTMP[10];
int Czysc[10];

void drukuj();
void czytaj();
void UstalDlugosc();
void Sortuj();
int CharNaInt( int dlugosc, int indeks);


void drukuj() {
	// drukuje  drugie litery napisow i napisy  
	int i;
	for (i = 0; i<ilosc; i++) {
		printf("%s", A[i]);
		//printf("%c %s", *(A[i] + 1), A[i]);
		//czyli   printf("%c %s",*(*(A+i)+1),*(A+i));  
		printf("\n");
	}
}

void czytaj() {
	char slowo[MDN];
	int i = 0;
	for (i = 0; i<ilosc; i++) {
		scanf("%15s", slowo);
		A[i] = (char*)malloc(sizeof(char)*MDN);
		B[i] = (char*)malloc(sizeof(char)*MDN);
		T[i] = (char*)malloc(sizeof(char)*MDN);
		strcpy(A[i], slowo);
	}
}

void UstalDlugosc() {
	int tmp = 0;
	for (int i = 0; i < ilosc; i++) {
		if ((int)strlen(A[i]) > tmp)
			tmp = (int)strlen(A[i]) ;
		Rozmiar[i] = (int)strlen(A[i]);

	}

	MaxDlugosc = tmp;
}


void Sortuj() {
	printf("MaxDlugosc = %d\n", MaxDlugosc);
	int C[27];
	for (int z = MaxDlugosc - 1; z >= 0; z--) {
		
		printf("sortuje po literze %d\n", z);
		int MaxZnak = CharNaInt(z, 0);
		for (int i = 1; i < ilosc; i++) {
			if (MaxZnak < CharNaInt(z, i))
				MaxZnak = CharNaInt(z, i);
		}

		
		printf("wyznaczam maxznak = %d\n", MaxZnak);
		// CountingSOrt
		for (int i = 0; i <= MaxZnak; i++)
			C[i] = 0;

		for (int i = 0; i < ilosc; i++)
			C[CharNaInt(z, i)]++;

		for (int i = 1; i <= MaxZnak; i++)
			C[i] += C[i - 1];
		printf("\n3.\n");
		drukuj();
		for (int i = ilosc -1 ; i >= 0; i--) {
			C[CharNaInt(z, i)] -= 1;
			strcpy(B[C[CharNaInt(z, i)]],A[i]);
			RozmTMP[C[CharNaInt(z, i)]] = Rozmiar[i];

		}

		printf("4.\n");
		printf("drukuj A normalne: \n");
		drukuj();

		for (int i = 0; i < ilosc; i++)
			strcpy(A[i], B[i]);
			
		for(int i = 0; i<ilosc; i++)
			Rozmiar[i] = RozmTMP[i];

		for (int i = 0; i<ilosc; i++)
			RozmTMP[i] = Czysc[i];

		printf("\n");
		printf("drukuj A po podlozeniu pod nie B \n");
		drukuj();
		printf("\nDrukuj tablice rozmiarow\n");
		for (int i = 0; i < ilosc; i++)
			printf("Rozmiar[%d] = %d\n", i, Rozmiar[i]);
		

		for (int i = 0; i < 27; i++)
			C[i] = 0;
		
		for (int i = 0; i < ilosc; i++)
			strcpy(B[i], T[i]);
	}
}

int CharNaInt (int nrLitery, int indeks) {
	if (Rozmiar[indeks] < nrLitery)
		return 0;
	char znak = *(A[indeks] + nrLitery);

	if ((int)znak >= 48 && (int)znak <= 57)
		return (int)znak-47;
	if ((int)znak >= 65 && (int)znak <= 90)
		return (int)znak - 64;
	if ((int)znak >= 97 && (int)znak <= 122)
		return (int)znak - 96;
}

int main() {
	printf("Podaj ile wyrazow chcesz: (max 10)\n");
	scanf("%d", &ilosc);

	A = (char**)malloc(ilosc * sizeof(char*));
	B = (char**)malloc(ilosc * sizeof(char*));
	T = (char**)malloc(ilosc * sizeof(char*));

	printf("tablica A: \n"); czytaj();
	UstalDlugosc();

	for (int i = 0; i < ilosc; i++) {
		printf("\nRozmiar[%d] = %d\n", i, Rozmiar[i]);
	}
	Sortuj();

	printf("\ntablica A po sortowaniu: \n");
	drukuj();

	return 0;
}

