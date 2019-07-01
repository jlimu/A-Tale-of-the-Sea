#include "tiendas.h"

tienda::tienda(int id, objetos *objeto) {
	_id = id;
	_listaObj = objeto;
	std::ifstream fitxer;
	std::string nomFitxer = ("datos/tiendas/" + std::to_string(id) + ".txt");
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		std::string e; //simula el nombre de la variable para no guardarla
		fitxer >> e >> _numObj;
		for (int i = 0; i < MaxItemsTienda; i++) {
			if (i < _numObj) {
				fitxer >> e >> _objID[i] >> e >> _objValor[i];
			}
			else {
				_objID[i] = 0;
				_objValor[i] = 0;
			}
		}

		fitxer.close();
	}
}
void tienda::muestraTienda(std::string &s) {
	if (_numObj != 0) {
		//std::cout << "---------TIENDA-------" << std::endl;
		s = "---------TIENDA-------\n";
		for (int i = 0; i < _numObj; i++) {
			//std::cout << i<<"->"<<(_listaObj + _objID[i])->getNombre() << "---" << _objValor[i] <<" monedas"<< std::endl;
			s += i + "->" + (_listaObj + _objID[i])->getNombre() + "---" + std::to_string(_objValor[i]) + " monedas\n";
		}
	}

}

