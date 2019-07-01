#include "zonas.h"

void zonas::mostrarZona() {
	std::cout << "Estas en la zona: " << _x << "-" << _y << " que es ";
	switch (_tipo) {
	case 0:
		std::cout << "mar";
		break;
	case 1:
		std::cout << "isla";
		break;
	}
	std::cout << std::endl;
	if (_enemigos != 0) {
		std::cout << "Hay un enemigo:" << (_listaEnemigos+_enemigos)->getNombre() << std::endl;
	}

	if (_tesoro != 0) {
		//std::cout << "Hay un tesoro" << listaTesoros[_tesoro].getEstado() << std::endl;
	}
	if (_objeto != 0) {
		std::cout << "Hay " << _cantidad << " " << (_listaObj +_objeto)->getNombre() << std::endl;
	}
	if (_NPC != 0) {
		std::cout << "Hay un NPC:" ;
	}
}
