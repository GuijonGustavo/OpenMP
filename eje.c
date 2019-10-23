/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <assert.h>

#define TAMANO 100

void simple(int n, float *a, float *b);

int main()
{

    int n = 6;
    float a[TAMANO];
    float b[TAMANO];

    simple(n, a, b);
    return 0; 

}

void simple(int n, float *a, float *b)
{
    int i;
    #pragma omp parallel for num_threads(2)
    for( i=1; i<n; i++ )
        {
            b[i]=( a[i] + b[i-1] ) / 2.0;
        printf("Checkpoint 1: b[%d] = %f. Thread # %d\n\n", i, b[i], omp_get_thread_num());
        }
        printf("Checkpoint 2: b[%d] = %f. Thread # %d\n\n", i, b[i], omp_get_thread_num());

}



*/

////////////
/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <assert.h>

int main()
{
    int x;
    x = 2;

    #pragma omp parallel num_threads(2) shared(x)
    {
        if(omp_get_thread_num()==0 )
        {
            x = 5;
        }
        else
        {
            printf("1: Hilo# %d: x = %d\n", omp_get_thread_num(),x);
        }
        #pragma omp barrier 
        if (omp_get_thread_num()==0)
        {
            printf("2: Hilo# %d: x = %d\n", omp_get_thread_num(),x);
        }
        else
        {
            printf("3: Hilo# %d: x = %d\n", omp_get_thread_num(),x);
        }
    }
return 0;
}
*/
////////////////Flush 2.2c
//
//
/* Flush es un punto de encuentro que permite asegurar
 * que todos lo threads de un equipo tienen una
 * visión consistente de ciertas variables de
 * memoria.
 *
 * Asegura que las modificaciones hechas por un thread
 * sobre variables visibles por otros threads son efectivas
 * (se han almacenado en memoria y se trabaja con estos
 * valores y no con los valores almacenados en los
 * registros).
 *
 * Un FLUSH proporciona consistencia entre operaciones
 * de memoria del thread actual y la memoria global
 *
 * Para alcanzar consistencia global cada thread debe
 * ejecutar una operación FLUSH
 *
 * Si no se especifica una lista de variables se aplica a
 * todas (podría ser muy costoso)
 *
 *Está presente implícitamente en las siguientes directivas (salvo que esté presente la directiva NOWAIT):
 *•  *BARRRIER,
 *•  *CRITICAL y END CRITICAL,
 *•  *ORDERED y END ORDERED
 *•  *PARALLEL y END PARALLEL,
 *•  *END DO,
 *•  *END SECTIONS,
 *•  *END SINGLE,
 *•  *END WORKSHARE,
 *•  *PARALLEL DO/for y END PARALLEL DO/for,
 *•  *PARALLEL SECTIONS y END PARALLEL SECTIONS,
 *•  *PARALLEL WORKSHARE y END PARALLEL WORKSHARE
 *•  *ATOMIC
 * 

*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <assert.h>

int main()
{
    int data;
    int flag=0;
    
    #pragma omp parallel num_threads(2)
    {
        if (omp_get_thread_num() ==0)	
           {
                data = 42;
       
                #pragma omp flush(flag, data)
               
    	        flag = 1;
    
    	        printf("Checkpoint 1: flag=%d data=%d. Thread # %d\n\n", flag, data, omp_get_thread_num());
                #pragma omp flush(flag)
        
            }
        else if(omp_get_thread_num() == 1)
        
            {
                #pragma omp flush(flag,data)
                
                while(data < 1)
            
                    {
                        #pragma omp flush(flag, data)	
                    }
    
    	        printf("Checkpoint 2: flag=%d data=%d. Thread # %d\n\n", flag, data, omp_get_thread_num());
    
                #pragma omp flush(flag, data)
    
    	        printf("Checkpoint 3: flag=%d data=%d. Thread # %d\n\n", flag, data, omp_get_thread_num());
            }
    }
    return 0;
}
*/

///////////Ejemplo 35.1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <assert.h>
/*
int main()
{
    int i, j;
    int *ptr_i, *ptr_j;
    
    i = 1;
    j = 2;
    
    ptr_i = &i;
    ptr_j = &j;
    
    printf("Checkpoint 1: i=%d y j=%d. Thread #: %d\n\n", i, j, omp_get_thread_num());

    #pragma omp parallel num_threads(8) firstprivate(j) //private(i)

    {
        printf("Checkpoint 2: i=%d y j=%d. Thread #: %d\n\n", i, j, omp_get_thread_num());
        i = 3;
        j = j + 2;
        //assert(*ptr_i == 1 && *ptr_j == 2);
        printf("Checkpoint 3: i=%d y j=%d. Thread #: %d\n\n", i, j, omp_get_thread_num());
    }

   // assert(i == 1 && j == 2);
    printf("Checkpoint 4: i=%d y j=%d. Thread #: %d\n\n", i, j, omp_get_thread_num());
    return 0;
}
*/
///////ejemplo 35.2c

