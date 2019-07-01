#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <sstream>
#include <string.h>
#include "usuari.h"
namespace fs = std::experimental::filesystem;
using namespace std;

class gestor_usuaris
{
public:
	gestor_usuaris() { first_usuari = NULL; }
	~gestor_usuaris();
	bool entrarUsuari(string nom, string contrasenya);
	void carregarUsuaris();
	void guardarUsuaris();
	void printUsuaris();
	bool crearUsuari(string nom, string email, string contrasenya);
	void eliminarUsuari(string nom);

private:
	Usuari *first_usuari;
};

gestor_usuaris::~gestor_usuaris()
{
	Usuari *current = first_usuari;
	Usuari *next;
	while (current != NULL)
	{
		next = current->getNext();
		delete current;
		current = next;
	}
	first_usuari = NULL;
}

bool gestor_usuaris::entrarUsuari(string nom, string contrasenya)
{
	bool trobat = false;
	Usuari *usuari_ptr = first_usuari;
	while (!trobat && usuari_ptr != NULL)
	{
		string _nom;
		_nom = usuari_ptr->getNom();
		if (_nom == nom)
			trobat = true;
		else
			usuari_ptr = usuari_ptr->getNext();
	}
	
	if (trobat)
	{
		trobat = false;
		string _contrasenya;
		_contrasenya = usuari_ptr->getContrasenya();
		if (_contrasenya == contrasenya)
			trobat = true;
	}

	return trobat;
}

void gestor_usuaris::carregarUsuaris()
{
	ifstream f;
	f.open("Usuarios_Partidas/usuaris.txt");

	if (f.is_open())
	{
		string nom;
		string email;
		string contrasenya;

		Usuari *prev;
		Usuari *actual;
		Usuari *ultim;

		f >> nom >> email >> contrasenya;
		actual = new Usuari(nom, email, contrasenya);
		first_usuari = actual;

		prev = actual;
		actual = actual->getNext();

		while(!f.eof())
		{
			f >> nom >> email >> contrasenya;

			actual = new Usuari(nom, email, contrasenya);
			prev->setNext(actual);

			ultim = prev;
			prev = actual;
			actual = actual->getNext();
		}
		ultim->setNext(NULL);
		delete prev;

		f.close();
	}
}

void gestor_usuaris::guardarUsuaris()
{
	ofstream f;
	f.open("Usuarios_Partidas/usuaris.txt");
	Usuari *ptr = first_usuari;

	if (f.is_open())
	{
		while (ptr != NULL)
		{
			f << ptr->getNom() << " " << ptr->getEmail() << " " << ptr->getContrasenya() << endl;
			ptr = ptr->getNext();
		}

		f.close();
	}
}

void gestor_usuaris::printUsuaris()
{
	Usuari *usuari = first_usuari;
	while (usuari != NULL)
	{
		cout << usuari->getNom() << " ";
		cout << usuari->getEmail() << " ";
		cout << usuari->getContrasenya() << endl;
		usuari = usuari->getNext();
	}
}

bool gestor_usuaris::crearUsuari(string nom, string email, string contrasenya)
{
	bool existeix = false;
	Usuari *ptr = first_usuari;

	while (!existeix && ptr != NULL)
	{
		if (nom == ptr->getNom() || email == ptr->getEmail())
			existeix = true;
		else
			ptr = ptr->getNext();
	}

	if (!existeix)
	{
		ofstream fitxer;
		string nomFitxer = "Usuarios_Partidas/usuaris.txt";
		fitxer.open(nomFitxer, ios::app);

		if (fitxer.is_open())
		{
			fitxer << nom  << " " << email << " " << contrasenya << endl;
			Usuari *usuari = first_usuari;
			Usuari *nou_usuari = new Usuari(nom, email, contrasenya);
			while (usuari->getNext() != NULL)
				usuari = usuari->getNext();
			usuari->setNext(nou_usuari);
			fitxer.close();
		}

		stringstream ss;
		fs::path p;

		fs::create_directory("Usuarios_Partidas/" + nom);

		for (int i = 0; i < 5; i++)
		{
			fs::create_directory("Usuarios_Partidas/" + nom + "/" + to_string(i + 1));

			fs::copy("datos/default", "Usuarios_Partidas/" + nom + "/" + to_string(i + 1), fs::copy_options::recursive);

			ofstream f_inventari("Usuarios_Partidas/" + nom + "/" + to_string(i + 1) + "/inventari.txt");
			f_inventari << "ID\tCANTIDAD" << endl;
			for (int i = 0; i < 10; i++)
			{
				f_inventari << "0\t0";
				if (i != 9)
					cout << endl;
			}
			f_inventari.close();

			ofstream f_jugador("Usuarios_Partidas/" + nom + "/" + to_string(i + 1) + "/jugador.txt");
			f_jugador << "PosX\t0" << endl;
			f_jugador << "PosY\t4" << endl;
			f_jugador << "nombre\t" << nom << endl;
			f_jugador << "vida\t7" << endl;
			f_jugador << "vidaMax\t10" << endl;
			f_jugador << "ataque\t5" << endl;
			f_jugador << "defensa\t3" << endl;
			f_jugador << "dinero\t200" << endl;
			f_jugador << "arma\t0" << endl;
			f_jugador << "armadura\t0";
			f_jugador.close();

			ofstream f_vaixell("Usuarios_Partidas/" + nom + "/" + to_string(i + 1) + "/vaixell.txt");
			f_vaixell << "id\t0" << endl;
			f_vaixell << "vida\t5" << endl;
			f_vaixell << "defensa\t6" << endl;
			f_vaixell << "dany\t7";
			f_vaixell.close();
		}

		ofstream f_partides("Usuarios_Partidas/" + nom + "/partides.txt");
		for (int i = 0; i < 5; i++)
		{
			f_partides << "id " << i << " nom [BUIT]" << endl;
		}
		f_partides.close();
	}

	return !existeix;
}

void gestor_usuaris::eliminarUsuari(string nom)
{
	Usuari *prev = NULL;
	Usuari *actual = first_usuari;
	bool trobat = false;

	while (!trobat && actual != NULL)
	{
		if (actual->getNom() == nom)
			trobat = true;
		else
		{
			prev = actual;
			actual = actual->getNext();
		}
	}

	if (trobat)
	{
		if (prev == NULL)
			first_usuari = actual->getNext();
		else
			prev->setNext(actual->getNext());
		delete actual;
		gestor_usuaris::guardarUsuaris();
	}
}
