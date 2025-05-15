#include <iostream>
#include <cstring>
//integrantes: LEIDY MELISSA GIRALDO MINA & LICETH YAILINETH RIASCOS ESCOBAR 

using namespace std;

struct Pelicula {
    char nombre[50];
    int fechaestreno;
    char genero[30];
    float recaudacion;
    struct Pelicula* izq;
    struct Pelicula* der;
};

struct Pelicula* raiz = NULL;
struct Pelicula* aux;
struct Pelicula* aux2 = NULL;
struct Pelicula* padre = NULL;

// Función para posicionar un nodo según el año
void posicionarNodo(struct Pelicula* nuevaRaiz) {
    if (aux->fechaestreno < nuevaRaiz->fechaestreno || aux->fechaestreno == nuevaRaiz->fechaestreno) {
        if(nuevaRaiz->izq == NULL){
            nuevaRaiz->izq = aux;
        }else{
            posicionarNodo(nuevaRaiz->izq);
        }
    }else{
        if(nuevaRaiz->der == NULL){
            nuevaRaiz->der = aux;
        }else{
            posicionarNodo(nuevaRaiz->der);
        }
    }
}

void agregarPelicula(){
    aux = (struct Pelicula*) malloc(sizeof(struct Pelicula));
    aux->izq = aux->der = NULL;

    cout<<"Nombre de la pelicula: ";
    cin.ignore();
    cin.getline(aux->nombre, 50);
    cout<<"fecha de realizacion: ";
    cin>>aux->fechaestreno;
    cin.ignore();
    cout<<"Genero: ";
    cin.getline(aux->genero, 30);
    cout<<"Recaudacion en millones: ";
    cin>>aux->recaudacion;

    if(raiz == NULL){
        raiz = aux;
    }else{
        posicionarNodo(raiz);
    }
}

void inorden(struct Pelicula* nodo){
    if(nodo != NULL){
        inorden(nodo->izq);
        cout<<nodo->nombre<<" ("<<nodo->fechaestreno<< ") - " <<nodo->genero<< " - $"<< nodo->recaudacion << "M\n";
        inorden(nodo->der);
    }
}

void preorden(struct Pelicula* nodo){
    if(nodo != NULL){
        cout<<nodo->nombre<<" (" << nodo->fechaestreno << ") - "<<nodo->genero<< " - $"<<nodo->recaudacion<<"M\n";
        preorden(nodo->izq);
        preorden(nodo->der);
    }
}

void posorden(struct Pelicula* nodo){
    if(nodo != NULL){
        posorden(nodo->izq);
        posorden(nodo->der);
        cout<<nodo->nombre<<" (" <<nodo->fechaestreno <<") - "<<nodo->genero<< " - $"<< nodo->recaudacion<< "M\n";
    }
}

void buscarNombre(struct Pelicula* nodo, const char* nombre) {
    if(nodo != NULL){
        if(strcmp(nodo->nombre, nombre) == 0){
            cout<<"Nombre: "<< nodo->nombre<<"\nfechaestreno: "<<nodo->fechaestreno<< "\nGenero: "<<nodo->genero<< "\nRecaudacion: $"<<nodo->recaudacion<<"M\n";
        }
        buscarNombre(nodo->izq, nombre);
        buscarNombre(nodo->der, nombre);
    }
}

void MostrarGenero(struct Pelicula* nodo, const char* genero){
    if(nodo != NULL){
        if(strcmp(nodo->genero, genero) == 0){
            cout<<nodo->nombre<<" (" <<nodo->fechaestreno<< ") - $"<< nodo->recaudacion<<"M\n";
        }
        MostrarGenero(nodo->izq, genero);
        MostrarGenero(nodo->der, genero);
    }
}

int recolectar(struct Pelicula* nodo, struct Pelicula* lista[], int i){
    if(nodo != NULL){
        i = recolectar(nodo->izq, lista, i);
        lista[i++] = nodo;
        i = recolectar(nodo->der, lista, i);
    }
    return i;
}

