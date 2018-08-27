/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "leer_ArchivosTxt.h"

char ruta_Nombre[] = NOMBRE_DIRECCION;
using namespace std;


int leer_VarProg(int variable) 
{
    FILE *miArchivo;
    char caracteres[50];
    char valores[10];
    unsigned int contador = 0;
    unsigned int a =0;
    unsigned int b =0;
    int valores_enteros=0;
  //  miArchivo = fopen("lectura_prueba.txt","r");                                //prueba PC
    miArchivo = fopen(ruta_Nombre,"r");                                           //Beagle
    if(miArchivo == NULL)
    {
        //cout << "no se pudo abrir el archivo "<< endl;
        return -1;
    }
    else
    {
        //cout << "\nAbri el archivo en modo lectura" << endl;
        cout << endl;
        //Leemos renglones del archivo hasta llegar a la variable que por parametro
        //se nos pidio
        for(unsigned int i = 0; i < (variable + 1); i++)
        {
            fgets(caracteres,50,miArchivo);                                     //para leer un renglon de archivo
        }
        //printf("El renglon que analizaremos es el siguiente :  ");
        //printf("%s",caracteres);                                                //imprimimos el arreglo caracteres
        asm("nop");
        //Recorremos el arreglo  de caracteres en busca del signo de = para leer el valor de la variable
        for(unsigned char i =0; i < (sizeof(caracteres) / sizeof(caracteres[0])); i++)
        {
            asm("nop");
            if(caracteres[i] == '=')
            {
                contador = i;                                                   //Guardamos la posicion del arreglo donde se encuentra el =
            }
            if(caracteres[i] == '\n')
            {
                i = (sizeof(caracteres) / sizeof(caracteres[0])) ;              //Si encontramos el salto de linea antes que el "=" salimos del for                                             //Guardamos la posicion del arreglo donde se encuentra el =
            }
        }
        if(contador != 0)
        {
            b = contador +2;                                                    //sumamos dos a la posicion donde se encuentra el "=" en el arreglo
            do
            {
                valores[a] = caracteres[b];                                     //Guardamos el valor de la variable en el arreglo valores
                a++;
                b++;
                asm("nop");
            }
            while(caracteres[b] != '\n');                                       //Hacemos esto hasta que nos encontremos el salto de linea(enter)
            asm("nop");
            //imprimimos los valores de la variable (Lo que esta despues del igual)
            /*for(unsigned int i =0; i < a; i++)
            {
                printf("%c",valores[i]);
            }*/
            asm("nop");
            valores_enteros = parseInt(valores,(a-1));                          //Pasamos del arreglo de char a un entero
            //printf("El valor convertido a entero es = %d \n",valores_enteros);
            a  =0;
            b =0;
            contador =0;
            rewind(miArchivo);
            fclose(miArchivo);
            asm("nop");
            return valores_enteros;
        }
        else
        {
            //cout << "Esta renglon no contiene una variable de calibracion" << endl;
            return -1;
        }
    }
}

//Recibe como parametro un arreglo de caracteres y regresa el entero que representan esos caracteres
int parseInt(char arreglo[], int len)
{
    int sum = 0;
    for (int x = 0; x < len; x++)
    {
        int n = arreglo[len - (x + 1)] - '0';                                   //Se resta el '0' para tener el valor del numero y no del valor en ASCII
        sum = sum + powInt(n, x);
    }
    return sum;
}

//Recibe como parametro un entero y la potencia a la que debe de ser elevada
int powInt(int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        x *= 10;
    }
    return x;
}