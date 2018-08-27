/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include "interfaz.h"
#include <stdlib.h>


typedef struct 
{
    bool hielo;                                                                 //saber si hay suficiente hielo o no
    bool vendiendoX;                                                            //Se encuentra vendiendo un cantidad X
    bool vendiendoY;                                                            //Se encuentra vendiendo un cantidad Y
    bool vendiendoZ;                                                            //Se encuentra vendiendo un cantidad X
    bool cayo_Hielo;                                
    double       cantidad_Hielo;                                                //cantidad de hielo que posee el contenerdor en Kg
    double      cantidad_Hielo_anterior;                                        //guardaremos una lectura anterior
    unsigned int hielo_a_vender;                                                //cantidad de hielo que se solicita que se venda
    double        hielo_vendido;                                                //la usaremos para monitorear cuando nos falta por vender
    double       cantidad_final;                                               //A esta cantidad hay que llegar cuando e stemos despachando
    unsigned int retardo;
    unsigned int ajusteRetardo;
    
    
} estado_sistema;
typedef struct
{
    bool solicitud_Venta;
    bool solicitud_Aceptada; 
    int venta_Terminada;
    int botonpres;
    
}estado_VM;
int boton=0;
estado_VM miVM;
FILE *archivo_EstadoVM,*pdat_EstadoVM, *ptxt_EstadoVM;
//char nombre_Arcdat[] = "EstadoVM.dat";
//char nombre_Arctxt[] = "EstadoVM.txt";
char nombre_Arcdat[] = archivo_dat;
char nombre_Arctxt[] = archivo_txt;

