#include "vec3.h"

cgmath::vec3::vec3() : x(0.0f), y(0.0f), z(0.0f)
{
}

cgmath::vec3::vec3(float x, float y, float z) : x(x), y(y), z(z)
{
}

/* 3. +operator[](i : int) : float&
El operador[] permite tener acceso de escritura a las variables de instancia utilizando un índice.El método no hace ningún
chequeo del índice utilizado.
*/
float& cgmath::vec3::operator[](int i)
{
	return (&x)[i];
}

/*
4. + <<{const}>> operator[](i:int):const float&
El operador [] permite tener acceso de sólo lectura a las variables de instancia utilizando un índice. El método no hace ningún
chequeo del índice utilizado.
*/

const float& cgmath::vec3::operator[](int i) const
{
	return (&x)[i];
}


/*5. + operator*=(s:float):vec3&
El operador *= multiplica cada una de las variables de instancia por el valor escalar s. Se debe regresar la referencia de la
instancia modificada de vec3.*/

cgmath::vec3& cgmath::vec3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this; //referencia al objeto
}

/*6. + operator/=(s:float):vec3&
El operador /= divide cada una de las variables de instancia por el valor escalar s. Se debe regresar la referencia de la instancia
modificada de vec3.
*/
cgmath::vec3& cgmath::vec3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

/*7. + operator+=(v:const vec3&):vec3&
El operador += suma cada una de las variables de instancia con la componente correspondiente de v. Se debe regresar la
referencia de la instancia modificada de vec3.*/
cgmath::vec3& cgmath::vec3::operator+=(const vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

/*8. + operator-=(v:const vec3&):vec3&
El operador -= resta cada una de las variables de instancia con la componente correspondiente de v. Se debe regresar la
referencia de la instancia modificada de vec3.*/
cgmath::vec3& cgmath::vec3::operator-=(const vec3 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

/*9. + <<{const}>> operator==(v:const vec3&):bool
El operador == realiza una comparación de la instancia actual de vec3 con el vector v. La comparación se realiza a nivel de
componente, es decir, las componentes (x, y) de ambos vectores deben ser idénticas. Se debe regresar true si todas las
componentes son iguales en ambos vectores, false de lo contrario.
*/
bool cgmath::vec3::operator==(const vec3 & v) const
{
	return (v.x == x && v.y == y && v.z == z);
}

/*10. + <<{const}>> magnitude():float
El método magnitude() calcula y regresa la magnitud de la instancia sobre la cual se manda a llamar.
*/
float cgmath::vec3::magnitude() const
{
	return sqrt(x * x + y * y + z*z);
}

/*11. + normalize():void
El método normalize() normaliza el vector de la instancia sobre la cual se manda a llamar.
*/
void cgmath::vec3::normalize()
{
	float k = 1.0 / sqrt(x * x + y * y + z*z);
	x *= k;
	y *= k;
	z *= k;
}

/*12. + magnitude(v:const vec3&):float
El método estático magnitude(…) calcula y regresa la magnitud del vector v.*/
float cgmath::vec3::magnitude(const vec3& v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

/*13. + normalize(v:const vec3&):vec3
El método estático normalize(…) calcula el vector normal de v y lo regresa como un nuevo objeto vec3. El método no
modifica el vec3 v.*/
cgmath::vec3 cgmath::vec3::normalize(const vec3& v)
{
	float k = 1.0 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	cgmath::vec3 v2(v.x * k, v.y * k, v.z*k);
	return v2;

}

/*14. + dot(a:const vec3&, b:const vec3&):float
El método estático dot(…) calcula y regresa el producto punto entre los vectores a y b.*/
float cgmath::vec3::dot(const vec3& a, const vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

/*+ cross(a:const vec3&, b:const vec3&):float
El método estático cross(…) calcula y regresa el producto cruz entre los vectores a y b.
*/
cgmath::vec3 cgmath::vec3::cross(const vec3 & a, const vec3 & b)
{
	cgmath::vec3 v2((a.y*b.z - a.z*b.y), -(a.x*b.z - a.z*b.x), (a.x*b.y - a.y*b.x));
	return v2;
}

