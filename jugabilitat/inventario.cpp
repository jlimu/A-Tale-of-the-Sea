#include "inventario.h"

inventario::inventario(std::string usuario, objetos *object) {
	std::ifstream fitxer;
	fitxer.open("datos/usuarios/" + usuario + "/inventario.txt");
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

void inventario::muestraInventario(int NumObjetos) {
	for (int i = 0; i < NumMaxObjectes; i++) {
		if (_espacio[i][0] != 0) {
			std::cout <<i<<": "<< (_listaObj + _espacio[i][0])->getNombre() << " - cantidad:" << _espacio[i][1] << std::endl;
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

bool inventario::añadir_objeto(int id, int cantidad) {
	bool añadido = true;
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
			añadido = false;	//HA SUPERADO LA CANTIDAD MAXIMA, NO SE PUEDE AÑADIR EL OBJETO AL INVENTARIO
			std::cout << "No puedes llevar tantos objetos iguales" << std::endl;
		}
		else {	//AÑADIMOS LA CANTIDAD DEL OBJETO AL INVENTARIO
			_espacio[i][1] += cantidad;
			std::cout << "Has conseguido:" << cantidad << " " << (_listaObj + _espacio[i][0])->getNombre() << std::endl;
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
			std::cout << "Has conseguido:" << cantidad << " " << (_listaObj + _espacio[i][0])->getNombre() << std::endl;
		}
	}
	if (!trobat) {	//NO SE HA ENCONTRADO NI EL OBJETO NI ESPACIO EN EL INVENTARIO
		añadido = false;
		std::cout << "Inventario lleno" << std::endl;
	}
	return añadido;
}

void inventario::muestraObjeto(int posicion) {
	if (_espacio[posicion][0] != 0) {
		(_listaObj + _espacio[posicion][0])->muestraObjeto();
	}
	else {
		std::cout << "No hay ningun objeto en esa posicion" << std::endl;
	}
}
int inventario::muestraPrecioVenta(int pos) {
	if ((_listaObj + _espacio[pos][0])->getDinero() != 0) {
		std::cout << (_listaObj + _espacio[pos][0])->getNombre() << " se vende por: " << (_listaObj + _espacio[pos][0])->getDinero() << " monedas" << std::endl;
	}
	else {
		if ((_listaObj + _espacio[pos][0]) == 0) {
			std::cout << "No tienes ningun objeto en esa posicion" << std::endl;
		}
		else {
			std::cout << (_listaObj + _espacio[pos][0])->getNombre() << " no se puede vender." << std::endl;
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

