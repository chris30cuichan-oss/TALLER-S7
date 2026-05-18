#ifndef PRODUCCION_H
#define PRODUCCION_H

#include <stdio.h>

int MAX_PRODUCTOS = 5;
int MAX_NOMBRE = 50;

// Funciones básicas
void limpiarBuffer();
int leerEntero(char mensaje[], int minimo);
float leerFloat(char mensaje[], float minimo);
void leerTexto(char mensaje[], char texto[], int tam);

// Funciones de productos
void ingresarProducto(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int *total);
void listarProductos(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int total);
int buscarProducto(char nombres[][50], int total, char buscado[]);
void editarProducto(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int total);
void eliminarProducto(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int *total);

// Funciones de cálculos
void calcularTotales(int cantidades[], float tiempos[], float recursos[], int total, float *tiempoTotal, float *recursoTotal);
void verificarProduccion(int cantidades[], float tiempos[], float recursos[], int total, float tiempoDisp, float recursoDisp);

#endif