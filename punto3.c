#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Producto {
int ProductoID; //Numerado en ciclo iterativo
int Cantidad; // entre 1 y 10
char *TipoProducto; // Algún valor del arreglo TiposProductos
float PrecioUnitario; // entre 10 - 100
};
typedef struct Producto Producto;
struct Cliente {
int ClienteID; // Numerado en el ciclo iterativo
char *NombreCliente; // Ingresado por usuario
int CantidadProductosAPedir; // (aleatorio entre 1 y 5)
Producto *Productos; //El tamaño de este arreglo depende de la variable
// “CantidadProductosAPedir”
};

typedef struct Cliente item;
struct Tnodo{
    item dato;
    struct Tnodo* siguiente;
};typedef struct Tnodo Tnodo;

char Nombres[3][20]={"Gonzalo","Tomas","Ricardo"};
char *TiposProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};;

item CargarCliente(int id);
void MuestraCliene(item estruct);
Tnodo* CrearListaVacia();
bool EsListaVacia(Tnodo* cabecera);
Tnodo* CrearNodo(item dato);
void InsertarNodo(Tnodo** cabecera, Tnodo* nodo);
void MostrarLista(Tnodo* lista);
float CostoTotalProducto(Tnodo* lista);
Tnodo* BuscaNodoPorId(Tnodo* lista, int id);
Producto BuscaProductoPorId(Tnodo* nodo, int id);
float CostoTotalCliente(Tnodo* lista);
void LiberaMemoria(Tnodo**lista);

int main(){
    printf("Ingrese la cantidad de clientes a cargar:  ");
    int clientes;
    scanf("%d", &clientes);
    item cliente;
    Tnodo* nodo;
    Tnodo* lista =CrearListaVacia();
    for (int i = 0; i < clientes; i++)
    {
        cliente=CargarCliente(i);
        nodo=CrearNodo(cliente);
        InsertarNodo(&lista,nodo);
    }
    MostrarLista(lista);
    printf("\n==========================CALCULA COSTO===========================\n");
    float costo=CostoTotalProducto(lista);
    printf("\nCosto total: %.2f ", costo);
    printf("\n====================================CALCULO COSTO CLIENTE===========================\n");
    float costoCliente=CostoTotalCliente(lista);
    printf("\nCosto total cliente: %.2f", costoCliente);
    LiberaMemoria(&lista);
    MostrarLista(lista);

}

item CargarCliente(int id){
    item cliente;
    cliente.CantidadProductosAPedir=rand()%6;
    cliente.ClienteID=id;
    cliente.NombreCliente=(char*)malloc(sizeof(char)*15);
    fflush(stdin);
    printf("\nNombre:  ");
    gets(cliente.NombreCliente);
    cliente.Productos=(Producto*)malloc(sizeof(Producto)*cliente.CantidadProductosAPedir);
    for (int i = 0; i < cliente.CantidadProductosAPedir; i++)
    {
        cliente.Productos[i].Cantidad=1+rand()%10;
        cliente.Productos[i].PrecioUnitario=10+rand()%91;
        cliente.Productos[i].ProductoID=i;
        cliente.Productos[i].TipoProducto=TiposProductos[rand()%5];
    }
    return(cliente);
}

Tnodo* CrearListaVacia(){
    return(NULL);
}

bool EsListaVacia(Tnodo* cabecera){
    if(cabecera==NULL){
        return(true);
    }else
    {
        return(false);
    }
    
}

Tnodo* CrearNodo(item dato){
    Tnodo* nodo=(Tnodo*)malloc(sizeof(struct Tnodo*));
    nodo->dato=dato;
    nodo->siguiente=NULL;
    return(nodo);
}

void InsertarNodo(Tnodo** cabecera, Tnodo* nodo){
    nodo->siguiente=*cabecera;
    *cabecera=nodo;
}

void MostrarLista(Tnodo* lista){
    printf("\n==================================MUESTRA LISTA===================================\n");
    while (!EsListaVacia(lista))
    {
        printf("\n--------------------MUESTRA NODO ------------\n");
        MuestraCliene(lista->dato);
        lista=lista->siguiente;
    }
    
}

void MuestraCliene(item estruct){
    printf("\n__________________DATOS CLIENTE %d_______________\n",estruct.ClienteID);
    printf("Nombre: %s\nId: %d\nCantidad Productos a pedir: %d", estruct.NombreCliente, estruct.ClienteID, estruct.CantidadProductosAPedir);
    for (int i = 0; i < estruct.CantidadProductosAPedir; i++)
    {
        printf("\n---------------------PRODUCTO %d----------------\n", estruct.Productos[i].ProductoID);
        printf("ID: %d\nCantidad: %d\nTipo: %s\nPrecio: %.2f", estruct.Productos[i].ProductoID,estruct.Productos[i].Cantidad,estruct.Productos[i].TipoProducto,estruct.Productos[i].PrecioUnitario);
    }
    
}

float CostoTotalProducto(Tnodo* lista){
    float costo=0;
    int id;
    printf("\nIngrese el id del cliente del que desea buscar un producto:  ");
    scanf("%d", &id);
    Tnodo* buscado=BuscaNodoPorId(lista,id);
    if(buscado){
        printf("\nIngrese el id del producto que desea buscar:  ");
        scanf("%d", &id);
        Producto Prodbuscado=BuscaProductoPorId(buscado,id);
        costo=Prodbuscado.Cantidad*Prodbuscado.PrecioUnitario;
        
    }
    return(costo);

}

Tnodo* BuscaNodoPorId(Tnodo* lista, int id){
    Tnodo* buscado=NULL;
    while (!EsListaVacia(lista) && lista->dato.ClienteID!=id)
    {
        lista=lista->siguiente;
    }
    if (!EsListaVacia(lista))
    {
        buscado=lista;
    }
    return(buscado);
    
    
}

Producto BuscaProductoPorId(Tnodo* nodo, int id){
    Producto buscado;
    int bandera=0;
    if (!EsListaVacia(nodo))
    {
        for (int i = 0; i < nodo->dato.CantidadProductosAPedir; i++)
        {
            if (nodo->dato.Productos[i].ProductoID==id)
            {
                buscado= nodo->dato.Productos[i];
                bandera=1;
            }
            
        }
        if (bandera==1)
        {
            return(buscado);
        }
         
    }
    
}

float CostoTotalCliente(Tnodo* lista){
    float costo=0;
    Tnodo* nodoBuscado=NULL;
    printf("\nIngrese el id del cliente buscado:  ");
    int id;
    scanf("%d", &id);
    nodoBuscado=BuscaNodoPorId(lista,id);
    if (nodoBuscado)
    {
        for (int i = 0; i < nodoBuscado->dato.CantidadProductosAPedir; i++)
        {
            costo+=nodoBuscado->dato.Productos[i].Cantidad*nodoBuscado->dato.Productos[i].PrecioUnitario;
        }
        
    }
    return(costo);
}

void LiberaMemoria(Tnodo**lista){
    Tnodo* aux;
    int i;
    while (!EsListaVacia(*lista))
    {
        aux=*lista;
        free(aux->dato.NombreCliente);
        free(aux->dato.Productos);
        *lista=(*lista)->siguiente;
        free(aux);
        
    }
    
}