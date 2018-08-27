/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   corte.h
 * Author: Isaac
 *
 * Created on 30 de julio de 2018, 12:20 PM
 */

#ifndef CORTE_H
#define CORTE_H


#include <string.h>
#include "famiserial.h"
#include <iostream>
using namespace std;

#define  DEBUG_CORTE    "--debug_Corte"

/*Numero de maquina y folio*/
#define NUM_MAQ_L       0x00
#define NUM_MAQ_H       0x01
#define FOLIO_L         0x02
#define FOLIO_H         0x03

/*Version de software FAMISA*/
#define SOFTWARE_VERSION 0x04

/*Datos Monedero*/
#define CHANGER_MFR_00    0x05
#define CHANGER_MFR_01      0x06
#define CHANGER_MFR_02      0x07

#define CHANGER_SERIAL_00   0x08
#define CHANGER_SERIAL_01   0x09
#define CHANGER_SERIAL_02   0x0A
#define CHANGER_SERIAL_03   0x0B
#define CHANGER_SERIAL_04   0x0C
#define CHANGER_SERIAL_05   0x0D
#define CHANGER_SERIAL_06   0x0E
#define CHANGER_SERIAL_07   0x0F
#define CHANGER_SERIAL_08   0x10
#define CHANGER_SERIAL_09   0x11
#define CHANGER_SERIAL_10   0x12
#define CHANGER_SERIAL_11   0x13

#define CHANGER_MODEL_00   0x14
#define CHANGER_MODEL_01   0x15
#define CHANGER_MODEL_02   0x16
#define CHANGER_MODEL_03   0x17
#define CHANGER_MODEL_04   0x18
#define CHANGER_MODEL_05   0x19
#define CHANGER_MODEL_06   0x1A
#define CHANGER_MODEL_07   0x1B
#define CHANGER_MODEL_08   0x1C
#define CHANGER_MODEL_09   0x1D
#define CHANGER_MODEL_10   0x1E
#define CHANGER_MODEL_11   0x1F

/*Datos Billetero*/

#define BILL_MFR_00   0x20
#define BILL_MFR_01   0x21
#define BILL_MFR_02   0x22

#define BILL_SERIAL_00   0x23
#define BILL_SERIAL_01   0x24
#define BILL_SERIAL_02   0x25
#define BILL_SERIAL_03   0x26
#define BILL_SERIAL_04   0x27
#define BILL_SERIAL_05   0x28
#define BILL_SERIAL_06   0x29
#define BILL_SERIAL_07   0x2A
#define BILL_SERIAL_08   0x2B
#define BILL_SERIAL_09   0x2C
#define BILL_SERIAL_10   0x2D
#define BILL_SERIAL_11   0x2E

#define BILL_MODEL_00   0x2F
#define BILL_MODEL_01   0x30
#define BILL_MODEL_02   0x31
#define BILL_MODEL_03   0x32
#define BILL_MODEL_04   0x33
#define BILL_MODEL_05   0x34
#define BILL_MODEL_06   0x35
#define BILL_MODEL_07   0x36
#define BILL_MODEL_08   0x37
#define BILL_MODEL_09   0x38
#define BILL_MODEL_10   0x39
#define BILL_MODEL_11   0x3A


/*Cantidad de Ventas de X,Y y Z Kilos*/
#define VENTAAK_L       0x3B
#define VENTAAK_H       0x3C
#define VENTABK_L       0x3D
#define VENTABK_H       0x3E
#define VENTACK_L       0x3F
#define VENTACK_H       0x40
#define VENTADK_L       0x41
#define VENTADK_H       0x42

/*Precio de los productos*/
#define PRECIOAK_L        0x43
#define PRECIOAK_H        0x44

#define PRECIOBK_L        0x45
#define PRECIOBK_H        0x46

#define PRECIOCK_L        0x47
#define PRECIOCK_H        0x48

#define PRECIODK_L        0x49
#define PRECIODK_H        0x4A

/*Factor moneda*/
#define COIN_FAC        0x4B

/*Numero de monedas en tubos*/
#define NUM_MONTUB_50C_L    0x4C
#define NUM_MONTUB_50C_H    0x4D
#define NUM_MONTUB_1P_L     0x4E
#define NUM_MONTUB_1P_H     0x4F  
#define NUM_MONTUB_2P_L     0x50
#define NUM_MONTUB_2P_H     0x51
#define NUM_MONTUB_5P_L     0x52
#define NUM_MONTUB_5P_H     0x53
#define NUM_MONTUB_10P_L    0x54
#define NUM_MONTUB_10P_H    0x55
//#define NUM_MONTUB_20P_L
//#define NUM_MONTUB_20P_H

