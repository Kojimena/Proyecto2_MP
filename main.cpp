/*************************************************************************
UNIVERSIDAD DEL VALLE DE GUATEMALA
FACULTAD DE INGENIERÍA
DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN

Curso: Programación de microprocesadores
Actividad: Proyecto 2

Integrantes: 
Jimena Hernández 21199
Mark Albrand 21004
Diego Morales 21146
Javier Azurdia 21242
            
Descripción: Programa simulador de entregas de repartidores.
***********************************************************************/

#include <iostream>
#include <cstdlib> 
#include <vector>
#include <unistd.h>

// Variables globales
#define NTHREADS 4 
pthread_mutex_t mutex;

using namespace std;

struct Producto{ //estructura de los productos
    string nombre;
    double precio;
};

struct Cliente{ //estructura de los clientes
    string nombre;
    string direccion_entrega;
    double zona_entrega;
    int cantidadProductos;
    vector<Producto> productos;
    double tiempo;
    double subtotal;
};

//Catalogo de productos
Producto catalogo[] = {
    {"Papel higiénico pack 6 rollos", 30.00},
    {"Pechugas de pollo 1lb", 25.00},
    {"Camarones 1lb", 15.00},
    {"Crema humectante 400ml", 80.00},
    {"Tortrix limón pack 6 bolsas", 30.00},
    {"Coca-Cola pack 6 latas", 40.00},
    {"Desodorante 150mL", 30.00},
    {"Shampoo 1L", 60.00},
    {"XL Sour Blast 750mL", 70.00},
    {"Cerveza Gallo pack 15 latas", 110.00},
    {"Cigarros Malboro Cajetilla", 28.00},
    {"Aceite Ideal 800mL", 60.00},
    {"Combo Hamburguesa", 50.00},
    {"Bandeja Sushi 2 rollos", 130.00},
    {"Combo 2 hot-dogs", 30.00},
    {"Papas Fritas con queso", 15.00},
    {"Pollo rostizado entero", 120.00},
    {"Combo 10 alitas", 80.00},
    {"Combo sandwich pollo", 40.00},
    {"Pizza personal", 40.00},
    {"Donas 3 pack", 15.00},
    {"Monster lata", 15.00},
    {"Red Bull lata", 15.00},
    {"Vodka Smirnoff 750 ml", 130.00}
};

double determinar_distancia(int zona){ //funcion para determinar la distancia de entrega
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
        km=20.0;
        break;    
    default:
        km = -1;
        break;
    }
    return km;
}

void imprimir_catalogo(){ //funcion para imprimir el catalogo de productos
    cout << "\n------------------------------------CATÁLOGO DE PRODUCTOS------------------------------------" << endl;
    for (int i = 0; i < 24; i++)
    {
        Producto prod = catalogo[i];
        cout<< (i+1)<<". " <<prod.nombre << ": Q." << prod.precio <<endl;
    }
    cout << "---------------------------------------------------------------------------------------------" << endl;
}

//función para calcular el subtotal del pedido de cada clliente
void* SubtotalCliente(void *args){ // recibe como parámetros struct Cliente
    Cliente *cliente = (Cliente*) args;
    double subtotal = 0;
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < cliente->cantidadProductos; i++){ 
        subtotal += cliente->productos[i].precio; //calcula el subtotal
    }
    cliente->subtotal = subtotal; // se guarda el subtotal en la estructura del cliente 
    pthread_mutex_unlock(&mutex); 
}

// Función para determinar el tiempo de entrega
void* tiempo_entrega(void *args){ // recibe como parámetros struct Cliente
    Cliente *cliente = (Cliente*) args;
    // obtener la zona_entrega del struct
    int zona = cliente->zona_entrega;
    double distancia = determinar_distancia(zona);
    if (distancia <= 0){ // si la zona no existe
        cout << "Zona sin cobertura" << endl;
        return nullptr;
    }else{   
        double evento_rand = (rand() % 10) + 1;
        double velocidad = 50.00;
        double tiempo = (distancia / (velocidad - evento_rand)) * 60.00; //la velocidad será suma de la velocidad base y un número aleatorio entre 1 y 10.
        pthread_mutex_lock(&mutex);
        cliente->tiempo = tiempo; // se guarda el tiempo en el struct
        pthread_mutex_unlock(&mutex); 
    }
}

