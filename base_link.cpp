module base;
using namespace std;

void Base_Link::Save(ofstream& outfile) {
    outfile << id << endl;
    for (auto i : value) {
        outfile << " " << setprecision(18) << i;
    }
    outfile << endl;
}

void Base_Link::Load(ifstream& infile) {
    double temp;
    infile >> id;
    value.clear();
    while (infile.peek() != '\n') {
        infile >> temp;
        value.push_back(temp);
    }
}
