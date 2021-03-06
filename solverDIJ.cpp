#include "vector"
#include <algorithm>
#include <iostream>
#include <utility>
#include <queue>
#include <climits>
#include <set>
#include <bits/stdc++.h>

using namespace std;

// Struct to create nodes from
struct Node {
  // Current coords
  int x, y;
  // Distance from starting node
  int dist;
  // Previous node
  Node* prev;
};

// Struct to create a min prioriy queue
struct Compare {
  bool operator()(const Node* a, const Node* b) {
    return a->dist > b->dist;
  }
};

// Struct to allow unordered maps to have a key as a pair
struct hash_pair {
  template<class T1, class T2>
  size_t operator()(const pair<T1, T2>& p) const {
    auto hash1 = hash<T1>{}(p.first);
    auto hash2 = hash<T2>{}(p.second);
  
    if(hash1 != hash2) {
      return hash1 ^ hash2;
    }
    return hash1;
  }
};

// Function to recursively reverse from end node to start node
void recurse(Node* node, stack<Node*>& s, int startX, int startY) {
  // If there is a previous node
  if(node->prev) {
    // Push it to the stack
    s.push(node);
    // Try again with the previous previous node
    recurse(node->prev, s, startX, startY);
    // If there is no previous node
  } else {
    // Push the starting node to the stack
    Node *temp = new Node();
    temp->x = startX;
    temp->y = startY;
    s.push(temp);

    // Outputs to txt file
    freopen("output.txt","w",stdout);

    cout << "{";
    while(!s.empty()) {
      // Output the top of the stack
      cout << "{" << s.top()->x << "," << s.top()->y << "}" << (s.size() - 1 == 0 ? "" : ",");
      // Pop it off of the stack
      s.pop();
    }
    cout << "}";
    fclose(stdout);
    return;
  }
}

void dijMazeSolver(vector<vector<int>> maze, int startX, int startY) {
  // Node start info
  Node* source = new Node();
  source->x = startX;
  source->y = startY;
  source->dist = 0;
  
  // Priority queue based on minimum distances of the nodes
  priority_queue<Node*, vector<Node*>, Compare> q;
  // Unordered map for visited values
  unordered_map<pair<int,int>, Node*, hash_pair> m;
  // Valid directions
  vector<pair<int,int>> directions = {{1,0},{0,1},{-1,0},{0,-1}};

  // Push the starting node to the pq
  q.push(source);

  bool found = false;
  while(!found) {
    // Explore and pop the top node
    Node* node = q.top();
    q.pop();

    // Current node info
    int x = node->x;
    int y = node->y;
    int distance = node->dist;

    // Add to visited
    m[{x,y}] = node;
    
    // If the node is the goal
    if(maze[x][y] == 2) {
      // Exit out of this while loop
     found = true;
    }

    // Go through each direction
    for(int i = 0; i < directions.size(); i++) {
      // Neighboring node info
      int nx = x + directions[i].first;
      int ny = y + directions[i].second;
  
      // If not out of bounds, not a wall, or not visited
      if(nx >= 0 && ny >= 0 && nx < maze.size() && ny < maze[0].size() && maze[nx][ny] != 1 && m.find({nx,ny}) == m.end()) {
    // Create a new node
    Node* newNode = new Node();
    newNode->x = nx;
    newNode->y = ny;
    // Set distance to prev + 1
    newNode->dist = distance + 1;
    // Set prev to current node
    newNode->prev = node;

    // Push the neighboring node
    q.push(newNode);
    }
  }
}
  // Go through all nodes in the visited list
  for(auto it : m) {
    // Find the goal node
    if(maze[it.first.first][it.first.second] == 2) {
      // Create a stack as temp storage for reversing
      stack<Node*> s;
      // Recursively reverse until starting node
      recurse(it.second, s, startX, startY);
    }  
  }
}

int main() {
  // Maze input
  vector<vector<int>> maze = {
        {0,0,0,0,0,0,1,1,1,0},
        {0,1,0,1,0,1,0,1,0,0},
        {1,0,0,1,0,0,0,0,0,1},
        {0,0,1,1,0,1,1,0,1,0},
        {0,1,1,0,0,1,0,0,1,0},
        {1,0,0,0,1,0,1,0,1,0},
        {0,1,0,1,0,0,0,0,0,0},
        {0,0,0,0,1,0,1,1,0,1},
        {1,0,1,0,0,1,0,0,0,0},
        {0,2,0,1,0,0,1,0,1,0}
    };

  // Starting coords
  int startY = 0, startX = 0;

  dijMazeSolver(maze, startY, startX);

  // Program close
  return 0;
}