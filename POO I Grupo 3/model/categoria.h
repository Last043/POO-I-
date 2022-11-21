#include <iostream>
#pragma once
using namespace std;
class Categoria
{
private:
	int codCat;
	string nomCat;
public:
	Categoria(int codCat, string nomCat)
	{
		this->codCat=codCat;
		this->nomCat=nomCat;
	}
	//Set
	void setCodigo(int codCat)
	{
		this->codCat = codCat;
	}
	void setNombre(string nomCat)
	{
		this->nomCat = nomCat;
	}
	//Get
	int getCodigo()
	{
		return this->codCat;
	}
	string getNomCat()
	{
		return this->nomCat;
	}
};