/*
void g(int k); 
void f(int n);
int a;

int main()
{
    int k = 3;
    int n = 48;
    g(k); 
    f(n);
    return 0;
}
   
void g(int k) 
{
    a = k;
}
    
void f(int n)
{
    int a = 0;
    printf("Valor de a antes de entrar en el pragma: %d\n\n", a);
    #pragma omp parallel for private(a)
    for(int i = 1; i < n; i++)
    {
        a = i;
        g(a * 2);
        printf("Valor de a  en el ciclo for: %d\n\n", a);
    }
    printf("Valor de a saliendo del pragma: %d\n\n", a);
}

*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <assert.h>


void priv_example3();

int main()
{

    priv_example3();
    return 0;

}


void priv_example3()
{

    int i, a;

    #pragma omp parallel private(a) num_threads(6)
    {
        printf("Checkpoint 1: a = %d. Hilo# %d\n\n", a, omp_get_thread_num());
    
        a = 1;

        printf("Checkpoint 2: a = %d. Hilo# %d\n\n", a, omp_get_thread_num());
        #pragma omp parallel for private(a)
	for(i = 0; i < 10; i++)
	{
	
            a = 2;	
	
        printf("Checkpoint 3: a = %d. Hilo# %d\n\n", a, omp_get_thread_num());
	}
        //assert(a == 1) ;
        printf("Checkpoint 4: a = %d. Hilo# %d\n\n", a, omp_get_thread_num());
    }

}
*/

/////Firstprivate
/*
El siguiente ejemplo ilustra el tamaño y el valor de los elementos de lista de tipo matriz o puntero en una cláusula firstprivate. El tamaño de los nuevos elementos de la lista se basa en el tipo del elemento de la lista original correspondiente, según lo determine el lenguaje base. 

En este ejemplo:

• El tipo de A es una matriz de dos matrices de dos entradas.

• El tipo de B se ajusta al puntero a la matriz de n ints, porque es un parámetro de función.

• El tipo de C se ajusta al puntero a int, porque es un parámetro de función.

• El tipo de D es una matriz de dos matrices de dos entradas.

• El tipo de E es una matriz de n matrices de n ints.

Hay que tener en cuenta que B y E implican tipos de matriz de longitud variable. Los nuevos elementos del tipo de matriz se inicializan como si cada elemento entero de la matriz original se asignara al elemento correspondiente de la nueva matriz. Los de tipo puntero se inicializan como por asignación del elemento original al nuevo elemento.

firstprivate(valor-i_1, ..., valor-i_N): Cada hilo tiene una copia local del dato. La copia local se inicializa con el valor de la copia global en el momento de encontrarse con la directiva a la que se aplica la cláusula.

De modo que en este A, B,C tienen el mismo valor porque son la misma variable global. Mientras que B y E son de longitud variable porque no se inicializan como variable global.

Esta clausula declara privadas las variables de la lista y además las inicializa a sus valores anteriores (valores en el master). Las variables globales son recogidas por el master.

*/
/*
// Ejemplo 37.1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <assert.h>

void f(int n, int B[n][n], int C[]);

int A[2][2] = {1, 2, 3, 4};

int main()
{

    f(2, A, A[0]);
    return 0;

}

void f(int n, int B[n][n], int C[])
{
    
    int D[2][2] = {1, 2, 3, 4};
    int E[n][n];
    
    assert(n>=2);
    E[1][1] = 4;
    
    printf("Checkpoint 1: A = %d, B = %d, C = %d, D = %d, E = %d. Hilo# %d\n\n", A, B, C, D, E, omp_get_thread_num());
    #pragma omp parallel firstprivate(B, C, D, E) num_threads(8)
    {
    printf("Checkpoint 2: A = %d, B = %d, C = %d, D = %d, E = %d. Hilo# %d\n\n", A, B, C, D, E, omp_get_thread_num());
    
        assert(sizeof(B) == sizeof(int (*)[n]));
        assert(sizeof(C) == sizeof(int *));
        assert(sizeof(D) == 4 * sizeof(int));
        assert(sizeof(E) == n * n * sizeof(int));
        
        assert(&B[1][1] == &A[1][1]);
        assert(&C[3] == &A[1][1]);
        assert(D[1][1] == 4);
        assert(E[1][1] == 4);
    
    }
    
    printf("Checkpoint 3: A = %d, B = %d, C = %d, D = %d, E = %d. Hilo# %d\n\n", A, B, C, D, E, omp_get_thread_num());
}

*/
/////////Lastprivate
//La correcta ejecución a veces depende del valor que la última iteración de un ciclo asigna a una variable. Dichos programas deben enumerar todas esas variables en una última cláusula privada para que los valores de las variables sean los mismos que cuando el bucle se ejecuta secuencialmente.
//
//lastprivate(valor-i_1, ..., valor-i_N): Cada hilo tiene una copia local del dato. La copia global será actualizada por el hilo que ejecuta la última iteración según el orden secuencial de programa.
//
//Declara privadas las variables de
//la lista y además actualiza las variables con su último
//valor al terminar el trabajo paralelo.
//• Son variables computadas dentro del lazo y utilizadas fuera (por
//defecto las variables privadas no existen fuera del lazo)
//• Si una variable se declara como LASTPRIVATE el valor de la
//variable al salir del bucle es el valor que toma en el procesador
//que ejecuta la última iteración del bucle
//
//
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <assert.h>

