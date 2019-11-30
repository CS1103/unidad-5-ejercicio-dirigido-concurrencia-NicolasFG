#ifndef PD4_MATRIZ_CONCURRENTE_H
#define PD4_MATRIZ_CONCURRENTE_H
#include<vector>
#include <iostream>
#include <sys/time.h>
#define NUM_HILOS 2
using namespace std;


template <typename T>
vector<vector<T>> matriz1;
template <typename T>
vector<vector<T>> matriz2;
template <typename T>
vector<vector<T>> matriz3;



template<typename T1>
class Matriz_concurrente {
public:
    int filas{};
    int columnas{};
    vector<vector<T1>> matriz;

    Matriz_concurrente() = default;

    Matriz_concurrente(int filas, int columnas) : filas{filas}, columnas{columnas}{}

    void llenarMatriz(vector<T1>&);
    void imprimirMatriz();
    Matriz_concurrente<T1> operator * (Matriz_concurrente<T1> m);

};

template<typename T1>
void Matriz_concurrente<T1>::llenarMatriz( vector<T1> &c)
{
    for (auto it = c.begin() ; it < c.end();)
    {
        for(auto i=0;i<filas;i++)
        {
            vector<T1> vec;
            for(int j=0;j<columnas;j++)
            {
                vec.push_back(*it);
                it++;
            }
            matriz.push_back(vec);
        }

    }
}


template<typename T1>
void Matriz_concurrente<T1>::imprimirMatriz()
{
    for(int i=0;i<filas;i++)
    {
        for(int j=0;j<columnas;j++)
        {
            cout<<matriz.at(i).at(j)<<" ";
        }
        cout<<endl;
    }
}

struct datos {
    long thread_id;
    int num_filas1;
    int num_columnas1;
    int num_filas2;
    int num_columnas2;
};

struct datos datos_pasar[NUM_HILOS];


template <typename T>
void* multiplicar_paralelo(void* parametros) {

    int j, filas1, columnas1, columnas2,z;
    long i, lim_inf, lim_sup;
    long t;
    struct datos* mis_datos;
    mis_datos=(struct datos*)parametros;
    t = mis_datos->thread_id;
    filas1 = mis_datos->num_filas1;
    columnas1 = mis_datos->num_columnas1;
    columnas2 = mis_datos->num_columnas2;

    if(filas1%NUM_HILOS != 0 && t==NUM_HILOS-1 )
    {
        lim_inf = t * (filas1 / NUM_HILOS);
        lim_sup = (t + 1) * (filas1 / NUM_HILOS) +1;
    }
    else
    {
        lim_inf = t * (filas1 / NUM_HILOS);
        lim_sup = (t + 1) * (filas1 / NUM_HILOS);
    }

    T sum=0;

    for (i = lim_inf; i < lim_sup; i++) {
        for (j = 0; j < columnas2; j++) {
            for (z = 0; z < columnas1; z++) {
                sum += matriz1<T>[i][z]*matriz2<T>[z][j];
            }
            matriz3<T>[i][j]=sum;
            sum=0;
        }
    }

    pthread_exit(nullptr);
}



template<typename T1>
Matriz_concurrente<T1> Matriz_concurrente<T1>::operator * (Matriz_concurrente<T1> m)
{

    if(columnas == m.filas )
    {
        Matriz_concurrente<T1> R =Matriz_concurrente<T1>(filas,m.columnas);
        for(int i=0;i<filas;i++)
        {
            vector<T1> a;
            for(int j=0;j<m.columnas;j++){
                a.push_back(0);
            }
            matriz3<T1>.push_back(a);
        }

        matriz1<T1>  =matriz;
        matriz2<T1>  =m.matriz;

        int rc;
        long t;
        void* status;

        struct timeval start;
        struct timeval finish;


        pthread_t hilos[NUM_HILOS];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        gettimeofday(&start, 0);

        for (t = 0;t < NUM_HILOS; t++) {
            datos_pasar[t].thread_id=t;
            datos_pasar[t].num_filas1=filas;
            datos_pasar[t].num_columnas1=columnas;
            datos_pasar[t].num_filas2=m.filas;
            datos_pasar[t].num_columnas2=m.columnas;
            printf("Creando el hilo %ld \n",t);

            rc = pthread_create(&hilos[t],&attr,multiplicar_paralelo<T1>,(void*)&datos_pasar[t]);

            if (rc) {
                printf("ERROR codigo %d \n",rc);
                exit(-1);
            }


        }

        pthread_attr_destroy(&attr);

        for(t=0;t<NUM_HILOS;t++) {
            rc = pthread_join(hilos[t],&status);
            if (rc) {
                printf("ERROR,codigo %d \n",rc);
                exit(-1);
            }
        }
        gettimeofday(&finish, 0);
        cout<<endl;
        R.matriz = matriz3<T1>;
        R.imprimirMatriz();

        pthread_exit(nullptr);

    }
    else
        throw runtime_error("No se puede hacer la multiplicación");



}


#endif //PD4_MATRIZ_CONCURRENTE_H
