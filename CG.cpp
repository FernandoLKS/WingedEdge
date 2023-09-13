#include <iostream>
#include <vector>

using namespace std;

class Edge;
class Vertex;
class Face;

class Edge{
    public:

    Vertex *Ini, *End;
    Face *Left, *Right;
    Edge *LeftPre, *LeftSuc, *RightPre, *RightSuc;

    void setVertex(Vertex* Ini, Vertex* End){
        this->Ini = Ini;
        this->End = End;
    }

    void setFace(Face* Ini, Face* End){
        this->Left = Ini;
        this->Right = End;
    }

    void setEdge(Edge* LeftPre, Edge* LeftSuc, Edge* RightPre, Edge* RightSuc){
        this->LeftPre = LeftPre;
        this->LeftSuc = LeftSuc;
        this->RightPre = RightPre;
        this->RightSuc = RightSuc;
    }
};

class Vertex{
    public:
    vector<float> coords;
    Edge *EdgeIncident;
};

class Face{
    public:

    Edge *EdgeFace;
};

int main(int argc, char** argv){
    FILE *ObjFile;
    ObjFile = fopen(argv[1], "rb");

    int AmountLines = 0;

    while(!feof(ObjFile)){
        cout << AmountLines << endl;
        AmountLines += 1;        
    }
 
    fclose(ObjFile);

    return 0;
}
