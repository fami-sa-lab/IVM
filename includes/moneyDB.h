/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   moneyDB.h
 * Author: Isaac
 *
 * Created on 12 de julio de 2018, 11:17 AM
 */

#include <sqlite3.h>
#include <time.h>
#include <iostream>
#include <string.h>
#include <stdio.h>


#ifndef MONEYDB_H
#define MONEYDB_H

using namespace std;

#define DB_PATH "/home/root/debugMDB/db/ventas.db" //modificar direccion

#define SQL_INSERT_VENTA    "INSERT INTO tbl_venta (col_fecha_hora, col_item_id, col_precio, col_depositado, col_cambio) VALUES ('%s','%d','%0.2f','%0.2f','%0.2f');"
//#define SQL_INSERT_VENTA    "INSERT INTO tbl_venta (col_fecha_hora,col_item_id,col_precio,col_depositado,col_cambio) VALUES ('07/16/18 16:30:06','1','7.00','10.00','3.00');"
#define SQL_SELECT_LAST_VENTA      "SELECT seq FROM sqlite_sequence where name = 'tbl_venta';"
#define SQL_INSERT_TUBOS_IN  "INSERT INTO tbl_tubos (col_venta_id, col_in_out, col_50c, col_1p, col_2p, col_5p, col_10p, col_20p) VALUES ('%d','1','%d','%d','%d','%d','%d','%d');" 
#define SQL_INSERT_CAJA_MONEDAS  "INSERT INTO tbl_caja (col_venta_id, col_50c, col_1p, col_2p, col_5p, col_10p, col_20p) VALUES ('%d','%d','%d','%d','%d','%d','%d');" 
#define SQL_INSERT_CAJA_BILLETES  "INSERT INTO tbl_billetes (col_venta_id, col_20p, col_50p, col_100p, col_200p, col_500p ,col_1000p) VALUES ('%d','%d','%d','%d','%d','%d','%d');" 
#define SQL_INSERT_TUBOS_OUT  "INSERT INTO tbl_tubos (col_venta_id, col_in_out, col_50c, col_1p, col_2p, col_5p, col_10p, col_20p) VALUES ('%d','0','%d','%d','%d','%d','%d','%d');" 

#define SQL_INSERT_CORTE    "INSERT INTO tbl_cortes (col_fecha) VALUES ('%s');"
#define SQL_SELECT_CORTE     "SELECT seq FROM sqlite_sequence where name = 'tbl_cortes';"

#define SQL_SELECT_VENTAS_0 "SELECT COUNT(col_item_id) FROM tbl_venta WHERE col_item_id IS 0;"
#define SQL_SELECT_VENTAS_1 "SELECT COUNT(col_item_id) FROM tbl_venta WHERE col_item_id = 1;"
#define SQL_SELECT_VENTAS_2 "SELECT COUNT(col_item_id) FROM tbl_venta WHERE col_item_id = 2;"
#define SQL_SELECT_VENTAS_3 "SELECT COUNT(col_item_id) FROM tbl_venta WHERE col_item_id = 3;"

#define SQL_SUM_TUBOS_OUT_50C "SELECT SUM(col_50c) FROM tbl_tubos WHERE col_in_out = 0;"
#define SQL_SUM_TUBOS_OUT_1P "SELECT SUM(col_1p) FROM tbl_tubos WHERE col_in_out = 0;"
#define SQL_SUM_TUBOS_OUT_2P "SELECT SUM(col_2p) FROM tbl_tubos WHERE col_in_out = 0;"
#define SQL_SUM_TUBOS_OUT_5P "SELECT SUM(col_5p) FROM tbl_tubos WHERE col_in_out = 0;"
#define SQL_SUM_TUBOS_OUT_10P "SELECT SUM(col_10p) FROM tbl_tubos WHERE col_in_out = 0;"
#define SQL_SUM_TUBOS_OUT_20P "SELECT SUM(col_20p) FROM tbl_tubos WHERE col_in_out = 0;"

