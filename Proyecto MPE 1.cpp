#include <cmath>
#include <time.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <utility>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

#define NUM_FILAS 16
#define NUM_COLUMNAS 10

/*FUNCIONES AUXILIARES*/

//Función para retornar la salida esperada, en base al nombre de un archivo.txt
vector<int> getResultadoEsperadoDeNombreDeArchivo(string filepath){
	if(filepath == "./a.txt"){
		return {1,0,0,0,0};
	}
	else if(filepath == "./e.txt"){
		return {0,1,0,0,0};
	}
	else if(filepath == "./i.txt"){
		return {0,0,1,0,0};
	}
	else if(filepath == "./o.txt"){
		return {0,0,0,1,0};
	}
	else if(filepath == "./u.txt"){
		return {0,0,0,0,1};
	}
	//Perdón, es que el switch de C++ no acepta cadenas
}

/*Función para retornar todas las vocales contenidas en un archivo .txt, así como
la salida esperada de dicha vocal*/
vector<pair<vector<vector<int>>, vector<int>>> leerEjemplosUnaLetra(string filepath){
	vector<pair<vector<vector<int>>, vector<int>>> ER;
	vector<vector<int>> matriz;
	
	ifstream archivo_entrada;
	archivo_entrada.open(filepath);
	string linea;
	while(getline(archivo_entrada, linea)){
		if(linea != "&"){
			stringstream ss (linea);
			string digito;
			vector<int> fila;
			
			/*getline(ss, digito, ' ') separa la linea por espacios, y copia los valores separados en
			la variable digito*/
			while(std::getline(ss, digito, ' ')){
				fila.push_back(stoi(digito)); 
				
			}
			
			matriz.push_back(fila);
			
		}else{
			vector<int> vector_esperado = getResultadoEsperadoDeNombreDeArchivo(filepath);
			pair<vector<vector<int>>, vector<int>> par(matriz, vector_esperado);
			ER.push_back(par);
			matriz.clear();
		}
	}
	archivo_entrada.close();
	return ER;
}

/*Función para retornar todas las vocales contenidas en todos los archivos .txt.
Básicamente concatena los resultados de la función anterior*/
vector<pair<vector<vector<int>>, vector<int>>> leerEjemplos(){
	vector<pair<vector<vector<int>>, vector<int>>> ERa = leerEjemplosUnaLetra("./a.txt");
	vector<pair<vector<vector<int>>, vector<int>>> ERe = leerEjemplosUnaLetra("./e.txt");
	vector<pair<vector<vector<int>>, vector<int>>> ERi = leerEjemplosUnaLetra("./i.txt");
	vector<pair<vector<vector<int>>, vector<int>>> ERo = leerEjemplosUnaLetra("./o.txt");
	vector<pair<vector<vector<int>>, vector<int>>> ERu = leerEjemplosUnaLetra("./u.txt");
	
	vector<pair<vector<vector<int>>, vector<int>>> ER = {};
	
	ER.insert(ER.end(), ERa.begin(), ERa.end());
	ER.insert(ER.end(), ERe.begin(), ERe.end());
	ER.insert(ER.end(), ERi.begin(), ERi.end());
	ER.insert(ER.end(), ERo.begin(), ERo.end());
	ER.insert(ER.end(), ERu.begin(), ERu.end());
	
	
	return ER;
}
/*Función para leer la vocal que se encuentra en el archivo "entrada.txt"
la cual es la vocal que el usuario desea que la red reconozca*/
vector<vector<int>> leerEntrada(){
	vector<vector<int>> matriz;
	
	ifstream archivo_entrada;
	archivo_entrada.open("./entrada.txt");
	string linea;
	while(getline(archivo_entrada, linea)){
		if(linea != "&"){
			stringstream ss (linea);
			string digito;
			vector<int> fila;
			while(std::getline(ss, digito, ' ')){
				fila.push_back(stoi(digito)); 
			}
			matriz.push_back(fila);
		}
	}
	archivo_entrada.close();
	return matriz;
}

