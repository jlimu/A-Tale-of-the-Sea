#pragma once
#include<sys/socket.h>
#include<string.h>
#include "gestor_servidor.h"

class interficie_client
{
public:
	interficie_client() {}
	~interficie_client() {}
	void connectar(int new_sock, int &s);
};

void interficie_client::connectar(int new_sock, int &s)
{
	char buffer[100];
	memset(buffer, '\0', 100);
	strcpy(buffer, "Connectant amb el servidor de A Tale of the Sea...\n...\nConnexio establerta!\n\n");
	send(new_sock, buffer, strlen(buffer), 0);

	gestor_servidor GS;
	GS.menu_benvinguda(new_sock);
	do {
		s = GS.rebre_accio(new_sock);
		if (s == 0)
		{
			memset(buffer, '\0', 100);
			strcpy(buffer, "Accio invalida\n\n");
			send(new_sock, buffer, strlen(buffer), 0);
		}

	} while (s <= 0);
	GS.envia_succes(new_sock, s);
}
