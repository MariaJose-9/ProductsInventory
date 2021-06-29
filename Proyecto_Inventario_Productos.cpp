#include <iostream>
#include <string>
#include<iomanip>
#include <fstream>
using namespace std;

const string DOCUMENT_NAME = "products.txt";

struct productStruct
{
    string ID;
    string name;
    string category;
    float price;
	int quantity;
};

struct nodo{
	productStruct product;
	nodo *next;
};

typedef struct nodo *Tlista;

void insert_product (Tlista &lista);
void insert_product_to_list(Tlista &lista, productStruct dato);
void update_product_menu(Tlista &lista);
void update_product(Tlista &lista, string ID);
void delete_product(Tlista &lista, string ID);
void delete_product_menu(Tlista &lista);
void list_products(Tlista &lista);
void write_listing_header();
void show_product (productStruct p);
void read_products_document(Tlista &lista);
void save_product(productStruct product);
void write_product_document(productStruct product, ofstream &file);
void write_all_products(Tlista &lista);
int main_menu ();

int main() {
	Tlista lista = NULL;
	read_products_document(lista);
	int opcion;
	do{
		opcion = main_menu();
		switch(opcion){
		 	case 1:
		 		insert_product(lista);
		 	break;
		 	case 2:
		 		update_product_menu(lista);
		 	break;
		 	case 3:
		 		delete_product_menu(lista);
		 	break;
		 	case 4:
		 		list_products(lista);
		 	break;
		 	default:
		 		cout << "Saliendo......" << endl;
		 	break;
		}
	}while(opcion != 0);
}

int main_menu(){
	system("cls"); 
	int opcion;
	cout << "\n\t\t MENU PRINCIPAL" << endl;
	cout << "\n\t Por favor seleccione una opcion:" <<endl<< endl;
	cout << "1 - Agregar producto"   << endl;
	cout << "2 - Editar producto"  << endl;
	cout << "3 - Eliminar producto"      << endl;
	cout << "4 - Listar productos" << endl;
	cout << "0 - Salir del programa"     << endl;
	cout << " \n Option: "; 
	cin >> opcion;
	return opcion;
}

productStruct read_product(string ID){
  	productStruct product;
  	cout << "\n\t Ingrese los datos del producto:" <<endl<< endl;
  	if(ID.empty()){
  		cout << "ID: ";
		getline(cin, product.ID);
	}else{
		product.ID = ID;
	}
	cout << "categoria: ";
	getline(cin, product.category);
	cout << "Nombre: ";
	getline(cin, product.name);
	cout << "Precio: ";
	cin >> product.price;
	cout << "Cantidad: ";
	cin >> product.quantity;
	return product;
}

/*---------------------------------Menu insertar producto-------------------------------------------------------------------*/
void insert_product (Tlista &lista)
{
	string ID;
  	productStruct product;
  	cin.ignore();
  	system("cls"); 
  	cout << "\n\t\t MENU INSERTAR PRODUCTO";
  	product = read_product("");
  
//	cout << "ID: " << product.ID
//	    << "; Categoria: " << product.category
//	    << "; Nombre: " << product.name
//	    << "; Precio: " << product.price
//	    << "; Cantidad: " << product.quantity
//	    << endl;

	save_product(product);
	    
	insert_product_to_list(lista, product);
}

void insert_product_to_list(Tlista &lista, productStruct dato)
{
    Tlista t, q = new(struct nodo);
 
    q->product  = dato;
    q->next = NULL;
 
    if(lista==NULL)
    {
        lista = q;
    }
    else
    {
        t = lista;
        while(t->next!=NULL)
        {
            t = t->next;
        }
        t->next = q;
    }
}

/*---------------------------------Menu editar producto-------------------------------------------------------------------*/
void update_product_menu(Tlista &lista){
	string ID;
	cin.ignore();
	system("cls");
	cout << "\n\t\t MENU EDITAR PRODUCTO\n\n";
	cout << "Ingrese el ID del producto que desea editar: ";
	getline(cin, ID);
	update_product(lista, ID);
}

void update_product(Tlista &lista, string ID){
	Tlista aux, ant;
    aux = lista;
 
    if(lista!=NULL)
    {
        while(aux != NULL)
        {
            if(aux->product.ID == ID)
            {
            	cout<<"producto encontrado: "<<endl;
            	write_listing_header();
            	show_product(aux->product);
                aux->product = read_product(ID);
                write_all_products(lista);
                cout<<"El producto con ID " <<ID<< " ha sido actualizado\n";
                cout << "\n";
				system("pause");
                return;
            }
            aux = aux->next;
        }
        cout<<"El producto con ID " <<ID<< " no ha sido encontrado\n";
        cout << "\n";
		system("pause");
    }
    else {
    	cout<<" Lista vacia..!\n";
        cout << "\n";
		system("pause");
	} 
}

