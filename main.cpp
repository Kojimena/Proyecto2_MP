/* 
UNIVERSIDAD DEL VALLE DE GUATEMALA
FACULTAD DE INGENIERÍA
DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN

Curso: Programación de microprocesadores
Actividad: Proyecto 2

Integrantes: 
Jimena Hernández 21199
Mark Albrand 
Diego Morales
Javier Azurdia 21242
            
Descripción: Programa simulador de entregas de repartidores.
 */

#include <iostream>
#include <cstdlib> // para el random 
using namespace std;
int cantidadClientes;

struct Producto{
    string nombre;
    int cantidad;
    float precio;
};

struct Cliente{
    string nombre;
    string direccion_entrega;
    double zona_entrega;
    int cantidadProductos;
    Producto productos[10];
    double tiempo;
};

Producto catalogo[] = {

    {"Papel higienico pack 6 rollos", 0,  30.00},
    {"Pechugas de pollo 1lb", 0, 25.00},
    {"Camarones 1lb", 0, 15.00},
    {"Crema humectante 400ml", 0, 80.00},
    {"Tortrix limón pack 6 bolsas", 0, 30.00},
    {"Coca-cola pack 6 latas", 0, 40.00},
    {"Desodorante 150mL", 0, 30.00},
    {"Shampoo 1l", 0, 60.00},
    {"XL Sour Blast 750mL", 0, 70.00},
    {"Cerveza Gallo pack 15 latas", 0, 110.00},
    {"Cigarros Malboro Cajetilla", 0, 28.00},
    {"Aceite Ideal 800mL", 0, 60.00},
    {"Combo Hambuerguesa", 0, 50.00},
    {"Bandeja Sushi 2 rollos", 0, 130.00},
    {"Combo 2 hotdogs", 0, 30.00},
    {"Papas Fritas con queso", 0, 15.00},
    {"Pollo rostizado entero", 0, 120.00},
    {"Combo 10 alitas", 0, 80.00},
    {"Combo sandwitch pollo", 0, 40.00},
    {"Pizza personal", 0, 40.00},
    {"Donas 3 pack", 0, 15.00},
    {"Monster lata", 0, 15.00},
    {"Red Bull lata", 0, 15.00},
    {"Vodka Smirnoff 750 ml", 0, 130.00}
};


int determinar_distancia(int zona){
    double km = 0.0;
    switch (zona)
    {
    case 1:    
    km=15.0;    
        break;
    case 2:
    km=8.9;      
        break;
    case 3:   
    km=6.7;      
        break;
    case 4:  
    km=5.3;       
        break;
    case 5:   
    km=5.0;      
        break;
    case 6:   
    km=12.1;      
        break;
    case 7:
    km=13.4;         
        break;
    case 8:
    km=5.6;         
        break;
    case 9:
    km=4.5;         
        break;
    case 10:
    km=7.5;         
        break;
    case 11:  
    km=9.7;       
        break;
    case 12:   
    km=12.2;      
        break;
    case 13:  
    km=8.5;       
        break;
    case 14:    
    km=5.9;     
        break;
    case 15:    
    km=1;     
        break;
    case 16:  
    km=15.0;       
        break;
    case 17: 
    km=5.7;        
        break;
    case 18:  
    km=10.7;       
        break;
    case 19:  
    km=18.7;       
        break;
    case 21:  
    km=17.5;       
        break;
    case 24:  
    km=12.1;       
        break;
    case 25:  
    km=20.0;;       
        break;    
    default:
    km = -1;
        break;
    }
    return km;
}

void imprimir_catalogo(){
    cout << "------------------------------------CATALOGO DE PRODUCTOS------------------------------------" << endl;
    for (int i = 0; i < 24; i++)
    {
        Producto prod = catalogo[i];
        cout<< "\n"<<(i+1) <<prod.nombre << ": Q." << prod.precio <<endl;
    }
    cout << "---------------------------------------------------------------------------------------------" << endl;
}

//funcion para calcular el total de productos vendidos y el total de dinero
void* totalVendido(void *args){ // recibe como parámetros struct Cliente
    Cliente *cliente = (Cliente*) args;
    float total = 0;
    int totalProductos = 0;
    for(int i = 0; i < cliente->cantidadProductos; i++){
        total += cliente->productos[i].precio * cliente->productos[i].cantidad;
        totalProductos += cliente->productos[i].cantidad;
    }
    cout << "Total de productos vendidos: " << totalProductos << endl;
    cout << "Total de dinero: " << total << endl;
}

void* tiempo_entrega(void *args){ // recibe como parámetros struct Cliente
    
    Cliente *cliente = (Cliente*) args;
    
    // obtener la zona_entrega del struct
    int zona = cliente->zona_entrega;
    int distancia = determinar_distancia(zona);
    int eventorand = 5 - rand() % 10 + 1; // velocidad aleatoria entre 1 y 10
    int velocidad = 60;
    int tiempo = (distancia / velocidad) + eventorand;
    cliente->tiempo = tiempo;
    
}

// Subrutina principal para simular las actividades de cada moto de manera individual
void* repartir(void *args){
    
}


int main(){
    // Variables
    int cant_clientes = 1;
    bool cont = true;
    int opcion;

    // HIlos

    
    //Se declara un array de tamaño dinámico para la cantidad de clientes.
    Cliente* clientes = (Cliente*)malloc(sizeof(Cliente)*cant_clientes);
    cout << "\nBienvenido a PanaPedidos\n" << endl;    
    
    while (cont)
    {
        Cliente cliente;
        cout<<"Ingrese su nombre: "<<endl;
        cin>>cliente.nombre;
        cout << "Ingrese el número de la zona de entrega: " << endl;
        cin >> cliente.zona_entrega;
        cout<<"Ingrese su direccion de entrega: "<<endl;
        cin>>cliente.direccion_entrega;
        

        // Pedir la orden
        imprimir_catalogo();
        
        cout<<"\nElija un máximo de 10 productos, ingresando su identificador.\n  Para finalizar ingrese 0. "<<endl;
        for (int i = 0; i < 10; i++)
        {
            int id = 0;
            cin >> id;

            if(id == 0){
                break;  // Salir del IF
            }

            Producto prod = catalogo[id + 1];
            cliente.productos[i] = prod;
        }
        
        


        // Generar cantidad de clientes variable
        cout << "Desea agregar otro cliente? (1 = si, 0 = no)" << endl;
        cin >> opcion;
        
        if (opcion == 1){
            cont = true;
            clientes = (Cliente*)realloc(clientes, sizeof(Cliente)*cant_clientes);
            cant_clientes++;
        }
        else{
            
            cont = false;
        }
        

    }
    

    cout << "\nSu pedido ha sido enviado a: " << clientes[0].direccion_entrega << endl;
    cout << "Su pedido ha sido enviado a: " << clientes[0].nombre << endl;

}
