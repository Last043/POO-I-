#include <iostream>
#include<vector>
#include<fstream>
#include <cstdlib>
#include<String>
#include<cstring>
#include <ctime>
#include"../model/venta.h"
#include "detalleVentacontroller.h"
#include "clientecontroller.h"
#include "productocontroller.h"
#include "vendedorcontroller.h"

using std::stoi;
using std::stof;
using namespace std;
void generarVenta();
void anularVenta();

class VentaController{
private:
	vector<Venta> vectorVenta;
public:
	VentaController()
	{
		vector<Venta> vectorVenta;
		cargarDatosDelArchivo();
	}
	
	void add(Venta obj)
	{
		vectorVenta.push_back(obj);
	}
	
	Venta get(int pos)
	{
		return vectorVenta[pos];		
	}
	
	int size()
	{
		return vectorVenta.size();
	}	
	
	int getCorrelativo()
	{
		if(vectorVenta.size() == 0)
		{
			return 1;
		}
		else
		{
			return vectorVenta[size() - 1].getCodigo() + 1; 	
		}		
	}
	
	Venta getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int mitad;
		Venta objError;
		objError.setFecha("Error");
		mitad=(inferior + superior)/2;
		while(inferior<=superior)
		{
			if (vectorVenta[mitad].getCodigo() == codigo)
			{
				return vectorVenta[mitad];
			}
			if (vectorVenta[mitad].getCodigo() > codigo)
			{
				superior = mitad - 1;
			}
			if (vectorVenta[mitad].getCodigo() < codigo)
			{
				inferior = mitad + 1;
			}
			mitad = (inferior + superior)/2;
		}
		return objError;
	}
	
	int getPostArray(Venta obj)
	{
		for(int i=0;i<vectorVenta.size();i++)
		{
			if(obj.getCodigo() == vectorVenta[i].getCodigo())	
			{
				return i;
			}
		}		
		return -1;
	}
	void remove(Venta obj)
	{
		vectorVenta.erase(vectorVenta.begin() + getPostArray(obj));
	}
	
	//Grabar datos en el archivo
	void grabarEnArchivo(Venta venta)
	{
		try
		{
			fstream archivoVenta;
			archivoVenta.open("venta.csv",ios::app);
			if(archivoVenta.is_open()) 
			{
				archivoVenta<<venta.getCodigo()<<";"
					<<venta.getCodCliente()<<";"
					<<venta.getFecha()<<";"
					<<venta.getSerie()<<";"
					<<venta.getCodVendedor()<<";"
					<<venta.getPrecioTotal()<<";"<<endl;
				archivoVenta.close();
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
			fstream archivoVenta;
			archivoVenta.open("venta.csv",ios::out);
			if(archivoVenta.is_open())
			{
				for(Venta x:vectorVenta)
				{
					archivoVenta<<x.getCodigo()<<";"<<x.getCodCliente()<<";"<<x.getFecha()<<";"<<x.getSerie()<<";"<<x.getCodVendedor()<<";"<<x.getPrecioTotal()<<";"<<endl;
				}
				archivoVenta.close();					
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
			fstream archivoVenta;
			archivoVenta.open("venta.csv",ios::in);
			if(archivoVenta.is_open())
			{
				while(!archivoVenta.eof() && getline(archivoVenta,linea)) 
				{
					i=0;
					while((posi=linea.find(";")) != string::npos) 
					{
						temporal[i]=linea.substr(0,posi); 
						linea.erase(0,posi+1); 
						i++;
					}
					//Asignar los valores al vector
					Venta objVenta(std::stoi(temporal[0]),std::stoi(temporal[1]),temporal[2],std::stoi(temporal[3]),std::stoi(temporal[4]),std::stof(temporal[5]));
					add(objVenta);
				}
			}
			archivoVenta.close();
		}
		catch (exception e)
		{
			cout<<"Ocurrio un error al grabar en el archivo";
		}
	}
};

VentaController* ventController = new VentaController();
DetalleVentaController* detVentController = new DetalleVentaController();
void generarVenta()
{
	system("title Generar Venta");
	system("color 7d");
	string 	nombreProducto;
	int 	inferior = 0;
	int 	superior = cliController->size();
	int 	primero=0;
	int 	ultimo = proController->size();
	int 	codigo;
	int 	serie;
	int 	fij=100000000;
	int 	codCliente;
	int 	codVendedor;
	int 	codProducto;
	string 	nomProducto;
	int 	cantidad;
	float 	subTotal=0;
	string 	cont;
	string 	flag;
	string 	comprar;
	string 	confirm;
	string 	menVen;
	bool 	exis=false;
	do
	{
		float	precioTotal=0;
		codigo = ventController->getCorrelativo();
		serie=fij+codigo;
		cout<<"\n\t\t\t\t\t\t\t\tSerie: "<<serie<<"\n";
		
		cout << "\t\t\t\t\t\t\t\tFecha: ";
		time_t tiempo = time(NULL);//variables donde guardo el valor de la funcion time. 
		struct tm *tlocal = localtime(&tiempo); //estructura donde obtengo el tiempo 
		char fecha[20]; //array donde guardo la fecha
		strftime(fecha,20,"%d/%m/%Y",tlocal); //formato para guardar la fecha obtenido en *tlocal como dd/mm/yyyy
		cout<<fecha;
		cout << "\n\t\t\t\t\t\t\t\tHora: ";
		char hora[10]; 
		strftime(hora,10,"%H:%M:%S",tlocal); 
		cout<<hora;
		cout<<"\n\n\t\t\tCodigo del Vendedor: ";
		cin>>codVendedor;
		cin.ignore();
		Vendedor venObj = venController->getBuscarPorCodigo(codVendedor,inferior,superior);
		if(venObj.getNombre() !="Error")
		{
			cout<<"\t\t\tCodigo del Cliente: ";
			cin>>codCliente;
			cin.ignore();
			Cliente cliObj = cliController->getBuscarPorCodigo(codCliente,inferior,superior);
			if(cliObj.getNombre() !="Error")
			{
				cout<<"\t\t\tNombre: "<<cliObj.getNombre()<<"\n";
				cout<<"\t\t\tDni: "<<cliObj.getDni()<<"\n\n";
				do
				{
					cout<<"\t\t\t---------\n";
					cout<<"\t\t\tProductos\n";
					cout<<"\t\t\t---------\n";
					cout<<"\t\t\tNombre del Producto: ";
					
					getline(cin,nomProducto);
					subTotal=0;
					exis=false;
					for(int i = 0;i<proController->size();i++)
					{
						if (nomProducto==proController->get(i).getNomPro())
						{
							cout<<"\t\t\t["<<proController->get(i).getCodigo()<<"]"<<"\t"<<proController->get(i).getNomPro()
								<<"\t"<<proController->get(i).getDesPro()<<"\tS/."<<proController->get(i).getPrePro()<<"\n";
							exis=true;
						}
					}
					if(exis==true)
					{
						cout<<"\n\t\t\tSeleccione un producto: ";
						cin>>codProducto;
						
						Producto proObj = proController->getBuscarPorCodigo(codProducto,primero,ultimo);
						if(proObj.getDesPro() !="Error" && nomProducto==proObj.getNomPro())
						{
							cout<<"\n\t\t\t--Detalles del producto seleccionado--\n";
							cout<<"\t\t\tCodigo: "<<proObj.getCodigo()<<"\tNombre: "<<proObj.getNomPro()<<"\tDescripcion: "<<proObj.getDesPro()
								<<"\tPrecio: S/. "<<proObj.getPrePro()<<"\n";
							cout<<"\t\t\tCantidad: ";
							cin>>cantidad;
							subTotal=proObj.getPrePro()*cantidad;
							precioTotal=subTotal+precioTotal;
							cout<<"\n\t\t\t*********************\n";
							cout<<"\t\t\t--Detalle de compra--\n";
							cout<<"\t\t\t*********************\n";
							cout<<"\t\t\tProducto "<<"Cantidad "<<"Precio "<<"SubTotal\n";
							for(int i = 0;i<detVentController->size();i++)
							{
								if(codigo==detVentController->get(i).getCodigo())
								{
									cout<<"\t\t\t   "<<detVentController->get(i).getCodProducto()<<"\t   "<<detVentController->get(i).getCantidad()
										<<"\t   S/."<<detVentController->get(i).getPrecioProducto()<<"\t   S/."<<detVentController->get(i).getSubTotal()<<"\n";
								}
							}
							cout<<"\t\t\t---------------------------------\n";
							cout<<"\t\t\t   "<<proObj.getCodigo()<<"\t   "<<cantidad<<"\t   S/."<<proObj.getPrePro()<<"\t   S/."<<subTotal<<"\n\n";
							cout<<"\t\t\t\tPrecio Total: |S/. "<<precioTotal<<"|\n\n";
							cout<<"\t\t\tEsta seguro de esta compra? (S/s): ";
							cin>>confirm;
							if(confirm=="S" || confirm=="s")
							{
								DetalleVenta detalleVenta(codigo,hora,codProducto,cantidad,proObj.getPrePro(),subTotal);
								detVentController->add(detalleVenta);
								detVentController->grabarEnArchivo(detalleVenta);
							}
							else{
								
							}
						}
						else
						{
							cout<<"\n\t\t\tEL CODIGO INGRESADO NO CORRESPONDE A NINGUN PRODUCTO MOSTRADO EN PANTALLA\n\n";
							cout<<"\t\t\t";
							system("pause");
							cin.ignore();
						}
					}
					else
					{
						cout<<"\t\t\tEL PRODUCTO NO EXISTE\n";
						cout<<"\t\t\t";
						system("pause");
					}
					
					cout<<"\t\t\tDesea continuar comprando? (S/s): ";
					cin>>comprar;
					cin.ignore();
					if(comprar=="S" || comprar=="s")
					{
						system("cls");
						cout<<"\n\t\t\t\t\t\t\t\tSerie: "<<serie<<"\n";
						cout << "\t\t\t\t\t\t\t\tFecha: ";
						cout<<fecha;
						cout << "\n\t\t\t\t\t\t\t\tHora: ";
						char hora[10]; 
						strftime(hora,10,"%H:%M:%S",tlocal); 
						cout<<hora;
						cout<<"\n\n\t\t\tCodigo del Cliente: ";
						cout<<codCliente;
						cout<<"\n\t\t\tNombre: "<<cliObj.getNombre()<<"\n";
						cout<<"\t\t\tDni: "<<cliObj.getDni()<<"\n\n";
					}
					else
					{
						if(subTotal>0)
						{
							Venta venta(codigo,codCliente,fecha,serie,codVendedor,precioTotal);
							ventController->add(venta);
							ventController->grabarEnArchivo(venta);
						}
					}
					
				} while(comprar=="S" || comprar=="s");
			}
			else
			{
				cout<<"\n\t\t\tEl cliente no está registrado\n";
				cin.ignore();
				cout<<"\n\n\t\t\tDesea ir al menu Cliente? (S/s):";
				cin>>cont;
				if(cont=="S" || cont=="s")
				{
					system("cls");
					menuCliente();
				}
				else
				{
					cout<<"\n\n\n\t\t";
					system("pause");
					system("cls");
					generarVenta();
				}
			}
		}
		else
		{
			cout<<"\n\t\t\tEl vendedor no está registrado\n";
			cin.ignore();
			cout<<"\n\n\t\t\tDesea ir al menu Vendedor? (S/s):";
			cin>>menVen;
			if(menVen=="S" || menVen=="s")
			{
				system("cls");
				menuVendedor();
			}
			else
			{
				cout<<"\n\n\n\t\t";
				system("pause");
				system("cls");
				generarVenta();
			}
		}
		cout<<"\n\t\t\tDesea generar otra venta? (S/s): ";
		cin>>flag;
		system("cls");
	} while(flag == "S" || flag == "s");
	system("cls");
}

void anularVenta()
{
	system("title Eliminar Venta");
	system("color 7d");
	int cod;
	int inferior = 0;
	int superior = ventController->size();
	cout<<"\n\n\t\t\tEliminar Venta \n";
	cout<<"\t\t\t-----------------\n\n\n";
	cout<<"\t\tIngresar el codigo a eliminar: ";
	cin>>cod;
	Venta objEliminar = ventController->getBuscarPorCodigo(cod,inferior,superior);
	DetalleVenta objDetEliminar = detVentController->getBuscarPorCodigo(cod,inferior,superior);
	if(objEliminar.getFecha() !="Error" && objDetEliminar.getHora() !="Error")
	{
		ventController->remove(objEliminar);
		for(int i = 0;i<detVentController->size();i++)
		{
			if(cod==detVentController->get(i).getCodigo())
			{
				detVentController->remove(objDetEliminar);
				detVentController->grabarEliminarArchivo();
				i--;
			}
		}
		ventController->grabarEliminarArchivo();
		cout<<"\n\n\t\tREGISTRO ELIMINADO SATISFACTORIAMENTE!!!";
	}
	else
	{
		cout<<"\n\t\tNO SE ENCONTRO EL REGISTRO!!\n";
	}
	cout<<"\n\n\n\t\t";
	system("pause");
	system("cls");
}
