#include<iostream>
#include<vector>
#include<fstream>
#include <cstdlib>
#include<string>
#include<cstring>
#include"../model/producto.h"
#include "categoriaController.h"
#pragma once
using std::stoi;
using std::stof;
using namespace std;
void menuProducto();
void grabarProducto();
void listarProducto();
void buscarProducto();
void modificarProducto();
void eliminarProducto();

class ProductoController
{
private:
	vector<Producto> vectorProducto;
public:
	ProductoController()
	{
		cargarDatosArchivo();
	}
	
	void add(Producto objeto)
	{
		vectorProducto.push_back(objeto);
	}
	
	Producto get(int posicion)
	{
		return vectorProducto[posicion];
	}
	//obtener el tamano del arreglo
	int size()
	{
		return vectorProducto.size();
	}	
	//Correlativo del numero
	int getCorrelativo()
	{
		if(vectorProducto.size() == 0)
		{
			return 1;
		}
		else
		{
			return vectorProducto[size() - 1].getCodigo() + 1; 	
		}		
	}
	
	Producto getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int mitad;
		Producto objError;
		objError.setDescripcion("Error");
		mitad=(inferior + superior)/2;
		while(inferior<=superior)
		{
			if (vectorProducto[mitad].getCodigo() == codigo)
			{
				return vectorProducto[mitad];
			}
			if (vectorProducto[mitad].getCodigo() > codigo)
			{
				superior = mitad - 1;
			}
			if (vectorProducto[mitad].getCodigo() < codigo)
			{
				inferior = mitad + 1;
			}
			mitad = (inferior + superior)/2;
		}
		return objError;
	}
	
	bool modificar(Producto obj,string nom,string des,float precio,int stk,int codCat)
	{
		for(int i=0;i<vectorProducto.size();i++)
		{
			if(obj.getCodigo() == vectorProducto[i].getCodigo())	
			{
				vectorProducto[i].setNombre(nom);
				vectorProducto[i].setDescripcion(des);
				vectorProducto[i].setPrecio(precio);
				vectorProducto[i].setStock(stk);
				vectorProducto[i].setCategoria(codCat);
				return true;
			}
		}
		return false;
	}
	
	int getPostArray(Producto obj)
	{
		for(int i=0;i<vectorProducto.size();i++)
		{
			if(obj.getCodigo() == vectorProducto[i].getCodigo())	
			{
				return i;
			}
		}		
		return -1;
	}
	void remove(Producto obj)
	{
		vectorProducto.erase(vectorProducto.begin() + getPostArray(obj));
	}
	
	//Grabar los datos en el archivo 
	void grabarEnArchivo(Producto producto)
	{
		try
		{
			fstream archivoProducto;
			archivoProducto.open("producto.csv", ios::app);
			if(archivoProducto.is_open())
			{
				archivoProducto<<producto.getCodigo()<<";"
					<<producto.getNomPro()<<";"
					<<producto.getDesPro()<<";"
					<<producto.getPrePro()<<";"
					<<producto.getStkPro()<<";"
					<<producto.getCodCat()<<";"<<endl;
				archivoProducto.close();
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
	//Grabar las modificaciones
	void grabarModificarEliminarArchivo()
	{
		try
		{
			fstream archivoProducto;
			archivoProducto.open("producto.csv",ios::out);
			if(archivoProducto.is_open())
			{
				for(Producto x:vectorProducto)
				{
					archivoProducto<<x.getCodigo()<<";"<<x.getNomPro()<<";"<<x.getDesPro()<<";"<<x.getPrePro()<<";"<<x.getStkPro()<<";"<<x.getCodCat()<<";"<<endl;
				}
				archivoProducto.close();					
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}		
	}
	//Cargar datos del archivo
	void cargarDatosArchivo()
	{
		try
		{
			int 	i;
			size_t 	posi;
			string 	linea;
			string 	temporal[6];
			fstream	archivoProducto;
			archivoProducto.open("producto.csv",ios::in);
			if(archivoProducto.is_open())
			{
				while(!archivoProducto.eof() && getline(archivoProducto,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Producto objProducto(std::stoi(temporal[0]),temporal[1],temporal[2],std::stof(temporal[3]),std::stoi(temporal[4]),std::stoi(temporal[5]));
					
					add(objProducto);
				}
			}
			
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
};

ProductoController* proController = new ProductoController();
void menuProducto()
{
	int opt;	
	system("title Menu Producto");
	system("color 7d");
	do
	{
		cout<<"\n\n\t\t\t\t\t\t --------------\n";
		cout<<"\t\t\t\t\t\t| MENU PRODUCTO | \n";
		cout<<"\t\t\t\t\t\t ---------------\n\n\n\n";
		cout<<"\t\t\t\t\tRegistrar nuevo...........[1]\n\n";
		cout<<"\t\t\t\t\tListar....................[2]\n\n";
		cout<<"\t\t\t\t\tBuscar....................[3]\n\n";
		cout<<"\t\t\t\t\tModificar.................[4]\n\n";
		cout<<"\t\t\t\t\tEliminar..................[5]\n\n";
		cout<<"\t\t\t\t\tSalir.....................[6]\n\n\n";
		cout<<"\t\t\t\t\tIngrese una opcion: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");grabarProducto();break;
		case 2:system("cls");listarProducto();break;
		case 3:system("cls");buscarProducto();break;
		case 4:system("cls");modificarProducto();break;
		case 5:system("cls");eliminarProducto();break;
		case 6:system("cls");cout<<"\n\n\n\n\n\n\t\t\t\t\tSALISTE DEL MENU PRODUCTO\n\n\n\n";break;
		default:cout<<"Ingrese una opción correcta[1-6]";
		}
	} while(opt!=6);
	cout<<"\t\t\t\t\t";
	system("pause");
	system("cls");
}

void grabarProducto()
{
	int codP;
	string nomP, desP;
	float preP;
	int stkP;
	int codC;
	string  flag;
	system("title Registrar Producto");
	system("color 7d");
	do
	{
		cout<<"\n\n\t\t\t\t Registrar nuevo producto \n";
		cout<<"\t\t\t\t ------------------------\n\n";
		codP = proController->getCorrelativo();
		cout<<"\t\t\tCodigo del producto: "<<codP<<"\n\n";
		cin.ignore();
		cout<<"\t\t\tNombre: ";
		getline(cin,nomP);
		cout<<"\n\t\t\tDescripcion: ";
		getline(cin,desP);
		cout<<"\n\t\t\tPrecio: S/.";
		cin>>preP;
		
		cout<<"\n\t\t\tStock: ";
		cin>>stkP;
		
		cout<<"\n\t\t\tCodigo de Categoria:\n";
		cout<<"\n\t\t\t***Lista de Categorias***\n";
		for(int i = 0;i<catController->size();i++)
		{
			cout<<"\t\t\t["<<catController->get(i).getCodigo()<<"]"<<"\t"
				<<catController->get(i).getNomCat()<<"\n";
		}
		cout<<"\n\t\t\tSelecciona una categoria: ";
		cin>>codC;
		cin.ignore();
		Producto producto(codP,nomP,desP,preP,stkP,codC);	
		proController->add(producto);
		
		proController->grabarEnArchivo(producto);
		cout<<"\n\t\t\tRegistrar otro Producto(S/s): ";
		cin>>flag;
		
		system("cls");
	} 
	while(flag == "S" || flag == "s");
	system("cls");
}	

void listarProducto()
{
	system("title Listar Productos");
	system("color 7d");
	cout<<"\n\n\t\t Lista de todos los productos \n";
	cout<<"\t\t ----------------------------\n\n";
	for(int i=0;i<proController->size();i++)
	{
		cout<<"\n\t"<<proController->get(i).getCodigo()<<"\t"
			<<proController->get(i).getNomPro()<<"\t"
			<<proController->get(i).getDesPro()<<"\tS/."
			<<proController->get(i).getPrePro()<<"\t"
			<<proController->get(i).getStkPro()<<"\t"
			<<proController->get(i).getCodCat()<<"\n";
	}
	cout<<"\n\n\n\t";
	system("pause");
	system("cls");	
}

void buscarProducto()
{
	system("title Buscar Productos");
	system("color 7d");
	int codPro, inferior, superior;
	inferior = 0;
	superior = proController->size();
	cout<<"\n\n\t\t\tBuscar Producto \n";
	cout<<"\t\t\t---------------\n\n\n";
	cout<<"\t\tIngresar codigo del producto a buscar: ";
	cin>>codPro;
	Producto proObj = proController->getBuscarPorCodigo(codPro,inferior,superior);
	if(proObj.getDesPro() !="Error")
	{
		cout<<"\n\t\t\t**Registro encontrado**\n\n";
		cout<<"\t\tCodigo: "<<proObj.getCodigo()<<"\n\n";
		cout<<"\t\tNombre: "<<proObj.getNomPro()<<"\n\n";
		cout<<"\t\tDescripcion: "<<proObj.getDesPro()<<"\n\n";
		cout<<"\t\tPrecio: S/."<<proObj.getPrePro()<<"\n\n";
		cout<<"\t\tStock: "<<proObj.getStkPro()<<"\n\n";
		cout<<"\t\tCodigo de Categoria: "<<proObj.getCodCat()<<"\n\n";
	}
	else
	{
		cout<<"\n\t\tNo se encontro el registro!\n";
		cout<<"\n\n\n\t\t";
		system("pause");
		menuProducto();
	}
	cout<<"\n\n\n\t\t";
	system("pause");
	system("cls");
}

void modificarProducto()
{
	system("title Modificar Productos");
	system("color 7d");
	int codPro;
	int inferior = 0;
	int superior = proController->size();
	cout<<"\n\n\t\t\tModificar Producto \n";
	cout<<"\t\t\t------------------\n\n\n";
	cout<<"\t\tIngresar el codigo a modificar: ";
	cin>>codPro;
	Producto proObj = proController->getBuscarPorCodigo(codPro,inferior,superior);
	if(proObj.getDesPro() != "Error")
	{	
		/*Buscar objeto a modificar*/
		cout<<"\n\t\t\t**Registro Encontrado**\n\n";
		cout<<"\t\tCodigo: "<<proObj.getCodigo()<<"\n\n";
		cout<<"\t\tNombre: "<<proObj.getNomPro()<<"\n\n";
		cout<<"\t\tDescripcion: "<<proObj.getDesPro()<<"\n\n";
		cout<<"\t\tPrecio: S/."<<proObj.getPrePro()<<"\n\n";
		cout<<"\t\tStock: "<<proObj.getStkPro()<<"\n\n";
		cout<<"\t\tCodigo de categoria: "<<proObj.getCodCat()<<"\n\n";
		cin.ignore();	
		/*Fin del objeto a modificar*/
		string nomP,desP;
		float 	preP;
		int	   stkP, codCP;
		cout<<"\n\t\t\t**Modificando Campos**\n\n";
		cout<<"\t\tModificando el Nombre...: ";
		getline(cin,nomP);
		cout<<"\t\tModificando Descripcion...: ";
		getline(cin,desP);
		cout<<"\n\t\tModificando el Precio...: S/.";
		cin>>preP;
		cout<<"\n\t\tModificando Stock...: ";
		cin>>stkP;
		cout<<"\n\t\tModificando Codigo de Categoria...: ";
		cout<<"\n\n\t\t\t***Lista de Categorias***\n";
		for(int i = 0;i<catController->size();i++)
		{
			cout<<"\t\t\t["<<catController->get(i).getCodigo()<<"]"<<"\t"
				<<catController->get(i).getNomCat()<<"\n";
		}
		cout<<"\n\t\t\tSeleccione una categoria: ";
		cin>>codCP;
		bool estado = proController->modificar(proObj,nomP,desP,preP,stkP,codCP);
		if(estado = true)
		{
			cout<<"\n\n\t\tREGISTRO MODIFICADO SATISFACTORIAMENTE!!!\n";
			//Grabar en archivo
			proController->grabarModificarEliminarArchivo();
		}
		else
		{
			cout<<"\n\n\t\tNO SE ENCONTRO EL REGISTRO A MODIFICAR!\n";
			cout<<"\n\n\t\t";
			system("pause");
			menuProducto();		
		}
	}
	else
	{
		cout<<"\n\n\t\tNO SE ENCONTRO EL REGISTRO!\n";		
	}
	cout<<"\n\n\n\t\t";
	system("pause");
	system("cls");	
}
void eliminarProducto()
{
	system("title Eliminar Productos");
	system("color 7d");
	int cod;
	int inferior = 0;
	int superior = proController->size();
	cout<<"\n\n\t\t\tEliminar Producto \n";
	cout<<"\t\t\t-----------------\n\n\n";
	cout<<"\t\tIngresar el codigo a eliminar: ";
	cin>>cod;
	Producto objEliminar = proController->getBuscarPorCodigo(cod,inferior,superior);
	if(objEliminar.getDesPro() !="Error")
	{
		proController->remove(objEliminar);
		cout<<"\n\n\t\tREGISTRO ELIMINADO SATISFACTORIAMENTE!!!";
		/*Grabar en archivo*/
		proController->grabarModificarEliminarArchivo();
	}
	else
	{
		cout<<"\n\t\tNO SE ENCONTRO EL REGISTRO!!\n";
	}
	cout<<"\n\n\n\t\t";
	system("pause");
	system("cls");
}



