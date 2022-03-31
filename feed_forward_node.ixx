#pragma once
export module feed_forward_node;
import base;


export class Feed_Forward_Node : public Base_Node {
protected:
	virtual double Transfer_Function(double val) { return val; }
public:
	//Feed_Forward_Node() = delete;
	Feed_Forward_Node(int v_size=1, int e_size=1) : Base_Node(v_size, e_size) {}
	virtual void Run(int mode = 0) override;
	virtual std::string Get_Name() override;
};

std::string Feed_Forward_Node::Get_Name() {
	static std::string name = "FEED_FORWARD_NODE";
	return name;
}

void Feed_Forward_Node::Run(int mode) {
	double total = 0.0;
	for (auto i : in_links) {
		total += i->Weighted_In_Value();
	}
	value[mode] = Transfer_Function(total);
}