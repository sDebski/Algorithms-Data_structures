#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void Heapify(int A[], int rozmiar);
void BuildHeap(int A[], int rozmiar);
void HeapSort(int A[], int rozmiar);

int RozmiarKopca = 0;

void Heapify(int A[], int rozmiar){

        int largest = rozmiar;
        int l= 2*rozmiar+1; // lewy syn
        int r= 2*rozmiar+2; // prawy syn
        if(l<=RozmiarKopca && A[l]>A[rozmiar])
                largest = l;
        if (r<=RozmiarKopca && A[r]>A[largest])
                largest = r;
        if (largest != rozmiar ){
                int pomoc=A[rozmiar];
                A[rozmiar]=A[largest];
                A[largest]=pomoc;
                Heapify(A, largest);
        }
}


void BuildHeap(int A[], int rozmiar){
        RozmiarKopca=rozmiar-1;
        for (int i = RozmiarKopca/2 - 1; i>=0 ;i--)
        Heapify(A, i);
}


void HeapSort(int A[], int rozmiar){
        BuildHeap(A, rozmiar);
        for( int i = rozmiar -1; i >= 0; i--){
                int pomoc = A[0];
                A[0] = A[i];
                A[i] = pomoc;
                RozmiarKopca--;
                Heapify(A, 0);
	}
}


int main(){

  char *s = NULL;
  int licznik = 0;
  int liczba;
  int A[30];

  FILE *file = fopen("liczby.txt", "r" );

  if(file == NULL){
  printf("blad otwarcia pliku");
  return 1;

  }

  while( fscanf(file,"%d", &liczba) == 1 ){
                A[licznik++] = liczba;
  }

  fclose(file);

  HeapSort(A,licznik);

  for(int i = 0; i<licznik; i++)
  printf("%d\t",A[i]);


  FILE *zapisz = fopen("wynik.txt", "w");

  for( int i = 0; i<licznik ;i++)
        fprintf(zapisz, "%d\n", A[i]);

  fclose(zapisz);


return 0;

}

