#include <string>

using namespace std;

class Usuario {
private:
    string username;
    string password; // no podia poner contraseña :/
public:
    Usuario *siguiente;

    Usuario(string, string);

    ~Usuario();

    Usuario *getSiguienteUsuario();

    string getUsuario();

    string getPwd();
};
