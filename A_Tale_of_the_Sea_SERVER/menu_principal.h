#pragma once
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include "gestor_partides.h"

class menu_principal
{
public:
	menu_principal() {}
	~menu_principal() {}
	int mp(int new_sock, string usuari, bool &entra_partida, int &id, string &nom);
	void iniciar_partida(int new_sock, gestor_partides GP, string usuari, int &id, string &nom, int &finish);
	void cargar_partida(int new_sock, gestor_partides GP, int &finish, int &num_partida);
	void eliminar_partida(int new_sock, gestor_partides GP, string usuari, int &finish);
};

int menu_principal::mp(int new_sock, string usuari, bool &entra_partida, int &id, string &nom)
{
	char buffer[1000];
	int finish = -1;
	gestor_partides GP(usuari);

	int opcio;
	string partides;

	memset(buffer, '\0', 1000);
	strcpy(buffer, "Benvingut al menú principal, ");
	strcpy(buffer + strlen(buffer), usuari.c_str());
	strcpy(buffer + strlen(buffer), "\n\n");
	send(new_sock, buffer, strlen(buffer), 0);

	do {
		memset(buffer, '\0', 1000);
		strcpy(buffer, "\nSeleccioni opcio de partida:\n");
		strcpy(buffer + strlen(buffer), "1. Iniciar\n");
		strcpy(buffer + strlen(buffer), "2. Cargar\n");
		strcpy(buffer + strlen(buffer), "3. Eliminar\n");
		strcpy(buffer + strlen(buffer), "4. Mostrar\n");
		strcpy(buffer + strlen(buffer), "5. Sortir\n\n");
		send(new_sock, buffer, strlen(buffer), 0);

		do {
			memset(buffer, '\0', 1000);
			recv(new_sock, buffer, 1000, 0);
			opcio = atoi(buffer);
		} while (opcio < 1 && opcio > 4);

		switch (opcio)
		{
			case 1:
			menu_principal::iniciar_partida(new_sock, GP, usuari, id, nom, finish);
			entra_partida = true;
			break;

			case 2:
			menu_principal::cargar_partida(new_sock, GP, finish, id);
			entra_partida = true;
			break;

			case 3:
			menu_principal::eliminar_partida(new_sock, GP, usuari, finish);
			break;

			case 4:
			partides = GP.mostrar_partides();
			memset(buffer, '\0', 1000);
			strcpy(buffer, partides.c_str());
			send(new_sock, buffer, strlen(buffer), 0);
			break;

			case 5:
			finish = 0;
			break;

			default:
			memset(buffer, '\0', 1000);
			strcpy(buffer, "Opcio no valida\n\n");
			send(new_sock, buffer, strlen(buffer), 0);
		}

		GP.carregar(usuari);
	} while (finish == -1);
	
	return 0;
}

void menu_principal::iniciar_partida(int new_sock, gestor_partides GP, string usuari, int &id, string &nom, int &finish)
{
	char buffer[100];
	memset(buffer, '\0', 100);
	strcpy(buffer, "Posi el nom del teu jugador\n");
	send(new_sock, buffer, strlen(buffer), 0);
	memset(buffer, '\0', 100);
	recv(new_sock, buffer, 100, 0);

	string aux_nom(buffer);
	aux_nom.erase(aux_nom.size() - 2);
	nom = aux_nom;

	memset(buffer, '\0', 100);
	if (GP.iniciar(id, nom, usuari))
	{
		strcpy(buffer, "NOVA PARTIDA\n");
		send(new_sock, buffer, strlen(buffer), 0);
		finish = 1;
	}
	else
	{
		strcpy(buffer, "\nJa estas al limit de partides creades\n");
		send(new_sock, buffer, strlen(buffer), 0);
	}
}

void menu_principal::cargar_partida(int new_sock, gestor_partides GP, int &finish, int &num_partida)
{
	char buffer[1000];
	string partides = GP.mostrar_partides();
	memset(buffer, '\0', 1000);
	strcpy(buffer, partides.c_str());
	send(new_sock, buffer, strlen(buffer), 0);
	memset(buffer, '\0', 1000);
	recv(new_sock, buffer, 1, 0);
	int opcio = atoi(buffer);
	memset(buffer, '\0', 1);
	if (GP.cargar(opcio))
	{
		strcpy(buffer, "PARTIDA CARGADA AMB EXIT");
		send(new_sock, buffer, strlen(buffer), 0);
		finish = 1;
		num_partida = opcio;
	}
	else
	{
		strcpy(buffer, "Opcio no valida");
		send(new_sock, buffer, strlen(buffer), 0);
	}
}

void menu_principal::eliminar_partida(int new_sock, gestor_partides GP, string usuari, int &finish)
{
	string partides;
	char buffer[1000];
	partides = GP.mostrar_partides();
	memset(buffer, '\0', 1000);
	strcpy(buffer, partides.c_str());
	send(new_sock, buffer, strlen(buffer), 0);
	memset(buffer, '\0', 1000);
	recv(new_sock, buffer, 1, 0);
	int opcio = atoi(buffer);
	memset(buffer, '\0', 1);
	if (GP.eliminar(opcio, usuari))
	{
		strcpy(buffer, "PARTIDA ELIMINADA AMB EXIT");
		send(new_sock, buffer, 1000, 0);
	}
	else
	{
		strcpy(buffer, "Opcio no valida");
		send(new_sock, buffer, 1000, 0);
	}
}
