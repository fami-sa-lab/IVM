/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GPIO.h
 * Author: Isaac
 *
 * Created on 1 de junio de 2018, 03:21 PM
 */

#ifndef GPIO_H
#define GPIO_H

#include <string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<cstdlib>
#include<cstdio>


using namespace std;
using std::string;
using std::ofstream;
using std::ifstream;

#define GPIO_PATH "/sys/class/gpio/"

enum GPIO_VALUE{ LOW=0, HIGH=1 };

class GPIO {
public:
    GPIO(int number);
    int setValue(GPIO_VALUE value);
    int readValue();
    
private:
    int number;
    string name, path;
    
    int write(string path, string filename, string value);
    int write(string path, string filename, int value);
    string read(string path, string filename);
};


#endif /* GPIO_H */

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

string GPIO::read(string path, string filename){
    ifstream fs;
    string value;
   fs.open((path + filename).c_str());
   if (!fs.is_open()){
    perror("GPIO: write failed to open file ");
    
   }
   getline(fs,value);
   fs.close();
   return value;
   
}

int GPIO::readValue(){
    string input = this -> read(this -> path,"value");
    if (input == "0") return 0;
    else return 1;
     
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

