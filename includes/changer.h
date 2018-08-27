/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   changer.h
 * Author: Oscar Maradiaga
 *
 * Created on 30 de abril de 2018, 11:18 AM
 */

#ifndef CHANGER_H
#define CHANGER_H

#define DEBUG_CHANGER   "--debug_Changer"
#define DEBUG_BILL_VALIDATOR   "--debug_BV"

#define MAX_RETRY       10

#include "mdbBus.h"
#include <stdlib.h>
#include <cstdio>
#include <stdint-gcc.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#define     FAILED      -1
#define     SUCCESS     0
#define     DONE        1

//columnas de coinTypeTubeValue
#define     TUBE        0
#define     VALUE       1

//changer commands and initialization sequence states
#define     CHANGER_RESET   0x08
#define     CHANGER_SETUP   0x09
#define     CHANGER_TUBE_STATUS     0X0A
#define     CHANGER_POLL    0X0B
#define     CHANGER_COIN_TYPE   0x0C
#define     CHANGER_DISPENSE    0x0D
#define     CHANGER_EXPANSION_ID    0x0F

//changer cointype aacept or no accept
#define     NO_ACCEPT   0
#define     ACCEPT      1

#define     CHANGER_CONF        "in/changer.conf"

//changer poll status reponse
#define        _ACK                      0
#define        ESCROW_REQUEST           1
#define        PAYOUT_BUSY              2
#define        NO_CREDIT                3
#define        DEFECTIVE_TUBE_SENSOR    4
#define        DOUBLE_ARRIVAL            5
#define        ACCEPTOR_UNPLUGGED       6
#define        ROM_CHECKSUM_ERROR       7
#define        COIN_ROUTING_ERROR       8
#define        CHANGER_BUSY             9
#define        RESET                    10
#define        COIN_JAM                 11
#define        COIN_REMOVAL             12

//changer poll response type
#define         COIN_DISPENSED_MANUAL   0
#define         COINS_DEPOSITED         1
#define         STATUS                  2
#define         SLUG                    3
#define         ERROR                   4

//changer poll routing
#define         CASHBOX                 4
#define         TUBES                   5
#define         REJECTED                7



//Bill Validator commands and initialization sequence states
#define         BV_RESET                    0x30
#define         BV_SETUP                   0x31
#define         BV_SECURITY                0x32
#define         BV_POLL                    0x33
#define         BV_BIIL_TYPE               0x34
#define         BV_ESCROW                  0x35
#define         BV_STACKER                 0x36
#define         BV_EXPANSION_ID               0x37

//Bill Validator response type
#define         BV_POLL_STATUS              0
#define         BV_POLL_DEPOSITED           1

//Bill Validator BILL ROUTING
#define         BILL_STACKED                    0
#define         ESCROW_POSITION                 1
#define         BILL_RETURNED                   2
#define         BILL_TO_RECYCLER                3    
#define         DISABLED_BILL_REJECTER          4
#define         BILL_TO_RECYCLER_MANUAL_FILL    5
#define         MANUAL_DISPENSE                 6
#define         RECYCLER_TO_CASHBOX             7

//Bill Validator poll status response

//              _ACK                        0 //definido en coins
#define         DEFECTIVE_MOTOR             1
#define         SENSOR_PROBLEM              2
#define         VALIDATOR_BUSY              3
#define         CHECKSUM_ERROR              4
#define         VALIDATOR_JAMMED            5
#define         VALIDATOR_RESET             6
#define         BILL_REMOVED                7
#define         CASH_BOX_OUT_OF_POSITION    8
#define         VALIDATOR_DISABLED          9
#define         INVALID_ESCROW_REQUEST      10
#define         BILL_REJECTED               11


// status defines
#define REINITIALIZE    -2
#define UNPLUGGED       -1
#define OK              0
#define INITIALIZING    1

struct Data {//structura para manejar datos de VMC y Changer
    char data[36];
    char dataLen;
};

struct PollResponse {
    int type;
    int status;
    char coinType;
    char routing;
};

struct Setup_s {
    char changerFeatureLevel;
    int country;
    int coinScalingFactor;
    char decimalPlaces;
    int coinTypeRouting;
    int coinTypeCredit[16];
};

struct Id_s {
    char manufacturerCode[4];
    char serialNumber[13];
    char modelNumber[13];
    char softwareVersion[2];
    char optionalFeatures[4];
};

struct TubeStatus_s {
    int msgStatus; //estado del mensaje
    int tubeFullStatus; //16 bits indican si cada tubo está lleno o vacío
    int tubeStatus[16]; //16 bits indican la cantidad de monedas en el tubo
};

union CoinEnable_u {

    struct {
        char coinEn15 : 1;
        char coinEn14 : 1;
        char coinEn13 : 1;
        char coinEn12 : 1;
        char coinEn11 : 1;
        char coinEn10 : 1;
        char coinEn9 : 1;
        char coinEn8 : 1;
        char coinEn7 : 1;
        char coinEn6 : 1;
        char coinEn5 : 1;
        char coinEn4 : 1;
        char coinEn3 : 1;
        char coinEn2 : 1;
        char coinEn1 : 1;
        char coinEn0 : 1;
    };

    struct {
        char low;
        char high;
    };
    uint16_t coinEnable;
}; //           coin/ bill Enable

union ManualDispense_u {

    struct {
        char manualDispense15 : 1;
        char manualDispense14 : 1;
        char manualDispense13 : 1;
        char manualDispense12 : 1;
        char manualDispense11 : 1;
        char manualDispense10 : 1;
        char manualDispense9 : 1;
        char manualDispense8 : 1;
        char manualDispense7 : 1;
        char manualDispense6 : 1;
        char manualDispense5 : 1;
        char manualDispense4 : 1;
        char manualDispense3 : 1;
        char manualDispense2 : 1;
        char manualDispense1 : 1;
        char manualDispense0 : 1;
    };

    struct {
        char high;
        char low;
    };
    uint16_t manualDispense;
}; //        Manual dispense / Escrow

