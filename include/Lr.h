/********************************************************************
 * Lr.h - header file of the LR function which defines 
 *           a method of classifying samples
 *
 * Copyright (C) isherman@vols.utk.edu, Sep 2014
 *
 *
 ********************************************************************/

#ifndef LR__H_
#define LR__H_

#include <iostream>
using namespace std;


  //Given a sample (tedata), and a training set (train), and priors (Pw), and # of classes (c), 
  // return a label saying which class the sample belongs to.
  int lr(const Matrix &train, const Matrix &tedata, const int c, const Matrix &Pw);
#endif