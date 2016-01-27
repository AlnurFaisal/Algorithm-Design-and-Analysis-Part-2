#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

class edgenode
{
	private:
		int cost;
		int nextNumber;

	public:
		edgenode(int, int);
		int getCost();
		int getNextnum();
};

edgenode::edgenode(int c, int n)
{
	cost = c;
	nextNumber = n;
}
int edgenode::getCost()
{
	return cost;
}
int edgenode::getNextnum()
{
	return nextNumber;
}

int main()
{
	/* - Program would be able to read a text file that has 500 * 500 edges
	   - K is the size of the number of cluster. K is set to 4
	   - Idea is to have the program decrease the number of cluster till there is 4 cluster using greedy algorithm
	   - Given distance are not distinct
	   - Measure the maximum spacing once k = 4
	   - Create a graph with the data provided. With the graph setup, group through similar vertices and slowly decrease k cluster to 4
       - Use union find method to merge so to reduce the k cluster */

	 // Variable Declarations
	   int source, destination, cost;
	   int count = 0;
	   int quit  = 0;
	   string templine;
	   std::vector <std::list<edgenode> > adjList(500);

	// Create a while & for loop to generate the auto creation of the edgenode from reading of the text file
		
		ifstream infile("/Users/alnurfaisal/Desktop/edge_distance.txt");
		if(infile.is_open())
		{
			// !!Will use the data taken from the first line to generate the maximum cycles(499). After first initial test!!
			// Skips the reading of the first line 
			std::getline(infile, templine);
			cout << "There is " << templine << " nodes." << endl ;
			// Start reading the txt file from the second line
				for(int x=0; x<499; x++)
				{
					for(int y=0; y<499; y++)
					{
						// Create vector of object to store edgenode to build adjency list(graph using adjency list)
						// Vector index will reflect the index of the source node(eg. if graph link is 1 : 4 means 1 
						// is the vector index and 4 is stored in the edgenode object as destination)
	//**************************Create if condition to stop the getlile command ********************************************
						if(!infile.eof())
						{
							std::getline(infile, templine);
							std::istringstream iss(templine);
							iss >> source >> destination >> cost;
							cout << "The values are: " << source << " " << destination << " " << cost << endl;
							adjList[source].push_back(edgenode(cost, destination));
						}
						else
						{
							quit++;
							break;
						}
						
					}
					if(quit == 1)
					{
						break;
					}
				}
		}
		else
		{
			cout << "Unable to open file. " << endl;
		}
		
		

		std::vector<std::list<edgenode> >::iterator i;

		for(std::vector<std::list<edgenode> >::iterator i = adjList.begin(); i != adjList.end(); ++i)
		{

			std::list<edgenode> li = *i;
			for(std::list<edgenode>::iterator iter = li.begin(); iter != li.end(); ++iter)
			{
				cout << "Node " << count << " is connected to Node ";
				cout << (*iter).getNextnum() << " and the cost between both vertices is " << (*iter).getCost() << ".";
				cout << endl;
			}
			count++;

		}

		// Graph created using adjency list. To apply clustering using union find.
	
	
	return 0;
}