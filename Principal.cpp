# include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <stdio.h> // para usar texbox
#include <windows.h> // Libreria que me permite utilizar el "Sleep(tiempo)"---> sirve para hacer una pausa de x tiempo
using namespace std;

#include <fstream> // para activar las funciones de manejo de texto
using std::ifstream;

//libreria para el menu principal y para el diseño del ahorcado
# include "Menus.h"

//para el ingreso de palabras
void Ingreso_palabra( int );

//para cambiar de minisculas a mayusculas
void CambioMayusMinus(char *);

//imprime el avance de la palabra
void valor_palabra(const char*,int&);

/*nombre del archivo, donde se colocara la palabra
retorna elarreglo dinamico de cadenas. int& tameño del arreglo.*/
char** cargar_palabra(const char*,char*,int&);

//Para el Ingreso de Una nueva letra
bool nueva_letra(const char*, char*, char);

void main()
{
	srand(time(0));

	char** palabras = NULL;
	char palabraactual[100];
	char archivo1[30];
	char cadena[100];
	char d;
	int cantidadpalabras = 40;
	int maximointentos;
	int tam = 0;
	int contador = 0;
	int longi;
	int msgboxID;
	
	bool load = false;
	
	int opcionM; //Para menu principal
	int llamar = 1; // llama al ingreso de palabras

	do
	{
		//para mostrar el "_" para cada letra de cada palabra
		for(int i=0; i<100; i++)
		{
			cadena[i] = '2';
		}

		//inicializamos el menu
		opcionM = Menu_Principal();
		
		switch ( opcionM )
		{
			// llamamos a la funcion de ingreso de palabras
			case 1:
				system("cls");
				Ingreso_palabra( llamar );
				break;

			// Empieza el Juego
			case 2:
				//inicializado de variables
				d = NULL;
				cadena[100] = NULL;
				palabras = NULL;
				palabraactual[100] = NULL;
				archivo1[30] = NULL;
				tam = 0;
				contador = 0;
				longi = 0;
				
				msgboxID = MessageBox(NULL,TEXT("Solo utiliza las las letras de la A - Z sin ENTER"),TEXT("INFORMACION"),MB_ICONASTERISK | MB_OK );
				// cargamos el archivo de texto
				if (!load)
				{
					cin.getline(archivo1,30);
					if (!archivo1[0])
					strcpy(archivo1,"ahorcado.txt");
				}
				
				//Cargamos la palabra que se escoge aleatoriamente
				palabras = cargar_palabra(archivo1,palabraactual,cantidadpalabras); 
			    
				while(true)
					if(palabraactual[tam])
						tam++;
				else
					break;

				maximointentos = 6; // Inicializamos los inteneto 
				system("cls");
				//Empieza y corremos el juego para el Ingreso de palabras
				do
				{
					system("color f0");
					tranca();// la base del ahorcado
					
					gotoxy(5,23);cout <<"Le Quedan " << maximointentos << " intentos";
					
					// llamamos la funcion que nos separa la palabra
					valor_palabra(cadena,tam); 
					
					//con esta separamos la pabra para no limpiar la pantalla y no se nos amontonen las letras
					longi = strlen(palabraactual);
					for (int P=1; P<=longi; P++)
					{
						cout << " ";
					}
					// Nos pide ingresar una letra
					gotoxy(5,3);cout << "Introduzca una letra: ";
					d = getch(); // solo toma un caracter, alfanumerio, un espacio o un enter
					d = toupper(d); // nos convierte la letra seleccionada a mayusculas 
					gotoxy(27,3);cout << d; // motramos en pantalla el caracter seleccionado
					
					if(!nueva_letra(palabraactual,cadena,d))
						maximointentos--;
					contador = 0;
					
					for(int pp=0; pp<tam; pp++)
						if(cadena[pp] == palabraactual[pp])
						contador++;	
			
					if(contador == tam)
					{
						gotoxy(5,15);cout << "H A S  G A N A D O !";
						gotoxy(5,6);cout << palabraactual << "                               ";
						gotoxy(5,24);system("pause");
						break;
					}
					
					//Muestra cada parte del cuerpo
					if (maximointentos == 5)
						cabeza();
					if (maximointentos == 4)
						cuerpo();
					if (maximointentos == 3)
						brazo_derecho();
					if (maximointentos == 2)
						brazo_izquierdo();
					if (maximointentos == 1)
						pie_derecho();
					if (maximointentos == 0)
						pie_izquierdo();
					
				}while( maximointentos > 0 );// FIN DEL WHILE

				if( maximointentos <= 0 )
				{
					gotoxy(5,15);cout << "H A S  P E R D I D O !" << endl;
					gotoxy(42,6);cout <<  " :   0   0   ; " << endl;
					gotoxy(42,9);cout <<  "  \\  (--)   /  " << endl;   
					gotoxy(5,16);cout << "La palabra era: " << palabraactual << endl;
					gotoxy(5,24);system("pause");
				}

				for( int i=0; i<100 ;i++)
				{
					cadena[i]='2';
				}
				break;

			case 3:
				break;

			default:
				system("cls");
				gotoxy(28,12);cout << "ERROR. opcion no valida" << endl;
				getch();
				break;
		} //fin del switch
	}while( opcionM != 3 ); //fin del do while
}// fin del main()

