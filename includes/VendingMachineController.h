/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VendingMachineController.h
 * Author: Isaac
 *
 * Created on 1 de junio de 2018, 12:51 PM
 */

#ifndef VENDINGMACHINECONTROLLER_H
#define VENDINGMACHINECONTROLLER_H

#include "changer.h"
#include <string.h>
#include "GPIO.h"
#include <time.h>
#include <iostream>
#include <valarray>
#include "interfaz.h"
#include "moneyDB.h"
#include "leer_ArchivosTxt.h"
#include "corte.h"
//#include "mdbBus.h"

#define DEBUG_VMC   "--debug_VMC"

//VMC FSM
#define INITIALIZE  0
#define DETECT_COIN 1
#define INHIBIT     2
#define CHANGE      3
#define DISPATCH    4
#define ENABLE      5

//DETECT COIN FSM
#define CREDIT      0


#define TRANSACTION_COMPLETE 1

#define SELECCIONE      0
#define SELECCIONADO    1
#define DEPOSITANDO     2      
#define CAMBIO          3
#define INICIALIZANDO   4
#define  SELECCIONE_DEPOSITADO  5
#define  SURTIENDO      6
#define  NO_HIELO       7
#define  ESPERE  8

//changer change sequence states
#define         CALCULATE               0
#define         DISPENSE_COIN           1
#define         POLL_BUSY_PAYOUT        2

#define         NO_CORTE    0
#define         CORTE_REQUESTED       1
#define         SEND_CORTE  2
#define         CORTE_DONE  3

struct item_s {
    char amount; //cantidad de articulos que se venderán
    char name[8][25]; //nombres de articulos
    int price[8]; //precios
    int highestPrice;
    int available[8]; //disponible para venta
};

struct vendingState_s {
    int state;
    int status;
};

class VendingMachineController : protected Changer, protected BillValidator, protected moneyDB, protected Corte {
public:
    VendingMachineController(int argc, char** argv);
    int searchMoney();
    int pollButtons();
    int getCredit();
    struct vendingState_s stateMachineVSM(int pSelectedItem);
    int PrintGTK(int msg, int pSelectedItem);
    int registerSale();
    int searchCorte();
    int sendCorte();
    int corteRequest;
private:
    int credit;
    int escrow;
    int change;
    int charge;

    int buttons[5];
    int detectCoinSequence(int pSelectedItem);
    int updateCredit();
    int readButton(char pGpio);
    int hieloSuficiente();
    int giveChangeSequence(int pChange);
    int calculateChangeCoins(int pChange, char pChangeTypeAmount[10][2]);
    item_s Items;
    int vmcDebugFlag;

    int machineNumber;


};
#endif /* VENDINGMACHINECONTROLLER_H */

VendingMachineController::VendingMachineController(int argc, char** argv) {
    int mdb_fp;
    vmcDebugFlag = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--debug_VMC") == 0) {
                //               cout << "VMC debug on" << endl;
                vmcDebugFlag = 1;
            }
        }
    }
    mdb_fp = initializeMDB(argc, argv, 1); //mdb en ttyO1
    Changer::config(mdb_fp, argc, argv);
    BillValidator::config(mdb_fp, argc, argv);
    Corte::config(argc, argv, 4); //cortes en ttyO4

    Items.price[0] = leer_VarProg(PRECIO_A);
    Items.price[1] = leer_VarProg(PRECIO_B);
    Items.price[2] = leer_VarProg(PRECIO_C);
    Items.price[3] = leer_VarProg(PRECIO_D);

    setDatosMaquina(leer_VarProg(NUM_MAQ), Items.price[0], Items.price[1], Items.price[2], Items.price[3]);

    Items.highestPrice = 0;
    Items.amount = 0;
    for (int i = 0; i < 4; i++) {
        if (Items.price[i] > 0) {
            Items.amount++;
            if (Items.price[i] > Items.highestPrice) {
                Items.highestPrice = Items.price[i];
            }
        }
    }


    //Items.amount = 2;
    //Items.highestPrice = 2200;

    sprintf(Items.name[0], "%d Kg Hielo la Torre", leer_VarProg(PESO_A));
    sprintf(Items.name[1], "%d Kg Hielo la Torre", leer_VarProg(PESO_B));
    sprintf(Items.name[2], "%d Kg Hielo la Torre", leer_VarProg(PESO_C));
    sprintf(Items.name[3], "%d Kg Hielo la Torre", leer_VarProg(PESO_D));

    //strncpy(Items.name[0], "5Kg Hielo la Torre", 25);
    //Items.price[0] = 700;
    //Items.available[0] = 1;

    //strncpy(Items.name[1], "7Kg Hielo la Torre", 25);
    //Items.price[1] = 2200;
    //Items.available[1] = 1;// Revisar si aun necesito la variable

    buttons[3] = 61; //61   [3]
    buttons[4] = 65; //65   [4]
    buttons[0] = 46; //46   [0]
    buttons[1] = 26; //26   [1]
    buttons[2] = 44; //44   [2]

    credit = 0;
    charge = 0;
    change = 0;

    corteRequest = NO_CORTE;

    ini_VMID();

}

