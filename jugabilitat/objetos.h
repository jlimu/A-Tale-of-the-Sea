#pragma once
#include <string>
#include <iostream>
#include <fstream>

class objetos {
public:
	objetos(int id);
	objetos() { _id = 0, _nombre = "", _cantidadMax = 0, _tipo = 0, _descripcion = ""; }
	void muestraObjeto();
	std::string getNombre() { return _nombre; }
	int getMax() { return _cantidadMax; }
	int getTipo() { return _tipo; }
	int getVida() { return _vida; }
	int getAtaque() { return _ataque; }
	int getDefensa() { return _defensa; }
	int getDinero() { return _dinero; }
	std::string getDesc() { return _descripcion; }

private:
	int _id;
	std::string _nombre;
	int _cantidadMax;
	int _tipo;	//1=armadura, 2=consumible, 3=material, 4=especial, 5=arma
	int	_vida;
	int	_ataque;
	int	_defensa;
	int	_dinero;
	std::string _descripcion;
};