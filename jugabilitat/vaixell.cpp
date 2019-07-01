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

void vaixell::mostrar_dades()
{
	std::cout << "Dades del teu vaixell: " << std::endl;
	std::cout << "id: " << _id << std::endl;
	std::cout << "vida: " << _vida << std::endl;
	std::cout << "defensa: " << _defensa << std::endl;
	std::cout << "dany: " << _dany << std::endl;
}