struct CoinType_s {
    CoinEnable_u CoinEnable;
    ManualDispense_u ManualDispense;
};

struct CoinDeposited_s {
    unsigned char cashBox[16]; //16 tipos de monedas
    unsigned char tubes[16];
    unsigned char reject[16];
};

struct BillDeposited_s {
    unsigned char stack[16]; //16 tipos de billetes
    unsigned char escrow[16];
    unsigned char returned[16];
    unsigned char recycler[16];
    unsigned char disabled[16];
    unsigned char recycler_manual[16];
    unsigned char manual_dispense[16];
    unsigned char reycler_cashbox[16];
};


class BillValidator;

class Changer {
public:
    Changer();
    int config(int serialfd, int argc, char** argv);

    int reset();
    int setup();
    struct TubeStatus_s tubeStatus();
    struct PollResponse poll();
    int coinType(int accept);
    int dispense(char pCoinType, char pAmount);
    int ID();

    int initializeSequence();

    int isInhibited();
    int status;
    //columna 0 indica si moneda va a tubo (1) o no (0). 
    //columna 1 guarda valor en centavos ($1 -> 100) 
    //para los 16 tipos de monedas posibles
    int coinTypeTubeValue[16][2];
private:
    int inhibited;
    struct Setup_s setupResponseProcess();
    struct TubeStatus_s tubeStatusResponseProcess();
    struct PollResponse pollProcess();
    struct CoinType_s setCoinType(int accept);
    struct Id_s IdResponseProcess();
    int mdb_fd; //mdb bus file descriptor

    int acceptedCoins[6]; // {50,100,200,500,1000,2000}
    char changerDebugFlag;

    int retry;

    Data VMC;
    Data CoinChanger;
    //Setup_s Setup;
    //Id_s Id;
    //TubeStatus_s TubeStatus;
    CoinDeposited_s CoinDeposited;
};

class BillValidator {
public:
    BillValidator();
    int config(int serialfd, int argc, char** argv);
    int initializeSequence();
    int stateMachinInit;
    int reset();
    struct PollResponse poll();
    int setup();
    int ID();
    int stacker();
    int billType(int accept);
    int isInhibited();
    int billTypeValue[16];
    int status;
private:

    struct PollResponse pollProcess();
    int setupResponseProcess();
    int IdResponseProcess();
    int stackerResponseProcess();
    struct CoinType_s setBillType(int accept);
    int mdb_fd;
    int debugFlag;
    int inhibited;
    int retry;
    Data VMC;
    Data Validator;
    BillDeposited_s BillDeposited;
};
#endif /* CHANGER_H */

//Constructor de objeto

Changer::Changer() {

}

/*
 * int Changer::config(int serialfd, int argc, char** argv)
 *      int     serialfd    descriptor serial del puerto al que transmitirá buffer
 *      int     argc        numero de argumentos del main
 *      char**  argv        argumentos del main
 * 
 * PURPOSE :    Configura bandera de debug y recibe el descriptor serial para guardarlo como variable de clase
 *
 * RETURN :     mdb_fd      descriptor a puerto serial de MDB
 * 
 * NOTES :      
 *      [1]Busca en parámetros de main "--debug_Changer"
 *      [2]configura bandera de debug para monedero
 *      [3]Toma descriptor serial y lo guarda como variable de clase
 */
int Changer::config(int serialfd, int argc, char** argv) {
    changerDebugFlag = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strncmp(argv[i], DEBUG_CHANGER, strlen(DEBUG_CHANGER)) == 0) {
                cout << "Changer debug on" << endl;
                changerDebugFlag = 1;
            }
        }
    }
    //return initializeMDB(argc, argv, 1);
    mdb_fd = serialfd;

    status = INITIALIZING;

    return mdb_fd;
}

/*
 * int Changer::reset() * 
 * PURPOSE :    Regresa monedero a modo de operacion default
 *
 * RETURN :     0       si recibe ACK de monedero (reset exitoso)
 *              -1      si no recibe ACK (reset fallido)
 * 
 * NOTES :      
 *      [1]Mensaje de reset no lleva datos
 *      [2]solo puede recibir como respuesta ACK
 */

int Changer::reset() {
    char cmd = CHANGER_RESET;
    VMC.dataLen = 0;
    if (changerDebugFlag)
        printf("RESET\n");

       CoinChanger.dataLen = sendCommand(mdb_fd, cmd, VMC.data, VMC.dataLen, CoinChanger.data, LONG_TIMEOUT);
    if(CoinChanger.dataLen == 0){
        retry++;
        if(retry > MAX_RETRY){
            status = UNPLUGGED;
            retry = 0;
        }
    }else{
        retry = 0;
    }

    if (CoinChanger.dataLen == 1 && CoinChanger.data[0] == 0) {
        if (changerDebugFlag)
            printf("\n reset: ACK \n");
        return SUCCESS;
    } else {
        if (changerDebugFlag) {
            printf("\n reset failed \n");

        }
        return FAILED;
    }
}

/*
 * int Changer::setup() * 
 * PURPOSE :    Recibe configuraciones del monedero 
 *              feature level, country, scaling factor, decimal places, 
 *              coin type routing, coin type credit. 
 *
 * RETURN :     SUCCEED           si datos de configuracion se recibieron completos y correctos
 *              FAILED          si hubo error en recepción
 * 
 * NOTES :      
 *      [1] mensaje de setup no lleva datos
 *      [2] respuesta de setup es de 23 bytes. Responde ACK si respuesta es correcta
 *<<<<<<<<<<<PENDIENTE: el periferico no tiene que enviar los 23 bytes. Si el tipo de moneda tiene credito 0 puede omitir los bytes>>>>>>>>>>>>>>
 *<<<<<<<<<<< Si el monedero envia menos de 23 bytes, va a fallar. CORREGIR>>>>>>>>>>>>>>>>>>>> 
 *      [3] procesa los datos recibidos en función setupResponseProcess()
 *      [4] devuelve resultado de la recepción de datos
 */