void ini_VMID(void)
{
    //preguntamos si existe los archivos, con esto sabemos si ya se creo el diectorio
    if(file_Exist(pdat_EstadoVM,nombre_Arcdat) && file_Exist(ptxt_EstadoVM,nombre_Arctxt))
    {
        miVM.solicitud_Aceptada = false;
        miVM.solicitud_Venta = false;
        miVM.venta_Terminada = false;
        actualizar_ArchivoTexto();
        actualizar_ArchivoDat();
    }
    else
    {
        //Creamos la carpeta donde se guardaran los archivos y volvemos a preguntar
        system(ruta_archivos);
        miVM.solicitud_Aceptada = false;
        miVM.solicitud_Venta = false;
        miVM.venta_Terminada = false;
        actualizar_ArchivoTexto();
        actualizar_ArchivoDat();
    }
    
//    if(!(file_Exist(pdat_EstadoVM,nombre_Arcdat)))                                                //para saber si existe
//    {
//        miVM.solicitud_Aceptada = false;
//        miVM.solicitud_Venta = false;
//        miVM.venta_Terminada = false;
//        actualizar_ArchivoTexto();
//        actualizar_ArchivoDat();
//    }
//    else
//    {
//        //el archivo exite, hay que leer los parametros que ahi estan escritos
//        pdat_EstadoVM= fopen(nombre_Arcdat,"rb");
//        fread(&miVM,sizeof(estado_VM),1,pdat_EstadoVM);
//        actualizar_ArchivoTexto();
//    }
}
void set_SolicitudVenta(int botonpres)
{
    miVM.solicitud_Venta = true;
    miVM.botonpres = botonpres;
    //boton = botonpres;
    actualizar_ArchivoDat();
    actualizar_ArchivoTexto();        
}
int get_botonPres(void)
{
    leer_ArchivoDat();
    return miVM.botonpres;
}
void clear_SolicitudVenta(void)
{
    miVM.solicitud_Venta = false;
    actualizar_ArchivoDat();
    actualizar_ArchivoTexto();
}
int get_SolicitudVenta(void)
{
    leer_ArchivoDat();
    if(miVM.solicitud_Venta)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void set_SolicitudAceptada(void)
{
    miVM.solicitud_Aceptada = true;
    actualizar_ArchivoDat();
    actualizar_ArchivoTexto();
}
void clear_SolicitudAceptada(void)
{
    miVM.solicitud_Aceptada = false;
    actualizar_ArchivoDat();
    actualizar_ArchivoTexto();
}
bool get_SolicitudAceptada(void)
{
   leer_ArchivoDat();
   return  miVM.solicitud_Aceptada; 
}
void set_VentaTerminada(int estado)
{
    //una vez que la venta termino, hay que reiniciar las variables
    miVM.solicitud_Venta = false;
    miVM.solicitud_Aceptada = false;
    miVM.botonpres = 0;
    miVM.venta_Terminada = 1;
    actualizar_ArchivoDat();
    actualizar_ArchivoTexto();
}
void clear_VentaTerminada(void)
{
    miVM.venta_Terminada = 0;
    actualizar_ArchivoDat();
    actualizar_ArchivoTexto();
}
//Devuelve el estado en que se encuentra el despachador de hielo
//1  = venta terminada, 0= venta no ha terminado, 2= hubo un error 
int estado_Venta(void)
{
    leer_ArchivoDat();
    return miVM.venta_Terminada;
}

//recibe como parametro un apuntador a la estructura FILE y un arreglo de caracteres que son el nombre/ruta del archivo
//regresa true si existe el archivo y false si no existe
bool file_Exist(FILE *archivo, char nombre[])
{   
    archivo = fopen(nombre,"r");
    if(archivo == NULL)
    {
        return false;
    }
    else
    {
        fclose(archivo);
        return true;
    }
}

//Modificamos el archivo de texto
int actualizar_ArchivoTexto(void)
{
    ptxt_EstadoVM = fopen(nombre_Arctxt,"w");
    if(ptxt_EstadoVM == NULL)
    {
        printf("no se pudo crear el archivo de texto");
        return -1;
    }
    else
    {
        fprintf(ptxt_EstadoVM,"Solicitud Venta = %i\n",miVM.solicitud_Venta);    //escribimos en un rchivo de texto para poderlo visualizar
        fprintf(ptxt_EstadoVM,"Solicitud Aceptada = %i\n",miVM.solicitud_Aceptada);
        fprintf(ptxt_EstadoVM,"Venta Terminada = %i\n",miVM.venta_Terminada);
        fprintf(ptxt_EstadoVM,"Boton presionado = %i\n",miVM.botonpres);
    }
    rewind(ptxt_EstadoVM);
    fflush(ptxt_EstadoVM);
    fclose(ptxt_EstadoVM);
    return 0;
}

//Modificamos el archivo .dat que se usara como itnerfaz entre el programa que
//controla la venta y el programa que controla la parte de dispensar hielo
int actualizar_ArchivoDat(void)
{
    pdat_EstadoVM = fopen(nombre_Arcdat,"wb");
    if(pdat_EstadoVM == NULL)
    {
        printf("no se pudo crear el archivo de .dat");
        return -1;
    }
    else
    {
        fwrite(&miVM,sizeof(estado_VM),1,pdat_EstadoVM);
    }
    rewind(pdat_EstadoVM);
    fflush(pdat_EstadoVM);
    fclose(pdat_EstadoVM);
    return 0;
}

int leer_ArchivoDat(void)
{
    pdat_EstadoVM = fopen(nombre_Arcdat,"rb");
    if(pdat_EstadoVM == NULL)
    {
        printf("no se pudo leer el archivo de .dat");
        return -1;
    }
    else
    {
        fread(&miVM,sizeof(estado_VM),1,pdat_EstadoVM);
    }
    rewind(pdat_EstadoVM);
    fflush(pdat_EstadoVM);
    fclose(pdat_EstadoVM);
 //-   actualizar_ArchivoTexto();
    return 0;
}
//hay que hacer una prueba corriendo el programa que despacha el hielo y el
//programa que se encarga de venderlo, y ver que ambos puedan comunicarse
//atraves de esta libreria usando el archivo que se creo