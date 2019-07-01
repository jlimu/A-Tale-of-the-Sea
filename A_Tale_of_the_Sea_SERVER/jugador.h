#pragma once
#include <string>
#include <iostream>
//#include <fstream>

//#include "creacion.h"
#include "misiones.h"	//Para poder ver (por ejemplo) las misiones activas (guardando una lista de IDs de estas o algo así)
#include "mapa.h"
#include "inventario.h"
//#include "vaixell.h"


class jugador
{
public:
	jugador() {}
	jugador(std::string usuari, int partida, inventario *invent, map *mapa, misiones *mision);
	//~jugador() { _inventario=NULL, _mapa=NULL; }
	
	void consultarInventario(int NumObjetos, std::string &s) { _inventario->muestraInventario(NumObjetos, s); }
	void consultarPersonaje(std::string &s);
	void eliminarInventario(int posicion) { _inventario->eliminarObjeto(posicion); }
	void usarObjeto(int posicion);
	void consultarMapa(std::string &s) { _mapa->mostarMapa(_x,_y, s); }
	void moverArriba(std::string &s);
	void moverAbajo(std::string &s);
	void moverDerecha(std::string &s);
	void moverIzquierda(std::string &s);
	
	void iniciar_combate(){}
	int getEnemigo() { return _mapa->getEnemigo(_y*_mapa->getLimitX() + _x); }
	void eliminarEnemigo() { _mapa->eliminarEnemigo(_y*_mapa->getLimitX() + _x); }
	int getObjetoZona() { return _mapa->getObjetoZona(_y*_mapa->getLimitX() + _x); }
	int getCantObjZona() { return _mapa->getCantObjZona(_y*_mapa->getLimitX() + _x); }
	void muestraObjeto(int pos, std::string &s) { _inventario->muestraObjeto(pos, s); }
	void Zoom(std::string &s) { _mapa->Zoom(_y*_mapa->getLimitX() + _x, s); }
	int muestraPrecioVenta(int pos, std::string &s) { return _inventario->muestraPrecioVenta(pos, s); }

	void abrir_missiones(int NumMisiones, std::string &s);
	void abrir_mission(int posicion, int NumMisiones, std::string &s);
	int hablar_NPC() { return _mapa->getNPC(_y*_mapa->getLimitX() + _x); }
	int getZona() { return _y * _mapa->getLimitX() + _x; }
	bool ComprobarMisionActiva(int id) { return (_misiones + id)->getActiva(); }
	bool ComprobarMisionComplet(int id) { return (_misiones + id)->getCompletada(); }
	void AceptarMision(int id) { (_misiones + id)->setActiva(); }
	int MisiongetEnemigoCantidad(int id) { return (_misiones+id)->getEnemigoCantidad(); }
	bool ComprobarObjMision(int id);
	void completarMision(int id, std::string &s);
	void vender(int pos) { _dinero+=_inventario->vender(pos); }
	void comprar(int objID, int precio, std::string &s);
	//dadas_barco()
	//craft()
	//mostrar_crafts()

	
	int getAtaque() { return _ataque; }
	int getVida() { return _vida; }
	std::string getNom() { return _nom; }
	void setVida(int vida) { _vida += vida; }
	bool recoger_objeto(int id, int cantidad, int oro, std::string &s);

private:
	int _x;
	int _y;
	std::string _nom;
	int _vida;
	int _vidaMax;
	int _ataque;
	int _defensa;
	int _dinero;
	int _arma;
	int _armadura;
	inventario *_inventario;
	map *_mapa;
	int IDmisiones;
	misiones *_misiones;
	//vaixell _vaixell;
};