// Subrutina principal para simular las actividades de cada moto de manera individual
void* repartir(void *args){
    Cliente *clientesRepartir = (Cliente*) args;
    sleep(clientesRepartir->tiempo);  // Se simulará el tiempo con la relación de 1 minuto == 1 segundo en sleep
    cout << "Se ha realizado la entrega de: " << clientesRepartir->nombre << endl;    
}


int main(){
    int rc;
    pthread_t tid[NTHREADS];
    pthread_attr_t attr;  //atributos de los hilos
    pthread_attr_init(&attr); //inicializar los atributos de los hilos
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); //crear los hilos como joinable (se pueden unir)

    // Variables
    int cant_clientes = 1;
    bool cont = true;
    int opcion;
    
    Cliente* clientes = (Cliente*)malloc(sizeof(Cliente) * cant_clientes);  //Se declara un array de tamaño dinámico para la cantidad de clientes.
    cout << "\nBienvenido a PanaPedidos\n" << endl; 
    cout << "\nPor favor, ingresa los siguientes datos para poder realizar tu pedido\n" << endl;    
    
    while (cont)
    {
        Cliente cliente;
        cout<<"Ingrese su nombre: "<<endl;
        cin>>cliente.nombre;
        cout << "Indique el número de la zona de entrega: " << endl;
        cin >> cliente.zona_entrega;
        // Se verifica que la zona de entrega sea válida
        if (cliente.zona_entrega >= 1 && cliente.zona_entrega <= 25){
            if(cliente.zona_entrega == 20 || cliente.zona_entrega == 22 || cliente.zona_entrega == 23){
                cout << "Zona sin cobertura" << endl;
                continue;
            }else{
                cout<<"Ingrese su direccion de entrega: "<<endl;
                cin>>cliente.direccion_entrega; 
            }
        }else{
            cout << "Zona sin cobertura" << endl;
            continue;
        }
        
        // Se imprime el catálogo de productos
        imprimir_catalogo();
        
        // Se pide al usuario que ingrese la cantidad de productos que desea
        int cant_prod = 0;
        cout<<"\nElija los productos que desea, ingresando su identificador.\n  Para finalizar ingrese 0. "<<endl;
        int id = -1;
        while(id != 0){
            cin >> id;  // Ingreso de un producto
            if(id == 0){  // Terminar la orden
                break;
            } else if (id < 0 || id > 24) {
                cout  << "Producto no encontrado" << endl;
                break;
            }
            cant_prod++;
            Producto prod = catalogo[id - 1]; // Se obtiene el producto del catálogo
            cliente.productos.push_back(prod); // Se agrega el producto al cliente
        }
        cliente.cantidadProductos = cant_prod;
        clientes[cant_clientes - 1] = cliente;        

        // Generar cantidad de clientes variable
        cout << "\nDesea agregar otro cliente? (1 = si, 0 = no)" << endl;
        cin >> opcion;
        
        if (opcion == 1){
            cont = true;
            cant_clientes++;
            clientes = (Cliente*)realloc(clientes, sizeof(Cliente)*cant_clientes);
        }
        else{
            cont = false;
        }        
    }

    // Calcular los tiempos de entrega para cada cliente
    for (int i=0; i<NTHREADS; i++) {
        for (int j = 0; j < cant_clientes; ++j) {
            rc = pthread_create(&tid[i], &attr, tiempo_entrega, (void*)(&clientes[j]));
        }

        // La variable rc recibe errores en formato entero
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc); //si hay error, imprimir el error
            exit(-1); //salir del programa
        }
    }
    for (int i=0; i<NTHREADS; i++) {
        rc = pthread_join(tid[i], nullptr);
        if (rc) {
        printf("ERROR; return code from pthread_join() is %d\n", rc); //si hay error, imprimir el error
        exit(-1); //salir del programa
        }
    }

    //calcular el total de clientes por operador.
    int n1, n2, n3, n4;

    int cantidad_motos; 

    if (cant_clientes > 4){
        n1 = cant_clientes / 4;
        n2 = cant_clientes / 4;
        n3 = cant_clientes / 4;
        n4 = (cant_clientes / 4) + (cant_clientes % 4);
        
        cantidad_motos = 4;
        
    }

    if (cant_clientes == 4){
        n1 = 1;
        n2 = 1;
        n3 = 1;
        n4 = 1;
        cantidad_motos = 4;

    }

    if (cant_clientes < 4){
        if(cant_clientes == 1){
            n1 = 1;
            n2 = 0;
            n3 = 0;
            n4 = 0;
            cantidad_motos = 1;
            
        } else if (cant_clientes == 2){
            n1 = 1;
            n2 = 1;
            n3 = 0;
            n4 = 0;
            cantidad_motos = 2;
        } else if (cant_clientes == 3){
            n1 = 1;
            n2 = 1;
            n3 = 1;
            n4 = 0;
            cantidad_motos = 3;
        }
    }

    Cliente clienteMotorista1[n1];
    Cliente clienteMotorista2[n2];
    Cliente clienteMotorista3[n3];
    Cliente clienteMotorista4[n4];
    

    // asignar los clientes a los arrays.
    for(int i = 0; i < n1; i++){
        clienteMotorista1[i] = clientes[i];
    }

    for(int i = 0; i < n2; i++){
        clienteMotorista2[i] = clientes[i+n1];
    }

    for(int i = 0; i < n3; i++){
        clienteMotorista3[i] = clientes[i+n1+n2];
    }

    for(int i = 0; i < n4; i++){
        clienteMotorista4[i] = clientes[i+n1+n2+n3];
    }
    
    // Repartir a todos los clientes
    // Moto 1
    for(int i=0; i<n1; i++){
        cout<<"El tiempo a entregar para " << clienteMotorista1[i].nombre << " es de " << clienteMotorista1[i].tiempo<<" minutos"<<endl;
        rc = pthread_create(&tid[0], &attr, repartir, (void*)(&clienteMotorista1[i]));
    }
    // Moto 2    
    for(int i=0; i<n2; i++){
        cout<<"El tiempo a entregar para " << clienteMotorista2[i].nombre << " es de " << clienteMotorista2[i].tiempo<<" minutos"<<endl;
        rc = pthread_create(&tid[1], &attr, repartir, (void*)(&clienteMotorista2[i]));
    }
    // Moto 3
    for(int i=0; i<n3; i++){
        cout<<"El tiempo a entregar para " << clienteMotorista3[i].nombre << " es de " << clienteMotorista3[i].tiempo<<" minutos"<<endl;
        rc = pthread_create(&tid[2], &attr, repartir, (void*)(&clienteMotorista3[i]));

    }
    // Moto 4
    for(int i=0; i<n4; i++){
        cout<<"El tiempo a entregar para " << clienteMotorista1[i].nombre << " es de " << clienteMotorista1[i].tiempo<<" minutos"<<endl;
        rc = pthread_create(&tid[3], &attr, repartir, (void*)(&clienteMotorista4[i]));

    }
    
    for (int i=0; i<NTHREADS; i++) {
        rc = pthread_join(tid[i], nullptr);
    }
    
    
    for (int j = 0; j < cant_clientes; j++)
    {
        rc = pthread_create(&tid[0], &attr, SubtotalCliente, (void*)(&clientes[j]));
    }    

    
    for (int i=0; i<NTHREADS; i++) {
        rc = pthread_join(tid[i], nullptr);
    }

    // Resumen de ventas
    cout << "Facturas" << endl;
    double ventas = 0;
    for (int i = 0; i < cant_clientes; i++)
    {
        ventas += clientes[i].subtotal;
        // Repaso de la orden
        cout<<"\nOrden a nombre de: " << clientes[i].nombre << endl;
        cout<<"Dirección de entrega: " << clientes[i].direccion_entrega << endl;
        cout << "Cantidad de productos: " << clientes[i].cantidadProductos << endl;
        cout << "La orden contiene los siguientes productos: " << endl;
        for (int j = 0; j < clientes[i].cantidadProductos; j++)
        {
            Producto prod = clientes[i].productos[j];
            cout << "\t-> " << prod.nombre << ": Q." << prod.precio << endl;
        }
        cout << "\nSubtotal de la orden: Q." << clientes[i].subtotal << endl;
    }
    

    // Mensajes de salida
    cout<<"\nEl total de ventas del día es de: Q." << ventas << endl;
    cout<<"\nSe han termiado de repartir los pedidos"<< endl;
    cout<<"Gracias por usar el sistema de pedidos PanaPedidos"<< endl;
    cout<<"Hasta pronto!"<< endl;

    // Liberar memoria
    pthread_attr_destroy(&attr);
    free(clientes);
    return 0;
}