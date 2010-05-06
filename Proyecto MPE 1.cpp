#include <cmath>
#include <time.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <tuple>
#include <utility>
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
		for(int n = 0; n < 500; n++){
			pos = rand() % 5 + 0;
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
};

Capa::Capa(int n){
	numero_neuronas = n;
	
	for(int i = 0; i < numero_neuronas; i++){
		Perceptron nueva_neurona = Perceptron(0.0, 0.07);
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
	//srand(42);
	
	vector<vector<int>> entrada_a = 
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
	
	
	vector<vector<int>> entrada_e = 
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
	
	vector<vector<int>> entrada_i = 
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
	
	vector<vector<int>> entrada_o = 
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
	
	vector<vector<int>> entrada_u = 
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
	
	
	vector<vector<int>> entrada_a_kevin =
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	
	vector<vector<int>> entrada_e_kevin =
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	
	vector<vector<int>> entrada_i_kevin =
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	
	vector<vector<int>> entrada_o_kevin =
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	
	vector<vector<int>> entrada_u_kevin =
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	pair<vector<vector<int>>, vector<int>> par_a(entrada_a, {1,0,0,0,0});
	pair<vector<vector<int>>, vector<int>> par_e(entrada_e, {0,1,0,0,0});
	pair<vector<vector<int>>, vector<int>> par_i(entrada_i, {0,0,1,0,0});
	pair<vector<vector<int>>, vector<int>> par_o(entrada_o, {0,0,0,1,0});
	pair<vector<vector<int>>, vector<int>> par_u(entrada_u, {0,0,0,0,1});
	
	
	vector<pair<vector<vector<int>>, vector<int>>> ER =
	{
		par_a,
		par_e,
		par_i,
		par_o,
		par_u
	};
	
	
	
	Capa capa = Capa(5);
	cout << "Procesando letra a" << endl;
	capa.procesar(entrada_a);
	resultadoFinal(capa.getMaximoResultado());
	
	cout << "Procesando letra e" << endl;
	capa.procesar(entrada_e);
	resultadoFinal(capa.getMaximoResultado());
	
	cout << "Procesando letra i" << endl;
	capa.procesar(entrada_i);
	resultadoFinal(capa.getMaximoResultado());
	
	cout << "Procesando letra o" << endl;
	capa.procesar(entrada_o);
	resultadoFinal(capa.getMaximoResultado());
	
	cout << "Procesando letra u" << endl;
	capa.procesar(entrada_u);
	resultadoFinal(capa.getMaximoResultado());
	
	cout << endl << "Entrenando..." << endl ;
	capa.entrenar(ER);
	cout << "Fin del Entrenamiento" << endl << endl;
	
	cout << "Procesando letra a" << endl;
	capa.procesar(entrada_a);
	resultadoFinal(capa.getMaximoResultado());
	
	cout << "Procesando letra e" << endl;
	capa.procesar(entrada_e);
	resultadoFinal(capa.getMaximoResultado());
	
	cout << "Procesando letra i" << endl;
	capa.procesar(entrada_i);
	resultadoFinal(capa.getMaximoResultado());
	
	cout << "Procesando letra o" << endl;
	capa.procesar(entrada_o);
	resultadoFinal(capa.getMaximoResultado());
	
	cout << "Procesando letra u" << endl;
	capa.procesar(entrada_u);
	resultadoFinal(capa.getMaximoResultado());
	
	
	return 0;
}
