#pragma once
//#include "jugador.h"
#include <string>
using namespace std;

class Partida
{
public:
	Partida() {}
	Partida(int id, string nom) { _id = id; _nom = nom; next = NULL; }
	~Partida() {}

	int getId() { return _id; }
	string getNomJugador() { return _nom; }
	Partida* getNext() { return next; }
	void setNext(Partida *partida) { next = partida; }

private:
	Partida *next;
	int _id;
	string _nom;
	string _usuari;
	//Jugador _jugador;
};
