#pragma once

#include <iostream>

namespace cgmath
{
	class vec2
	{
	public:
		// Los atributos se almacenan de manera contigua en memoria. Pueden usar esto a su favor
		// para simplificar el codigo de algunas secciones.
		float x;
		float y;

		vec2();
		vec2(float x, float y);

		//sobrecarga
		float& operator[](int i);
		const float& operator[](int i) const;

		vec2& operator*=(float s);
		vec2& operator/=(float s);
		vec2& operator+=(const vec2& v);
		vec2& operator-=(const vec2& v);
		bool operator==(const vec2& v) const;
		float magnitude() const;
		void normalize();
		static float magnitude(const vec2& v);
		static vec2 normalize(const vec2& v);
		static float dot(const vec2& a, const vec2& b);

		/*15. + <<{friend}>> operator<<(os:ostream&, v:const vec2&):ostream&
		El operador << crea un string con una representación en texto de la instancia sobre la cual se manda a llamar. La
		representación correcta debe ser los componentes del vector entre paréntesis, separados por comas. Permite asociar un
		output stream (cout por ejemplo) con un vec2.
		*/
		friend std::ostream& operator<< (std::ostream& os, const vec2& v) {
			os << "(" << v.x << ", " << v.y << ")";
			return os;
		}
	};

	/*16. + <<{inline}>> operator*(v:const vec2&, s:float):vec2
	El operador * permite realizar una multiplicación entre un vector (operando izquierdo) y un escalar (operando derecho). Cada
	una de las componentes de v deberán ser multiplicadas por s y el resultado almacenado en un nuevo objeto vec2 que deberá
	regresarse como resultado de ejecutar este método.*/
	inline vec2 operator*(const vec2& v, float s) {
		cgmath::vec2 v2(v.x*s, v.y*s);
		return v2;
	}

	/*17. + <<{inline}>> operator*(s:float, v:const vec3&):vec3
	Similar al ejercicio 16. Este operador habilita la propiedad conmutativa de la multiplicación entre un vector y un escalar.
	*/
	inline vec2 operator*(float s, const vec2& v) {
		cgmath::vec2 v2(v.x*s, v.y*s);
		return v2;
	}

	/*18. + <<{inline}>> operator/(v:const vec2&, s:float):vec2
	El operador / permite realizar una división entre un vector (operando izquierdo) y un escalar (operando derecho). Cada una
	de las componentes de v deberán ser divididas por s y el resultado almacenado en un nuevo objeto vec2 que deberá
	regresarse como resultado de ejecutar este método.
	*/
	inline vec2 operator/ (const vec2& v, float s) {
		cgmath::vec2 v2(v.x/s, v.y/s);
		return v2;
	}

	/*19. + <<{inline}>> operator+(a:const vec2&, b:const vec2&):vec2
	El operador + permite realizar una suma entre dos vectores. Cada componente del vector a deberá ser sumado con la
	componente correspondiente en el vector b y el resultado almacenado en un nuevo objeto vec2 que deberá regresarse
	como resultado de ejecutar este método.*/
	inline vec2 operator+ (const vec2& a, const vec2& b) {
		cgmath::vec2 v2(a.x + b.x, a.y + b.y);
		return v2;
	}

	/*20. + <<{inline}>> operator-(a:const vec2&, b:const vec2&):vec2
	El operador – permite realizar una entre dos vectores. Cada componente del vector b deberá ser restado de la componente
	correspondiente en el vector a y el resultado deberá almacenado en un nuevo objeto vec2 que deberá regresarse como
	resultado de ejecutar este método.
	*/
	inline vec2 operator- (const vec2& a, const vec2& b) {
		cgmath::vec2 v2(a.x - b.x, a.y - b.y);
		return v2;
	}

	/* 21. + <<{inline}>> operator-(v:const vec2&):vec2
	El operador – permite negar las componentes del vector v. El resultado deberá ser almacenado en un nuevo objeto vec2,
	que deberá regresarse como resultado de ejecutar este método.
	*/
	inline vec2 operator- (const vec2& v) {
		cgmath::vec2 v2(-v.x, -v.y);
		return v2;
	}
}

