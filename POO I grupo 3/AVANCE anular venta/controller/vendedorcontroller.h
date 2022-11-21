#include <iostream>
#include<vector>
#include<fstream>
#include <cstdlib>
#include<String>
#include<cstring>
#include <ctime>
#include"../model/vendedor.h"
#pragma once
using std::stoi;
using namespace std;
void menuVendedor();
void grabarVendedor();
void listarVendedor();
void buscarVendedor();
void modificarVendedor();
void eliminarVendedor();

class VendedorController{
private:
	vector<Vendedor> vectorVendedor;
public:
	VendedorController()
	{
		vector<Vendedor> vectorVendedor;
		cargarDatosDelArchivo();
	}
	//agregar nuevos objetos de tipo Vendedor
	void add(Vendedor obj)
	{
		vectorVendedor.push_back(obj);
	}
	//Obtener un objeto de tipo Vendedor
	Vendedor get(int pos)
	{
		return vectorVendedor[pos];		
	}
	//Cantidad de registros del arreglo
	int size()
	{
		return vectorVendedor.size();
	}	
	
	//Correlativo del numero
	int getCorrelativo()
	{
		if(vectorVendedor.size() == 0)
		{
			return 1;
		}
		else
		{
			return vectorVendedor[size() - 1].getCodigo() + 1; 	
		}		
	}
	Vendedor getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int mitad;
		Vendedor objError;
		objError.setNombre("Error");
		mitad=(inferior + superior)/2;
		while(inferior<=superior)
		{
			if (vectorVendedor[mitad].getCodigo() == codigo)
			{
				return vectorVendedor[mitad];
			}
			if (vectorVendedor[mitad].getCodigo() > codigo)
			{
				superior = mitad - 1;
			}
			if (vectorVendedor[mitad].getCodigo() < codigo)
			{
				inferior = mitad + 1;
			}
			mitad = (inferior + superior)/2;
		}
		return objError;
	}
	
	bool modificar(Vendedor obj,string nom,string fecha,int dni,int edad)
	{
		for(int i=0;i<vectorVendedor.size();i++)
		{
			if(obj.getCodigo() == vectorVendedor[i].getCodigo())	
			{
				vectorVendedor[i].setNombre(nom);
				vectorVendedor[i].setFecha(fecha);
				vectorVendedor[i].setDni(dni);
				vectorVendedor[i].setEdad(edad);
				return true;
			}
		}
		return false;
	}
	
	int getPostArray(Vendedor obj)
	{
		for(int i=0;i<vectorVendedor.size();i++)
		{
			if(obj.getCodigo() == vectorVendedor[i].getCodigo())	
			{
				return i;
			}
		}		
		return -1;
	}
	void remove(Vendedor obj)
	{
		vectorVendedor.erase(vectorVendedor.begin() + getPostArray(obj));
	}
	//Grabar datos en el archivo
	void grabarEnArchivo(Vendedor vendedor)
	{
		try
		{
			fstream archivoVendedor;
			archivoVendedor.open("vendedor.csv",ios::app);
			if(archivoVendedor.is_open()) /*Flujo de salida, mete los datos en el archivo*/
			{
				archivoVendedor<<vendedor.getCodigo()<<";"
					<<vendedor.getNombre()<<";"
					<<vendedor.getFecha()<<";"
					<<vendedor.getDni()<<";"
					<<vendedor.getEdad()<<";"<<endl;
				archivoVendedor.close();
			}
		}
		catch (exception e)
		{
			cout<<"Ocurrio un error al grabar en el archivo";
		}
	}
	//Grabar las modificaciones
	void grabarModificarEliminarArchivo()
	{
		try
		{
			fstream archivoVendedor;
			archivoVendedor.open("vendedor.csv",ios::out);
			if(archivoVendedor.is_open())
			{
				for(Vendedor x:vectorVendedor)
				{
					archivoVendedor<<x.getCodigo()<<";"<<x.getNombre()<<";"<<x.getFecha()<<";"<<x.getDni()<<";"<<x.getEdad()<<";"<<endl;
				}
				archivoVendedor.close();					
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
			string	temporal[5]; /*Porque tiene 4 columnas*/
			fstream archivoVendedor;
			archivoVendedor.open("vendedor.csv",ios::in);
			if(archivoVendedor.is_open())
			{
				while(!archivoVendedor.eof() && getline(archivoVendedor,linea))
				{
					i=0;
					while((posi=linea.find(";")) != string::npos) 
					{
						temporal[i]=linea.substr(0,posi);
						linea.erase(0,posi+1); 
						i++;
					}
					//Asignar los valores al vector
					Vendedor objVendedor(std::stoi(temporal[0]),temporal[1],temporal[2],std::stoi(temporal[3]),std::stoi(temporal[4]));
					add(objVendedor);
				}
			}
			archivoVendedor.close();
		}
		catch (exception e)
		{
			cout<<"Ocurrio un error al grabar en el archivo";
		}
	}
};

