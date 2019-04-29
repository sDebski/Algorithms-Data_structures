
   #include<stdio.h>
   #include<stdlib.h>
   #define MDN 256
   
   int **c;
   int **b;
   void LCS_Length(int *x,int *y,int m,int n){
  
   for(int i = 0;i<= m;i++){
           c[i][0] = 0;
  }
  for(int j = 1;j<=n;j++){
                  c[0][j] = 0;
  }
  for(int i = 1;i<=m;i++){
          for(int j=1;j<=n;j++){
                  if(x[i]==y[j]){
                          c[i][j] = c[i-1][j-1]+1;
                          b[i][j] = '\\';
                  }
                  else if(c[i-1][j] >= c[i][j-1]){
                          c[i][j] = c[i-1][j];
                          b[i][j] = '|';
                  }
                  else{
                          c[i][j] = c[i][j-1];
                          b[i][j] = '-';
                  }
          }
  }
  }
  void PrintLCS(int *x, int *y, int i,int j){
          if(i==0 || j==0){
                  return;
          }
          if(b[i][j] == '\\'){
                  PrintLCS(x,y,i-1,j-1);
                  printf("%d",x[i]);
          }
  else if(b[i][j] == '|'){
          PrintLCS(x,y,i-1,j);
  }
  else{
          PrintLCS(x,y,i,j-1);
  }
  }


  int main(){
         int m, n;
        printf("\nPodaj rozmiary dwoch ciagow: ");
        scanf("%d%d", &m,&n);
         int* x = (int*)calloc(MDN + 1, sizeof(int));
         int* y = (int*)calloc(MDN + 1, sizeof(int));

        printf("\nPodaj pierwszy ciag liczb: ");
         for(int i=1;i<=m;i++){
         scanf("%d", &x[i]);
         }
        printf("\nPodaj drugi ciag liczb: ");
         for(int i=1;i<=n;i++){
         scanf("%d", &y[i]);
  }
          b = (int**)calloc(MDN + 1, sizeof(int*));
          c = (int**)calloc(MDN + 1, sizeof(int*));
          for(int i=0;i<=MDN;i++){
                  b[i]=(int*)calloc(MDN + 1, sizeof(int));
                 c[i]=(int*)calloc(MDN + 1, sizeof(int));
         }

         LCS_Length(x,y,m,n);
        printf("\nWspolny podciag: ");
         PrintLCS(x,y,m,n);
 printf("\n");
 }

