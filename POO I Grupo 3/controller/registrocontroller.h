#include <iostream>
#include<vector>
#include<conio.h>
#include<fstream>
#include <cstdlib>
#include<string>
#include<cstring>
#include"../model/registro.h"
#include "categoriacontroller.h"
#include "productocontroller.h"
#include "clientecontroller.h"
#include "vendedorcontroller.h"
#include "ventacontroller.h"
using std::stoi;
using namespace std;
void acceder();
void menuGeneral();
void registrarUsuario();
void menuDeOpciones();
void generarVenta();
string desencriptar(string);

class RegistroController{
private:
	vector<Registro> vectorRegistro;
public:
	RegistroController()
	{
		vector<Registro> vectorRegistro;
		cargarDatosDelArchivo();
	}
	//agregar nuevos objetos de tipo Registro
	void add(Registro obj)
	{
		vectorRegistro.push_back(obj);
	}
	//Obtener un objeto de tipo Registro
	Registro get(int pos)
	{
		return vectorRegistro[pos];		
	}
	//Cantidad de registros del arreglo
	int size()
	{
		return vectorRegistro.size();
	}	
	//Correlativo del numero
	int getCorrelativo()
	{
		if(vectorRegistro.size() == 0)
		{
			return 1;
		}
		else
		{
			return vectorRegistro[size() - 1].getCodigo() + 1; 	
		}		
	}
	//Grabar datos en el archivo
	void grabarEnArchivo(Registro registro)
	{
		try
		{
			fstream archivoRegistro;
			archivoRegistro.open("registro.csv",ios::app);
			if(archivoRegistro.is_open()) 
			{
				archivoRegistro<<registro.getCodigo()<<";"
					<<registro.getUsuario()<<";"
					<<registro.getContrasena()<<";"
					<<registro.getDni()<<";"<<endl;
				archivoRegistro.close();
			}
		}
		catch (exception e)
		{
			cout<<"Ocurrio un error al grabar en el archivo";
		}
	}
	void cargarDatosDelArchivo()
	{
		try
		{
			int 	i;
			size_t 	posi;
			string 	linea;
			string	temporal[4]; /*Porque tiene 4 columnas*/
			fstream archivoRegistro;
			archivoRegistro.open("registro.csv",ios::in);
			if(archivoRegistro.is_open())
			{
				while(!archivoRegistro.eof() && getline(archivoRegistro,linea)) /*Si no ha llegado al fin y saca la informacion del archivo y pasa el registro a la variable linea*/
				{
					i=0;
					while((posi=linea.find(";")) != string::npos) /*Hasta que llegue al punto y coma*/
					{
						temporal[i]=linea.substr(0,posi); /*posi: cantidad de caracteres antes de llegar al punto y coma*/
						linea.erase(0,posi+1); /*para eliminar hasta el punto y coma*/
						i++;
					}
					//Asignar los valores al vector
					Registro objRegistro(std::stoi(temporal[0]),temporal[1],temporal[2],std::stoi(temporal[3]));
					add(objRegistro);
				}
			}
			archivoRegistro.close();
		}
		catch (exception e)
		{
			cout<<"Ocurrio un error al grabar en el archivo";
		}
	}
};

