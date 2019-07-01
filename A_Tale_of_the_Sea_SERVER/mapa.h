#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "zonas.h"
const int NumZonas = 25;


class map {
public:
	map(std::string usuari, int partida, objetos *object, enemigos *enemigo,int filas, int columnas);
	map() { _mapa[NumZonas] = 0; }
	void mostarMapa(const int &x,const int &y, std::string &s);
	void mostarZona(const int &pos, std::string &s) { _zona[pos].mostrarZona(s); }
	int getLimitX() { return NumFilas; }
	int getLimitY() { return NumColumnas; }
	int getEnemigo(int id) { return _zona[id].getEnemigo(); }
	int getObjetoZona(int id) { return _zona[id].getObjetoZona(); }
	int getCantObjZona(int id) { return _zona[id].getCantObjZona(); }
	void Zoom(int zona, std::string &s);
	int getNPC(int zona) { return _zona[zona].getNpc(); }
	void eliminarEnemigo(int zona) { _zona[zona].eliminarEnemigo(); }
private:
	zonas _zona[NumZonas];
	int _mapa[NumZonas];
	int NumFilas;
	int NumColumnas;

};