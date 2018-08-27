/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   leer_ArchivosTxt.h
 * Author: Vostro-2
 *
 * Created on 26 de julio de 2018, 11:49 AM
 */

#ifndef LEER_ARCHIVOSTXT_H
#define LEER_ARCHIVOSTXT_H

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_MAQ                 4
#define PESO_A                  7
#define PESO_B                  10
#define PESO_C                  13
#define PESO_D                  16
#define PRECIO_A                19
#define PRECIO_B                22
#define PRECIO_C                25
#define PRECIO_D                28
#define SERIE_MDB               31
#define SERIE_CORTES            34
#define NOMBRE_DIRECCION        "/home/root/debugMDB/in/properties.conf"          //ruta del archivo de configuracion
int parseInt(char arreglo[],int len);
int powInt(int x, int y);
int leer_VarProg(int variable);


#ifdef __cplusplus
}
#endif

#endif /* LEER_ARCHIVOSTXT_H */

