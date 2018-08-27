/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SPI_OUT.cpp
 * Author: famisa
 * 
 * Created on 6 de noviembre de 2017, 10:43 AM
 */

#include "SPI_OUT.hpp"
#include "SPI_BP5400.hpp"

SPI_OUT::SPI_OUT() {
    
}

int SPI_OUT::set_all(){
    unsigned char data;
    unsigned char cmd;
    
    cmd = 0x30;
    data = 0x02;
    
    return send(cmd,data);
}

int SPI_OUT::clear_all(){
    unsigned char data;
    unsigned char cmd;
    
    cmd = 0x30;
    data= 0x01;
    
    return send(cmd,data);
}

/*int SPI_OUT::set_pin(char pOutputLen, unsigned char pOutput[]) {
    char cmd = 0x31;
    
    return send(cmd,pOutputLen,pOutput);
}
*/
/*int SPI_OUT::clear_pin(char pOutputLen, unsigned char pOutput[]) {
    char cmd = 0x32;
    
    return send(cmd,pOutputLen,pOutput);
}*/

int SPI_OUT::send(unsigned char pCmd, unsigned char pData){
    int aux1, aux2;
    unsigned char msg[30];
    char msglen;
    unsigned char chksum = 0;
    
    int result;
    msglen = 5;
    /*
    msg[0] = 0xff;
    msg[1] = 0xff;
    msg[2] = 0xff;
    */
    
    msg[0] = 0x02;
    msg[1] = pCmd;
    //msg[2] = pDataLen;
    
    msg[2] = pData;
    
    
    for(aux2 = 0; aux2 < msglen - 2; aux2++){
        chksum ^= msg[aux2];
    }
    msg[3] = chksum;
    msg[4] = 0x03;
    result = SPI_BP5400::transfer(msg,this -> answer, msglen);
    return result;
}