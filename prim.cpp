/***************************************************
 * Title: HW#6 Prims Algo
 * Abstract: implement Prims Algo
 * ID: 0000
 * Name: Alejandro Caicedo
 * Date: 2/24/2020
 * *************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits.h>

const int NUM_EDGE_COLUMNS = 3;
using namespace std;

void displayEdges( int** array, int numEdges);
void displayCostMatrix( int** array, int numVerts);
void displayVisited(int* vis, int numVis);
void populateNodeCost(int** edgeArray, int numEdges, int** nodeCostArray, int numNodes);
void primsAlgo( int** cost, int numCosts, int* visited, int &numVisited);

int main(){

	string fileName;
	ifstream infile;
	int numNodes;
	int numEdges;

	int** edgeArray;
	int** nodeCostArray;

	int startingNode;

	int* visited;
	int numVisited = 0;

	cout << "Enter a file name: " ;
	getline(cin, fileName);
	infile.open( fileName.c_str() );

	if (!infile){
		cout << "Could not open file. Exiting" << endl;
		return -1;
	}


	if ( !( infile >> numNodes)){
		cout << "Error reading first line" << endl;
		cout << "This likely points to a formatting error in the text file" << endl;
		cout << "Please check file and try again" << endl;
		cout << "EXITING" << endl;
		return -1;
	}

	if ( !( infile >> numEdges)){
		cout << "Error reading Second line" << endl;
		cout << "This likely points to a formatting error in the text file" << endl;
		cout << "Please check file and try again" << endl;
		cout << "EXITING" << endl;
		return -1;
	}

	// this is read as [startNode, endNode, cost]
	edgeArray = new int*[numEdges];
	for (int i = 0; i < numEdges; i++){
		edgeArray[i] = new int[NUM_EDGE_COLUMNS];
	}

	//populate
	for (int i = 0; i < numEdges; i++){
		for (int j = 0; j < NUM_EDGE_COLUMNS; j++){
			infile >> edgeArray[i][j];
		}
	}

	visited = new int[numNodes + 1]; // dont use 0th idx
	nodeCostArray = new int*[numNodes + 1]; //were going to ignore row0 and col0
											// so 4 nodes make a 5x5 so we can directly ref from input file

	for (int i = 0; i < (numNodes + 1); i++){
		nodeCostArray[i] = new int[numNodes + 1];
	}

	populateNodeCost(edgeArray, numEdges, nodeCostArray, numNodes);

	cout << "Enter a starting Vertex: ";
	cin >> startingNode;

	numVisited = 1;
	visited[1] = startingNode;

	primsAlgo( nodeCostArray, (numNodes + 1), visited, numVisited);

	cout << "num visited: " << numVisited << endl;

	displayCostMatrix(  nodeCostArray, numNodes+1);
	//displayMatrix(edgeArray, numEdges);
	displayVisited(visited, numVisited);


	// Clean Up
	for (int i = 0; i < numEdges; i++){
		delete[] edgeArray[i];
	}
	for (int i = 0; i < (numNodes + 1); i++){
		delete[] nodeCostArray[i];
	}

	delete[] edgeArray;
	delete[] nodeCostArray;
	delete[] visited;
	return 0;
}


void displayEdges( int** array, int numEdges){
	cout << endl;
	for (int i = 0; i < numEdges; i++){
		for (int j = 0; j < NUM_EDGE_COLUMNS; j++){
			cout << array[i][j] << " ";
		}
		cout << endl;
	}

}

void displayCostMatrix( int** array, int numVerts){
	for (int i = 0; i < numVerts; i++){
		for (int j = 0; j < numVerts; j++){
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}

void displayVisited(int* vis, int numVis){
	cout << "Order Visited: ";
	for (int i = 1; i <= numVis; i++){
		cout << vis[i] << " ";
	}
	cout << endl;
}

void populateNodeCost(int** edgeArray, int numEdges, int** nodeCostArray, int numNodes){

	for (int i = 0; i < (numNodes + 1); i++){
		for (int j = 0; j < (numNodes + 1); j++){
			nodeCostArray[i][j] = INT_MAX;
		}
	}

	int row;
	int col;
	int cost;
	for (int i = 0; i < numEdges; i++){
		row = edgeArray[i][0];
		col = edgeArray[i][1];
		cost = edgeArray[i][2];
		nodeCostArray[row][col] = cost;
	}
}

void primsAlgo( int** cost, int numCosts, int* visited, int &numVisited){

	//start at starting node, be greedy
	int minCost = INT_MAX;
	int minIdx;
	bool hasBeenVisited;
	cout << "num visited = " << numVisited << endl;
	cout << "numCosts = "  << numCosts << endl;
	while (numVisited != numCosts){

		minCost = INT_MAX;
		for(int accessibleNodes = 1; accessibleNodes <= numVisited; accessibleNodes++ ){


			for (int curCost = 1; curCost < numCosts; curCost++){
				cout << "[" << visited[accessibleNodes] << "][" << curCost << "]" << endl;
				// check visited nodes
				for (int visNodes = 1; visNodes <= numVisited; visNodes++){
					//cout << "visNode: " << visNodes << " || curCost: " << curCost << endl;
					if (curCost == visited[visNodes] ){
						//skip this
						hasBeenVisited = true;
						break;
					}
				}

				if (hasBeenVisited){
					//cout << "broke out of loop num: " << curCost << endl;
					hasBeenVisited = false;
					continue;
				}

				// Will reach here if it has NOT been visited
				if (cost[ visited[accessibleNodes] ][curCost] < minCost){
					// will reach here if currCost less than curMin
					minCost = cost[ visited[accessibleNodes] ][curCost] ;
					minIdx = curCost;
				}

			} // end curCost

		} // end Accessible Nodes


		if (minCost != INT_MAX){
			numVisited++;
			visited[numVisited] = minIdx;
			cout << "minIdx:" << minIdx << " || cost: " << minCost;
		} else {
			// no more mins, so all done
			cout << "oops" << endl;
			break;
		}

	} // end while

}