#define SQL_SUM_TUBOS_IN_50C "SELECT SUM(col_50c) FROM tbl_tubos WHERE col_in_out = 1;"
#define SQL_SUM_TUBOS_IN_1P "SELECT SUM(col_1p) FROM tbl_tubos WHERE col_in_out = 1;"
#define SQL_SUM_TUBOS_IN_2P "SELECT SUM(col_2p) FROM tbl_tubos WHERE col_in_out = 1;"
#define SQL_SUM_TUBOS_IN_5P "SELECT SUM(col_5p) FROM tbl_tubos WHERE col_in_out = 1;"
#define SQL_SUM_TUBOS_IN_10P "SELECT SUM(col_10p) FROM tbl_tubos WHERE col_in_out = 1;"
#define SQL_SUM_TUBOS_IN_20P "SELECT SUM(col_20p) FROM tbl_tubos WHERE col_in_out = 1;"

#define SQL_SUM_CAJA_50C "SELECT SUM(col_50c) FROM tbl_caja;"
#define SQL_SUM_CAJA_1P "SELECT SUM(col_1p) FROM tbl_caja;"
#define SQL_SUM_CAJA_2P "SELECT SUM(col_2p) FROM tbl_caja;"
#define SQL_SUM_CAJA_5P "SELECT SUM(col_5p) FROM tbl_caja;"
#define SQL_SUM_CAJA_10P "SELECT SUM(col_10p) FROM tbl_caja;"
#define SQL_SUM_CAJA_20P "SELECT SUM(col_20p) FROM tbl_caja;"

#define SQL_SUM_BILLETES_20P "SELECT SUM(col_20p) FROM tbl_billetes;"
#define SQL_SUM_BILLETES_50P "SELECT SUM(col_50p) FROM tbl_billetes;"
#define SQL_SUM_BILLETES_100P "SELECT SUM(col_100p) FROM tbl_billetes;"
#define SQL_SUM_BILLETES_200P "SELECT SUM(col_200p) FROM tbl_billetes;"
#define SQL_SUM_BILLETES_500P "SELECT SUM(col_500p) FROM tbl_billetes;"
#define SQL_SUM_BILLETES_1000P "SELECT SUM(col_1000p) FROM tbl_billetes;"

#define SQL_UPDATE_DATOS "UPDATE tbl_datos SET col_num_maquina = %d, col_precio_A = %d, col_precio_B = %d, col_precio_C = %d, col_precio_D = %d;"

#define SQL_SELECT_NUM_MAQUINA     "SELECT col_num_maquina FROM tbl_datos;"
#define SQL_SELECT_PRECIO_A     "SELECT col_precio_A FROM tbl_datos;"
#define SQL_SELECT_PRECIO_B     "SELECT col_precio_B FROM tbl_datos;"
#define SQL_SELECT_PRECIO_C     "SELECT col_precio_C FROM tbl_datos;"
#define SQL_SELECT_PRECIO_D     "SELECT col_precio_D FROM tbl_datos;"

#define SQL_UPDATE_VENTAS_A "UPDATE tbl_cortes SET col_ventasA = %d WHERE col_folio = %d;"
#define SQL_UPDATE_VENTAS_B "UPDATE tbl_cortes SET col_ventasB = %d WHERE col_folio = %d;"
#define SQL_UPDATE_VENTAS_C "UPDATE tbl_cortes SET col_ventasC = %d WHERE col_folio = %d;"
#define SQL_UPDATE_VENTAS_D "UPDATE tbl_cortes SET col_ventasD = %d WHERE col_folio = %d;"

#define SQL_RESET_BILLETES  "DELETE FROM tbl_billetes;"
#define SQL_RESET_CAJA  "DELETE FROM tbl_caja;"
#define SQL_RESET_TUBOS  "DELETE FROM tbl_tubos;"
#define SQL_RESET_VENTA  "DELETE FROM tbl_venta;"
#define SQL_RESET_CORTES  "DELETE FROM tbl_cortes;"

