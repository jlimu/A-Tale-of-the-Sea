#pragma once
#include<sys/socket.h>
#include<string.h>
#include "gestor_usuaris.h"

class menu_benvinguda
{
public:
	menu_benvinguda() {}
	~menu_benvinguda() {}
	int login(int new_sock, string &usuari);
	int registre(int new_sock, string &usuari);
	void sortir(int new_sock);
};

int menu_benvinguda::login(int new_sock, string &usuari)
{
	bool ret = false;
	char buffer[100];

	int in = -1;
	do {
		memset(buffer, '\0', 100);
		strcpy(buffer, "Nom d'usuari: ");
		send(new_sock, buffer, strlen(buffer), 0);

		memset(buffer, '\0', 100);
		recv(new_sock, buffer, 100, 0);
		
		string nom(buffer);
		nom.erase(nom.size() - 2);

		if (nom == "S" || nom == "s")
			return in;

		usuari = nom;

		memset(buffer, '\0', 100);
		strcpy(buffer, "Contrasenya: ");
		send(new_sock, buffer, strlen(buffer), 0);

		memset(buffer, '\0', 100);
		recv(new_sock, buffer, 100, 0);

		string contrasenya(buffer);
		contrasenya.erase(contrasenya.size() - 2);

		gestor_usuaris GU;
		GU.carregarUsuaris();

		ret = GU.entrarUsuari(nom, contrasenya);
		memset(buffer, '\0', 100);
		if (ret)
		{
			strcpy(buffer, "Login valid\n\nMENU PRINCIPAL\n\n");
			send(new_sock, buffer, strlen(buffer), 0);
			in = 0;
		}
		else
		{
			strcpy(buffer, "Login invalid\nIntenta-ho de nou. 'S' o 's' per sortir.\n");
			send(new_sock, buffer, strlen(buffer), 0);
		}
	} while (in == -1);

	return in;
}

int menu_benvinguda::registre(int new_sock, string &usuari)
{
	bool ret = false;
	char buffer[100];

	int in = -1;
	do {
		memset(buffer, '\0', 100);
		strcpy(buffer, "Nom d'usuari: ");
		send(new_sock, buffer, strlen(buffer), 0);

		memset(buffer, '\0', 100);
		recv(new_sock, buffer, 100, 0);

		string nom(buffer);
		nom.erase(nom.size() - 2);

		if (nom == "S" || nom == "s")
			return in;

		usuari = nom;

		memset(buffer, '\0', 100);
		strcpy(buffer, "E-mail: ");
		send(new_sock, buffer, strlen(buffer), 0);

		memset(buffer, '\0', 100);
		recv(new_sock, buffer, 100, 0);

		string email(buffer);
		email.erase(email.size() - 2);

		memset(buffer, '\0', 100);
		strcpy(buffer, "Contrasenya: ");
		send(new_sock, buffer, strlen(buffer), 0);

		memset(buffer, '\0', 100);
		recv(new_sock, buffer, 100, 0);

		string contrasenya(buffer);
		contrasenya.erase(contrasenya.size() - 2);

		gestor_usuaris GU;
		GU.carregarUsuaris();

		ret = GU.crearUsuari(nom, email, contrasenya);
		memset(buffer, '\0', 100);
		if (ret)
		{
			strcpy(buffer, "Registre valid\n\nMENU PRINCIPAL\n\n");
			send(new_sock, buffer, strlen(buffer), 0);
			in = 0;
		}
		else
		{
			strcpy(buffer, "Registre invalid\nIntenta-ho de nou. 'S' o 's' per sortir.\n");
			send(new_sock, buffer, strlen(buffer), 0);
		}
	} while (in == -1);

	return in;
}

void menu_benvinguda::sortir(int new_sock)
{
	char buffer[100];
	memset(buffer, '\0', 100);
	strcpy(buffer, "Sortint del servidor de A Tale of the Sea...\n...\nConnexio tancada amb exit!\n");
	send(new_sock, buffer, strlen(buffer), 0);
}
