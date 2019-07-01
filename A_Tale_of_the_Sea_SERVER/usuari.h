#pragma once
#include <string>
using namespace std;

class Usuari
{
public:
	Usuari() {_nom = ""; _email = ""; _contrasenya = ""; nextUsuari = NULL;}
	Usuari(string nom, string email, string contrasenya)
	{_nom = nom; _email = email; _contrasenya = contrasenya; nextUsuari = NULL;}
	~Usuari() {}

	string getNom() {return _nom;}
	string getEmail() {return _email;}
	string getContrasenya() {return _contrasenya;}

	void setNom(char *nom) {_nom = nom;}
	void setEmail(string email) {_email = email;}
	void setContrasenya(char *contrasenya) {_contrasenya = contrasenya;}
	void eliminaUsuari();

	bool afegirPartida();
	bool eliminarPartida();

	Usuari *getNext() {return nextUsuari;}
	void setNext(Usuari *usuari) {nextUsuari = usuari;}

private:
	Usuari *nextUsuari;
	string _nom;
	string _email;
	string _contrasenya;
};
