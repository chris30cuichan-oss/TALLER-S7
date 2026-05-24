#include <stdio.h>

int MAX_PRODUCTOS = 5;
int MAX_NOMBRE = 50;
void limpiarBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF){}
}
void leerTexto(char mensaje[], char texto[], int tam){
    int error, i;
    do{
        error = 0;
        printf("%s", mensaje);
        scanf(" %49[^\n]", texto);
        limpiarBuffer();
        if(texto[0] == '\0'){
            printf("Texto vacio\n");
            error = 1;
        }
        for(i = 0; texto[i] != '\0'; i++){
            if(!((texto[i] >= 'A' && texto[i] <= 'Z') ||
                 (texto[i] >= 'a' && texto[i] <= 'z') ||
                  texto[i] == ' ')){
                error = 1;
                break;
            }
        }
        if(error == 1){
            printf("Solo letras permitidas\n");
        }
    }while(error == 1);
}
int leerEntero(char mensaje[], int minimo){
    char texto[50];
    int i, error, numero;
    do{
        error = 0;
        numero = 0;
        printf("%s", mensaje);
        scanf("%49s", texto);
        limpiarBuffer();
        for(i = 0; texto[i] != '\0'; i++){
            if(texto[i] < '0' || texto[i] > '9'){
                error = 1;
                break;
            }
        }
        if(error == 1){
            printf("Solo numeros enteros\n");
        }
    }while(error == 1);
    for(i = 0; texto[i] != '\0'; i++){
        numero = numero * 10 + (texto[i] - '0');
    }
    while(numero < minimo){
        printf("Debe ser mayor o igual a %d\n", minimo);
        printf("%s", mensaje);
        scanf("%49s", texto);
        limpiarBuffer();
        numero = 0;
        for(i = 0; texto[i] != '\0'; i++){
            numero = numero * 10 + (texto[i] - '0');
        }
    }
    return numero;
}
float leerFloat(char mensaje[], float minimo){
    char texto[50];
    int i, error, puntos;
    float numero;
    do{
        error = 0;
        puntos = 0;
        printf("%s", mensaje);
        scanf("%49s", texto);
        limpiarBuffer();
        for(i = 0; texto[i] != '\0'; i++){
            if(texto[i] == '.'){
                puntos++;
                if(puntos > 1){
                    error = 1;
                    break;
                }
            }
            else if(texto[i] < '0' || texto[i] > '9'){
                error = 1;
                break;
            }
        }
        if(error == 1){
            printf("Numero decimal invalido\n");
        }
    }while(error == 1);
    sscanf(texto, "%f", &numero);
    while(numero < minimo){
        printf("Debe ser mayor o igual a %.2f\n", minimo);
        printf("%s", mensaje);
        scanf("%49s", texto);
        limpiarBuffer();
        sscanf(texto, "%f", &numero);
    }
    return numero;
}
void ingresarProducto(char nombres[][50],
                      int cantidades[],
                      float tiempos[],
                      float recursos[],
                      int *total){
    if(*total >= MAX_PRODUCTOS){
        printf("Maximo de productos alcanzado\n");
        return;
    }
    leerTexto("Nombre: ", nombres[*total], MAX_NOMBRE);
    cantidades[*total] =
        leerEntero("Cantidad: ", 1);
    tiempos[*total] =
        leerFloat("Tiempo por unidad: ", 0.01);
    recursos[*total] =
        leerFloat("Recursos por unidad: ", 0.01);
    (*total)++;
}
void listarProductos(char nombres[][50],
                     int cantidades[],
                     float tiempos[],
                     float recursos[],
                     int total){
    int i;
    if(total == 0){
        printf("No hay productos\n");
        return;
    }
    printf("\n-----------------------------------------------\n");
    printf("No  Nombre      Cantidad   Tiempo   Recursos\n");
    printf("-----------------------------------------------\n");
    for(i = 0; i < total; i++){
        printf("%d   %-10s %5d      %.2f      %.2f\n",
               i + 1,
               nombres[i],
               cantidades[i],
               tiempos[i],
               recursos[i]);
    }
}
int buscarProducto(char nombres[][50],
                   int total,
                   char buscado[]){
    int i, j, igual;
    for(i = 0; i < total; i++){
        igual = 1;
        for(j = 0; j < 50; j++){
            if(nombres[i][j] != buscado[j]){
                igual = 0;
                break;
            }
            if(nombres[i][j] == '\0'){
                break;
            }
        }
        if(igual){
            return i;
        }
    }
    return total;
}
void editarProducto(char nombres[][50],
                    int cantidades[],
                    float tiempos[],
                    float recursos[],
                    int total){
    char buscado[50];
    int pos;
    int opcion;
    if(total == 0){
        printf("No hay productos\n");
        return;
    }
    leerTexto("Producto a editar: ",
               buscado,
               MAX_NOMBRE);
    pos = buscarProducto(nombres,
                         total,
                         buscado);
    if(pos == total){
        printf("Producto no encontrado\n");
        return;
    }
    do{
        printf("\n1.Nombre\n");
        printf("2.Cantidad\n");
        printf("3.Tiempo\n");
        printf("4.Recursos\n");
        printf("5.Salir\n");
        opcion = leerEntero("Opcion: ", 1);
        while(opcion < 1 || opcion > 5){
            printf("Opcion invalida\n");
            opcion = leerEntero("Opcion: ", 1);
        }
        switch(opcion){
            case 1:
                leerTexto("Nuevo nombre: ",
                          nombres[pos],
                          MAX_NOMBRE);
                break;
            case 2:
                cantidades[pos] =
                    leerEntero("Nueva cantidad: ", 1);
                break;
            case 3:
                tiempos[pos] =
                    leerFloat("Nuevo tiempo: ", 0.01);
                break;
            case 4:
                recursos[pos] =
                    leerFloat("Nuevos recursos: ", 0.01);
                break;
        }
    }while(opcion != 5);
}
void eliminarProducto(char nombres[][50],
                      int cantidades[],
                      float tiempos[],
                      float recursos[],
                      int *total){
    char buscado[50];
    int pos;
    int i, j;
    if(*total == 0){
        printf("No hay productos\n");
        return;
    }
    leerTexto("Producto a eliminar: ",
               buscado,
               MAX_NOMBRE);
    pos = buscarProducto(nombres,
                         *total,
                         buscado);
    if(pos == *total){
        printf("Producto no encontrado\n");
        return;
    }
    for(i = pos; i < *total - 1; i++){
        for(j = 0; j < 50; j++){
            nombres[i][j] = nombres[i + 1][j];
        }
        cantidades[i] = cantidades[i + 1];
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
    }
    (*total)--;
    printf("Producto eliminado\n");
}
void calcularTotales(int cantidades[],
                     float tiempos[],
                     float recursos[],
                     int total,
                     float *tiempoTotal,
                     float *recursoTotal){
    int i;
    *tiempoTotal = 0;
    *recursoTotal = 0;
    for(i = 0; i < total; i++){
        *tiempoTotal += cantidades[i] * tiempos[i];
        *recursoTotal += cantidades[i] * recursos[i];
    }
}
void verificarProduccion(int cantidades[],
                         float tiempos[],
                         float recursos[],
                         int total,
                         float tiempoDisp,
                         float recursoDisp){
    float tiempoTotal;
    float recursoTotal;
    calcularTotales(cantidades,
                     tiempos,
                     recursos,
                     total,
                     &tiempoTotal,
                     &recursoTotal);
    printf("\nTiempo total requerido: %.2f\n",
           tiempoTotal);
    printf("Recursos totales requeridos: %.2f\n",
           recursoTotal);
    if(tiempoTotal <= tiempoDisp &&
       recursoTotal <= recursoDisp){
        printf("SI se puede producir\n");
    }
    else{
        printf("NO se puede producir\n");
    }
}
int main(){
    char nombres[5][50];
    int cantidades[5];
    float tiempos[5];
    float recursos[5];
    int total = 0;
    int opcion;
    float tiempoDisp;
    float recursoDisp;
    tiempoDisp =
        leerFloat("Tiempo disponible: ", 1);
    recursoDisp =
        leerFloat("Recursos disponibles: ", 1);
    do{
        printf("\n========== MENU ==========\n");
        printf("1. Ingresar producto\n");
        printf("2. Listar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular totales\n");
        printf("6. Verificar produccion\n");
        printf("7. Salir\n");
        opcion = leerEntero("Opcion: ", 1);
        while(opcion < 1 || opcion > 7){
            printf("Opcion invalida\n");
            opcion = leerEntero("Opcion: ", 1);
        }
        switch(opcion){
            case 1:
                ingresarProducto(nombres,
                                  cantidades,
                                  tiempos,
                                  recursos,
                                  &total);
                break;
            case 2:
                listarProductos(nombres,
                                 cantidades,
                                 tiempos,
                                 recursos,
                                 total);
                break;
            case 3:
                editarProducto(nombres,
                                cantidades,
                                tiempos,
                                recursos,
                                total);
                break;
            case 4:
                eliminarProducto(nombres,
                                  cantidades,
                                  tiempos,
                                  recursos,
                                  &total);
                break;
            case 5:{
                float t;
                float r;
                calcularTotales(cantidades,
                                 tiempos,
                                 recursos,
                                 total,
                                 &t,
                                 &r);
                printf("\nTiempo total: %.2f\n", t);
                printf("Recursos totales: %.2f\n", r);
                break;
            }
            case 6:
                verificarProduccion(cantidades,
                                     tiempos,
                                     recursos,
                                     total,
                                     tiempoDisp,
                                     recursoDisp);
                break;
        }
    }while(opcion != 7);
    return 0;
}