#define SQL_RESET_SEQ_BILLETES  "UPDATE sqlite_sequence SET seq=0 WHERE name='tbl_billetes';"
#define SQL_RESET_SEQ_CAJA  "UPDATE sqlite_sequence SET seq=0 WHERE name='tbl_caja';"
#define SQL_RESET_SEQ_TUBOS "UPDATE sqlite_sequence SET seq=0 WHERE name='tbl_tubos';"
#define SQL_RESET_SEQ_VENTAS  "UPDATE sqlite_sequence SET seq=0 WHERE name='tbl_venta';"

#define SQL_RESET       "DELETE FROM tbl_billetes; DELETE FROM tbl_caja; DELETE FROM tbl_tubos; DELETE FROM tbl_venta; DELETE FROM tbl_cortes; UPDATE sqlite_sequence SET seq=0 WHERE name='tbl_billetes'; UPDATE sqlite_sequence SET seq=0 WHERE name='tbl_caja'; UPDATE sqlite_sequence SET seq=0 WHERE name='tbl_tubos'; UPDATE sqlite_sequence SET seq=0 WHERE name='tbl_venta';"
//modificar direccion
#define BACKUP_DB   "sqlite3 /home/root/debugMDB/db/ventas.db '.backup /home/root/debugMDB/db/ventas%03d'"


#define TUBOS_DEPOSITO    0
#define TUBOS_CAMBIO      1
#define CAJA_MONEDA 2
#define CAJA_BILLETE    3

#define CORTE 1

struct monedas_s {
    int flag;
    int mxn_50c;
    int mxn_1p;
    int mxn_2p;
    int mxn_5p;
    int mxn_10p;
    int mxn_20p;
};

struct billetes_s {
    int flag;
    int mxn_20p;
    int mxn_50p;
    int mxn_100p;
    int mxn_200p;
    int mxn_500p;
    int mxn_1000p;
};

class moneyDB {
public:
    moneyDB();
    moneyDB(int corte);
    ~moneyDB();
    int creaCorte();

    int openDatabase();
    void closeDatabase();

    void resetCount();
    int registerCoin(int pType, int coinValue, int amount);
    int updateDatabase();

    int backupDatabase();
    int resetDatabase();
    
    int getAuditData();

    int setDatosMaquina(int pNumMaquina, int precioA, int precioB, int precioC, int precioD);
    
    int getNumeroMaquina();
    int getFolio();
    struct monedas_s getTubosIn();
    struct monedas_s getTubosOut();
    struct monedas_s getCajaMonedas();
    struct billetes_s getCajaBilletes();
    
    int getVentasA();
    int getVentasB();
    int getVentasC();
    int getVentasD();
    
    int getPrecioA();
    int getPrecioB();
    int getPrecioC();
    int getPrecioD();
    int precio;
    int insertado;
    int cambio;
    int articulo;

    int updateDB; // indica que existe registro por agregar a base de datos.

    struct monedas_s tubosDeposito;
    struct monedas_s tubosCambio;
    struct monedas_s cajaMonedas;
    struct billetes_s cajaBilletes;

private:
    int dbResult;
    sqlite3 *db;
    char sentencia[1000];
    string sqlStatement;
    char *zErrMsg;
    sqlite3_stmt *resultado;
    const char* siguiente;

    int getTimeDate();
    char timeDate[80];

    int folio;


};

#endif /* MONEYDB_H */

moneyDB::moneyDB() {
    precio = 0;
    insertado = 0;
    cambio = 0;
    resetCount();
    openDatabase();
}

moneyDB::moneyDB(int Corte) {

    openDatabase();
    creaCorte();
}

moneyDB::~moneyDB(){
    closeDatabase();
}


int moneyDB::resetDatabase(){
    sprintf(sentencia, SQL_RESET, timeDate);
    dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "database reset succesfull\n");
    }
}