int VendingMachineController::updateCredit() {
    struct PollResponse result;
    int inserted;
    result = Changer::poll();
    if (result.type == COINS_DEPOSITED && result.coinType >= 0) {
        credit += inserted = Changer::coinTypeTubeValue[result.coinType][VALUE];
        if (result.routing == TUBES) {
            moneyDB::registerCoin(TUBOS_DEPOSITO, inserted, 0);
        } else if (result.routing == CASHBOX) {
            moneyDB::registerCoin(CAJA_MONEDA, inserted, 0);
        }
    }

    result = BillValidator::poll();
    if (result.type == BV_POLL_DEPOSITED && result.coinType >= 0) {
        credit += inserted = BillValidator::billTypeValue[result.coinType];
        moneyDB::registerCoin(CAJA_BILLETE, inserted, 0);
        if (result.routing == ESCROW_POSITION) {//por si se usa escrow
            escrow = BillValidator::billTypeValue[result.coinType];
        }
    }
    return credit;
}

int VendingMachineController::readButton(char pGpio) {
    GPIO gpio(pGpio);
    return gpio.readValue();
}

int VendingMachineController::pollButtons() {
    char counter;
    int state;
    for (int i = 0; i < Items.amount; i++) {
        do {
            state = readButton(buttons[i]);
            if (state == 0) {
                counter++;
            }
            if (counter >= 3) {
                return i;
            }
        } while (state == 0);
    }
    return -1;
}

struct vendingState_s VendingMachineController::stateMachineVSM(int pSelectedItem) {
    static char state = INITIALIZE;
    int result;
    int resultBill;
    static int aceptado = 0;
    static int solicitud = 0;
    static int surtiendo = 0;
    static int noHielo = 0;

    struct vendingState_s vendingResult;

    if ((Changer::status == UNPLUGGED || BillValidator::status == UNPLUGGED) && Changer::isInhibited() && BillValidator::isInhibited()) {
        state = INITIALIZE;
    } else if (Changer::status == UNPLUGGED || BillValidator::status == UNPLUGGED) {
        state = INHIBIT;
    }