void Ingreso_palabra( int Ingreso )
{
	char cadena[128][128];//bidemencional, letras palabras, como decir filas columnas
	int x = 0;
	int cantidad = 0; // para la capturar cantidad de palabras
	int palabras;
	// Crea un fichero de salida
	ofstream guardar; //
	guardar.open ("ahorcado.txt", ios::app);
	
	gotoxy(30,1);cout << "INGRESO DE PALABRAS";

	gotoxy(5,5);cout << "Cuantas palabras va a ingresar: ";
	cin >> cantidad;

	system("cls");
	for (x=0; x<cantidad; x++)   
	{
		cout << "palabra " << x << ": ";
		cin >> cadena[x];
		CambioMayusMinus(cadena[x]); // llamamos a la funcion para que nos guarde toas las palabras a mayusculas
	}
	
	//nos muestra todos lo arreglos que tenemos guardados
	system("cls");
	for (int w=0; w<x; w++) 
	{
		cout << cadena[w] << endl;
		guardar << cadena[w] << endl; // mandar a guardar al texto
	}
	system("pause");

}

/*el primer parametro representa el nombre del archivo, donde se colocara las palabras
retorna elarreglo dinamico de cadenas.El tercer parametro guarda el tamaño del arreglo*/
char** cargar_palabra(const char* archivo, char* palabra, int& tam)
{
	ifstream words(archivo);
	int cuenta;
	if(!words)
	{
		cout <<"No se puede abrir el archivo no existe"<<endl;
		system("Pause");
	}
	int i = rand()% 30;//numero de palabras posibles;
	for (int k=0; k<=i; k++)
	{
		words >> palabra;
	}
	char** array = new char*[tam];
	if(!array)
	{
		cout << "no hay memoria";
		system("Pause");
	}
	for(int t=0; t< 25; t++)
	{
		array[t] = NULL;
	}

	int y = 0;
	while(palabra[y])
	{
		array[y] = new char;
		*array[y] = palabra[y];
		y++;
	}	
	words.close();
	return array;
}

/*toma el caracter del tercer parametro y verifica si esta en la palabra que va
 en el primer parametro, si esta entonces lo colocara en la o las posiciones adecuadas en 
 la cadena que va en el segundo parametro, retorna true si esta o false si no esta*/
bool nueva_letra(const char* p_actual, char* act, char letra)
{
	int q = 0;
	bool retval = false;

	while(p_actual[q])
	{
		if (letra == p_actual[q])
		{
			act[q] = letra;
			retval = true;
		}
		q++;
	}
return retval;
}

/*Imprime el avance que lleva la palabra*/
void valor_palabra(const char* temp, int& lim)
{
	gotoxy(5,6);
	for(int s=0; s<lim; s++)
		if(temp[s] == '2')
			cout << "_" << " ";
		else
		 cout << temp[s];
}


//funcio para cambiar toda la cadena de caracteres a mayusculas
void CambioMayusMinus(char *PtrCadena)
{
	while( *PtrCadena != '\0')
	{
		if(islower(*PtrCadena))
			*PtrCadena = toupper(*PtrCadena);
		else
			*PtrCadena;

		PtrCadena++;
	}
}