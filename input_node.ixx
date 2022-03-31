#pragma once
export module input_node;
import base;

export class Input_Node :public Base_Node {
public:
	//Input_Node() = delete;
	Input_Node(int size = 1) : Base_Node(size,size) {}
	virtual std::string Get_Name() override;
};

std::string Input_Node::Get_Name() {
	static std::string name = "INPUT_NODE";
	return name;
}