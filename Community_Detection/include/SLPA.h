/*
 * SLPA.h
 *
 *  Created on: Oct 7, 2013
 *  Author: Anatoli Melechko, Gaurav Saraf, Kalpesh Padia
 *  Based on algorithm by Jierui Xie and Boleslaw K. Szymanski published in
 *  "Towards Linear Time Overlapping Community Detection in Social Networks"
 */

#ifndef SLPA_H_
#define SLPA_H_

#include "Graph.h"
#include "Node.h"
#include <tr1/unordered_map>
#include <tr1/random>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "error.h"

typedef std::tr1::unordered_map<Label, std::vector<NodeID> > Community;
typedef std::set<string> Set;

class SLPA{
public:
	Graph* theGraph;
	string inputFileName;
    string outputFileName;
    Community final_communities;
    Set final_set;
	SLPA(string, string);
	virtual ~SLPA();
	void propagateLabels(int numIterations);
	void outputCommunities(double);
	void writeCommunities();
private:

	unsigned int selectRandomNode();

};


#endif /* SLPA_H_ */
