/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MDBDevice.h
 * Author: Oscar Maradiaga
 *
 * Created on 24 de abril de 2018, 11:48 AM
 */


#ifndef MDBBUS_H
#define MDBBUS_H

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <cstdio>
#include <iostream>
using namespace std;

#define DEBUG_MDB   "--debug_MDB"

#define ODD     1
#define EVEN    2

#define ACK     0x0
#define RET     0xAA
#define NAK     0xFF

#define STD_TIMEOUT    10000 // 10ms
#define LONG_TIMEOUT    20000 //100ms
char mdbDebugFlag;

//prototipos de funcion

int initializeMDB(int argc, char** argv, char pPort);
int sendCommand(int serialfd, char pCommand, char *pData, char pDataLength, char response[36], int pTimeout);
int sendACK(int serialfd);
int sendRET(int serialfd);
//int serial_fp;
//int serial_fp_2;

int openPort(char pPort);
int closePort(int serialfd);
int writeMDB(int serialfd, char pTxData[10], char rxData[36], char dataLength, int pTimeout);
int readMDB(int serialfd, char DataRead[36], int pTimeout);
// char mdbDebugFlag;
#endif

/*
 * int initializeMDB(int argc, char** argv, char pPort) 
 *      int         argc        numero de argumentos del main
 *      char**      argv        argumentos del main
 *      char        pPort       numero de puerto correspondiente a MDB (1 o 4) 
 * 
 * PURPOSE :    Inicializa bandera de debug y manda a abril puerto serial 
 *              correspondiente al MDB
 *
 * RETURN :      serialfd       descriptor puerto serie. -1 si falla.
 * 
 * NOTES :      
 *      [1]Busca el parametro de la funcion --debug_MDB para activar bandera de debug
 *      [2]Abre el puerto serial y devuelve el descriptor del puerto serie
 */
int initializeMDB(int argc, char** argv, char pPort) {
    int serialfd;
    mdbDebugFlag = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strncmp(argv[i], DEBUG_MDB, strlen(DEBUG_MDB)) == 0) {
                cout << "MDB debug on" << endl;
                mdbDebugFlag = 1;
            }
        }
    }

    serialfd = openPort(pPort);
    if (serialfd < 0) {
        return -1;
    }
    return serialfd;
}

/*
 * int openPort(char pPort) 
 *      char        pPort       numero de puerto correspondiente a MDB (1 o 4) 
 * 
 * PURPOSE :    Abre y configura puerto serial para uso con MDB
 *
 * RETURN :      serialfd       descriptor puerto serie. -1 si falla.
 * 
 * NOTES :      
 *      [1]concatena numero de puerto a la direccion
 *      [2]Abre el puerto serial 
 *      [3]Configura 8 bits, no paridad, 38400bps,
 *      [4}Devuelve descriptor serial  
 */
int openPort(char pPort) {
    struct termios newtermios;
    int serialfd;

    char SerialNameCom[15] = "/dev/ttyO";
    // Open the serial port
    SerialNameCom[9] = pPort + '0';
    serialfd = open(SerialNameCom, O_RDWR | O_NOCTTY);
    if (serialfd == -1) {
        fflush(stdout);
        printf("Error al abrir puerto serial %s\n", SerialNameCom);
        return -1;
    }

    if (tcgetattr(serialfd, &newtermios) == -1) {
        return -1;
    }
    //    newtermios.c_cflag |= CBAUD | CS8 | CLOCAL | CREAD; //8 bits, habilita lectura
    //    newtermios.c_cflag &= ~(PARENB | CBAUDEX | CIBAUD);      // deshabilita paridad
    //    newtermios.c_iflag |= IGNPAR;       //ignora paridad
    //    newtermios.c_iflag &= ~(INLCR | INPCK | ISTRIP | INLCR | ICRNL | IUCLC | IXANY) ;       // evita mapear NL (newline - 0x0a) a CR (carriage return 0x0d)
    //    newtermios.c_oflag = 0;
    //    newtermios.c_lflag = 0;
    //    newtermios.c_cc[VMIN] = 1;
    //    newtermios.c_cc[VTIME] = 0;

    newtermios.c_cflag |= CBAUD | CS8 | CLOCAL | CREAD; //8 bits, habilita lectura
    newtermios.c_cflag &= ~(PARENB | CBAUDEX | CIBAUD); // deshabilita paridad
    newtermios.c_iflag |= IGNPAR; //ignora paridad
    //newtermios.c_iflag &= ~(INLCR | INPCK | ISTRIP | INLCR | ICRNL | IUCLC | IXANY | IGNCR| IXOFF | IMAXBEL | IXON) ;       // evita mapear NL (newline - 0x0a) a CR (carriage return 0x0d)
    newtermios.c_iflag = 0;
    newtermios.c_oflag = 0;
    newtermios.c_lflag = 0;
    newtermios.c_cc[VMIN] = 1;
    newtermios.c_cc[VTIME] = 5;

    cfsetospeed(&newtermios, B38400); //38499 baud
    cfsetispeed(&newtermios, B38400);

    if (tcflush(serialfd, TCIFLUSH) == -1) { //vacia buffers
        return -1;
    }


    if (tcflush(serialfd, TCOFLUSH) == -1) {
        return -1;
    }

    if (tcsetattr(serialfd, TCSANOW, &newtermios) == -1) { //aplica cambios YA
        return -1;
    }
    if (mdbDebugFlag){
        //printf("open port %s succesfull\n", SerialNameCom);
    }
    //-- Return the file descriptor
    return serialfd;
}