/*Numero de monedas en caja, 2 bytes para cada una de las 16 posibles denominaciones*/
#define MONCAJ_50C_L    0x56
#define MONCAJ_50C_H    0x57
#define MONCAJ_1P_L     0x58
#define MONCAJ_1P_H     0x59
#define MONCAJ_2P_L     0x5A
#define MONCAJ_2P_H     0x5B
#define MONCAJ_5P_L     0x5C
#define MONCAJ_5P_H     0x5D
#define MONCAJ_10P_L    0x5E
#define MONCAJ_10P_H    0x5F
#define MONCAJ_20P_L    0x60
#define MONCAJ_20P_H    0x61

#define MONCAJ_DEN7_L   0x62
#define MONCAJ_DEN7_H   0x63
#define MONCAJ_DEN8_L   0x64
#define MONCAJ_DEN8_H   0x65
#define MONCAJ_DEN9_L   0x66
#define MONCAJ_DEN9_H   0x67
#define MONCAJ_DEN10_L  0x68
#define MONCAJ_DEN10_H  0x69
#define MONCAJ_DEN11_L  0x6A
#define MONCAJ_DEN11_H  0x6B
#define MONCAJ_DEN12_L  0x6C
#define MONCAJ_DEN12_H  0x6D
#define MONCAJ_DEN13_L  0x6E
#define MONCAJ_DEN13_H  0x6F
#define MONCAJ_DEN14_L  0x70
#define MONCAJ_DEN14_H  0x71
#define MONCAJ_DEN15_L  0x72
#define MONCAJ_DEN15_H  0x73
#define MONCAJ_DEN16_L  0x74
#define MONCAJ_DEN16_H  0x75

/*Monedas entregadas como cambio*/
#define MONDEL_50C_L    0x76
#define MONDEL_50C_H    0x77
#define MONDEL_1P_L     0x78
#define MONDEL_1P_H     0x79
#define MONDEL_2P_L     0x7A
#define MONDEL_2P_H     0x7B
#define MONDEL_5P_L     0x7C
#define MONDEL_5P_H     0x7D
#define MONDEL_10P_L    0x7E
#define MONDEL_10P_H    0x7F

/*Factor Billete*/
#define FACTOR_BILLETE  0x80

/*Numero de Billetes en caja, 2 bytes para cada una de las 16 posibles denominaciones*/
#define BILLCAJ_20P_L   0x81
#define BILLCAJ_20P_H   0x82
#define BILLCAJ_50P_L   0x83
#define BILLCAJ_50P_H   0x84
#define BILLCAJ_100P_L  0x85
#define BILLCAJ_100P_H  0x86
#define BILLCAJ_200P_L  0x87
#define BILLCAJ_200P_H  0x88
#define BILLCAJ_500P_L  0x89
#define BILLCAJ_500P_H  0x8A
#define BILLCAJ_1000P_L 0x8B
#define BILLCAJ_1000P_H 0x8C

#define BILLCAJ_DEN7_L  0x8D
#define BILLCAJ_DEN7_H  0x8E
#define BILLCAJ_DEN8_L  0x8F
#define BILLCAJ_DEN8_H  0x90
#define BILLCAJ_DEN9_L  0x91
#define BILLCAJ_DEN9_H  0x92
#define BILLCAJ_DEN10_L 0x93
#define BILLCAJ_DEN10_H 0x94
#define BILLCAJ_DEN11_L 0x95
#define BILLCAJ_DEN11_H 0x96
#define BILLCAJ_DEN12_L 0x97
#define BILLCAJ_DEN12_H 0x98
#define BILLCAJ_DEN13_L 0x99
#define BILLCAJ_DEN13_H 0x9A
#define BILLCAJ_DEN14_L 0x9B
#define BILLCAJ_DEN14_H 0x9C
#define BILLCAJ_DEN15_L 0x9D
#define BILLCAJ_DEN15_H 0x9F
#define BILLCAJ_DEN16_L 0x100
#define BILLCAJ_DEN16_H 0x101

/*Billetes entregadas como cambio*/
#define BILLDEL_20P_L   0x102
#define BILLDEL_20P_H   0x103
#define BILLDEL_50P_L   0x104
#define BILLDEL_50P_H   0x105
#define BILLDEL_100P_L  0x106
#define BILLDEL_100P_H  0x107
#define BILLDEL_200P_L  0x108
#define BILLDEL_200P_H  0x109

/*ALERTAS*/
#define SAL_CAJA        0x10A
#define HIELO_MANUAL_L  0x10B
#define HIELO_MANUAL_H  0x10C
#define TAPON_MANUAL    0x10D                                                    //Probablemente no se use esto   
#define ERROR_TAPON     0x10E                                                    //Probablemente no se use esto  
#define FALLA_ELECTRICA 0x10F

