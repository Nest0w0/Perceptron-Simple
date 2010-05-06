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
}

vector<pair<vector<vector<int>>, vector<int>>> leerEjemplosUnaLetra(string filepath){
	vector<pair<vector<vector<int>>, vector<int>>> ER;
	vector<vector<int>> matriz;
	
	ifstream archivo_entrada;
	archivo_entrada.open(filepath);
	string linea;
	int i , j = 0;
	while(getline(archivo_entrada, linea)){
		if(linea != "&"){
			stringstream ss (linea);
			string digito;
			j = 0;
			vector<int> fila;
			while(std::getline(ss, digito, ' ')){
				fila.push_back(stoi(digito)); 
				j++;
			}
			matriz.push_back(fila);
			i++;
		}else{
			i = 0;
			vector<int> vector_esperado = getResultadoEsperadoDeNombreDeArchivo(filepath);
			pair<vector<vector<int>>, vector<int>> par(matriz, vector_esperado);
			ER.push_back(par);
			matriz.clear();
		}
	}
	archivo_entrada.close();
	return ER;
}

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
	return pesos;
}

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
		
		void toStringPesos(){
			cout << "================================================================================" << endl;
			for(int i = 0; i < NUM_FILAS; i++){
				for(int j = 0; j < NUM_COLUMNAS; j++){
					cout << pesos[i][j] << " ";
				}
				cout << endl;
			}
			cout << "================================================================================" << endl;
		}
		
		double get_umbral(){
			return umbral;
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

Perceptron::Perceptron(double u, double r){
	umbral = u;
	razon_aprendizaje = r;
	
	for(int i = 0; i < NUM_FILAS; i++){
		for(int j = 0; j < NUM_COLUMNAS; j++){
			pesos[i][j] = -1.0 + (double)(rand()) / ((double) RAND_MAX/(1 - (-1)));
			//((double) rand())/RAND_MAX;
		}
	}
}

Perceptron::Perceptron(double u, double r, vector<vector<double>> matriz_pesos){
	umbral = u;
	razon_aprendizaje = r;
	
	for(int i = 0; i < NUM_FILAS; i++){
		for(int j = 0; j < NUM_COLUMNAS; j++){
			pesos[i][j] = matriz_pesos[i][j];
		}
	}
}

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
		int pos;
		for(int n = 0; n < 1000; n++){
			pos = rand() % (ER.size()) + 0;
			procesar(ER[pos].first);
			for(int i = 0; i < 4; i++){
				if(salida[i] != ER[pos].second[i]){
					neuronas[i].ajustarPesos(ER[pos].second[i], salida[i], ER[pos].first);
				}
			}
		}
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

Capa::Capa(int n){
	numero_neuronas = n;
	
	for(int i = 0; i < numero_neuronas; i++){
		Perceptron nueva_neurona = Perceptron(0.0, 0.07);
		neuronas.push_back(nueva_neurona);
	}
}

Capa::Capa(int n, vector<vector<vector<double>>> lista_matrices_pesos){
	numero_neuronas = n;
	
	for(int i = 0; i < numero_neuronas; i++){
		Perceptron nueva_neurona = Perceptron(0.0, 0.07, lista_matrices_pesos[i]);
		neuronas.push_back(nueva_neurona);
	}
}

int main(){
	//srand(time(NULL));
	srand(42);
	
	ifstream archivo_pesos;
	archivo_pesos.open("./pesos.txt");
	
	if(archivo_pesos.is_open()){
		archivo_pesos.close();
		vector<vector<vector<double>>> lista_pesos = leerPesos();
		Capa capa = Capa(5, lista_pesos);
		vector<vector<int>> vocal = leerEntrada();
		capa.procesar(vocal);
		resultadoFinal(capa.getMaximoResultado());
	}else{
		archivo_pesos.close();
		Capa capa = Capa(5);
		vector<pair<vector<vector<int>>, vector<int>>> ER = leerEjemplos();
		capa.entrenar(ER);
		vector<vector<int>> vocal = leerEntrada();
		capa.procesar(vocal);
		resultadoFinal(capa.getMaximoResultado());
		capa.guardarBaseConocimientos();
	}

	return 0;
}
