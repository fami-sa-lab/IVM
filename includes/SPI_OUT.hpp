/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SPI_OUT.hpp
 * Author: famisa
 *
 * Created on 6 de noviembre de 2017, 10:43 AM
 */

#ifndef SPI_OUT_HPP
#define SPI_OUT_HPP

#include "SPI_BP5400.hpp"

class SPI_OUT: public SPI_BP5400 {
public:
    SPI_OUT();
    int set_all();
    int clear_all();
    //int set_pin(char pOutputLen,unsigned char pOutput[]);
    //int clear_pin(char pOutputLen,unsigned char pOutput[]);
private:
    

    unsigned char answer[30];
    int send(unsigned char pCmd, unsigned char pData);
};

#endif /* SPI_OUT_HPP */

