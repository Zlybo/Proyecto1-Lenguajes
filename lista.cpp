#include "lista.h"

using namespace std;

Usuario::Usuario(string username, string password) {
    this->username = username;
    this->password = password;
}

Usuario::~Usuario() {
}

Usuario *Usuario::getSiguienteUsuario() {
    return this->siguiente;
}

string Usuario::getUsuario() {
    return this->username;
}

string Usuario::getPwd() {
    return this->password;
}