/*Errores monedero*/
#define CHN_ESCROW      0x110
#define CHN_NOCREDIT    0x111
#define CHN_TUBSEN      0x112
#define CHN_DOBARRV     0x113
#define CHN_UNPLUGG     0x114
#define CHN_TUBERJAM    0x115
#define CHN_ROMERROR    0x116
#define CHN_ROUTERROR   0x117
#define CHN_RESET       0x118
#define CHN_COINJAM     0x119

/*Errores Billetero*/
#define FUTURO_00     0x11A
#define FUTURO_01     0x11B
#define FUTURO_02     0x11C
#define FUTURO_03     0x11D
#define FUTURO_04     0x11E
#define FUTURO_05     0x11F
#define FUTURO_06     0x120
#define FUTURO_07     0x121
#define FUTURO_08     0x122
#define FUTURO_09     0x123


/*Futuro*/
#define FUTURO_10     0x124
#define FUTURO_11     0x125
#define FUTURO_12     0x126
#define FUTURO_13     0x127
#define FUTURO_14     0x128
#define FUTURO_15     0x129
#define FUTURO_16     0x12A
#define FUTURO_17     0x12B
#define FUTURO_18     0x12C


/*Check sum*/
#define CHECKSUM        0x12D

#define PARTE_ALTA  2
#define PARTE_BAJA  1    

class Corte : protected Famiserial {
public:

    Corte();
    int config(int argc, char** argv, int pPort);
    

    int setNumeroMaquina(int pNumeroMaquina);
    int setFolio(int pFolio);
    int setVentas(int pVentasA, int pVentasB, int pVentasC, int pVentasD);
    int setPrecios(int pPrecioA, int pPrecioB, int pPrecioC, int pPrecioD);
    int setTubosIn(int pMXN50c, int pMXN1p, int pMXN2p, int pMXN5p, int pMXN10p, int pMXN20p);
    int setTubosOut(int pMXN50c, int pMXN1p, int pMXN2p, int pMXN5p, int pMXN10p, int pMXN20p);
    int setCajaMonedas(int pMXN50c, int pMXN1p, int pMXN2p, int pMXN5p, int pMXN10p, int pMXN20p);
    int SetCajaBilletes(int pMXN20p, int pMXN50p, int pMXN100p, int pMXN200p, int pMXN500p, int pMXN1000p);

    int getRequest();
    int corteBluetooth();

    int printBuffer();

    void acomodar_Corte(void);
private:
    unsigned char int_To_Char(unsigned int dato, unsigned int byteAregresar);
    char calcular_Checksum();
    int openBluetooth(int pPort);
    
    char buffer_Corte[CHECKSUM + 1];
    int debugFlag;


};
#endif /* CORTE_H */

int Corte::printBuffer() {
    int count = 0;
    for (int i = 0; i < (sizeof (buffer_Corte) / sizeof (buffer_Corte[0])); i++) {
        cout << hex << static_cast<int> (buffer_Corte[i]) << " ";
        count++;
        if (count >= 10) {
            count = 0;
            cout << endl;
        }
    }
}

int Corte::getRequest() {
    char serialBuffer[10];
    char cmpBuffer[4] = {0, 0, 'H', 'H'};
    if (Famiserial::readSerial(serialBuffer, 4) == 4) {
        if (memcmp(cmpBuffer, serialBuffer, sizeof (cmpBuffer)) == 0) {

            //if (Famiserial::writeSerial(cmpBuffer, 4) == 4) {
            //sleep(1);
            return 1;
            //}
        }
    }
    return 0;
}

