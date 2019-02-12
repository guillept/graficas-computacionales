#pragma once

#include "vec3.h"
#include <iostream>

namespace cgmath
{
	class mat3
	{
	public:
		mat3();
		mat3(float diagonal);
		mat3(const vec3& a, const vec3&b, const vec3& c);
		vec3& operator[](int column);
		const vec3& operator[](int column) const;
		bool operator==(const mat3& m) const;
		static float determinant(const mat3& m);
		static mat3 inverse(const mat3& m);
		static mat3 transpose(const mat3& m);

		friend std::ostream& operator<< (std::ostream& os, const mat3& m) {
			for (int i = 0; i < 3; i++)
			{
				if (i < 2)
					os << m[0][i] << " " << m[1][i] << " " << m[2][i] << "\n";
				else
					os << m[0][i] << " " << m[1][i] << " " << m[2][i];
			}
			return os;
		}

	private:
		float n[3][3];
	};

	/* 11. + <<{inline}>> operator*(m:const mat3&, v:const vec3&):vec3
	El operador * permite realizar una multiplicación entre una matriz 3x3 (operando izquierdo) y un vector columna de 3 componentes (operando derecho). 
	El resultado debe ser almacenado en un nuevo objeto vec3 que deberá regresarse como resultado de ejecutar este método.
	*/
	inline vec3 operator*(const mat3& m1, const vec3& v) {
		// row(A), col(A), row(B), col(B)
		int const r = 3, c = 3, r2 = 3, c2 = 1;
		float matrix[r][c2] = {};
		float mul;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c2; j++) {
				mul = 0;
				for (int k = 0; k < c; k++) {
					mul += m1[k][i] * v[k]; //matrices volteadas, col*row
				}
				matrix[i][j] = mul;
			}
		}

		return cgmath::vec3(matrix[0][0], matrix[0][1], matrix[0][2]);
		/*
		float a = m1[0][0] * v.x + m1[0][1] * v.y + m1[0][2] * v.z;
		float b = m1[1][0] * v.x + m1[1][1] * v.y + m1[1][2] * v.z;
		float c = m1[2][0] * v.x + m1[2][1] * v.y + m1[2][2] * v.z;
		return vec3(a, b, c); */
	}

	/* 12. + <<{inline}>> operator*(m1:const mat3&, m2:const mat3&):mat3
	El operador * permite realizar una multiplicación entre una matriz 3x3 (operando izquierdo) y otra matriz 3x3 (operando derecho). 
	El resultado debe ser almacenado en un nuevo objeto mat3 que deberá regresarse como resultado de ejecutar este método.*/
	inline mat3 operator*(const mat3& m1, const mat3& m2) {
		// row(A), col(A), row(B), col(B)
		int const r = 3, c = 3, r2 = 3, c2 = 3;
		float matrix[r][c2] = {};
		float mul;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c2; j++) {
				mul = 0;
				for (int k = 0; k < c; k++) {
					mul += m2[i][k] * m1[k][j]; 
				}
				matrix[i][j] = mul;
			}
		}
		
		return cgmath::mat3(reinterpret_cast<vec3&>(matrix[0]), reinterpret_cast<vec3&>(matrix[1]), reinterpret_cast<vec3&>(matrix[2]));
	}
}
