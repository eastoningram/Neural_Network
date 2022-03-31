#pragma once
export module base;
//--------------------------------------------------------------------------

import <iostream>;
import <iomanip>;
import <fstream>;
import <vector>;
import <list>;
import <string>;

using std::ofstream;
using std::ifstream;

export extern const int NODE_VALUE = 0;
export extern const int LEARNING_RATE = 1;
export extern const int NODE_ERROR = 0;
export extern const int WEIGHT = 0;

class Base_Node;  // Forward declaration so links can use the base node type
export class Base_Link   // Base Neural-Network Link class
{
private:

  inline static int ticket = -1; 
  // This static variable is shared by all links derived from the base link class. 
  // Its purpose is to give each link created from the base_link class a unique identification number.

protected:
  int id;                          // ID number for link
  std::vector<double> value;       // Value(s) for Link
  Base_Node* in_node;              // Node instance link is comming from
  Base_Node* out_node;             // Node instance link is going to

public:
    // Base_Link() = delete;
    Base_Link(int v_size = 1) { value.resize(v_size, 0.0); id = ++ticket; }      // Constructor
  virtual void Save(ofstream& outfile);
  virtual void Load(ifstream& infile);
  inline virtual void Epoch(int mode = 0) {}
  inline virtual std::vector<double> Get_Values() { return value; }
  inline virtual double Get_Value(int id = WEIGHT){ return value[id]; }
  inline virtual void Set_Value(double new_val, int id = WEIGHT){ value[id] = new_val; }
  inline virtual void Set_In_Node(Base_Node* node, int id){ in_node = node; }
  inline virtual void Set_Out_Node(Base_Node* node, int id){ out_node = node; }
  inline virtual Base_Node* In_Node(){ return in_node; }
  inline virtual Base_Node* Out_Node() { return out_node; }
  inline virtual std::string Get_Name();
  inline int Get_ID(){ return id; }
  inline virtual double In_Value(int mode = NODE_VALUE);
  inline virtual double Out_Value(int mode = NODE_VALUE);
  inline virtual double In_Error(int mode = NODE_ERROR);
  inline virtual double Out_Error(int mode = NODE_ERROR);

  inline virtual void Update_Weight(double new_val) { value[WEIGHT] += new_val; }
  inline virtual double Weighted_In_Value(int mode = NODE_VALUE);
  inline virtual double Weighted_Out_Value(int mode = NODE_VALUE);
  inline virtual double Weighted_In_Error(int mode = NODE_VALUE);
  inline virtual double Weighted_Out_Error(int mode = NODE_VALUE);
};

export class Base_Node            // Base Neural-Network Node
{
private:
  inline static int ticket = -1;

protected:
  int id;             // Identification Number
  std::vector<double> value;      // Value(s) stored by this node
  std::vector<double> error;      // Error value(s) stored by this node

  std::list<Base_Link*> in_links;     // List for input links
  std::list<Base_Link*> out_links;    // List for output links

public:
    //Base_Node() = delete;
    Base_Node(int v_size=1, int e_size=1) {
        id = ++ticket; value.resize(v_size, 0.0); error.resize(e_size, 0.0);
    }

  std::list<Base_Link*>* In_Links(){ return &in_links; }
  std::list<Base_Link*>* Out_Links(){ return &out_links; }

  virtual void Run(int mode = 0){}
  virtual void Learn(int mode = 0){}
  virtual void Epoch(int code = 0){}
  virtual void Load(ifstream& infile);
  virtual void Save(ofstream& outfile);

  inline virtual double Get_Value(int id = NODE_VALUE) const { return value[id]; }
  inline virtual void Set_Value(double new_val, int id = NODE_VALUE) { value[id] = new_val; }
  inline virtual double Get_Error(int id = NODE_ERROR) const { return error[id]; }
  inline virtual void Set_Error(double new_val, int id = NODE_ERROR) { error[id] = new_val; }

  inline int Get_ID() const { return id; }
  inline virtual std::string Get_Name();
  virtual void Print(ofstream& out);

  // Link and Base Interactions
  void Create_Link_To(Base_Node& to_node, Base_Link* link);

  friend void Connect(Base_Node& from_node, Base_Node& to_node, Base_Link* link);
  friend void Connect(Base_Node& from_node, Base_Node& to_node, Base_Link& link);
  friend void Connect(std::shared_ptr<Base_Node> from_node, std::shared_ptr<Base_Node> to_node, std::shared_ptr<Base_Link> link);
  
  friend int Disconnect(Base_Node* from_node, Base_Node* to_node);
};

// Inline Functions that reference objects outside their scope should be defined:
// - outside that class
// - inside the same file

double Base_Link::In_Value(int mode) {
    return in_node->Get_Value(mode);
}

double Base_Link::Out_Value(int mode) {
    return out_node->Get_Value(mode);
}

double Base_Link::In_Error(int mode) {
    return in_node->Get_Error(mode);
}

double Base_Link::Out_Error(int mode) {
    return out_node->Get_Error(mode);
}

std::string Base_Node::Get_Name() {
    static std::string name = "BASE_NODE";
    return name;
}

std::string Base_Link::Get_Name() {
    static std::string name = "BASE_LINK";
    return name;
}

double Base_Link::Weighted_In_Value(int mode)
{
    return in_node->Get_Value(mode) * value[WEIGHT];
}

double Base_Link::Weighted_Out_Value(int mode)
{
    return out_node->Get_Value(mode) * value[WEIGHT];
}

double Base_Link::Weighted_Out_Error(int mode)
{
    return out_node->Get_Error(mode) * value[WEIGHT];
}

double Base_Link::Weighted_In_Error(int mode)
{
    return in_node->Get_Error(mode) * value[WEIGHT];
}