int Changer::setup() {
    char cmd = CHANGER_SETUP;

    VMC.dataLen = 0;
    if (changerDebugFlag)
        printf("SETUP\n");

       CoinChanger.dataLen = sendCommand(mdb_fd, cmd, VMC.data, VMC.dataLen, CoinChanger.data, LONG_TIMEOUT);
    if(CoinChanger.dataLen == 0){
        retry++;
        if(retry > MAX_RETRY){
            status = UNPLUGGED;
            retry = 0;
        }
    }else{
        retry = 0;
    }

    if (CoinChanger.dataLen == 23) {
        sendACK(mdb_fd);
        if (changerDebugFlag)
            printf("\n setup: OK \n");
        struct Setup_s ChangerSetup;
        ChangerSetup = setupResponseProcess();
        return SUCCESS;
    } else {
        if (changerDebugFlag)
            printf("\n setup failed \n");
        return FAILED;
    }
}

/*
 * struct TubeStatus_s Changer::tubeStatus() 
 * PURPOSE :    Recibe el estado de de los tubos del monedero
 *
 * RETURN :    struct TubeStatus_s  TubeStatus
 *        Tubestatus.msgStatus       SUCCESS      si respuesta de monedero es correcta y completa
 *                                   FAILED       si respuesta no es correcta o completa
 * NOTES :      
 *      [1] mensaje de tube status no lleva datos
 *      [2] respuesta de tube status es de 18 bytes. Responde ACK si respuesta es correcta
 *<<<<<<<<<<<PENDIENTE: el periferico no tiene que enviar los 18 bytes. Si el tubo no tiene monedas puede omitir los bytes>>>>>>>>>>>>>>
 *<<<<<<<<<<< Si el monedero envia menos de 18 bytes, va a fallar. CORREGIR>>>>>>>>>>>>>>>>>>>> 
 *      [3] procesa los datos recibidos en función tubeStatusResponseProcess()
 *      [4] devuelve resultado de la recepción de datos
 */
struct TubeStatus_s Changer::tubeStatus() {
    struct TubeStatus_s TubeStatus;
    char cmd = CHANGER_TUBE_STATUS;
    VMC.dataLen = 0;
    if (changerDebugFlag)
        printf("TUBE STATUS\n");

      CoinChanger.dataLen = sendCommand(mdb_fd, cmd, VMC.data, VMC.dataLen, CoinChanger.data, LONG_TIMEOUT);
    if(CoinChanger.dataLen == 0){
        retry++;
        if(retry > MAX_RETRY){
            status = UNPLUGGED;
            retry = 0;
        }
    }else{
        retry = 0;
    }

    if (CoinChanger.dataLen == 18) {
        sendACK(mdb_fd);
        if (changerDebugFlag)
            printf("\n Tube Status: OK \n");
        TubeStatus = tubeStatusResponseProcess();
        TubeStatus.msgStatus = SUCCESS;
        return TubeStatus;
    } else {
        if (changerDebugFlag)
            printf("\n Tube Status failed \n");
        TubeStatus.msgStatus = FAILED;
        return TubeStatus;
    }
}

/*
 * struct PollResponse Changer::poll()  
 * PURPOSE :    para monitorear monedero y recibir alguna actualizacion de moneda o reporte de estado
 *
 * RETURN :    struct PollResponse  result
 *          result.type             STATUS     
 *              result.status       _ACK        Monedero responde con ACK
 * 
 *          result.type     ERROR           si respuesta no es correcta o completa    
 *                                   
 * NOTES :      
 *      [1] mensaje de poll no lleva datos
 *      [2] respuesta de poll puede ser ACK o cambio de estado, deposito de moneda o moneda dispensada. Responde ACK si datos recibidos están completos
 *<<<<<<<<<<<PENDIENTE: El tamaño de la respuesta de poll es dinámico. Puede mandar mas de un estado, o moneda depositada, etc mientras se mantengan por debajo de los 16 bytes>>>>>>>>>>>>>>
 *<<<<<<<<<<< La función solo procesará el primer dato de la respuesta. CORREGIR>>>>>>>>>>>>>>>>>>>> 
 *      [3] procesa los datos recibidos en función tubeStatusResponseProcess()
 *      [4] devuelve resultado de la recepción de datos
 */

struct PollResponse Changer::poll() {
    struct PollResponse result;
    char cmd = CHANGER_POLL;
    VMC.dataLen = 0;
    if (changerDebugFlag)
        printf("POLL \n");

    CoinChanger.dataLen = sendCommand(mdb_fd, cmd, VMC.data, VMC.dataLen, CoinChanger.data, LONG_TIMEOUT);
    if(CoinChanger.dataLen == 0){
        retry++;
        if(retry > MAX_RETRY){
            status = UNPLUGGED;
            retry = 0;
        }
    }else{
        retry = 0;
    }
   

    for (int i = 0; i < CoinChanger.dataLen; i++) {//Si quito el for falla URGE corregir
        //printf("%2x ", CoinChanger.data[0]);
    }
    if (CoinChanger.dataLen >= 1) {
        if (CoinChanger.data[0] != 0) {
            sendACK(mdb_fd);
        }
        result = pollProcess();

        return result;

    } else {
        result.type = ERROR;
    }

}

/*
 * int Changer::coinType(int accept) 
 *      int       accept:
 *                      ACCEPT      habilita la recepción de todas las monedas;
 *                      NO_ACCEPT   deshabilita la recepción de todas las monedas
 * 
 * PURPOSE :    para establecer las monedas que aceptará o no aceptará el monedero
 *
 * RETURN :   SUCCEED           si recibe ACK del monedero
 *            FAILED            si no recibe ACK del monedero    
 *                                   
 * NOTES :      
 *      [1] mensaje de coin type lleva 4 datos (ver especificaciones MDB)
 *      [2] setCoinType() habilita las monedas deseadas
 *     
 */