int Corte::corteBluetooth() {
    char serialBuffer[10];
    char cmpBuffer[4] = {0, 0, 'B', 'B'};
    char response[1] = {'@'};
    int retry = 0;
    
    buffer_Corte[CHANGER_MFR_00] = 'M';
    buffer_Corte[CHANGER_MFR_01] = 'E';
    buffer_Corte[CHANGER_MFR_02] = '1';
    
    buffer_Corte[CHANGER_SERIAL_00] = 'X';
    buffer_Corte[CHANGER_SERIAL_01] = 'X';
    buffer_Corte[CHANGER_SERIAL_02] = 'X';
    buffer_Corte[CHANGER_SERIAL_03] = 'X';
    buffer_Corte[CHANGER_SERIAL_04] = 'X';
    buffer_Corte[CHANGER_SERIAL_05] = 'X';
    buffer_Corte[CHANGER_SERIAL_06] = 'X';
    buffer_Corte[CHANGER_SERIAL_07] = 'X';
    buffer_Corte[CHANGER_SERIAL_08] = 'X';
    buffer_Corte[CHANGER_SERIAL_09] = 'X';
    buffer_Corte[CHANGER_SERIAL_10] = 'X';
    buffer_Corte[CHANGER_SERIAL_11] = 'X';
    
    buffer_Corte[CHANGER_MODEL_00] = 'Z';
    buffer_Corte[CHANGER_MODEL_01] = 'Z';
    buffer_Corte[CHANGER_MODEL_02] = 'Z';
    buffer_Corte[CHANGER_MODEL_03] = 'Z';
    buffer_Corte[CHANGER_MODEL_04] = 'Z';
    buffer_Corte[CHANGER_MODEL_05] = 'Z';
    buffer_Corte[CHANGER_MODEL_06] = 'Z';
    buffer_Corte[CHANGER_MODEL_07] = 'Z';
    buffer_Corte[CHANGER_MODEL_08] = 'Z';
    buffer_Corte[CHANGER_MODEL_09] = 'Z';
    buffer_Corte[CHANGER_MODEL_10] = 'Z';
    buffer_Corte[CHANGER_MODEL_11] = 'Z';
    
    buffer_Corte[BILL_MFR_00] = 'M';
    buffer_Corte[BILL_MFR_01] = 'E';
    buffer_Corte[BILL_MFR_02] = '1';
    
    buffer_Corte[BILL_SERIAL_00] = 'X';
    buffer_Corte[BILL_SERIAL_01] = 'X';
    buffer_Corte[BILL_SERIAL_02] = 'X';
    buffer_Corte[BILL_SERIAL_03] = 'X';
    buffer_Corte[BILL_SERIAL_04] = 'X';
    buffer_Corte[BILL_SERIAL_05] = 'X';
    buffer_Corte[BILL_SERIAL_06] = 'X';
    buffer_Corte[BILL_SERIAL_07] = 'X';
    buffer_Corte[BILL_SERIAL_08] = 'X';
    buffer_Corte[BILL_SERIAL_09] = 'X';
    buffer_Corte[BILL_SERIAL_10] = 'X';
    buffer_Corte[BILL_SERIAL_11] = 'X';
    
    buffer_Corte[BILL_MODEL_00] = 'Z';
    buffer_Corte[BILL_MODEL_01] = 'Z';
    buffer_Corte[BILL_MODEL_02] = 'Z';
    buffer_Corte[BILL_MODEL_03] = 'Z';
    buffer_Corte[BILL_MODEL_04] = 'Z';
    buffer_Corte[BILL_MODEL_05] = 'Z';
    buffer_Corte[BILL_MODEL_06] = 'Z';
    buffer_Corte[BILL_MODEL_07] = 'Z';
    buffer_Corte[BILL_MODEL_08] = 'Z';
    buffer_Corte[BILL_MODEL_09] = 'Z';
    buffer_Corte[BILL_MODEL_10] = 'Z';
    buffer_Corte[BILL_MODEL_11] = 'Z';
    
    
    
    
    calcular_Checksum();
    if (Famiserial::writeSerial(buffer_Corte, sizeof (buffer_Corte)) >= sizeof (buffer_Corte)) {
        if (debugFlag) {
            printBuffer();
        }       
        do {
            usleep(20000);
            if (Famiserial::readSerial(serialBuffer, 4) == 4) {
                if (memcmp(cmpBuffer, serialBuffer, sizeof (cmpBuffer)) == 0) {
                    if (Famiserial::writeSerial(response, 1) == 1) {
                        return 1;
                    }
                }

            }
        } while (retry++ <= 1000);
    }
    return 0;
}

Corte::Corte() {
    memset(buffer_Corte, 0x0, (sizeof (buffer_Corte) / sizeof (buffer_Corte[0])));

}

int Corte::config(int argc, char** argv, int pPort){
    debugFlag = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strncmp(argv[i], DEBUG_CORTE, strlen(DEBUG_CORTE)) == 0) {
                cout << "Corte debug on" << endl;
                debugFlag = 1;
                Famiserial::debugFlag = 1;
            }
        }
    }
    return openBluetooth(pPort);
}

int Corte::openBluetooth(int pPort) {
    return Famiserial::openPort(pPort);
}

int Corte::setNumeroMaquina(int pNumeroMaquina) {
    buffer_Corte[NUM_MAQ_L] = int_To_Char(pNumeroMaquina, PARTE_BAJA);
    buffer_Corte[NUM_MAQ_H] = int_To_Char(pNumeroMaquina, PARTE_ALTA);
    if (debugFlag) {
        cout << "Numero de Maquina: " << dec << pNumeroMaquina << "-- 0x" << hex << pNumeroMaquina << endl;
        cout << dec << NUM_MAQ_L << ": " << hex << static_cast<int> (int_To_Char(pNumeroMaquina, PARTE_BAJA)) << endl;
        cout << dec << NUM_MAQ_H << ": " << hex << static_cast<int> (int_To_Char(pNumeroMaquina, PARTE_ALTA)) << endl;
        cout << endl;
    }


    return 0;
}

