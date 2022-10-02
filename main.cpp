#include <iostream>
#include <fstream>
#include "lista.h"
#include <vector>

using namespace std;

// Enlaza todos los usuarios que hayan en el txt
Usuario *enlazarTxt() {
    ifstream archivo("usuarios.txt");
    string usuario;
    string password;
    getline(archivo, usuario);
    getline(archivo, password);

    Usuario *head = new Usuario(usuario, password);
    head->siguiente = NULL;

    Usuario *tail = head;
    while (getline(archivo, usuario) && getline(archivo, password)) {
        Usuario *node = new Usuario(usuario, password);
        node->siguiente = NULL;

        tail->siguiente = node;
        tail = node;
    }
    archivo.close();
    return head;
}

// Agrega un nuevo usuario al final de la lista y al final del archivo .txt
void agregarUsuario(Usuario *head, string usuario, string password) {
    // Agregar a la lista
    Usuario *nuevoUsuario = new Usuario(usuario, password);
    nuevoUsuario->siguiente = NULL;
    while (head->getSiguienteUsuario() != NULL) {
        head = head->getSiguienteUsuario();
    }
    head->siguiente = nuevoUsuario;

    // Agregar al txt
    fstream archivo;
    archivo.open("usuarios.txt", ios_base::app); // el segundo aparametro hace que se agreguen al final
    archivo << endl;
    archivo.write(usuario.data(), usuario.size()) << endl << password.data(), usuario.size();
    archivo.close();
    cout << "Usuario añadido"<<endl;
}

void buscarUsuario(Usuario *head, string usuarioEcontrar, string passwordEncontrar) {
    while (head != NULL) {
        string usuario = head->getUsuario();
        string password = head->getPwd();
        if (usuarioEcontrar == usuario && passwordEncontrar == password) {
            cout << "Bienvenido" << endl;
            break;
        }
        head = head->getSiguienteUsuario();
    }
    // Terminó de revisar y no encontro coincidencia
    if (head == NULL) {
        cout << "No se encontro ese usuario" << endl;
    }
}

void eliminarUnaLineaTxt(int line_number) {
    fstream leer;
    leer.open("usuarios.txt");
    // Se crea un vector exactamente igual a la lista del txt
    vector<string> lines;
    string linea;
    while (getline(leer, linea))
        lines.push_back(linea);
    leer.close();
    //--------------------------------------------------------
    ofstream escribir;
    escribir.open("usuarios.txt");
    // Se le resta 1 por que se esta trabajando con vectores
    line_number--;

    // Escribimos todas las lineas guardadas en el vector hacia el archivo MENOS la que queremos eliminar
    for (int i = 0; i < lines.size(); i++)
        if (i != line_number)
            escribir << lines[i] << endl;
    escribir.close();
}

void eliminarUsuario(Usuario *nodoActual, string usuarioEcontrar, string passwordEncontrar) {

    // Eliminar usuario de la lista
    Usuario *anterior;
    while (nodoActual != NULL) {
        string usuario = nodoActual->getUsuario();
        string password = nodoActual->getPwd();
        if (usuarioEcontrar == usuario && passwordEncontrar == password) {
            anterior->siguiente = nodoActual->siguiente; // Enlaza el nodo anterior con el siguiente nodo
            nodoActual->siguiente = NULL; // Elimina el enlace entre nodo actual y el siguiente nodo
            cout << "usuario eliminado" << endl;
            break;
        }
        anterior = nodoActual;
        nodoActual = nodoActual->getSiguienteUsuario();
    }
    // Terminó de revisar y no encontro coincidencia
    if (nodoActual == NULL) {
        cout << "No se encontro ese usuario" << endl;
    }

    // Eliminar usuario del archivo .txt
    fstream archivo;
    int x = 0;
    string linea;
    archivo.open("usuarios.txt");
    while (getline(archivo, linea)) {
        if (linea == usuarioEcontrar) {
            eliminarUnaLineaTxt(x + 1);
            eliminarUnaLineaTxt(x + 1);
        }
        x++;
    }
}


void mostrarLista(Usuario *head) {
    while (head != NULL) {
        cout << head->getUsuario() << " ->Usuario" << endl;
        head = head->getSiguienteUsuario();
    }
}

int main() {
    string usuario;
    string password;
    Usuario *head = enlazarTxt();
    int eleccion;
    while (true){
        cout << "(1) Ingresar un nuevo usuario, digite primero usuario y luego contrasena" << endl;
        cout << "(2) Buscar un usuario existente, digite primero usuario y luego contrasena" << endl;
        cout << "(3) Eliminar un usuario existente, digite primero usuario y luego contrasena" << endl;
        cout << "(4) Mostrar lista" << endl;
        cout << "(5) Salir del menu" <<endl;
        cin >> eleccion;
        if (eleccion == 1){
            cin >> usuario;
            cin >> password;
            agregarUsuario(head,usuario,password);
        }
        else if (eleccion == 2){
            cin >> usuario;
            cin >> password;
            buscarUsuario(head, usuario, password);
        }
        else if (eleccion == 3){
            cin >> usuario;
            cin >> password;
            eliminarUsuario(head, usuario, password);
        }
        else if (eleccion == 4){
            mostrarLista(head);
        }
        else if (eleccion == 5){
            break;
        }
        else{
            cout << "digite alguna de las opciones anteriores"<<endl;
        }
    }
    eliminarUsuario(head, "username3", "pwd3");
    buscarUsuario(head, "username3", "pwd3");
    mostrarLista(head);


}