/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MDBDevice.h
 * Author: Isaac
 *
 * Created on 24 de abril de 2018, 11:48 AM
 */

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#ifndef MDBDEVICE_H
#define MDBDEVICE_H

#define ODD     1
#define EVEN    2

#define ACK     0x0
#define RET     0xAA
#define NAK     0xFF

struct port {
    int serialfp;
    char rxData[36];
    int bytesWritten;
    int bytesRead;
    int parity;
};

class MDBDevice {
public:
    MDBDevice();
    int initializeMDB(char txPort, char rxPort);
    int sendCommand(char pCommand, char *pData, char pDataLength, char response[36]);
    int sendACK();
    int sendRET();
    //int serial_fp;
    //int serial_fp_2;
private:
    int openPort(char pPort);
    int writeMDB(char pTxData[10], char rxData[36], char dataLength);
    int readMDB(char * DataRead);
    int getTotalOnes(char pByte);


    struct port PortTx;
    struct port PortRx;
};


#endif /* MDBDEVICE_H */

MDBDevice::MDBDevice() {

}

int MDBDevice::initializeMDB(char txPort, char rxPort) {
    PortTx.serialfp = openPort(txPort);
    if (PortTx.serialfp < 0) {
        return -1;
    }
    PortRx.serialfp = openPort(rxPort);
    if (PortRx.serialfp < 0) {
        return -1;
    }
    return 0;
}

int MDBDevice::openPort(char pPort) {
    struct termios newtermios;
    int fp;

    char SerialNameCom[15] = "/dev/ttyO";
    // Open the serial port
    SerialNameCom[9] = pPort + 48;
    fp = open(SerialNameCom, O_RDWR | O_NOCTTY);
    if (fp == -1) {
        fflush(stdout);
        printf("Error al abrir puerto serial %s\n", SerialNameCom);
        return -1;
    }

    newtermios.c_cflag = CBAUD | CS8 | PARENB | PARODD | CLOCAL | CREAD;
    newtermios.c_iflag |= (INPCK);
    newtermios.c_iflag &= ~(IGNPAR | ISTRIP | PARMRK);
    newtermios.c_oflag = 0;
    newtermios.c_lflag = 0;
    newtermios.c_cc[VMIN] = 1;
    newtermios.c_cc[VTIME] = 0;

    // Set the speed
    cfsetospeed(&newtermios, B9600);
    cfsetispeed(&newtermios, B9600);

    // flush the input buffer
    if (tcflush(fp, TCIFLUSH) == -1) {
        return -1;
    }

    // flush the output buffer
    if (tcflush(fp, TCOFLUSH) == -1) {
        return -1;
    }

    //-- Configure the serial port now!!
    if (tcsetattr(fp, TCSANOW, &newtermios) == -1) {
        return -1;
    }
    printf("open port %s succesfull\n", SerialNameCom);
    //-- Return the file descriptor

    return fp;
}

int MDBDevice::sendCommand(char pCommand, char *pData, char pDataLength, char response[36]) {
    char txData[36] = {};
    char index = 0;
    char checksum = 0;
    txData[index++] = pCommand;
    checksum = pCommand;
    for (int i = 0; i < pDataLength; i++) {
        txData[index++] = pData[i];
        checksum += pData[i];
    }
    txData[index++] = checksum;
    writeMDB(txData, response, index);
}

int MDBDevice::sendACK() {
    char byteACK = 0x00;
    struct termios modtermios;
    if (tcgetattr(PortTx.serialfp, &modtermios) == -1) {
        return -1;
    }
    modtermios.c_cflag |= PARENB | CMSPAR;
    modtermios.c_cflag &= ~PARODD;
    if (tcsetattr(PortTx.serialfp, TCSANOW, &modtermios) == -1) {
        return -1;
    }

    PortTx.bytesWritten = write(PortTx.serialfp, &byteACK, 1);
    printf("%d written \n", PortTx.bytesWritten);
}

/*int MDBDevice::sendRET() {
    char byteACK = 0xAA;
    struct termios modtermios;
    if (tcgetattr(Port1.serialfp, &modtermios) == -1) {
        return -1;
    }
    modtermios.c_cflag |= PARENB | CMSPAR;
    modtermios.c_cflag &= ~PARODD;
    if (tcsetattr(Port1.serialfp, TCSANOW, &modtermios) == -1) {
        return -1;
    }

    Port1.bytesWritten = write(Port1.serialfp, &byteACK, 1);
    printf("%d written \n", Port1.bytesWritten);
}
 */
