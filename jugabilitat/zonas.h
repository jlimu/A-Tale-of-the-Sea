#pragma once
#include <iostream>
#include "enemigos.h"
#include "npcs.h"
class zonas {
public:
	zonas(int &x, int &y, int &tipo, int &enemig, int &NPC, int &tesoro, int &objeto, int &cantidad, objetos *object, enemigos *enemigo) { _x = x, _y = y, _tipo = tipo, _enemigos = enemig, _NPC = NPC, _tesoro = tesoro, _objeto = objeto, _cantidad = cantidad, _listaObj = object, _listaEnemigos = enemigo; }
	zonas() { _x = 0, _y = 0, _tipo = 0, _enemigos = 0, _NPC = 0, _tesoro = 0, _objeto = 0, _cantidad = 0, _listaObj = NULL; }
	void mostrarZona();
	int getEnemigo() { return _enemigos; }
	int getObjetoZona() { return _objeto; }
	int getCantObjZona() { return _cantidad; }
	int getTipo() { return _tipo; }
	int getNpc() { return _NPC; }
	void eliminarEnemigo() { _enemigos = 0; }

private:
	int _x;
	int _y;
	int _tipo;	//0=mar, 1=isla
	int _enemigos;
	int _NPC;
	int _tesoro;
	int _objeto;
	int _cantidad;
	objetos *_listaObj;
	enemigos *_listaEnemigos;

};
