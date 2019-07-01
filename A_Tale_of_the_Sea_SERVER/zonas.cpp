#include "zonas.h"

void zonas::mostrarZona(std::string &s) {
	//std::cout << "Estas en la zona: " << _x << "-" << _y << " que es ";
	s = "Estas en la zona: " + std::to_string(_x) + "-" + std::to_string(_y) + " que es ";
	switch (_tipo) {
	case 0:
		//std::cout << "mar";
		s += "mar";
		break;
	case 1:
		//std::cout << "isla";
		s += "isla";
		break;
	}
	//std::cout << std::endl;
	s += "\n";
	if (_enemigos != 0) {
		//std::cout << "Hay un enemigo:" << (_listaEnemigos+_enemigos)->getNombre() << std::endl;
		s += "Hay un enemigo:" + (_listaEnemigos+_enemigos)->getNombre() + "\n";
	}

	if (_tesoro != 0) {
		//std::cout << "Hay un tesoro" << listaTesoros[_tesoro].getEstado() << std::endl;
	}
	if (_objeto != 0) {
		//std::cout << "Hay " << _cantidad << " " << (_listaObj +_objeto)->getNombre() << std::endl;
		s += "Hay " + std::to_string(_cantidad) + " " + (_listaObj +_objeto)->getNombre() + "\n";
	}
	if (_NPC != 0) {
		//std::cout << "Hay un NPC:" ;
		s += "Hay un NPC:";
	}
}
