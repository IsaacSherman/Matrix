#include "Matrix.h"
#ifndef FOOZIEWHATSITZ
#define FOOZIEWHATSITZ


void normalize(Matrix &tr, Matrix &te, const int nf, const int flag);
int pca(Matrix &tr, Matrix &te, const int nf, const float err, const int flag);
Matrix fld(Matrix &tr, const int nf, const int classNum);
int knn(Matrix tr, Matrix Sample, int nf, int c, int k, double n=2, bool usePartial = true);
#endif