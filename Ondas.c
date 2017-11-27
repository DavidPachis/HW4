//este script es para resolveer la ecuacion de onda 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define c  250.0
#define n_puntos  129.0
#define n_puntost 100000.0
#define t2 50000
#define t4 25000
#define t8 12500
#define PI 3.14159265
#define L 0.64
//#define Ny
//#define Nx
void Solve1D (double *x, double *A,double *B);
void Solve1DP (double *x, double *A,double *B);
//void Solve2D (double *M,double *N);
//double **Matrix(void)

int main(void)
{ 
 int i; 
 double *A,*x,*B;
 //double **M;
 int r;
 x = malloc(n_puntos * sizeof(double));
 A = malloc(n_puntos * sizeof(double)); 
 B = malloc(n_puntos * sizeof(double));
// double **M = Matrix();

 //for (i = 0; i < Ny; i++)
   // {
//        for (j = 0; j < Nx; j++)
  //      {
  //          M[i][j] = (double) 0;
  //      }
  //  }

 FILE *in;
 float var;
 char filename[100]="cond_ini_cuerda.dat";

 in = fopen(filename, "r");
 if(!in)
 {
  printf("la habeis cagado abriendo el archivo tio %s\n", filename);
  exit(1);
 }
 //printf("ahora si, como asi que como asi que como fue \n");
 
 for (i=0;i<n_puntos;i++)
 {
   fscanf(in, "%f", &var);
   x[i] = var;
   fscanf(in, "%f\n", &var);
   A[i] = var;
   B[i] = var;
 }
 
 //fclose(in);
// FILE *in;
// float var;
 //char filename2[100]="cond_ini_tambor.dat";

// in = fopen(filename2, "r");
 //if(!in)
 //{
  //printf("la habeis cagado abriendo el archivo tio %s\n", filename2);
  //exit(1);
// }
 //printf("ahora si, como asi que como asi que como fue \n");

  //for (i = 0; i < Ny; i++)
  //  {
  //      for (j = 0; j < Nx; j++)
  //      {
  //          M[i][j] = (double) 0;
  //         fscanf(in, "%f", &var);
  // x[i] = var;
 //  fscanf(in, "%f\n", &var);
  // A[i] = var;
   //B[i] = var;
        //}
    //}
  

   
 
 
 //fclose(in);


 Solve1D (x, A, B);
 Solve1DP (x, A, B); 
 //Solve2D (M,N);
 //printf ("no la habeis cagado tio \n");
 return 0;
}
void Solve1D (double *x, double *A,double *B)
{   
    double delta_x = x[3]-x[2];
    double delta_t = 1.0/n_puntost;
    //printf("%d/%f=%f\n",1,n_puntos,delta_x);
    //printf("%f\n",delta_x);
    double r;
    double r2;
    r = c * delta_t / delta_x;
    double *A_future, *A_present,*A_copia;
    double *TMedios, *TCuartos, *TOctavos;
    A_future = malloc(n_puntos * sizeof(double));
    A_present= malloc(n_puntos * sizeof(double));
    TMedios  = malloc(n_puntos * sizeof(double));
    TCuartos = malloc(n_puntos * sizeof(double));
    TOctavos = malloc(n_puntos * sizeof(double));
    int i;
    int j;
    int tamano = n_puntos-1;
    r2 = r*r;
    //printf("%f\n",r2);
    
    for(i = 0; i < n_puntos; i++)
     {
       // primer paso para generar un pasado 
       if (i==0)
        {
         //A_present[i] = A[i]+r2*0.5*(A[i+1]-2*A[i]+A[i-1]) no tiene vecino -, y como esta fijo pues es el mismo 
         A_present[i] = A[i];
         A_present[tamano] = A[i];   
             
        }
       else if(i==n_puntos-1)
        {
         //A_present[i] = A[i]+r2*0.5*(A[i+1]-2*A[i]+A[i-1]) no tiene vecino +,y como esta fijo pues es el mismo
         A_present[i] = A[i];
        } 
       else
        {
         A_present[i] = A[i]+r2*0.5*(A[i+1]-2*A[i]+A[i-1]);
         //printf("caso %d %f =%f+ %f* %f* %f- %f*%f+%f \n",i,A_present[i],A[i],r2,0.5,A[i+1],2.0,A[i],A[i-1]);
        }   
     }
    for (j=0;j<n_puntost;j++)
     {
     //este for es para contruir un futuro, 129 veces y guardar solo el que me piden
      for (i=0; i < n_puntos; i++)
       {
         // este for es para crear el estado en un tiempo t+1 de cada punto de la cuerda, y queda gurdado en future
         if (i==0)
          { 
           //como esta fijo pues es el mismo
           A_future[i] = A_present[i];
           A_present[tamano] = A[i];
          }
         else if(i==n_puntos-1)
         {
           //como esta fijo pues es el mismo
           A_future[i] = A_present[i];
         }
         else
         {
          A_future[i] = 2*(1-r2)*A_present[i]-A[i]+r2*(A_present[i+1]+A_present[i-1]);
           //printf("%f caso %d %d\n",A_future[i],i,j);
         }      
       }
      if (j==t2)
       {
         printf("t/2\n");
         for (i=0; i < n_puntos; i++)
             {
              TMedios[i]=A_present[i];
              printf("%f\n",TMedios[i]);
             }
        //printf("se guardaron los datos de t/2\n");
       }
      if (j==t4)
       {
         printf(" t/4\n");
         for (i=0; i < n_puntos; i++)
             {
                 TCuartos[i]=A_present[i];
                 
                 printf("%f\n",TCuartos[i]);
             }  
          //printf("se guardaron los datos de t/4\n");
       }
      if (j==t8)
       {
         printf(" t/8\n");
         for (i=0; i < n_puntos; i++)
             {
                TOctavos[i]=A_present[i];
                
                printf("%f\n",TOctavos[i]);
             }
          // printf("se guardaron los datos de t/8\n");
       }
       
      for (i=0; i < n_puntos; i++)
       {
               A[i] = A_present[i];
               A_present[i] = A_future[i];
       }
      //printf("se paso al siguiente ciclo %d\n",j);
      
    }
  //aca creo un archivo para los datos de los diferentes periodos  
 FILE *in;
 char filename[100]="new_dataCuerda.dat";

 in = fopen(filename, "w");
 if(!in)
 {
  printf("la habeis cagado abriendo el archivo tio %s\n", filename);
  exit(1);
 }
 for (i=0;i<n_puntos;i++)
  {
    fprintf(in, "%f %f %f %f %f\n",x[i],B[i],TOctavos[i],TCuartos[i],TMedios[i]);
  }
 fclose(in);
 printf ("FIN \n");
}

