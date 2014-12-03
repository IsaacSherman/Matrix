/********************************************************************
 ** lr.cpp
 **
 ** Purpose: Supervised learning: 
 **    Maximum posterior probability (MPP). This algorithm assumes 
 **    Gaussian distribution and zero-one loss 
 ** 
 ** Prototype: int lr(Matrix train, Matrix test, 
 **                    int class, Matrix Pw) 
 **    - train: the training set of m x (n+1) matix
 **             where m is the nr of rows (or samples)
 **             n is the number of features
 **             the last column is the class label, starting at 1
 **    - test: the testing sample to be classified, a column vector
 **            with a dimension nx1
 **    - class: number of different classes, assuming the class labels
 **             starts at 0
 **    - case: 1, 2, 3 - case I, II or III
 **    - Pw: Prior probability. A column vector of dimension cx1
 ** 
 **    - output: the class label of the input test sample
 **
 ** 	Original (mpp.cpp) Created by: Hairong Qi (hqi@utk.edu)
 **
 ** Modified by Isaac Sherman
 **   - 02/20/2008: the class label starts at 0 instead of 1
 **
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Pr.h"

using namespace std;

int lr(const Matrix &train, const Matrix &tedata, const int c, const Matrix &Pw, int cases)
{
  static int first = 1, nf;
  static double varavg;
  static Matrix *means, *covs, covavg;
  int nctr, ncte, nrtr, nrte;
  int i, j;
  Matrix covsum, tmp;
  double sum;
	if (c != 2) {
	cout<<"this implementation of LR only works for 2 cases.\n";
	exit(1);
	}
  //////////////////////////////////////////////////////////////////////
  // calculate the means and covs only when the function is called the 1st time
  if (first==1) {
    // get the size of input raw data
    nctr = train.getCol();
    ncte = tedata.getCol();
    nrtr = train.getRow();
    nrte = tedata.getRow();
    if (nctr != (nrte+1)) {
      cout << "LR: "
	   << "Training and testing set do not have same number of features\n";
      exit(3);
    }
    nf = nctr-1;

    // calculate the mean and covariance of each class
    // the mean is a cxnf matrix and the cov is a c*nf x nf matrix
    means = (Matrix *) new Matrix [c];
    for (i=0; i<c; i++)
      means[i].createMatrix(nf, 1);
    covs = (Matrix *) new Matrix [c];
    for (i=0; i<c; i++)
      covs[i].createMatrix(nf, nf);

    // the following two matrices are used for case 2
    // the average covariance matrix is used as the common matrix
    covsum.createMatrix(nf,nf);
    covavg.createMatrix(nf,nf);

    for (i=0; i<c; i++) {
      tmp = getType(train, i);
      covs[i] = cov(tmp, nf);
      means[i] = mean(tmp, nf);
      covsum = covsum + covs[i];
    }
    
    // calculate the average covariance to be used by case II
    covavg = covsum / (double)c;

    // calculate the average variance to be used by case I
    sum = 0.0;
    for (i=0; i<c; i++)
      sum += covavg(i,i);
    varavg = sum / (double)c;

    first++;
  
   
   
   }

  //////////////////////////////////////////////////////////
  // classification
  Matrix disc(1,c), sdisc(1,c), pos(1,c);
  double mdist, edist;

  // find the discriminant function value
    switch (cases) {
  case 1:
    for (i=0; i<c; i++) {        // for each class
      edist = euc(tedata, means[i]);
      disc(0,i) = log(2*M_PI)*c/2 - log(Pw(i,0)) + edist*edist;
    }
    break;
  case 2:
    for (i=0; i<c; i++) {
      mdist = mah(tedata, covavg, means[i]);
      	  disc(0,i) = log(2*M_PI)*c/2-2*log(varavg) - log(Pw(i,0)) + mdist*mdist;
    }
    break;
  case 3:
    for (i=0; i<c; i++) {
		//mdist = mah(tedata, covs[i], means[i]);
      //disc(0,i) = .5*(log(det(covs[i]) - mdist*mdist));
	  mdist = mah(tedata, covs[i], means[i]);
	  
	  disc(0,i) = log(2*M_PI)*c/2-2*log(det(covs[i])) - log(Pw(i,0)) + mdist*mdist;
    }
	}
   
  

  // sort the discriminant function value in the ascending order
  insertsort(disc, sdisc, pos);

  // return the label of the class with the least discriminant value
  //if(cases == 2 or cases == 1) return (int) pos(0,nc-1);
  return (int)pos(0,0);
}