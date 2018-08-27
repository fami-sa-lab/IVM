/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   famiserial.h
 * Author: Isaac
 *
 * Created on 31 de julio de 2018, 10:59 AM
 */

#ifndef FAMISERIAL_H
#define FAMISERIAL_H
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstdio>
#include <iostream>
class Famiserial{
public:
   Famiserial();
    Famiserial(int pPort); 
   int openPort(char pPort);
   int writeSerial(char pTxData[], int dataLength);
   int readSerial(char DataRead[], int MaxValT);
   int closePort(); 
   int debugFlag;
   
private:
    int serialfd;
    
    
};

#endif /* FAMISERIAL_H */
Famiserial::Famiserial(){
     debugFlag = 0;
}

Famiserial::Famiserial(int pPort){
     openPort(pPort);
}

int Famiserial::openPort(char pPort) {
    struct termios newtermios;
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
    newtermios.c_cflag |= CBAUD | CS8 | CLOCAL | CREAD; //8 bits, habilita lectura
    newtermios.c_cflag &= ~(PARENB | CBAUDEX | CIBAUD); // deshabilita paridad
    newtermios.c_iflag |= IGNPAR; //ignora paridad
    //newtermios.c_iflag &= ~(INLCR | INPCK | ISTRIP | INLCR | ICRNL | IUCLC | IXANY | IGNCR| IXOFF | IMAXBEL | IXON) ;       // evita mapear NL (newline - 0x0a) a CR (carriage return 0x0d)
    newtermios.c_iflag = 0;
    newtermios.c_oflag = 0;
    newtermios.c_lflag = 0;
    newtermios.c_cc[VMIN] = 1;
    newtermios.c_cc[VTIME] = 5;

    cfsetospeed(&newtermios, B9600); //38400 baud
    cfsetispeed(&newtermios, B9600);

    if (tcflush(serialfd, TCIFLUSH) == -1) { //vacia buffers
        return -1;
    }


    if (tcflush(serialfd, TCOFLUSH) == -1) {
        return -1;
    }

    if (tcsetattr(serialfd, TCSANOW, &newtermios) == -1) { //aplica cambios YA
        return -1;
    }
    //-- Return the file descriptor
    return serialfd;
}

int Famiserial::writeSerial(char pTxData[], int dataLength) {
    int bytesWritten;
    char txData[500];
    memset(txData,0,500);
    memcpy(txData,pTxData,500);

    if (tcflush(serialfd, TCIOFLUSH) == -1) {
        return -1;
    }

    bytesWritten = write(serialfd, txData, dataLength); //pendiente validar que se manden todos los datos;
    if (debugFlag){
        printf("%d written \n", bytesWritten);
    }       
    
    return bytesWritten;
}
 

            
 
int Famiserial::readSerial(char DataRead[], int MaxValT) {
    fd_set fds;
    char dataBuffer[500];
    struct timeval timeout;
    int count = 0, ret = 0;
    int n, i; //maxima cantidad de datos a recibir manual indica 36 (37 con checksum?)
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000; //define timeout 10ms (para evitar que ocurra timeout con comandos largos
    
    do {
        FD_ZERO(&fds);
        FD_SET(serialfd, &fds);
        ret = select(FD_SETSIZE, &fds, NULL, NULL, &timeout); //monitorea puerto en espera de un dato; regra 1 si hay dato en puerto
        if (ret == 1) { //si hay dato en puerto
            n = read(serialfd, &dataBuffer[count], MaxValT - count); //lee datos en puerto 
            count += n; //incrementa contador de datos recibidos
            timeout.tv_usec = 1500;
        }
    } while (count < MaxValT && ret == 1); //mientras no se exceda cantidad maxima de datos y siga habiendo datso es puerto
    
    
    if (debugFlag && count > 0) {
        //cout << "Debug on"<<endl;
        printf("Data Received[%d]:", count);
    }
    
    for (int i = 0; i < count; i++) { //transfiere datos a buffer
        DataRead[i] = dataBuffer[i];
        if (debugFlag) {
           printf(" %2x",  DataRead[i]);
        }
    }
    
    if (debugFlag && count > 0) {
        printf(" \n");
    }
     
    return count;
}

int Famiserial::closePort() {
    return close(serialfd);
}
