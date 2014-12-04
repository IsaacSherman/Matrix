#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "Matrix.h"             // include the Matrix class definition
#include "Pr.h"
#include "Norm.h"
#include <cstring>
#define USAGE "./pca [file assuming extension .tr/.te] NumberOfFeatures, err\n will find the normalization of the file and output it into [file]_norm.[fileExtension]"

int main(int argc, char * argv[]){

if(argc != 4) {
cerr<<USAGE<<endl;
return 1;
}
int nf = atoi(argv[2]);
float err = atof(argv[3]);
string fileName("");
for(int i = 0; i < strlen(argv[1]); ++i){
if(argv[1][i] != '.') fileName += argv[1][i];
else break;
}

string prefix = "t";
string inFileTr = fileName+".tr", inFileTe = fileName+".te", outFileTr = (prefix+fileName+".tr"), outFileTe = (prefix+fileName+".te");


Matrix A = readData(inFileTr.c_str(), nf+1), B = readData(inFileTr.c_str(), nf+1);

int tnf = pca(A, B, nf, err, 0);
//temp = subMatrix(te,i,0,i,nf-1);
Matrix tempA1=subMatrix(A, 0, 0, A.getRow()-1, tnf-1), 
	tempA2 = subMatrix(A, 0, nf, A.getRow()-1,nf), newA(A.getRow(), tnf+1);



for(int i = 0; i < A.getRow(); ++i){
		for(int j = 0; j < tnf+1; ++j){
			if(j < tnf) newA(i, j) = tempA1(i, j);
			else newA(i, j) = tempA2(i, 0);
			}
	}
	A = newA;
/*	tempA1 = subMatrix(B, 0, 0, B.getRow()-1, tnf-1);
	tempA2 = subMatrix(B, 0, nf, B.getRow()-1, nf);
	newA = Matrix(B.getRow(), tnf+1);
for(int i = 0; i < B.getRow(); ++i){
		for(int j = 0; j < tnf+1; ++j){
			if(j < tnf) newA(i, j) = tempA1(i, j);
			else newA(i, j) = tempA2(i, 0);
			}
	}
	B = newA;
*/
writeData(A, outFileTr.c_str());
//writeData(B, outFileTr.c_str());

return 0;
}