int moneyDB::backupDatabase(){
    char systemBuffer[100];
    sprintf(systemBuffer,BACKUP_DB,folio);
    system(systemBuffer);
}

int moneyDB::creaCorte() {
    getTimeDate();
    sprintf(sentencia, SQL_INSERT_CORTE, timeDate);
    dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "Folio created successfully\n");
    }
    
    folio = getFolio();
    
}

int moneyDB::openDatabase(void) {
    dbResult = sqlite3_open(DB_PATH, &db);
    if (dbResult) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        fprintf(stderr, "Opened database succesfully\n");
        return 0;
    }
}

void moneyDB::closeDatabase() {
    sqlite3_close(db);
}

void moneyDB::resetCount() {
    tubosDeposito.flag = 0;
    tubosDeposito.mxn_50c = 0;
    tubosDeposito.mxn_1p = 0;
    tubosDeposito.mxn_2p = 0;
    tubosDeposito.mxn_5p = 0;
    tubosDeposito.mxn_10p = 0;
    tubosDeposito.mxn_20p = 0;

    tubosCambio.flag = 0;
    tubosCambio.mxn_50c = 0;
    tubosCambio.mxn_1p = 0;
    tubosCambio.mxn_2p = 0;
    tubosCambio.mxn_5p = 0;
    tubosCambio.mxn_10p = 0;
    tubosCambio.mxn_20p = 0;

    cajaMonedas.flag = 0;
    cajaMonedas.mxn_50c = 0;
    cajaMonedas.mxn_1p = 0;
    cajaMonedas.mxn_2p = 0;
    cajaMonedas.mxn_5p = 0;
    cajaMonedas.mxn_10p = 0;
    cajaMonedas.mxn_20p = 0;

    cajaBilletes.flag = 0;
    cajaBilletes.mxn_20p = 0;
    cajaBilletes.mxn_50p = 0;
    cajaBilletes.mxn_100p = 0;
    cajaBilletes.mxn_200p = 0;
    cajaBilletes.mxn_500p = 0;
    cajaBilletes.mxn_1000p = 0;
}

int moneyDB::registerCoin(int pType, int coinValue, int amount) {
    switch (pType) {
        case TUBOS_DEPOSITO:
            tubosDeposito.flag = 1;
            switch (coinValue) {
                case 50:
                    tubosDeposito.mxn_50c++;
                    break;
                case 100:
                    tubosDeposito.mxn_1p++;

                    break;
                case 200:
                    tubosDeposito.mxn_2p++;

                    break;
                case 500:
                    tubosDeposito.mxn_5p++;

                    break;
                case 1000:
                    tubosDeposito.mxn_10p++;

                    break;
                case 2000:
                    tubosDeposito.mxn_20p++;
                    break;
            }
            break;

        case TUBOS_CAMBIO:
            tubosCambio.flag = 1;
            switch (coinValue) {
                case 50:
                    tubosCambio.mxn_50c += amount;
                    break;
                case 100:
                    tubosCambio.mxn_1p += amount;

                    break;
                case 200:
                    tubosCambio.mxn_2p += amount;

                    break;
                case 500:
                    tubosCambio.mxn_5p += amount;

                    break;
                case 1000:
                    tubosCambio.mxn_10p += amount;

                    break;
                case 2000:
                    tubosCambio.mxn_20p += amount;
                    break;
            }
            break;

        case CAJA_MONEDA:
            cajaMonedas.flag = 1;
            switch (coinValue) {
                case 50:
                    cajaMonedas.mxn_50c++;
                    break;
                case 100:
                    cajaMonedas.mxn_1p++;

                    break;
                case 200:
                    cajaMonedas.mxn_2p++;

                    break;
                case 500:
                    cajaMonedas.mxn_5p++;

                    break;
                case 1000:
                    cajaMonedas.mxn_10p++;

                    break;
                case 2000:
                    cajaMonedas.mxn_20p++;
                    break;
            }
            break;

        case CAJA_BILLETE:
            cajaBilletes.flag = 1;
            switch (coinValue) {
                case 2000:
                    cajaBilletes.mxn_20p++;
                    break;
                case 5000:
                    cajaBilletes.mxn_50p++;

                    break;
                case 10000:
                    cajaBilletes.mxn_100p++;

                    break;
                case 20000:
                    cajaBilletes.mxn_200p++;

                    break;
                case 50000:
                    cajaBilletes.mxn_500p++;

                    break;
                case 100000:
                    cajaBilletes.mxn_1000p++;
                    break;
            }
            break;

    }
}

