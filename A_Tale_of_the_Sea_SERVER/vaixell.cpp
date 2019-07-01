#include "vaixell.h"

vaixell::vaixell(std::string usuario)
{
	std::ifstream f;
	f.open("datos/usuarios/" + usuario + "/vaixell.txt");
	if (f.is_open())
	{
		int id, vida, defensa, dany;
		f >> id;
		f >> vida;
		f >> defensa;
		f >> dany;

		_id = id;
		_vida = vida;
		_defensa = defensa;
		_dany = dany;

		f.close();
	}
}

void vaixell::mostrar_dades(std::string &s)
{
	/*
	std::cout << "Dades del teu vaixell: " << std::endl;
	std::cout << "id: " << _id << std::endl;
	std::cout << "vida: " << _vida << std::endl;
	std::cout << "defensa: " << _defensa << std::endl;
	std::cout << "dany: " << _dany << std::endl;
	*/

	s = "Dades del teu vaixell: \nid: " +
		std::to_string(_id) + "\n" +
		"vida: " + std::to_string(_vida) + "\n" +
		"defensa: " + std::to_string(_defensa) + "\n" +
		"dany: " + std::to_string(_dany) + "\n";
}
