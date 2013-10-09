#include "Node.h"
#include "Graph.h"
#include <tr1/unordered_map>
#include <vector>

Node::Node()
{
    //ctor
}

//Node::Node(Label node_ID)
//{
//    nodeID = node_ID;
//    mymap[nodeID] = 1;
//    community_count++;
//    maxlabel.insert(1);
//}

Node::Node(NodeID id)
{
    nodeID = id;
    mymap[nodeID] = 1;
    community_count = 1;
    listen_count = 0;
    //maxlabel.insert(1);
}

Node::~Node()
{
    //dtor
}

/** Access label
 * \return The current value of label
 */
Label Node::GetNodeID()
{
    return nodeID;
}

/** Access neighbors
 * \return The current value of neighbors
 */
Neighbors Node::GetNeighbors()
{
    return neighbors;
}

/** Set neighbors
 * \param val New value to set
 */
void Node::AddNeighbor(NodeID x)
{
    neighbors.push_back(x);
}

/** Find community;
 * \return true if community found;
 */
bool Node::isCommunityPresent(Label x)
{
    Community_Map::const_iterator got = mymap.find(x);
    if(got == mymap.end())
        return false;
    else
        return true;
}

/** Get Community Frequency;
 * \return the frequency of a community;
 */
unsigned int Node::GetCommunityCount(Label x)
{
    if(isCommunityPresent(x))
    {
        Community_Map::const_iterator got = mymap.find(x);
        return got->second;
    }
    else
        return 0;
}

/** Add a Community;
 */
void Node::AddCommunity(Label x)
{
    if(isCommunityPresent(x))
        mymap[x]++;
    else
        mymap[x] = 1;
    community_count++;
}

void Node::AddListenedLabel(Label x)
{
    if(isLabelListened(x))
        mylistener[x]++;
    else
        mylistener[x] = 1;
    listen_count++;
}

bool Node::isLabelListened(Label x)
{
    Listener_Map::const_iterator got = mylistener.find(x);
    if(got == mylistener.end())
        return false;
    else
        return true;
}

Label Node::getPopularLabel()
{
    cout<<"My total count is "<<listen_count<<endl;
    Label max_label = mylistener.begin()->first;
    float max_popular_probability = (float)mylistener.begin()->second/listen_count;
    cout<<"Following labels listened\n";
    for(Listener_Map::iterator it = mylistener.begin(); it != mylistener.end(); ++it)
    {
        Label current_label = it->first;
        unsigned int current_label_count = it->second;
        cout<<current_label<<'\t'<<current_label_count<<endl;
        float current_probability = (float)current_label_count/listen_count;
        if(current_probability > max_popular_probability)
        {
            max_label = current_label;
            max_popular_probability = current_probability;
        }
    }
    return max_label;
}

void Node::listen()
{
    int total_neighbors = neighbors.size();
    cout<<"Printing neighbors for Node: "<<GetNodeID()<<'\n';
    for(Neighbors::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
        cout<<*it<<'\t';
    cout<<'\n';
    int i = 0;
    Node *node[total_neighbors]; //initialize an array to store pointer to neighbors
    for(Neighbors::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        node[i] = Graph::getNode(*it);
        Label listened_label = node[i]->speak();
        if(isLabelListened(listened_label))
            mylistener[listened_label]++;
        else
            mylistener[listened_label] = 1;
        listen_count++;
        i++;
    }
    cout<<"Finished listening labels\n";
    // End of listening phase
    // Get the most popular listened label
    Label popular_label = getPopularLabel();
    cout<<"Adding community "<<popular_label<<" to the list of communities\n";
    // Add the popular_label to mymap
    if(isCommunityPresent(popular_label))
        mymap[popular_label]++;
    else
        mymap[popular_label] = 1;
    community_count++;
    listen_count = 0;
    mylistener.clear();
}

//void Node::listen(){
//	cout<<"I am node " << nodeID << " and I am listening"<<endl;
//}

Label Node::speak(){
    cout<<"Node "<<nodeID<<" is speaking"<<endl;
	Label mostLabel=nodeID;//returns most probable label
	double randy = doubleRand();
	cout<<"Randy is "<<randy<<endl;
	double intervalEdge = 0;
	Community_Map::iterator mapIt;
	for (mapIt = mymap.begin(); mapIt!=mymap.end(); ++mapIt){
		Label currentLabel = mapIt->first;
		unsigned int currentLabelCount = mapIt->second;  //points to value
		intervalEdge = intervalEdge + ((double)currentLabelCount)/community_count;
		cout<<"------------------intervalEdge = "<< intervalEdge<<endl;
		if(randy<=intervalEdge){
			cout<<"mostLabel returned by speak is "<<currentLabel<<endl;
			return currentLabel;
		}

	}

	return mostLabel;
}

double Node::doubleRand(){
	//srand (time(NULL));
	double f = (double)rand()/RAND_MAX;
	return f;
}

Community_Map Node::getMyMap()
{
    return mymap;
}

unsigned int Node::getTotalCommunityCount()
{
    return community_count;
}

