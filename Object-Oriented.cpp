// Object-Oriented.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
import base;
import input_node;
import adaline_node;
import adaline_link;
import bias_node;
import pattern;
import <iostream>;
import <fstream>;
import <vector>;
import <iomanip>;

using namespace std;

vector<Pattern> Create_Data(const int set_num);
void Populate(const int set_num);

int main(){
	const int set_num = 250;
	//Populate(set_num);
	auto data = Create_Data(set_num);
	
	// Create ADALINE
	shared_ptr<Base_Node> Node[4];
	shared_ptr<Base_Link> Link[3];

	Node[0] = make_shared <Input_Node>();
	Node[1] = make_shared <Input_Node>();
	Node[2] = make_shared <Bias_Node>();
	Node[3] = make_shared <ADALINE_Node>(0.45);
	Link[0] = make_shared <ADALINE_Link>();
	Link[1] = make_shared <ADALINE_Link>();
	Link[2] = make_shared <ADALINE_Link>();

	Connect(Node[0], Node[3], Link[0]);
	Connect(Node[1], Node[3], Link[1]);
	Connect(Node[2], Node[3], Link[2]);

	// Train
	/*int iteration = 0;
	int good = 0;

	while (good < set_num) {
		good = 0;
		for (int i = 0; i < set_num; i++) {
			Node[0]->Set_Value(data[i].In(0));
			Node[1]->Set_Value(data[i].In(1));

			Node[3]->Run();

			if (data[i].Out(0) != Node[3]->Get_Value()) {
				Node[3]->Learn();
				break;
			}
			else {
				good++;
			}
		}
		cout << iteration << ". " << good << "/" << set_num << endl;
		iteration++;
	}

	// Save
	ofstream outfile("adaline.net");
	for (auto i : Node) {
		i->Save(outfile);
	}
	for (auto i : Link) {
		i->Save(outfile);
	}
	outfile.close(); */

	// Load
	ifstream infile("adaline.net");
	for (auto i : Node) {
		i->Load(infile);
	}
	for (auto i : Link) {
		i->Load(infile);
	}
	infile.close();

	// Run
	for (int i = 0; i < set_num; i++) {
		Node[0]->Set_Value(data[i].In(0));
		Node[1]->Set_Value(data[i].In(1));

		Node[3]->Run();

		cout << "Pattern: " << setw(3) << i << " Input: (";
		cout << data[i].In(0) << ",";
		cout << data[i].In(1) << ") ADALINE:";
		cout << setw(3) << Node[3]->Get_Value() << " Actual:";
		cout << setw(3) << data[i].Out(0) << endl;
	}
}

void Populate(const int set_num) {
	double x, y, y1, output;
	ofstream outfile("lin2var.trn");

	for (int i = 0; i < set_num; i++) {
		x = ((double)rand() / (double)RAND_MAX) * 2.0 - 1.0;
		y = ((double)rand() / (double)RAND_MAX) * 2.0 - 1.0;

		y1 = (-5 * x - 2) / -4;

		if (y < y1) {
			output = 1;
		}
		else {
			output = -1;
		}

		outfile << i << " " << x << " " << y << " " << " " << output << endl;
	}
	outfile.close();
}

vector<Pattern> Create_Data(const int set_num) {
	// Load Training set into Pattern
	vector<Pattern> data;
	ifstream infile("lin2var.trn");
	for (int i = 0; i < set_num; i++) {
		data.push_back(Pattern(2, 1, infile));
	}
	infile.close();
	return data;
}