int Changer::coinType(int accept) {
    char cmd = CHANGER_COIN_TYPE;
    struct CoinType_s CoinType;
    CoinType = setCoinType(accept);
    VMC.dataLen = 4;
    //    VMC.data[0] = 0x00;
    //    VMC.data[1] = 0x3d; //acepta todas las denominaciones HARDCODED
    VMC.data[2] = 0x00; //deshabilita entrega manual de monedas
    VMC.data[3] = 0xff;

    VMC.data[0] = CoinType.CoinEnable.high;
    VMC.data[1] = CoinType.CoinEnable.low;
    //        VMC.data[2]= CoinType.ManualDispense.high;
    //        VMC.data[3]=  CoinType.ManualDispense.low;                  
    if (changerDebugFlag)
        printf("Coin Type\n");

       CoinChanger.dataLen = sendCommand(mdb_fd, cmd, VMC.data, VMC.dataLen, CoinChanger.data, LONG_TIMEOUT);
    if(CoinChanger.dataLen == 0){
        retry++;
        if(retry > MAX_RETRY){
            status = UNPLUGGED;
            retry = 0;
        }
    }else{
        retry = 0;
    }

    if (CoinChanger.dataLen == 1 && CoinChanger.data[0] == 0) {
        if (changerDebugFlag)
            printf("Coin Type: ACK \n");
        return SUCCESS;
    } else
        return FAILED;
}

/*
 * Changer::Dispense(char pCoinType, char pAmount) 
 *      char    pCoinType
 *      char    pAmount
 * 
 * PURPOSE :    dispensa tantas monedas indique pAmount del tipo indicado por pCoinType
 *
 * RETURN :   SUCCESS           si recibe ACK del monedero
 *            FAILED            si no recibe ACK del monedero    
 *                                   
 * NOTES :      
 *      [1] mensaje de dispense lleva 1 dato (ver especificaciones MDB)
 *      [2] debe recibir ACK cuando el monedero comienza a dispensar
 *     
 */
int Changer::dispense(char pCoinType, char pAmount) {
    char cmd = CHANGER_DISPENSE;
    if (pAmount > 15) {
        return -1; //Acepta maximo 15 monedas;
    }
    if (changerDebugFlag)
        printf("DISPENSE \n");
    VMC.dataLen = 1;
    VMC.data[0] = pAmount << 4;
    VMC.data[0] |= pCoinType;

       CoinChanger.dataLen = sendCommand(mdb_fd, cmd, VMC.data, VMC.dataLen, CoinChanger.data, LONG_TIMEOUT);
    if(CoinChanger.dataLen == 0){
        retry++;
        if(retry > MAX_RETRY){
            status = UNPLUGGED;
            retry = 0;
        }
    }else{
        retry = 0;
    }

    if (CoinChanger.dataLen == 1 && CoinChanger.data[0] == 0) {
        if (changerDebugFlag) {
            printf("Dispense: ACK \n");
        }
        return SUCCESS;

    } else {
        return FAILED;
    }
}

/*
 * Changer::ID()
 * 
 * PURPOSE :    obtiene datos de identificación del monedero (véase especificación MDB changer >> Expansion >> ID)
 *
 * RETURN :   SUCCESS           si recibe ACK del monedero
 *            FAILED            si no recibe ACK del monedero    
 *                                   
 * NOTES :      
 *      [1] mensaje de ID lleva 1 datos que es el comando de expansion (ver especificaciones MDB)
 *      [2] recibe 33 datos
 *     
 */
int Changer::ID() {
    char cmd = 0x0f;
    VMC.dataLen = 1;
    VMC.data[0] = 00;
    if (changerDebugFlag)
        cout << "ID" << endl;

      CoinChanger.dataLen = sendCommand(mdb_fd, cmd, VMC.data, VMC.dataLen, CoinChanger.data, LONG_TIMEOUT);
    if(CoinChanger.dataLen == 0){
        retry++;
        if(retry > MAX_RETRY){
            status = UNPLUGGED;
            retry = 0;
        }
    }else{
        retry = 0;
    }

    if (CoinChanger.dataLen == 33) {
        sendACK(mdb_fd);
        struct Id_s IdResult;
        if (changerDebugFlag)
            printf("\n ID: OK \n");
        IdResult = IdResponseProcess();
        return SUCCESS;
    } else
        if (changerDebugFlag)
        printf("\n ID failed \n");
    return FAILED;
}

/*
 *Changer::initializeSequence()
 * 
 * PURPOSE :    Secuencia para inicializar monedero 
 *
 * RETURN :    ERROR            si no hay suficientes monedas para dar cambio
 *             coinTypes        la cantidad de tipo de monedas por entregar
 *   
 * ESTADOS:
 *      CHANGER_RESET           Regresa a estado default
 *      CHANGER_POLL            para recibir "JUST RESET" (status reset en poll?)
 *      CHANGER_SETUP           recibir configuracion de monedero
 *      CHANGER_EXPANSION_ID    recibir parametros de identificacion del monedero
 *      CHANGER_TUBE_STATUS     recibir estado de los tubos
 *      CHANGER_COIN_TYPE       habilita las monedas
 *                                 
 * NOTES :      
 *      [1] Busca la mayor denominación disponible, que sea menor o igual a la cantidad por entregar, que tenga tubo, y que el tubo tenga monedas
 *      [2] 
 *     
 */
