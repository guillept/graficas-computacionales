#include "vec4.h"

cgmath::vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

cgmath::vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

/* 3. +operator[](i : int) : float&
El operador[] permite tener acceso de escritura a las variables de instancia utilizando un índice.El método no hace ningún
chequeo del índice utilizado.
*/
float& cgmath::vec4::operator[](int i)
{
	return (&x)[i];
}

/*
4. + <<{const}>> operator[](i:int):const float&
El operador [] permite tener acceso de sólo lectura a las variables de instancia utilizando un índice. El método no hace ningún
chequeo del índice utilizado.
*/

const float& cgmath::vec4::operator[](int i) const
{
	return (&x)[i];
}


/*5. + operator*=(s:float):vec4&
El operador *= multiplica cada una de las variables de instancia por el valor escalar s. Se debe regresar la referencia de la
instancia modificada de vec4.*/

cgmath::vec4& cgmath::vec4::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this; //referencia al objeto
}

/*6. + operator/=(s:float):vec4&
El operador /= divide cada una de las variables de instancia por el valor escalar s. Se debe regresar la referencia de la instancia
modificada de vec4.
*/
cgmath::vec4& cgmath::vec4::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}

/*7. + operator+=(v:const vec4&):vec4&
El operador += suma cada una de las variables de instancia con la componente correspondiente de v. Se debe regresar la
referencia de la instancia modificada de vec4.*/
cgmath::vec4& cgmath::vec4::operator+=(const vec4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

/*8. + operator-=(v:const vec4&):vec4&
El operador -= resta cada una de las variables de instancia con la componente correspondiente de v. Se debe regresar la
referencia de la instancia modificada de vec4.*/
cgmath::vec4& cgmath::vec4::operator-=(const vec4 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

/*9. + <<{const}>> operator==(v:const vec4&):bool
El operador == realiza una comparación de la instancia actual de vec4 con el vector v. La comparación se realiza a nivel de
componente, es decir, las componentes (x, y) de ambos vectores deben ser idénticas. Se debe regresar true si todas las
componentes son iguales en ambos vectores, false de lo contrario.
*/
bool cgmath::vec4::operator==(const vec4 & v) const
{
	return (v.x == x && v.y == y && v.z == z && v.w == w);
}