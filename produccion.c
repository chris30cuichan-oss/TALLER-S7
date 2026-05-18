#include "produccion.h"

// Funciones básicas
void limpiarBuffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF){}
}

int leerEntero(char mensaje[], int minimo){
    int valor;
    do{
        printf("%s", mensaje);
        if(scanf("%d",&valor)!=1 || valor<minimo){
            printf("Dato invalido\n");
            limpiarBuffer();
        } else break;
    }while(1);
    limpiarBuffer();
    return valor;
}

float leerFloat(char mensaje[], float minimo){
    float valor;
    do{
        printf("%s", mensaje);
        if(scanf("%f",&valor)!=1 || valor<minimo){
            printf("Dato invalido\n");
            limpiarBuffer();
        } else break;
    }while(1);
    limpiarBuffer();
    return valor;
}

void leerTexto(char mensaje[], char texto[], int tam){
    do{
        printf("%s", mensaje);
        scanf("%s", texto);
        limpiarBuffer();
        if(texto[0]=='\0') printf("Nombre vacio\n");
        else break;
    }while(1);
}

// Funciones de productos
void ingresarProducto(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int *total){
    if(*total>=MAX_PRODUCTOS){printf("Ya se alcanzó el máximo de productos permitidos\n"); return;}
    leerTexto("Nombre del producto: ", nombres[*total], MAX_NOMBRE);
    cantidades[*total] = leerEntero("Cantidad: ",1);
    tiempos[*total] = leerFloat("Tiempo por unidad: ",0.01);
    recursos[*total] = leerFloat("Recursos por unidad: ",0.01);
    int nuevoTotal = *total + 1;
    *total = nuevoTotal;
    printf("Producto ingresado correctamente. Total de productos ahora: %d\n", *total);
}

void listarProductos(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int total){
    if(total==0){printf("No hay productos\n"); return;}
    printf("No  Nombre     Cantidad  Tiempo  Recursos\n");
    for(int i=0;i<total;i++)
        printf("%d   %s       %d        %.2f     %.2f\n", i+1, nombres[i], cantidades[i], tiempos[i], recursos[i]);
}

int buscarProducto(char nombres[][50], int total, char buscado[]){
    for(int i=0;i<total;i++){
        int igual=1;
        for(int j=0;j<MAX_NOMBRE;j++){
            if(nombres[i][j]!=buscado[j]){igual=0; break;}
            if(nombres[i][j]=='\0') break;
        }
        if(igual) return i;
    }
    return total;
}

void editarProducto(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int total){
    if(total==0){printf("No hay productos para editar\n"); return;}
    char buscado[50]; leerTexto("Producto a editar: ", buscado, MAX_NOMBRE);
    int pos = buscarProducto(nombres,total,buscado);
    if(pos==total){printf("Producto no encontrado\n"); return;}
    int opcion;
    do{
        printf("1.Nombre 2.Cantidad 3.Tiempo 4.Recursos 5.Salir\n");
        opcion = leerEntero("Opcion: ",1);
        switch(opcion){
            case 1: leerTexto("Nuevo nombre: ", nombres[pos], MAX_NOMBRE); break;
            case 2: cantidades[pos] = leerEntero("Nueva cantidad: ",1); break;
            case 3: tiempos[pos] = leerFloat("Nuevo tiempo: ",0.01); break;
            case 4: recursos[pos] = leerFloat("Nuevos recursos: ",0.01); break;
            case 5: break;
            default: printf("Opción inválida. Intente nuevamente.\n");
        }
    }while(opcion!=5);
}

void eliminarProducto(char nombres[][50], int cantidades[], float tiempos[], float recursos[], int *total){
    if(*total==0){printf("No hay productos para eliminar\n"); return;}
    char buscado[50]; leerTexto("Producto a eliminar: ", buscado, MAX_NOMBRE);
    int pos = buscarProducto(nombres,*total,buscado);
    if(pos==*total){printf("Producto no encontrado\n"); return;}
    for(int i=pos;i<*total-1;i++){
        for(int j=0;j<MAX_NOMBRE;j++) nombres[i][j]=nombres[i+1][j];
        cantidades[i]=cantidades[i+1];
        tiempos[i]=tiempos[i+1];
        recursos[i]=recursos[i+1];
    }
    int nuevoTotal = *total - 1;
    *total = nuevoTotal;
    printf("Producto eliminado correctamente. Total de productos ahora: %d\n", *total);
}

// Funciones de cálculos
void calcularTotales(int cantidades[], float tiempos[], float recursos[], int total, float *tiempoTotal, float *recursoTotal){
    *tiempoTotal=0; *recursoTotal=0;
    for(int i=0;i<total;i++){
        *tiempoTotal += cantidades[i]*tiempos[i];
        *recursoTotal += cantidades[i]*recursos[i];
    }
}

void verificarProduccion(int cantidades[], float tiempos[], float recursos[], int total, float tiempoDisp, float recursoDisp){
    float tiempoTotal, recursoTotal;
    calcularTotales(cantidades, tiempos, recursos, total, &tiempoTotal, &recursoTotal);
    if(tiempoTotal<=tiempoDisp && recursoTotal<=recursoDisp)
        printf("SI se puede producir\n");
    else
        printf("NO se puede producir\n");
}