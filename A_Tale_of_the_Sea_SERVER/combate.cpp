#include "combate.h"

int combate::atacar(std::string &s) {
	int muerto = 0;
	//std::cout << "Atacas al enemigo " << _enemigo.getNombre()<<":"<< std::endl;
	s = "Atacas al enemigo " + _enemigo.getNombre() + ":\n";

	_jugador->setVida(-(_enemigo.getAtaque()));
	if (_jugador->getVida() <= 0) {
		muerto = 1;
		//std::cout << "--------------HAS MUERTO-----------" << std::endl;
		s += "--------------HAS MUERTO-----------\n";
	}
	else {
		_enemigo.setVida(-(_jugador->getAtaque()));
		if (_enemigo.getVida() <= 0) {
			muerto = 2;
			//std::cout << "--------------HAS MATADO A " << _enemigo.getNombre() << "-----------" << std::endl;
			s += "--------------HAS MATADO A " + _enemigo.getNombre() + "-----------\n";
			//std::cout << "Vida restante:" << _jugador->getVida() << std::endl;
			s += "Vida restante: " + std::to_string(_jugador->getVida()) + "\n";
			if (!_jugador->recoger_objeto(_enemigo.getDropObj(), _enemigo.getDropCant(), _enemigo.getDinero(), s)) {	//No se ha recogido el objeto
				//std::cout << "No hay espacio en el inventario para los objetos" << std::endl;
				s += "No hay espacio en el inventario para los objetos\n";
			}
		}
		else {
			//std::cout << _enemigo.getNombre() << "   daño:" << _enemigo.getAtaque() << "   vida:" << _enemigo.getVida() << std::endl << _jugador->getNom() << "   daño:" << _jugador->getAtaque() << "   vida:" << _jugador->getVida() << std::endl;
			s += _enemigo.getNombre() + "   dano:" + std::to_string(_enemigo.getAtaque()) + "   vida:" + std::to_string(_enemigo.getVida()) + "\n";
			s += _jugador->getNom() + "   dano:" + std::to_string(_jugador->getAtaque()) + "   vida:" + std::to_string(_jugador->getVida()) + "\n";
		}
	}

	return (muerto);

}
