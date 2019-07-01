#pragma once
#include<sys/socket.h>
#include<string.h>
#include "gestor_usuaris.h"

class gestor_servidor
{
public:
	gestor_servidor() {}
	~gestor_servidor() {}
	void menu_benvinguda(int new_sock);
	int rebre_accio(int new_sock);
	void envia_succes(int new_sock, int op);
};

void gestor_servidor::menu_benvinguda(int new_sock)
{
	char buffer[1024];
	memset(buffer, '\0', 1024);
	strcpy(buffer, "Benvigut al server d'ATotS\n\n");
	strcpy(buffer + strlen(buffer), "Per entrar utilitzi la comanda login\n");
	strcpy(buffer + strlen(buffer), "Per registrar-se utilitzi la comanda registrar\n");
	strcpy(buffer + strlen(buffer), "Per sortir utilitzi la comanda sortir\n");
	send(new_sock, buffer, strlen(buffer), 0);

	gestor_usuaris GU;
}

int gestor_servidor::rebre_accio(int new_sock)
{
	int valid = 0;
	char buffer[100];
	memset(buffer, '\0', 100);
	recv(new_sock, buffer, 100, 0);
	if (strcmp(buffer, "login\r\n") == 0)
	{
		valid = 1;
	}
	else if (strcmp(buffer, "registrar\r\n") == 0)
	{
		valid = 2;
	}
	else if (strcmp(buffer, "sortir\r\n") == 0)
	{
		valid = 3;
	}
	return valid;
}

void gestor_servidor::envia_succes(int new_sock, int op)
{
	char buffer[100];

	switch (op)
	{
		case 0:
		memset(buffer, '\0', 100);
		strcpy(buffer, "Comanda desconeguda\n");
		send(new_sock, buffer, strlen(buffer), 0);
		break;

		case 1:
		memset(buffer, '\0', 100);
		strcpy(buffer, "Benvingut a ATotS (login)\n");
		send(new_sock, buffer, strlen(buffer), 0);
		break;

		case 2:
		memset(buffer, '\0', 100);
		strcpy(buffer, "Benvingut a ATotS (registrar)\n");
		send(new_sock, buffer, strlen(buffer), 0);
		break;

		case 3:
		memset(buffer, '\0', 100);
		strcpy(buffer, "Sortint del server\n");
		send(new_sock, buffer, strlen(buffer), 0);
	}
}
