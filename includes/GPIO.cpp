/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GPIO.cpp
 * Author: Isaac
 * 
 * Created on 18 de febrero de 2018, 12:04 AM
 */

#include "GPIO.hpp"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<cstdio>
//#include<fcntl.h>
//#include<unistd.h>
//#include<sys/epoll.h>
//#include<pthread.h>

using namespace std;

GPIO::GPIO( int number) {
    this -> number = number;

    ostringstream s;
    s << "gpio" << number;
    this -> name = string(s.str());
    this -> path = GPIO_PATH + this -> name + "/";
}
int GPIO::write(string path, string filename, string value){
   ofstream fs;
   fs.open((path + filename).c_str());
   if (!fs.is_open()){
    perror("GPIO: write failed to open file ");
    return -1;
   }
   fs << value;
   fs.close();
   return 0;
}

int GPIO::setValue(GPIO_VALUE value) {
    switch (value) {
        case HIGH: return this->write(this->path, "value", "1");
            break;
        case LOW: return this->write(this->path, "value", "0");
            break;
    }
    return -1;
}

