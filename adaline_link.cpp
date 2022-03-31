module adaline_link;
using namespace std;

void ADALINE_Link::Save(ofstream& outfile) {
	outfile << setw(4) << id << " ";
	outfile << setprecision(18) << value[WEIGHT] << " ";
	outfile << setw(4) << In_Node()->Get_ID() << " " << setw(4) << Out_Node()->Get_ID() << endl;
}

void ADALINE_Link::Load(ifstream& infile) {
	infile >> id;
	infile >> value[WEIGHT];
	double dummy;
	infile >> dummy;
	infile >> dummy;
}

std::string ADALINE_Link::Get_Name() {
	static std::string name = "ADALINE_LINK";
	return name;
}