    switch (state) {
        case INITIALIZE:
            vendingResult.state = INITIALIZE;
            result = Changer::initializeSequence();
            resultBill = BillValidator::initializeSequence();
            PrintGTK(INICIALIZANDO, pSelectedItem);
            if (result && resultBill) {
                //state = DETECT_COIN;
                state = ENABLE;
            } else {
                state = INITIALIZE;
            }
            break;


        case DETECT_COIN:
            vendingResult.state = DETECT_COIN;

            result = detectCoinSequence(pSelectedItem);

            if (corteRequest == CORTE_REQUESTED) {
                PrintGTK(ESPERE, pSelectedItem);
                state = INHIBIT;
                vendingResult.status = FAILED;
                
                return vendingResult;
            } else if (corteRequest == CORTE_DONE) {
                state = INITIALIZE;
                Changer::status = REINITIALIZE;
                BillValidator::status = REINITIALIZE;
                vendingResult.status = SUCCESS;
                corteRequest = NO_CORTE;
                return vendingResult;
            }

            if (pSelectedItem < 0) {
                charge = 0;
            }

            if (charge == 0 && credit == 0) {
                if (hieloSuficiente()) {
                    PrintGTK(SELECCIONE, pSelectedItem);
                    if (noHielo == 1) {
                        noHielo = 0;
                        state = ENABLE;
                        vendingResult.status = SUCCESS;
                        return vendingResult;
                    }

                } else {
                    PrintGTK(NO_HIELO, pSelectedItem);
                    noHielo = 1;
                    state = INHIBIT;
                    vendingResult.status = FAILED;
                    return vendingResult;
                }

            } else if (charge == 0 && credit > 0) {
                PrintGTK(SELECCIONE_DEPOSITADO, pSelectedItem);
            } else if (charge > 0 && credit > 0) {
                PrintGTK(DEPOSITANDO, pSelectedItem);
            } else if (charge > 0 && credit == 0) {
                PrintGTK(SELECCIONADO, pSelectedItem);
            }


            if (result && pSelectedItem >= 0 && Changer::isInhibited() && BillValidator::isInhibited()) {
                state = CHANGE;
            } else if (result && !Changer::isInhibited() && !BillValidator::isInhibited()) {
                state = INHIBIT;
            } else {
                state = DETECT_COIN;
            }


            break;

        case INHIBIT:
            vendingResult.state = INHIBIT;
            Changer::coinType(NO_ACCEPT);
            BillValidator::billType(NO_ACCEPT);
            if (vmcDebugFlag) {
                printf("INHIBIT COINS\n");
            }
            if(corteRequest == CORTE_REQUESTED){
                 state = DETECT_COIN;
                 corteRequest = SEND_CORTE;
            }else if (pSelectedItem >= 0 && noHielo == 0) {
                state = CHANGE;
            } else {
                state = DETECT_COIN;
            }


            break;

        case CHANGE:
            vendingResult.state = CHANGE;
            if (credit > charge) {
                change = credit - charge;
                //Changer::tubeStatus();
                //Changer::change(credit - charge);
                PrintGTK(CAMBIO, pSelectedItem);
                vendingResult.status = giveChangeSequence(change);
                if (vendingResult.status == DONE) { //termina de dar cambio
                    state = DISPATCH;
                    moneyDB::updateDB = 1;
                    moneyDB::precio = this -> charge;
                    moneyDB::insertado = this -> credit;
                    moneyDB::cambio = this -> change;
                    moneyDB::articulo = pSelectedItem;
                    //PrintGTK(SELECCIONE, pSelectedItem);
                    //return DONE; //1 cuando vendió exitosamente
                } else {
                    state = CHANGE;
                }
            } else {
                state = DISPATCH;
                moneyDB::updateDB = 1;
                moneyDB::precio = this -> charge;
                moneyDB::insertado = this -> credit;
                moneyDB::cambio = this -> change;
                moneyDB::articulo = pSelectedItem;
            }
            break;
        case DISPATCH:
            vendingResult.state = DISPATCH;
            Changer::poll();
            BillValidator::poll();

            if (!solicitud) {
                set_SolicitudVenta(pSelectedItem + 7);
                solicitud = 1;
            } else if (!aceptado) {
                aceptado = get_SolicitudAceptada();
                if (aceptado)
                    surtiendo = 1;
            } else if (surtiendo) {
                PrintGTK(SURTIENDO, pSelectedItem);
                if (estado_Venta())
                    surtiendo = 0;
            } else {
                clear_VentaTerminada();
                aceptado = 0;
                solicitud = 0;
                surtiendo = 0;
                state = ENABLE;
            }
            break;
        case ENABLE:

            vendingResult.state = ENABLE;
            if (Changer::status == INITIALIZING && BillValidator::status == INITIALIZING) { //habilita al inicializar
                vendingResult.status = SUCCESS;
                Changer::status = OK;
                BillValidator::status = OK;
            } else {
                credit = 0; //habilita despues de venta
                charge = 0;
                change = 0;
                escrow = 0;
                PrintGTK(SELECCIONE, pSelectedItem);
                vendingResult.status = DONE; // TODO: estructura qe comunique estado de FSM a main
            }
            Changer::coinType(ACCEPT);
            BillValidator::billType(ACCEPT);
            state = DETECT_COIN;

            break;
    }
    return vendingResult;
}

int VendingMachineController::detectCoinSequence(int pSelectedItem) {
    static int creditAux = 0;
    updateCredit(); //poll

    //Si entra una moneda
    if (creditAux != credit) {
        creditAux = credit;
        if (this -> credit >= this -> Items.highestPrice) { //si se ha ingresado suficiente dinero
            return 1;
        }
        if (vmcDebugFlag) {
            printf("Credit : %d \n", this -> credit); //muestra en pantalla crédito ingresado
        }
    }
    if (pSelectedItem >= 0) {//si se selecciono un articulo
        charge = Items.price[pSelectedItem];
        if (this -> credit >= charge) {
            return 1;
        }
    } else {
        charge = 0;
    }
    return 0;
}