int Changer::initializeSequence() {
    static int state = CHANGER_RESET;
    static int initialized = 0;
    int result = 0;

    if (status == UNPLUGGED || status == REINITIALIZE) {
        state = CHANGER_RESET;
        initialized = 0;
        status = INITIALIZING;
    }
    //cout << "coin initialize state: "<< state << endl; 
    switch (state) {
        case CHANGER_RESET:
            result = reset();
            if (result == SUCCESS) {
                state = CHANGER_POLL;
            } else {
                state = CHANGER_RESET;
            }
            break;
        case CHANGER_POLL:
            struct PollResponse pollResult;
            pollResult = poll();

            if (pollResult.type == STATUS && pollResult.status == _ACK && !initialized) {//Ignora lo que haya recibido el poll
                state = CHANGER_SETUP;
            } else {
                state = CHANGER_POLL;
            }
            break;
        case CHANGER_SETUP:
            result = setup();
            if (result == SUCCESS) {
                state = CHANGER_EXPANSION_ID;
            } else {
                state = CHANGER_SETUP;
            }
            break;
        case CHANGER_EXPANSION_ID:
            result = ID();
            if (result == SUCCESS) {
                state = CHANGER_TUBE_STATUS;
            } else {
                state = CHANGER_EXPANSION_ID;
            }
            break;
        case CHANGER_TUBE_STATUS:
            struct TubeStatus_s TubeStatusResult;
            TubeStatusResult = tubeStatus();
            if (TubeStatusResult.msgStatus == SUCCESS) {
                state = CHANGER_POLL;
                //state = CHANGER_COIN_TYPE;
                initialized = 1; //Inicialización lista.
            } else {
                state = CHANGER_TUBE_STATUS;
            }
            break;
        case CHANGER_COIN_TYPE:
            result = coinType(ACCEPT);
            if (result == 0) {
                state = CHANGER_POLL;
                status = OK;
                initialized = 1; //Inicialización lista.
            } else {
                state = CHANGER_COIN_TYPE;
            }
            break;
    }
    return initialized;
}

struct Setup_s Changer::setupResponseProcess() {
    struct Setup_s Setup;
    Setup.changerFeatureLevel = CoinChanger.data[0];

    Setup.country = CoinChanger.data[1];
    Setup.country <<= 8;
    Setup.country |= CoinChanger.data[2];

    Setup.coinScalingFactor = 0x00ff & CoinChanger.data[3];

    Setup.decimalPlaces = CoinChanger.data[4];

    Setup.coinTypeRouting = CoinChanger.data[5];
    Setup.coinTypeRouting <<= 8;
    Setup.coinTypeRouting = CoinChanger.data[6];

    for (int i = 0; i < 16; i++) {
        Setup.coinTypeCredit[i] = 0x00ff & CoinChanger.data[7 + i];
        //coinTypeValue[i] = Setup.coinScalingFactor * Setup.coinTypeCredit[i];

        coinTypeTubeValue[i][TUBE] = (Setup. coinTypeRouting >> i) & 1;
        coinTypeTubeValue[i][VALUE] = Setup.coinScalingFactor * Setup.coinTypeCredit[i];
        if (changerDebugFlag)
            cout << "Moneda tipo " << i << " tiene valor de " << coinTypeTubeValue[i][VALUE] << endl;
    }

    if (changerDebugFlag) {
        printf("Feature level: %c\n", Setup.changerFeatureLevel);
        printf("Country: %d\n", Setup.country);
        printf("Coin Scaling Factor: %c\n", Setup.coinScalingFactor);
        printf("Decimal places: %c\n", Setup.decimalPlaces);
        printf("\n");
        printf("num\tCoin Type Routing\tCoin Type Credit\n");
        for (int i = 0; i < 16; i++) {
            printf("%d\t\t%d\t\t%d\n", i, (Setup.coinTypeRouting >> i)&1, (int*) Setup.coinTypeCredit[i]);
        }

        printf("\n");
    }
    return Setup;
}

struct Id_s Changer::IdResponseProcess() {
    struct Id_s Id;
    Id.manufacturerCode[0] = CoinChanger.data[0];
    Id.manufacturerCode[1] = CoinChanger.data[1];
    Id.manufacturerCode[2] = CoinChanger.data[2];
    Id.manufacturerCode[3] = 0;

    for (int i = 0; i < 12; i++) {
        Id.serialNumber[i] = CoinChanger.data[i + 3];
    }
    Id.serialNumber[12] = 0;
    for (int i = 0; i < 12; i++) {
        Id.modelNumber[i] = CoinChanger.data[i + 15];
    }
    Id.modelNumber[12] = 0;

    Id.softwareVersion[0] = CoinChanger.data[27];
    Id.softwareVersion[1] = CoinChanger.data[28];

    Id.optionalFeatures[0] = CoinChanger.data[29];
    Id.optionalFeatures[1] = CoinChanger.data[30];
    Id.optionalFeatures[2] = CoinChanger.data[31];
    Id.optionalFeatures[3] = CoinChanger.data[32];

    if (changerDebugFlag) {
        printf("Manufacturer Code: %s\n", Id.manufacturerCode);
        printf("Serial Number: %s\n", Id.serialNumber);
        printf("Model number: %s\n", Id.modelNumber);
        printf("Software version: %2x%2x\n", (int*) Id.softwareVersion[0], (int*) Id.softwareVersion[1]);
        printf("\n\n");
    }
    return Id;
}

struct TubeStatus_s Changer::tubeStatusResponseProcess() {
    struct TubeStatus_s TubeStatus;
    TubeStatus.tubeFullStatus = CoinChanger.data[0];
    TubeStatus.tubeFullStatus <<= 8;
    TubeStatus.tubeFullStatus = CoinChanger.data[1];

    for (int i = 0; i < 16; i++) {
        TubeStatus.tubeStatus[i] = 0x00ff & CoinChanger.data[2 + i];
    }

    if (changerDebugFlag) {
        printf("tube No.\tFull?\tStatus\n");
        for (int i = 0; i < 16; i++) {
            printf("%d \t\t%d\t\t%d\n", i, (TubeStatus.tubeFullStatus >> i)&1, (int*) TubeStatus.tubeStatus[i]);
        }
        printf("\n\n");
    }
    return TubeStatus;
}

struct CoinType_s Changer::setCoinType(int accept) {
    CoinType_s CoinType;
    CoinType.CoinEnable.coinEnable = 0;
    inhibited = 1;
    if (accept == ACCEPT) {
        inhibited = 0;
        for (int i = 0; i < 15; i++) {
            if (coinTypeTubeValue[i][VALUE] > 0) {
                CoinType.CoinEnable.coinEnable |= (1 << i);
            }
        }
    }

    return CoinType;
}

/*
 * En caso de moneda depositada:
 *      regresa tipo de moneda depositada 
 * En caso de status
 *      regresa status + 16 (bit 5 set)
 * pendiente procesar respuestas FTL (poll recibe 16 byte)
 * pendiente procesar monedas despachadas
 */