/*Función para guardar las matrices de pesos en un archvo "pesos.txt"
el cual actuará como la base de conocimientos para las siguientes
ejecuciones del programa */
void escribirPesos(vector<vector<vector<double>>> matrices_pesos){
	ofstream archivo_salida;
	archivo_salida.open("./pesos.txt");
	
	vector<vector<double>> matriz;
	for(int n = 0; n < matrices_pesos.size(); n++){
		matriz = matrices_pesos[n];
		for(int i = 0;  i < matriz.size(); i++){
			for(int j = 0; j < matriz[i].size(); j++){
				archivo_salida << matriz[i][j];
				if(j != (matriz[i].size() - 1)){
					archivo_salida <<  " ";
				}
			}
			archivo_salida << endl;
		}
		archivo_salida << '&' << endl;	
	}
	
	archivo_salida.close();
}

/*Función para leer las matrices de pesos guardadas en el archivo "pesos.txt"*/
vector<vector<vector<double>>> leerPesos(){
	vector<vector<vector<double>>> pesos;
	vector<vector<double>> matriz;
	
	ifstream archivo_entrada;
	archivo_entrada.open("./pesos.txt");
	string linea;
	while(getline(archivo_entrada, linea)){
		if(linea != "&" && linea != ""){
			stringstream ss (linea);
			string digito;
			vector<double> fila;
			while(std::getline(ss, digito, ' ')){
				fila.push_back(stod(digito));
			}
			matriz.push_back(fila);
		}else{
			pesos.push_back(matriz);
			matriz.clear();
		}
	}
	archivo_entrada.close();
	cout << "Base de conocimiento cargada exitosamente" << endl;
	return pesos;
}

/*Función para dar el resultado final al usuario.
Básicamente es la interfaz de salida, funciona recibiendo un número
entre 0 y 4, que representa la posicion de la neurona que tuvo el
resultado más alto luego de procesar la entrada. A partir de esto
un print informa al usuario de la conclusión de la red. */
void resultadoFinal(int pos_max){
	switch (pos_max){
		case 0:
			cout << "Es una a." << endl;
			break;
		case 1:
			cout << "Es una e." << endl;
			break;
		case 2:
			cout << "Es una i." << endl;
			break;
		case 3:
			cout << "Es una o." << endl;
			break;
		case 4:
			cout << "Es una u." << endl;
			break;
		}
}

/*Clase Perceptrón (o Neurona), su atributo más importante es el de los pesos,
el cual es una matriz de 16x10. Cada celda de esta matriz está asociada con un
digito de la entrada (o un pixel si fuera una imagen)*/
class Perceptron{
	double umbral;
	double pesos [NUM_FILAS][NUM_COLUMNAS];
	double razon_aprendizaje;
	
	public:
		Perceptron(double u, double r);
		Perceptron(double u, double r, vector<vector<double>> matriz_pesos);
		
		double suma(vector<vector<int>> entrada){
			double sumatoria = 0;
			
			for(int i = 0; i < entrada.size(); i++){
				for(int j = 0; j < entrada[i].size(); j++){
					sumatoria += entrada[i][j]*pesos[i][j];
				}
			}
			
			return sumatoria + umbral;
		}
		
		double salida(vector<vector<int>> entradas){
			return sigmoide(suma(entradas));
		}
		
		double sigmoide(double sumatoria){
			return 1/(1 + exp(-sumatoria));
		}
		
		void ajustarPesos(int valor_esperado, int valor_obtenido, vector<vector<int>> entrada){
			for(int i = 0; i < NUM_FILAS; i++){
				for(int j = 0; j < NUM_COLUMNAS; j++){
					pesos[i][j] += entrada[i][j]*razon_aprendizaje*(valor_esperado - valor_obtenido);
				}
			}
		}
		
		vector<vector<double>> getPesos(){
			vector<vector<double>> matriz_pesos;
			vector<double> fila;
			for(int i = 0; i < NUM_FILAS; i++){
				for(int j = 0; j < NUM_COLUMNAS; j++){
					fila.push_back(pesos[i][j]);
				}
				matriz_pesos.push_back(fila);
				fila.clear();
			}
			return matriz_pesos;
		}
};

/*La clase Perceptrón tiene dos constructores.
El primero construye el Perceptrón con su matriz de pesos
llena de número aleatorios*/
Perceptron::Perceptron(double u, double r){
	umbral = u;
	razon_aprendizaje = r;
	
	for(int i = 0; i < NUM_FILAS; i++){
		for(int j = 0; j < NUM_COLUMNAS; j++){
			//Genera un número aleatorio real entre -1 y 1
			pesos[i][j] = -1.0 + (double)(rand()) / ((double) RAND_MAX/(1 - (-1)));
		}
	}
}

