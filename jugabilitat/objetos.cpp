#include "objetos.h"

objetos::objetos(int id) {
	std::ifstream fitxer;
	std::string nomFitxer = ("datos/objetos/" + std::to_string(id) + ".txt");
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		_id = id;

		std::string e; //simula el nombre de la variable para no guardarla
		fitxer >> e >> _nombre;
		while (e != "&fin") {
			fitxer >> e;
			if (e != "&fin") {
				_nombre += " " + e;
			}
		}
		fitxer >> e >> _cantidadMax >> e >> _tipo >> e >> _vida >> e >> _ataque >> e >> _defensa >> e >> _dinero >> e >> _descripcion;
		while (!fitxer.eof()) {
			fitxer >> e;
			_descripcion += " "+e;
		}
		fitxer.close();
	}
}

void objetos::muestraObjeto() {
	std::cout << "id=" << _id << std::endl
		<< "nombre=" << _nombre << std::endl
		<< "cantidad_max=" << _cantidadMax << std::endl
		<< "tipo=" << _tipo << std::endl
		<< "descripcion=" << _descripcion << std::endl;
}
