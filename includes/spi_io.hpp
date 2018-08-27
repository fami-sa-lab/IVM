/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   spi_io.hpp
 * Author: Isaac
 *
 * Created on 17 de febrero de 2018, 10:09 PM
 */

#ifndef SPI_IO_HPP
#define SPI_IO_HPP

#include "SPI_BP5400.hpp"
#include "GPIO.hpp"
const unsigned char ALL = 0xff;

class spi_io: public SPI_BP5400 {
public:   
    spi_io();
    int writeHigh( unsigned char pOutput);
    int writeLow( unsigned char pOutput);
    int writePort(unsigned char pOutputs);
    int readInput(unsigned char pInput);
    int readInputs(unsigned char pInputs[]);
    
private:
    
}; 
#endif /* SPI_IO_HPP */