/*El segundo construye el Perceptrón a partir de una
matriz de pesos recibida por parámetro. De esta forma, el perceptrón
recupera el conocimiento adquirido en las ejecuciones previas*/
Perceptron::Perceptron(double u, double r, vector<vector<double>> matriz_pesos){
	umbral = u;
	razon_aprendizaje = r;
	
	for(int i = 0; i < NUM_FILAS; i++){
		for(int j = 0; j < NUM_COLUMNAS; j++){
			pesos[i][j] = matriz_pesos[i][j];
		}
	}
}

/*Clase Capa, sus atributos más importantes son:
1. Una lista de Perceptrones, que representan la capa en sí
2. Una lista de resultados, que recopila el resultado de la función de activación
de cada neurona en la capa
3. Una lista de salida, que tiene un 1 en la posicion del perceptrón cuya
función de activación tuvo un resultado más alto, y tiene 0's en todas las demás
posiciones*/
class Capa{
	int numero_neuronas;
	vector<Perceptron> neuronas;
	vector<double> resultado;
	vector<int> salida;	
	
	public:
		Capa(int numero_neuronas);
		Capa(int numero_neuronas, vector<vector<vector<double>>> lista_matrices_pesos);
		
	void procesar(vector<vector<int>> entrada){
		vector<double> nuevo_resultado;
		for(int i = 0; i < numero_neuronas; i++){
			nuevo_resultado.push_back(neuronas[i].salida(entrada));
		}
		resultado = nuevo_resultado;
		procesarResultadoASalida(getMaximoResultado());
	}
	
	int getMaximoResultado(){
		double maxima = -RAND_MAX;
		int posicion_maxima = 0;
		for(int i = 0; i < numero_neuronas; i++){
			if(resultado[i] > maxima){
				maxima = resultado[i];
				posicion_maxima = i;
			}
		}
		return posicion_maxima;
	}
		
	void procesarResultadoASalida(int pos_max){
		vector<int> nueva_salida;
		for(int i = 0; i < numero_neuronas; i++){
			if(i == pos_max){
				nueva_salida.push_back(1);
			}else{
				nueva_salida.push_back(0);
			}
		}
		salida = nueva_salida;
	}
	
	void toStringResultado(){
		for(int i = 0; i < numero_neuronas; i++){
			cout<< resultado[i] << " ";
		}
		cout << endl;
	}
	
	void toStringSalida(){
		for(int i = 0; i < numero_neuronas; i++){
			cout<< salida[i] << " ";
		}
		cout << endl;
	}
	
	
	void entrenar(vector<pair<vector<vector<int>>, vector<int>>> ER){
		cout << "Iniciando entrenamiento" << endl;
		int pos;
		int iteraciones = 500;
		/*El entrenamiento se va a realizar 500 veces, o una cantidad
		de veces igual la longitud de la lista de Pares Entrada-Resultados
		multiplcada por 10, lo que sea mayor*/
		if(iteraciones < (ER.size()*10)){
			iteraciones = ER.size()*10;
		}
		
		for(int n = 0; n < iteraciones; n++){
			pos = rand() % (ER.size()) + 0;
			procesar(ER[pos].first);
			for(int i = 0; i < 4; i++){
				if(salida[i] != ER[pos].second[i]){
					neuronas[i].ajustarPesos(ER[pos].second[i], salida[i], ER[pos].first);
				}
			}
		}
		cout << "Entrenamiento terminado. ";
		cout << "Se guardara la base de conocimiento adquirida al terminar el programa" << endl;
	}
	
	vector<Perceptron> getNeuronas(){
		return neuronas;
	}
	
	vector<double> getResultado(){
		return resultado;
	}
	
	void guardarBaseConocimientos(){
		vector<vector<vector<double>>> lista_pesos;
		for(int n = 0; n < numero_neuronas; n++){
			lista_pesos.push_back(neuronas[n].getPesos());
		}
		
		escribirPesos(lista_pesos);
	}
};

/*La Clase Capa tiene dos constructores.
El primero inicia los pesos de cada uno de sus perceptrones aleatoriamente*/
Capa::Capa(int n){
	numero_neuronas = n;
	
	for(int i = 0; i < numero_neuronas; i++){
		Perceptron nueva_neurona = Perceptron(0.0, 0.07);
		neuronas.push_back(nueva_neurona);
	}
}