int Corte::setFolio(int pFolio) {
    buffer_Corte[FOLIO_L] = int_To_Char(pFolio, PARTE_BAJA); //parte baja Folio;
    buffer_Corte[FOLIO_H] = int_To_Char(pFolio, PARTE_ALTA);
    if (debugFlag) {
        cout << "Folio: " << dec << pFolio << "-- 0x" << hex << pFolio << endl;
        cout << dec << FOLIO_L << ": " << hex << static_cast<int> (int_To_Char(pFolio, PARTE_BAJA)) << endl;
        cout << dec << FOLIO_H << ": " << hex << static_cast<int> (int_To_Char(pFolio, PARTE_ALTA)) << endl;
        cout << endl;
    }
    return 0;
}

int Corte::setVentas(int pVentasA, int pVentasB, int pVentasC, int pVentasD) {
    buffer_Corte[VENTAAK_L] = int_To_Char(pVentasA, PARTE_BAJA);
    buffer_Corte[VENTAAK_H] = int_To_Char(pVentasA, PARTE_ALTA);

    if (debugFlag) {
        cout << "Ventas A: " << dec << pVentasA << "-- 0x" << hex << pVentasA << endl;
        cout << dec << VENTAAK_L << ": " << hex << static_cast<int> (int_To_Char(pVentasA, PARTE_BAJA)) << endl;
        cout << dec << VENTAAK_H << ": " << hex << static_cast<int> (int_To_Char(pVentasA, PARTE_ALTA)) << endl;
    }

    buffer_Corte[VENTABK_L] = int_To_Char(pVentasB, PARTE_BAJA);
    buffer_Corte[VENTABK_H] = int_To_Char(pVentasB, PARTE_ALTA);

    if (debugFlag) {
        cout << "Ventas B: " << dec << pVentasB << "-- 0x" << hex << pVentasB << endl;
        cout << dec << VENTABK_L << ": " << hex << static_cast<int> (int_To_Char(pVentasB, PARTE_BAJA)) << endl;
        cout << dec << VENTABK_L << ": " << hex << static_cast<int> (int_To_Char(pVentasB, PARTE_ALTA)) << endl;
    }

    buffer_Corte[VENTACK_L] = int_To_Char(pVentasC, PARTE_BAJA);
    buffer_Corte[VENTACK_H] = int_To_Char(pVentasC, PARTE_ALTA);

    if (debugFlag) {
        cout << "Ventas C: " << dec << pVentasC << "-- 0x" << hex << pVentasC << endl;
        cout << dec << VENTACK_L << ": " << hex << static_cast<int> (int_To_Char(pVentasC, PARTE_BAJA)) << endl;
        cout << dec << VENTACK_H << ": " << hex << static_cast<int> (int_To_Char(pVentasC, PARTE_ALTA)) << endl;
    }

    buffer_Corte[VENTADK_L] = int_To_Char(pVentasD, PARTE_BAJA);
    buffer_Corte[VENTADK_H] = int_To_Char(pVentasD, PARTE_ALTA);

    if (debugFlag) {
        cout << "Ventas D: " << dec << pVentasD << "-- 0x" << hex << pVentasD << endl;
        cout << dec << VENTADK_L << ": " << hex << static_cast<int> (int_To_Char(pVentasD, PARTE_BAJA)) << endl;
        cout << dec << VENTADK_H << ": " << hex << static_cast<int> (int_To_Char(pVentasD, PARTE_ALTA)) << endl;
        cout << endl;
    }




    return 0;
}

int Corte::setPrecios(int pPrecioA, int pPrecioB, int pPrecioC, int pPrecioD) {
    buffer_Corte[PRECIOAK_L] = int_To_Char(pPrecioA, PARTE_BAJA);
    buffer_Corte[PRECIOAK_H] = int_To_Char(pPrecioA, PARTE_ALTA);

    if (debugFlag) {
        cout << "pPrecioA " << dec << pPrecioA << "-- 0x" << hex << pPrecioA << endl;
        cout << dec << PRECIOAK_L << ": " << hex << static_cast<int> (int_To_Char(pPrecioA, PARTE_BAJA)) << endl;
        cout << dec << PRECIOAK_H << ": " << hex << static_cast<int> (int_To_Char(pPrecioA, PARTE_ALTA)) << endl;
    }

    buffer_Corte[PRECIOBK_L] = int_To_Char(pPrecioB, PARTE_BAJA);
    buffer_Corte[PRECIOBK_H] = int_To_Char(pPrecioB, PARTE_ALTA);

    if (debugFlag) {
        cout << "pPrecioB " << dec << pPrecioB << "-- 0x" << hex << pPrecioB << endl;
        cout << dec << PRECIOBK_L << ": " << hex << static_cast<int> (int_To_Char(pPrecioB, PARTE_BAJA)) << endl;
        cout << dec << PRECIOBK_H << ": " << hex << static_cast<int> (int_To_Char(pPrecioB, PARTE_ALTA)) << endl;
    }

    buffer_Corte[PRECIOCK_L] = int_To_Char(pPrecioC, PARTE_BAJA);
    buffer_Corte[PRECIOCK_H] = int_To_Char(pPrecioC, PARTE_ALTA);

    if (debugFlag) {
        cout << "pPrecioC " << dec << pPrecioC << "-- 0x" << hex << pPrecioC << endl;
        cout << dec << PRECIOCK_L << ": " << hex << static_cast<int> (int_To_Char(pPrecioC, PARTE_BAJA)) << endl;
        cout << dec << PRECIOCK_H << ": " << hex << static_cast<int> (int_To_Char(pPrecioC, PARTE_ALTA)) << endl;
    }


    buffer_Corte[PRECIODK_L] = int_To_Char(pPrecioD, PARTE_BAJA);
    buffer_Corte[PRECIODK_H] = int_To_Char(pPrecioD, PARTE_ALTA);

    if (debugFlag) {
        cout << "pPrecioD " << dec << pPrecioD << "-- 0x" << hex << pPrecioD << endl;
        cout << dec << PRECIODK_L << ": " << hex << static_cast<int> (int_To_Char(pPrecioD, PARTE_BAJA)) << endl;
        cout << dec << PRECIODK_H << ": " << hex << static_cast<int> (int_To_Char(pPrecioD, PARTE_ALTA)) << endl;
        cout << endl;
    }


    return 0;
}

