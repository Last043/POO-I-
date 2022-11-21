#include <iostream>
using namespace std;
class DetalleVenta{
private:
	int 	codigo;
	string 	hora;
	int 	codProducto;
	int 	cantidad;
	float 	precioProducto;
	float 	subTotal;
public:
	DetalleVenta(){}
	//Detalle venta
	DetalleVenta(int codigo, string hora, int codProducto, int cantidad, float precioProducto, float subTotal)
	{
		this->codigo = codigo;
		this->hora = hora;
		this->codProducto = codProducto;
		this->cantidad = cantidad;
		this->precioProducto = precioProducto;
		this->subTotal = subTotal;
	}
	//Set
	void setCodigo(int codigo)
	{
		this->codigo = codigo;
	}
	void setHora(string hora)
	{
		this->hora = hora;
	}
	void setCodProducto(int codProducto)
	{
		this->codProducto = codProducto;
	}
	void setCantidad(int cantidad)
	{
		this->cantidad = cantidad;
	}
	void setPrecioProducto(float precioProducto)
	{
		this->precioProducto = precioProducto;
	}
	void setSubTotal(float subTotal)
	{
		this->subTotal =subTotal;
	}
	//Get
	int getCodigo()
	{
		return codigo;
	}
	string getHora()
	{
		return hora;
	}
	int getCodProducto()
	{
		return codProducto;
	}
	int getCantidad()
	{
		return cantidad;
	}
	float getPrecioProducto()
	{
		return precioProducto;
	}
	float getSubTotal()
	{
		return subTotal;
	}
};
