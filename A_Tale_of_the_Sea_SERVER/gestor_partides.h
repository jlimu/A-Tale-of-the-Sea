#pragma once
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include "partida.h"
#include <experimental/filesystem>
#include <sstream>
namespace fs = std::experimental::filesystem;
using namespace std;

class gestor_partides
{
public:
	gestor_partides(string usuari) { first_partida = NULL; gestor_partides::carregar(usuari); }

	void carregar(string nom);
	string mostrar_partides();
	bool iniciar(int &id, string nom, string usuari);
	bool cargar(int num_partida);
	bool eliminar(int num_partida, string usuari);

private:
	Partida *first_partida;
};

void gestor_partides::carregar(string usuari)
{
	ifstream f;
	f.open("Usuarios_Partidas/" + usuari + "/partides.txt");

	if (f.is_open())
	{
		Partida *pre = NULL;
		Partida *ptr = NULL;
		Partida *ult = NULL;

		int id;
		string jugador;

		string aux;

		f >> aux >> id >> aux >> jugador;
		ptr = new Partida(id, jugador);
		first_partida = ptr;

		pre = ptr;
		ptr = ptr->getNext();

		while (!f.eof())
		{
			f >> aux >> id >> aux >> jugador;
			
			ptr = new Partida(id, jugador);
			pre->setNext(ptr);

			ult = pre;
			pre = ptr;
			ptr = ptr->getNext();
		}
		ult->setNext(NULL);
		delete pre;

		f.close();
	}
}

string gestor_partides::mostrar_partides()
{
	Partida *ptr = first_partida;

	string partides;

	partides = "Id: 1, Jugador " + ptr->getNomJugador() + "\n";
	ptr = ptr->getNext();
	partides += "Id: 2, Jugador " + ptr->getNomJugador() + "\n";
	ptr = ptr->getNext();
	partides += "Id: 3, Jugador " + ptr->getNomJugador() + "\n";
	ptr = ptr->getNext();
	partides += "Id: 4, Jugador " + ptr->getNomJugador() + "\n";
	ptr = ptr->getNext();
	partides += "Id: 5, Jugador " + ptr->getNomJugador() + "\n";
	ptr = ptr->getNext();

	return partides;
}

bool gestor_partides::iniciar(int &id, string nom, string usuari)
{
	bool partida = false;
	Partida *prev = NULL;
	Partida *ptr = first_partida;
	Partida *next = NULL;

	bool trobat = false;

	while (ptr != NULL && !trobat)
	{
		if (ptr->getNomJugador() == "[BUIT]")
		{
			trobat = true;
		}
		else
		{
			prev = ptr;
			ptr = ptr->getNext();
		}
	}

	if (trobat)
	{
		partida = true;

		next = ptr->getNext();
		int aux_id = ptr->getId();
		id = aux_id;
		delete ptr;
		ptr = new Partida(aux_id, nom);
		ptr->setNext(next);
		if (prev != NULL)
			prev->setNext(ptr);

		ofstream f;
		f.open("Usuarios_Partidas/" + usuari + "/partides.txt");
		if (f.is_open())
		{
			Partida *p = first_partida;
			while (p != NULL)
			{
				f << "id " << p->getId() << " nom " << p->getNomJugador() << endl;
				p = p->getNext();
			}
			f.close();
		}
	}

	return partida;
}

bool gestor_partides::cargar(int num_partida)
{
	bool trobat = false;
	Partida *ptr = first_partida;
	int count = 1;

	while (ptr != NULL && !trobat)
	{
		if (count == num_partida && ptr->getNomJugador() != "[BUIT]")
			trobat = true;
		else
		{
			ptr = ptr->getNext();
			count++;
		}
	}

	return trobat;
}

bool gestor_partides::eliminar(int num_partida, string usuari)
{
	bool trobat = false;
	Partida *pre = NULL;
	Partida *ptr = first_partida;
	int count = 1;

	while (ptr != NULL && !trobat)
	{
		if (count == num_partida && ptr->getNomJugador() != "[BUIT]")
			trobat = true;
		else
		{
			pre = ptr;
			ptr = ptr->getNext();
			count++;
		}
	}

	if (trobat)
	{
		int aux_id = count;
		Partida *next = ptr->getNext();
		delete ptr;
		ptr = new Partida(aux_id, "[BUIT]");
		if (pre != NULL)
			pre->setNext(ptr);
		ptr->setNext(next);

		fs::remove_all("Usuarios_Partidas/" + usuari + "/" + to_string(aux_id));

		stringstream ss;
		fs::path p;

		ss << "Usuarios_Partidas/" + usuari + "/" + to_string(aux_id);
		p = ss.str();

		fs::create_directory(p);
		fs::copy("datos/default", p, fs::copy_options::recursive);

		ofstream f_inventari("Usuarios_Partidas/" + usuari + "/" + to_string(aux_id) + "/inventario.txt");
		f_inventari << "ID\tCANTIDAD" << endl;
		for (int i = 0; i < 10; i++)
		{
			f_inventari << "0\t0";
			if (i != 9)
				cout << endl;
		}
		f_inventari.close();

		ofstream f_jugador("Usuarios_Partidas/" + usuari + "/" + to_string(aux_id) + "/jugador.txt");
		f_jugador << "PosX\t0" << endl;
		f_jugador << "PosY\t4" << endl;
		f_jugador << "nombre\t" << usuari << endl;
		f_jugador << "vida\t7" << endl;
		f_jugador << "vidaMax\t10" << endl;
		f_jugador << "ataque\t5" << endl;
		f_jugador << "defensa\t3" << endl;
		f_jugador << "dinero\t200" << endl;
		f_jugador << "arma\t0" << endl;
		f_jugador << "armadura\t0";
		f_jugador.close();

		ofstream f_vaixell("Usuarios_Partidas/" + usuari + "/" + to_string(aux_id) + "/vaixell.txt");
		f_vaixell << "id\t0" << endl;
		f_vaixell << "vida\t5" << endl;
		f_vaixell << "defensa\t6" << endl;
		f_vaixell << "dany\t7";
		f_vaixell.close();

		ofstream f("Usuarios_Partidas/" + usuari + "/partides.txt");
		if (f.is_open())
		{
			count = 1;
			ptr = first_partida;
			while (ptr != NULL)
			{
				f << "id " << count << " nom " << ptr->getNomJugador() << endl;
				ptr = ptr->getNext();
				count++;
			}
			f.close();
		}
	}

	return trobat;
}
