/*
 * LaCAM algorithm
 */
#pragma once

#include "dist_table.hpp"
#include "graph.hpp"
#include "instance.hpp"
#include "utils.hpp"

// low-level search node
struct Constraint {
  std::vector<int> who;
  Vertices where;
  const int depth;
  static uint LNODE_CNT;  // count Low level 
  Constraint();
  Constraint(Constraint* parent, int i, Vertex* v);  // who and where
  ~Constraint();
};

// high-level search node

struct Node {
  const Config C;
  Node* parent;
  static uint HNODE_CNT;  // count high level 
  // for low-level search
  std::vector<float> priorities;
  std::vector<int> order;
  std::queue<Constraint*> search_tree;
  const std::string h;

  Node(Config _C, DistTable& D, const std::string& _h, Node* _parent = nullptr);
  ~Node();
};
using Nodes = std::vector<Node*>;

// PIBT agent
struct Agent {
  const int id;
  Vertex* v_now;   // current location
  Vertex* v_next;  // next location
  Agent(int _id) : id(_id), v_now(nullptr), v_next(nullptr) {}
};
using Agents = std::vector<Agent*>;

// next location candidates, for saving memory allocation
using Candidates = std::vector<std::array<Vertex*, 5> >;

struct Planner {
  const Instance* ins;
  const Deadline* deadline;
  std::mt19937* MT;
  const int verbose;

  // solver utils
  const int N;  // number of agents
  const int V_size;

  // newly added
  static std::vector<int> conflict;
  static std::vector<int> option;

  DistTable D;
  Candidates C_next;                // next location candidates
  std::vector<float> tie_breakers;  // random values, used in PIBT
  Agents A;
  Agents occupied_now;   // for quick collision checking
  Agents occupied_next;  // for quick collision checking

  Planner(const Instance* _ins, const Deadline* _deadline, std::mt19937* _MT,
          int _verbose = 0);
  Solution solve();
  bool get_new_config(Node* S, Constraint* M);
  bool funcPIBT(Agent* ai);
};

// main function
Solution solve(const Instance& ins, const int verbose = 0,
               const Deadline* deadline = nullptr, std::mt19937* MT = nullptr);