#define TAMANO 50

void lastpriv(int n, float *a, float *b);

int main()
{
    int n = 11;
    float a[TAMANO];
    float b[TAMANO];

    lastpriv(n, a, b);
    return 0;
}


void lastpriv(int n, float *a, float *b)
{
    int i;
    
    #pragma omp parallel num_threads(9)
    {
        #pragma omp for lastprivate(i)
        for(i = 0; i <n-1; i++)
	{
            a[i] = b[i] + b[i+1];
            printf("Checkpoint 1: a[%d] = %f. Thread # %d\n\n", i, a[i], omp_get_thread_num());
	}
    }
    
     printf("Checkpoint 2: a[%d] = %f. Thread # %d\n\n", i, a[i], omp_get_thread_num());
     a[i] = b[i];
     printf("Checkpoint 3: a[%d] = %f. Thread # %d\n\n", i, a[i], omp_get_thread_num());
}
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <assert.h>

#define TAMANO 10

void reduction1(int *x, int *y, int n);

void main()
{
    int n = 10;
    int x[TAMANO];
    int y[TAMANO];

    reduction1(x, y, n);
}

void reduction1(int *x, int *y, int n)
{
    int i, b, c;
    int a, d;
    
    a = 0;
    b = 0;
    c = y[0];
    d = x[0];
    
    //#pragma omp parallel for num_threads(10) private(i) shared(x, y, n) reduction(^:b) reduction(min:c) reduction(max:d)
    for (i = 0; i < n; i++)
    {
        a += x[i];
        b ^= y[i];
        
        if (c > y[i]) c = y[i];
	
        d = fmaxf(d, x[i]);
	
        printf("Checkpoint 1: a = x[%d] = %d, b = y[%d] = %d, c = y[%d] = %d, d = %d Thread # %d\n\n", i, a, i, b, i, c, d, omp_get_thread_num());
    }
    printf("Checkpoint 2: a = x[%d] = %d, b = y[%d] = %d, c = y[%d] = %d, d = %d Thread # %d\n\n", i, a, i, b, i, c, d, omp_get_thread_num());
    
}
*/
/*
#include <stdio.h>
#include <omp.h>

int main()
{

int x;
x = 2;

#pragma omo parallel num_threads(2) shared(x)
{
    if(omp_get_thread_num() == 0)
    {
        x = 5;
        printf("Checkpoint 1: Thread # %d: x = %d\n\n", omp_get_thread_num(), x);
    }
    else 
    {
    
        printf("Checkpoint 2: Thread # %d: x = %d\n\n", omp_get_thread_num(), x);
    
    }
    
    #pragma omp barrier
    if(omp_get_thread_num() == 0)
    {
         printf("Checkpoint 3: Thread # %d: x = %d\n\n", omp_get_thread_num(), x);
    }
    else 
    {
         printf("Checkpoint 4: Thread # %d: x = %d\n\n", omp_get_thread_num(), x);
    }
}
return 0;
}
*/
/*
#include <stdio.h>
#include <omp.h>
#include<pthread.h>
int main()
{
    
    int flag = 0;
    
    printf("Checkpoint 1: Thread # %d: x = %d\n\n", omp_get_thread_num(), flag);
    //#pragma omp parallel num_threads(3)
    {
    printf("Checkpoint 2: Thread # %d: x = %d\n\n", omp_get_thread_num(), flag);
    
    if(omp_get_thread_num()==0)
    {
        //#pragma omp atomic update
        flag++;
        
        printf("Checkpoint 3: Thread # %d: x = %d\n\n", omp_get_thread_num(), flag);
    }
    else if(omp_get_thread_num()==1)
    {
    
        //#pragma omp flush(flag)
        //while(flag < 1)
        //{
        //    #pragma omp flush(flag)
        //}
    printf("Checkpoint 4: Thread # %d: x = %d\n\n", omp_get_thread_num(), flag);

    //#pragma omp atomic update
    flag++;

    printf("Checkpoint 5: Thread # %d: x = %d\n\n", omp_get_thread_num(), flag);
    }
    
    else if(omp_get_thread_num()==2)
    {
        //#pragma omp flush(flag)
        //while(flag < 2)
        //{
         //   #pragma omp flush(flag)
        //}
        
        printf("Checkpoint 6: Thread # %d: x = %d\n\n", omp_get_thread_num(), flag);
    }
    }
}
*/

#include <stdio.h>
#include <omp.h>
int main()
{

#ifdef _OPENMP
    printf("Checkpoint 1: Thread # %d\n\n", omp_get_thread_num());
#else
    printf("Checkpoint 2: Thread # %d\n\n", omp_get_thread_num());
#endif
return 0;
} 
