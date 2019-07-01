#include "mapa.h"

map::map(std::string usuario, objetos *object, enemigos *enemigo, int filas, int columnas) {
	NumFilas = filas;
	NumColumnas = columnas;
	std::ifstream fitxer;
	for (int i = 0; i < NumColumnas; i++) {
		for (int j = 0; j < NumFilas; j++) {
			fitxer.open("datos/usuarios/" + usuario + "/zonas/" + std::to_string(i) +"_"+ std::to_string(j)+ ".txt");
			if (fitxer.is_open())
			{
				std::string e; //simula el nombre de la variable para no guardarla
				int x;
				int y;
				int tipo;	//0=mar, 1=isla
				int enemg;
				int NPC;
				int tesoro;
				int objeto;
				int cantidad;
				x = i;
				y = j;
				fitxer >> e >> tipo >> e >> enemg >> e >> NPC >> e >> tesoro >> e >> objeto >> e >> cantidad;
				_zona[i + 5*j] = zonas(x, y, tipo, enemg, NPC, tesoro, objeto, cantidad, object, enemigo);
				fitxer.close();
			}
		}
	}
	fitxer.open("datos/mapa/mapa.txt");
	if (fitxer.is_open()) {
		for (int i = 0; i < NumZonas; i++) {
			fitxer >> _mapa[i];
		}
		fitxer.close();
	}
}

void map::mostarMapa(const int &x, const int &y) {
	for (int i = 0; i < NumFilas; i++) {
		for(int j = 0; j < NumColumnas; j++) {
			std::cout << ":-: ";
		}
		std::cout << std::endl;
		for (int j = 0; j < NumColumnas; j++) {
			if (i == y && j == x) {
				std::cout << "|" << "X" << "| ";
			}
			else {
				std::cout << "|" << _mapa[i * 5 + j] << "| ";
			}
		}

		std::cout << std::endl;
	}
	for (int j = 0; j < NumColumnas; j++) {
		std::cout << ":-: ";
	}
	std::cout << std::endl;
}

void map::Zoom(int zona) {
	int limite = 3; //(se mostrará zoom de (limite x limite) )
	int limiteXizq, limiteXder, limiteYarriba, limiteYabajo;
	if ((zona % NumFilas) - limite >= 0) {
		limiteXizq = limite;
	}
	else {
		//Estamos fuera por la izquierda
		limiteXizq = -(0-(zona % NumFilas) );
	}

	if ((zona % NumFilas) + limite < NumColumnas) {
		//correcto
		limiteXder = limite;
	}
	else {
		//Estamos fuera por la derecha
		limiteXder = limite - ((zona % NumFilas) + limite - (NumColumnas - 1));
	}

	if ((zona / NumFilas) - limite >= 0) {
		limiteYarriba = limite;
	}
	else {
		limiteYarriba = -(0-(zona / NumFilas));
	}

	if ((zona / NumFilas) + limite < NumFilas) {
		limiteYabajo = limite;
	}
	else {
		limiteYabajo = limite-((zona / NumFilas) + limite -(NumFilas-1));
	}
	//std::cout << limiteXizq << " , " << limiteXder << " , " << limiteYarriba << " , " << limiteYabajo << std::endl;
	
	for (int y = ((zona / NumFilas) - limiteYarriba) ; y <= ((zona / NumFilas) + limiteYabajo); y++) {
		for (int i = ((zona % NumFilas) - limiteXizq); i <= ((zona % NumFilas) + limiteXder); i++) {
			std::cout << ":-: ";
		}
		std::cout << std::endl;
		for (int x = ((zona % NumFilas)-limiteXizq); x <= ((zona % NumFilas) + limiteXder); x++) {
			
			//std::cout <<  y*NumFilas+x << "  ";
			if (y*NumFilas + x == zona) {
				std::cout << "|" << "X" << "| ";
			}
			else {
				std::cout << "|" << _zona[y*NumFilas + x].getTipo() << "| ";

			}
		}
		std::cout << std::endl;
	}
	for (int i = ((zona % NumFilas) - limiteXizq); i <= ((zona % NumFilas) + limiteXder); i++) {
		std::cout << ":-: ";
	}
	std::cout << std::endl;

}
