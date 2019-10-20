
#include "Matrix.h"

/**
 * Constructor for Matrix that takes the number of rows and columns in the matrix as parameters
 */
Matrix::Matrix(uint rows, uint cols){
	
	myRows = rows;
	myCols = cols;	

	mat = new double[rows*cols]; //A 1D array is used to represent a 2d array

	for(uint i=0;i<numRows();i++)
		for(uint j=0;j<numCols();j++)
			mat[i*numCols()+j] = 0; //i*numCols()+j allows for elements to be accessed as if mat were a 2d array
		
}

/**
 * Constructor for Matrix that creates a Matrix using the initializer_list<initializer_list<double>> parameter
 */
Matrix::Matrix(const i_list & list){

	myRows = list.size();
	myCols = list.begin()->size();

	mat = new double[myRows*myCols];
	
	auto list1 = list.begin();

	for(uint i=0;i<numRows();i++){
	
		auto list2 = list1[i].begin();

		for(uint j=0;j<numCols();j++){
			
			mat[i*numCols()+j] = list2[j];
	
		}
	
	}

}

/**
 * Copy constructor for Matrix that creates a deep copy
 */
Matrix::Matrix(const Matrix & m){

	myRows = m.numRows();
	myCols = m.numCols();

	mat = new double[m.numRows()*m.numCols()];

	for(uint i=0;i<m.numRows();i++)
		for(uint j=0;j<m.numCols();j++)
			mat[i*numCols()+j] = m.at(i,j);

}

/**
 * Destructor for Matrix
 */
Matrix::~Matrix(){

	delete[] mat;

}

/**
 * Adds a scalar double, s, to all values of the Matrix
 */
Matrix Matrix::add(double s) const{

	Matrix x (*this);

	for(uint i=0;i<numRows();i++)
		for(uint j=0;j<numCols();j++)
			x.at(i,j) += s;
					
	return x;

}

/**
 * Adds the values of a Matrix, m, to a copy of the current Matrix and returns the resulting Matrix
 */
Matrix Matrix::add(const Matrix & m) const{

	Matrix x (*this);

	for(uint i=0;i<numRows();i++)
		for(uint j=0;j<numCols();j++)
			x.at(i,j) += m.at(i,j);

	return x;

}

/**
 * Subtracts a scalar double, s, to all values of the Matrix
 */
Matrix Matrix::subtract(double s) const{

	Matrix x (*this);

	for(uint i=0;i<numRows();i++)
		for(uint j=0;j<numCols();j++)
			x.at(i,j) -= s;

	return x;

}

/**
 * Subtracts the values of a Matrix, m, to a copy of the current Matrix and returns the resulting Matrix
 */
Matrix Matrix::subtract(const Matrix & m) const{
	
	Matrix x (*this);
		
	for(uint i=0;i<numRows();i++)
		for(uint j=0;j<numCols();j++)
			x.at(i,j) -= m.at(i,j);

	return x;
	
}

/**
 * Multiplies a scalar double, s, to the values of the Matrix
 */
Matrix Matrix::multiply(double s) const{

	Matrix x (*this);

	for(uint i=0;i<numRows();i++)
		for(uint j=0;j<numCols();j++)
			x.at(i,j) *= s;

	return x;

}

/**
 * Performs matrix multiplication between two Matrices
 */
Matrix Matrix::multiply(const Matrix & m) const{
	
	Matrix x(numRows(), m.numCols());

	for(uint i=0;i<x.numRows();i++)
		for(uint j=0;j<x.numCols();j++)
			for(uint k=0;k<m.numRows();k++)
				x.at(i,j) += (mat[i*numCols()+k]*m.at(k,j));

	return x;

}	

/**
 * Divides the values of a Matrix by a scalar double, s
 */
Matrix Matrix::divide(double s) const{
		
	Matrix x (*this);

	for(uint i=0;i<numRows();i++)
		for(uint j=0;j<numCols();j++)
			x.at(i,j) /= s;

	return x;

}

/**
 * Transposes the Matrix, flipping the number of rows with the number of columns
 */
Matrix Matrix::t() const{

	Matrix x(numCols(),numRows());

	for(uint i=0;i<numRows();i++)
		for(uint j=0;j<numCols();j++)
			x.at(j,i) = mat[i*numCols()+j];

	return x;

}

/**
 * Overloads the + operator to allow addition of scalar doubles on a Matrix
 */