//Para ingresar al sistema
RegistroController* regController = new RegistroController();
string desencriptar(string cont)
{
	char desencriptado;
	for(int i=0; i<cont.size(); i++)
	{
		desencriptado = (cont[i] + 30);
		cont[i] = desencriptado;
	}
	return cont;
}
void acceder()
{
	char ch;
	bool acceso=false;
	system("title Acceder al sistema");
	system("color 74");
	for(int intentos=0;intentos<3;intentos++){
		string user, contra;
		string us="Daniela";
		string cont="ejemplo";
		cout<<"\n\n\n\n";
		cout<<"\t\t\t\t\t\t -------\n";
		cout<<"\t\t\t\t\t\t| LOGIN |\n";
		cout<<"\t\t\t\t\t\t -------\n\n\n\n";
		cout<<"\t\t\t\t\tIngrese Usuario: ";
		cin>>user;
		cout<<"\n\t\t\t\t\tIngrese su contraseña: ";
		ch = _getch();
		while(ch != 13)
		{
			if(ch != 8)
			{
				contra.push_back(ch);
				cout<<"*";
			}
			else
			{
				if(contra.length()>0)
				{
					cout<<"\b \b";
					contra.pop_back();
				}
				
			}
			ch = _getch();
		}
		if((user==us)&& (contra==cont))
		{
			acceso=true;
		}
		else
		{
			for(int i = 1;i<regController->size();i++)
			{
				if((regController->get(i).getUsuario()==user)&&(desencriptar(regController->get(i).getContrasena())==contra))
				{
					acceso=true;
				}
				
			}
		}
		if(acceso==true)
		{
			system("cls");
			menuGeneral();
		}
		else
		{
			if(intentos<2)
			{
				cout<<"\n\n\n\n\t\t\t ¡¡DATOS INVALIDOS, POR FAVOR VUELVA A INTENTARLO!!\n\n\n";
			}
			else
			{
				cout<<"\n\n\n\n\t\t\t\t ¡¡¡SE HA LLEGADO AL LIMITE DE INTENTOS!!!\n\n\n";
			}
		}
		cout<<"\t\t\t\t";
		system("pause");
		system("cls");
	}
}
void menuGeneral()
{
	int opt;	
	system("title Menu General");
	system("color 7d");
	do
	{
		cout<<"\n\n\t\t\t\t\t\t -------------\n";
		cout<<"\t\t\t\t\t\t| MENU GENERAL | \n";
		cout<<"\t\t\t\t\t\t -------------\n\n\n\n";
		cout<<"\t\t\t\t\t Registrar nuevo usuario........[1]\n\n\n";
		cout<<"\t\t\t\t\t Ir al menu de ventas...........[2]\n\n\n";
		cout<<"\t\t\t\t\t Salir..........................[3]\n\n\n\n";
		cout<<"\t\t\t\t\t Ingrese una opcion: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");registrarUsuario();break;
		case 2:system("cls");menuDeOpciones();break;
		case 3:system("cls");cout<<"\n\n\n\n\n\n\t\t\t\t\t**GRACIAS POR USAR NUESTRO PROGRAMA**\n\n\n\n";break;
		default:cout<<"Ingrese una opción correcta[1-3]";
		}
	} while(opt!=3);
}

void registrarUsuario()
{
	system("title Registrar Usuario");
	system("color 7d");
	int 	cod;
	string 	usuario;
	string 	contrasena;
	int dni;
	string  flag;
	do
	{
		cout<<"\n\n\t\t\t\t\t Registrar nuevo usuario \n";
		cout<<"\t\t\t\t\t -----------------------\n\n";
		cod = regController->getCorrelativo();
		cout<<"\t\t\tCodigo: "<<cod<<"\n\n";
		cin.ignore();
		
		cout<<"\t\t\tUsuario: ";
		getline(cin,usuario);
		
		cout<<"\n\t\t\tContrasena: ";
		getline(cin,contrasena);
		char encriptado;
		for(int i=0; i<contrasena.size(); i++)
		{
			encriptado = (contrasena[i] - 30);
			contrasena[i] = encriptado;
		}
		
		cout<<"\n\t\t\tDNI: ";
		cin>>dni;
		
		cin.ignore();
		
		Registro registro(cod,usuario,contrasena,dni);	
		regController->add(registro);
		
		regController->grabarEnArchivo(registro);
		cout<<"\n\n\n\t\t\tRegistrar otro usuario (S/s):";
		cin>>flag;
		
		system("cls");
	} 
	while(flag == "S" || flag == "s");
	
	system("cls");
}
void menuDeOpciones()
{
	int opt;
	system("title Menu de Opciones");
	system("color 7d");
	do
	{
		cout<<"\n\n\t\t\t\t\t  -----------------\n";
		cout<<"\t\t\t\t\t | MENU DE OPCIONES | \n";
		cout<<"\t\t\t\t\t  -----------------\n\n\n\n";
		cout<<"\t\t\t\tRegistro de clientes...................[1]\n\n";
		cout<<"\t\t\t\tRegistro de productos..................[2]\n\n";
		cout<<"\t\t\t\tRegistro de categorias de producto.....[3]\n\n";
		cout<<"\t\t\t\tRegistro de vendedores.................[4]\n\n";
		cout<<"\t\t\t\tGenerar venta..........................[5]\n\n";
		cout<<"\t\t\t\tAnular venta...........................[6]\n\n";
		cout<<"\t\t\t\tSalir..................................[7]\n\n\n";
		cout<<"\t\t\t\tIngresar una opción: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");menuCliente();break;
		case 2:system("cls");menuProducto();break;
		case 3:system("cls");menuCategoria();break;
		case 4:system("cls");menuVendedor();break;
		case 5:system("cls");generarVenta();break;
		case 6:system("cls");anularVenta();break;
		case 7:system("cls");cout<<"\n\n\n\n\n\n\t\t\t\t\tSALISTE DEL MENU DE OPCIONES\n\n\n\n";break;
		default:cout<<"Ingrese una opción correcta[1-7]";
		}
	} while(opt!=7);
	cout<<"\t\t\t\t\t";
	system("pause");
	system("cls");
}
