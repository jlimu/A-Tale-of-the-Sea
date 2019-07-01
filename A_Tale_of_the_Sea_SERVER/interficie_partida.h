#pragma once
#include <sys/socket.h>
#include <string.h>

#include <string>

#include "gestor_jugabilitat.h"

class interficie_partida
{
public:
	interficie_partida() {}
	~interficie_partida() {}
	void envia_accions(int new_sock, std::string usuari, int id, std::string nom);
};

void interficie_partida::envia_accions(int new_sock, std::string usuari, int id, std::string nom)
{
	char buffer[1000];

	memset(buffer, '\0', 1000);
	strcpy(buffer, "S'ha carregat la partida: id ");
	strcpy(buffer + strlen(buffer), std::to_string(id).c_str());
	strcpy(buffer + strlen(buffer), " nom ");
	strcpy(buffer + strlen(buffer), nom.c_str());
	strcpy(buffer + strlen(buffer), "\n");
	send(new_sock, buffer, strlen(buffer), 0);

	gestor_jugabilitat GJ;
	GJ.fer_accions(new_sock, usuari, id, nom);
}
