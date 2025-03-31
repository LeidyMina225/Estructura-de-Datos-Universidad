#include <iostream>
#include <string>

//Integrantes: LEIDY MELISSA GIRALDO MINA - LICETH YAILINETH RIASCOS ESCOBAR 

using namespace std;

struct Nodo {
    int id;
    char nombre[30];
    int edad;
    char genero;
    char motivo[50];
    Nodo* sig;
};

Nodo* fifo = NULL;    
Nodo* hist = NULL;   
Nodo* aux = NULL;
Nodo* aux2 = NULL;

void agregarCliente(){
    aux = (Nodo*)malloc(sizeof(Nodo));
    
    cout << "Ingrese el ID del cliente: ";
    cin >> aux->id;
    cin.ignore();
    cout << "Nombre: ";
    cin.getline(aux->nombre, 30);
    cout << "Edad: ";
    cin >> aux->edad;
    cout << "Genero (M/F): ";
    cin >> aux->genero;
    aux->genero = toupper(aux->genero);
    cin.ignore();
    cout << "Motivo de la llamada: ";
    cin.getline(aux->motivo, 50);
    
    aux->sig = NULL;
    
    if(!fifo){
        fifo = aux;
    }else{
        aux2 = fifo;
        while(aux2->sig != NULL){
            aux2 = aux2->sig;
        }
        aux2->sig = aux;
    }
    
    cout<<"Cliente agregado con éxito!"<<endl;
}

void mostrarClientes(){
    aux = fifo;
    if(!aux){
        cout<<"No hay clientes en espera."<<endl;
        return;
    }

    cout<<"\nClientes en espera:"<<endl;
    while (aux != NULL) {
        cout << "ID: " <<aux->id<<endl;
        cout<<" | Nombre: " <<aux->nombre<<endl;
        cout<<" | Edad: "<<aux->edad<<endl;
        cout<<" | Genero: "<<aux->genero<<endl;
        cout<<" | Motivo: "<<aux->motivo<<endl;
        aux = aux->sig;
    }
}

void contarClientes(){
    int contador = 0;
    aux = fifo;
    while(aux != NULL){
        contador++;
        aux = aux->sig;
    }
    cout<<"Clientes en espera: "<<contador<<endl;
}

void registrarHistorial(Nodo* cliente){
    cliente->sig = hist;
    hist = cliente;
}

void atenderCliente(){
    if(!fifo){
        cout<<"No hay clientes para atender."<<endl;
        return;
    }

    aux = fifo;
    fifo = fifo->sig;

    if(aux->edad < 18){
        cout<<"No se puede atender a menores de edad."<<endl;
        aux->sig = fifo;
        fifo = aux;
        return;
    }

    registrarHistorial(aux);
    
    cout<<"Cliente atendido: "<<aux->nombre<<endl;
}

void mostrarHistorial() {
    aux = hist;
    if(!aux){
        cout<<"No hay historial de atenciones."<<endl;
        return;
    }

    cout<<"\nHistorial de atenciones:"<<endl;
    while (aux != NULL) {
        cout<<"ID: "<<aux->id<<" | Nombre: "<<aux->nombre<<" | Edad: "<<aux->edad
             <<" | Genero: "<<aux->genero<<" | Motivo: "<<aux->motivo<<endl;
        aux = aux->sig;
    }
}

void deshacerUltimaAtencion() {
    if(!hist){
        cout<<"No hay atenciones previas para deshacer."<<endl;
        return;
    }

    aux = hist;
    hist = hist->sig;
    aux->sig = fifo;
    fifo = aux;

    cout<<"Se deshizo la última atención."<<endl;
}

int main() {
    int opcion;
    do {
        cout<<"\nMENU"<<endl;
        cout<<"1. Agregar cliente a la cola"<<endl;
        cout<<"2. Mostrar clientes en espera"<<endl;
        cout<<"3. Total clientes en espera"<<endl;
        cout<<"4. Atender siguiente cliente"<<endl;
        cout<<"5. Historial de atenciones"<<endl;
        cout<<"6. Deshacer última atención"<<endl;
        cout<<"7. Salir"<<endl;
        cout<<"Seleccione una opción: ";
        cin>>opcion;
        
        switch (opcion) {
            case 1: agregarCliente(); break;
            case 2: mostrarClientes(); break;
            case 3: contarClientes(); break;
            case 4: atenderCliente(); break;
            case 5: mostrarHistorial(); break;
            case 6: deshacerUltimaAtencion(); break;
            case 7: cout<<"Saliendo del sistema..."<<endl; break;
            default: cout<<"Opción inválida. Intente de nuevo."<<endl;
        }
    } while (opcion != 7);
    
    return 0;
}