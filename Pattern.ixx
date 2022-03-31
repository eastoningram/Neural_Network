#pragma once
export module pattern;

import <fstream>;
import <iostream>;
import <vector>;

using std::cout;

export class Pattern{
private:
    std::vector <double> in_set;          // Pointer to input pattern array
    std::vector <double> out_set;         // Pointer to output pattern array
    int id;                  // Pattern Identification Number

public:
    Pattern() = default;
    Pattern(int data_id, std::vector <double> in_array, std::vector <double> out_array);
    Pattern(int in_size, int out_size, std::ifstream& infile);

    inline int In_Size() const { return in_set.size(); }
    inline int Out_Size() const { return out_set.size(); }


    virtual inline double In(int id) const { return in_set[id]; }
    virtual inline double Out(int id) const { return out_set[id]; }

    virtual inline void Set_In(int id, double value){ in_set[id] = value; }
    virtual inline void Set_Out(int id, double value){ out_set[id] = value; }

    virtual void Save(std::ofstream& outfile);
    virtual void Load(int in_size, int out_size, std::ifstream& infile);

    virtual void Print(void);
    virtual inline int Get_ID(void) const { return id; }

    virtual void Copy(Pattern& in);
};


Pattern::Pattern(int data_id, std::vector <double> in_array, std::vector <double> out_array){
    id = data_id;
    for (auto i : in_array) {
        in_set.push_back(i);
    }

    for (auto i : out_array)
        out_set.push_back(i);
}

Pattern::Pattern(int in_size, int out_size, std::ifstream& infile){
    infile >> id;
    Load(in_size, out_size, infile);
}

// Function to save pattern to disk

void Pattern::Save(std::ofstream& outfile){
    outfile << id << "\t";
    for (auto i : in_set) {
        outfile << i << "\t";
    }
        

    for (int i = 0; i < out_set.size(); i++) {
        outfile << out_set[i];
        if (i != out_set.size() - 1) {
            outfile << '\t';
        }
    }

    outfile << std::endl;
}
//---------------------------------------------------------------------------
// Function to Load a pattern from disk

void Pattern::Load(int in_size, int out_size, std::ifstream& infile){
    double temp;
    for (int i = 0; i < in_size; i++) {
        infile >> temp;
        in_set.push_back(temp);
    }

    for (int i = 0; i < out_size; i++) {
        infile >> temp;
        out_set.push_back(temp);
    }

    char ch;
    ch = infile.peek();
    while (ch == '\n' or ch == EOF)
    {
        ch = infile.get();
        if (ch == EOF) break;
        ch = infile.peek();
    }
}
//---------------------------------------------------------------------------
// Function to print pattern

void Pattern::Print()
{
    cout << "ID: " << id << "   In: ";
    for (auto i : in_set) {
        cout << i << " ";
    }
        
    cout << "   Out: ";
    for (auto i : out_set) {
        cout << i << " ";
    }
    cout << std::endl;
}
//---------------------------------------------------------------------------
// Function to copy pattern

void Pattern::Copy(Pattern& orig)
{
    int i;

    if (orig.In_Size() == in_set.size())
        for (i = 0; i < in_set.size(); i++)
            in_set[i] = orig.In(i);

    if (orig.Out_Size() == out_set.size())
        for (i = 0; i < out_set.size(); i++)
            out_set[i] = orig.Out(i);
}
