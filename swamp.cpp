#include <random>
#include <ctime>
#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <cstdlib>

//Generates a nxn matrix, n = size. Fills it with random numbers from 1 to 9.
void generateSwamp(std::vector<std::vector<int>> &swamp,int size){
  std::srand(std::time(0));
  for(auto &row : swamp)
    for(auto &col : row)
      col=(std::rand()%9)+1;
}
// Prints the matrix passes as argument.
void print(std::vector<std::vector<int>> &swamp){
  for(auto row : swamp){
    for(auto col : row)
      std::cout << col << " ";
    std::cout  << std::endl;
    }
    std::cout  << std::endl;
}
// Finds one of the cheapest left-to-right paths in the swamp matrix and returns the cheapest total trek cost.
int findPath(std::vector<std::vector<int>> &swamp,std::vector<std::vector<int>> &shortestPath,int size){
  // Fill out the first column with the value of the first column in swamp.
  // This is all the possible starting poisitions.
  for(int row = 0 ; row < size ; ++row)
    shortestPath[row][0] = swamp[row][0];

  for(int col = 1 ; col < size ; ++col){
    for(int row = 0 ; row < size ; row++){
      int fromSame,fromBelow,fromTop;
      fromSame = shortestPath[row][col-1];
      fromBelow = row<(size-1) ? shortestPath[row+1][col-1] : std::numeric_limits<int>::max();
      fromTop = row>0 ? shortestPath[row-1][col-1] : std::numeric_limits<int>::max();
      int min = std::min(std::min(fromTop,fromBelow),fromSame);
      shortestPath[row][col] = min + swamp[row][col];
    }
  }
  //Returns the smallest total path cost
  int cheapestPathCost=std::numeric_limits<int>::max();
  for(int i = 0; i < size ; i++){
      if(cheapestPathCost>shortestPath[i][size-1])
        cheapestPathCost = shortestPath[i][size-1];
  }
  return cheapestPathCost;
}

//Backtracks through matrices swamp and shortestPath to find the one of the cheapest left-to-right path and prints it.
void printPath(std::vector<std::vector<int>> swamp, std::vector<std::vector<int>> shortestPath,int size){
  std::list<int> cheapestPath;
  int start=std::numeric_limits<int>::max();
  int index;
  //Get the index and value of the rightmost node with the smallest value, i.e. the finishing node
  // of the cheapest left-to-right path.
  for(int j = 0; j < size ; ++j){
    if(start>shortestPath[j][size-1]){
      start = shortestPath[j][size-1];
      index = j;
    }
  }
  cheapestPath.push_front(swamp[index][size-1]);

  int col = size-1;
  while(col){

    int fromSame,fromBelow,fromTop,currentNode;

    currentNode = swamp[index][col];
    fromBelow = index<(size-1) ? shortestPath[index+1][col-1] : std::numeric_limits<int>::max();
    fromTop = index>0 ? shortestPath[index-1][col-1] : std::numeric_limits<int>::max();
    fromSame = shortestPath[index][col-1];

    if(currentNode==start-fromBelow){
      start = fromBelow;
      index +=1;
      cheapestPath.push_front(swamp[index][col-1]);
    }
    else if(currentNode==start-fromTop){
      index -=1;
      start = fromTop;
      cheapestPath.push_front(swamp[index][col-1]);
    }
    else {
      start = fromSame;
      cheapestPath.push_front(swamp[index][col-1]);
    }
    --col;
  }
  //Print Cheapest Path.
  for(auto node:cheapestPath)
    std::cout << node << " ";
  std::cout << "\n" << std::endl;
}

int main(int argc, char const *argv[]) {

  if(argc==1){
    std::cout << "Enter matrix size!" << std::endl;
    return 0;
  }

  int size = atoi(argv[1]);
  std::vector<std::vector<int>> swamp(size,std::vector<int>(size,0));
  std::vector<std::vector<int>> shortestPath(size,std::vector<int>(size,0));

  generateSwamp(swamp,size);
  int cheapestPathCost = findPath(swamp,shortestPath,size);

  std::cout << "Svamp Matrix:\n"<< std::endl;
  print(swamp);
  std::cout << "Cheapest node path: ";
  printPath(swamp,shortestPath,size);
  std::cout << "Total path cost: " << cheapestPathCost << std::endl;

  return 0;
}