/*
 * int sendCommand(int serialfd, char pCommand, char *pData, char pDataLength, char response[36]) 
 *      int     serialfd            descriptor serial del puerto al que transmitirá buffer
 *      char    pCommand            comando de periférico MDB
 *      char*   pData               datos de VMC 
 *      char    pDataLength         longitud de datos de VMC (0 si no hay datos)
 *      char    response[36]        apuntador a buffer donde se almacenará respuesta de MDB
 * 
 * PURPOSE :    prepara buffer con los datos que se transmitiran al puerto serie 
 *              y los envía a funcion que escribe en puerto serial.
 *
 * RETURN :     resultado de writeMDB(). cantidad de datos recibidos por puerto serial.
 * 
 * NOTES :      
 *      [1]prepara buffer con forma:
 *              0x02   n(length) CMD DATA(optional) checksum 
 *               0          1     2    ........       n-1 
 *      [2]calcula checksum 
 *      [3]Envía datos a funcion que escribirá buffer y recibirá respuesta.
 *      [4]Devuelve cantidad de datos en respuesta 
 */
int sendCommand(int serialfd, char pCommand, char* pData, char pDataLength, char response[36], int pTimeout) {
    //0x02 Length CMD DATA(optional) checksum 
    //0     1      2   .......          n-1    
    char txData[38] = {};
    char rxData[36];
    char index = 2;
    char checksum = 0;
    int result;
    txData[0] = 0x02;
    txData[1] = 2 + pDataLength;
    txData[index++] = pCommand;
    checksum = pCommand;
    for (int i = 0; i < pDataLength; i++) {
        txData[index++] = pData[i];
        checksum += pData[i];
    }
    txData[index++] = checksum;
    result = writeMDB(serialfd, txData, rxData, index, pTimeout);
    for (int i = 0; i < result; i++) {
        response[i] = rxData[i];
    }
    return result;
}

/*
 * int sendACK(int serialfd) 
 *      int     serialfd            descriptor serial del puerto al que transmitirá buffer
 * 
 * PURPOSE :    Envía ACK (0x00) por puerto serial. 

 * RETURN :     int     bytesWritten    numero de datos escritos en puerto serial
 * 
 * NOTES :      Protocolo MDB indica que VMC debe responder con ACK si el mensaje
 *              de periférico contiene datos y el checksum es correcto.
 *              
 */
int sendACK(int serialfd) {
    int bytesWritten;
    char byteACK = 0x00;
    bytesWritten = write(serialfd, &byteACK, 1);
        if (mdbDebugFlag){
            //printf("%d written: ACK \n", bytesWritten);
        }
    return bytesWritten;
}

/*
 * int sendRET(int serialfd) 
 *      int     serialfd            descriptor serial del puerto al que transmitirá buffer
 * 
 * PURPOSE :    Envía RET (0xAA) por puerto serial. 

 * RETURN :     int     bytesWritten    numero de datos escritos en puerto serial
 * 
 * NOTES :    Protocolo MDB indica que VMC debe responder con RET si el mensaje
 *            de periférico contiene datos y el checksum es incorrecto. 
 *               
 */
int sendRET(int serialfd) {
    int bytesWritten;
    char byteRET = 0xAA;

    bytesWritten = write(serialfd, &byteRET, 1);
    if (mdbDebugFlag){ 
        //printf("%d written: RET \n", bytesWritten);
    }
}

/*
 * int writeMDB(int serialfd, char pTxData[10], char rxData[36], char dataLength) 
 *      int     serialfd        descriptor serial del puerto al que transmitirá buffer
 *      char    pTxData[10]     apuntador a buffer con los datos a tranmitir
 *      char    rxData[36]      apuntador a buffer con los datos recibidos
 *      char    dataLength      longitud de datos a transmitir
 * 
 * PURPOSE :    Transmite mensaje MDB y llama a funcion para recibir respuesta 

 * RETURN :     int     bytesRead    numero de datos recibidos en puerto serial
 * 
 * NOTES :    {1} Vacia buffers de entrada y salida de puerto serial
 *            [2] Transmite mensaje MDB por Puerto serie 
 *            [3] Lee datos del puerto y transmite RET para reinter la lectura un máximo de 3 veces, en caso de ser necesario
 *            {4} si la bandera de debug esta activada, despliega datos recibidos en pantalla
 *            [5] Devuelve cantidad de datos recibidos en el mensaje MDB (sin incluir checksum) 
 *               
 */
