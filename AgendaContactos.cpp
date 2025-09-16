#include <iostream>
#include <string>

using namespace std;

// Nodo de Contactos
struct Nodo {
    string nombre, telefono, correo;
    Nodo* siguiente;
};

// Metodo para validar telefono
bool validarTelefono(const string& tel) {

    // mínimo 8 caracteres para aceptar el numero
    if (tel.size() < 8) 
        return false;          

    // verificar que todos sean digitos
    for (char c : tel) {
        if (!isdigit(c)) 
            return false;         
    }
    return true;
}

//Validacion de correos
bool validarCorreo(const string& correo) {
    // Nos aseguramos que el correo contiene un @
    return (correo.find('@') != string :: npos);
}

// Metodo para agregar nuestros contactos
void agregarContacto(Nodo*& cabeza) {
    string nom, tel, cor;

    cout << "\nIngrese el nombre del contacto: ";
    getline(cin, nom);
    while (nom.empty()) {
        cout << "El nombre no puede estar vacio.\nIntente de nuevo\n";
        getline(cin, nom);
    }

    cout << "Ingrese el telefono del contacto en formato XXXXXXXX: ";
    getline(cin, tel);
    while (!validarTelefono(tel)) {
        cout << "Error.\nEl numero solo debe tener digitos y como minimo 8.\n" 
             << "Ingrese el telefono del contacto en formato XXXXXXXX: ";
        getline(cin, tel);
    }

    cout << "Ingrese el correo del contacto (debe contener @): ";
    getline(cin, cor);
    while (!validarCorreo(cor)) {
        cout << "El correo debe contener una @. Intente de nuevo: ";
        getline(cin, cor);
    }

    // Creamos un nuevo nodo para agregarlo
    Nodo* nuevo = new Nodo;
    nuevo->nombre = nom;
    nuevo->telefono = tel;
    nuevo->correo = cor;
    nuevo->siguiente = nullptr;

    // Agregando nodo a la lista
    if (!cabeza) {
        // si la lista esta vacia, cabeza sera el nuevo nodo
        cabeza = nuevo;
    } else {
        Nodo* actual = cabeza;

        // Recorremos la lista hasta el ultimo nodo
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        // añadimos el nodo al final
        actual->siguiente = nuevo;
    }

    cout << "\nContacto agregado correctamente.\n";
}

// Mostramos 
void mostrarContactos(const Nodo* cabeza) {
    // Verifamos que no este vacio
    if (!cabeza) {
        cout << "La agenda está vacía.\n";
        return;
    }

    cout << "\n--- LISTA DE CONTACTOS ---\n";

    // recorremos todo el nodo para imprimir los contactos
    while (cabeza) {
        cout << "Nombre: " << cabeza->nombre << endl;
        cout << "Teléfono: " << cabeza->telefono << endl;
        cout << "Correo: " << cabeza->correo << endl;
        cout << "-------------------------\n";
        // Pasamos al siguiente elemento de nuestro nodo (cabeza)
        cabeza = cabeza->siguiente;
    }
}

// Buscador de contactos
void buscarContacto(const Nodo* cabeza) {
    // Verificamos si la lista esta vacia
    if (!cabeza) {
        cout << "La agenda está vacía.\n";
        return;
    }

    string nombre;
    cout << "Ingrese el nombre a buscar: ";
    getline(cin, nombre);

    while (cabeza) {
        if (cabeza->nombre == nombre) {
            cout << "\nContacto encontrado:\n";
            cout << "Nombre: " << cabeza->nombre << endl;
            cout << "Teléfono: " << cabeza->telefono << endl;
            cout << "Correo: " << cabeza->correo << endl;
            return;
        }
        // Recorremos el nodo uno por uno
        cabeza = cabeza->siguiente;
    }
    cout << "No se encontró un contacto con ese nombre.\n";
}

// Eliminador de contactos
void eliminarContacto(Nodo*& cabeza) {
    // Verificamos si la cabeza (lista de nodos) esta vacia
    if (!cabeza) {
        cout << "La agenda está vacía.\n";
        return;
    }

    string nombre;
    cout << "Ingrese el nombre a eliminar: ";
    getline(cin, nombre);

    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

    // Recorremos la lista
    while (actual && actual->nombre != nombre) {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Si actual es nullptr entonces salimos del metodo
    if (!actual) {
        cout << "No se encontró un contacto con ese nombre.\n";
        return;
    }

    // Si anterior es un nullptr, el nodo que eliminamos sera la cabeza
    if (!anterior) {
        // cabeza ahora sera un nullptr
        // o lo que es lo mismo actual->siguiente 
        cabeza = actual->siguiente; 

    } else {
        // conectamos el nodo anterior a actual con el 
        // siguiente nodo (actual -> siguiente)
        anterior->siguiente = actual->siguiente;
    }

    // Eliminamos la direccion en memoria de actual
    delete actual;
    cout << "Contacto eliminado correctamente.\n";
}

// Borramos los nodos creados
void liberarMemoria(Nodo*& cabeza) {
    while (cabeza) {
        Nodo* temp = cabeza;
        // Pasamos a la siguiente posicion del nodo por eliminar sin problemas
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void menu(Nodo*& contactos){
    int opc;

    do{
        cout << "\n===== MENÚ AGENDA DE CONTACTOS =====\n";
        cout << "1. Agregar contacto\n";
        cout << "2. Mostrar contactos\n";
        cout << "3. Buscar contacto\n";
        cout << "4. Eliminar contacto\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opc;
        cin.ignore();

        switch(opc) {
            case 1: 
                agregarContacto(contactos); 
                break;
            case 2: 
                mostrarContactos(contactos); 
                break;
            case 3: 
                buscarContacto(contactos); 
                break;
            case 4:  
                eliminarContacto(contactos); 
                break;
            case 5: 
                cout << "Saliendo...\n"; 
                break;
            default:    
                cout << "Opción inválida.\n";
                break;
        }
    }while(opc != 5);

    liberarMemoria(contactos);
}

int main (){
    Nodo* contactos = nullptr;
    menu(contactos);
    return 0;
}   