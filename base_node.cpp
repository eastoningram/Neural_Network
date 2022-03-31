module base;
using namespace std;

void Base_Node::Load(ifstream& infile) {
    double temp;
    infile >> id;
    value.clear();
    while (infile.peek() != '\n') {
        infile >> temp;
        value.push_back(temp);
    }

    error.clear();
    while (infile.peek() != '\n') {
        infile >> temp;
        error.push_back(temp);
    }
}

void Base_Node::Save(ofstream& outfile){
  outfile << setw(4) << id << endl;
    for (auto i : value) {
        outfile << " " << setprecision(18) << i;
    }
    outfile << endl;

    for (auto i : error) {
        outfile << " " << setprecision(18) << i;
    }
    outfile << endl;
}

void Base_Node::Create_Link_To(Base_Node& to_node, Base_Link* link){
    out_links.push_back(link);
    to_node.In_Links()->push_back(link);
    link->Set_In_Node(this, id);
    link->Set_Out_Node(&to_node, to_node.Get_ID());
}

void Base_Node::Print(ofstream& out){
    out << "Node ID: " << id << "   Node Name: " << Get_Name() << endl;
    out << "Value Set: ";
    for (auto i : value) {
        out << i << " ";
    }
    out << endl;

    out << "Error Set: ";
    for (auto i : error) {
        out << i << " ";
    }
    out << endl;

    for (auto i : in_links) {
        out << "   In Link ID : " << i->Get_ID()
            << "  Link Name: " << i->Get_Name()
            << "  Source Node: " << i->In_Node()->Get_ID()
            << "  Value Set: ";
        for (auto j : i->Get_Values()) {
            out << j << " ";
        }
        out << endl;
    }
    for (auto i : out_links) {
        out << "   Out Link ID: " << i->Get_ID()
            << "  Link Name: " << i->Get_Name()
            << "  Dest Node: " << i->Out_Node()->Get_ID()
            << "  Value Set: ";
        for (auto j : i->Get_Values())
            out << j << " ";
        out << endl;
    }
    out << endl;
}