#pragma once
#include "objetos.h"
const int MaxItemsTienda = 5;

class tienda {
public:
	tienda(int id, objetos *objeto);
	tienda() { _numObj = 0, _objID[MaxItemsTienda] = 0, _objValor[MaxItemsTienda] = 0; }
	int getNumObj() { return _numObj; }
	int getObjID(int pos) { return _objID[pos]; }
	int getTObjValor(int pos) { return _objValor[pos]; }
	void muestraTienda(std::string &s);
private:
	int _id;
	int _numObj;
	int	_objID[MaxItemsTienda];
	int	_objValor[MaxItemsTienda];
	objetos *_listaObj;
};