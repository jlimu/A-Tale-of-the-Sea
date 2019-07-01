#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "objetos.h"

class enemigos {
public:
	enemigos(int id, objetos *object);
	enemigos() { _id = 0, _nombre = "", _vida = 0, _ataque = 0, _dinero = 0, _ObjID = 0, _ObjCantidad = 0, _descripcion = "", _listaObj = NULL; }
	void muestraEnemigo(std::string &s);
	std::string getNombre() { return _nombre; }
	int getVida() { return _vida; }
	int getAtaque() { return _ataque; }
	int getDinero() { return _dinero; }
	int getDropObj() { return _ObjID; }
	int getDropCant() { return _ObjCantidad; }
	std::string getDesc() { return _descripcion; }

	void setVida(int vida) { _vida += vida; }
private:
	int _id;
	std::string _nombre;
	int	_vida;
	int	_ataque;
	int	_dinero;
	int _ObjID;
	int _ObjCantidad;
	std::string _descripcion;

	objetos *_listaObj;

};