int VendingMachineController::PrintGTK(int msg, int pSelectedItem) {
    FILE *fGTK;
    char nomarch[] = "/home/root/Torniquete/GTK/mensaje.aps";
    char texto[128];
    float SaldoTotalMsg = 0;
    float TarifaMsg = 0;
    float SaldoTotalRestanteMsg;
    memset(texto, 0x00, 128);

    int sensorFeedback;

    switch (msg) {
        case SELECCIONE: // 0
            strcpy(texto, "Seleccione la cantidad \nde hielo a surtir");
            break;

        case SELECCIONADO: // 1
            TarifaMsg = (float) Items.price[pSelectedItem] / 100;
            sprintf(texto, "%s\nDeposite:\n$%0.2f", Items.name[pSelectedItem], TarifaMsg);
            break;

        case DEPOSITANDO: // 2
            TarifaMsg = (float) Items.price[pSelectedItem] / 100;
            SaldoTotalMsg = (float) credit / 100;
            SaldoTotalRestanteMsg = TarifaMsg - SaldoTotalMsg;
            sprintf(texto, "Monto a Pagar: $%0.2f \nMonto Ingresado: $%0.2f \nRestante: $%0.2f\n", TarifaMsg, SaldoTotalMsg, SaldoTotalRestanteMsg);
            break;

        case CAMBIO:// 3
            sprintf(texto, "\nSu cambio:\n%0.2f", (float) change / 100);
            break;

        case INICIALIZANDO: // 4
            strcpy(texto, "Inicializando Periféricos");
            break;

        case SELECCIONE_DEPOSITADO: // 5
            sprintf(texto, "Seleccione la cantidad \nde hielo a surtir\nDepositado: $%0.2f", (float) credit / 100);
            break;

        case SURTIENDO: // 6
            strcpy(texto, "\nSurtiendo\nPor favor espere");
            break;

        case NO_HIELO: // 7
            strcpy(texto, "No hay Hielo suficiente\nDisculpe las molestias");
            break;
        case ESPERE: //8
            strcpy(texto, "Espere un momento \nPor Favor");
            break;

    }

    fGTK = fopen(nomarch, "w");
    fprintf(fGTK, "%s", texto);
    fclose(fGTK);

    return 0;
}

int VendingMachineController::hieloSuficiente() {
    static char counter = 10;
    static int result = 0;
    counter++;
    if (counter >= 10) {
        counter = 0;
        result = get_Hielosuficiente();
    }

    return result;
}

/*
 * int Changer::giveChangeSequence(int pChange)
 *      int     pChange         cantidad por regresar de cambio
 * 
 * PURPOSE :    Maquina de estados para la secuencia de dar cambio
 *
 * RETURN :   SUCCESS           si recibe ACK del monedero
 *            FAILED            si no recibe ACK del monedero    
 *            DONE              teminó de dar cambio
 *   
 * ESTADOS:
 *      CALCULATE               en base a cantidad que se dará en cambio y en 
 *                              las cantidades de monedas disponibles, calcula 
 *                              las monedas y las cantidades que se entregarán
 *                              y las guarda en changeTypeAmount[][]
 * 
 *      DISPENSE_COIN           obtiene los tipos de monedas de changeTypeAmount[][]
 *                              y envía el comando de dispense para cada tipo de moneda 
 *                              según la cantidad necesaria. Si se requieren mas de 15 monedas,
 *                              envía el comando de dispensar mas de una vez.
 * 
 *      POLL_BUSY_PAYOUT        revisa el estado del monedero para revisar cuando haya terminado de
 *                              dispensar
 *                               
 * NOTES :    
 *      [1] comande dispense permite dispensar como máximo 15 monedas.
 *      [2] <<<<<<Pendiente que hacer cuando no hay monedas para dar cambio!!!!!>>>>>>
 *      [3] <<<<<<Revisar si hay cambio previo a la compra?????? >>>>>
 * 
 *     
 */
