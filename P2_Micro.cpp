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
Javier Azurdia
            
Descripción: Programa simulador de entregas de repartidores.
 */

#include <iostream>
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
    int cantidadProductos;

};

int main(){
    Cliente clientes[1];
    Producto productos[1];
    cout << "\nBienvenido a PanaPedidos\n" << endl;

    cout<<"Ingrese su direccion de entrega: "<<endl;
    cin>>clientes[0].direccion_entrega;
    cout<<"Ingrese su nombre: "<<endl;
    cin>>clientes[0].nombre;
    cout<<"Ingrese el nombre del producto: "<<endl;
    cin>>productos[0].nombre;
    cout<<"Ingrese la cantidad de este producto que desea: "<<endl;
    cin>>productos[0].cantidad;
    cout<<"Ingrese el precio del producto: "<<endl;
    cin>>productos[0].precio;

    cout << "\nSu pedido ha sido enviado a: " << clientes[0].direccion_entrega << endl;
    cout << "Su pedido ha sido enviado a: " << clientes[0].nombre << endl;




/*     int cantidadClientes;
    cout << "Ingrese la cantidad de clientes: " << endl;
    cin >> cantidadClientes;
    Cliente clientes[cantidadClientes];
    for(int i = 0; i < cantidadClientes; i++){
        cout << "Ingrese la direccion de entrega del cliente " << i+1 << ": " << endl;
        cin >> clientes[i].direccion_entrega;
        cout << "Ingrese la cantidad de productos del cliente " << i+1 << ": " << endl;
        cin >> clientes[i].cantidadProductos;

        //mostrar un catalogo de productos y que el cliente elija los productos que quiere

        

        Producto productos[clientes[i].cantidadProductos];
        for(int j = 0; j < clientes[i].cantidadProductos; j++){
            cout << "Ingrese el nombre del producto " << j+1 << ": " << endl;
            cin >> productos[j].nombre;
            cout << "Ingrese la cantidad del producto " << j+1 << ": " << endl;
            cin >> productos[j].cantidad;
            cout << "Ingrese el precio del producto " << j+1 << ": " << endl;
            cin >> productos[j].precio;
        }
    }
    return 0; */

}

