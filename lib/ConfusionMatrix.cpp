#include "ConfusionMatrix.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
/********************************************************************
 * ConfusionMatrix.cpp - implementation of the ConfusionMatrix library 
 * which defines the associated member functions
 *
 * Note: 
 *   This is a simple C++ library for extracting confusion matrices from 2 
 *   class systems. 
 *
 * Copyright (C) 2014 Isaac Sherman (isherman@vols.utk.edu)
 
*******************************************************************/
using namespace std;

           void ConfusionMatrix::RecordEvent(HitTypes hit)
            {
                switch (hit)
                {
                    case trueNegative:
                        this->trueNs++;
                        break;
                    case truePositive:
                        this->truePs++;
                        break;
                    case falsePositive:
                        this->falsePs++;
                        break;
                    case falseNegative:
                        this->falseNs++;
                        break;
                    default:
                        break;
                }
            }
           
			
            ConfusionMatrix::HitTypes EventType(bool correctAnswer, bool givenAnswer)
            {
                if (correctAnswer == givenAnswer)
                {
                    if (correctAnswer == true) return ConfusionMatrix::truePositive;
                    else return ConfusionMatrix::trueNegative;
                }
                else
                {//Answers don't match
                    if (correctAnswer == true) return ConfusionMatrix::falseNegative;
                    else return ConfusionMatrix::falsePositive;
                }
            }
			
            
            /// <summary>
            /// Accurate prediction, a hit.  Correct identification.
            /// </summary>
             int ConfusionMatrix::TruePositives(){    return truePs;   }
            /// <summary>
            /// Accurate rejection, correct rejection.  
            /// </summary>
             int ConfusionMatrix::TrueNegatives   ()         {                 return trueNs;             }
            /// <summary>
            /// Miss.  The class it was looking at was a subject it should have identified, and it failed to.
            /// </summary>
             int ConfusionMatrix::FalseNegatives    ()        {                 return falseNs;             }
            /// <summary>
            /// False Alarm- there was nothing there, but it attacked anyway.
            /// </summary>
             int ConfusionMatrix::FalsePositives      ()      {             return falsePs;           }
            //Derived Data
            /// <summary>
            /// TP+FN, the number of positives evaluated (correctly or not)
            /// </summary>
             int ConfusionMatrix::totalPositives ()             {                 return truePs + falseNs;             }
            /// <summary>
            /// TN+FP, the number of negatives evaluated (correctly or not)
            /// </summary>
             int ConfusionMatrix::totalNegatives()            {                return trueNs + falsePs;             }
            /// <summary>
            /// TN+FN, the total number of negatives reported
            /// </summary>
             int ConfusionMatrix::totalReportedNegatives()            {                return trueNs + falseNs;            }
            /// <summary>
            /// TP+FP, the total number of positives reported
            /// </summary>
             int ConfusionMatrix::totalReportedPositives ()            {                 return truePs + falsePs;             }
            /// <summary>
            /// True Positive Rate, Aka Hit Rate, TPR, recall (TP/(TP+FN))
            /// </summary>
             double ConfusionMatrix::HitRate()            {                 return (double)truePs / (double)totalPositives();             }
            /// <summary>
            /// True Negative Rate, aka SPC or Specificity
            /// </summary>
             double ConfusionMatrix::Specificity()            {                 return (double)TrueNegatives() / (double)totalNegatives();             }
            /// <summary>
            /// Precision, or Positive Predictive Value
            /// </summary>
             double ConfusionMatrix::Precision()            {                 return (double)TruePositives() / (double)(totalReportedPositives());             }
            /// <summary>
            /// Negative Predictive Value (TN/(TN+FN))
            /// </summary>
             double ConfusionMatrix:: NPV()            {                 return (double)trueNs / (double)(totalReportedNegatives());             }
            /// <summary>
            /// False Positive Rate, fall-out, or FPR (FP/(FP+TN));
            /// </summary>
             double ConfusionMatrix::FallOut()            {                return (double)(falsePs / totalNegatives());             }
            /// <summary>
            /// FalseDiscoveryRate(FP/(FP+TP)=1-PPV)
            /// </summary>
             double ConfusionMatrix::FalseDiscoveryRate()            {                 return (double)FalsePositives() / (totalReportedPositives());             }
             double ConfusionMatrix::MissRate()            {                 return (double)falseNs / (totalPositives());             }
            /// <summary>
            /// (TP+TN)/(P+N), rate it got right, overall
            /// </summary>
             double ConfusionMatrix::Accuracy (){  return (double)(truePs + trueNs) / (totalPositives() + totalNegatives()); } 
            /// <summary>
            /// F1, the harmonic mean of Precision and Sensitivity. 
            /// </summary>
             double ConfusionMatrix:: F1 (){  return (double)(truePs * 2) / (2 * truePs + falseNs + falsePs); }
            /// <summary>
            /// Measure of the quality of binary classifications.  0 is no better than chance, -1 is 100% inaccuracy, 1 is 100% accuracy
            /// Closely related to the chi-squared stat: Abs(MCC) = sqrt(chi^2/n);
            /// </summary>
			double ConfusionMatrix::MCC(){ return MatthewsCorrelationCoefficient();}
             double ConfusionMatrix::MatthewsCorrelationCoefficient()
            {
                    double ret;
                    if ((this->truePs + this->falsePs) == 0 || (this->truePs + this->falseNs) == 0 || (
                        this->trueNs + this->falsePs) == 0 || (this->trueNs + this->falseNs) == 0)//We'll get an infinity if we divide by zero, which would be out of our range
                        ret = (double)(this->truePs * this->trueNs - this->falsePs * this->falseNs);
                    else
                    {
                        double num = (double)(this->truePs * this->trueNs - this->falsePs * this->falseNs);
                        double denom = (double)(this->truePs + this->falsePs);
                        denom *= (this->truePs + this->falseNs);
                        denom *=(this->trueNs + this->falsePs);
                        denom*= (this->trueNs + this->falseNs);
                        denom = sqrt(denom);
                        ret = num / denom;
                    }
                    return ret;
                }
            
             ConfusionMatrix::ConfusionMatrix()            {                trueNs = truePs = falsePs = falseNs = 0;            }

             ConfusionMatrix::ConfusionMatrix(int tp, int tn, int fp, int fn)
            {
                truePs = tp;
                trueNs = tn;
                falsePs = fp;
                falseNs = fn;

            }
            /// <summary>
            /// Resets the core variables to 0
            /// </summary>
             void ConfusionMatrix::ResetMatrix()           {                trueNs = truePs = falsePs = falseNs = 0;            }
			 void ConfusionMatrix::WriteToFile(string fileName){
			 std::ofstream out;
				out.open(fileName.c_str(), std::ofstream::out);
			 if(out.good()){
			 out<<truePs<<","<<trueNs<<", "<<falsePs<<","<<falseNs<<endl;
			 out.close();
			 }
			 else{
			 cerr<<"Write to "<<fileName<<" failed."<<endl;
			 }
			 
			 }
			 
	