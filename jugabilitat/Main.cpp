#include "jugador.h"
#include "enemigos.h"
#include "npcs.h"
#include <iostream>
#include <string>
#include "combate.h"
#include "tiendas.h"
const int NumEnemigos = 2;
const int NumNPCs = 3;
const int NumObjetos = 6;
const int NumMisiones = 2;
const int NumTiendas = 1;
const int NumFilas = 7;
const int NumColumnas = 7;


int main() {
	std::string usuario;
	std::cout << "introduce nombre usuario:";
	usuario = "raular5";//std::cin >> usuario;
	std::cout << std::endl << "Se ha cargado (raular5) por k lo he puesto asi en el codigo xD, cargando clases" << std::endl ;

	objetos objeto[NumObjetos+1];
	for (int i = 0; i < NumObjetos + 1; i++) {
		objeto[i] = objetos(i);
	}
	enemigos enemigo[NumEnemigos + 1];
	for (int i = 0; i < NumEnemigos + 1; i++) {
		enemigo[i] = enemigos(i, &objeto[0]);
	}
	misiones mision[NumMisiones + 1];
	for (int i = 0; i < NumMisiones + 1; i++) {
		mision[i] = misiones(usuario, i, &objeto[0], &enemigo[0],NumFilas);
	}
	tienda tiendas[NumTiendas + 1];
	for (int i = 0; i < NumTiendas + 1; i++) {
		tiendas[i] = tienda(i, &objeto[0]);
	}
	npcs npc[NumNPCs+1];
	for (int i = 0; i < NumNPCs + 1; i++) {
		npc[i] = npcs(usuario, i, &objeto[0], &mision[0],&tiendas[0], NumFilas);
	}
	
	
	map mapa = map(usuario, &objeto[0], &enemigo[0],NumFilas,NumColumnas);
	inventario invent= inventario(usuario, &objeto[0]);
	jugador Usuario1= jugador(std::string(usuario), &invent,&mapa,&mision[0]);
	
	
	std::cout << "clases cargadas" << std::endl << "Usa H para ver las acciones disponibles." << std::endl << std::endl << std::endl;
	char accion = ' ';
	while (accion != 'S') {
		std::cout << "Introduce tu accion: ";
		std::cin >> accion;
		std::cout << std::endl;
		
		switch (accion) {
		case 'A':
		{
			if (Usuario1.getEnemigo() == 0) {
				std::cout << "No hay enemigos" << std::endl << std::endl;
			}
			else {
				std::cout << "Cargando enemigo para pelear." << std::endl;
				combate pelea(enemigo[Usuario1.getEnemigo()], &Usuario1);
				int muerto = 0;
				while ((!muerto) && (accion != 'E')) {	//Enemigo vivo y no queremos escapar
					switch (accion) {
					case 'A':
						muerto = pelea.atacar();
						break;
					case 'O': 
					{
						Usuario1.consultarInventario(NumObjetos);
						std::cout << "Que objeto quieres usar? (indica la posicíon del objeto): ";
						int id;
						std::cin >> id;
						std::cout << std::endl;
						Usuario1.usarObjeto(id);
						break;
					}
					case 'E':
						std::cout << "Salistes del combate" << std::endl;
						break;
					default:
						std::cout << "Accion invalida" << std::endl;
						break;
					}
					if (accion != 'E' && muerto ==0) {
						std::cout << std::endl << "Puedes atacar(A), usar objeto(O), escapar(E) :";
						std::cin >> accion;
						std::cout << std::endl << std::endl;
						}
					else {
						if (muerto==1) {
							std::cout << std::endl << "GAME OVER";
							accion = 'S';
						}
						if (muerto == 2) {
							Usuario1.eliminarEnemigo();
						}
					}
				}
			}
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			break;
		}
		case 'R':
			Usuario1.recoger_objeto(Usuario1.getObjetoZona(), Usuario1.getCantObjZona(), 0);
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		case 'L':
			Usuario1.Zoom();
			while (accion != 'P') {
				std::cout << "Elige la direccion a la que ir: NORTE (N) , SUR (S), ESTE (E) , OESTE (O)" << std::endl << "O para de moverte (P) :";
				std::cin >> accion;
				std::cout << std::endl;
				switch (accion) {
				case 'N':
					Usuario1.moverArriba();
					if (Usuario1.hablar_NPC() != 0) {
						std::cout << npc[Usuario1.hablar_NPC()].getNombre() << std::endl;
					}
					break;
				case 'S':
					Usuario1.moverAbajo();
					if (Usuario1.hablar_NPC() != 0) {
						std::cout << npc[Usuario1.hablar_NPC()].getNombre() << std::endl;
					}
					break;
				case 'E':
					Usuario1.moverDerecha();
					if (Usuario1.hablar_NPC() != 0) {
						std::cout << npc[Usuario1.hablar_NPC()].getNombre() << std::endl;
					}
					break;
				case 'O':
					Usuario1.moverIzquierda();
					if (Usuario1.hablar_NPC() != 0) {
						std::cout << npc[Usuario1.hablar_NPC()].getNombre() << std::endl;
					}
					break;
				case 'P':
					std::cout << "Has parado de moverte" << std::endl;
					break;
				default:
					std::cout << "Accion invalida" << std::endl;
					break;
				}
				std::cout << "	---------" << std::endl;
			}
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		case 'N':
			if (npc[Usuario1.hablar_NPC()].getZona() !=0) {
				if (npc[Usuario1.hablar_NPC()].getMision() != 0) {	//Tiene misiones
					if (Usuario1.ComprobarMisionComplet(Usuario1.hablar_NPC())) {
						std::cout << npc[Usuario1.hablar_NPC()].getTexto2() << std::endl;
					}
					else {
						std::cout << npc[Usuario1.hablar_NPC()].getTexto1() << std::endl;
						if (!Usuario1.ComprobarMisionActiva(Usuario1.hablar_NPC())) {	//No está activa
							do {
								std::cout << "Aceptar mision? Si (S), No(N):";
								std::cin >> accion;
								std::cout << std::endl;
								switch (accion) {
								case 'S':
									std::cout << "Aceptastes la mision." << std::endl;
									Usuario1.AceptarMision(npc[Usuario1.hablar_NPC()].getMision());
									break;
								case'N':
									std::cout <<  "No aceptastes la mision." << std::endl;
									break;
								default:
									std::cout <<accion<< " :no es una opcion valida." << std::endl;
									break;
								}
							} while (accion != 'S' && accion != 'N');
						}
						else {
							do {
								std::cout << "Puedes :Completar mision (C), cancelar mision(E), salir(S):";
								std::cin >> accion;
								std::cout << std::endl;
								switch (accion) {
								case 'C':
									if (Usuario1.MisiongetEnemigoCantidad(npc[Usuario1.hablar_NPC()].getMision())==0) {//Enemigos derrotados
										if (Usuario1.ComprobarObjMision(npc[Usuario1.hablar_NPC()].getMision()) == true) {//Objetos en inventario
											Usuario1.completarMision(npc[Usuario1.hablar_NPC()].getMision());
										}
										else {
											std::cout << "No tienes lo necesario para completar la mision." << std::endl;
										}
									}
									else {
										std::cout << "No has derrotado a los enemigos necesarios." << std::endl;
									}
									break;
								case'E':
									std::cout << "Cancelastes la mision." << std::endl;
									Usuario1.AceptarMision(npc[Usuario1.hablar_NPC()].getMision());
									break;
								case 'S':
									std::cout << "Dejastes de hablar." << std::endl;
									break;
								default:
									std::cout << accion << " :no es una opcion valida." << std::endl;
									break;
								}
							} while (accion != 'C' && accion != 'E' && accion != 'S');
						}
					}
				}
				else {	//No tienes misiones
					if (npc[Usuario1.hablar_NPC()].getTienda() != 0) {	//con tienda
						std::cout << npc[Usuario1.hablar_NPC()].getTexto1() << std::endl;
						do {
							std::cout << "Comprar (C),Vender(V),salir(S):";
							std::cin >> accion;
							std::cout << std::endl;
							switch (accion) {
							case 'C':
								npc[Usuario1.hablar_NPC()].muestraTienda();
								do {
									std::cout << "Hay algo que te interese? Si(S), No(N):";
									std::cin >> accion;
									std::cout << std::endl;
									switch (accion){
									case 'S': {
										std::cout << "Que quieres comprar?(indica la posicion del objeto que quieras comprar):";
										int pos;
										std::cin >> pos;
										std::cout << std::endl;
										int precio;
										int objetoID;
										if (npc[Usuario1.hablar_NPC()].comprar(pos, objetoID, precio)) {	//posicion correcta, existe el objeto
											Usuario1.comprar(objetoID, precio);
										}
									}
										break;
									case 'N':
										std::cout << "De acuerdo, vuelve cuando quieras c:" << std::endl;
										break;
									default:
										std::cout << accion << " :no es una opcion valida." << std::endl;
										break;
										}
								} while (accion != 'S' && accion != 'N');
								break;
							case'V': {
								Usuario1.consultarInventario(NumObjetos);
								std::cout << "Que quieres vender?(indica la posicion del objeto que quieras vender):";
								int pos ;
								std::cin >> pos;
								std::cout << std::endl;
								if (Usuario1.muestraPrecioVenta(pos) != 0) {
									std::cout << "Confirmar venta (V), cancelar venta(C):";
									std::cin >> accion;
									std::cout << std::endl;
									do {
										switch (accion) {
										case'V':
											Usuario1.vender(pos);
											break;
										case'C':
											std::cout << "No vendistes nada." << std::endl;
											break;
										default:
											std::cout << accion << " :no es una opcion valida." << std::endl;
											break;
										}
									} while (accion != 'V' && accion != 'C');
								}
								break;
							}
							case'S':
								std::cout << "Salistes de la tienda." << std::endl;
								break;
							default:
								std::cout << accion << " :no es una opcion valida." << std::endl;
								break;
							}
						} while (accion != 'S');
						
					}
					else {	//sin mision ni tienda
						std::cout << npc[Usuario1.hablar_NPC()].getTexto1() << std::endl;
					}
				}
			}
			else {
				std::cout << "No hay NPCS en esta zona" << std::endl;
			}
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		case 'H':
			//std::cout << "--------------------------------------------------------------------------------" << std::endl;
			std::cout << "Las acciones posibles son:" << std::endl << "-Iniciar combate(A)"
				<< std::endl << "-moverse (L)"
				<< std::endl << "-Recoger objeto (R)"
				<< std::endl << "-Hablar con un npc (N)"
				<< std::endl << "-Mostrar crafteos (C)"
				<< std::endl << "-Abrir inventario (I)"
				<< std::endl << "-Abrir mapa (M)"
				<< std::endl << "-Abrir misiones (Q)"
				<< std::endl << "-Ver datos personaje (P)"
				<< std::endl << "-Ver datos barco (B)"
				<< std::endl << "-Ayuda (H)"
				<< std::endl << "-Guardar (G)"
				<< std::endl << "-Salir partida (S)"<< std::endl;
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		case 'G':
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		case 'I':
			Usuario1.consultarInventario(NumObjetos);
			while (accion != 'S') {
				std::cout << std::endl << "Puedes: ver descripcion objeto(D), usar objeto(U),eliminar objeto (E)"<<std::endl<<"O cerrar inventario(S) :";
				std::cin >> accion;
				switch (accion) {
				case 'D': {
					std::cout << "Introduce la posición del objeto del cual quieres ver la descripcion: ";
					int id;
					std::cin >> id;
					std::cout << std::endl;
					Usuario1.muestraObjeto(id);
				}
					break;
				case 'U': {
					std::cout << "Que objeto quieres usar? (indica la posicíon del objeto): ";
					int id;
					std::cin >> id;
					std::cout << std::endl;
					Usuario1.usarObjeto(id);
					Usuario1.consultarInventario(NumObjetos);
					break;
				}
				case 'E': {
					std::cout << "Que objeto quieres eliminar? (indica la posicíon del objeto): ";
					int id;
					std::cin >> id;
					std::cout << std::endl;
					Usuario1.eliminarInventario(id);
					Usuario1.consultarInventario(NumObjetos);
					break;
				}
				case 'S':
					std::cout << "Cerrastes el inventario" << std::endl;
					break;
				default:
					std::cout << "Accion invalida" << std::endl;
					break;
				}
				std::cout << "	---------" << std::endl;
			}
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		case 'M':
			Usuario1.consultarMapa();
			while (accion != 'S') {
				std::cout << std::endl << "Puedes: Hacer Zoom(z), cerrar el mapa(S) :";
				std::cin >> accion;
				std::cout << std::endl;
				switch (accion) {
				case 'Z':
					Usuario1.Zoom();
					break;
				case 'S':
					std::cout << "Cerrastes el mapa" << std::endl;
					break;
				default:
					std::cout << "Accion invalida" << std::endl;
					break;

				}
			}
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		case 'Q':
			Usuario1.abrir_missiones(NumMisiones);
			while (accion != 'C') {
				std::cout << std::endl << "Puedes: Ver una mision en detalle(D), cerrar la pantalla de misiones(C) :";
				std::cin >> accion;
				std::cout << std::endl;
				switch (accion) {
				case 'D':
					std::cout << "Que mision quieres ver? (indica la posicíon de la mision): ";
					int id;
					std::cin >> id;
					std::cout << std::endl;
					std::cout<<"	--------	--------" << std::endl;
					Usuario1.abrir_mission(id, NumMisiones);
					std::cout << "	--------	--------" << std::endl;
					break;
				case 'C':
					std::cout << "Cerrastes la pantalla de misiones" << std::endl;
					break;
				default:
					std::cout << "Accion invalida" << std::endl;
					break;
				}
			}
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		case 'S':
			std::cout << "ADIOS C=" << std::endl;
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			break;
		case 'P':
			Usuario1.consultarPersonaje();
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		case 'B':
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		case 'C':
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		default:
			std::cout << "Accion invalida" << std::endl;
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			accion = ' ';
			break;
		}
	}

	return 0;
}