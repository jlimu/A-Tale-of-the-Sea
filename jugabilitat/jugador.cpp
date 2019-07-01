#include "jugador.h"


jugador::jugador(std::string usuario, inventario *invent, map *mapa, misiones *mision) {
	std::ifstream fitxer;
	fitxer.open("datos/usuarios/" + usuario + "/jugador.txt");
	if (fitxer.is_open())
	{
		std::string e; //simula el nombre de la variable para no guardarla
		fitxer >> e >> _x >> e >> _y >> e >> _nom >> e >> _vida >> e >>  _vidaMax >> e >> _ataque >> e >> _defensa >> e >> _dinero >> e >> _arma >> e >> _armadura;

		fitxer.close();
	}
	_inventario = invent;
	_mapa = mapa;
	_misiones = mision;
}
void jugador::consultarPersonaje() {
	std::cout << "nombre=" << _nom << "  X-Y=" << _x << "-" << _y <<std::endl
		<< "vida=" << _vida << "/" << _vidaMax << " ataque=" << _ataque << " defensa=" << _defensa <<std::endl
		<< "dinero=" << _dinero << " arma=" << _arma << " armadura=" << _armadura << std::endl;
}

void jugador::usarObjeto(int posicion) {
	_inventario->usarObjeto(posicion, _vida, _vidaMax, _ataque, _defensa, _dinero, _arma, _armadura);
}

void jugador::moverArriba() {
	_y -= 1;
	if (_y < 0) {
		_y = 0;
	}
	_mapa->mostarZona(_y * 5 + _x);
}
void jugador::moverAbajo() {
	_y += 1;
	if (_y > (_mapa->getLimitX() - 1)) {
		_y -= 1;
	}
	_mapa->mostarZona(_y * 5 + _x);
}
void jugador::moverDerecha() {
	_x += 1;
	if (_x > (_mapa->getLimitY() - 1)) {
		_x -= 1;
	}
	_mapa->mostarZona(_y * 5 + _x);
}
void jugador::moverIzquierda() {
	_x -= 1;
	if (_x < 0) {
		_x = 0;
	}
	_mapa->mostarZona(_y * 5 + _x);
}

void jugador::abrir_missiones(int NumMisiones) {
	for (int i = 1; i <= NumMisiones; i++) {
		if ((_misiones + i)->getActiva()) {
			std::cout <<i<<"- "<< (_misiones + i)->getNombre() << std::endl;
		}
	}
}

void jugador::abrir_mission(int posicion, int NumMisiones) {
	if ((posicion > NumMisiones)||!(_misiones+posicion)->getActiva()) {
		std::cout << "No puedes acceder a esa mision" << std::endl;
	}
	else {
		(_misiones + posicion)->muestraMision();
	}
}

bool jugador::ComprobarObjMision(int id) {
	bool encontrado = false;
	for (int i = 0; i < _inventario->getMaxObj(); i++) {
		if ((_misiones + id)->getObj() == _inventario->getObj(i)) {
			if ((_misiones + id)->getObjCantidad() <= _inventario->getObjCant(i)) {
				encontrado= true;
			}
		}
	}
	return encontrado;
}

void jugador::completarMision(int id) {
	if (!_inventario->añadir_objeto((_misiones + id)->getObjRecomp(), (_misiones + id)->getObjRecCant())) {//No se ha podido añadir
		std::cout << "No se puede completar la mision, no hay espacio en el inventario para añadir los objetos de la recompensa" << std::endl;
	}
	else {
		std::cout << (_misiones + id)->getTextComplet() << std::endl;
		(_misiones + id)->setCompletada();
		(_misiones + id)->setActiva();
		_dinero+=(_misiones + id)->getDineroRecomp();
		if ((_misiones + id)->getDineroRecomp() != 0) {
			std::cout << "Has conseguido " << (_misiones + id)->getDineroRecomp() << " monedas" << std::endl;
		}
	}
}

void jugador::comprar(int objID, int precio) {
	if (_inventario->añadir_objeto(objID, 1)) {	//correcto
		_dinero += precio;
	}
	else {
		std::cout << "No hay espacio en el inventario" << std::endl;
	}
}
