#pragma once
#include <iostream>

#include "jugador.h"
#include "enemigos.h"

class combate {
public:
	combate(enemigos enemig, jugador *jugad) { _enemigo = enemig, _jugador = jugad; }
	//combate() { _enemigo = NULL, _jugador = NULL; }
	void copiar_enemigo(enemigos enemig) { _enemigo = enemig; }
	int atacar();
private:
	enemigos _enemigo;
	jugador *_jugador;
};