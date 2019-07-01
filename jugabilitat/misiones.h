#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "objetos.h"
#include "enemigos.h"

class misiones {
public:
	misiones(std::string usuario, int id, objetos *objeto, enemigos *enemigo, int NumFilas);
	misiones() { _id = 0, _nombre = "", _NPCid = 0, _ObjID = 0, _ObjCantidad = 0, _Enemigo = 0, _EnemigoCantidad = 0, _Zona = 0, _Activa = 0, _Completada = 0, _ObjRecomp = 0, _ObjRecCant = 0, _DineroRecomp = 0, _descripcion = "", _textoComplet = "", _listaObj = NULL, _listaEnemigos = NULL; }
	void muestraMision();
	std::string getNombre() { return _nombre; }
	int getNPC() { return _NPCid; }
	int getObj() { return _ObjID; }
	int getObjCantidad() { return _ObjCantidad; }
	int getEnemigo() { return _Enemigo; }
	int getEnemigoCantidad() { return _EnemigoCantidad; }
	int getZona() { return _Zona; }
	bool getActiva() { return _Activa; }
	bool getCompletada() { return _Completada; }
	int getObjRecomp() { return _ObjRecomp; }
	int getObjRecCant() { return _ObjRecCant; }
	int getDineroRecomp() { return _DineroRecomp; }
	void setActiva() { _Activa=!_Activa; }
	void setCompletada() { _Completada = true; }
	std::string getDesc() { return _descripcion; }
	std::string getTextComplet() { return _textoComplet; }



private:
	int _id;
	std::string _nombre;
	int	_NPCid;
	int	_ObjID;
	int	_ObjCantidad;
	int _Enemigo;
	int _EnemigoCantidad;
	int _Zona;
	bool _Activa;
	bool _Completada;
	int _ObjRecomp;
	int _ObjRecCant;	//Cantidad de objetos de recompensa
	int _DineroRecomp;
	std::string _descripcion;
	std::string _textoComplet;

	objetos *_listaObj;
	enemigos *_listaEnemigos;
};