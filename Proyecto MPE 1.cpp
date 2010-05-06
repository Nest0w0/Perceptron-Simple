#include <cmath>
#include <time.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <tuple>
using namespace std;

#define NUM_FILAS 16
#define NUM_COLUMNAS 10

class Perceptron{
	double umbral;
	double pesos [NUM_FILAS][NUM_COLUMNAS];
	double razon_aprendizaje;
	// Añadir: Valor de aprendizaje
	
	public:
		Perceptron(double u, double r);
		
		double suma(int entradas[NUM_FILAS][NUM_COLUMNAS]){
			double sumatoria = 0;
			
			for(int i = 0; i < NUM_FILAS; i++){
				for(int j = 0; j < NUM_COLUMNAS; j++){
					sumatoria += entradas[i][j]*pesos[i][j];
				}
			}
			
			return sumatoria - umbral;
		}
		
		double salida(int entradas[NUM_FILAS][NUM_COLUMNAS]){
			return sigmoide(suma(entradas));
		}
		
		double sigmoide(double sumatoria){
			return 1/(1 + exp(-sumatoria));
		}
		
		void ajustarPesos(int valor_esperado, int valor_obtenido, int entradas[NUM_FILAS][NUM_COLUMNAS]){
			for(int i = 0; i < NUM_FILAS; i++){
				for(int j = 0; j < NUM_FILAS; j++){
					pesos[i][j] += entradas[i][j]*razon_aprendizaje*(valor_esperado - valor_obtenido);
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

class Capa{
	int numero_neuronas;
	vector<Perceptron> neuronas;
	vector<double> resultado;
	vector<int> salida;	
	
	public:
		Capa(int numero_neuronas);
		
	void procesar(int entrada[NUM_FILAS][NUM_COLUMNAS]){
		vector<double> nuevo_resultado;
		for(int i = 0; i < numero_neuronas; i++){
			nuevo_resultado.push_back(neuronas[i].salida(entrada));
		}
		resultado = nuevo_resultado;
	}
	
	int getMaximaSalida(){
		double maxima = -9.9;
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
	
	
	vector<Perceptron> getNeuronas(){
		return neuronas;
	}
	
	vector<double> getResultado(){
		return resultado;
	}
};

Capa::Capa(int n){
	numero_neuronas = n;
	
	for(int i = 0; i < numero_neuronas; i++){
		Perceptron nueva_neurona = Perceptron(50.0, 0.07);
		neuronas.push_back(nueva_neurona);
	}
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

int main(){
	srand(time(NULL));
	
	int entrada_a[NUM_FILAS][NUM_COLUMNAS] = 
	{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,1,1,1,0,0,1,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,1,0,0,1,1,1,0},
	{0,0,1,1,1,1,1,1,1,0},
	{0,0,0,1,1,1,1,0,1,1},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	};
	
	
	int entrada_e[NUM_FILAS][NUM_COLUMNAS] = 
	{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,1,1,1,1,1,1,0},
	{0,1,1,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,0,0,0},
	{0,1,1,1,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	};
	
	int entrada_i[NUM_FILAS][NUM_COLUMNAS] = 
	{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	};
	
	int entrada_o[NUM_FILAS][NUM_COLUMNAS] = 
	{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,1,1,1,0,0,1,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,1,0,0,1,1,1,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	};
	
	int entrada_u[NUM_FILAS][NUM_COLUMNAS] = 
	{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,0,0,0,0,1,1,0},
	{0,1,1,1,0,0,1,1,1,0},
	{0,0,1,1,1,1,1,1,1,0},
	{0,0,0,1,1,1,1,0,1,1},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	};
	
	tuple<int, float> tupla(2, 0.5);
	cout << get<0>(tupla) << endl;
	cout << get<1>(tupla) << endl;
	
	
	vector<int> salida_a = {1,0,0,0,0};
	tuple<vector<int>, vector<int>> juan({1,2,3,4,5}, salida_a);

	return 0;
}
