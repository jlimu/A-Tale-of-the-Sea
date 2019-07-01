#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>

#include "interficie_client.h"
#include "menu_benvinguda.h"
#include "menu_principal.h"
#include "interficie_partida.h"


int main()
{
	int sock, new_sock, fr;
	socklen_t addrlen;
	struct sockaddr_in server, client;
	char buffer[100];
	std::string message;
	bool finish = false;
	int opt = 1;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	addrlen = sizeof(struct sockaddr_in);

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	if (bind(sock, (struct sockaddr *)&server, addrlen) < 0)
	{
		return 1;
	}

	listen(sock, 10);

	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(0);

	while (1)
	{
		if ((new_sock = accept(sock, (struct sockaddr *)&client, &addrlen)) > 0)
		{
			if (fork() == 0)
			{
				interficie_client* IC;
				menu_benvinguda* MB;
				menu_principal* MP;
				interficie_partida *IP;
				
				int s = 0;

				int l = -1;
				int r = -1;

				string usuari = "";
				bool entra_partida = false;
				int id = 0;
				string nom = "";

				IC = new interficie_client();
				IC->connectar(new_sock, s);

				switch (s)
				{
					case 1:
					MB = new menu_benvinguda();
					l = MB->login(new_sock, usuari);

					if (l == 0)
					{
						MP = new menu_principal();
						MP->mp(new_sock, usuari, entra_partida, id, nom);

						if (entra_partida)
						{
							IP = new interficie_partida();
							IP->envia_accions(new_sock, usuari, id, nom);
							delete IP;
						}

						delete MP;
					}
					else
						finish = true;

					delete MB;
					break;

					case 2:
					MB = new menu_benvinguda();
					r = MB->registre(new_sock, usuari);

					if (r == 0)
					{
						MP = new menu_principal();
						MP->mp(new_sock, usuari, entra_partida, id, nom);

						if (entra_partida)
						{
							IP = new interficie_partida();
							IP->envia_accions(new_sock, usuari, id, nom);
							delete IP;
						}

						delete MP;
					}
					else
						finish = true;

					delete MB;
					break;

					case 3:
					MB->sortir(new_sock);
					delete MB;
				}

				delete IC;
				exit(0);
			}
			close(new_sock);
		}
	}
}
