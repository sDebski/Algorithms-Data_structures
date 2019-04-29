#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct element {
        int numb;
        char val[30];
} el_hash;

int hash(long int, int, int);
int ifFull(el_hash *, int);
void wypisz(el_hash *, int);
void countdel(el_hash *, int);


int hash(long int k, int i, int m) {
        int wynik = ((k%m) + i * i) % m;
        return wynik;
}


int  ifFull(el_hash *T, int m) {
        int ilosc = 0;
        for (int i = 0; i < m; i++) {
                if (T[i].numb != 0 && T[i].numb != -1)
                        ilosc++;
        }
        return ilosc;
}

void wypisz(el_hash *T, int m) {

        for (int i = 0; i < m; i++) {
                printf("%d. Liczba: %d \nKlucz: %s\n", i + 1, T[i].numb, T[i].val);
        }
        printf("\n\n");

}

void usun(el_hash *T, int m) {
        int licznik = 0;
        int i = 0;
        do {
                if (T[i].numb != 0) {
                        if (licznik % 2 == 1){
                                T[i].numb = -1;

                                for (int j = 0; j < 30; j++) {
                                        T[i].val[j] = 0;
                                }

                        }
                        licznik++;

                }
                i++;
        } while ((float)ifFull(T, m)>0.4*m );
}

void countdel(el_hash *T, int m) {
        int il = 0;
        for (int i = 0; i < m; i++) {
                if (T[i].numb == -1)
                        il++;

        }
        printf ("\nIlosc usunietych = %d\n",il);
}


int main() {

        for (int i = 0; i < 6; i++) {
                el_hash *T;

                int m;

                if (i == 0) {
                        m = 10;
                }

                if (i == 1) {
                        m = 400;
                }

                if (i == 2) {
                        m = 500;
                }

                if (i == 3) {
                        m = 600;
                }

                if (i == 4) {
                        m = 700;
                }

                if (i == 5) {
                        m = 800;
                }

                if (i == 6) {
                        m = 3000;
                }


                int licznik = 0;

                T = (el_hash *)calloc(m,sizeof(el_hash));

                 if(T != NULL){
                        printf("udalo sie zaalokowac pamiec\n");
                }

                FILE *file = fopen("nazwiska.txt", "r");

                if (file == NULL) {
                if (file == NULL) {
                        printf("blad otwarcia pliku");
                        return 1;

                }
                int liczba;
                char slowo[30];

                for (int j = 0; j < 30; j++)
                        slowo[j] = 0;

                long int wynik;
                int licz = 0;
                while ( (float)ifFull(T,m) < 0.8*(float)m) {
                        fscanf(file, "%d", &liczba);
                        fscanf(file, "%s", slowo);
                        //printf("%d udalo sie zczytac wyrazenie\n", licz++);
                        int blad = 0;
                        licznik = 2;
                        wynik = 0;

                        wynik = (int)slowo[0] *10+ (int)slowo[1] ;
                        do {
                                wynik = wynik * 10 +(int)slowo[licznik];

                                if (wynik < 0) {
                                        blad = 1;
                                        break;
                                }

                                licznik++;
                        } while (slowo[licznik] != 0);

                        if (blad != 1) {
                                int skok = 0;
                                while (1) {
                                        if (T[hash(wynik, skok, m)].numb == 0) {

                                                T[hash(wynik, skok, m)].numb = liczba;
                                                strcpy(T[hash(wynik, skok, m)].val, slowo);
                                                break;
                                        }
                                        else
                                                skok++;

                                }
                        }

                        for (int j = 0; j < 30; j++)
                                slowo[j] = 0;
                }

                for (int j = 0; j < 30; j++)
                        slowo[j] = 0;


                if (i == 0) {
                        wypisz(T, m);
                }

                usun(T, m);

                if (i == 0) {
                        wypisz(T, m);
                }
                countdel(T, m);


                ////////////////////////

                while ((float)ifFull(T, m) < 0.8*(float)m) {

                        fscanf(file, "%d", &liczba);
                        fscanf(file, "%s", slowo);
                        int blad = 0;
                        licznik = 2;

                        wynik = 0;
                        wynik = (int)slowo[0] * 10 + (int)slowo[1];
                        do {
                                wynik = wynik * 10 + (int)slowo[licznik];

                                if (wynik < 0) {
                                        blad = 1;
                                        break;
                                }

                                licznik++;
                        } while (slowo[licznik] != 0);

                        if (blad != 1) {
                                int skok = 0;
                                while (1) {
                                        if (T[hash(wynik, skok, m)].numb == 0 || T[hash(wynik, skok, m)].numb == -1) {

                                                T[hash(wynik, skok, m)].numb = liczba;
                                                strcpy(T[hash(wynik, skok, m)].val, slowo);
                                                break;
                                        }
                                        else
                                                skok++;

                                }
                        }


                        for (int j = 0; j < 30; j++)
                                slowo[j] = 0;
                }

                fclose(file);



                if (i == 0) {
                        wypisz(T, m);
                }

                countdel(T, m);

                if (i != 0) {
                        printf("\nPowy¿sze dzialania przeprowadzone na m = %d \n", m);
                }

                free(T);


        }

        return 0;

}