struct PollResponse Changer::pollProcess() {
    /*
     * Coin deposited: 01yyxxxx   zzzzzzzz
     *                   Z1          Z2                              
     *      yy
     *      00 : Cash Box
     *      01 : Tubes
     *      10 : Not Used
     *      11 : Reject
     * 
     *      xxxx: coin type (0-15)
     *      
     *      zzzzzzzz: amount gone into tube;
     */

    //pendiente procesar respuestas FTL (poll recibe 16 byte)
    struct PollResponse result;

    char coinType;
    coinType = CoinChanger.data[0] & 0x0f;

    if (CoinChanger.dataLen == 2) { // procesa monedas despachadas o depositada
        if ((CoinChanger.data[0] >> 7) == 1) { //if coin dispensed 
            //pendiente. mientras deshabilito dispensar monedas (ver Changer::coinType() )
            result.type = COIN_DISPENSED_MANUAL;


        } else if (((CoinChanger.data[0] >> 6) == 1)) { //if coin deposited
            result.type = COINS_DEPOSITED;

            result.routing = CoinChanger.data[0] >> 4;

            switch (result.routing) {
                case CASHBOX:
                    CoinDeposited.cashBox[coinType]++;
                    if (changerDebugFlag) {
                        printf("Moneda de %d depositada en caja\n", coinTypeTubeValue[coinType][VALUE]);
                    }
                    result.coinType = coinType;
                    break;
                case TUBES:
                    CoinDeposited.tubes[coinType]++;
                    if (changerDebugFlag) {
                        printf("Moneda de %d depositada en tubos\n", coinTypeTubeValue[coinType][VALUE]);
                    }
                    result.coinType = coinType;
                    break;
                case REJECTED:
                    CoinDeposited.reject[coinType]++;
                    result.coinType = -1;
                    break;
                default:
                    if (changerDebugFlag) {
                        cout << "Poll processing. Coin Routing Unkown" << endl;
                    }
                    result.coinType = -1;
            }

        }
    } else if (CoinChanger.dataLen == 1) { //procesa status
        result.type = STATUS;
        result.status = coinType;
    } else {
        cout << "POLL recibió Datos inesperados" << endl;
    }

    return result;
}

int Changer::isInhibited() {
    return inhibited;
}

BillValidator::BillValidator() {

}

int BillValidator::config(int serialfd, int argc, char **argv) {
    debugFlag = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strncmp(argv[i], DEBUG_BILL_VALIDATOR, strlen(DEBUG_BILL_VALIDATOR)) == 0) {
                cout << "Bill Validator debug on" << endl;
                debugFlag = 1;
            }
        }
    }

    mdb_fd = serialfd;
    status = INITIALIZING;
    return mdb_fd;
}

int BillValidator::reset() {
    char cmd = BV_RESET;
    this -> VMC.dataLen = 0;
    if (debugFlag) {
        cout << "Bill Validator RESET\n" << endl;
    }

    do {
        this -> Validator.dataLen = sendCommand(this -> mdb_fd, cmd, this -> VMC.data, this ->VMC.dataLen, this -> Validator.data, STD_TIMEOUT);
    } while (retry++ <= MAX_RETRY && Validator.dataLen == 0);
    if (retry > MAX_RETRY) {
        status = UNPLUGGED;
    }
    retry = 0;

    if (Validator.dataLen == 1 && Validator.data[0] == 0) {
        if (debugFlag)
            cout << "\n Bill Validator reset: ACK \n" << endl;
        return 0;
    } else {
        if (debugFlag)
            cout << "\n Bill Validator reset failed \n" << endl;
        return -1;
    }

}

struct PollResponse BillValidator::poll() {
    char cmd = BV_POLL;
    this -> VMC.dataLen = 0;
    if (debugFlag) {
        printf("Bill Validator POLL\n");
    }
    
    do {
        this -> Validator.dataLen = sendCommand(this -> mdb_fd, cmd, this -> VMC.data, this ->VMC.dataLen, this -> Validator.data, STD_TIMEOUT);
    } while (retry++ <= MAX_RETRY && Validator.dataLen == 0);
    if (retry > MAX_RETRY) {
        status = UNPLUGGED;
    }
    retry = 0;
     struct PollResponse result;
    //    printf("received %2x: ",Validator.dataLen);
    //    for (int i = 0; i < Validator.dataLen; i++) {//Si quito el for falla URGE corregir
    //        printf("%2x ", Validator.data[i]);
    //    }
    //    printf("\n\r ");
    if (Validator.dataLen >= 1) {
       
        if (Validator.data[0] != 0) {
            sendACK(mdb_fd);
        }
        result = pollProcess();

        return result;

    } else {
        result.type = ERROR;
        return result;
    }
}

int BillValidator::setup() {
    char cmd = BV_SETUP;
    VMC.dataLen = 0;
    if (debugFlag) {
        cout << "Bill Validator SETUP" << endl;
    }
    
    do {
        this -> Validator.dataLen = sendCommand(this -> mdb_fd, cmd, this -> VMC.data, this ->VMC.dataLen, this -> Validator.data,STD_TIMEOUT);
    } while (retry++ <= MAX_RETRY && Validator.dataLen == 0);
    if (retry > MAX_RETRY) {
        status = UNPLUGGED;
    }
    retry = 0;
    
    //    printf("received %2x: ",Validator.dataLen);
    //    for (int i = 0; i < Validator.dataLen; i++) {//Si quito el for falla URGE corregir
    //        printf("%2x ", Validator.data[i]);
    //    }
    //printf("\n\r ");
    if (Validator.dataLen >= 12 && Validator.dataLen <= 27) {
        sendACK(mdb_fd);
        if (debugFlag)
            cout << "Bill Validator setup: OK" << endl;
        // this -> Setup.coinTypeRouting.CTR.high = CoinChanger.data[5];
        // this -> Setup.coinTypeRouting.CTR.low = CoinChanger.data[6];
        //this -> Setup.coinTypeRouting = (CoinChanger.data[5] << 8) & CoinChanger.data[6];
        setupResponseProcess();
        return 0;
    } else {
        if (debugFlag)
            cout << "setup failed" << endl;
        return -1;
    }
}

