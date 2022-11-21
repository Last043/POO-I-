#include <iostream>
#include<vector>
#include<fstream>
#include <cstdlib>
#include<String>
#include<cstring>
#include <ctime>
#include"../model/cliente.h"
#pragma once
using std::stoi;
using namespace std;
void menuCliente();
void grabarCliente();
void listarCliente();
void buscarCliente();
void modificarCliente();
void eliminarCliente();

class ClienteController{
private:
	vector<Cliente> vectorCliente;
public:
	ClienteController()
	{
		vector<Cliente> vectorCliente;
		cargarDatosDelArchivo();
	}
	//agregar nuevos objetos de tipo Cliente
	void add(Cliente obj)
	{
		vectorCliente.push_back(obj);
	}
	//Obtener un objeto de tipo Cliente
	Cliente get(int pos)
	{
		return vectorCliente[pos];		
	}
	//Cantidad de registros del arreglo
	int size()
	{
		return vectorCliente.size();
	}	
	//Correlativo del numero
	int getCorrelativo()
	{
		if(vectorCliente.size() == 0)
		{
			return 1;
		}
		else
		{
			return vectorCliente[size() - 1].getCodigo() + 1; 	
		}		
	}
	Cliente getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int mitad;
		Cliente objError;
		objError.setNombre("Error");
		mitad=(inferior + superior)/2;
		while(inferior<=superior)
		{
			if (vectorCliente[mitad].getCodigo() == codigo)
			{
				return vectorCliente[mitad];
			}
			if (vectorCliente[mitad].getCodigo() > codigo)
			{
				superior = mitad - 1;
			}
			if (vectorCliente[mitad].getCodigo() < codigo)
			{
				inferior = mitad + 1;
			}
			mitad = (inferior + superior)/2;
		}
		return objError;
	}
	
	bool modificar(Cliente obj,string nom,string fecha,int dni,int edad)
	{
		for(int i=0;i<vectorCliente.size();i++)
		{
			if(obj.getCodigo() == vectorCliente[i].getCodigo())	
			{
				vectorCliente[i].setNombre(nom);
				vectorCliente[i].setFecha(fecha);
				vectorCliente[i].setDni(dni);
				vectorCliente[i].setEdad(edad);
				return true;
			}
		}
		return false;
	}
	
	int getPostArray(Cliente obj)
	{
		for(int i=0;i<vectorCliente.size();i++)
		{
			if(obj.getCodigo() == vectorCliente[i].getCodigo())	
			{
				return i;
			}
		}		
		return -1;
	}
	void remove(Cliente obj)
	{
		vectorCliente.erase(vectorCliente.begin() + getPostArray(obj));
	}
	//Grabar datos en el archivo
	void grabarEnArchivo(Cliente cliente)
	{
		try
		{
			fstream archivoCliente;
			archivoCliente.open("cliente.csv",ios::app);
			if(archivoCliente.is_open()) /*Flujo de salida, mete los datos en el archivo*/
			{
				archivoCliente<<cliente.getCodigo()<<";"
					<<cliente.getNombre()<<";"
					<<cliente.getFecha()<<";"
					<<cliente.getDni()<<";"
					<<cliente.getEdad()<<";"<<endl;
				archivoCliente.close();
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
			fstream archivoCliente;
			archivoCliente.open("cliente.csv",ios::out);
			if(archivoCliente.is_open())
			{
				for(Cliente x:vectorCliente)
				{
					archivoCliente<<x.getCodigo()<<";"<<x.getNombre()<<";"<<x.getFecha()<<";"<<x.getDni()<<";"<<x.getEdad()<<";"<<endl;
				}
				archivoCliente.close();					
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
			fstream archivoCliente;
			archivoCliente.open("cliente.csv",ios::in);
			if(archivoCliente.is_open())
			{
				while(!archivoCliente.eof() && getline(archivoCliente,linea)) /*Si no ha llegado al fin y saca la informacion del archivo y pasa el registro a la variable linea*/
				{
					i=0;
					while((posi=linea.find(";")) != string::npos) /*Hasta que llegue al punto y coma*/
					{
						temporal[i]=linea.substr(0,posi); /*posi: cantidad de caracteres antes de llegar al punto y coma*/
						linea.erase(0,posi+1); /*para eliminar hasta el punto y coma*/
						i++;
					}
					//Asignar los valores al vector
					Cliente objCliente(std::stoi(temporal[0]),temporal[1],temporal[2],std::stoi(temporal[3]),std::stoi(temporal[4]));
					add(objCliente);
				}
			}
			archivoCliente.close();
		}
		catch (exception e)
		{
			cout<<"Ocurrio un error al grabar en el archivo";
		}
	}
};

ClienteController* cliController = new ClienteController();
void menuCliente()
{
	int opt;	
	system("title Menu Cliente");
	system("color 7d");
	do
	{
		cout<<"\n\n\t\t\t\t\t\t -------------\n";
		cout<<"\t\t\t\t\t\t| MENU CLIENTE | \n";
		cout<<"\t\t\t\t\t\t -------------\n\n\n\n";
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
		case 1:system("cls");grabarCliente();break;
		case 2:system("cls");listarCliente();break;
		case 3:system("cls");buscarCliente();break;
		case 4:system("cls");modificarCliente();break;
		case 5:system("cls");eliminarCliente();break;
		case 6:system("cls");cout<<"\n\n\n\n\n\n\t\t\t\t\tSALISTE DEL MENU CLIENTE\n\n\n\n";break;
		default:cout<<"Ingrese una opción correcta[1-6]";
		}
	} while(opt!=6);
	cout<<"\t\t\t\t\t";
	system("pause");
	system("cls");
}

