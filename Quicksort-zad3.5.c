#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MLD 1000000000.0

int Partition(int[], int, int);
void Quicksort(int[], int, int);
int* utworz_tablice_randomowa(int , int * );
int* utworz_tablice_pesymistyczna(int , int *);
void Babelek_Sort(int[], int, int );
void Quicksort_Babel(int [], int, int, int);


int Partition(int A[], int p, int r){
        int x = A[r];
        int i = p-1;
        for( int j = p; j<=r; j++){
                if(A[j]<=x){
                        i++;
                        int pomoc = A[i];
                        A[i] = A[j];
                        A[j] = pomoc;
                }
        }
        if(i<r) return i;
        else return i-1;
}




void Quicksort(int A[], int p, int r){
        if(p<r){
                int q = Partition(A, p, r);
                Quicksort(A, p ,q);
                Quicksort(A, q+1, r);
        }
}


int * utworz_tablice_pesymistyczna(int n, int *Tablica){
int i;
    Tablica = (int *)calloc(n,sizeof(int));
    for(i=0;i<n;i++){
        Tablica[i]=n-i;
    }
return Tablica;
}

void Quicksort_Babel(int A[], int p, int r, int c){
        if(p<r){
                if(r-p+1 < c)
                        Babelek_Sort(A, p , r);
                else{
                        int q = Partition(A, p , r);
                        Quicksort(A, p, q);
                        Quicksort(A, q+1, r);
                }
        }

}




int* utworz_tablice_randomowa(int n, int *Tablica){
    int i;
    Tablica = (int *)calloc(n,sizeof(int));
    for(i=0;i<n;i++){
        Tablica[i] = (( rand() % n) + 1);
    }
   return Tablica;
}

void Babelek_Sort(int A[], int p , int r){
        int i,j;
        for ( i = p; i< r; i++){
                for(j=p; j<r; j++) {
                        if(A[j]>A[j+1]){
                                int pomoc = A[j];
                                A[j] = A[j+1];
                                A[j+1] = pomoc;
                        }
                }
        }

}

void Wypisz(int A[], int size){
        for(int i = 0; i< size; i++){
                printf("%3d", A[i]);
        }

}



int main(){


  int* A = NULL;
  struct timespec tp0, tp1;
  struct timespec tp2 , tp3;
  double Tn,x, Tn2;
  double c;
  int n;


   printf("Tablica B przed posortowaniem: \n");
   int B[]= { 4,7,2,9,1,9,5};
   Wypisz(B,7);
   Babelek_Sort(B, 0, 6);
   printf("\nTablica B po posortowaniu Babelkowym\n");
        Wypisz(B,7);

   printf("\nTablica C przed posortowaniem: \n");
   int C[]= {7,2,9,13,5,2,8};
        Wypisz(C,7);



  printf("\n\nDane Losowe:\n");
  printf("Rozmiar tablicy  |  Quicksort      |  Quicksort + Bb    \n");

 for(n=1000; n<3000; n +=500){

        c = n/2;
        A = utworz_tablice_randomowa(n, A);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
        Quicksort(A, 0, n-1);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
        free(A);

        A = utworz_tablice_randomowa(n, A);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp2);
        Quicksort_Babel(A, 0, n-1, c);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp3);

        free(A);


        Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
        Tn2=(tp3.tv_sec+tp3.tv_nsec/MLD)-(tp2.tv_sec+tp2.tv_nsec/MLD);

        printf("   n: %5d      |  czas: %3.5lf  |  czas: %3.5lf\n",n, Tn, Tn2);


}


  printf("Dane Pesymistyczne:\n");
  printf("Rozmiar tablicy  |  Quicksort      |  Quicksort + Bb    \n");

for(n=1000; n<3000; n +=500){

        c = n/2;

        A = utworz_tablice_pesymistyczna(n, A);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
        Quicksort(A, 0, n-1);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

        free(A);

        A = utworz_tablice_pesymistyczna(n, A);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp2);
        Quicksort_Babel(A, 0, n-1, c);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp3);

        free(A);

        Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
        Tn2=(tp3.tv_sec+tp3.tv_nsec/MLD)-(tp2.tv_sec+tp2.tv_nsec/MLD);

        printf("   n: %5d      |  czas: %3.5lf  |  czas: %3.5lf\n",n, Tn, Tn2);


}


return 0;

}