int BillValidator::ID() {
    char cmd = BV_EXPANSION_ID;
    VMC.dataLen = 1;
    VMC.data[0] = 0;
    if (debugFlag) {
        cout << "Bill Validator ID" << endl;
    }
    do {
        this -> Validator.dataLen = sendCommand(this -> mdb_fd, cmd, this -> VMC.data, this ->VMC.dataLen, this -> Validator.data,STD_TIMEOUT);
    } while (retry++ <= MAX_RETRY && Validator.dataLen == 0);
    if (retry > MAX_RETRY) {
        status = UNPLUGGED;
    }
    retry = 0;
    
    if (Validator.dataLen == 29) {
        sendACK(mdb_fd);
        if (debugFlag)
            cout << "Bill Validator ID: OK" << endl;
        IdResponseProcess();
        return 0;
    } else {
        if (debugFlag)
            cout << "ID failed" << endl;
        return -1;
    }
}

int BillValidator::stacker() {
    char cmd = BV_STACKER;
    VMC.dataLen = 0;
    if (debugFlag) {
        cout << "Bill Validator STACKER" << endl;
    }
    
    do {
        this -> Validator.dataLen = sendCommand(this -> mdb_fd, cmd, this -> VMC.data, this ->VMC.dataLen, this -> Validator.data, STD_TIMEOUT);
    } while (retry++ <= MAX_RETRY && Validator.dataLen == 0);
    if (retry > MAX_RETRY) {
        status = UNPLUGGED;
    }
    retry = 0;
    
    if (Validator.dataLen == 2) {
        sendACK(mdb_fd);
        if (debugFlag)
            cout << "Bill Validator stacker: OK" << endl;
        // this -> Setup.coinTypeRouting.CTR.high = CoinChanger.data[5];
        // this -> Setup.coinTypeRouting.CTR.low = CoinChanger.data[6];
        //this -> Setup.coinTypeRouting = (CoinChanger.data[5] << 8) & CoinChanger.data[6];
        stackerResponseProcess();
        return 0;
    } else {
        if (debugFlag)
            cout << "setup failed" << endl;
        return -1;
    }
}

int BillValidator::billType(int accept) {
    char cmd = BV_BIIL_TYPE;
    CoinType_s BillType;
    BillType = setBillType(accept);
    VMC.dataLen = 4;
    //VMC.data[0] = 0x00;
    //VMC.data[1] = 0x3d; //acepta todas las denominaciones HARDCODED
    VMC.data[2] = 0x00; //deshabilita escrow de billetes
    VMC.data[3] = 0x00;

    VMC.data[0] = BillType.CoinEnable.high;
    VMC.data[1] = BillType.CoinEnable.low;
    //        VMC.data[2]= CoinType.ManualDispense.high;
    //        VMC.data[3]=  CoinType.ManualDispense.low;                  
    if (debugFlag)
        cout << "BILL Type" << endl;
    
    
    do {
        this -> Validator.dataLen = sendCommand(this -> mdb_fd, cmd, this -> VMC.data, this ->VMC.dataLen, this -> Validator.data, STD_TIMEOUT);
    } while (retry++ <= MAX_RETRY && Validator.dataLen == 0);
    if (retry > MAX_RETRY) {
        status = UNPLUGGED;
    }
    retry = 0;

    if (Validator.dataLen == 1 && Validator.data[0] == 0) {
        if (debugFlag)
            cout << "Coin Type: ACK" << endl;
        return 0;
    } else
        return -1;
}

int BillValidator::initializeSequence() {
    static int state = BV_RESET;
    int result;
    static int initialized = 0;
    struct PollResponse pollResult;
    
    if(status == UNPLUGGED || status == REINITIALIZE){
        state = BV_RESET;
        initialized = 0;
        status = INITIALIZING;
    }
    
    switch (state) {
        case BV_RESET:
            result = reset();
            if (result == 0) {
                state = BV_POLL;
            } else {
                state = BV_RESET;
            }
            break;

        case BV_POLL:
            pollResult = poll();
            if (pollResult.type == BV_POLL_STATUS && (pollResult.status == _ACK || pollResult.status == VALIDATOR_DISABLED) && !initialized) {
                state = BV_SETUP;
            } else {
                state = BV_POLL;
            }
            break;
        case BV_SETUP:
            result = setup();
            if (result == 0) {
                state = BV_EXPANSION_ID;
            } else {
                state = BV_SETUP;
            }
            break;
        case BV_EXPANSION_ID:
            result = ID();
            if (result == 0) {
                state = BV_STACKER;
            } else {
                state = BV_EXPANSION_ID;
            }
            break;
        case BV_STACKER:
            result = stacker();
            if (result == 0) {
               // state = BV_BIIL_TYPE;
                state = BV_POLL;
                initialized = 1;
            } else {
                state = BV_STACKER;
            }
            break;

        case BV_BIIL_TYPE:
            result = billType(ACCEPT);
            if (result == 0) {
                status = OK;
                initialized = 1;
            } else {
                state = BV_BIIL_TYPE;
            }
            break;
    }
    return initialized;
}

struct PollResponse BillValidator::pollProcess() {
    /*
     * Bill deposited: 1yyyxxxx  
     *                   Z1                                     
     *      yyy : Bill Routing
     *      000 : Bill Stacked
     *      001 : Escrow Position
     *      010 : Bill Returned
     *      011 : Bill to Recycler
     *      100 : Disable Bill Rejected
     *      101 : Bill to Recycler - Manual Fill    
     *      110 : Manual Dispense
     *      111 : Transferred from recycler to cashbox
     *     
     *      xxxx: bill type (0-15)

     */

    //pendiente procesar respuestas FTL (poll recibe 16 byte)
    struct PollResponse result;
    char billType;
    
