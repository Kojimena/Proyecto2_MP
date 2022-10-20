#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
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
#include <cstdlib> // para el random
#include <vector>

#define NTHREADS 4 //  hilos a crear
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
};

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

double determinar_distancia(int zona){
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

void imprimir_catalogo(){
    cout << "------------------------------------CATÁLOGO DE PRODUCTOS------------------------------------" << endl;
    for (int i = 0; i < 24; i++)
    {
        Producto prod = catalogo[i];
        cout<< (i+1)<<". " <<prod.nombre << ": Q." << prod.precio <<endl;
    }
    cout << "---------------------------------------------------------------------------------------------" << endl;
}

//función para calcular el total de productos vendidos y el total de dinero
void* totalVendido(void *args){ // recibe como parámetros struct Cliente
    Cliente *cliente = (Cliente*) args;
    float total = 0;
    for(int i = 0; i < cliente->cantidadProductos; i++){
        total += cliente->productos[i].precio * cliente->cantidadProductos;
    }
    cout << "---------------------------------------------" << endl;
    cout << "Total de productos vendidos: " << cliente->cantidadProductos << endl;
    cout << "Total de ganancias: " << total << endl;
}

void* tiempo_entrega(void *args){ // recibe como parámetros struct Cliente
    Cliente *cliente = (Cliente*) args;
    // obtener la zona_entrega del struct
    int zona = cliente->zona_entrega;
    double distancia = determinar_distancia(zona);
    if (distancia <= 0){ // si la zona no existe
        cout << "Zona sin cobertura" << endl;
        return nullptr;
    }else{   
        double evento_rand = rand() % 10 + 1;
        double velocidad = 50.00;
        double tiempo = (distancia / (velocidad + evento_rand)) * 60.00; //la velocidad será suma de la velocidad base y un número aleatorio entre 1 y 10.
        cliente->tiempo = tiempo; // se guarda el tiempo en el struct
        cout << "Tiempo de entrega: " << tiempo << " minutos" << endl;
    }
}

// Subrutina principal para simular las actividades de cada moto de manera individual
void* repartir(void *args){
    
}


int main(){
    // Hilos
    int rc;
    pthread_t tid[NTHREADS];
    pthread_attr_t attr;  //atributos de los hilos
    pthread_attr_init(&attr); //inicializar los atributos de los hilos
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); //crear los hilos como joinable (se pueden unir)

    // Variables
    int cant_clientes = 1;
    bool cont = true;
    int opcion;

    // Hilos

    //Se declara un array de tamaño dinámico para la cantidad de clientes.
    Cliente* clientes = (Cliente*)malloc(sizeof(Cliente) * cant_clientes);
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
        
        int cant_prod = 0;
        cout<<"\nElija los productos que desea, ingresando su identificador.\n  Para finalizar ingrese 0. "<<endl;
        int id = -1;
        while(id != 0){
            cin >> id;  // Ingreso de un producto

            if(id == 0){  // Terminar la orden
                break;
            }
            cant_prod++;
            Producto prod = catalogo[id - 1]; // Se obtiene el producto del catálogo
            cliente.productos.push_back(prod); // Se agrega el producto al cliente
        }
        cliente.cantidadProductos = cant_prod;
        clientes[cant_clientes - 1] = cliente;

        // Repaso de la orden
        cout << "Cantidad de productos: " << cliente.cantidadProductos << endl;
        cout << "Su orden contiene los siguientes productos: " << endl;
        for (int i = 0; i < cant_prod; i++)
        {
            Producto prod = cliente.productos[i];
            cout << prod.nombre << ": Q." << prod.precio << endl;
        }


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
        rc = pthread_create(&tid[i], &attr, tiempo_entrega, (void*)(&clientes[0]));
        
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

    // Funcion para calcular el total de clientes por operador.
    int n1;
    int n2;
    int n3;
    int n4;

    if (cant_clientes > 4){
        n1 = cant_clientes / 4;
        n2 = cant_clientes / 4;
        n3 = cant_clientes / 4;
        n4 = (cant_clientes / 4) + (cant_clientes % 4);
    }

    if (cant_clientes == 4){ // mas de algo va a servir esto.
        n1 = 1;
        n2 = 1;
        n3 = 1;
        n4 = 1;
    }

    if (cant_clientes < 4){
        if(cant_clientes == 1){
            n1 = 1;
            n2 = 0;
            n3 = 0;
            n4 = 0;
        } else if (cant_clientes == 2){
            n1 = 1;
            n2 = 1;
            n3 = 0;
            n4 = 0;
        } else if (cant_clientes == 3){
            n1 = 1;
            n2 = 1;
            n3 = 1;
            n4 = 0;
        }
    }


    /**
     * si cantidad clientes < 4
     *  lo de arriba.
     *
     *  Si hay menos de 4 clientes, no sería más fácil usar un case? Digamos
     *  que hay solo2, entonces solo usamos dos motoristas.
     *
     *  En realidad, nos sale hasta mas "caro" usar mas de un solo motorista para cada cliente.
     *
     */


    Cliente clienteMotorista1[n1];
    Cliente clienteMotorista2[n2];
    Cliente clienteMotorista3[n3];
    Cliente clienteMotorista4[n4];

    

    // Calcular el total vendido
    for (int i=0; i<NTHREADS; i++) {
        rc = pthread_create(&tid[i], &attr, totalVendido, (void*)(&clientes[0]));
        
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

    pthread_attr_destroy(&attr);
    
}



#pragma clang diagnostic pop