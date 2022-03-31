#pragma once
export module bias_node;
import input_node;

export class Bias_Node :public Input_Node {
public:
	//Bias_Node() = delete;
	Bias_Node(double bias = 1.0) :Input_Node(1) { value[0] = bias; }
	virtual void Set_Value(double value, int id = 0) override { }
	virtual double Get_Value(int id = 0) const override { return value[0]; }
	virtual std::string Get_Name() override;
};

std::string Bias_Node::Get_Name() {
	static std::string name = "BIAS_NODE";
	return name;
}