int Corte::setTubosIn(int pMXN50c, int pMXN1p, int pMXN2p, int pMXN5p, int pMXN10p, int pMXN20p) {
    cout << "Tubos IN" << endl;
    buffer_Corte[NUM_MONTUB_50C_L] = int_To_Char(pMXN50c, PARTE_BAJA); //Monedas en tubo de 50c
    buffer_Corte[NUM_MONTUB_50C_H] = int_To_Char(pMXN50c, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN50c " << dec << pMXN50c << "-- 0x" << hex << pMXN50c << endl;
        cout << dec << NUM_MONTUB_50C_L << ": " << hex << static_cast<int> (int_To_Char(pMXN50c, PARTE_BAJA)) << endl;
        cout << dec << NUM_MONTUB_50C_H << ": " << hex << static_cast<int> (int_To_Char(pMXN50c, PARTE_ALTA)) << endl;
    }

    buffer_Corte[NUM_MONTUB_1P_L] = int_To_Char(pMXN1p, PARTE_BAJA); //Monedas en tubos de 1p
    buffer_Corte[NUM_MONTUB_1P_H] = int_To_Char(pMXN1p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN1p " << dec << pMXN1p << "-- 0x" << hex << pMXN1p << endl;
        cout << dec << NUM_MONTUB_1P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN1p, PARTE_BAJA)) << endl;
        cout << dec << NUM_MONTUB_1P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN1p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[NUM_MONTUB_2P_L] = int_To_Char(pMXN2p, PARTE_BAJA); //Monedas en tubos de 2p
    buffer_Corte[NUM_MONTUB_2P_H] = int_To_Char(pMXN2p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN2p " << dec << pMXN2p << "-- 0x" << hex << pMXN2p << endl;
        cout << dec << NUM_MONTUB_2P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN2p, PARTE_BAJA)) << endl;
        cout << dec << NUM_MONTUB_2P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN2p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[NUM_MONTUB_5P_L] = int_To_Char(pMXN5p, PARTE_BAJA); //monedas en tubos de 5p
    buffer_Corte[NUM_MONTUB_5P_H] = int_To_Char(pMXN5p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN5p " << dec << pMXN5p << "-- 0x" << hex << pMXN5p << endl;
        cout << dec << NUM_MONTUB_5P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN5p, PARTE_BAJA)) << endl;
        cout << dec << NUM_MONTUB_5P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN5p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[NUM_MONTUB_10P_L] = int_To_Char(pMXN10p, PARTE_BAJA); //monedas en tubos de 5p
    buffer_Corte[NUM_MONTUB_10P_H] = int_To_Char(pMXN10p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN10p " << dec << pMXN10p << "-- 0x" << hex << pMXN10p << endl;
        cout << dec << NUM_MONTUB_10P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN10p, PARTE_BAJA)) << endl;
        cout << dec << NUM_MONTUB_10P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN10p, PARTE_ALTA)) << endl;
        cout << endl;
    }
    return 0;
}

