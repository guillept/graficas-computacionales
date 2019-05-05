#pragma once

#include <iostream>

namespace cgmath
{
	class vec4
	{
	public:
		float x;
		float y;
		float z;
		float w;

		vec4();
		vec4(float x, float y, float z, float w);

		//sobrecarga
		float& operator[](int i);
		const float& operator[](int i) const;
		vec4& operator*=(float s);
		vec4& operator/=(float s);
		vec4& operator+=(const vec4& v);
		vec4& operator-=(const vec4& v);
		bool operator==(const vec4& v) const;
		
		/*15. + <<{friend}>> operator<<(os:ostream&, v:const vec4&):ostream&
		El operador << crea un string con una representación en texto de la instancia sobre la cual se manda a llamar. La
		representación correcta debe ser los componentes del vector entre paréntesis, separados por comas. Permite asociar un
		output stream (cout por ejemplo) con un vec4.
		*/
		friend std::ostream& operator<< (std::ostream& os, const vec4& v) {
			os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
			return os;
		}
	};

	/*16. + <<{inline}>> operator*(v:const vec4&, s:float):vec4
	El operador * permite realizar una multiplicación entre un vector (operando izquierdo) y un escalar (operando derecho). Cada
	una de las componentes de v deberán ser multiplicadas por s y el resultado almacenado en un nuevo objeto vec4 que deberá
	regresarse como resultado de ejecutar este método.*/
	inline vec4 operator*(const vec4& v, float s) {
		cgmath::vec4 v2(v.x*s, v.y*s, v.z*s, v.w*s);
		return v2;
	}

	/*17. + <<{inline}>> operator*(s:float, v:const vec4&):vec4
	Similar al ejercicio 16. Este operador habilita la propiedad conmutativa de la multiplicación entre un vector y un escalar.
	*/
	inline vec4 operator*(float s, const vec4& v) {
		cgmath::vec4 v2(v.x*s, v.y*s, v.z*s, v.w*s);
		return v2;
	}

	/*18. + <<{inline}>> operator/(v:const vec4&, s:float):vec4
	El operador / permite realizar una división entre un vector (operando izquierdo) y un escalar (operando derecho). Cada una
	de las componentes de v deberán ser divididas por s y el resultado almacenado en un nuevo objeto vec4 que deberá
	regresarse como resultado de ejecutar este método.
	*/
	inline vec4 operator/ (const vec4& v, float s) {
		cgmath::vec4 v2(v.x / s, v.y / s, v.z / s, v.w / s);
		return v2;
	}

	/*19. + <<{inline}>> operator+(a:const vec4&, b:const vec4&):vec4
	El operador + permite realizar una suma entre dos vectores. Cada componente del vector a deberá ser sumado con la
	componente correspondiente en el vector b y el resultado almacenado en un nuevo objeto vec4 que deberá regresarse
	como resultado de ejecutar este método.*/
	inline vec4 operator+ (const vec4& a, const vec4& b) {
		cgmath::vec4 v2(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
		return v2;
	}

	/*20. + <<{inline}>> operator-(a:const vec4&, b:const vec4&):vec4
	El operador – permite realizar una entre dos vectores. Cada componente del vector b deberá ser restado de la componente
	correspondiente en el vector a y el resultado deberá almacenado en un nuevo objeto vec4 que deberá regresarse como
	resultado de ejecutar este método.
	*/
	inline vec4 operator- (const vec4& a, const vec4& b) {
		cgmath::vec4 v2(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
		return v2;
	}

	/* 21. + <<{inline}>> operator-(v:const vec4&):vec4
	El operador – permite negar las componentes del vector v. El resultado deberá ser almacenado en un nuevo objeto vec4,
	que deberá regresarse como resultado de ejecutar este método.
	*/
	inline vec4 operator- (const vec4& v) {
		cgmath::vec4 v2(-v.x, -v.y, -v.z, -v.w);
		return v2;
	}

	inline vec4 operator*(const vec4& v1, const vec4& v2)
	{
		return vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
	}

}