VendedorController* venController = new VendedorController();
void menuVendedor()
{
	int opt;	
	system("title Menu Vendedor");
	system("color 7d");
	do
	{
		cout<<"\n\n\t\t\t\t\t\t --------------\n";
		cout<<"\t\t\t\t\t\t| MENU VENDEDOR | \n";
		cout<<"\t\t\t\t\t\t --------------\n\n\n\n";
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
		case 1:system("cls");grabarVendedor();break;
		case 2:system("cls");listarVendedor();break;
		case 3:system("cls");buscarVendedor();break;
		case 4:system("cls");modificarVendedor();break;
		case 5:system("cls");eliminarVendedor();break;
		case 6:system("cls");cout<<"\n\n\n\n\n\n\t\t\t\t\tSALISTE DEL MENU VENDEDOR\n\n\n\n";break;
		default:cout<<"Ingrese una opción correcta[1-6]";
		}
	} while(opt!=6);
	cout<<"\t\t\t\t\t";
	system("pause");
	system("cls");
}

void grabarVendedor()
{
	system("title Registrar Nuevo Vendedor");
	system("color 7d");
	int 	cod;
	string 	nom;
	string 	fecha;
	int 	dni;
	int 	edad;
	string 	flag;
	do
	{
		cout<<"\n\n\t\t\t\t\t Registrar nuevo Vendedor \n";
		cout<<"\t\t\t\t\t ------------------------\n\n";
		cod = venController->getCorrelativo();
		cout<<"\t\t\tCodigo: "<<cod<< "\n\n";
		cin.ignore();
		
		cout << "\t\t\tNombre del Vendedor: ";
		getline(cin,nom);
		
		cout << "\n\t\t\tFecha de registro: ";
		time_t tiempo = time(NULL);
		struct tm *tlocal = localtime(&tiempo);  
		char fecha[20]; 
		strftime(fecha,20,"%d/%m/%Y",tlocal); 
		cout<<fecha;
		
		cout<<"\n\n\t\t\tDNI: ";
		cin>>dni;
		
		cout<<"\n\t\t\tEdad: ";
		cin>>edad;
		cin.ignore();
		Vendedor vendedor(cod,nom,fecha,dni,edad);
		
		venController->add(vendedor);
		venController->grabarEnArchivo(vendedor);
		
		cout << "\n\n\n\t\t\tRegistrar otro Vendedor (S/s): ";
		cin >> flag;
		
		system("cls");
		
	} while(flag == "S" || flag == "s");
	system("cls");
}

void listarVendedor()
{
	system("title Listar Vendedores");
	system("color 7d");
	cout<<"\n\n\t\t Lista de todos los Vendedores \n";
	cout<<"\t\t -----------------------------\n\n";
	for(int i=0;i<venController->size();i++)
	{
		cout<<"\n\t"<<venController->get(i).getCodigo()<<"\t"
			<<venController->get(i).getNombre()<<"\t"
			<<venController->get(i).getFecha()<<"\t"
			<<venController->get(i).getDni()<<"\t"
			<<venController->get(i).getEdad()<<"\n";
	}
	cout<<"\n\n\n\t";
	system("pause");
	system("cls");	
}

