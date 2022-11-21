#include <iostream>
#include<vector>
#include<fstream>
#include <cstdlib>
#include<String>
#include<cstring>
#include <ctime>
#include"../model/detalle.h"
#pragma once
using std::stoi;
using std::stof;
using namespace std;

class DetalleVentaController{
private:
	vector<DetalleVenta> vectorDetalleVenta;
public:
	DetalleVentaController()
	{
		vector<DetalleVenta> vectorDetalleVenta;
		cargarDatosDelArchivo();
	}
	
	void add(DetalleVenta obj)
	{
		vectorDetalleVenta.push_back(obj);
	}
	
	DetalleVenta get(int pos)
	{
		return vectorDetalleVenta[pos];		
	}
	
	int size()
	{
		return vectorDetalleVenta.size();
	}	
	
	int getCorrelativo()
	{
		if(vectorDetalleVenta.size() == 0)
		{
			return 1;
		}
		else
		{
			return vectorDetalleVenta[size() - 1].getCodigo() + 1; 	
		}		
	}
	
	DetalleVenta getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int mitad;
		DetalleVenta objError;
		objError.setHora("Error");
		mitad=(inferior + superior)/2;
		while(inferior<=superior)
		{
			if (vectorDetalleVenta[mitad].getCodigo() == codigo)
			{
				return vectorDetalleVenta[mitad];
			}
			if (vectorDetalleVenta[mitad].getCodigo() > codigo)
			{
				superior = mitad - 1;
			}
			if (vectorDetalleVenta[mitad].getCodigo() < codigo)
			{
				inferior = mitad + 1;
			}
			mitad = (inferior + superior)/2;
		}
		return objError;
	}
	
	int getPostArray(DetalleVenta obj)
	{
		for(int i=0;i<vectorDetalleVenta.size();i++)
		{
			if(obj.getCodigo() == vectorDetalleVenta[i].getCodigo())	
			{
				return i;
			}
		}		
		return -1;
	}
	void remove(DetalleVenta obj)
	{
		vectorDetalleVenta.erase(vectorDetalleVenta.begin() + getPostArray(obj));
	}
	
	//Grabar datos en el archivo
	void grabarEnArchivo(DetalleVenta detalleVenta)
	{
		try
		{
			fstream archivoDetalleVenta;
			archivoDetalleVenta.open("detalleVenta.csv",ios::app);
			if(archivoDetalleVenta.is_open()) 
			{
				archivoDetalleVenta<<detalleVenta.getCodigo()<<";"
					<<detalleVenta.getHora()<<";"
					<<detalleVenta.getCodProducto()<<";"
					<<detalleVenta.getCantidad()<<";"
					<<detalleVenta.getPrecioProducto()<<";"
					<<detalleVenta.getSubTotal()<<";"<<endl;
				archivoDetalleVenta.close();
			}
		}
		catch (exception e)
		{
			cout<<"Ocurrio un error al grabar en el archivo";
		}
	}
	
	//Grabar las modificaciones
	void grabarEliminarArchivo()
	{
		try
		{
			fstream archivoDetalleVenta;
			archivoDetalleVenta.open("detalleVenta.csv",ios::out);
			if(archivoDetalleVenta.is_open())
			{
				for(DetalleVenta x:vectorDetalleVenta)
				{
					archivoDetalleVenta<<x.getCodigo()<<";"<<x.getHora()<<";"<<x.getCodProducto()<<";"<<x.getCantidad()<<";"<<x.getPrecioProducto()<<";"<<x.getSubTotal()<<";"<<endl;
				}
				archivoDetalleVenta.close();					
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}		
	}
	
	void cargarDatosDelArchivo()
	{
		try
		{
			int 	i;
			size_t 	posi;
			string 	linea;
			string	temporal[6]; 
			fstream archivoDetalleVenta;
			archivoDetalleVenta.open("detalleVenta.csv",ios::in);
			if(archivoDetalleVenta.is_open())
			{
				while(!archivoDetalleVenta.eof() && getline(archivoDetalleVenta,linea)) 
				{
					i=0;
					while((posi=linea.find(";")) != string::npos) 
					{
						temporal[i]=linea.substr(0,posi); 
						linea.erase(0,posi+1); 
						i++;
					}
					//Asignar los valores al vector
					DetalleVenta objDetalleVenta(std::stoi(temporal[0]),temporal[1],std::stoi(temporal[2]),std::stoi(temporal[3]),std::stof(temporal[4]),std::stof(temporal[5]));
					add(objDetalleVenta);
				}
			}
			archivoDetalleVenta.close();
		}
		catch (exception e)
		{
			cout<<"Ocurrio un error al grabar en el archivo";
		}
	}
};