int VendingMachineController::giveChangeSequence(int pChange) {
    static char changeTypeAmount[10][2]; // arreglo de datos donde guardará tipo de dato que dispensará y la cantidad
    static int coinTypes; //tipos distintos de monedas que se darán de cambio                   
    static int auxCoin = 0; //indica el tipo de moneda(en changeTypeAmount[][]) que sigue en dispensar
    char amount; //cantidad de monedas que pasará al comando dispense
    int result;
    struct PollResponse pollResult;
    static int state = CALCULATE;

    switch (state) {
        case CALCULATE:
            coinTypes = calculateChangeCoins(pChange, changeTypeAmount); //calcula tipos y cantidades de monedas
            if (coinTypes <= 0) { //no hay suficientes monedas para dar cambio
                cout << "No hay cambio" << endl;
                auxCoin = 0;
                state = CALCULATE; //se queda en CALCULATE 
                return FAILED;
            }
            state = DISPENSE_COIN; // Despues de calcular pasa a Dispensar
            // No break para que se mande mínimo un comando cada 100 ms    
        case DISPENSE_COIN:
            amount = changeTypeAmount[auxCoin][1]; //para evitar pedir que se dispense mas de 15 monedas    
            if (amount > 15) { //si hay que dispensar mas de 15 monedas
                amount = 15; //primero dispensar 15
                changeTypeAmount[auxCoin][1] -= 15; //y al siguiente comando se dispensan las demás
            } else {
                changeTypeAmount[auxCoin][1] = 0;
            }
            result = Changer::dispense(changeTypeAmount[auxCoin][0], amount); //envia comando dispense
            if (result == SUCCESS) { //si se recibió ACK del monedero
                moneyDB::registerCoin(TUBOS_CAMBIO, Changer::coinTypeTubeValue[changeTypeAmount[auxCoin][0]][1], amount);
                state = POLL_BUSY_PAYOUT; //procederá a esperar que termine de dispensar    
                cout << "go to POLL BUSY" << endl;
                if (changeTypeAmount[auxCoin][1] == 0) { //si ya se dispensaron todas las monedas de este tipo
                    auxCoin++; //la siguiente vuelta dispensa otra moneda
                }
            } else {
                //<<<<<<<<<<<<<Que hacer si no recibe respuesta al dispensar!!!!?!?!>>>>>>>>>>>>>
                //<<<<<<<<<<<<<Generar Log con fecha y hora?>>>>>>>>>>>
                cout << "ERROR DISPENSE" << endl; //no recibe respuesta al dispensar
                auxCoin = 0;
                state = CALCULATE;
                return FAILED;
            }
            break;

        case POLL_BUSY_PAYOUT:
            cout << " POLL BUSY PAYOUT" << endl;
            pollResult = Changer::poll(); //POLL
            if (pollResult.type == STATUS && pollResult.status == _ACK) { //Espera a recibir ACK
                //otra opcion sería esperar que deje de recibir Status de PAYOUT BUSY por si hay otros status
                if (auxCoin == coinTypes) { //si ya se dispensaron todas las monedas
                    auxCoin = 0; //resetea auxCoin
                    state = CALCULATE; //resetea el estado

                    if (vmcDebugFlag) {
                        cout << "Ha terminado de dar cambio" << endl;
                    }

                    return DONE;
                }
                state = DISPENSE_COIN; //si hay monedas pendientes por dispensar 
                cout << "Faltan monedas por dispensar" << endl;
            } else {
                state = POLL_BUSY_PAYOUT; // si aun no recibe ACK, mantenerse en este estado
                cout << " Dando Cambio " << endl;
            }
            break;
    }
    return SUCCESS;
}

/*
 *int Changer::calculateChangeCoins(int pChange, char pChangeTypeAmount[10][2])
 *      int         pChange       cantidad de cambio total
 *      char        pChangeTypeAmount[10][2]    Almacena tipos y cantidades de monedas
 * 
 * PURPOSE :    Calcular el tipo y la cantidad de monedas que se dispensarán para dar el cambio
 *
 * RETURN :    ERROR            si no hay suficientes monedas para dar cambio
 *             coinTypes        la cantidad de tipo de monedas por entregar
 *                                   
 * NOTES :      
 *      [1] Busca la mayor denominación disponible, que sea menor o igual a la cantidad por entregar, que tenga tubo, y que el tubo tenga monedas
 *      [2] 
 *     
 */