int Corte::setTubosOut(int pMXN50c, int pMXN1p, int pMXN2p, int pMXN5p, int pMXN10p, int pMXN20p) {
    cout << "Tubos OUT" << endl;
    buffer_Corte[MONDEL_50C_L] = int_To_Char(pMXN50c, PARTE_BAJA); //Monedas en tubo de 50c
    buffer_Corte[MONDEL_50C_H] = int_To_Char(pMXN50c, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN50c " << dec << pMXN50c << "-- 0x" << hex << pMXN50c << endl;
        cout << dec << MONDEL_50C_L << ": " << hex << static_cast<int> (int_To_Char(pMXN50c, PARTE_BAJA)) << endl;
        cout << dec << MONDEL_50C_H << ": " << hex << static_cast<int> (int_To_Char(pMXN50c, PARTE_ALTA)) << endl;
    }

    buffer_Corte[MONDEL_1P_L] = int_To_Char(pMXN1p, PARTE_BAJA); //Monedas en tubos de 1p
    buffer_Corte[MONDEL_1P_H] = int_To_Char(pMXN1p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN1p " << dec << pMXN1p << "-- 0x" << hex << pMXN1p << endl;
        cout << dec << MONDEL_1P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN1p, PARTE_BAJA)) << endl;
        cout << dec << MONDEL_1P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN1p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[MONDEL_2P_L] = int_To_Char(pMXN2p, PARTE_BAJA); //Monedas en tubos de 2p
    buffer_Corte[MONDEL_2P_H] = int_To_Char(pMXN2p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN2p " << dec << pMXN2p << "-- 0x" << hex << pMXN2p << endl;
        cout << dec << MONDEL_2P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN2p, PARTE_BAJA)) << endl;
        cout << dec << MONDEL_2P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN2p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[MONDEL_5P_L] = int_To_Char(pMXN5p, PARTE_BAJA); //monedas en tubos de 5p
    buffer_Corte[MONDEL_5P_H] = int_To_Char(pMXN5p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN5p " << dec << pMXN5p << "-- 0x" << hex << pMXN5p << endl;
        cout << dec << MONDEL_5P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN5p, PARTE_BAJA)) << endl;
        cout << dec << MONDEL_5P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN5p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[MONDEL_10P_L] = int_To_Char(pMXN10p, PARTE_BAJA); //monedas en tubos de 5p
    buffer_Corte[MONDEL_10P_H] = int_To_Char(pMXN10p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN10p " << dec << pMXN10p << "-- 0x" << hex << pMXN10p << endl;
        cout << dec << MONDEL_10P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN10p, PARTE_BAJA)) << endl;
        cout << dec << MONDEL_10P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN10p, PARTE_ALTA)) << endl;
        cout << endl;
    }

    return 0;
}

int Corte::setCajaMonedas(int pMXN50c, int pMXN1p, int pMXN2p, int pMXN5p, int pMXN10p, int pMXN20p) {
    cout << "Caja Monedas" << endl;

    buffer_Corte[MONCAJ_50C_L] = int_To_Char(pMXN50c, PARTE_BAJA); //Monedas en tubo de 50c
    buffer_Corte[MONCAJ_50C_H] = int_To_Char(pMXN50c, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN50c " << dec << pMXN50c << "-- 0x" << hex << pMXN50c << endl;
        cout << dec << MONCAJ_50C_L << ": " << hex << static_cast<int> (int_To_Char(pMXN50c, PARTE_BAJA)) << endl;
        cout << dec << MONCAJ_50C_H << ": " << hex << static_cast<int> (int_To_Char(pMXN50c, PARTE_ALTA)) << endl;
    }

    buffer_Corte[MONCAJ_1P_L] = int_To_Char(pMXN1p, PARTE_BAJA); //Monedas en tubos de 1p
    buffer_Corte[MONCAJ_1P_H] = int_To_Char(pMXN1p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN1p " << dec << pMXN1p << "-- 0x" << hex << pMXN1p << endl;
        cout << dec << MONCAJ_1P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN1p, PARTE_BAJA)) << endl;
        cout << dec << MONCAJ_1P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN1p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[MONCAJ_2P_L] = int_To_Char(pMXN2p, PARTE_BAJA); //Monedas en tubos de 2p
    buffer_Corte[MONCAJ_2P_H] = int_To_Char(pMXN2p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN2p " << dec << pMXN2p << "-- 0x" << hex << pMXN2p << endl;
        cout << dec << MONCAJ_2P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN2p, PARTE_BAJA)) << endl;
        cout << dec << MONCAJ_2P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN2p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[MONCAJ_5P_L] = int_To_Char(pMXN5p, PARTE_BAJA); //monedas en tubos de 5p
    buffer_Corte[MONCAJ_5P_H] = int_To_Char(pMXN5p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN5p " << dec << pMXN5p << "-- 0x" << hex << pMXN5p << endl;
        cout << dec << MONCAJ_5P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN5p, PARTE_BAJA)) << endl;
        cout << dec << MONCAJ_5P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN5p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[MONCAJ_10P_L] = int_To_Char(pMXN10p, PARTE_BAJA); //monedas en tubos de 5p
    buffer_Corte[MONCAJ_10P_H] = int_To_Char(pMXN10p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN10p " << dec << pMXN10p << "-- 0x" << hex << pMXN10p << endl;
        cout << dec << MONCAJ_10P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN10p, PARTE_BAJA)) << endl;
        cout << dec << MONCAJ_10P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN10p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[MONCAJ_20P_L] = int_To_Char(pMXN20p, PARTE_BAJA); //monedas en tubos de 5p
    buffer_Corte[MONCAJ_20P_H] = int_To_Char(pMXN20p, PARTE_ALTA);
    if (debugFlag) {
        cout << "pMXN10p " << dec << pMXN20p << "-- 0x" << hex << pMXN20p << endl;
        cout << dec << MONCAJ_20P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN20p, PARTE_BAJA)) << endl;
        cout << dec << MONCAJ_20P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN20p, PARTE_ALTA)) << endl;
        cout << endl;
    }
    return 0;
}

