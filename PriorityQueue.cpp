#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "PriorityQueue.hpp"
#include <iomanip>

void swap(GroupNode *node1, GroupNode *node2){
  GroupNode temp = *node1;
  *node1 = *node2;
  *node2 = temp;
}

int parent(int index)
{
  return (index-1)/2;
}

/*
Returns the left child of a node.
*/
int leftChild(int index)
{
  return ((2*index) + 1);
}

/*
Returns the right child of a node.
*/
int rightChild(int index)
{
  return ((2*index) + 2);
}

void PriorityQueue::enqueue (std::string _groupName, int _groupSize, int _cookingTime){
  if(currentQueueSize == maxQueueSize){
    std::cout << "Heap full, cannot enqueue" << std::endl;
    return;
  }
  GroupNode newNode;
  newNode.cookingTime = _cookingTime;
  newNode.groupSize = _groupSize;
  newNode.groupName = _groupName;
  priorityQueue[currentQueueSize] = newNode;
  repairUpward(currentQueueSize);
  currentQueueSize++;
}

void PriorityQueue::repairUpward(int nodeIndex){
  //int max = nodeIndex;
  int p = parent(nodeIndex);
  if(priorityQueue[p].groupSize < priorityQueue[nodeIndex].groupSize){
    return;
  }
  else if(priorityQueue[p].groupSize > priorityQueue[nodeIndex].groupSize){
    swap(&priorityQueue[p], &priorityQueue[nodeIndex]);
    repairUpward(p);
  }
  else if(priorityQueue[p].cookingTime > priorityQueue[nodeIndex].cookingTime){
    swap(&priorityQueue[p], &priorityQueue[nodeIndex]);
    repairUpward(p);
  }
}

PriorityQueue::PriorityQueue(int queueSize){
  maxQueueSize = queueSize;
  currentQueueSize = 0;
  priorityQueue = new GroupNode[queueSize];
}

// Purpose: free all resources that the object has acquired
PriorityQueue::~PriorityQueue(){
  delete[] priorityQueue;
}


//Purpose: remove the group (allocate the table) at the front of the priority queue from
void PriorityQueue::dequeue(){
  if(currentQueueSize == 0){
    std::cout << "Heap empty, cannot dequeue" << std::endl;
    return;
  }
  priorityQueue[0] = priorityQueue[currentQueueSize-1];
  currentQueueSize--;
  repairDownward(0);
}

// return: groupID of the group at the front of the priority queue
GroupNode PriorityQueue::peek(){
  if(currentQueueSize == 0){
    std::cout << "Heap empty, nothing to peek" << std::endl;
    return GroupNode{};
  }
  else{
    return priorityQueue[0];
  }
}

//return: true if queue is full, false otherwise
bool PriorityQueue::isFull(){
  if(currentQueueSize == maxQueueSize){
    return true;
  }
  return false;
}

// return: true if queue is empty, false otherwise
bool PriorityQueue::isEmpty(){
  if(currentQueueSize == 0){
    return true;
  }
  return false;
}

int PriorityQueue::sum(){
  int sum = 0;
  int count = 0;
  while(count != ){
    sum = sum +
  }

}

// Purpose: maintain heap properties by swapping node with child if necessary
void PriorityQueue::repairDownward(int nodeIndex){
  int min = nodeIndex;
  int l = leftChild(nodeIndex);
  int r = rightChild(nodeIndex);
  if(l < currentQueueSize && priorityQueue[l].groupSize < priorityQueue[nodeIndex].groupSize){
    min = l;
    if(priorityQueue[r].groupSize < priorityQueue[l].groupSize && r < currentQueueSize){
      min = r;
    }
  }
  if(r < currentQueueSize && priorityQueue[r].groupSize < priorityQueue[nodeIndex].groupSize){
    min = r;
  }
  if(l < currentQueueSize && priorityQueue[l].cookingTime < priorityQueue[nodeIndex].cookingTime && priorityQueue[l].groupSize == priorityQueue[nodeIndex].groupSize){
    min = l;
    if(priorityQueue[l].groupSize == priorityQueue[r].groupSize && r < currentQueueSize && priorityQueue[r].cookingTime < priorityQueue[l].cookingTime){
      min = r;
    }
  }
  if(r < currentQueueSize && priorityQueue[r].cookingTime < priorityQueue[nodeIndex].cookingTime && priorityQueue[r].groupSize == priorityQueue[nodeIndex].groupSize){
    min = r;
  }
  if(min != nodeIndex){
    swap(&priorityQueue[min], &priorityQueue[nodeIndex]);
    repairDownward(min);
  }
  return;
}

int main(int argc, char *argv[]){
  PriorityQueue p(std::stoi(argv[1]));
  std::string input = "0";
  std::string name = "";
  std::string time = "";
  std::string size = "";
  while(stoi(input) != 6){
    std::cout << "============Main Menu============" << std::endl;
    std::cout << "1. Get group information from file" << std::endl;
    std::cout << "2. Add a group to Priority Queue" << std::endl;
    std::cout << "3. Show next group in the queue" << std::endl;
    std::cout << "4. Serve Next group" << std::endl;
    std::cout << "5. Serve Entire Queue" << std::endl;
    std::cout << "6. Quit" << std::endl;
    getline(std::cin,input);
    switch(stoi(input)){
      case 1:
          {
        std::string file;
        std::cout << "Enter filename:" << std::endl;
        std::cin >> file;
        std::ifstream queue(file);
        if(!queue.is_open()){
          std::cout << "File failed to open" << std::endl;
        }
        int count = 0;
        while(getline(queue, name, ' ') || count == std::stoi(argv[1])){
          getline(queue, size, ' ');
          getline(queue, time);
          count++;
          p.enqueue(name, std::stoi(size), std::stoi(time));
        }
        if(count == std::stoi(argv[1])){
          std::cout << "Heap full, cannot enqueue" << std::endl;
        }
        break;
        }
      case 2:
          {
        std::cout << "Enter Group Name: " << std::endl;
        getline(std::cin, name);
        std::cout << "Enter Group Size: " << std::endl;
        getline(std::cin, size);
        std::cout << "Enter Estimated Cooking Time: " << std::endl;
        getline(std::cin, time);
        if(p.isFull()){
          std::cout << "Heap full, cannot enqueue" <<std::endl;
        }
        else{
          p.enqueue(name,std::stoi(size),std::stoi(time));
        }
        break;
        }
      case 3:
          {
        if(p.isEmpty()){
          std::cout << "Heap empty, nothing to peek" << std::endl;
          break;
        }
        std::cout << "Group Name: " << p.peek().groupName << std::endl;
        std::cout << "Group Size: " << p.peek().groupSize << std::endl;
        std::cout << "Group Time: "<< p.peek().cookingTime << std::endl;
        break;
        }
      case 4:
      if(p.isEmpty()){
        std::cout << "Heap empty, cannot dequeue" << std::endl;
      }
      else{
        std::cout << "Group Name: " << p.peek().groupName;
        std::cout << " - Total Cook Time for the Group: " << p.peek().cookingTime << std::endl;
        p.dequeue();
      }
        break;
      case 5:
        if(p.isEmpty()){
          std::cout << "Heap empty, cannt dequeue" << std::endl;
        }
        while(!p.isEmpty()){
          std::cout << "Group Name: " << p.peek().groupName;
          std::cout << " - Total Cook Time for the Group: " << p.peek().cookingTime << std::endl;
          p.dequeue();
        }
        break;
      case 6:
        std::cout << "Goodbye!" << std::endl;
        break;
    }
  }
}