/*El segundo inicia los pesos de cada uno de sus perceptrones acorde
a los contenidos en el archivo "pesos.txt", recuperando la base de
conocimiento de la red*/
Capa::Capa(int n, vector<vector<vector<double>>> lista_matrices_pesos){
	numero_neuronas = n;
	
	for(int i = 0; i < numero_neuronas; i++){
		Perceptron nueva_neurona = Perceptron(0.0, 0.07, lista_matrices_pesos[i]);
		neuronas.push_back(nueva_neurona);
	}
}

int main(){
	/*
	Realizado por Nestor Aguilar (C.I: 28.316.308)
	
	Este programa requiere de dos elementos básicos para funcionar correctamente:
	
	1. Un archivo "entrada.txt" en su mismo directorio el cual contiene una matriz
	de 16x10, que contiene 0's y 1's, y representa la vocal que desea la red intente
	reconocer. Si desea cambiar la vocal que la red neuronal intenta reconocer, basta
	con sustituir la matriz que se encuentra en el archivo "entrada.txt" por la matriz 
	que represente la vocal que desea, y ejecutar el programa nuevamente.
	
	2. Un archivo "<vocal>.txt" en su mismo directorio por cada vocal, que contiene 
	matrices 16x10, que contienen 0's y 1's, y representan la vocal correspondiente 
	a su nombre de archivo (es decir "a.txt" contiene matrices que representan vocales a,
	"e.txt" contiene matrices que representan vocales e, y así sucesivamente), cada matriz
	terminada en un ampersand (&). Estos archivos son importantes porque se usarán como 
	ejemplo para el entrenamiento de la red neuronal. En la entrega del proyecto se
	suministraron archivos .txt para cada vocal con 15 o 16 ejemplos cada uno. Si desea 
	añadir o eliminar ejemplos para hacer un entrenamiento más o menos exhaustivo, 
	basta con añadir o eliminar dichas matrices de sus archivos correspondientes. 
	No olvide colocar un ampersand (&) al final.
	
	
	El flujo del programa es el siguiente:
	
	1. Buscará un archivo "pesos.txt" en el mismo directorio. Este archivo representa
	la base de conocimientos de la red neuronal.
	
	2. Si lo encuentra, procederá a cargar el archivo y crear la red neuronal con la
	base de conocimientos, para luego procesar la vocal contenida en el archivo "entrada.txt".
	
	3. Si no lo encuentra, procederá a crear la red neuronal con un estado inicial
	aleatorio, luego procederá a cargar los ejemplos y entrenar a la red con ellos.
	Una vez el entrenamiento haya terminado, procesará la vocal contenida en el archivo 
	"entrada.txt". Finalmente, guardará los pesos adquiridos luego del entrenamiento
	en un archivo "pesos.txt" recién creado, para las siguientes ejecuciones.
	
	En la entrega del proyecto, se suministró un archivo "pesos.txt" con la última
	base de conocimientos de la red, por lo que la primera ejecución de programa trabajará
	en base a estos conocimientos. Si desea probar el entrenamiento de la red neuronal,
	basta con eliminar el archivo "pesos.txt" del directorio.
	*/	
	
	srand(time(NULL));
	ifstream archivo_pesos;
	archivo_pesos.open("./pesos.txt");
	
	if(archivo_pesos.is_open()){
		archivo_pesos.close();
		vector<vector<vector<double>>> lista_pesos = leerPesos();
		Capa capa = Capa(5, lista_pesos);
		vector<vector<int>> vocal = leerEntrada();
		cout << "Procesando vocal..." << endl;
		capa.procesar(vocal);
		resultadoFinal(capa.getMaximoResultado());
	}else{
		archivo_pesos.close();
		Capa capa = Capa(5);
		vector<pair<vector<vector<int>>, vector<int>>> ER = leerEjemplos();
		capa.entrenar(ER);
		vector<vector<int>> vocal = leerEntrada();
		cout << "Procesando vocal..." << endl;
		capa.procesar(vocal);
		resultadoFinal(capa.getMaximoResultado());
		capa.guardarBaseConocimientos();
	}

	/*La Red Neuronal se llama "IAbdul"
	Salude a IAbdul antes de que se acabe su ejecución...*/
	return 0;
	/*Adiós IAbdul*/
}
