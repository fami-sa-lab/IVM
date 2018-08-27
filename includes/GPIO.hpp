/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GPIO.hpp
 * Author: Isaac
 *
 * Created on 18 de febrero de 2018, 12:04 AM
 */

#ifndef GPIO_HPP
#define GPIO_HPP
#include <string>
#include<fstream>
using std::string;
using std::ofstream;

#define GPIO_PATH "/sys/class/gpio/"

enum GPIO_VALUE{ LOW=0, HIGH=1 };

class GPIO {
public:
    GPIO(int number);
    int setValue(GPIO_VALUE value);
private:
    int number;
    string name, path;
    
    int write(string path, string filename, string value);
    int write(string path, string filename, int value);
};

#endif /* GPIO_HPP */

