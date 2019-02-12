#pragma once

#include "vec4.h"
#include <iostream>

namespace cgmath
{
	class mat4
	{
	public:
		mat4();
		mat4(float diagonal);
		mat4(const vec4& a, const vec4&b, const vec4& c, const vec4& d);
		vec4& operator[](int column);
		const vec4& operator[](int column) const;
		bool operator==(const mat4& m) const;
		static mat4 inverse(const mat4& m);

		friend std::ostream& operator<< (std::ostream& os, const mat4& m) {
			for (int i = 0; i < 4; i++)
			{
				if (i < 3)
					os << m[0][i] << " " << m[1][i] << " " << m[2][i] << " " << m[3][i] << "\n";
				else
					os << m[0][i] << " " << m[1][i] << " " << m[2][i] << " " << m[3][i];
			}
			return os;
		}

	private:
		float n[4][4] = { 0 };
	};

	/* 11. + <<{inline}>> operator*(m:const mat4&, v:const vec4&):vec4
	El operador * permite realizar una multiplicación entre una matriz 3x3 (operando izquierdo) y un vector columna de 3 componentes (operando derecho).
	El resultado debe ser almacenado en un nuevo objeto vec4 que deberá regresarse como resultado de ejecutar este método.
	*/
	inline vec4 operator*(const mat4& m1, const vec4& v) {
		// row(A), col(A), row(B), col(B)
		int const r = 4, c = 4, r2 = 4, c2 = 1;
		float matrix[r][c2] = {};
		float mul;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c2; j++) {
				mul = 0;
				for (int k = 0; k < c; k++) {
					mul += m1[k][i] * v[k]; 
				}
				matrix[i][j] = mul;
			}
		}

		return cgmath::vec4(matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]);
		/*
		float a = m1[0][0] * v.x + m1[0][1] * v.y + m1[0][2] * v.z;
		float b = m1[1][0] * v.x + m1[1][1] * v.y + m1[1][2] * v.z;
		float c = m1[2][0] * v.x + m1[2][1] * v.y + m1[2][2] * v.z;
		return vec4(a, b, c); */
	}

	/* 12. + <<{inline}>> operator*(m1:const mat4&, m2:const mat4&):mat4
	El operador * permite realizar una multiplicación entre una matriz 3x3 (operando izquierdo) y otra matriz 3x3 (operando derecho).
	El resultado debe ser almacenado en un nuevo objeto mat4 que deberá regresarse como resultado de ejecutar este método.*/
	inline mat4 operator*(const mat4& m1, const mat4& m2) {
		// row(A), col(A), row(B), col(B)
		int const r = 4, c = 4, r2 = 4, c2 = 4;
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

		return cgmath::mat4(reinterpret_cast<vec4&>(matrix[0]), reinterpret_cast<vec4&>(matrix[1]), reinterpret_cast<vec4&>(matrix[2]), reinterpret_cast<vec4&>(matrix[3]));
	}
}

/*- n:float[4][4] = { 0 }
+ mat4()
+ mat4(diagonal:float)
+ mat4(a:const vec4&, b:const vec4&, c:const vec4&, d:const vec4&)
+ operator[](column:int):vec4&
+ <<{const}>> operator[](column:int):const vec4&
+ <<{const}>> operator==(m:const mat4&):bool
+ inverse(m:const mat4&):mat4
+ <<{friend}>> operator<<(os:ostream&, m:const mat4&):ostream&
+ <<{inline}>> operator*(m:const mat4&, v:const vec4&):vec4
+ <<{inline}>> operator*(m1:const mat4&, m2:const mat4&):mat4*/