int writeMDB(int serialfd, char pTxData[38], char rxData[36], char dataLength, int pTimeout) {
    int bytesWritten;
    char rxData1[36]; //Guarda Datos de primera lectura
    int bytesRead; //almacena cantidad de datos leídos
    int RETcount = 0;
    char txData[38];
    memset(txData,0,38);
    memcpy(txData,pTxData,38);
    memset(rxData1, 0, 36);


    if (tcflush(serialfd, TCIOFLUSH) == -1) {
        return -1;
    }

    bytesWritten = write(serialfd, txData, dataLength); //pendiente validar que se manden todos los datos;
    if (mdbDebugFlag){
        printf("%d written \n", bytesWritten);
    }
    do {
        bytesRead = readMDB(serialfd, rxData1, pTimeout); //leer resultado
        if (bytesRead == RET) {
            sendRET(serialfd);
            RETcount++;
        }
    } while ((RETcount <= 3) && (bytesRead == RET)); //reintentar si la funcion de lectura obtuvo checksum errone (RET). intentar 3 veces;
    if (bytesRead == RET) {
        return -1;
    }

    if (mdbDebugFlag) {
        //cout << "Debug on"<<endl;
        printf("Data Received[%d]:", bytesRead);
    }
    for (int i = 0; i < bytesRead; i++) {
        rxData[i] = rxData1[i];
        if (mdbDebugFlag) {
           printf(" %2x", rxData[i]);
        }
    }
    if (mdbDebugFlag) {
        printf(" \n");
    }
    //cout << "Debug off"<<endl;
    //
    //printf("\r"); //Si lo quito no funciona URGE CORREGIR

    return bytesRead;
    //return Port1.bytesRead;
}

/*
 * int readMDB(int serialfd, char * DataRead) 
 *      int     serialfd        descriptor serial del puerto al que transmitirá buffer
 *      char    DataRead[36]    apuntador a buffer con los datos recibidos
 * 
 * PURPOSE :    Recibe datos de puerto serial, los almacena en un buffer, y calcula el checksum 
 * 
 * RETURN :     int     count    numero de datos recibidos en puerto serial
 * 
 * NOTES :    {1} Selecciona el descriptor serial para revisar si esta listo para lectura
 *            [2] Si selector indica que hay dato, lo lee, almacena, incrementa cuenta y calcula checksum
 *            [3] valida checksum y si se recibe dato con checksum se excluye el checksum del buffer de datos recibidos
 *            {4} mueve datos recibidos a buffer de apuntador indicado por parametro de función (checksum exluido)
 *            [5] Devuelve cantidad de datos recibidos en el mensaje MDB (sin incluir checksum) 
 *               
 */
int readMDB(int serialfd, char DataRead[36], int pTimeout) {
    fd_set fds;
    char dataBuffer[37];
    struct timeval timeout;
    int count = 0;
    int ret = 0;
    int n, i, MaxValT = 37; //maxima cantidad de datos a recibir manual indica 36 (37 con checksum?)
    char checksum;
    timeout.tv_sec = 0;
    //timeout.tv_usec = 10000; //define timeout 10ms (para evitar que ocurra timeout con comandos largos
    timeout.tv_usec = pTimeout;
    do {
        FD_ZERO(&fds);
        FD_SET(serialfd, &fds);
        ret = select(FD_SETSIZE, &fds, NULL, NULL, &timeout); //monitorea puerto en espera de un dato; regra 1 si hay dato en puerto
        if (ret == 1) { //si hay dato en puerto
            n = read(serialfd, &dataBuffer[count], 1); //lee datos en puerto 
            //printf("%02x ",dataBuffer[count]);
            checksum += dataBuffer[count]; //calcula checksum 
            count += n; //incrementa contador de datos recibidos
            timeout.tv_usec = 1500;
        }
    } while (count < MaxValT && ret == 1); //mientras no se exceda cantidad maxima de datos y siga habiendo datso es puerto
    //printf ("\n received %d bytes.",count);
    checksum -= dataBuffer[count - 1]; //resta ultimo dato a cáclulo de checksum
    if (count > 0) { //si se recibieron mas de 0 datos
        if (checksum != dataBuffer[count - 1]) { //si el ultimo dato recibido es diferente a checksum calculado
            return RET;
        }
        if (count > 1) { //para excluir checksum
            count--;
            //sendACK(serialfd);
        }
    }
    for (int i = 0; i < count; i++) { //transfiere datos a buffer
        DataRead[i] = dataBuffer[i];
    }
    return count;
}

int closePort(int serialfd) {
    return close(serialfd);
}