void Solve1DP (double *x, double *A,double *B)
{ 
    double delta_x = x[3]-x[2];
    double delta_t = 1.0/n_puntost;
    double r;
    double r2;
    r = c * delta_t / delta_x;
    double *A_future, *A_present,*A_copia;
    double *TMedios, *TCuartos, *TOctavos;
    A_future = malloc(n_puntos * sizeof(double));
    A_present= malloc(n_puntos * sizeof(double));
    TMedios  = malloc(n_puntos * sizeof(double));
    TCuartos = malloc(n_puntos * sizeof(double));
    TOctavos = malloc(n_puntos * sizeof(double));
    int i;
    int j;
    int t =0; 
    int tamano = n_puntos-1; 
    r2 = r*r;
    //printf("%f\n",r2);
    
// primer paso para generar PRESENTE a partir un pasado de consiciones iniciales 
    for(i = 0; i < n_puntos; i++)
     {
       
       if (i==0)
        {
         //A_present[i] = A[i]+r2*0.5*(A[i+1]-2*A[i]+A[i-1]) no tiene vecino -, y como esta fijo pues es el mismo 
         A_present[i] =sin((2*PI*c/L)); 
         B[i]= 0;    
        }
       else if(i==n_puntos-1)
        {
      //A_present[i] = A[i]+r2*0.5*(A[i+1]-2*A[i]+A[i-1]) no tiene vecino y va atener una perturbacion dada por sin((2pic/L)*t)
         A_present[i] = A[i];
         B[i]= 0;
        } 
       else
        {
         A[i]=0;
         A_present[i] = A[i]+r2*0.5*(A[i+1]-2*A[i]+A[i-1]);
         
         B[i]= 0;
         //printf("caso %d %f =%f+ %f* %f* %f- %f*%f+%f \n",i,A_present[i],A[i],r2,0.5,A[i+1],2.0,A[i],A[i-1]);
        }   
     }
    for (j=1;j<n_puntost;j++)
     {
     //este for es para contruir un futuro, 129 veces y guardar solo el que me piden
      for (i=0; i < n_puntos; i++)
       {
         // este for es para crear el estado en un tiempo t+1 de cada punto de la cuerda, y queda gurdado en future
         if (i==0)
          { 
           //como esta fijo pues es el mismo
           A_future[i] = A_present[i]+sin((2*PI*c/L)*j);
           
          }
         else if(i==n_puntos-1)
         {
           //acá le introdusco la perturbacion
           A_future[i] = A_present[i];
         }
         else
         {
          A_future[i] = 2*(1-r2)*A_present[i]-A[i]+r2*(A_present[i+1]+A_present[i-1]);
           //printf("%f caso %d %d\n",A_future[i],i,j);
         }      
       }
      if (j==t2)
       {
         printf("t/2\n");
         for (i=0; i < n_puntos; i++)
             {
              TMedios[i]=A_present[i];
              printf("%f\n",TMedios[i]);
             }
        //printf("se guardaron los datos de t/2\n");
       }
      if (j==t4)
       {
         printf(" t/4\n");
         for (i=0; i < n_puntos; i++)
             {
                 TCuartos[i]=A_present[i];
                 
                 printf("%f\n",TCuartos[i]);
             }  
          //printf("se guardaron los datos de t/4\n");
       }
      if (j==t8)
       {
         printf(" t/8\n");
         for (i=0; i < n_puntos; i++)
             {
                TOctavos[i]=A_present[i];
                
                printf("%f\n",TOctavos[i]);
             }
          // printf("se guardaron los datos de t/8\n");
       }
       
      for (i=0; i < n_puntos; i++)
       {
               A[i] =A_present[i];
               A_present[i] = A_future[i];
       }
      //printf("se paso al siguiente ciclo %d\n",j);
      
    }
  //aca creo un archivo para los datos de los diferentes periodos  
 FILE *in;
 char filename[100]="new_dataCuerdaPertur.dat";

 in = fopen(filename, "w");
 if(!in)
 {
  printf("la habeis cagado abriendo el archivo tio %s\n", filename);
  exit(1);
 }
 for (i=0;i<n_puntos;i++)
  {
    fprintf(in, "%f %f %f %f %f\n",x[i],B[i],TOctavos[i],TCuartos[i],TMedios[i]);
  }
 fclose(in);
 printf ("FIN \n");
}
//void Solve2D (double *M,double *B)
//{ 
// 
//}
//double **Matrix(void)
//{
//    int i;
//    double **matrix;
//    matrix = malloc(Ny*sizeof(double *));

//    for(i = 0; i < Ny; i++)
//    {
//        matrix[i] = malloc(Nx*sizeof(double));
//    }

  //  return matrix;
//}