void grabarCliente()
{
	system("title Registrar Nuevo Cliente");
	system("color 7d");
	int 	cod;
	string 	nom;
	string 	fecha;
	int 	dni;
	int 	edad;
	string 	flag;
	do
	{
		cout<<"\n\n\t\t\t\t\t Registrar nuevo cliente \n";
		cout<<"\t\t\t\t\t -----------------------\n\n";
		cod = cliController->getCorrelativo();
		cout<<"\t\t\tCodigo: "<<cod<< "\n\n";
		cin.ignore();
		
		cout << "\t\t\tNombre del Cliente: ";
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
		Cliente cliente(cod,nom,fecha,dni,edad);
		
		cliController->add(cliente);
		cliController->grabarEnArchivo(cliente);
		
		cout << "\n\n\n\t\t\tRegistrar otro cliente (S/s): ";
		cin >> flag;
		
		system("cls");
		
	} while(flag == "S" || flag == "s");
	system("cls");
}

void listarCliente()
{
	system("title Listar Clientes");
	system("color 7d");
	cout<<"\n\n\t\t Lista de todos los clientes \n";
	cout<<"\t\t --------------------------\n\n";
	for(int i=0;i<cliController->size();i++)
	{
		cout<<"\n\t"<<cliController->get(i).getCodigo()<<"\t"
			<<cliController->get(i).getNombre()<<"\t"
			<<cliController->get(i).getFecha()<<"\t"
			<<cliController->get(i).getDni()<<"\t"
			<<cliController->get(i).getEdad()<<"\n";
	}
	cout<<"\n\n\n\t";
	system("pause");
	system("cls");	
}

