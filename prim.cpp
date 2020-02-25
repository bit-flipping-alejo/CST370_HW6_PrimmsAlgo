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

void populateNodeCost(int** edgeArray, int numEdges, int** nodeCostArray, int numNodes);
int main(){

	string fileName;
	ifstream infile;
	int numNodes;

	int numEdges;
	int** edgeArray;

	int** nodeCostArray;



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

	nodeCostArray = new int*[numNodes + 1]; //were going to ignore row0 and col0
											// so 4 nodes make a 5x5 so we can directly ref from input file

	for (int i = 0; i < (numNodes + 1); i++){
		nodeCostArray[i] = new int[numNodes + 1];
	}

	populateNodeCost(edgeArray, numEdges, nodeCostArray, numNodes);

	displayCostMatrix(  nodeCostArray, numNodes+1);

	//displayMatrix(edgeArray, numEdges);



	for (int i = 0; i < numEdges; i++){
		delete[] edgeArray[i];
	}

	delete[] edgeArray;

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








