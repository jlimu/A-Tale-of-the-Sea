#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "misiones.h"
#include "tiendas.h"

class npcs {
public:
	npcs(std::string usuari, int partida, int id, objetos *object,misiones *mision,tienda *tiendas, int NumFilas);
	npcs() { _id = 0, _nombre = "", _mision = 0, _zona = 0, _texto1 = "", _texto2 = "", _listaObj = NULL, _listaMisiones = NULL, _listaTiendas=NULL; }
	std::string getNombre() { return _nombre; }
	int getTienda() { return _tienda; }
	int getMision() { return _mision; }
	int getZona() { return _zona; }
	void muestraTienda(std::string &s) { (_listaTiendas + _tienda)->muestraTienda(s); }
	std::string getTexto1() { return _texto1; }	//Sin mision completada
	std::string getTexto2() { return _texto2; }	//Con mision completada
	bool comprar(int pos,int &objID, int &precio, std::string &s);

private:
	int _id;
	std::string _nombre;
	int _tienda;
	int _mision;
	int _zona;
	std::string _texto1;
	std::string _texto2;

	objetos *_listaObj;
	misiones *_listaMisiones;
	tienda *_listaTiendas;

};