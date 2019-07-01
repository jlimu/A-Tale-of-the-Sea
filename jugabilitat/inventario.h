#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "objetos.h"

const int NumMaxObjectes = 10;
class inventario {
public:
	inventario(std::string usuario, objetos *object);
	inventario() { _espacio[NumMaxObjectes][2] = 0, _listaObj = NULL; }
	void muestraInventario(int NumObjetos);
	void eliminarObjeto(int posicion);
	void usarObjeto(int posicion, int &vida, int &vidaMax, int &ataque, int &defensa, int &dinero, int &arma, int &armadura);
	void muestraObjeto(int posicion);
	bool añadir_objeto(int id, int cantidad);
	int getMaxObj() { return NumMaxObjectes; }
	int getObj(int pos) { return _espacio[pos][0]; }
	int getObjCant(int pos) { return _espacio[pos][1]; }
	int muestraPrecioVenta(int pos);
	int vender(int pos);
private:
	int _espacio[NumMaxObjectes][2];	//[espacio del inventario][0=id,1=cantidad]
	objetos *_listaObj;
};