Matrix Matrix::operator + (const double s) const{

	Matrix x(*this);

	return x.add(s);

}

/**
 * Overloads the + operator to allow addition of two Matrices
 */
Matrix Matrix::operator + (const Matrix & m) const{

	Matrix x(*this);

	return x.add(m);

}	

/**
 * Overloads the - operator to allow subtraction of scalar dobules on a Matrix
 */
Matrix Matrix::operator - (const double s) const{

	Matrix x(*this);

	return x.subtract(s);

}

/**
 * Overloads the - operator to allow subtraction between two Matrices
 */
Matrix Matrix::operator - (const Matrix & m) const{ 

	Matrix x(*this);
	
	return x.subtract(m);

}

/**
 * Overloads the * operator to allow multiplication of scalar doubles on a Matrix 
 */
Matrix Matrix::operator * (const double s) const{

	Matrix x(*this);

	return x.multiply(s);

}

/**
 * Overloads the * operator to allow matrix multiplication between two Matrices
 */
Matrix Matrix::operator * (const Matrix & m) const{ 

	Matrix x(*this);

	return x.multiply(m);

}

/**
 * Overloads the / operator to allow division of scalar doubles on a Matrix
 */
Matrix Matrix::operator / (const double s) const{

	Matrix x(*this);
	
	return x.divide(s);

}

/**
 * Overloads the unary operator - to negate all the values in a Matrix
 */
Matrix Matrix::operator - () const{

	Matrix x(*this);

	return x.multiply(-1);

}

/**
 * Overloads the function call operator () to allow Matrix elements to be altered
 */
double & Matrix::operator () (uint row, uint col){

	return mat[row*numCols()+col];

}

/**
 * Overloads the function call operator () to allow Matrix elements to be accessed
 */
const double & Matrix::operator () (uint row, uint col) const{

	return mat[row*numCols()+col];

}

/**
 * Overloads the assignment operator = to allow Matrices to be copied
 */
void Matrix::operator = (const Matrix & m){

	delete[] mat;

	mat = new double[m.numRows()*m.numCols()];

	myRows = m.numRows();
	myCols = m.numCols();

	for(uint i=0;i<m.numRows();i++)
		for(uint j=0;j<m.numCols();j++)
			mat[i*numCols()+j] = m.at(i,j);

}

/**
 * Overloads the + operator to allow scalar doubles to be added to the Matrix on the left hand side of the expression
 */
Matrix operator + (const double s, const Matrix & m){

	Matrix x(m);

	return x.add(s);

}

/**
 * Overloads the - operator to allow scalar dobules to be subtracted from the Matrix on the left hand side of the expression
 */
Matrix operator - (const double s, const Matrix & m){

	Matrix x(m);

	for(uint i=0;i<x.numRows();i++)
		for(uint j=0;j<x.numCols();j++)
			x.at(i,j) = s - m.at(i,j);

	return x;

}

/**
 * Overloads the * operator to allow scalar doubles to be multiplied to the Matrix on the left hand side of the expression
 */
Matrix operator * (const double s, const Matrix & m){

	Matrix x(m);

	return x.multiply(s);

}

/**
 * Overlodas the / operator to allow scalar doubles to be divided from the Matrix on the left hand side of the expression
 */
Matrix operator / (const double s, const Matrix & m){

	Matrix x(m);

	for(uint i=0;i<x.numRows();i++)
		for(uint j=0;j<x.numCols();j++)
			x.at(i,j) = s / m.at(i,j);

	return x;

}

/**
 * Overlods the stream operator << to allow for a Matrix to be printed out
 */
ostream & operator << (ostream & os, const Matrix & m){

	for(uint i=0;i<m.numRows();i++){

		os << "[ ";

		for(uint j=0;j<m.numCols();j++){

			os << m.at(i,j) << " ";
		
		}

		os << "]\n";

	}

	return os;	

}

/**
 * Returns the number of rows in a Matrix
 */
const uint Matrix::numRows() const{
		
	return myRows;

}

/**
 * Returns the number of columns in a Matrix
 */
const uint Matrix::numCols() const{
		
	return myCols;

}

/**
 * Allows for Matrix elements at a certain index to be altered
 */
double & Matrix::at(uint row, uint col){
	
	return mat[row*numCols()+col];

}

/**
 * Allows for Matrix elements at a certain index to be accessed
 */
const double & Matrix::at(uint row, uint col) const{

	return mat[row*numCols()+col];

}

