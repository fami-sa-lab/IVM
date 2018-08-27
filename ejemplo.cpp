/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Vostro-2
 *
 * Created on 26 de julio de 2018, 03:58 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "includes/leer_ArchivosTxt.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    int valor =leer_VarProg(NUM_MAQ); 
    printf("la Funcion me devolvio = %d \n",valor);
    valor =leer_VarProg(PESO_A);
  /*  printf("la Funcion me devolvio = %d \n",valor);
    valor =leer_VarProg(PESO_B);
    printf("la Funcion me devolvio = %d \n",valor);
    valor =leer_VarProg(PESO_C);
    printf("la Funcion me devolvio = %d \n",valor);
    valor =leer_VarProg(PESO_D);
    printf("la Funcion me devolvio = %d \n",valor);
    valor =leer_VarProg(PRECIO_D);
    printf("la Funcion me devolvio = %d \n",valor);
    valor =leer_VarProg(PRECIO_C);
    printf("la Funcion me devolvio = %d \n",valor);
    valor =leer_VarProg(SERIE_MDB);
    printf("la Funcion me devolvio = %d \n",valor);
    valor =leer_VarProg(SERIE_CORTES);
    printf("la Funcion me devolvio = %d \n",valor);*/
    return 0;
}

