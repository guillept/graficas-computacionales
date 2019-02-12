#include "complex.h"
#include <iostream>

cgmath::complex::complex() : real(0.0f), imag(0.0f) {};

cgmath::complex::complex(float real, float imag) : real(real), imag(imag) {}

void cgmath::complex::print() const
{
	std::cout << real << " + " << imag << " " << std:: endl;
}

void cgmath::complex::add(const complex & other)
{
	real += other.real;
	imag += other.imag;

}

cgmath::complex& cgmath::complex::operator+=(const complex & other)
{
	real += other.real;
	imag += other.imag;
	return *this; //referencia al objeto
};

//static no es necesartio, si regresas referencia se borra al terminar el main
cgmath::complex cgmath::complex::add(const cgmath::complex& a, const cgmath::complex& b) {
	cgmath::complex c;
	return cgmath::complex(a.real + b.real, a.imag + b.imag);
};