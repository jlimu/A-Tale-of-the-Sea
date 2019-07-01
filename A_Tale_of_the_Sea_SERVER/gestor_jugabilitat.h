#pragma once
#include <sys/socket.h>
#include <string.h>

#include "jugador.h"
#include "enemigos.h"
#include "npcs.h"
#include <iostream>
#include <string>
#include "combate.h"
#include "tiendas.h"
#include "misiones.h"
const int NumEnemigos = 2;
const int NumNPCs = 3;
const int NumObjetos = 6;
const int NumMisiones = 2;
const int NumTiendas = 1;
const int NumFilas = 5;
const int NumColumnas = 5;

class gestor_jugabilitat
{
public:
	gestor_jugabilitat() {}
	~gestor_jugabilitat() {}
	void fer_accions(int new_sock, std::string usuari, int id, std::string nom);
};

void gestor_jugabilitat::fer_accions(int new_sock, std::string usuari, int id, std::string nom)
{
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
		mision[i] = misiones(usuari, id, i, &objeto[0], &enemigo[0],NumFilas);
	}
	tienda tiendas[NumTiendas + 1];
	for (int i = 0; i < NumTiendas + 1; i++) {
		tiendas[i] = tienda(i, &objeto[0]);
	}
	npcs npc[NumNPCs+1];
	for (int i = 0; i < NumNPCs + 1; i++) {
		npc[i] = npcs(usuari, id, i, &objeto[0], &mision[0],&tiendas[0], NumFilas);
	}
	
	map mapa = map(usuari, id, &objeto[0], &enemigo[0],NumFilas,NumColumnas);
	inventario invent = inventario(usuari, id, &objeto[0]);
	jugador Usuario1 = jugador(usuari, id, &invent,&mapa,&mision[0]);

	bool finish = false; // if accio es 'S', finish es true
	char buffer[1000];
	std::string s; // string que es passa per referencia a traves de les funcions de les clases entitat
	// per enviar amb el socket

	char accion;
	memset(buffer, '\0', 1000);
	strcpy(buffer, "Clases cargadas\n");
	strcpy(buffer + strlen(buffer), "Utiliza H para ver las acciones disponibles.\n\n\n");
	send(new_sock, buffer, strlen(buffer), 0);

	while (!finish)
	{
		memset(buffer, '\0', 100);
		strcpy(buffer, "Introduce tu accion: ");
		send(new_sock, buffer, strlen(buffer), 0);

		memset(buffer, '\0', 100);
		recv(new_sock, buffer, 3, 0);
		std::string aux(buffer);
		aux.erase(aux.size()-2);
		accion = aux[0];

		switch (accion) {
		case 'A':
		{
			if (Usuario1.getEnemigo() == 0) {
				memset(buffer, '\0', 1000);
				strcpy(buffer, "No hay enemigos\n\n");
				send(new_sock, buffer, strlen(buffer), 1000);
			}
			else {
				memset(buffer, '\0', 1000);
				strcpy(buffer, "Cargando enemigo para pelear.\n");
				send(new_sock, buffer, strlen(buffer), 1000);
				combate pelea(enemigo[Usuario1.getEnemigo()], &Usuario1);
				int muerto = 0;
				while ((!muerto) && (accion != 'E')) {	//Enemigo vivo y no queremos escapar
					switch (accion) {
					case 'A':
						muerto = pelea.atacar(s);
						memset(buffer, '\0', 1000);
						strcpy(buffer, s.c_str());
						send(new_sock, buffer, strlen(buffer), 1000);
						break;
					case 'O': 
					{
						Usuario1.consultarInventario(NumObjetos, s);
						memset(buffer, '\0', 1000);
						strcpy(buffer, s.c_str());
						send(new_sock, buffer, strlen(buffer), 1000);

						memset(buffer, '\0', 1000);
						strcpy(buffer, "Que objeto quieres usar? (indica la posicion del objeto): ");
						send(new_sock, buffer, strlen(buffer), 0);
						
						int id;
						memset(buffer, '\0', 1000);
						recv(new_sock, buffer, 1, 0);
						id = atoi(buffer);
						
						memset(buffer, '\0', 1000);
						strcpy(buffer, "\n");
						send(new_sock, buffer, strlen(buffer), 0);
						
						Usuario1.usarObjeto(id);
						break;
					}
					case 'E':
						memset(buffer, '\0', 1000);
						strcpy(buffer, "Salistes del combate\n");
						send(new_sock, buffer, strlen(buffer), 0);
						break;
					default:
						memset(buffer, '\0', 1000);
						strcpy(buffer, "Accion invalida\n");
						send(new_sock, buffer, strlen(buffer), 0);
						break;
					}
					if (accion != 'E' && muerto ==0) {
						memset(buffer, '\0', 1000);
						strcpy(buffer, "\nPuedes atacar(A), usar objeto(O), escapar(E) :");
						send(new_sock, buffer, strlen(buffer), 0);
						
						memset(buffer, '\0', 1000);
						recv(new_sock, buffer, 3, 0);
						std::string aux(buffer);
						aux.erase(aux.size()-2);
						accion = aux[0];
						
						memset(buffer, '\0', 1000);
						strcpy(buffer, "\n\n");
						send(new_sock, buffer, strlen(buffer), 0);
						}
					else {
						if (muerto==1) {
							memset(buffer, '\0', 1000);
							strcpy(buffer, "\nGAME OVER");
							send(new_sock, buffer, strlen(buffer), 0);
							accion = 'S';
						}
						if (muerto == 2) {
							Usuario1.eliminarEnemigo();
						}
					}
				}
			}
			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);
			break;
		}
		case 'R':
			
			Usuario1.recoger_objeto(Usuario1.getObjetoZona(), Usuario1.getCantObjZona(), 0, s);

			memset(buffer, '\0', 1000);
			strcpy(buffer, s.c_str());
			send(new_sock, buffer, strlen(buffer), 0);

			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);
			
			accion = ' ';
			break;

		case 'L':
			Usuario1.Zoom(s);

			memset(buffer, '\0', 1000);
			strcpy(buffer, s.c_str());
			send(new_sock, buffer, strlen(buffer), 0);

			while (accion != 'P') {
				memset(buffer, '\0', 1000);
				strcpy(buffer, "Elige la direccion a la que ir: NORTE (N) , SUR (S), ESTE (E) , OESTE (O)\nO para de moverte (P) :");
				send(new_sock, buffer, strlen(buffer), 0);
				
				memset(buffer, '\0', 1000);
				recv(new_sock, buffer, 3, 0);
				std::string aux(buffer);
				aux.erase(aux.size()-2);
				accion = aux[0];
				
				memset(buffer, '\0', 1000);
				strcpy(buffer, "\n");
				
				send(new_sock, buffer, strlen(buffer), 0);
				switch (accion) {
				case 'N':
					Usuario1.moverArriba(s);

					memset(buffer, '\0', 1000);
					strcpy(buffer, s.c_str());
					send(new_sock, buffer, strlen(buffer), 0);

					if (Usuario1.hablar_NPC() != 0) {
						memset(buffer, '\0', 1000);
						strcpy(buffer, (npc[Usuario1.hablar_NPC()].getNombre()).c_str());
						strcpy(buffer + strlen(buffer), "\n");
						send(new_sock, buffer, strlen(buffer), 0);
					}
					break;
				case 'S':
					Usuario1.moverAbajo(s);

					memset(buffer, '\0', 1000);
					strcpy(buffer, s.c_str());
					send(new_sock, buffer, strlen(buffer), 0);

					if (Usuario1.hablar_NPC() != 0) {
						memset(buffer, '\0', 1000);
						strcpy(buffer, (npc[Usuario1.hablar_NPC()].getNombre()).c_str());
						strcpy(buffer + strlen(buffer), "\n");
						send(new_sock, buffer, strlen(buffer), 0);
					}
					break;
				case 'E':
					Usuario1.moverDerecha(s);

					memset(buffer, '\0', 1000);
					strcpy(buffer, s.c_str());
					send(new_sock, buffer, strlen(buffer), 0);

					if (Usuario1.hablar_NPC() != 0) {
						memset(buffer, '\0', 1000);
						strcpy(buffer, (npc[Usuario1.hablar_NPC()].getNombre()).c_str());
						strcpy(buffer + strlen(buffer), "\n");
						send(new_sock, buffer, strlen(buffer), 0);
					}
					break;
				case 'O':
					Usuario1.moverIzquierda(s);

					memset(buffer, '\0', 1000);
					strcpy(buffer, s.c_str());
					send(new_sock, buffer, strlen(buffer), 0);

					if (Usuario1.hablar_NPC() != 0) {
						memset(buffer, '\0', 1000);
						strcpy(buffer, (npc[Usuario1.hablar_NPC()].getNombre()).c_str());
						strcpy(buffer + strlen(buffer), "\n");
						send(new_sock, buffer, strlen(buffer), 0);
					}
					break;
				case 'P':
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Has parado de moverte");
					send(new_sock, buffer, strlen(buffer), 0);
					break;
				default:
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Accion invalida");
					send(new_sock, buffer, strlen(buffer), 0);
					break;
				}
				memset(buffer, '\0', 1000);
				strcpy(buffer, "	---------\n");
				send(new_sock, buffer, strlen(buffer), 0);
			}
			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);
			accion = ' ';
			break;
		case 'N':
			if (npc[Usuario1.hablar_NPC()].getZona() !=0) {
				if (npc[Usuario1.hablar_NPC()].getMision() != 0) {	//Tiene misiones
					if (Usuario1.ComprobarMisionComplet(Usuario1.hablar_NPC())) {
						memset(buffer, '\0', 1000);
						strcpy(buffer, (npc[Usuario1.hablar_NPC()].getTexto2()).c_str());
						strcpy(buffer + strlen(buffer), "\n");
						send(new_sock, buffer, strlen(buffer), 0);
					}
					else {
						memset(buffer, '\0', 1000);
						strcpy(buffer, (npc[Usuario1.hablar_NPC()].getTexto1()).c_str());
						strcpy(buffer + strlen(buffer), "\n");
						send(new_sock, buffer, strlen(buffer), 0);
						if (!Usuario1.ComprobarMisionActiva(Usuario1.hablar_NPC())) {	//No está activa
							do {
								memset(buffer, '\0', 1000);
								strcpy(buffer, "Aceptar mision? Si (S), No(N):");
								send(new_sock, buffer, strlen(buffer), 0);

								memset(buffer, '\0', 1000);
								recv(new_sock, buffer, 3, 0);
								std::string aux(buffer);
								aux.erase(aux.size()-2);
								accion = aux[0];

								switch (accion) {
								case 'S':
									memset(buffer, '\0', 1000);
									strcpy(buffer, "\nAceptastes la mision.\n");
									send(new_sock, buffer, strlen(buffer), 0);
									Usuario1.AceptarMision(npc[Usuario1.hablar_NPC()].getMision());
									break;
								case'N':
									memset(buffer, '\0', 1000);
									strcpy(buffer, "\nNo aceptastes la mision.\n");
									send(new_sock, buffer, strlen(buffer), 0);
									break;
								default:
									memset(buffer, '\0', 1000);
									strcpy(buffer, "\n");
									strcpy(buffer + strlen(buffer), &accion);
									strcpy(buffer + strlen(buffer), " :no es una opcion valida.\n");
									send(new_sock, buffer, strlen(buffer), 0);
									break;
								}
							} while (accion != 'S' && accion != 'N');
						}
						else {
							do {
								memset(buffer, '\0', 1000);
								strcpy(buffer, "Puedes :Completar mision (C), cancelar mision(E), salir(S):");
								send(new_sock, buffer, strlen(buffer), 0);

								memset(buffer, '\0', 1000);
								recv(new_sock, buffer, 3, 0);
								std::string aux(buffer);
								aux.erase(aux.size()-2);
								accion = aux[0];

								memset(buffer, '\0', 1000);
								strcpy(buffer, "\n");
								send(new_sock, buffer, strlen(buffer), 0);

								switch (accion) {
								case 'C':
									if (Usuario1.MisiongetEnemigoCantidad(npc[Usuario1.hablar_NPC()].getMision())==0) {//Enemigos derrotados
										if (Usuario1.ComprobarObjMision(npc[Usuario1.hablar_NPC()].getMision()) == true) {//Objetos en inventario
											Usuario1.completarMision(npc[Usuario1.hablar_NPC()].getMision(), s);
											memset(buffer, '\0', 1000);
											strcpy(buffer, s.c_str());
											send(new_sock, buffer, strlen(buffer), 0);
										}
										else {
											memset(buffer, '\0', 1000);
											strcpy(buffer, "No tienes lo necesario para completar la mision.\n");
											send(new_sock, buffer, strlen(buffer), 0);
										}
									}
									else {
										memset(buffer, '\0', 1000);
										strcpy(buffer, "No has derrotado a los enemigos necesarios.\n");
										send(new_sock, buffer, strlen(buffer), 0);
									}
									break;
								case'E':
									memset(buffer, '\0', 1000);
									strcpy(buffer, "Cancelastes la mision.\n");
									send(new_sock, buffer, strlen(buffer), 0);
									Usuario1.AceptarMision(npc[Usuario1.hablar_NPC()].getMision());
									break;
								case 'S':
									memset(buffer, '\0', 1000);
									strcpy(buffer, "Dejastes de hablar.\n");
									send(new_sock, buffer, strlen(buffer), 0);
									break;
								default:
									memset(buffer, '\0', 1000);
									strcpy(buffer, " :no es una opcion valida.\n");
									send(new_sock, buffer, strlen(buffer), 0);
									break;
								}
							} while (accion != 'C' && accion != 'E' && accion != 'S');
						}
					}
				}
				else {	//No tienes misiones
					if (npc[Usuario1.hablar_NPC()].getTienda() != 0) {	//con tienda
						memset(buffer, '\0', 1000);
						strcpy(buffer, (npc[Usuario1.hablar_NPC()].getTexto1()).c_str());
						strcpy(buffer, "\n");
						send(new_sock, buffer, strlen(buffer), 0);
						do {
							memset(buffer, '\0', 1000);
							strcpy(buffer, "Comprar (C),Vender(V),salir(S):");
							send(new_sock, buffer, strlen(buffer), 0);

							memset(buffer, '\0', 1000);
							recv(new_sock, buffer, 3, 0);
							std::string aux(buffer);
							aux.erase(aux.size()-2);
							accion = aux[0];

							memset(buffer, '\0', 1000);
							strcpy(buffer, "\n");
							send(new_sock, buffer, strlen(buffer), 0);

							switch (accion) {
							case 'C':
								npc[Usuario1.hablar_NPC()].muestraTienda(s);

								memset(buffer, '\0', 1000);
								strcpy(buffer, s.c_str());
								send(new_sock, buffer, strlen(buffer), 0);

								do {
									memset(buffer, '\0', 1000);
									strcpy(buffer, "Hay algo que te interese? Si(S), No(N):");
									send(new_sock, buffer, strlen(buffer), 0);

									memset(buffer, '\0', 1000);
									recv(new_sock, buffer, 3, 0);
									std::string aux(buffer);
									aux.erase(aux.size()-2);
									accion = aux[0];

									memset(buffer, '\0', 1000);
									strcpy(buffer, "\n");
									send(new_sock, buffer, strlen(buffer), 0);

									switch (accion){
									case 'S': {
										memset(buffer, '\0', 1000);
										strcpy(buffer, "Que quieres comprar?(indica la posicion del objeto que quieras comprar):");
										send(new_sock, buffer, strlen(buffer), 0);

										int pos;
										memset(buffer, '\0', 1000);
										recv(new_sock, buffer, 1, 0);
										pos = atoi(buffer);

										memset(buffer, '\0', 1000);
										strcpy(buffer, "\n");
										send(new_sock, buffer, strlen(buffer), 0);

										int precio;
										int objetoID;

										if (npc[Usuario1.hablar_NPC()].comprar(pos, objetoID, precio, s)) {	//posicion correcta, existe el objeto
											memset(buffer, '\0', 1000);
											strcpy(buffer, s.c_str());
											send(new_sock, buffer, strlen(buffer), 0);

											Usuario1.comprar(objetoID, precio, s);

											memset(buffer, '\0', 1000);
											strcpy(buffer, s.c_str());
											send(new_sock, buffer, strlen(buffer), 0);
										}
										else
										{
											memset(buffer, '\0', 1000);
											strcpy(buffer, s.c_str());
											send(new_sock, buffer, strlen(buffer), 0);
										}
									}
										break;
									case 'N':
										memset(buffer, '\0', 1000);
										strcpy(buffer, "De acuerdo, vuelve cuando quieras c:\n");
										send(new_sock, buffer, strlen(buffer), 0);
										break;
									default:
										memset(buffer, '\0', 1000);
										strcpy(buffer, " :no es una opcion valida.\n");
										send(new_sock, buffer, strlen(buffer), 0);
										break;
										}
								} while (accion != 'S' && accion != 'N');
								break;
							case'V': {
								Usuario1.consultarInventario(NumObjetos, s);

								memset(buffer, '\0', 1000);
								strcpy(buffer, s.c_str());
								send(new_sock, buffer, strlen(buffer), 0);

								memset(buffer, '\0', 1000);
								strcpy(buffer, "Que quieres vender?(indica la posicion del objeto que quieras vender):");
								send(new_sock, buffer, strlen(buffer), 0);
								
								int pos;
								memset(buffer, '\0', 1000);
								recv(new_sock, buffer, 1, 0);
								pos = atoi(buffer);

								memset(buffer, '\0', 1000);
								strcpy(buffer, "\n");
								send(new_sock, buffer, strlen(buffer), 0);

								if (Usuario1.muestraPrecioVenta(pos, s) != 0) {
									memset(buffer, '\0', 1000);
									strcpy(buffer, s.c_str());
									send(new_sock, buffer, strlen(buffer), 0);

									memset(buffer, '\0', 1000);
									strcpy(buffer, "Confirmar venta (V), cancelar venta(C):");
									send(new_sock, buffer, strlen(buffer), 0);

									memset(buffer, '\0', 1000);
									recv(new_sock, buffer, 3, 0);
									std::string aux(buffer);
									aux.erase(aux.size()-2);
									accion = aux[0];

									memset(buffer, '\0', 1000);
									strcpy(buffer, "\n");
									send(new_sock, buffer, strlen(buffer), 0);

									do {
										switch (accion) {
										case'V':
											Usuario1.vender(pos);
											break;
										case'C':
											memset(buffer, '\0', 1000);
											strcpy(buffer, "No vendistes nada.\n");
											send(new_sock, buffer, strlen(buffer), 0);
											break;
										default:
											memset(buffer, '\0', 1000);
											strcpy(buffer, " :no es una opcion valida.\n");
											send(new_sock, buffer, strlen(buffer), 0);
											break;
										}
									} while (accion != 'V' && accion != 'C');
								}
								break;
							}
							case'S':
								memset(buffer, '\0', 1000);
								strcpy(buffer, "Salistes de la tienda.\n");
								send(new_sock, buffer, strlen(buffer), 0);
								break;
							default:
								memset(buffer, '\0', 1000);
								strcpy(buffer, " :no es una opcion valida.\n");
								send(new_sock, buffer, strlen(buffer), 0);
								break;
							}
						} while (accion != 'S');
						
					}
					else {	//sin mision ni tienda
						memset(buffer, '\0', 1000);
						strcpy(buffer, (npc[Usuario1.hablar_NPC()].getTexto1()).c_str());
						strcpy(buffer + strlen(buffer), "\n");
						send(new_sock, buffer, strlen(buffer), 0);
					}
				}
			}
			else {
				memset(buffer, '\0', 1000);
				strcpy(buffer, "No hay NPCS en esta zona\n");
				send(new_sock, buffer, strlen(buffer), 0);
			}
			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);
			accion = ' ';
			break;
		case 'H':
			memset(buffer, '\0', 1000);
			strcpy(buffer, "Las acciones posibles son:\n-Iniciar combate(A)");
			strcpy(buffer + strlen(buffer), "\n-moverse (L)");
			strcpy(buffer + strlen(buffer), "\n-Recoger objeto (R)");
			strcpy(buffer + strlen(buffer), "\n-Hablar con un npc (N)");
			strcpy(buffer + strlen(buffer), "\n-Mostrar crafteos (C)");
			strcpy(buffer + strlen(buffer), "\n-Abrir inventario (I)");
			strcpy(buffer + strlen(buffer), "\n-Abrir mapa (M)");
			strcpy(buffer + strlen(buffer), "\n-Abrir misiones (Q)");
			strcpy(buffer + strlen(buffer), "\n-Ver datos personaje (P)");
			strcpy(buffer + strlen(buffer), "\n-Ver datos barco (B)");
			strcpy(buffer + strlen(buffer), "\n-Ayuda (H)");
			strcpy(buffer + strlen(buffer), "\n-Guardar (G)");
			strcpy(buffer + strlen(buffer), "\n-Salir partida (S)\n");
			strcpy(buffer + strlen(buffer), "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);
			accion = ' ';
			break;
		case 'G':
			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);
			accion = ' ';
			break;
		case 'I':
			Usuario1.consultarInventario(NumObjetos, s);

			memset(buffer, '\0', 1000);
			strcpy(buffer, s.c_str());
			send(new_sock, buffer, strlen(buffer), 0);

			while (accion != 'S') {
				memset(buffer, '\0', 1000);
				strcpy(buffer, "\nPuedes: ver descripcion objeto(D), usar objeto(U),eliminar objeto (E)\nO cerrar inventario(S) :");
				send(new_sock, buffer, strlen(buffer), 0);

				memset(buffer, '\0', 1000);
				recv(new_sock, buffer, 3, 0);
				std::string aux(buffer);
				aux.erase(aux.size()-2);
				accion = aux[0];

				switch (accion) {
				case 'D': {
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Introduce la posición del objeto del cual quieres ver la descripcion: ");
					send(new_sock, buffer, strlen(buffer), 0);

					int id;
					memset(buffer, '\0', 1000);
					recv(new_sock, buffer, 1, 0);
					id = atoi(buffer);

					memset(buffer, '\0', 1000);
					strcpy(buffer, "\n");
					send(new_sock, buffer, strlen(buffer), 0);

					Usuario1.muestraObjeto(id, s);
					memset(buffer, '\0', 1000);
					strcpy(buffer, s.c_str());
					send(new_sock, buffer, strlen(buffer), 0);
				}
					break;
				case 'U': {
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Que objeto quieres usar? (indica la posicíon del objeto): ");
					send(new_sock, buffer, strlen(buffer), 0);

					int id;
					memset(buffer, '\0', 1000);
					recv(new_sock, buffer, 1, 0);
					id = atoi(buffer);

					memset(buffer, '\0', 1000);
					strcpy(buffer, "\n");
					send(new_sock, buffer, strlen(buffer), 0);

					Usuario1.usarObjeto(id);

					Usuario1.consultarInventario(NumObjetos, s);

					memset(buffer, '\0', 1000);
					strcpy(buffer, s.c_str());
					send(new_sock, buffer, strlen(buffer), 0);
					break;
				}
				case 'E': {
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Que objeto quieres eliminar? (indica la posicíon del objeto): ");
					send(new_sock, buffer, strlen(buffer), 0);

					int id;
					memset(buffer, '\0', 1000);
					recv(new_sock, buffer, 1, 0);
					id = atoi(buffer);

					memset(buffer, '\0', 1000);
					strcpy(buffer, "\n");
					send(new_sock, buffer, strlen(buffer), 0);

					Usuario1.eliminarInventario(id);
					Usuario1.consultarInventario(NumObjetos, s);

					memset(buffer, '\0', 1000);
					strcpy(buffer, s.c_str());
					send(new_sock, buffer, strlen(buffer), 0);
					break;
				}
				case 'S':
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Cerrastes el inventario\n");
					send(new_sock, buffer, strlen(buffer), 0);
					break;
				default:
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Accion invalida\n");
					send(new_sock, buffer, strlen(buffer), 0);
					break;
				}
				memset(buffer, '\0', 1000);
				strcpy(buffer, "	---------\n");
				send(new_sock, buffer, strlen(buffer), 0);
			}
			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);
			accion = ' ';
			break;
		case 'M':
			Usuario1.consultarMapa(s);

			memset(buffer, '\0', 1000);
			strcpy(buffer, s.c_str());
			send(new_sock, buffer, strlen(buffer), 0);

			while (accion != 'S') {
				memset(buffer, '\0', 1000);
				strcpy(buffer, "\nPuedes: Hacer Zoom(z), cerrar el mapa(S) :");
				send(new_sock, buffer, strlen(buffer), 0);

				memset(buffer, '\0', 1000);
				recv(new_sock, buffer, 3, 0);
				std::string aux(buffer);
				aux.erase(aux.size()-2);
				accion = aux[0];

				memset(buffer, '\0', 1000);
				strcpy(buffer, "\n");
				send(new_sock, buffer, strlen(buffer), 0);

				switch (accion) {
				case 'Z':
					Usuario1.Zoom(s);
					memset(buffer, '\0', 1000);
					strcpy(buffer, s.c_str());
					send(new_sock, buffer, strlen(buffer), 0);
					break;
				case 'S':
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Cerrastes el mapa\n");
					send(new_sock, buffer, strlen(buffer), 0);
					break;
				default:
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Accion invalida\n");
					send(new_sock, buffer, strlen(buffer), 0);
					break;

				}
			}
			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);
			accion = ' ';
			break;
		case 'Q':
			Usuario1.abrir_missiones(NumMisiones, s);

			memset(buffer, '\0', 1000);
			strcpy(buffer, s.c_str());
			send(new_sock, buffer, strlen(buffer), 0);

			while (accion != 'C') {
				memset(buffer, '\0', 1000);
				strcpy(buffer, "\nPuedes: Ver una mision en detalle(D), cerrar la pantalla de misiones(C) :");
				send(new_sock, buffer, strlen(buffer), 0);

				memset(buffer, '\0', 1000);
				recv(new_sock, buffer, 3, 0);
				std::string aux(buffer);
				aux.erase(aux.size()-2);
				accion = aux[0];

				memset(buffer, '\0', 1000);
				strcpy(buffer, "\n");
				send(new_sock, buffer, strlen(buffer), 0);

				switch (accion) {
				case 'D':
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Que mision quieres ver? (indica la posicíon de la mision): ");
					send(new_sock, buffer, strlen(buffer), 0);

					int id;
					memset(buffer, '\0', 1000);
					recv(new_sock, buffer, 1, 0);
					id = atoi(buffer);

					memset(buffer, '\0', 1000);
					strcpy(buffer, "\n");
					send(new_sock, buffer, strlen(buffer), 0);

					memset(buffer, '\0', 1000);
					strcpy(buffer, "	--------	--------\n");
					send(new_sock, buffer, strlen(buffer), 0);

					Usuario1.abrir_mission(id, NumMisiones, s);

					memset(buffer, '\0', 1000);
					strcpy(buffer, s.c_str());
					send(new_sock, buffer, strlen(buffer), 0);
					
					memset(buffer, '\0', 1000);
					strcpy(buffer, "	--------	--------\n");
					send(new_sock, buffer, strlen(buffer), 0);

					break;
				case 'C':
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Cerrastes la pantalla de misiones\n");
					send(new_sock, buffer, strlen(buffer), 0);
					break;
				default:
					memset(buffer, '\0', 1000);
					strcpy(buffer, "Accion invalida\n");
					send(new_sock, buffer, strlen(buffer), 0);
					break;
				}
			}
			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);

			accion = ' ';
			break;
		case 'S':
			finish = true;

			memset(buffer, '\0', 1000);
			strcpy(buffer, "ADIOS C=\n");
			send(new_sock, buffer, strlen(buffer), 0);

			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);
			break;
		case 'P':
			Usuario1.consultarPersonaje(s);

			memset(buffer, '\0', 1000);
			strcpy(buffer, s.c_str());
			send(new_sock, buffer, strlen(buffer), 0);

			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);

			accion = ' ';
			break;
		case 'B':
			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);

			accion = ' ';
			break;
		case 'C':
			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);

			accion = ' ';
			break;
		default:
			memset(buffer, '\0', 1000);
			strcpy(buffer, "Accion invalida\n");
			send(new_sock, buffer, strlen(buffer), 0);

			memset(buffer, '\0', 1000);
			strcpy(buffer, "--------------------------------------------------------------------------------\n");
			send(new_sock, buffer, strlen(buffer), 0);

			accion = ' ';
			break;
		}
	}
}