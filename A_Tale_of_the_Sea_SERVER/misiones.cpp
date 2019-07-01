#include "misiones.h"

misiones::misiones(std::string usuari, int partida, int id, objetos *objeto, enemigos *enemigo,int NumFilas) {
	_listaObj = objeto;
	_listaEnemigos = enemigo;

	std::ifstream fitxer;
	std::string nomFitxer = ("Usuarios_Partidas/" + usuari + "/" + std::to_string(partida) + "/misiones/" + std::to_string(id) + ".txt");
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
		fitxer >> e >> _NPCid >> e >> _ObjID >> e >> _ObjCantidad >> e >> _Enemigo >> e >> _EnemigoCantidad >> e >> _Zona;
		fitxer >> _ObjRecomp; //Uso _ObjRecomp como auxiliar para guardar la variable Y de la zona
		_Zona += (_ObjRecomp*NumFilas);
		fitxer >> e >> _Activa >> e >> _Completada >> e >> _ObjRecomp >> e >> _ObjRecCant >> e >> _DineroRecomp >> e >> _descripcion;
		while (e != "&fin") {
			fitxer >> e;
			if (e != "&fin") {
				_descripcion += " " + e;
			}
		}
		fitxer >> e;
		while (!fitxer.eof()) {
			fitxer >> e;
			_textoComplet += " " + e;
		}
		fitxer.close();
	}
}

void misiones::muestraMision(std::string &s) {
	//std::cout <<  _id << "- " << _nombre << std::endl;
	s = _id + "- " + _nombre + "\n";
	if (_ObjCantidad != 0) {
		//std::cout << "Consigue: " << _ObjCantidad << " " << (_listaObj + _ObjID)->getNombre() << std::endl;
		s += "Consigue: " + std::to_string(_ObjCantidad) + " " + (_listaObj + _ObjID)->getNombre() + "\n";
	}
	if (_EnemigoCantidad != 0) {
		//std::cout << "Derrota: " << _EnemigoCantidad << " " << (_listaEnemigos + _Enemigo)->getNombre() << std::endl;
		s += "Derrota: " + std::to_string(_EnemigoCantidad) + " " + (_listaEnemigos + _Enemigo)->getNombre() + "\n";
	}
	//std::cout << "Zona:" << _Zona << " Activa=" << _Activa << " Completada=" << _Completada 
	//std::cout<< "Recompensa: " ;
	s += "Recompensa: ";
	if (_ObjRecomp != 0) {
		//std::cout << _ObjRecCant << " " << (_listaObj + _ObjRecomp)->getNombre();
		s += std::to_string(_ObjRecCant) + " " + (_listaObj + _ObjRecomp)->getNombre();
	}
	else {
		//std::cout << "Ningun objeto.";
		s += "Ningun objeto.";
	}
	if (_DineroRecomp != 0) {
		//std::cout << ", " << _DineroRecomp << " monedas" << std::endl;
		s += ", " + std::to_string(_DineroRecomp) + " monedas\n";
	}
	//std::cout << std::endl << "Descripcion:" << _descripcion << std::endl;//<< " Texto al completar=" << _textoComplet << std::endl;
	s += "\nDescripcion:" + _descripcion + "\n";


}
