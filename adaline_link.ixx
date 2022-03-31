#pragma once
export module adaline_link;
import base;
import random;

import <iomanip>;
import <fstream>;


export class ADALINE_Link : public Base_Link {
public:
	//ADALINE_Link() = default;
	ADALINE_Link(int v_size=1) : Base_Link(v_size) { value[WEIGHT] = Random(-1.0, 1.0); }
	virtual void Save(std::ofstream& outfile) override;
	virtual void Load(std::ifstream& infile) override;
	virtual std::string Get_Name() override;
};
