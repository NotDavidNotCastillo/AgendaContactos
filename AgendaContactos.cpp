#include <iostream>
using namespace std;

class Contacto{
	int telefono;
	string contacto;
	string correo;
	
	public:
		string getContacto(){
		return contacto;
		}
		int getTelefono(){
		return telefono;
		}
		string getCorreo(){
		return correo;
		}
};

int main(){
	return 0;
}