int moneyDB::getTimeDate() {
    time_t rawTime;
    struct tm * timeinfo;

    time(&rawTime);
    timeinfo = localtime(&rawTime);

    memset(this -> timeDate, 0, 80);
    strftime(timeDate, 80, "%D %T", timeinfo);
}

int moneyDB::updateDatabase() {
    int ventaID;
    getTimeDate();
    cout << "Se registra venta el " << timeDate << "PRECIO: " << this -> precio << ", INSERTADO: " << this -> insertado
            << ", CAMBIO: " << this -> cambio << endl;

    //crea registro de venta
    sprintf(sentencia, SQL_INSERT_VENTA, timeDate, articulo, static_cast<float> (precio) / 100, static_cast<float> (insertado) / 100, static_cast<float> (cambio) / 100);
    //strcpy(sentencia ,SQL_INSERT_VENTA);  
    dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "Records created successfully\n");
    }

    //obtiene el id de venta del registro insertado previamente
    sprintf(sentencia, SQL_SELECT_LAST_VENTA); //identifica la version de distribucion en la base de datos 
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            ventaID = sqlite3_column_int(resultado, 0);
            cout << "Id de Venta: " << ventaID << endl;
            ;
        }
    }

    //verifica si hubo monedas a tubo para agregar registro
    if (tubosDeposito.flag) {

        sprintf(sentencia, SQL_INSERT_TUBOS_IN, ventaID, tubosDeposito.mxn_50c, tubosDeposito.mxn_1p, tubosDeposito.mxn_2p, tubosDeposito.mxn_5p, tubosDeposito.mxn_10p, tubosDeposito.mxn_20p);
        dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg);
        if (dbResult != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return -1;
        } else {
            fprintf(stdout, "Records created successfully\n");
        }
    }

    //verifica si hubo monedas a caja para agregar registro
    if (cajaMonedas.flag) {
        sprintf(sentencia, SQL_INSERT_CAJA_MONEDAS, ventaID, cajaMonedas.mxn_50c, cajaMonedas.mxn_1p, cajaMonedas.mxn_2p, cajaMonedas.mxn_5p, cajaMonedas.mxn_10p, cajaMonedas.mxn_20p);
        dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg);
        if (dbResult != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return -1;
        } else {
            fprintf(stdout, "Records created successfully\n");
        }
    }

    //verifica si hubo billetes a caja para agregar registro
    if (cajaBilletes.flag) {
        sprintf(sentencia, SQL_INSERT_CAJA_BILLETES, ventaID, cajaBilletes.mxn_20p, cajaBilletes.mxn_50p, cajaBilletes.mxn_100p, cajaBilletes.mxn_200p, cajaBilletes.mxn_500p, cajaBilletes.mxn_1000p);
        dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg);
        if (dbResult != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return -1;
        } else {
            fprintf(stdout, "Records created successfully\n");
        }
    }

    //verifica si dio cambio para agregar registro
    if (tubosCambio.flag) {
        sprintf(sentencia, SQL_INSERT_TUBOS_OUT, ventaID, tubosCambio.mxn_50c, tubosCambio.mxn_1p, tubosCambio.mxn_2p, tubosCambio.mxn_5p, tubosCambio.mxn_10p, tubosCambio.mxn_20p);
        dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg);
        if (dbResult != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return -1;
        } else {
            fprintf(stdout, "Records created successfully\n");
        }

    }

    updateDB = 0;
    resetCount();
    return 0;
}

