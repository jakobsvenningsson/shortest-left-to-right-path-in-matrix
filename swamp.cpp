#include <random>
#include <ctime>
#include <iostream>
#include <vector>
#include <list>
#include <limits>

void generateSwamp(std::vector<std::vector<int>> &swamp,int size){
  std::srand(std::time(0));
  for(auto &row : swamp)
    for(auto &col : row)
      col=(std::rand()%6)+1;
}
void print(std::vector<std::vector<int>> &swamp){
  for(auto row : swamp){
    for(auto col : row)
      std::cout << col << " ";
    std::cout  << std::endl;
    }
    std::cout  << std::endl;
}

int findPath(std::vector<std::vector<int>> &swamp,std::vector<std::vector<int>> &shortestPath,int size){
  for(int row = 0 ; row < size ; ++row)
    shortestPath[row][0] = swamp[row][0];
  for(int col = 1 ; col < size ; ++col){
    for(int row = 0 ; row < size ; row++){
      //std::cout << swamp[row][col] << " ";
      int fromSame,fromBelow,fromTop;
      fromSame = shortestPath[row][col-1];
      if(row<(size-1)){
        fromBelow = shortestPath[row+1][col-1];
      }
      else
        fromBelow = std::numeric_limits<int>::max();
      if(row>0)
          fromTop = shortestPath[row-1][col-1];
      else
          fromTop = std::numeric_limits<int>::max();

    int min = std::min(std::min(fromTop,fromBelow),fromSame);
    shortestPath[row][col] = min + swamp[row][col];

    }
  }
  //Returns the smallest total  path cost
  int shortest=0;
  for(int i = 0; i < size ; i++){
      if(shortest==0 || shortest>shortestPath[i][size-1])
        shortest = shortestPath[i][size-1];
  }
  return shortest;
}

void printPath(std::vector<std::vector<int>> swamp, std::vector<std::vector<int>> shortestPath,int size){
  std::list<int> path;
  int start = std::numeric_limits<int>::max();
  int index=std::numeric_limits<int>::max();

  //Get the index and value of the rightmost node with the smallest value
    for(int j = 0; j < size ; ++j){
      if(start==0 || start>shortestPath[j][size-1]){
        start = shortestPath[j][size-1];
        index = j;
      }
    }
    path.push_front(swamp[index][size-1]);

  int col = size-1;
  while(col){
    int fromSame,fromBelow,fromTop,current;
    if(index<size-1){
      fromBelow = shortestPath[index+1][col-1];
      current = swamp[index][col];
      if(current==start-fromBelow){
        start = fromBelow;
        index = index+1;
        path.push_front(swamp[index][col-1]);
        --col;
        continue;
      }
    }
    if(index>0){
      fromTop = shortestPath[index-1][col-1];
      current = swamp[index][col];
      if(current==start-fromTop){
        index = index-1;
        start = fromTop;
        path.push_front(swamp[index][col-1]);
        --col;
        continue;
      }
    }

    fromSame = shortestPath[index][col-1];
    current = swamp[index][col];
    if(current==start-fromSame){
      start = fromSame;
      path.push_front(swamp[index][col-1]);
      --col;
      continue;
    }
    --col;

  }
  for(auto node:path)
    std::cout << node << " ";
  std::cout << "\n" << std::endl;
}


int main(){
  int size = 20;
  std::vector<std::vector<int>> swamp(size,std::vector<int>(size,0));
  std::vector<std::vector<int>> shortestPath(size,std::vector<int>(size,0));
  generateSwamp(swamp,size);
  int x = findPath(swamp,shortestPath,size);
  std::cout << "Svamp Matrix:\n"<< std::endl;
  print(swamp);
  std::cout << "Cheapest node path: ";
  printPath(swamp,shortestPath,size);
  std::cout << "Total cost: " << x << std::endl;
  return 0;
}
