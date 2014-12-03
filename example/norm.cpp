#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "Matrix.h"             // include the Matrix class definition
#include "Pr.h"
#include "Norm.h"
#include <cstring>
#define USAGE "./norm [file assuming extension .tr/.te] NumberOfFeatures err will take the normalized files and reduce the dimensionality using the PCA method"

int main(int argc, char * argv[]){
if(argc != 3) {
cerr<<USAGE<<endl;
return 1;
}
int nf = atoi(argv[2]);
string fileName("");
for(int i = 0; i < strlen(argv[1]); ++i){
if(argv[1][i] != '.') fileName += argv[1][i];
else break;
}


string inFileTr = fileName+".tr", inFileTe = fileName+".te", outFileTr = (fileName+"_norm"+".tr"), outFileTe = (fileName+"_norm"+".te");


Matrix A = readData(inFileTr.c_str(), nf+1), B = readData(inFileTe.c_str(), nf+1);

normalize(A, B, nf, 1);

writeData(A, outFileTr.c_str());
writeData(B, outFileTe.c_str());


return 0;
}