/*---------------------------------Menu eliminar producto-------------------------------------------------------------------*/
void delete_product_menu(Tlista &lista){
	string ID;
	cin.ignore();
	system("cls");
	cout << "\n\t\t MENU ELIMINAR PRODUCTOS\n\n";
	cout << "Ingrese el ID del producto que desea eliminar: ";
	getline(cin, ID);
	delete_product(lista, ID);
}

void delete_product(Tlista &lista, string ID)
{
    Tlista aux, ant;
    aux = lista;
 
    if(lista!=NULL)
    {
        while(aux != NULL)
        {
            if(aux->product.ID == ID)
            {
                if(aux == lista)
                    lista = lista->next;
                else
                    ant->next = aux->next;
 
                delete(aux);
                write_all_products(lista);
                cout<<"El producto con ID " <<ID<< " ha sido eliminado\n";
                cout << "\n";
				system("pause");
                return;
            }
            ant = aux;
            aux = aux->next;
        }
        cout<<"El producto con ID " <<ID<< " no ha sido encontrado\n";
        cout << "\n";
		system("pause");
    }
    else {
    	cout<<" Lista vacia..!\n";
        cout << "\n";
		system("pause");
	} 
}

/*---------------------------------Menu listar productos-------------------------------------------------------------------*/
void write_listing_header()
{
	cout << endl;
	cout << "  ID    |     Nombre     |    Categoria    |    Precio    |     Quantity   " << endl;
	cout << "---------------------------------------------------------------------------" << endl;
}

void show_product (productStruct p)
{
  cout << setw(4)  << p.ID;
  cout << setw(18) << p.name;
  cout << setw(15) << p.category;
  cout << setw(15) << p.price;
  cout << setw(15) << p.quantity;
    cout << endl;
}

void list_products(Tlista &lista){
	Tlista t;
	if(lista==NULL)
    {
        cout << "No hay productos en la lista" << endl;
        cout << "\n";
	    system("pause");
    }else{
    	system("cls");
		cout << "\n\t\t MENU LISTAR PRODUCTOS\n";
    	write_listing_header();
		t = lista;
	    do
	    {
	    	show_product(t->product);
	        t = t->next;
	    }while(t != NULL);
	    cout << "\n";
		system("pause");
	}
}

/*-----------------------------------------------Funciones para documentos---------------------------------------------*/
void read_products_document(Tlista &lista){
    string nombre = DOCUMENT_NAME;
    string linea;
 
    ifstream fichero(nombre.c_str());
    if( fichero.fail() )
    {
        cout << "No existe el fichero!" << endl;
        exit(1);
    }
 
    do
    {
        getline(fichero,linea);
        bool emptyLine = linea.empty();
        if(!linea.empty()){
        	productStruct product;
	    	string datosArray [5];
	    	int len = linea.size() +1;
	    	int index = 0;
	    	string dato = "";
			for(int i = 0;i < len; i++)
			{
				if(linea[i] != ',' && linea[i] != ';'){
					dato = dato + linea[i];	
				}else{
					datosArray[index] = dato;
					index++;
					dato = "";
				}
			}
//			cout << "\n\n " << endl;
//			cout << "datos: " << datosArray[0]<< endl;
//			cout << "datos: " << datosArray[1]<< endl;
//			cout << "datos: " << datosArray[2]<< endl;
//			cout << "datos: " << datosArray[3]<< endl;
//			cout << "datos: " << datosArray[4]<< endl;
			product.ID = datosArray[0];
			product.name = datosArray[1];
			product.category = datosArray[2];
			product.price = stof(datosArray[3]);
			product.quantity = stoi(datosArray[4]);
			insert_product_to_list(lista, product); 
		}
      	
    }while (! fichero.eof());
    fichero.close();
}

void save_product(productStruct product){
	string nombre = DOCUMENT_NAME;
	ofstream file(nombre.c_str(), ios_base::app);
	if (file.fail())
    cerr << "Error al abrir el archivo: Pruebas.txt" << endl;
    else{
		write_product_document(product, file);
		file.close();
	}
}

void write_product_document(productStruct product, ofstream &file){
    file << endl << product.ID << ","
	<< product.name << ","
	<< product.category << ","
	<< product.price << ","
	<< product.quantity << ";";
}

void write_all_products(Tlista &lista){
	Tlista aux;
	aux = lista;
	string nombre = DOCUMENT_NAME;
	ofstream file(nombre.c_str());
    do
    {
    	write_product_document(aux->product, file);
        aux = aux->next;
    }while(aux != NULL);
    file.close();
}
