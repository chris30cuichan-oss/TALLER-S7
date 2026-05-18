#include <stdio.h>
#include "produccion.h"

int main(){
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
    int cantidades[MAX_PRODUCTOS];
    float tiempos[MAX_PRODUCTOS];
    float recursos[MAX_PRODUCTOS];
    int total=0;
    int opcion;
    float tiempoDisp=100, recursoDisp=100;

    do{
        printf("\n1.Ingresar 2.Listar 3.Editar 4.Eliminar 5.Calcular 6.Verificar 7.Salir\n");
        opcion = leerEntero("Opcion: ",1);
        switch(opcion){
            case 1: ingresarProducto(nombres,cantidades,tiempos,recursos,&total); break;
            case 2: listarProductos(nombres,cantidades,tiempos,recursos,total); break;
            case 3: editarProducto(nombres,cantidades,tiempos,recursos,total); break;
            case 4: eliminarProducto(nombres,cantidades,tiempos,recursos,&total); break;
            case 5:{
                float t,r; calcularTotales(cantidades,tiempos,recursos,total,&t,&r);
                printf("Tiempo total: %.2f, Recursos total: %.2f\n", t,r);
                break;
            }
            case 6: verificarProduccion(cantidades,tiempos,recursos,total,tiempoDisp,recursoDisp); break;
            case 7: break;
            default: printf("Opción inválida. Por favor, seleccione un número válido del menú.\n");
        }
    }while(opcion!=7);

    return 0;
}