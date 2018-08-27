/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Isaac
 *
 * Created on 24 de abril de 2018, 11:39 AM
 */

/*
 * 03/08/18
 * TODO: 
 *      Procesar polls debidamente (casos donde reporta mas de un estado) actualmente solo proceso el primero.
 *      Esto puede causar que pierda billetes.
 * 
 *      Responder ante mensajes de error de los perif'ericos y mostrar los mas importantes en pantalla.
 * 
 *      Implementar LOGS (base de datos o con equivalente a printf redireccionando stdio a un archivo o fprintf).
 * 
 *       Implementar interfaz para modificar precios
 * 
 *      Implementar otro metodo de cortes. (crear pdfs en BBB y transmitir por area local, pagina web en beaglebone)
 *          
 * 
 */


#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "includes/VendingMachineController.h"

#define __100MS     CLOCKS_PER_SEC/10 

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int selectedItem = -1; //boton del articulo seleccionado
    //int *item = &selectedItem; //apuntador a articulo seleccionado
    int result = -1;
    struct vendingState_s vendingResult;
    clock_t anterior, actual;
    time_t corteAnterior, corteActual;
    time_t botonAnterior, botonActual;
    
    time(&corteAnterior); //inicializa corte anterior
    time(&botonAnterior); //inicializa boton anterior
    
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strncmp(argv[i], "help", 4) == 0) {
                cout << "--debug_MDB" << endl;
                cout << "--debug_Changer" << endl;
                cout << "--debug_VMC" << endl;
                cout << "--debug_Corte" << endl;
                return 0;
            }
        }
    }

    VendingMachineController Despachador(argc, argv); //constructor de despachador

    anterior = clock(); // tiempo inicial

    while (1) {
        //MDB timing
        actual = clock(); //tiempo inicial
        if ((actual - anterior) >= __100MS) { //cada 100ms envia comandos de VSM a periféricos
            anterior = actual; //guarda tiempo de último comado

            vendingResult = Despachador.stateMachineVSM(selectedItem);
            if (vendingResult.state == ENABLE && vendingResult.status == DONE) {
                selectedItem = -1; //resetea elemento seleccionado
            }
        }

        //usleep(20000); //liberar tiempo de procesador
        if(Despachador.corteRequest == SEND_CORTE){
            Despachador.sendCorte();
        }

        if (vendingResult.state == DETECT_COIN) {
            //poll buttons
            result = Despachador.pollButtons(); //guarda en result el boton presionado, que corresponderá al número de artículo
            if (result >= 0 && result != selectedItem) { //si result es mayor que cero
                selectedItem = result; //actualiza artículo seleccionado
                cout << "Boton " << selectedItem << " presionado." << endl;
                time(&botonAnterior);
            }
            
            if(selectedItem >= 0){
                time(&botonActual);
                if ( difftime(botonActual,botonAnterior) >= 10){
                    if(Despachador.getCredit() == 0){
                        selectedItem = -1;
                    }
                }
            }
           
            /*Revisa si hay solicitud de corte a través del puerto serial
             para mandar a deshabilitar periféricos */

            if (Despachador.getCredit() == 0 && Despachador.corteRequest == NO_CORTE) { //si no hay transaccion en proceso y no hay ningun corte en progreso
                time(&corteActual);
                if (difftime(corteActual, corteAnterior) >= 1) {
                    time(&corteAnterior);
                    Despachador.searchCorte(); //Busca solicitud de corte cada segundo
                }
            }
                       
        }
        if (vendingResult.state == DISPATCH) {// mientras maquina surte hielo aprovecha para actualizar base de datos
            Despachador.registerSale();
        }


    }
    return 0;
}

