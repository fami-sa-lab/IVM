/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   interfaz.h
 * Author: Vostro-2
 *
 * Created on 28 de junio de 2018, 04:57 PM
 */

#ifndef INTERFAZ_H
#define INTERFAZ_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>    
#define     BOTONX                  7
#define     BOTONY                  8
#define     BOTONZ                  9
#define ruta_archivos   "mkdir /home/root/.netbeans/remote/192.168.7.2/desktop-kidd58f-Windows-x86_64/C/Users/Vostro-2/Documents/proyectos_netbeans/archivos_interfaz"
#define archivo_dat     "/home/root/.netbeans/remote/192.168.7.2/desktop-kidd58f-Windows-x86_64/C/Users/Vostro-2/Documents/proyectos_netbeans/archivos_interfaz/escritura_prueba.dat"
#define archivo_txt     "/home/root/.netbeans/remote/192.168.7.2/desktop-kidd58f-Windows-x86_64/C/Users/Vostro-2/Documents/proyectos_netbeans/archivos_interfaz/escritura_prueba.txt"
    
void ini_VMID(void);
void set_SolicitudVenta(int botonpres);
void clear_SolicitudVenta(void);
int get_SolicitudVenta(void);
void set_SolicitudAceptada(void);
void clear_SolicitudAceptada(void);
bool get_SolicitudAceptada(void);
void set_VentaTerminada(int estado);
void clear_VentaTerminada(void);
int estado_Venta(void);
bool file_Exist(FILE *archivo,char nombre[]);
int actualizar_ArchivoTexto(void);
int actualizar_ArchivoDat(void);
int leer_ArchivoDat(void);
int get_botonPres(void);


#ifdef __cplusplus
}
#endif

#endif /* INTERFAZ_H */

