/**********************************************************
 * preprocessing.cpp  
 *
 *   - normalize: normalize training and test set
 *   - pca: principal component analysis
 * 
 * Author: Hairong Qi (C) hqi@utk.edu
 *
 **********************************************************/
#include "Matrix.h"
#include "Pr.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;


/**
 * Matrix normalization.
 * @param tr The training set.
 * @param te The test set. 
 * @param nf The number of features.
 * @param flag If flag is on, it's supervised learning; otherwise, it's
 *             unsupervised learning and the second argument can be empty.
 */
void normalize(Matrix &tr, Matrix &te, const int nf, const int flag)
{
  Matrix mu, Sigma, sigma;

  // get the statistics from the training set
  mu = mean(tr, nf);

  Sigma = cov(tr, nf);
  sigma.createMatrix(nf,1);
  for (int j=0; j<nf; j++)
    sigma(j,0) = sqrt(Sigma(j,j));

  // normalize the training set
  for (int i=0; i<tr.getRow(); i++) {
    for (int j=0; j<nf; j++)
      tr(i,j) = (tr(i,j)-mu(j,0)) / sigma(j,0);
  }

  // normalize the test set
  if (flag) {
    for (int i=0; i<te.getRow(); i++) {
      for (int j=0; j<nf; j++)
	te(i,j) = (te(i,j)-mu(j,0)) / sigma(j,0);
    }
  }
}


/**
 * Principal component analysis.
 * @param tr The training set.
 * @param te The test set. 
 * @param nf The number of features.
 * @param err The error rate needs to be satisfied.
 * @param flag If flag is on, it's supervised learning; otherwise, it's
 *             unsupervised learning and the second argument can be empty.
 * @return The number of features after PCA based on "err"
 */
int pca(Matrix &tr, Matrix &te, const int nf, const float err, const int flag)
{
  Matrix Sigma, temp;
  Matrix d(1,nf),   // eigenvalue (a row vector) 
    V(nf,nf),       // eigenvector with each col an eigenvector
    pV;             // eigenvectors selected based on "err"
  int p, pnf;
  float psum, sum;

  Sigma = cov(tr, nf);
  jacobi(Sigma, d, V);
  eigsrt(d, V);   // sort the eigenvalue in the ascending order

  // determine the number of principal components to keep based on "err" given
  sum = 0.0;
  for (int i=0; i<nf; i++){
     sum += d(0,i);
	}
  p = 0;
  psum = 0.0;
  while (psum/sum < err && p < nf) {

    psum += d(0,p++);
 
  }
  pnf = nf - --p;

  pV = subMatrix(V,0,p,nf-1,nf-1);
  cout<<"pnf = "<<pnf <<" and p = "<< p<<endl;
  // perform the transformation 
  for (int i=0; i<tr.getRow(); i++) {          // for training set
    temp = subMatrix(tr,i,0,i,nf-1);//Pull 1 row
    temp = temp->*pV;
    for (int j=0; j<pnf; j++){
      tr(i,j) = temp(0,j);
	  }
  }
  if (flag) {
    for (int i=0; i<te.getRow(); i++) {          // for test set
      temp = subMatrix(te,i,0,i,nf-1);
      temp = temp->*pV;
    for (int j=0; j<pnf; j++){
      te(i,j) = temp(0,j);
	  }
    }
  }

  return pnf;
}

Matrix fld(Matrix &tr, const int nf, const int c)//Returns v, the optimal direction matrix
{
vector<Matrix> mu(c), covs(c), data(c), scatter(c);//Vectors of multiple matrices to handle variable numbers of classes.
int classes[c], count[c];//Indexed along with the vectors of matrices. This is now many samples belong to a given class.
for(int i = 0; i < c; ++i){
classes[i] = int(0);
}
Matrix ScatterW, SwInv, ret, muTot = mean(tr, nf), runningTot(nf,nf), STwixt;//SW, Sw^-1, return matrix v, mu for all the samples, SB (SBetween -> SBetwixt-> STwixt)
for(int i = 0; i < tr.getRow(); ++i)
{

 classes[(int)tr(i, nf)]+=1; //find c[i] for each class i where i E 0 <= i <= c
}

for(int i = 0; i < c; ++i){
cout<<"samples belonging to class " << i <<" = "<< classes[i]<<"c = "<< c<< endl;
Matrix temp(classes[i], nf);
data[i] = Matrix(classes[i], nf);
count[i] = int(0);
//mu[i]=Matrix(nf, 1);
//covs[i]=Matrix(1, nf);
}

for (int targetClass = 0; targetClass < c; ++targetClass){
	for(int i = 0; i < tr.getRow(); ++i){
	if(targetClass != tr(i, nf)) continue;
		for(int j = 0; j < nf; ++j){
			data[(int)tr(i, nf)](count[targetClass], j) = tr(i,j);
		}
	}
}

ScatterW = Matrix(nf, nf);
for(int i = 0; i < c; ++i){//Generate mean, covsariance and scatter while summing Sw
mu[i] = mean(data[i], nf);
covs[i] = cov(data[i], nf);
scatter[i] = classes[i] * covs[i];
ScatterW = ScatterW+scatter[i];
//cout<<"mu["<<i<<"] = "<<mu[i] << "Covariant of that index = "<<covs[i]<<"And scatter "<<scatter[i]<<endl;
}
SwInv = inverse(ScatterW);//Invert Sw
cout<<"SwInv = "<<SwInv.getRow()<<"x"<<SwInv.getCol()<<"matrix, while mu[0] is "<<mu[0].getRow()<<"x"<<mu[0].getCol()<<endl;
ret = SwInv ->* (mu[0]-mu[1]);//I'm going to return here, and finish implementing MDA at some point for more than 2 classes.

cout<<"ret = "<<endl<<ret;
return ret;

for(int i = 0; i < c; ++i){//sum the distance between the means of the classes and the mean of the samples
runningTot = runningTot+(classes[i]*( (mu[i]-muTot) ->* transpose((mu[i] - muTot))));//MDA
}
//STwixt =
}