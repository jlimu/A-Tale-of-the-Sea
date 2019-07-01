#include "npcs.h"

npcs::npcs(std::string usuario, int partida, int id, objetos *object, misiones *mision,tienda *tiendas, int NumFilas) {
	_id = id;
	_listaObj=object;
	_listaMisiones = mision;
	_listaTiendas = tiendas;

	std::ifstream fitxer;
	std::string nomFitxer = ("Usuarios_Partidas/" + usuario + "/" + std::to_string(partida) + "/npc/" + std::to_string(id) + ".txt");
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		std::string e; //simula el nombre de la variable para no guardarla
		fitxer >> e >> _nombre;
		while (e != "&fin") {
			fitxer >> e;
			if (e != "&fin") {
				_nombre += " " + e;
			}
		}

		fitxer >> e >> _tienda >> e >> _mision >> e >> _zona;
		_zona = _zona;
		int aux;
		fitxer >> aux; //Uso aux como auxiliar para guardar la variable Y de la zona
		_zona += aux * NumFilas;
		fitxer >> e >> _texto1;
		while (e != "&fin") {
			fitxer >> e;
			if (e != "&fin") {
				_texto1 += " " + e;
			}
		}

		fitxer >> e;
		fitxer >> e;
		while (!fitxer.eof()) {
			_texto2 += " " + e;
			fitxer >> e;
		}
		fitxer.close();
	}
}

bool npcs::comprar(int pos, int &objID,  int &precio, std::string &s) {
	bool correcto;
	if (pos<(_listaTiendas + _tienda)->getNumObj()) {
		correcto = true;
		objID = (_listaTiendas + _tienda)->getObjID(pos);
		precio = (_listaTiendas + _tienda)->getTObjValor(pos);
	}
	else {
		//std::cout << "No hay ningun objeto con esa posicion" << std::endl;
		s = "No hay ningun objeto con esa posicion\n";
		correcto = false;
	}
	return correcto;
}