int Corte::SetCajaBilletes(int pMXN20p, int pMXN50p, int pMXN100p, int pMXN200p, int pMXN500p, int pMXN1000p) {
    cout << "Caja Billetes" << endl;
    buffer_Corte[BILLCAJ_20P_L] = int_To_Char(pMXN20p, PARTE_BAJA);
    buffer_Corte[BILLCAJ_20P_H] = int_To_Char(pMXN20p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN20p " << dec << pMXN20p << "-- 0x" << hex << pMXN20p << endl;
        cout << dec << BILLCAJ_20P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN20p, PARTE_BAJA)) << endl;
        cout << dec << BILLCAJ_20P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN20p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[BILLCAJ_50P_L] = int_To_Char(pMXN50p, PARTE_BAJA);
    buffer_Corte[BILLCAJ_50P_H] = int_To_Char(pMXN50p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN50p " << dec << pMXN50p << "-- 0x" << hex << pMXN50p << endl;
        cout << dec << BILLCAJ_50P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN50p, PARTE_BAJA)) << endl;
        cout << dec << BILLCAJ_50P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN50p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[BILLCAJ_100P_L] = int_To_Char(pMXN100p, PARTE_BAJA);
    buffer_Corte[BILLCAJ_100P_H] = int_To_Char(pMXN100p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN100p " << dec << pMXN100p << "-- 0x" << hex << pMXN100p << endl;
        cout << dec << BILLCAJ_100P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN100p, PARTE_BAJA)) << endl;
        cout << dec << BILLCAJ_100P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN100p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[BILLCAJ_200P_L] = int_To_Char(pMXN200p, PARTE_BAJA);
    buffer_Corte[BILLCAJ_200P_H] = int_To_Char(pMXN200p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN200p " << dec << pMXN200p << "-- 0x" << hex << pMXN200p << endl;
        cout << dec << BILLCAJ_200P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN200p, PARTE_BAJA)) << endl;
        cout << dec << BILLCAJ_200P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN200p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[BILLCAJ_500P_L] = int_To_Char(pMXN500p, PARTE_BAJA);
    buffer_Corte[BILLCAJ_500P_H] = int_To_Char(pMXN500p, PARTE_ALTA);
    if (debugFlag) {
        cout << "pMXN500p " << dec << pMXN500p << "-- 0x" << hex << pMXN500p << endl;
        cout << dec << BILLCAJ_500P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN500p, PARTE_BAJA)) << endl;
        cout << dec << BILLCAJ_500P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN500p, PARTE_ALTA)) << endl;
    }

    buffer_Corte[BILLCAJ_1000P_L] = int_To_Char(pMXN1000p, PARTE_BAJA);
    buffer_Corte[BILLCAJ_1000P_H] = int_To_Char(pMXN1000p, PARTE_ALTA);

    if (debugFlag) {
        cout << "pMXN1000p " << dec << pMXN1000p << "-- 0x" << hex << pMXN1000p << endl;
        cout << dec << BILLCAJ_1000P_L << ": " << hex << static_cast<int> (int_To_Char(pMXN1000p, PARTE_BAJA)) << endl;
        cout << dec << BILLCAJ_1000P_H << ": " << hex << static_cast<int> (int_To_Char(pMXN1000p, PARTE_ALTA)) << endl;
    }

    return 0;

}

unsigned char Corte::int_To_Char(unsigned int dato, unsigned int byteAregresar) {
    unsigned char MSB = 0;
    unsigned char LSB = 0;

    MSB = ((dato & 0x0000FF00) >> 8);
    LSB = (dato & 0x000000FF);
    if (byteAregresar == PARTE_ALTA) {
        return MSB;
    }
    if (byteAregresar == PARTE_BAJA) {
        return LSB;
    }
}

char Corte::calcular_Checksum() {
    char suma = 0;
    for (int i = 0; i < (sizeof (buffer_Corte) / sizeof (buffer_Corte[0])) - 1; i++) {
        suma += buffer_Corte[i];
    }
    buffer_Corte[CHECKSUM] = suma;
    return 0;
}