int moneyDB::setDatosMaquina(int pNumMaquina, int precioA, int precioB, int precioC, int precioD) {

    sprintf(sentencia, SQL_UPDATE_DATOS, pNumMaquina, precioA, precioB, precioC, precioD);
    printf("%s\n", sentencia);
    dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg); //inserta filas
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "datos maquina updated\n");
    }

    return 0;
}

int moneyDB::getNumeroMaquina() {
    int numMaquina = 0;
    sprintf(sentencia, SQL_SELECT_NUM_MAQUINA);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            numMaquina = sqlite3_column_int(resultado, 0);
            //cout << "numMaquina: " << numMaquina << endl;

        }
    }
    return numMaquina;
}

int moneyDB::getFolio() {
    int folio;
    sprintf(sentencia, SQL_SELECT_CORTE);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            folio = sqlite3_column_int(resultado, 0);
        }
    }
    return folio;
}

struct monedas_s moneyDB::getTubosIn() {
    struct monedas_s tubosIn;

    sprintf(sentencia, SQL_SUM_TUBOS_IN_50C);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosIn.flag = -1;
        return tubosIn;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosIn.mxn_50c = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_TUBOS_IN_1P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosIn.flag = -1;
        return tubosIn;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosIn.mxn_1p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_TUBOS_IN_2P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosIn.flag = -1;
        return tubosIn;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosIn.mxn_2p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_TUBOS_IN_5P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosIn.flag = -1;
        return tubosIn;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosIn.mxn_5p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_TUBOS_IN_10P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosIn.flag = -1;
        return tubosIn;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosIn.mxn_10p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_TUBOS_IN_20P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosIn.flag = -1;
        return tubosIn;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosIn.mxn_20p = sqlite3_column_int(resultado, 0);
        }
    }

    return tubosIn;

}

struct monedas_s moneyDB::getTubosOut() {
    struct monedas_s tubosOut;

    sprintf(sentencia, SQL_SUM_TUBOS_OUT_50C);
    
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosOut.flag = -1;
        return tubosOut;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosOut.mxn_50c = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_TUBOS_OUT_1P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosOut.flag = -1;
        return tubosOut;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosOut.mxn_1p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_TUBOS_OUT_2P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosOut.flag = -1;
        return tubosOut;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosOut.mxn_2p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_TUBOS_OUT_5P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosOut.flag = -1;
        return tubosOut;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosOut.mxn_5p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_TUBOS_OUT_10P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosOut.flag = -1;
        return tubosOut;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosOut.mxn_10p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_TUBOS_OUT_20P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        tubosOut.flag = -1;
        return tubosOut;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            tubosOut.mxn_20p = sqlite3_column_int(resultado, 0);
        }
    }

    return tubosOut;
}

struct monedas_s moneyDB::getCajaMonedas() {
    struct monedas_s cajasMonedas;

    sprintf(sentencia, SQL_SUM_CAJA_50C);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajasMonedas.flag = -1;
        return cajasMonedas;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            cajasMonedas.mxn_50c = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_CAJA_1P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajasMonedas.flag = -1;
        return cajasMonedas;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            cajasMonedas.mxn_1p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_CAJA_2P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajasMonedas.flag = -1;
        return cajasMonedas;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            cajasMonedas.mxn_2p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_CAJA_5P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajasMonedas.flag = -1;
        return cajasMonedas;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            cajasMonedas.mxn_5p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_CAJA_10P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajasMonedas.flag = -1;
        return cajasMonedas;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            cajasMonedas.mxn_10p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_CAJA_20P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajasMonedas.flag = -1;
        return cajasMonedas;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            cajasMonedas.mxn_20p = sqlite3_column_int(resultado, 0);
        }
    }

    return cajasMonedas;
}

