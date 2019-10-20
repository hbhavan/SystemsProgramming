
#include <iostream>
#include <string>
#include "Matrix.h"

using namespace std;

int main(){

	Matrix m1(2,3);
	cout << "\nMatrix m1, a 2x3 matrix of 0s:\n" << m1;

	m1.at(0,0) = 0;
	m1.at(0,1) = 1;
	m1.at(0,2) = 2;
	m1.at(1,0) = 3;
	m1.at(1,1) = 4;
	m1.at(1,2) = 5;
	cout << "\nSet values of m1 using at()\n" << m1;
	
	cout << "\nGet the value at (0,2) using m1(0,2):" << m1(0,2) << endl;
	
	cout << "\n----------------------------------------------------------------------------------";
	Matrix m2(m1);
	cout << "\nMatrix m2, a copy of m1 made using the copy constructor:\n" << m2;
	
	Matrix m3(2,2);
	m3 = m2;
	cout << "\nMatrix m3, a copy of m2 made using the overloaded copy operator:\n" << m3;
	cout << "----------------------------------------------------------------------------------\n";	

	cout << "\n----------------------------------------------------------------------------------";
	cout << "\nAdd 4 to m1 using add(double):\n" << m1.add(4);

	cout << "\nAdd m1 to m2 using add(Matrix):\n" << m1.add(m2);

	Matrix m4 = m1 + 3;
	cout << "\nMatrix m4, a matrix made from m1 + 3 using the overloaded + operator:\n" << m4;

	cout << "\nAdd 10 to m1 using the overloaded + operator with 10 on the left hand side:\n" << (10 + m1);
	cout << "----------------------------------------------------------------------------------\n";

	cout << "\n----------------------------------------------------------------------------------";
	cout << "\nSubtract 1 from m4 using subtract(double):\n" << m4.subtract(1);

	cout << "\nSubtract m1 from m4 using subtract(Matrix):\n" << m4.subtract(m1);

	cout << "\nSubtract 2 from m4 using the overloaded - operator:\n" << (m4 - 2);

	cout << "\nSubtract m4 from 20 using the overloaded - operator with 20 on the left hand side:\n" << (20 - m4);
	cout << "----------------------------------------------------------------------------------\n";

	cout << "\n----------------------------------------------------------------------------------";
	cout << "\nMultiply m1 by 2 using multiply(double):\n" << m1.multiply(2);	
		
	cout << "\nMultiply m1 by 5 using the overloaded *:\n" << (m1 * 5);

	cout << "\nMulitply m1 by 3 using the overloaded * operator with 3 on the left hand side:\n" << (3 * m1);

	Matrix m5(3,1);
	m5(0,0) = 2;
	m5(1,0) = 2;
	m5(2,0) = 2;
	cout << "\nMatrix m5, a 3x1 matrix made using the overloaded () operator:\n" << m5;

	cout << "\nMupltiply m1 by m5 using multiply(Matrix):\n" << m1.multiply(m5);

	Matrix m6(3,2);
	m6 = {{3,4},{3,4},{3,4}};
	cout << "\nMatrix m6, a 3x2 matrix made using the initializer list {{3,4},{3,4},{3,4}}:\n" << m6;

	cout << "\nMultiply m4 by m6 using the overloaded * operator:\n" << (m4 * m6);
	cout << "----------------------------------------------------------------------------------\n";

	cout << "\n----------------------------------------------------------------------------------";
	cout << "\nDivide m5 by 2 using divide(double):\n" << m5.divide(2);

	cout << "\nDivide m6 by 12 using the overloaded / operator:\n" << (m6 / 12);

	cout << "\nDivide 12 by m6 using the overloaded / operator with 12 on the left hand side:\n" << (12 / m6);
	cout << "----------------------------------------------------------------------------------\n";

	cout << "\nTranspose m1 using t():\n" << m1.t();

	cout << "\nNegate m4 using the overloaded - unary operator:\n" << (-m4); 
}
