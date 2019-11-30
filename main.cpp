#include <iostream>
#include <vector>
#include "matriz_concurrente.h"
#include "lectura.h"
#include <ctime>
using namespace std;

int main() {

    //Matrices para el primer ejemplo
//    Matriz_concurrente<int> ma1;
//    Matriz_concurrente<int> ma2;
    //Matrices para el segundo ejemplo
//    Matriz_concurrente<int> ma3;
//    Matriz_concurrente<int> ma4;
    //Matrices para el tercer ejemplo
//    Matriz_concurrente<int> ma5;
//    Matriz_concurrente<int> ma6;
    //Matrices para el cuarto ejemplo
    Matriz_concurrente<float> ma7;
    Matriz_concurrente<float> ma8;


//    Read("ejemplo1.txt", ma1, ma2);
//    cout << "Lectura ejemplo1";
//    cout <<endl;
//    Matriz_concurrente<int> ma_resultado;
//    ma_resultado = ma1 * ma2;
//    ma_resultado.imprimirMatriz();

    cout <<endl;
    cout <<endl;

//    Read("ejemplo2.txt", ma3, ma4);
//    cout << "Lectura ejemplo2";
//    cout <<endl;
//    Matriz_concurrente<int> ma_resultado2;
//    ma_resultado2 = ma3 * ma4;
//    ma_resultado2.imprimirMatriz();

    cout <<endl;
    cout <<endl;

//    Read("ejemplo3.txt", ma5, ma6);
//    cout << "Lectura ejemplo3";
//    cout <<endl;
//    Matriz_concurrente<int> ma_resultado3;
//    ma_resultado3 = ma5 * ma6;
//    ma_resultado3.imprimirMatriz();

    cout <<endl;
    cout <<endl;

    Read("ejemplo4.txt", ma7, ma8);
    cout << "Lectura ejemplo4";
    cout <<endl;
    Matriz_concurrente<float> ma_resultado4;
    ma_resultado4 = ma7 * ma8;
    ma_resultado4.imprimirMatriz();



    return 0;
}