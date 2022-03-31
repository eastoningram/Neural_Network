module base;
using namespace std;

void Connect(Base_Node& from_node, Base_Node& to_node, Base_Link* link) {
    from_node.Create_Link_To(to_node, link);
}

void Connect(Base_Node& from_node, Base_Node& to_node, Base_Link& link) {
    from_node.Create_Link_To(to_node, &link);
}

void Connect(shared_ptr<Base_Node> from_node, shared_ptr<Base_Node> to_node, shared_ptr<Base_Link> link) {

    from_node->Create_Link_To(*to_node, link.get()); 
}

int Disconnect(Base_Node* from_node, Base_Node* to_node) {
    //list<Base_Link*>* out_links = from_node->Out_Links();
    for (auto i : *from_node->Out_Links()) {
        if (i->Out_Node() == to_node) {
            from_node->Out_Links()->remove(i);
            i->Out_Node()->In_Links()->remove(i);
            return 1;
        }
    }
    return 0;
}
