/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   spi_io.cpp
 * Author: Isaac
 * 
 * Created on 17 de febrero de 2018, 10:08 PM
 */

#include "spi_io.hpp"

spi_io::spi_io() {

}

int spi_io::writeHigh(unsigned char pOutput) {

    unsigned char msg[5];
    unsigned char answer[5];
    GPIO CS_02(67);
    GPIO CS_01(68);
    if (pOutput >= 0 && pOutput <= 7) {
        msg[0] = 0x02;
        if (pOutput == ALL) {
            msg[1] = 0x30;
            msg[2] = 0x02;
        } else {
            msg[1] = 0x31;
            msg[2] = 1 << pOutput;
        }
        
        msg[3] = 0X2 ^ msg[2] ^ msg[1];
        msg[4] = 0x03;
        CS_01.setValue(LOW);
        CS_02.setValue(HIGH);
        int result = SPI_BP5400::transfer(msg, answer, 5);
        return result;
    } else {
        return -1;
    }
}

int spi_io::writeLow(unsigned char pOutput) {
    unsigned char msg[5];
    unsigned char answer[5];
    GPIO CS_01(68);
    GPIO CS_02(67);
    if (pOutput >= 0 && pOutput <= 7) {
        msg[0] = 0x02;
        if (pOutput == ALL) {
            msg[1] = 0x30;
            msg[2] = 0x01;
        } else {
            msg[1] = 0x32;
            msg[2] = 1 << pOutput;
        }

        msg[3] = 0X2 ^ msg[2] ^ msg[1];
        msg[4] = 0x03;
        CS_01.setValue(LOW);
        CS_02.setValue(HIGH);
        int result = SPI_BP5400::transfer(msg, answer, 5);
        return result;
    } else {
        return -1;
    }
}


int spi_io::writePort(unsigned char pOutputs) {
    unsigned char msg[5];
    unsigned char answer[5];
    GPIO CS_01(68);
    GPIO CS_02(67);
 
        
        msg[0] = 0x02;
        msg[1] = 0x33;
        msg[2] = pOutputs;
 
        msg[3] = 0X31 ^ msg[2];
        msg[4] = 0x03;
        CS_01.setValue(LOW);
        CS_02.setValue(HIGH);
        int result = SPI_BP5400::transfer(msg, answer, 5);
        return result;
    
}

int spi_io::readInput(unsigned char pInput){
    unsigned char msg[4];
    unsigned char answer[4];
    
    GPIO CS_01(68);
    GPIO CS_02(67);
    
    msg[0] = 0x02;
    msg[1] = 0x40;
    msg[2] = 0xff;
    msg[3] = 0xff;
    
    CS_01.setValue(HIGH);
    CS_02.setValue(HIGH);
    
    SPI_BP5400::transfer(msg, answer, 4);
    if(pInput <= 7){
        return ((answer[2] >> pInput)&1);
    }else{
        return ((answer[3] >> (pInput-8))&1);
    }    
    
}

int spi_io::readInputs(unsigned char pInputs[]){
    unsigned char msg[4];
    unsigned char answer[4];
    
    GPIO CS_01(68);
    GPIO CS_02(67);
    
    msg[0] = 0x02;
    msg[1] = 0x40;
    msg[2] = 0xff;
    msg[3] = 0xff;
    
    CS_01.setValue(HIGH);
    CS_02.setValue(HIGH);
    
       
    SPI_BP5400::transfer(msg, answer, 4);
    
    pInputs[0] = (answer[2] >> 0) & 1;
    pInputs[1] = (answer[2] >> 1) & 1;
    pInputs[2] = (answer[2] >> 2) & 1;
    pInputs[3] = (answer[2] >> 3) & 1;
    pInputs[4] = (answer[2] >> 4) & 1;
    pInputs[5] = (answer[2] >> 5) & 1;
    pInputs[6] = (answer[2] >> 6) & 1;
    pInputs[7] = (answer[2] >> 7) & 1;
    
    pInputs[8] = (answer[3] >> 0) & 1;
    pInputs[9] = (answer[3] >> 1) & 1;
    return 0;   
    
}
