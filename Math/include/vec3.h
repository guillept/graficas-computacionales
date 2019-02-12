#pragma once

#include <iostream>

namespace cgmath
{
	class vec3
	{
	public:
		float x;
		float y;
		float z;

		vec3();
		vec3(float x, float y, float z);

		float& operator[](int i);
		const float& operator[](int i) const;
		vec3& operator*=(float s);
		vec3& operator/=(float s);
		vec3& operator+=(const vec3& v);
		vec3& operator-=(const vec3& v);
		bool operator==(const vec3& v) const;
		float magnitude() const;
		void normalize();
		static float magnitude(const vec3& v);
		static vec3 normalize(const vec3& v);
		static float dot(const vec3& a, const vec3& b);
		static vec3 cross(const vec3& a, const vec3& b);

		/*15. + <<{friend}>> operator<<(os:ostream&, v:const vec3&):ostream&
		El operador << crea un string con una representación en texto de la instancia sobre la cual se manda a llamar. La
		representación correcta debe ser los componentes del vector entre paréntesis, separados por comas. Permite asociar un
		output stream (cout por ejemplo) con un vec3.
		*/
		friend std::ostream& operator<< (std::ostream& os, const vec3& v) {
			os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
			return os;
		}
	};

	/*16. + <<{inline}>> operator*(v:const vec3&, s:float):vec3
	El operador * permite realizar una multiplicación entre un vector (operando izquierdo) y un escalar (operando derecho). Cada
	una de las componentes de v deberán ser multiplicadas por s y el resultado almacenado en un nuevo objeto vec3 que deberá
	regresarse como resultado de ejecutar este método.*/
	inline vec3 operator*(const vec3& v, float s) {
		cgmath::vec3 v2(v.x*s, v.y*s, v.z*s);
		return v2;
	}

	/*17. + <<{inline}>> operator*(s:float, v:const vec3&):vec3
	Similar al ejercicio 16. Este operador habilita la propiedad conmutativa de la multiplicación entre un vector y un escalar.
	*/
	inline vec3 operator*(float s, const vec3& v) {
		cgmath::vec3 v2(v.x*s, v.y*s, v.z*s);
		return v2;
	}

	/*18. + <<{inline}>> operator/(v:const vec3&, s:float):vec3
	El operador / permite realizar una división entre un vector (operando izquierdo) y un escalar (operando derecho). Cada una
	de las componentes de v deberán ser divididas por s y el resultado almacenado en un nuevo objeto vec3 que deberá
	regresarse como resultado de ejecutar este método.
	*/
	inline vec3 operator/ (const vec3& v, float s) {
		cgmath::vec3 v2(v.x / s, v.y / s, v.z / s);
		return v2;
	}

	/*19. + <<{inline}>> operator+(a:const vec3&, b:const vec3&):vec3
	El operador + permite realizar una suma entre dos vectores. Cada componente del vector a deberá ser sumado con la
	componente correspondiente en el vector b y el resultado almacenado en un nuevo objeto vec3 que deberá regresarse
	como resultado de ejecutar este método.*/
	inline vec3 operator+ (const vec3& a, const vec3& b) {
		cgmath::vec3 v2(a.x + b.x, a.y + b.y, a.z + b.z);
		return v2;
	}

	/*20. + <<{inline}>> operator-(a:const vec3&, b:const vec3&):vec3
	El operador – permite realizar una entre dos vectores. Cada componente del vector b deberá ser restado de la componente
	correspondiente en el vector a y el resultado deberá almacenado en un nuevo objeto vec3 que deberá regresarse como
	resultado de ejecutar este método.
	*/
	inline vec3 operator- (const vec3& a, const vec3& b) {
		cgmath::vec3 v2(a.x - b.x, a.y - b.y, a.z - b.z);
		return v2;
	}

	/* 21. + <<{inline}>> operator-(v:const vec3&):vec3
	El operador – permite negar las componentes del vector v. El resultado deberá ser almacenado en un nuevo objeto vec3,
	que deberá regresarse como resultado de ejecutar este método.
	*/
	inline vec3 operator- (const vec3& v) {
		cgmath::vec3 v2(-v.x, -v.y, -v.z);
		return v2;
	}

}

