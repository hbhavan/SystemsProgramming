
#include <iostream>
#include <initializer_list>
#include <cstdlib>

using namespace std;

typedef unsigned int uint;
typedef initializer_list<initializer_list<double>> i_list;

class Matrix{

	private:
		double* mat;
		uint myRows;
		uint myCols;	

	public:
	
		Matrix(uint, uint);
		Matrix(const i_list & list);
		Matrix(const Matrix &);
		~Matrix();

		Matrix add(double) const;
		Matrix add(const Matrix &) const;

		Matrix subtract(double) const;
		Matrix subtract(const Matrix &) const;

		Matrix multiply(double) const;
		Matrix multiply(const Matrix &) const;

		Matrix divide(double) const;
		Matrix t() const;

		Matrix operator + (const double) const;
		Matrix operator + (const Matrix &) const;

		Matrix operator - (const double) const;
		Matrix operator - (const Matrix &) const;

		Matrix operator * (const double) const;
		Matrix operator * (const Matrix &) const;

		Matrix operator / (double) const;		

		Matrix operator -() const;

		double & operator () (uint row, uint col);
		const double & operator () (uint row, uint col) const;

		void operator = (const Matrix &);
		
		const uint numRows() const;
		const uint numCols() const;

		double & at(uint, uint);
		const double & at(uint, uint) const;

};

Matrix operator + (const double, const Matrix &);

Matrix operator - (const double, const Matrix &);

Matrix operator * (const double, const Matrix &);

Matrix operator / (const double, const Matrix &);

ostream & operator << (ostream &,const Matrix &);
