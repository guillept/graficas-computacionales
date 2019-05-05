#include "mat4.h"
#include <math.h>
#include "vec2.h"
#include <iostream>

/*1. + mat4()
Constructor que inicializa las variables de instancia a sus valores por default. El valor por default de n contiene todos sus
valores inicializados en 0.
*/
cgmath::mat4::mat4() : n{0}
{
}

/*2. + mat4(diagonal:float)
Constructor que inicializa las variables de instancia utilizando el parámetro diagonal para dar valor a la diagonal de la matriz.
*/
cgmath::mat4::mat4(float diagonal) : n {{diagonal, 0, 0, 0}, {0, diagonal, 0, 0}, {0, 0, diagonal, 0}, { 0, 0, 0, diagonal} }
{
}

/*3. + mat4(a:const vec4&, b:const vec4&, c:const vec4&)
Constructor que inicializa las variables de instancia utilizando los parámetros a, b y c como vectores columna.
*/
cgmath::mat4::mat4(const vec4 & a, const vec4 & b, const vec4 & c, const vec4& d)
{
	n[0][0] = a[0]; n[0][1] = a[1];	n[0][2] = a[2]; n[0][3] = a[3];
	n[1][0] = b[0]; n[1][1] = b[1]; n[1][2] = b[2]; n[1][3] = b[3];
	n[2][0] = c[0]; n[2][1] = c[1]; n[2][2] = c[2]; n[2][3] = c[3];
	n[3][0] = d[0]; n[3][1] = d[1]; n[3][2] = d[2]; n[3][3] = d[3];

}


/*4. + operator[](column:int):vec4&
El operador [] permite tener acceso de escritura a los vectores columna almacenados en esta matriz utilizando un índice. El
método no hace ningún chequeo del índice utilizado.
*/
cgmath::vec4& cgmath::mat4::operator[](int column)
{
	return reinterpret_cast<vec4&>(n[column]); //cast le vas a decir al arreglo que esos 3 floats  consecutivos en memoria los interprete como un vec4
}

/*5. + <<{const}>> operator[](column:int):const vec4&
El operador [] permite tener acceso de sólo lectura a los vectores columna almacenados en esta matriz utilizando un índice.
El método no hace ningún chequeo del índice utilizado.
*/
const cgmath::vec4& cgmath::mat4::operator[](int column) const
{

	return reinterpret_cast<const vec4&>(n[column]);
}

/*
6. + <<{const}>> operator==(m:const mat4&):bool
El operador == realiza una comparación de la instancia actual de mat4 con la matriz m. La comparación se realiza a nivel de
componente, es decir, todos los elementos correspondientes de ambas matrices deben ser idénticos. Se debe regresar true
si todas las componentes son iguales en ambas matrices, false de lo contrario.
*/
bool cgmath::mat4::operator==(const mat4& m) const
{
	return (reinterpret_cast<const vec4&>(n[0]) == m[0]
		&& reinterpret_cast<const vec4&>(n[1]) == m[1]
		&& reinterpret_cast<const vec4&>(n[2]) == m[2]
		&& reinterpret_cast<const vec4&>(n[3]) == m[3]);
}

/*8. + inverse(m:const mat4&):mat4
El método estático inverse(…) calcula la matriz inversa de la matriz 3x3 m y la regresa como un nuevo objeto mat4. El
método no modifica la mat4 m.
*/
cgmath::mat4 cgmath::mat4::inverse(const cgmath::mat4& m)
{
	float Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
	float Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
	float Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

	float Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	float Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
	float Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

	float Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
	float Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
	float Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

	float Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	float Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
	float Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

	float Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
	float Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
	float Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

	float Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
	float Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
	float Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

	cgmath::vec4 Fac0(Coef00, Coef00, Coef02, Coef03);
	cgmath::vec4 Fac1(Coef04, Coef04, Coef06, Coef07);
	cgmath::vec4 Fac2(Coef08, Coef08, Coef10, Coef11);
	cgmath::vec4 Fac3(Coef12, Coef12, Coef14, Coef15);
	cgmath::vec4 Fac4(Coef16, Coef16, Coef18, Coef19);
	cgmath::vec4 Fac5(Coef20, Coef20, Coef22, Coef23);

	cgmath::vec4 Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
	cgmath::vec4 Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
	cgmath::vec4 Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
	cgmath::vec4 Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

	cgmath::vec4 Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
	cgmath::vec4 Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
	cgmath::vec4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
	cgmath::vec4 Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

	cgmath::vec4 SignA(+1, -1, +1, -1);
	cgmath::vec4 SignB(-1, +1, -1, +1);
	mat4 Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

	cgmath::vec4 Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

	cgmath::vec4 Dot0(m[0] * Row0);
	float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

	float OneOverDeterminant = 1.0f / Dot1;

	Inverse[0] *= OneOverDeterminant;
	Inverse[1] *= OneOverDeterminant;
	Inverse[2] *= OneOverDeterminant;
	Inverse[3] *= OneOverDeterminant;

	return Inverse;
}