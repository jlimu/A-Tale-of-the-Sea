#pragma once
#include <string>
#include <iostream>
#include <fstream>

class vaixell
{
public:
	vaixell(std::string usuario);
	void mostrar_dades(std::string &s);

private:
	int _id;
	int _vida;
	int _defensa;
	int _dany;
};

/*
[20:59, 6/9/2019] Raul: por asi decirlo si
[20:59, 6/9/2019] Raul: solo son valores k luego se sumaran cuando hagamos una pelea
[20:59, 6/9/2019] Raul: pero basicamente tiene por ejemplo, vida: 10
daño:5
[20:59, 6/9/2019] Raul: y cosas asi
[21:01, 6/9/2019] Raul: la idea es k crees la clase, las variables, el .txt con algunas variables ya creadas y el constructor de la clase al cual le deberias pasar creo k el nombre del jugador como string para saber a k carpeta dentro de usuario acceder para leer los datos
[21:02, 6/9/2019] Raul: oh y tmb la funcion mostra dades k haga un cout de las dadas de vaixell
[21:03, 6/9/2019] Raul: todas las variables son int
*/