#include "inventario.h"

inventario::inventario(std::string usuari, int partida, objetos *object) {
	std::ifstream fitxer;
	fitxer.open("Usuarios_Partidas/" + usuari + "/" + std::to_string(partida) + "/inventario.txt");
	if (fitxer.is_open())
	{
		std::string e; //simula el nombre de la variable para no guardarla
		int posicion = 0;
		fitxer >> e >> e;
		while (!fitxer.eof()) {
			fitxer >> _espacio[posicion][0] >> _espacio[posicion][1];
			posicion++;
		}
		fitxer.close();
	}
	_listaObj = object;
}

void inventario::muestraInventario(int NumObjetos, std::string &s) {
	s = "";
	for (int i = 0; i < NumMaxObjectes; i++) {
		if (_espacio[i][0] != 0) {
			//std::cout <<i<<": "<< (_listaObj + _espacio[i][0])->getNombre() << " - cantidad:" << _espacio[i][1] << std::endl;
			s += i + ": " + (_listaObj + _espacio[i][0])->getNombre() + " - cantidad:" + std::to_string(_espacio[i][1]) + "\n";
		}
	}
}

void inventario::eliminarObjeto(int posicion) {
	_espacio[posicion][0] = 0;
	_espacio[posicion][1] = 0;
}

void inventario::usarObjeto(int posicion, int &vida, int &vidaMax, int &ataque, int &defensa, int &dinero, int &arma, int &armadura) {
	//Augmento estadisticas
	vida += (_listaObj + _espacio[posicion][0])->getVida();
	if (vida > vidaMax) {
		vida = vidaMax;
	}
	ataque += (_listaObj + _espacio[posicion][0])->getAtaque();
	defensa += (_listaObj + _espacio[posicion][0])->getDefensa();
	int aux = 0;
	switch ((_listaObj + _espacio[posicion][0])->getTipo()) {
	case 1:	//armadura
		//Quito antigua armadura
		aux = armadura;
		armadura = _espacio[posicion][0];
		_espacio[posicion][0] = aux;
		//Disminuyo estadisticas antiguo objeto
		ataque -= (_listaObj + _espacio[posicion][0])->getAtaque();
		defensa -= (_listaObj + _espacio[posicion][0])->getDefensa();
		break;
	case 2:	//consumible
		_espacio[posicion][1] -= 1;
		break;
	case 5:	//arma
		//Quito antigua arma
		aux = arma;
		arma = _espacio[posicion][0];
		_espacio[posicion][0] = aux;
		//Disminuyo estadisticas antiguo objeto
		ataque -= (_listaObj + _espacio[posicion][0])->getAtaque();
		defensa -= (_listaObj + _espacio[posicion][0])->getDefensa();;
		break;
	}
	if ((_espacio[posicion][0] == 0) || (_espacio[posicion][1] == 0)) {
		_espacio[posicion][1] = 0;
		_espacio[posicion][0] = 0;
	}

}

bool inventario::anadir_objeto(int id, int cantidad, std::string &s) {
	bool anadido = true;
	bool trobat = false;
	int i = 0;
	while (!trobat && i < NumMaxObjectes) {	//buscando mismo ID en el inventario
		if (_espacio[i][0] == id) {
			trobat = true;
		}
		else {
			i++;
		}
	}
	if (trobat) {
		if ((_espacio[i][1] + cantidad) > (_listaObj + _espacio[i][0])->getMax()) {	//COMPROBAR QUE NO SUPERA LA CANTIDAD MAXIMA
			anadido = false;	//HA SUPERADO LA CANTIDAD MAXIMA, NO SE PUEDE AÑADIR EL OBJETO AL INVENTARIO
			//std::cout << "No puedes llevar tantos objetos iguales" << std::endl;
			s = "No puedes llevar tantos objetos iguales\n";
		}
		else {	//AÑADIMOS LA CANTIDAD DEL OBJETO AL INVENTARIO
			_espacio[i][1] += cantidad;
			//std::cout << "Has conseguido:" << cantidad << " " << (_listaObj + _espacio[i][0])->getNombre() << std::endl;
			s = "Has conseguido:" + std::to_string(cantidad) + " " + (_listaObj + _espacio[i][0])->getNombre() + "\n";
		}
	}
	else {
		i = 0;
		while (!trobat && i < NumMaxObjectes) {	//buscando espacio vacio en el inventario
			if (_espacio[i][0] == 0) {
				trobat = true;
			}
			else {
				i++;
			}
		}
		if (trobat) {	//AÑADIMOS EL OBJETO AL INVENTARIO
			_espacio[i][0] = id;
			_espacio[i][1] = cantidad;
			//std::cout << "Has conseguido:" << cantidad << " " << (_listaObj + _espacio[i][0])->getNombre() << std::endl;
			s += "Has conseguido:" + std::to_string(cantidad) + " " + (_listaObj + _espacio[i][0])->getNombre() + "\n";
		}
	}
	if (!trobat) {	//NO SE HA ENCONTRADO NI EL OBJETO NI ESPACIO EN EL INVENTARIO
		anadido = false;
		//std::cout << "Inventario lleno" << std::endl;
		s += "Inventario lleno\n";
	}
	return anadido;
}

void inventario::muestraObjeto(int posicion, std::string &s) {
	if (_espacio[posicion][0] != 0) {
		(_listaObj + _espacio[posicion][0])->muestraObjeto(s);
	}
	else {
		//std::cout << "No hay ningun objeto en esa posicion" << std::endl;
		s = "No hay ningun objeto en esa posicion\n";
	}
}
int inventario::muestraPrecioVenta(int pos, std::string &s) {
	if ((_listaObj + _espacio[pos][0])->getDinero() != 0) {
		//std::cout << (_listaObj + _espacio[pos][0])->getNombre() << " se vende por: " << (_listaObj + _espacio[pos][0])->getDinero() << " monedas" << std::endl;
		s = (_listaObj + _espacio[pos][0])->getNombre() + " se vende por: " + std::to_string((_listaObj + _espacio[pos][0])->getDinero()) + " monedas\n";
	}
	else {
		if ((_listaObj + _espacio[pos][0]) == 0) {
			//std::cout << "No tienes ningun objeto en esa posicion" << std::endl;
			s = "No tienes ningun objeto en esa posicion\n";
		}
		else {
			//std::cout << (_listaObj + _espacio[pos][0])->getNombre() << " no se puede vender." << std::endl;
			s = (_listaObj + _espacio[pos][0])->getNombre() + " no se puede vender.\n";
		}
	}

	return (_listaObj + _espacio[pos][0])->getDinero();
}
int inventario::vender(int pos) {
	int dinero = (_listaObj + _espacio[pos][0])->getDinero();
	_espacio[pos][1] -= 1;
	if (_espacio[pos][1] <= 0) {
		_espacio[pos][0] = 0;
	}
	return dinero;
}

