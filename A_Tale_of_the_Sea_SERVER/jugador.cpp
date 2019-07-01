#include "jugador.h"


jugador::jugador(std::string usuari, int partida, inventario *invent, map *mapa, misiones *mision) {
	std::ifstream fitxer;
	fitxer.open("Usuarios_Partidas/" + usuari + "/" + std::to_string(partida) + "/jugador.txt");
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
void jugador::consultarPersonaje(std::string &s) {
	/*
	std::cout << "nombre=" << _nom << "  X-Y=" << _x << "-" << _y <<std::endl
		<< "vida=" << _vida << "/" << _vidaMax << " ataque=" << _ataque << " defensa=" << _defensa <<std::endl
		<< "dinero=" << _dinero << " arma=" << _arma << " armadura=" << _armadura << std::endl;
		*/

	s = "nombre=" + _nom + "  X-Y=" + std::to_string(_x) + "-" + std::to_string(_y) + "\n" +
		"vida=" + std::to_string(_vida) + "/" + std::to_string(_vidaMax) + " ataque=" + std::to_string(_ataque) + "defensa=" + std::to_string(_defensa) + "\n" +
		"dinero=" + std::to_string(_dinero) + " arma=" + std::to_string(_arma) + " armadura=" + std::to_string(_armadura) + "\n";
}

void jugador::usarObjeto(int posicion) {
	_inventario->usarObjeto(posicion, _vida, _vidaMax, _ataque, _defensa, _dinero, _arma, _armadura);
}

void jugador::moverArriba(std::string &s) {
	_y -= 1;
	if (_y < 0) {
		_y = 0;
	}
	_mapa->mostarZona(_y * 5 + _x, s);
}
void jugador::moverAbajo(std::string &s) {
	_y += 1;
	if (_y > (_mapa->getLimitX() - 1)) {
		_y -= 1;
	}
	_mapa->mostarZona(_y * 5 + _x, s);
}
void jugador::moverDerecha(std::string &s) {
	_x += 1;
	if (_x > (_mapa->getLimitY() - 1)) {
		_x -= 1;
	}
	_mapa->mostarZona(_y * 5 + _x, s);
}
void jugador::moverIzquierda(std::string &s) {
	_x -= 1;
	if (_x < 0) {
		_x = 0;
	}
	_mapa->mostarZona(_y * 5 + _x, s);
}

void jugador::abrir_missiones(int NumMisiones, std::string &s) {
	s = "";
	for (int i = 1; i <= NumMisiones; i++) {
		if ((_misiones + i)->getActiva()) {
			//std::cout <<i<<"- "<< (_misiones + i)->getNombre() << std::endl;
			s += i + "- " + (_misiones + i)->getNombre() + "\n";
		}
	}
}

void jugador::abrir_mission(int posicion, int NumMisiones, std::string &s) {
	if ((posicion > NumMisiones)||!(_misiones+posicion)->getActiva()) {
		//std::cout << "No puedes acceder a esa mision" << std::endl;
		s = "No puedes acceder a esa mision\n";
	}
	else {
		(_misiones + posicion)->muestraMision(s);
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

void jugador::completarMision(int id, std::string &s) {
	if (!_inventario->anadir_objeto((_misiones + id)->getObjRecomp(), (_misiones + id)->getObjRecCant(), s)) {//No se ha podido añadir
		//std::cout << "No se puede completar la mision, no hay espacio en el inventario para añadir los objetos de la recompensa" << std::endl;
		s = "No se puede completar la mision, no hay espacio en el inventario para añadir los objetos de la recompensa\n";
	}
	else {
		s = (_misiones + id)->getTextComplet() + "\n";
		(_misiones + id)->setCompletada();
		(_misiones + id)->setActiva();
		_dinero+=(_misiones + id)->getDineroRecomp();
		if ((_misiones + id)->getDineroRecomp() != 0) {
			//std::cout << "Has conseguido " << (_misiones + id)->getDineroRecomp() << " monedas" << std::endl;
			s += "Has conseguido " + std::to_string((_misiones + id)->getDineroRecomp()) + " monedas\n";
		}
	}
}

void jugador::comprar(int objID, int precio, std::string &s) {
	if (_inventario->anadir_objeto(objID, 1, s)) {	//correcto
		_dinero += precio;
	}
	else {
		//std::cout << "No hay espacio en el inventario" << std::endl;
		s = "No hay espacio en el inventario\n";
	}
}

bool jugador::recoger_objeto(int id, int cantidad, int oro, std::string &s)
{
	bool a = _inventario->anadir_objeto(id, cantidad, s);
	_dinero += oro;
	s += "Has conseguido" + std::to_string(oro) + "monedas\n";
	return a;
}
