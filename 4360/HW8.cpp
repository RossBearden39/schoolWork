/* Author: Ross Bearden
   Class: CSCI 4360
   Date: 4/13/17
   Assignment: Homework 8

   Purpose: This program will solve a maze using breadth-first search. The program will take a data file
   			containing the world and the goal coordinates as arguements and print print out the number of
   			steps it took to solve the maze as well as the path.
*/

#include <iostream>
#include <string>
#include <queue>

struct coord{
	int x;
	int y;
}start;

//Array of coordinates that will hold the shortest path
coord path[8][16] {0};

//World 1, can be commented out in place of another world
int world[8][16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1,
	            0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
		    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
                    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,  
		    0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
		    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
		    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
		    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0};

//World 2
/*
int world[8][16] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 
		    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
		    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 
		    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
	            0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
	            0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
		    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
		    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
*/

//Function declarations
int search(coord &goal);
bool findChild(coord currentNode);

int main(int argc, char* argv[])
{
	//Initialize start node
	start.x = 0;
	start.y = 0;

	//Initialize path array to all zeros
	coord temp;
	temp.x = -1;
	temp.y = -1;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 16; j++){
			path[i][j] = temp;
		}
	}
	//coord goal;
	coord goal;
	//Total steps of path
	int stepsTaken = 0;

	//Get goal coordinates
	std::cout << "Input the goal coordinates: ";
	std::cin >> goal.x >> goal.y;
	
	//Check coordinates are valid
	if(world[goal.y][goal.x] == 1 | goal.x > 15 | goal.y > 7)
	{
	   std::cout << "The given coordinates are not valid\n";
	   exit(1);
	}
	//Call search function to find shortest path
	stepsTaken = search(goal);

	//Print out number of steps taken and the path
	std::cout << "The number of steps from (" << start.x <<"," << start.y;
	std::cout << ") to (" <<goal.x << ", " << goal.y << ") is " << stepsTaken << std::endl;
	std::cout << "The path is: ";
	
	//Print out path up to but not including goal node
	coord currNode = start;
	
	while(currNode.x != goal.x | currNode.y != goal.y){
		std::cout << "(" << currNode.x << ", " << currNode.y << "), ";
		currNode = path[currNode.y][currNode.x];
	}
	
	//Prints out goal node
	std::cout << "(" << currNode.x << ", " << currNode.y << ")" << std::endl;

	return 0;
}


//Function that performs the breadth-first search starting form the goal and looking for the starting coordinates
//Returns totalSteps from start to goal and populates an array with shortest path
int search(coord &goal){
	int totalSteps = 0;
	coord currNode = goal;			//temp variable for current node being checked
	std::queue<coord> fringe;		//Queue to keep track of nodes to be searched
	path[goal.y][goal.x] = goal;
	//Loops till start node is found
	while(currNode.x != start.x | currNode.y != start.y){
		coord temp = currNode;
		//Checks left
		if(currNode.x -1 >= 0)
		{
			temp.x -= 1;
			if(findChild(temp)){
				fringe.push(temp);
				path[temp.y][temp.x] = currNode;
			}

		}
		//Check up
		if(currNode.y -1 >= 0)
		{
			temp = currNode;
			temp.y -= 1;
			if(findChild(temp)){
				fringe.push(temp);
				path[temp.y][temp.x] = currNode;
			}
		}
		//Check right
		if(currNode.x +1 <= 15)
		{
			temp = currNode;
			temp.x += 1;
			if(findChild(temp)){
				fringe.push(temp);
				path[temp.y][temp.x] = currNode;
			}
		}
		//Check down
		if(currNode.y +1 <= 7)
		{
			temp = currNode;
			temp.y += 1;
			if(findChild(temp)){
				fringe.push(temp);
				path[temp.y][temp.x] = currNode;
			}
		}
		//Get head of queue
		currNode = fringe.front();
		//Pop head node
		fringe.pop();
	
		
	}
	currNode = start;
	//Counts the steps from start to goal
        while(currNode.x != goal.x | currNode.y != goal.y){
                totalSteps++;
                currNode = path[currNode.y][currNode.x];
        }


	return totalSteps;
}
//This function recieve a possible child node and returns it if it valid
bool findChild(coord currentNode)
{
	//std::cout << "Checking Node: " << currentNode.x << ", " << currentNode.y << std::endl;
	if(world[currentNode.y][currentNode.x] != 1)
		if(path[currentNode.y][currentNode.x].x == -1 && path[currentNode.y][currentNode.x].y == -1 ){
			//std::cout << "Adding Node: " << currentNode.x << ", " << currentNode.y << std::endl;
			return true;
		}
	else{
		//std::cout << "Not Adding Node: " << currentNode.x << ", " << currentNode.y << std::endl;
		return false;
	}
	else{
		//std::cout << "Not Adding Node: " << currentNode.x << ", " << currentNode.y << std::endl;
		return false;
	}
}
