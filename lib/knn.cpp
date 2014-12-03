#include "Matrix.h"
#include <set>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;


struct knnComp{
bool operator()(const vector<double> & lhs, const vector<double>& rhs) const
{ return lhs[1] < rhs[1];}
};
double getKthElementOfSet(int k, int index,
		set<vector<double>, knnComp> & neighbors){
set<vector<double>, knnComp>::iterator it = neighbors.begin();
int i;
  for ( i = 0; it!=neighbors.end() && i < k; ++it, ++i);
  return (*it)[index];
  }
 int getMax(vector<int> a){
 int max= -1, ret = -1;
 for(int i = 0; i < a.size(); ++i){
 if(max < a[i]) {
 max = a[i]; ret = i;
 }
 }
 for(int i = ret+1; i < a.size(); ++i){
 if(max == a[i]) {
 ret = -1;//Tie
 break;
 }
 }
 return ret;
 }
 
 vector<int> getTieIndices(vector<int> votes){
 vector<int>ret;
 int max = -1;
 for(int i = 0; i < votes.size(); ++i){
 if(max < votes[i]) max = votes[i];
 }
 for(int i = 0; i < votes.size(); ++i){
 if(votes[i] == max) ret.push_back(i);
 }
 return ret;
 
 }
 

int knn(Matrix tr, Matrix Sample, int nf, int c, int k, double n = 2, bool usePartial = true){
set<vector<double>, knnComp> neighbors;
for(int i = 0; i < tr.getRow(); ++i){
	vector<double> *temp = new vector<double>(3, 0);
if(i > k && usePartial) { //do partial distance stuff
	double maxDist = pow(getKthElementOfSet(k,1, neighbors), n);
	//index 0 is the position in the training set,
	//index 1 is the distance from the sample
	//index 2 is the class label
	double dist = 0;
	bool alreadyGreater = false;
	for(int j = 0; j < nf+1; ++j){
	dist+= pow((tr(i, j)-Sample(0, j)),n);
	if(dist >= maxDist) {
	alreadyGreater = true;
	break;
	}
	}
	if(!alreadyGreater){
	dist = pow(dist, 1.0/n);
	(*temp)[0] = i;
	(*temp)[1] =dist;
	(*temp)[2] = tr(i, nf);
	neighbors.insert(*temp);
	}
}
else{
	
	//index 0 is the position in the training set,
	//index 1 is the distance from the sample
	//index 2 is the class label

	double dist = 0;
	for(int j = 0; j < nf+1; ++j){
	dist+= pow((tr(i, j)-Sample(0, j)),n);
	//add the partial distance jigger here in the upper block
	}
	dist = pow(dist, 1.0/n);
	(*temp)[0] = i;	
	(*temp)[1] = dist;
	(*temp)[2] = tr(i, nf);
	neighbors.insert(*temp);

}
}
//All the training jiggers are whatchacallitted.

set<vector<double>, knnComp>::iterator it;
it = neighbors.begin();
vector<int> votes(c, 0);
for(int i = 0; i < k; ++i, ++it)
votes[(int)getKthElementOfSet(i, 2, neighbors)]++;

int maxVote = getMax(votes);
if(maxVote == -1) {//tie
vector<int> tie = getTieIndices(votes);	
return tie[rand() % tie.size()];
}
else return maxVote;


}



