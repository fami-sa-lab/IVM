/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SPI_BP5400.cpp
 * Author: famisa
 * 
 * Created on 6 de noviembre de 2017, 10:05 AM
 */

#include "SPI_BP5400.hpp"

SPI_BP5400::SPI_BP5400() {
    this -> bits = 5;
    this -> mode = 1;
    this -> speed = 100000;
}

int  SPI_BP5400::openSPI(){
    if ((fd = open(SPI_PATH, O_RDWR)) < 0) {
        perror("SPI Error: Can't open device.");
        return -1;
    }
    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) {
        perror("SPI: Can't set SPI mode.");
        return -1;
    }
    if (ioctl(fd, SPI_IOC_RD_MODE, &mode) == -1) {
        perror("SPI: Can't get SPI mode.");
        return -1;
    }
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1) {
        perror("SPI: Can't set bits per word.");
        return -1;
    }
    if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) == -1) {
        perror("SPI: Can't get bits per word.");
        return -1;
    }
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {
        perror("SPI: Can't set max speed HZ");
        return -1;
    }
    if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) == -1) {
        perror("SPI: Can't get max speed HZ.");
        return -1;
    }
}

void SPI_BP5400::closeSPI() {
    close(fd); 
}

int SPI_BP5400::transfer(unsigned char tx_data[],unsigned char rx_data[],int length){
    int i;
    int result;
    for(i = 0; i < length; i++){
        result = txfer(&tx_data[i],&rx_data[i]);
        if( result < 0){
            return result;
        }
    }
    return result;
}
int SPI_BP5400::txfer(unsigned char send[], unsigned char receive[]){
    struct spi_ioc_transfer transfer; //the transfer structure
    transfer.tx_buf = (unsigned long) send; //the buffer for sending data
    transfer.rx_buf = (unsigned long) receive; //the buffer for receiving data
    transfer.len = 5; //the length of buffer
    transfer.speed_hz = this -> speed; //the speed in Hz
    transfer.bits_per_word = this -> bits; //bits per word
    transfer.delay_usecs = 0; //delay in us
    transfer.pad = 0;
    // send the SPI message (all of the above fields, inc. buffers)
    int status = ioctl(this -> fd, SPI_IOC_MESSAGE(1), &transfer);
    if (status < 0) {
        perror("SPI: SPI_IOC_MESSAGE Failed");
        return -1;
    }
    return status;
}

/*int SPI_BP5400::txfer(unsigned char send[], unsigned char receive[]){
    struct spi_ioc_transfer transfer; //the transfer structure
    transfer.tx_buf = (unsigned long) send; //the buffer for sending data
    transfer.rx_buf = (unsigned long) receive; //the buffer for receiving data
    transfer.len = 1; //the length of buffer
    transfer.speed_hz = this -> speed; //the speed in Hz
    transfer.bits_per_word = this -> bits; //bits per word
    transfer.delay_usecs = 0; //delay in us
    transfer.pad = 0;
    // send the SPI message (all of the above fields, inc. buffers)
    int status = ioctl(this -> fd, SPI_IOC_MESSAGE(1), &transfer);
    if (status < 0) {
        perror("SPI: SPI_IOC_MESSAGE Failed");
        return -1;
    }
    return status;
}
*/
