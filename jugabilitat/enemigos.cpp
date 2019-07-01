#include "enemigos.h"

enemigos::enemigos(int id, objetos *object){
	_listaObj = object;

	std::ifstream fitxer;
	std::string nomFitxer = ("datos/enemigos/" + std::to_string(id) + ".txt");
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
		fitxer >> e >> _ataque >> e >> _vida >> e >> _ObjID >> e >> _ObjCantidad >> e >> _dinero >> e >> _descripcion;
		while (!fitxer.eof()) {
			fitxer >> e;
			_descripcion += " " + e;
		}
		fitxer.close();
	}
}

void enemigos::muestraEnemigo(){
	std::cout << "id=" << _id << " nombre=" << _nombre << " vida=" << _vida << " ataque=" << _ataque << " drop=" << _dinero << "monedas, " << _ObjCantidad << " " << (_listaObj + _ObjID)->getNombre() << " descripcion=" << _descripcion << std::endl;
}