struct billetes_s moneyDB::getCajaBilletes() {
    struct billetes_s billetes;

    sprintf(sentencia, SQL_SUM_BILLETES_20P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajaBilletes.flag = -1;
        return cajaBilletes;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            billetes.mxn_20p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_BILLETES_50P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajaBilletes.flag = -1;
        return cajaBilletes;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            billetes.mxn_50p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_BILLETES_100P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajaBilletes.flag = -1;
        return cajaBilletes;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            billetes.mxn_100p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_BILLETES_200P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajaBilletes.flag = -1;
        return cajaBilletes;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            billetes.mxn_200p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_BILLETES_500P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajaBilletes.flag = -1;
        return cajaBilletes;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            billetes.mxn_500p = sqlite3_column_int(resultado, 0);
        }
    }

    sprintf(sentencia, SQL_SUM_BILLETES_1000P);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        cajaBilletes.flag = -1;
        return cajaBilletes;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            billetes.mxn_1000p = sqlite3_column_int(resultado, 0);
        }
    }

    return billetes;
}

int moneyDB::getVentasA() {
    int ventas;

    sprintf(sentencia, SQL_SELECT_VENTAS_0);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            ventas = sqlite3_column_int(resultado, 0);
        }
    }
    sprintf(sentencia, SQL_UPDATE_VENTAS_A,ventas,folio);
    dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg); //inserta filas
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "Ventas A updated\n");
    }
     
    return ventas;

}

int moneyDB::getVentasB() {
    int ventas;
    sprintf(sentencia, SQL_SELECT_VENTAS_1);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            ventas = sqlite3_column_int(resultado, 0);
        }
    }
    
     sprintf(sentencia, SQL_UPDATE_VENTAS_B,ventas,folio);

    dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg); //inserta filas
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "Ventas B updated\n");
    }
    
    return ventas;
}

int moneyDB::getVentasC() {
    int ventas;
    sprintf(sentencia, SQL_SELECT_VENTAS_2);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            ventas = sqlite3_column_int(resultado, 0);
        }
    }
    
    sprintf(sentencia, SQL_UPDATE_VENTAS_C,ventas,folio);

    dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg); //inserta filas
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "Ventas C updated\n");
    }
    
    return ventas;
}

int moneyDB::getVentasD() {
    int ventas;
    sprintf(sentencia, SQL_SELECT_VENTAS_3);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            ventas = sqlite3_column_int(resultado, 0);
        }
    }
    
    sprintf(sentencia, SQL_UPDATE_VENTAS_D,ventas,folio);

    dbResult = sqlite3_exec(db, sentencia, NULL, NULL, &zErrMsg); //inserta filas
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "Ventas D updated\n");
    }
    
    return ventas;
}

int moneyDB::getPrecioA(){
    int precio;
    sprintf(sentencia, SQL_SELECT_PRECIO_A);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            precio = sqlite3_column_int(resultado, 0);
        }
    }
    return precio;
}

int moneyDB::getPrecioB(){
    int precio;
    sprintf(sentencia, SQL_SELECT_PRECIO_B);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            precio = sqlite3_column_int(resultado, 0);
        }
    }
    return precio;
}

int moneyDB::getPrecioC(){
    int precio;
    sprintf(sentencia, SQL_SELECT_PRECIO_C);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            precio = sqlite3_column_int(resultado, 0);
        }
    }
    return precio;
}

int moneyDB::getPrecioD(){
    int precio;
    sprintf(sentencia, SQL_SELECT_PRECIO_D);
    dbResult = sqlite3_prepare(db, sentencia, 80, &resultado, &siguiente);
    if (dbResult != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        while (sqlite3_step(resultado) == SQLITE_ROW) {
            precio = sqlite3_column_int(resultado, 0);
        }
    }
    return precio;
}