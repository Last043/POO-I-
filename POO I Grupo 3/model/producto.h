#include <iostream>

using namespace std;
class Producto
{
private:
	int codPro;
	string nomPro;
	string desPro;
	float prePro;
	int stkPro;
	int codCat;
public:
	Producto(){}
	Producto(int codPro, string nomPro, string desPro, float prePro, int stkPro, int codCat)
	{
		this->codPro=codPro;
		this->nomPro=nomPro;
		this->desPro=desPro;
		this->prePro=prePro;
		this->stkPro=stkPro;
		this->codCat=codCat;
	}
	//Set
	void setCodigo(int codPro)
	{
		this->codPro = codPro;
	}
	void setNombre(string nomPro)
	{
		this->nomPro = nomPro;
	}
	void setDescripcion(string desPro)
	{
		this->desPro = desPro;
	}
	void setPrecio(float prePro)
	{
		this->prePro = prePro;
	}
	void setStock(int stkPro)
	{
		this->stkPro = stkPro;
	}
	void setCategoria(int codCat)
	{
		this->codCat =codCat;
	}
	//Get
	int getCodigo()
	{
		return this->codPro;
	}
	string getNomPro()
	{
		return this->nomPro;
	}
	string getDesPro()
	{
		return this->desPro;
	}
	float getPrePro()
	{
		return this->prePro;
	}
	int getStkPro()
	{
		return this->stkPro;
	}
	int getCodCat()
	{
		return this->codCat;
	}
};
