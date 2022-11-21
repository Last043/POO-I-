#include <iostream>
using namespace std;
class Registro{
private:
	int 	codigo;
	string 	usuario;
	string 	contrasena;
	int 	dni;
public:
	Registro(){}
	Registro(int codigo,string usuario,string contrasena, int dni)
	{
		this->codigo = codigo;
		this->usuario = usuario;
		this->contrasena = contrasena;
		this->dni 	 = dni;
	}
	int getCodigo()
	{
		return codigo;
	}
	string getUsuario()
	{
		return usuario;
	}
	string getContrasena()
	{
		return contrasena;
	}
	int getDni()
	{
		return dni;
	}
};


