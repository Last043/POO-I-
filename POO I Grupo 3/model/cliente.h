#include <iostream>
using namespace std;
class Cliente{
private:
	int 	codigo;
	string 	nombre;
	string 	fecha;
	int 	dni;
	int 	edad;
public:
	Cliente(){}
	Cliente(int codigo,string nombre,string fecha, int dni, int edad)
	{
		this->codigo = codigo;
		this->nombre = nombre;
		this->fecha = fecha;
		this->dni  = dni;
		this->edad = edad;
	}
	//Set
	void setCodigo(int codigo)
	{
		this->codigo = codigo;
	}
	void setNombre(string nombre)
	{
		this->nombre = nombre;
	}
	void setFecha(string fecha)
	{
		this->fecha = fecha;
	}
	void setDni(int dni)
	{
		this->dni = dni;
	}
	void setEdad(int edad)
	{
		this->edad =edad;
	}
	//Get
	int getCodigo()
	{
		return codigo;
	}
	string getNombre()
	{
		return nombre;
	}
	string getFecha()
	{
		return fecha;
	}
	int getDni()
	{
		return dni;
	}
	int getEdad()
	{
		return edad;
	}
};
