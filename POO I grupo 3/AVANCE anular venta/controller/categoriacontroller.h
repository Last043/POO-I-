#include<iostream>
#include<vector>
#include<fstream>
#include <cstdlib>
#include<string>
#include<cstring>
#include"../model/categoria.h"
#pragma once
using std::stoi;
using namespace std;
void menuCategoria();
void grabarCategoria();
void listarCategoria();

class CategoriaController
{
private:
	vector<Categoria> vectorCategoria;
public:
	CategoriaController()
	{
		cargarDatosArchivo();
	}
	
	void add(Categoria objeto)
	{
		vectorCategoria.push_back(objeto);
	}
	
	Categoria get(int posicion)
	{
		return vectorCategoria[posicion];
	}
	//obtener el tamano del arreglo
	int size()
	{
		return vectorCategoria.size();
	}	
	//Correlativo del numero
	int getCorrelativo()
	{
		if(vectorCategoria.size() == 0)
		{
			return 1;
		}
		else
		{
			return vectorCategoria[size() - 1].getCodigo() + 1; 	
		}		
	}
	
	//Grabar los datos en el archivo 
	void grabarEnArchivo(Categoria categoria)
	{
		try
		{
			fstream archivoCategoria;
			archivoCategoria.open("categoria.csv", ios::app);
			if(archivoCategoria.is_open())
			{
				archivoCategoria<<categoria.getCodigo()<<";"
					<<categoria.getNomCat()<<";"<<endl;
				archivoCategoria.close();
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
			string 	temporal[2];
			fstream	archivoCategoria;
			archivoCategoria.open("categoria.csv",ios::in);
			if(archivoCategoria.is_open())
			{
				while(!archivoCategoria.eof() && getline(archivoCategoria,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Categoria objCategoria(std::stoi(temporal[0]),temporal[1]);
					
					add(objCategoria);
				}
			}
			
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
};

CategoriaController* catController = new CategoriaController();
void menuCategoria()
{
	int opt;	
	system("title Menu Categoria");
	system("color 7d");
	do
	{
		cout<<"\n\n\t\t\t\t\t\t ---------------\n";
		cout<<"\t\t\t\t\t\t| MENU CATEGORIA | \n";
		cout<<"\t\t\t\t\t\t ----------------\n\n\n\n";
		cout<<"\t\t\t\t\tRegistrar nuevo...........[1]\n\n";
		cout<<"\t\t\t\t\tListar....................[2]\n\n";
		cout<<"\t\t\t\t\tSalir.....................[3]\n\n\n";
		cout<<"\t\t\t\t\tIngrese una opcion: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");grabarCategoria();break;
		case 2:system("cls");listarCategoria();break;
		case 3:system("cls");cout<<"\n\n\n\n\n\n\t\t\t\t\tSALISTE DEL MENU CATEGORIA\n\n\n\n";break;
		default:cout<<"Ingrese una opción correcta[1-3]";
		}
	} while(opt!=3);
	cout<<"\t\t\t\t\t";
	system("pause");
	system("cls");
}

void grabarCategoria()
{
	int codC;
	string nomC;
	string  flag;
	system("title Registrar Categoria");
	system("color 7d");
	do
	{
		cout<<"\n\n\t\t\t\t Registrar nueva categoria \n";
		cout<<"\t\t\t\t ------------------------\n\n";
		codC = catController->getCorrelativo();
		cout<<"\t\t\tCodigo de categoria: "<<codC<<"\n\n";
		cin.ignore();
		cout<<"\t\t\tNombre: ";
		getline(cin,nomC);
		
		Categoria categoria(codC,nomC);	
		catController->add(categoria);
		
		catController->grabarEnArchivo(categoria);
		cout<<"\n\t\t\tRegistrar otra categoria(S/s): ";
		cin>>flag;
		
		system("cls");
	} 
	while(flag == "S" || flag == "s");
	system("cls");
}	

void listarCategoria()
{
	system("title Listar Categorias");
	system("color 7d");
	cout<<"\n\n\t\t Lista de todas las Categorias \n";
	cout<<"\t\t -----------------------------\n\n";
	for(int i=0;i<catController->size();i++)
	{
		cout<<"\n\t"<<catController->get(i).getCodigo()<<"\t"
			<<catController->get(i).getNomCat()<<"\n";
	}
	cout<<"\n\n\n\t";
	system("pause");
	system("cls");	
}