int VendingMachineController::calculateChangeCoins(int pChange, char pChangeTypeAmount[10][2]) {
    char maxValueType = 15;
    int coinTypes = 0; //numero de diferentes denominaciones que se entregarán de cambio.
    int coinAmount;
    int coinsToGive = 0;
    int j = 0;
    struct TubeStatus_s TubeStatus;
    TubeStatus = Changer::tubeStatus();
    if (TubeStatus.msgStatus == SUCCESS) {

        for (int j = 0; j < 10; j++) {

            for (int i = 0; i <= maxValueType; i++) { //Encuentra la mayor denominacion disponible 
                if (coinTypeTubeValue[maxValueType - i][VALUE] != 0) {
                    if (coinTypeTubeValue[maxValueType - i][VALUE] <= pChange) { //que sea menor o igual que la cantidad a devolver
                        if (coinTypeTubeValue[maxValueType - i][TUBE]) {//que vaya a tubo
                            coinAmount = TubeStatus.tubeStatus[maxValueType - i]; //Verifica cantidad de monedas de esta denominación hay en tubo
                            if (coinAmount > 0) {
                                maxValueType = maxValueType - i;
                                break;
                            }

                        }//end if
                    }//end if
                }//end if
            }//end for

            coinTypes++;
            do {
                pChange -= coinTypeTubeValue[maxValueType][VALUE]; //descuenta valor a moneda
                coinAmount--; //descuenta cantidad a numero de monedas disponibles
                coinsToGive++; //incrementa contador de las monedas que se entregarán de este tipo
            } while (coinAmount > 0 && pChange >= coinTypeTubeValue[maxValueType][VALUE]); //repetir mientras haya monedas y la cantidad de cambio sea mayor que el valor de la moneda

            pChangeTypeAmount[j][0] = maxValueType; //guarda tipo de moneda
            pChangeTypeAmount[j][1] = coinsToGive; //guarda cantidad de monedas
            cout << "Entrega " << coinsToGive << " de " << coinTypeTubeValue[maxValueType][VALUE] << endl;
            coinsToGive = 0; //resetea coins to give
            maxValueType--;

            if (pChange == 0) { //si ya terminó de dar cambio salir de ciclo
                break;
            }

        }//end for
        if (pChange != 0) {
            cout << "No hay suficiente monedas para dar cambio" << endl;
            return ERROR;
        } else
            return coinTypes;

    }//end if
}//end change

int VendingMachineController::registerSale() {
    if (moneyDB::updateDB) {
        moneyDB::updateDatabase();
    }
}

int VendingMachineController::searchCorte() {
    if (Corte::getRequest()) {
        corteRequest = CORTE_REQUESTED;
    } else {
        corteRequest = NO_CORTE;
    }
    return corteRequest;
}

int VendingMachineController::getCredit() {
    return this -> credit;
}

int VendingMachineController::sendCorte() {
    moneyDB db(CORTE);
    struct monedas_s monedas;
    struct billetes_s billetes;

    Corte::setNumeroMaquina(db.getNumeroMaquina());
    Corte::setFolio(db.getFolio());
    Corte::setVentas(db.getVentasA(), db.getVentasB(), db.getVentasC(), db.getVentasD());
    Corte::setPrecios(db.getPrecioA(), db.getPrecioB(), db.getPrecioC(), db.getPrecioD());

    monedas = db.getTubosIn();
    Corte::setTubosIn(monedas.mxn_50c, monedas.mxn_1p, monedas.mxn_2p,
            monedas.mxn_5p, monedas.mxn_10p, monedas.mxn_20p);

    monedas = db.getTubosOut();
    Corte::setTubosOut(monedas.mxn_50c, monedas.mxn_1p, monedas.mxn_2p,
            monedas.mxn_5p, monedas.mxn_10p, monedas.mxn_20p);

    monedas = db.getCajaMonedas();
    Corte::setCajaMonedas(monedas.mxn_50c, monedas.mxn_1p, monedas.mxn_2p,
            monedas.mxn_5p, monedas.mxn_10p, monedas.mxn_20p);

    billetes = db.getCajaBilletes();
    Corte::SetCajaBilletes(billetes.mxn_20p, billetes.mxn_50p, billetes.mxn_100p,
            billetes.mxn_200p, billetes.mxn_500p, billetes.mxn_1000p);

    if (Corte::corteBluetooth()) {
        cout << "Corte exitoso" << endl;
        db.backupDatabase();
        db.resetDatabase();
        corteRequest = CORTE_DONE;
        return 1;
    } else {
        cout << "Corte Fallido" << endl;
        corteRequest = CORTE_DONE;
        return 0;
    }
    return 0;
}
