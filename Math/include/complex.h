#pragma once

#include <iostream>

namespace cgmath
{
	class complex {
	public: 

		//Variables almcenan en Memoria contigua
		float real;
		float imag;
		
		complex();
		complex(float real, float imag);

		void print() const;

		//friend expone sus miembros
		//sobrecarga de operadores
		friend inline std::ostream& operator<< (std::ostream& os, const complex& c) {
			os << c.real << " + " << c.imag << "i" << std::endl;
			return os;
		}

		// manera tradicional -> 
		void add(const complex& other);

		//sobrecarga
		complex& operator+=(const complex& other);


		static complex add(const complex& a, const complex& b);

	};

	// no se implementan en el cpp
	// el codigo lo guarda en memoria para optimizar ciertas llamadas. CPU no procesa tanto pero ocupa memoria.
	inline complex operator+(const complex& a, const complex& b) {
		return complex(a.real + b.real, a.imag + b.imag);
	}

}
