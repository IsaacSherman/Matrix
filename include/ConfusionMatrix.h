#ifndef ___COMA_H__
#define ___COMA_H__
/********************************************************************
 * ConfusionMatrix.h - header file of the ConfusionMatrix library 
 * which defines a new class "ConfusionMatrix" and the associated
 * member functions
 *
 * Note: 
 *   This is a simple C++ library for extracting confusion matrices from 2 
 *   class systems. 
 *
 * Copyright (C) 2014 Isaac Sherman (isherman@vols.utk.edu)
 
*******************************************************************/
#include <cmath>

#include <string>

using namespace std;

        class ConfusionMatrix
        {
            /// <summary>
            /// Core data
            /// </summary>
            int truePs, trueNs, falsePs, falseNs;
            public:
			typedef enum { truePositive, trueNegative, falsePositive, falseNegative }HitTypes;
		void ResetMatrix();
		double MatthewsCorrelationCoefficient(); 
		double MCC(); 
		double Accuracy(); 
		double F1();
		ConfusionMatrix(); ConfusionMatrix(int, int, int, int); 
		double MissRate();
		double FalseDiscoveryRate();	
		double	FallOut(); 
		double  Precision(); 
		double  Predictive();
		double Specificity();
		double HitRate();
		int  TruePositives(); 
		int  TrueNegatives();
		int  FalsePositives();
		int  FalseNegatives(); 
		int totalReportedPositives();
		int totalReportedNegatives();
		int totalPositives();
		int totalNegatives();
		double  NPV(); 
		void RecordEvent(HitTypes); 
		void WriteToFile(string fileName);
			};//sensitivity (getHitRate,, Specificity, Precision, and getHitRate.

ConfusionMatrix:: HitTypes EventType(bool, bool);

		#endif