void mostrarFracasos(struct Pelicula* raiz){
    struct Pelicula* lista[100];
    int n = recolectar(raiz, lista, 0);

    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++) {
            if (lista[j]->recaudacion > lista[j+1]->recaudacion){
                struct Pelicula* temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    cout<<"3 Fracasos taquilleros:\n";
    for(int i = 0; i < n && i < 3; i++){
        cout << lista[i]->nombre << " - $" << lista[i]->recaudacion << "M\n";
    }
}

void buscarPeliculaEliminar(struct Pelicula* nodo, const char* nombre) {
    if(nodo != NULL){
        if (strcmp(nodo->nombre, nombre) == 0) {
            aux2 = nodo;
        }
        buscarPeliculaEliminar(nodo->izq, nombre);
        buscarPeliculaEliminar(nodo->der, nombre);
    }
}

void ubicarPadre(struct Pelicula* a){
    if(a == NULL) return;

    if ((a->izq == aux2) || (a->der == aux2)) {
        padre = a;
    } else {
        if (a->izq != NULL) {
            ubicarPadre(a->izq);
        }
        if (a->der != NULL) {
            ubicarPadre(a->der);
        }
    }
}

void eliminar(){
    char nombreEliminar[50];
    cout<<"Nombre de la pelicula a eliminar: ";
    cin.ignore();
    cin.getline(nombreEliminar, 50);

    aux2 = NULL;
    padre = NULL;
    buscarPeliculaEliminar(raiz, nombreEliminar);

    if (aux2 != NULL) {
        struct Pelicula* subIzq = aux2->izq;
        struct Pelicula* subDer = aux2->der;

        if (aux2 != raiz) {
            ubicarPadre(raiz);
            if (padre != NULL) {
                if (padre->izq == aux2) {
                    padre->izq = NULL;
                } else if (padre->der == aux2) {
                    padre->der = NULL;
                }
            }
        } else {
            raiz = NULL; 
        }

        free(aux2);
        aux2 = NULL;

        cout<<"Pelicula eliminada exitosamente.\n";

        if (subIzq != NULL) {
            aux = subIzq;
            if (raiz == NULL) raiz = subIzq;
            else posicionarNodo(raiz);
        }
        if (subDer != NULL) {
            aux = subDer;
            if (raiz == NULL) raiz = subDer;
            else posicionarNodo(raiz);
        }

    } else {
        cout<<"No se encontró la pelicula para eliminar\n";
    }
}


int main() {
    int opcion;
    char nombreBuscar[50];
    char generoBuscar[30];

    do {
        cout <<"\n--- MENU ---\n";
        cout <<"1. Agregar pelicula"<<endl;
        cout <<"2. Mostrar inorden"<<endl;
        cout <<"3. Mostrar preorden"<<endl;
        cout <<"4. Mostrar posorden"<<endl;
        cout <<"5. Buscar por nombre"<<endl;
        cout <<"6. Mostrar por genero"<<endl;
        cout <<"7. Mostrar 3 fracasos taquilleros"<<endl;
        cout <<"8. Salir"<<endl;
        cout <<"9. Eliminar pelicula por nombre"<<endl;
        cout <<"Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarPelicula();
                break;
            case 2:
                cout <<"Recorrido Inorden:\n";
                inorden(raiz);
                break;
            case 3:
                cout << "Recorrido Preorden:\n";
                preorden(raiz);
                break;
            case 4:
                cout <<"Recorrido Posorden:\n";
                posorden(raiz);
                break;
            case 5:
                cout <<"Nombre a buscar: ";
                cin.ignore();
                cin.getline(nombreBuscar, 50);
                buscarNombre(raiz,nombreBuscar);
                break;
            case 6:
                cout <<"Genero a mostrar: ";
                cin.ignore();
                cin.getline(generoBuscar, 30);
                MostrarGenero(raiz,generoBuscar);
                break;
            case 7:
                mostrarFracasos(raiz);
                break;
            case 8:
                cout <<"Saliendo...\n";
                break;
            case 9:
                eliminar();
                break;
            default:
                cout <<"Opcion inválida.\n";
        }

    } while (opcion != 8);

    return 0;
}
