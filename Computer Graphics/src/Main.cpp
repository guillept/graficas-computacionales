#include <iostream>

#include "complex.h" //busca en carpeta include

int main(int argc, char* argv[])
{

	cgmath::complex c; //instanciado objeto de tipo complex. Constructor de default
	cgmath::complex c2(1.0f, 2.0f);

	/* c.print();
	c2.print(); */

	std::cout << c;
	std::cout << c2;

	c.add(c2);
	std::cout << c;

	c += c2;
	std::cout << c;

	cgmath::complex c3  = cgmath::complex::add(c, c2);

	std::cout << c3;


	std::cout << c + c2 + c3 << std::endl;

	std::cout << "Press Enter" << std::endl;
	std::cin.get(); //abrir consola y pedir enter
	return 0;
}