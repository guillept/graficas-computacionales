#include "mat3.h"
#include <math.h>
#include "vec2.h"
#include <iostream>

/*1. + mat3()
Constructor que inicializa las variables de instancia a sus valores por default. El valor por default de n contiene todos sus
valores inicializados en 0.
*/
cgmath::mat3::mat3()
{
}

/*2. + mat3(diagonal:float)
Constructor que inicializa las variables de instancia utilizando el parámetro diagonal para dar valor a la diagonal de la matriz.
*/
cgmath::mat3::mat3(float diagonal)
{
	n[0][0] = diagonal;
	n[1][1] = diagonal;
	n[2][2] = diagonal;
}

/*3. + mat3(a:const vec3&, b:const vec3&, c:const vec3&)
Constructor que inicializa las variables de instancia utilizando los parámetros a, b y c como vectores columna.
*/
cgmath::mat3::mat3(const vec3 & a, const vec3 & b, const vec3 & c) 
{
	n[0][0] = a[0]; n[0][1] = a[1];	n[0][2] = a[2];
	n[1][0] = b[0]; n[1][1] = b[1]; n[1][2] = b[2];
	n[2][0] = c[0]; n[2][1] = c[1]; n[2][2] = c[2];

}


/*4. + operator[](column:int):vec3&
El operador [] permite tener acceso de escritura a los vectores columna almacenados en esta matriz utilizando un índice. El
método no hace ningún chequeo del índice utilizado.
*/
cgmath::vec3& cgmath::mat3::operator[](int column)
{
	return reinterpret_cast<vec3&>(n[column]); //cast le vas a decir al arreglo que esos 3 floats  consecutivos en memoria los interprete como un vec3
}

/*5. + <<{const}>> operator[](column:int):const vec3&
El operador [] permite tener acceso de sólo lectura a los vectores columna almacenados en esta matriz utilizando un índice.
El método no hace ningún chequeo del índice utilizado.
*/
const cgmath::vec3& cgmath::mat3::operator[](int column) const
{

	return reinterpret_cast<const vec3&>(n[column]);
}

/*
6. + <<{const}>> operator==(m:const mat3&):bool
El operador == realiza una comparación de la instancia actual de mat3 con la matriz m. La comparación se realiza a nivel de
componente, es decir, todos los elementos correspondientes de ambas matrices deben ser idénticos. Se debe regresar true
si todas las componentes son iguales en ambas matrices, false de lo contrario.
*/
bool cgmath::mat3::operator==(const mat3& m) const
{
	return (reinterpret_cast<const vec3&>(n[0]) == m[0]
		&& reinterpret_cast<const vec3&>(n[1]) == m[1]
		&& reinterpret_cast<const vec3&>(n[2]) == m[2]);
}

/*7. + determinant(m:const mat3&):float
El método estático determinant(…) calcula y regresa el determinante de la matriz 3x3 m.
*/
float cgmath::mat3::determinant(const mat3& m)
{
	return 
		// azules
		m[0][0] * m[1][1] * m[2][2]
		+ m[0][1] * m[1][2] * m[2][0]
		+ m[0][2] * m[1][0] * m[2][1]
		//rojos
		- m[0][2] * m[1][1] * m[2][0]
		- m[0][0] * m[1][2] * m[2][1]
		- m[0][1] * m[1][0] * m[2][2];
}

/*8. + inverse(m:const mat3&):mat3
El método estático inverse(…) calcula la matriz inversa de la matriz 3x3 m y la regresa como un nuevo objeto mat3. El
método no modifica la mat3 m.
*/
cgmath::mat3 cgmath::mat3::inverse(const mat3 & m)
{
	//Algoritmo tomado de http://www.math-cs.gordon.edu/courses/ma342/handouts/gauss.pdf
	//Repo inspiración https://github.com/peterabraham/Gauss-Jordan-Elimination

	int i, j, k;
	int const n = 3;
	float pivote;
	float A[n*2][n*2] = {};

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

	cgmath::vec3 a(A[0][3], A[0][4], A[0][5]);
	cgmath::vec3 b(A[1][3], A[1][4], A[1][5]);
	cgmath::vec3 c(A[2][3], A[2][4], A[2][5]);

	return mat3(a, b, c);

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

/*9. + transpose(m:const mat3&):mat3
El método estático transpose(…) calcula y regresa la matriz transpuesta de la matriz 3x3 m.
*/
cgmath::mat3 cgmath::mat3::transpose(const mat3 & m)
{
	//vectores fila = antiguos columna
	cgmath::vec3 a(m[0][0], m[1][0], m[2][0]);
	cgmath::vec3 b(m[0][1], m[1][1], m[2][1]);
	cgmath::vec3 c(m[0][2], m[1][2], m[2][2]);

	return mat3(a, b, c);
}
