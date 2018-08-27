/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SPI_BP5400.hpp
 * Author: famisa
 *
 * Created on 6 de noviembre de 2017, 10:05 AM
 */

#ifndef SPI_BP5400_HPP
#define SPI_BP5400_HPP

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<linux/spi/spidev.h>
#include<stdint.h>

#include "GPIO.hpp"


#define SPI_PATH "/dev/spidev1.0"

using namespace std;

class SPI_BP5400 {
public:
    SPI_BP5400();
    int openSPI();
    void closeSPI();
    int transfer(unsigned char tx_data[],unsigned char rx_data[],int length);
    int txfer(unsigned char send[], unsigned char receive[]);
    
private:
    uint8_t bits;
    uint8_t mode;
    uint32_t speed;
    int fd;
    
};

#endif /* SPI_BP5400_HPP */

