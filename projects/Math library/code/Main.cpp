#include "core/VectorMath.h";
#include "core/MatrixMath.h";
#include <iostream>;
using namespace std;

void main() {
	VectorMath4 vectorA (7, 4, -1,0);
	VectorMath4 vectorB(-5, 1, 3,0);
	VectorMath4 vectorC (6, -3, 2,0);
	VectorMath4 vectorD (-2, -4, 11, 1);

	//VectorMath4 vectorResult;
	//vectorResult = vectorA + vectorB;
	//vectorResult.PrintVector();
	//vectorResult = vectorB - vectorA;
	//vectorResult.PrintVector();
	//vectorResult = vectorResult * 4;
	//vectorResult.PrintVector();
	//cout << vectorA.Length() << endl;
	//vectorA.Normalize();
	//vectorA.PrintVector();

	MatrixMath matrixA(vectorA, vectorB, vectorC, vectorD);
	MatrixMath matrixB(vectorC, vectorD, vectorB);

	MatrixMath matrixC = matrixA* matrixA;
	//matrixC.PrintMatrix();

	/*cout << endl;
	matrixB.PrintMatrix();

	cout << endl;
	matrixA.VectorMultiplication(vectorC).PrintVector();
	
	cout << endl;
	MatrixMath resultMatrix = matrixA * matrixB;
	resultMatrix.PrintMatrix();

	cout << endl;
	RotateMatrix(25, VectorMath3(1, 0, 0)).PrintMatrix();

	cout << endl;
	MatrixMath BD = MatrixMath(vectorA, vectorB, vectorC, vectorD);
	BD.PrintMatrix();*/

}