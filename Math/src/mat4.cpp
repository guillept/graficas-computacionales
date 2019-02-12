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
cgmath::mat4 cgmath::mat4::inverse(const mat4 & m)
{
	//Algoritmo tomado de http://www.math-cs.gordon.edu/courses/ma342/handouts/gauss.pdf
	//Repo inspiración https://github.com/peterabraham/Gauss-Jordan-Elimination

	int i, j, k;
	int const n = 4;
	float pivote;
	float A[n * 2][n * 2] = {};

	//Copias matriz orignial
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A[i][j] = m[i][j];

			//Matriz aumentada
			if (i == j)
				A[i][j + n] = 1;
			else
				A[i][j + n] = 0;
		}
	}

	//Transofrmacion gaussiana
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < 2 * n; i++)
		{
			if (k != i)
			{
				pivote = A[i][k] / A[k][k];
				for (j = 0; j < 2 * n; j++) {
					A[i][j] -= A[k][j] * pivote;
				}
			}
		}
	}

	for (i = 0; i < n; ++i)
	{
		pivote = A[i][i];
		for (j = 0; j < 2 * n; ++j)
		{
			A[i][j] = A[i][j] / pivote;
		}
	}


	/*
	1               0               0             0.5               0               0
	0               1               0               0             0.5               0
	0               0               1               0               0             0.5
	*/

	cgmath::vec4 a(A[0][4], A[0][5], A[0][6], A[0][7]);
	cgmath::vec4 b(A[1][4], A[1][5], A[1][6], A[1][7]);
	cgmath::vec4 c(A[2][4], A[2][5], A[2][6], A[2][7]);
	cgmath::vec4 d(A[3][4], A[3][5], A[3][6], A[3][7]);


	return cgmath::mat4(a, b, c, d);

	/*
	std::cout << "-------------------\n\n";
	for (i=0;i<n;i++)            //print the new matrix
	{
		for (j=0;j<n*2;j++)
			cout<<A[i][j]<<setw(16);
		cout<<"\n";
	}
	std::cout << "-------------------\n\n";
	*/
}