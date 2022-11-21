#include <iostream>
using namespace std;
class Venta{
private:
	int 	codigo;
	int 	serie;
	string 	fecha;
	int 	codCliente;
	int 	codVendedor;
	float 	precioTotal;
public:
	Venta(){}
	//Venta
	Venta(int codigo, int codCliente, string fecha, int serie, int codVendedor, float precioTotal)
	{
		this->codigo = codigo;
		this->codCliente = codCliente;
		this->fecha = fecha;
		this->serie  = serie;
		this->codVendedor  = codVendedor;
		this->precioTotal = precioTotal;
	}
	//Set
	void setCodigo(int codigo)
	{
		this->codigo = codigo;
	}
	void setSerie(int serie)
	{
		this->serie = serie;
	}
	void setFecha(string fecha)
	{
		this->fecha = fecha;
	}
	void setCodCliente(int codCliente)
	{
		this->codCliente = codCliente;
	}
	void setCodVendedor(int codVendedor)
	{
		this->codVendedor = codVendedor;
	}
	void setPrecioTotal(float precioTotal)
	{
		this->precioTotal = precioTotal;
	}
	//Get
	int getCodigo()
	{
		return codigo;
	}
	int getSerie()
	{
		return serie;
	}
	string getFecha()
	{
		return fecha;
	}
	int getCodCliente()
	{
		return codCliente;
	}
	int getCodVendedor()
	{
		return codVendedor;
	}
	float getPrecioTotal()
	{
		return precioTotal;
	}
};