int MDBDevice::writeMDB(char pTxData[10], char rxData[36], char dataLength) {

    char rxData1[36]; //Guarda Datos de primera lectura
    char rxData2[36]; //Guarda Datos de segunda Lectura
    char *txPtr; //puntero hacia dato a transmitir 
    int result; //almacena cantidad de datos leídos
    char parityFlag = ODD;
    char byteACK = 0xAA;

    //limpia buffers de recepcion y transmision
    if (tcflush(PortTx.serialfp, TCIOFLUSH) == -1) {
        return -1;
    }
    if (tcflush(PortRx.serialfp, TCIOFLUSH) == -1) {
        return -1;
    }

    //limpia buffers de datos
    memset(rxData1, 0, 36);
    memset(rxData2, 0, 36);

    //obtiene configuracion de puerto seriañ
    struct termios modtermios;
    struct termios modtermios2;

    if (tcgetattr(PortTx.serialfp, &modtermios) == -1) {
        return -1;
    }

    if (tcgetattr(PortRx.serialfp, &modtermios2) == -1) {
        return -1;
    }

    modtermios.c_cflag |= PARENB; //Habilita paridad y deshabilita CMSPAR
    modtermios.c_cflag &= ~CMSPAR;

    modtermios2.c_cflag |= PARENB | PARODD; //Habilita paridad y deshabilita CMSPAR
    if (tcsetattr(PortRx.serialfp, TCSANOW, &modtermios2) == -1) {
        return -1;
    }
    for (int i = 0; i < dataLength; i++) {
        txPtr = pTxData + i;
        switch (i) {
            case 0:
                //modtermios.c_cflag |= PARODD;
                if (getTotalOnes(*txPtr) % 2) {
                    modtermios.c_cflag &= ~PARODD;
                } else {
                    modtermios.c_cflag |= PARODD;
                }
                break;
            default:
                //modtermios.c_cflag &= ~PARODD;
                if (getTotalOnes(*txPtr) % 2) {
                    modtermios.c_cflag |= PARODD;
                } else {
                    modtermios.c_cflag &= ~PARODD;
                }
        }
        if (tcsetattr(PortTx.serialfp, TCSANOW, &modtermios) == -1) {
            return -1;
        }
        if(dataLength > 2)//daba problemas cuando empece a mandar comandos con datos
            usleep(600);
        PortTx.bytesWritten += write(PortTx.serialfp, txPtr, 1);
    }
    result = readMDB(rxData1);

    if (result > 1 ) { //pendiente agregar mas condiciones
        modtermios2.c_cflag &= ~PARODD;
        if (tcsetattr(PortRx.serialfp, TCSANOW, &modtermios2) == -1) {
            return -1;
        }

        //RET
        modtermios.c_cflag &= ~PARODD;
        if (tcsetattr(PortTx.serialfp, TCSANOW, &modtermios) == -1) {
            return -1;
        }
        
        //Envia ACK: pendiente verificar Checksum previamente.
        PortTx.bytesWritten = write(PortTx.serialfp, &byteACK, 1);
        printf("%d written \n", PortTx.bytesWritten);
        //sendRET();
        //prepara paridad para leer segunda vuelta
        readMDB(rxData2);
    }

    printf("Data Received[%d]:", result);
    for (int i = 0; i < result; i++) {
        rxData[i] = rxData1[i] | rxData2[i];
        printf(" %2x", rxData[i]);
    }
    printf(" \n");
    return result;
    //return Port1.bytesRead;
}

int MDBDevice::readMDB(char * DataRead) {

    fd_set fds;
    struct timeval timeout;
    int count = 0;
    int ret = 0;
    int n, i, MaxValT = 36;

    timeout.tv_sec = 0;
    timeout.tv_usec = 5000;
    do {
        FD_ZERO(&fds);
        FD_SET(PortRx.serialfp, &fds);
        ret = select(FD_SETSIZE, &fds, NULL, NULL, &timeout);
        if (ret == 1) {
            n = read(PortRx.serialfp, &PortRx.rxData[count], MaxValT - count);
            count += n;
            timeout.tv_usec = 3000;
        }
    } while (count < MaxValT && ret == 1);
    PortRx.bytesRead = count;
    printf("Port2: received %d bytes\n", PortRx.bytesRead);

    printf("Data Received[%d]:", count);
    for (i = 0; i < count; i++) {
        DataRead[i] = PortRx.rxData[i];
        printf(" %2x", DataRead[i]);
    }
    printf("\n");
    //-- Return the number of bytes read. 0 If a timeout has occurred.
    return count;
}

int MDBDevice::getTotalOnes(char pByte) {
    int result = 0;

    for (int i = 0; i < 8; i++) {
        result += (pByte & (0x80 >> i))>> (7 - i);
    }
    return result;
}