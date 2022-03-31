#pragma once
export module adaline_node;
import feed_forward_node;


export class ADALINE_Node :public Feed_Forward_Node {
protected:
	virtual double Transfer_Function(double value) override;
public:
	ADALINE_Node() :Feed_Forward_Node(2,1) {}
	ADALINE_Node(double lr) :Feed_Forward_Node(2, 1) { value[LEARNING_RATE] = lr; }
	virtual void Learn(int mode) override;
	virtual std::string Get_Name() override;
};


std::string ADALINE_Node::Get_Name() {
	static std::string name = "ADALINE_NODE";
	return name;
}

double ADALINE_Node::Transfer_Function(double value) {
	if (value < 0) {
		return -1.0;
	}
	else {
		return 1.0;
	}
}

void ADALINE_Node::Learn(int mode) {
	// Error = Desired_Output - ADALINE_Output
	error[NODE_ERROR] = value[NODE_VALUE] *-2.0;
	double delta; 
	for (auto i : in_links) {
		// New_Weight = Weight +Learning_Rate * Error * Input_Value
		delta = value[LEARNING_RATE] * i->In_Value() * error[NODE_ERROR];
		i->Update_Weight(delta);
	}
}