void buscarVendedor()
{
	system("title Buscar Vendedores");
	system("color 7d");
	int codVen, inferior, superior;
	inferior = 0;
	superior = venController->size();
	cout<<"\n\n\t\t\tBuscar Vendedor \n";
	cout<<"\t\t\t---------------\n\n\n";
	cout<<"\t\tIngresar codigo del Vendedor a buscar: ";
	cin>>codVen;
	Vendedor venObj = venController->getBuscarPorCodigo(codVen,inferior,superior);
	if(venObj.getNombre() !="Error")
	{
		cout<<"\n\t\t\t**Registro encontrado**\n\n";
		cout<<"\t\tCodigo: "<<venObj.getCodigo()<<"\n\n";
		cout<<"\t\tNombre: "<<venObj.getNombre()<<"\n\n";
		cout<<"\t\tFecha de registro: "<<venObj.getFecha()<<"\n\n";
		cout<<"\t\tDni: "<<venObj.getDni()<<"\n\n";
		cout<<"\t\tEdad: "<<venObj.getEdad()<<"\n\n";
	}
	else
	{
		cout<<"\n\t\tNo se encontro el registro!\n";
		cout<<"\n\n\n\t\t";
		system("pause");
		menuVendedor();
	}
	cout<<"\n\n\n\t\t";
	system("pause");
	system("cls");
}

void modificarVendedor()
{
	system("title Modificar Vendedores");
	system("color 7d");
	int codVen;
	int inferior = 0;
	int superior = venController->size();
	cout<<"\n\n\t\t\tModificar Vendedor \n";
	cout<<"\t\t\t----------------\n\n\n";
	cout<<"\t\tIngresar el codigo a modificar: ";
	cin>>codVen;
	Vendedor venObj = venController->getBuscarPorCodigo(codVen,inferior,superior);
	if(venObj.getNombre() != "Error")
	{	
		/*Buscar objeto a modificar*/
		cout<<"\n\t\t\t**Registro Encontrado**\n\n";
		cout<<"\t\tCodigo: "<<venObj.getCodigo()<<"\n\n";
		cout<<"\t\tNombre: "<<venObj.getNombre()<<"\n\n";
		cout<<"\t\tFecha: "<<venObj.getFecha()<<"\n\n";
		cout<<"\t\tDni: "<<venObj.getDni()<<"\n\n";
		cout<<"\t\tEdad: "<<venObj.getEdad()<<"\n\n";
		cin.ignore();	
		/*Fin del objeto a modificar*/
		string nomV,fecV;
		int	   dniV, edadV;	
		cout<<"\n\t\t\t**Modificando Campos**\n\n";
		cout<<"\t\tModificando el Nombre...: ";
		getline(cin,nomV);
		cout<<"\n\t\tModificando la Fecha...: ";
		getline(cin,fecV);
		cout<<"\n\t\tModificando el DNI...: ";
		cin>>dniV;
		cout<<"\n\t\tModificando la edad...: ";
		cin>>edadV;
		bool estado = venController->modificar(venObj,nomV,fecV,dniV,edadV);
		if(estado = true)
		{
			cout<<"\n\t\tREGISTRO MODIFICADO SATISFACTORIAMENTE!!!\n";
			//Grabar en archivo
			venController->grabarModificarEliminarArchivo();
		}
		else
		{
			cout<<"\n\n\t\tNO SE ENCONTRO EL REGISTRO A MODIFICAR!\n";
			cout<<"\n\n\t\t";
			system("pause");
			menuVendedor();		
		}
	}
	else
	{
		cout<<"NO SE ENCONTRO EL REGISTRO\n";		
	}
	cout<<"\n\n\n\t\t";
	system("pause");
	system("cls");	
}
void eliminarVendedor()
{
	system("title Eliminar Vendedores");
	system("color 7d");
	int cod;
	int inferior = 0;
	int superior = venController->size();
	cout<<"\n\n\t\t\tEliminar Vendedor \n";
	cout<<"\t\t\t-----------------\n\n\n";
	cout<<"\t\tIngresar el codigo a eliminar: ";
	cin>>cod;
	Vendedor objEliminar = venController->getBuscarPorCodigo(cod,inferior,superior);
	if(objEliminar.getNombre() !="Error")
	{
		venController->remove(objEliminar);
		cout<<"\n\n\t\tREGISTRO ELIMINADO SATISFACTORIAMENTE!!!";
		/*Grabar en archivo*/
		venController->grabarModificarEliminarArchivo();
	}
	else
	{
		cout<<"\n\t\tNO SE ENCONTRO EL REGISTRO!!\n";
	}
	cout<<"\n\n\n\t\t";
	system("pause");
	system("cls");
}