void buscarCliente()
{
	system("title Buscar Clientes");
	system("color 7d");
	int codCli, inferior, superior;
	inferior = 0;
	superior = cliController->size();
	cout<<"\n\n\t\t\tBuscar Cliente \n";
	cout<<"\t\t\t--------------\n\n\n";
	cout<<"\t\tIngresar codigo del cliente a buscar: ";
	cin>>codCli;
	Cliente cliObj = cliController->getBuscarPorCodigo(codCli,inferior,superior);
	if(cliObj.getNombre() !="Error")
	{
		cout<<"\n\t\t\t**Registro encontrado**\n\n";
		cout<<"\t\tCodigo: "<<cliObj.getCodigo()<<"\n\n";
		cout<<"\t\tNombre: "<<cliObj.getNombre()<<"\n\n";
		cout<<"\t\tFecha de registro: "<<cliObj.getFecha()<<"\n\n";
		cout<<"\t\tDni: "<<cliObj.getDni()<<"\n\n";
		cout<<"\t\tEdad: "<<cliObj.getEdad()<<"\n\n";
	}
	else
	{
		cout<<"\n\t\tNo se encontro el registro!\n";
		cout<<"\n\n\n\t\t";
		system("pause");
		menuCliente();
	}
	cout<<"\n\n\n\t\t";
	system("pause");
	system("cls");
}

void modificarCliente()
{
	system("title Modificar Clientes");
	system("color 7d");
	int codCli;
	int inferior = 0;
	int superior = cliController->size();
	cout<<"\n\n\t\t\tModificar Cliente \n";
	cout<<"\t\t\t---------------\n\n\n";
	cout<<"\t\tIngresar el codigo a modificar: ";
	cin>>codCli;
	Cliente cliObj = cliController->getBuscarPorCodigo(codCli,inferior,superior);
	if(cliObj.getNombre() != "Error")
	{	
		/*Buscar objeto a modificar*/
		cout<<"\n\t\t\t**Registro Encontrado**\n\n";
		cout<<"\t\tCodigo: "<<cliObj.getCodigo()<<"\n\n";
		cout<<"\t\tNombre: "<<cliObj.getNombre()<<"\n\n";
		cout<<"\t\tFecha: "<<cliObj.getFecha()<<"\n\n";
		cout<<"\t\tDni: "<<cliObj.getDni()<<"\n\n";
		cout<<"\t\tEdad: "<<cliObj.getEdad()<<"\n\n";
		cin.ignore();	
		/*Fin del objeto a modificar*/
		string nomC,fecC;
		int	   dniC, edadC;	
		cout<<"\n\t\t\t**Modificando Campos**\n\n";
		cout<<"\t\tModificando el Nombre...: ";
		getline(cin,nomC);
		cout<<"\n\t\tModificando la Fecha...: ";
		getline(cin,fecC);
		cout<<"\n\t\tModificando el DNI...: ";
		cin>>dniC;
		cout<<"\n\t\tModificando la edad...: ";
		cin>>edadC;
		bool estado = cliController->modificar(cliObj,nomC,fecC,dniC,edadC);
		if(estado = true)
		{
			cout<<"\n\t\tREGISTRO MODIFICADO SATISFACTORIAMENTE!!!\n";
			//Grabar en archivo
			cliController->grabarModificarEliminarArchivo();
		}
		else
		{
			cout<<"\n\n\t\tNO SE ENCONTRO EL REGISTRO A MODIFICAR!\n";
			cout<<"\n\n\t\t";
			system("pause");
			menuCliente();		
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
void eliminarCliente()
{
	system("title Eliminar Clientes");
	system("color 7d");
	int cod;
	int inferior = 0;
	int superior = cliController->size();
	cout<<"\n\n\t\t\tEliminar Cliente \n";
	cout<<"\t\t\t-----------------\n\n\n";
	cout<<"\t\tIngresar el codigo a eliminar: ";
	cin>>cod;
	Cliente objEliminar = cliController->getBuscarPorCodigo(cod,inferior,superior);
	if(objEliminar.getNombre() !="Error")
	{
		cliController->remove(objEliminar);
		cout<<"\n\n\t\tREGISTRO ELIMINADO SATISFACTORIAMENTE!!!";
		/*Grabar en archivo*/
		cliController->grabarModificarEliminarArchivo();
	}
	else
	{
		cout<<"\n\t\tNO SE ENCONTRO EL REGISTRO!!\n";
	}
	cout<<"\n\n\n\t\t";
	system("pause");
	system("cls");
}