    if (Validator.data[0] >> 7) {//bill detected;
        result.type = BV_POLL_DEPOSITED;
        billType = Validator.data[0] & 0x0f;

        result.routing = (Validator.data[0] >> 4) & 0b0111;
        switch (result.routing) {
            case BILL_STACKED:

                BillDeposited.stack[billType]++;
                result.coinType = billType;
                break;
            case ESCROW_POSITION:
                BillDeposited.escrow[billType]++;
                result.coinType = billType;
                break;

            case BILL_RETURNED:
                BillDeposited.returned[billType]++;
                result.coinType = -1;
                break;

            case BILL_TO_RECYCLER:
                BillDeposited.recycler[billType]++;
                result.coinType = billType;
                break;

            case DISABLED_BILL_REJECTER:
                BillDeposited.disabled[billType]++;
                result.coinType = -1;
                break;

            case BILL_TO_RECYCLER_MANUAL_FILL:
                BillDeposited.recycler_manual[billType]++;
                result.coinType = -1;
                break;

            case MANUAL_DISPENSE:
                BillDeposited.manual_dispense[billType]++;
                result.coinType = -1;
                break;

            case RECYCLER_TO_CASHBOX:
                BillDeposited.reycler_cashbox[billType]++;
                result.coinType = -1;
                break;
        }
    } else {
        result.type = BV_POLL_STATUS;
        result.status = Validator.data[0] & 0x0f;
    }
    return result;
}

int BillValidator::setupResponseProcess() {

    struct BillSetup_s {
        int featureLevel;
        int country;
        int billScalingFactor;
        char decimalPlaces;
        int stackerCapacity;
        int securityLevels;
        char escrow;
        int bilTypeCredit[16];
    };
    BillSetup_s Setup;

    memset(Setup.bilTypeCredit, 0, 16);
    memset(billTypeValue, 0, 16);

    Setup.featureLevel = Validator.data[0];

    Setup.country = 0x00FF & Validator.data[1]; // tomar bcd no decimal
    Setup.country <<= 8;
    Setup.country |= Validator.data[2];

    Setup.billScalingFactor = 0x00FF & Validator.data[3];
    Setup.billScalingFactor <<= 8;
    Setup.billScalingFactor |= Validator.data[4];

    Setup.decimalPlaces = Validator.data[5];

    Setup.stackerCapacity = Validator.data[6];
    Setup.stackerCapacity <<= 8;
    Setup.stackerCapacity |= Validator.data[7];

    Setup.securityLevels = Validator.data[8];
    Setup.securityLevels <<= 8;
    Setup.securityLevels |= Validator.data[9];

    Setup.escrow = Validator.data[10];
    for (int i = 0; i < Validator.dataLen - 11; i++) {
        Setup.bilTypeCredit[i] = 0x00ff & Validator.data[11 + i];
        billTypeValue[i] = Setup.billScalingFactor * Setup.bilTypeCredit[i];
        if (debugFlag)
            cout << "Billete tipo " << i << " tiene valor de " << billTypeValue[i] << endl;
    }

    if (debugFlag) {
        cout << "Feature level: " << Setup.featureLevel << endl;
        cout << "Country: " << Setup.country << endl;
        cout << "Bill Scaling Factor: " << Setup.billScalingFactor << endl;
        cout << "Decimal places: " << Setup.decimalPlaces << endl;
        cout << "num\t\tBill Type Credit" << endl;
        for (int i = 0; i < Validator.dataLen - 11; i++) {
            cout << i << "\t\t" << Setup.bilTypeCredit[i] << endl;
        }
        cout << endl;
    }
    return 0;
}

int BillValidator::IdResponseProcess() {
    struct Id_s Id;
    Id.manufacturerCode[0] = Validator.data[0];
    Id.manufacturerCode[1] = Validator.data[1];
    Id.manufacturerCode[2] = Validator.data[2];
    Id.manufacturerCode[3] = 0;

    for (int i = 0; i < 12; i++) {
        Id.serialNumber[i] = Validator.data[i + 3];
    }
    Id.serialNumber[12] = 0;
    for (int i = 0; i < 12; i++) {
        Id.modelNumber[i] = Validator.data[i + 15];
    }
    Id.modelNumber[12] = 0;

    Id.softwareVersion[0] = Validator.data[27];
    Id.softwareVersion[1] = Validator.data[28];

    Id.optionalFeatures[0] = 0;
    Id.optionalFeatures[1] = 0;
    Id.optionalFeatures[2] = 0;
    Id.optionalFeatures[3] = 0;

    if (debugFlag) {
        printf("Manufacturer Code: %s\n", Id.manufacturerCode);
        printf("Serial Number: %s\n", Id.serialNumber);
        printf("Model number: %s\n", Id.modelNumber);
        printf("Software version: %2x%2x\n", (int*) Id.softwareVersion[0], (int*) Id.softwareVersion[1]);
        printf("\n\n");
    }
    return 0;

}

int BillValidator::stackerResponseProcess() {

    struct Stacker_s {
        int isFull;
        int amount;
    };

    struct Stacker_s Stacker;
    Stacker.isFull = Validator.data[0] >> 7;
    Stacker.amount = 0x007f & Validator.data[0];
    Stacker.amount <<= 8;
    Stacker.amount = Validator.data[1];

    if (debugFlag) {
        if (Stacker.isFull) {
            cout << "Stacker is full" << endl;
        } else {
            cout << "Stacker is not full" << endl;
        }
        cout << Stacker.amount << " bill in stacker" << endl;
    }
    return 0;

}

struct CoinType_s BillValidator::setBillType(int accept) {
    CoinType_s BillType;
    BillType.CoinEnable.coinEnable = 0;
    inhibited = 1;
    if (accept == ACCEPT) {
        inhibited = 0;
        for (int i = 0; i < 15; i++) {
            if (billTypeValue[i] > 0) {
                BillType.CoinEnable.coinEnable |= (1 << i);
            }
        }
    }
    return BillType;
}

int BillValidator::isInhibited() {
    return inhibited;
}