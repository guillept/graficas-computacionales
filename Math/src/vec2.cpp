#include "vec2.h"

cgmath::vec2::vec2() : x(0.0f), y(0.0f)
{
}

cgmath::vec2::vec2(float x, float y) : x(x), y(y)
{
}

/* 3. +operator[](i : int) : float&
El operador[] permite tener acceso de escritura a las variables de instancia utilizando un índice.El método no hace ningún
chequeo del índice utilizado.
*/
float& cgmath::vec2::operator[](int i)
{
	return (&x)[i];
}

/*
4. + <<{const}>> operator[](i:int):const float&
El operador [] permite tener acceso de sólo lectura a las variables de instancia utilizando un índice. El método no hace ningún
chequeo del índice utilizado.
*/

const float& cgmath::vec2::operator[](int i) const
{
	return (&x)[i];
}


/*5. + operator*=(s:float):vec2&
El operador *= multiplica cada una de las variables de instancia por el valor escalar s. Se debe regresar la referencia de la
instancia modificada de vec2.*/

cgmath::vec2& cgmath::vec2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this; //referencia al objeto
}

/*6. + operator/=(s:float):vec2&
El operador /= divide cada una de las variables de instancia por el valor escalar s. Se debe regresar la referencia de la instancia
modificada de vec2.
*/
cgmath::vec2& cgmath::vec2::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

/*7. + operator+=(v:const vec2&):vec2&
El operador += suma cada una de las variables de instancia con la componente correspondiente de v. Se debe regresar la
referencia de la instancia modificada de vec2.*/
cgmath::vec2& cgmath::vec2::operator+=(const vec2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

/*8. + operator-=(v:const vec2&):vec2&
El operador -= resta cada una de las variables de instancia con la componente correspondiente de v. Se debe regresar la
referencia de la instancia modificada de vec2.*/
cgmath::vec2& cgmath::vec2::operator-=(const vec2 & v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

/*9. + <<{const}>> operator==(v:const vec2&):bool
El operador == realiza una comparación de la instancia actual de vec2 con el vector v. La comparación se realiza a nivel de
componente, es decir, las componentes (x, y) de ambos vectores deben ser idénticas. Se debe regresar true si todas las
componentes son iguales en ambos vectores, false de lo contrario.
*/
bool cgmath::vec2::operator==(const vec2 & v) const
{
	return (v.x == x && v.y == y);
}


/*10. + <<{const}>> magnitude():float
El método magnitude() calcula y regresa la magnitud de la instancia sobre la cual se manda a llamar.
*/
float cgmath::vec2::magnitude() const
{
	return sqrt(x * x + y * y);
}

/*11. + normalize():void
El método normalize() normaliza el vector de la instancia sobre la cual se manda a llamar.
*/
void cgmath::vec2::normalize()
{
	float k = 1.0 / sqrt(x * x + y * y);
	x *= k;
	y *= k;
}

/*12. + magnitude(v:const vec2&):float
El método estático magnitude(…) calcula y regresa la magnitud del vector v.*/
float cgmath::vec2::magnitude(const vec2& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

/*13. + normalize(v:const vec2&):vec2
El método estático normalize(…) calcula el vector normal de v y lo regresa como un nuevo objeto vec2. El método no
modifica el vec2 v.*/
cgmath::vec2 cgmath::vec2::normalize(const vec2& v)
{
	float k = 1.0 / sqrt(v.x * v.x + v.y * v.y);
	cgmath::vec2 v2(v.x * k, v.y * k);
	return v2;

}

/*14. + dot(a:const vec2&, b:const vec2&):float
El método estático dot(…) calcula y regresa el producto punto entre los vectores a y b.*/
float cgmath::vec2::dot(const vec2& a, const vec2& b)
{
	return a.x * b.x + a.y * b.y;
}

