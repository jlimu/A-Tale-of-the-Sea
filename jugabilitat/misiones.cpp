#include "misiones.h"

misiones::misiones(std::string usuario, int id, objetos *objeto, enemigos *enemigo,int NumFilas) {
	_listaObj = objeto;
	_listaEnemigos = enemigo;

	std::ifstream fitxer;
	std::string nomFitxer = ("datos/usuarios/" + usuario+"/misiones/"+ std::to_string(id) + ".txt");
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

void misiones::muestraMision() {
	std::cout <<  _id << "- " << _nombre << std::endl;
	if (_ObjCantidad != 0) {
		std::cout << "Consigue: " << _ObjCantidad << " " << (_listaObj + _ObjID)->getNombre() << std::endl;
	}
	if (_EnemigoCantidad != 0) {
		std::cout << "Derrota: " << _EnemigoCantidad << " " << (_listaEnemigos + _Enemigo)->getNombre() << std::endl;
	}
	//std::cout << "Zona:" << _Zona << " Activa=" << _Activa << " Completada=" << _Completada 
	std::cout<< "Recompensa: " ;
	if (_ObjRecomp != 0) {
		std::cout << _ObjRecCant << " " << (_listaObj + _ObjRecomp)->getNombre();
	}
	else {
		std::cout << "Ningun objeto.";
	}
	if (_DineroRecomp != 0) {
		std::cout << ", " << _DineroRecomp << " monedas" << std::endl;
	}
	std::cout << std::endl << "Descripcion:" << _descripcion << std::endl;//<< " Texto al completar=" << _textoComplet << std::endl;


}
