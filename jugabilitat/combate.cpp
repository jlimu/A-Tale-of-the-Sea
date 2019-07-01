#include "combate.h"

int combate::atacar() {
	int muerto = 0;
	std::cout << "Atacas al enemigo " << _enemigo.getNombre()<<":"<< std::endl;

	_jugador->setVida(-(_enemigo.getAtaque()));
	if (_jugador->getVida() <= 0) {
		muerto = 1;
		std::cout << "--------------HAS MUERTO-----------" << std::endl;
	}
	else {
		_enemigo.setVida(-(_jugador->getAtaque()));
		if (_enemigo.getVida() <= 0) {
			muerto = 2;
			std::cout << "--------------HAS MATADO A " << _enemigo.getNombre() << "-----------" << std::endl;
			std::cout << "Vida restante:" << _jugador->getVida() << std::endl;
			if (!_jugador->recoger_objeto(_enemigo.getDropObj(), _enemigo.getDropCant(), _enemigo.getDinero())) {	//No se ha recogido el objeto
				std::cout << "No hay espacio en el inventario para los objetos" << std::endl;
			}
		}
		else {
			std::cout << _enemigo.getNombre() << "   daño:" << _enemigo.getAtaque() << "   vida:" << _enemigo.getVida() << std::endl << _jugador->getNom() << "   daño:" << _jugador->getAtaque() << "   vida:" << _jugador->getVida() << std::endl;
		}
	}

	return (muerto);

}
