#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

class Edge;
class Vertex;
class Face;

std::vector<Vertex*> ListVertex;
std::vector<Edge*> ListEdge;
std::vector<Face*> ListFace;

int EdgeValue = 1, VertexValue = 1, FaceValue = 1;

class Edge{
private:
    int id;
    Vertex *Ini = nullptr, *End = nullptr;
    Face *Left = nullptr;
    Face *Right = nullptr;
    Edge *LeftPre = nullptr, *LeftSuc = nullptr, *RightPre = nullptr, *RightSuc = nullptr;

public:
    Edge(int id){
        this->id = id;
        EdgeValue++;
    }

    void setVertex(Vertex* Ini, Vertex* End){
        this->Ini = Ini;
        this->End = End;
    }

    void setFaceLeft(Face* Left){
        this->Left = Left;
    }

    void setFaceRight(Face* Right){
        this->Right = Right;
    }

    void setLeftPre(Edge* LeftPre){
        this->LeftPre = LeftPre;
    }
    void setLeftSuc(Edge* LeftSuc){
        this->LeftSuc = LeftSuc;
    }
    void setRightPre(Edge* RightPre){
        this->RightPre = RightPre;
    }
    void setRightSuc(Edge* RightSuc){
        this->RightSuc = RightSuc;
    }

    Vertex* getVertexIni(){
        return this->Ini;
    }

    Vertex* getVertexEnd(){
        return this->End;
    }

    Face* getFaceLeft(){
        return this->Left;
    }

    Face* getFaceRight(){
        return this->Right;
    }

    Edge* getLeftPre(){
        return this->LeftPre;
    }

    Edge* getLeftSuc(){
        return this->LeftSuc;
    }

    Edge* getRightPre(){
        return this->RightPre;
    }

    Edge* getRightSuc(){
        return this->RightSuc;
    }

    int getId(){
        return this->id;
    }

    void ShowInformations();
};

class Vertex{
    private:
    int id;
    std::vector<float> Coord;
    Edge *EdgeIncident = nullptr;

    public:    
    Vertex(int id, float x, float y, float z) : Coord(3){
        this->id = id;
        this->Coord[0] = x;
        this->Coord[1] = y;
        this->Coord[2] = z;
        VertexValue++;
    }

    void setEdgeIncident(Edge* EdgeIncident){
        this->EdgeIncident = EdgeIncident;
    }

    std::vector<float> getCoord(){
        return this->Coord;
    }

    Edge* getEdgeIncident(){
        return this->EdgeIncident;
    }

    int getId(){
        return this->id;
    }

    void ShowInformations();
};

class Face{
    private:
    int id;
    Edge* EdgeFace = nullptr;    

    public:
    Face(int id){
        this->id = id;
        FaceValue++;
    }

    void setEdgeFace(Edge* EdgeFace){
        this->EdgeFace = EdgeFace;
    }

    Edge* getEdgeFace(){
        return this->EdgeFace;
    }

    int getId(){
        return this->id;
    }

    void ShowInformations();
};

void Edge::ShowInformations() {
    std::cout << "E" << this->id << " / ";

    if (this->Ini != nullptr) {
        std::cout << "V" << this->Ini->getId() << " / ";
    } else {
        std::cout << "V-N/A" <<  " / ";
    }

    if (this->End != nullptr) {
        std::cout << "V" << this->End->getId() << " / ";
    } else {
        std::cout << "V-N/A" <<  " / ";
    }

    if (this->Left != nullptr) {
        std::cout << "F" << this->Left->getId() << " / ";
    } else {
        std::cout << "F-N/A" <<  " / ";
    }

    if (this->Right != nullptr) {
        std::cout << "F" << this->Right->getId() << " / ";
    } else {
        std::cout << "F-N/A" <<  " / ";
    }

    if (this->LeftPre != nullptr) {
        std::cout << "E" << this->LeftPre->getId() << " / ";
    } else {
        std::cout << "E-N/A" <<  " / ";
    }

    if (this->LeftSuc != nullptr) {
        std::cout << "E" << this->LeftSuc->getId() << " / ";
    } else {
        std::cout << "E-N/A" <<  " / ";
    }

    if (this->RightPre != nullptr) {
        std::cout << "E" << this->RightPre->getId() << " / ";
    } else {
        std::cout << "E-N/A" <<  " / ";
    }

    if (this->RightSuc != nullptr) {
        std::cout << "E" << this->RightSuc->getId();
    } else {
        std::cout << "E-N/A";
    }

    std::cout << std::endl;
}
void Vertex::ShowInformations() {
    std::cout << "V" << this->id << " / ";
    if (this->EdgeIncident != nullptr) {
        std::cout << "E" << this->EdgeIncident->getId() << std::endl;
    } else {
        std::cout << "E-N/A" << std::endl;
    }
}

void Face::ShowInformations() {
    std::cout << "F" << this->id << " / ";
    if (this->EdgeFace != nullptr) {
        std::cout << "E" << this->EdgeFace->getId() << std::endl;
    } else {
        std::cout << "E-N/A" << std::endl;
    }
}

void ShowInformationsTotal(){
    std::cout << std::endl << "Edge Table" << std::endl;
        std::cout << "--------------------------------------------------------------------------" << std::endl;
    std::cout << "V.Ini / V.End / F.Left / F.Right / E.L.Pre / E.L.Suc / E.D.Pre / E.D.Suc" << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl;
    for(int i=0; i<ListEdge.size(); i++){        
        ListEdge[i]->ShowInformations();
    }

    std::cout << std::endl << "Vertex Table" << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << "Vertex / Edge" << std::endl;
    std::cout << "---------------" << std::endl;
    for(int i=0; i<ListVertex.size(); i++){
        ListVertex[i]->ShowInformations();
    }

    std::cout << std::endl << "Face Table" << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << "Face / Edge" << std::endl;
    std::cout << "---------------" << std::endl;
    for(int i=0; i<ListFace.size(); i++){
        ListFace[i]->ShowInformations();
    }
    std::cout << std::endl;
}

Edge* is_EdgeAlreadyCreated(Vertex *A, Vertex*B){
    for(int i=0; i<ListEdge.size(); i++){
        Edge *EdgeVerify = ListEdge[i];
        Vertex* Ini = EdgeVerify->getVertexIni();
        Vertex* End = EdgeVerify->getVertexEnd();
        
        if((Ini == A and End == B) or (Ini == B and End == A)) 
            return EdgeVerify;        
    }
    return nullptr;
}

void CreateWingedEdge(char* file){
    std::ifstream File(file);    

    if(!File.is_open()){
        std::cerr << "Error opening the file" << std::endl;
        exit(1);
    }

    std::string Line;

    while(std::getline(File, Line)){       
        std::istringstream LineStream(Line);

        std::string Command;
        LineStream >> Command;        

        //Vertex command
        if (Command == "v"){
            float x, y, z;
            LineStream >> x >> y >> z;      
            Vertex* V = new Vertex(VertexValue,x,y,z);     
            ListVertex.push_back(V);
        }       

        //Face command        
        else if(Command == "f"){   
                  
            int vertex;
            char previousCharacter, Character;
            std::vector<int> FaceVertices;       

            LineStream.get(previousCharacter);            
        
            while (LineStream.get(Character)){
                //Reading the vertices of the edges              
                if(Character != '/' and Character != ' '){
                    if(previousCharacter == ' '){                                       
                        vertex = Character - '0';
                        FaceVertices.push_back(vertex);
                    }                    
                }       
                previousCharacter = Character;
            }
            
            Face* F = new Face(FaceValue); 
            ListFace.push_back(F); 

            //Creating and adding edges to the list       

            for(int i=0; i<FaceVertices.size(); i++){                
                Vertex *VertexA, *VertexB; 
                VertexA = ListVertex[FaceVertices[i]-1];

                if(i == FaceVertices.size() - 1)
                    VertexB = ListVertex[FaceVertices[0]-1];                   
                else
                    VertexB = ListVertex[FaceVertices[i+1]-1];  
                                              

                //Check if the edge has already been created             
                Edge *E = is_EdgeAlreadyCreated(VertexA, VertexB);

                if(E == nullptr){   
                    //If not, create the object and determine the vertices     
                    E = new Edge(EdgeValue);               
                    E->setVertex(VertexA, VertexB); 
                
                    //the final vertex will have this edge as an incident
                    if(VertexB->getEdgeIncident() == nullptr) 
                        VertexB->setEdgeIncident(E);

                    //If the edge did not exist before, the left face will be the one created
                    if(E->getFaceLeft() == nullptr){
                        E->setFaceLeft(F);
                    }

                    ListEdge.push_back(E);
                }  
                else{
                    //If the edge already exists, the right face will be the one created
                    if(E->getFaceRight() == nullptr){
                        E->setFaceRight(F);
                    }
                }               
                
                //The created face will assign the first edge as its face edge
                if(F->getEdgeFace() == nullptr)
                    F->setEdgeFace(E);                         
            }                 
        }              

        //Vertex normal command (for the winged edge structure, there is no need)
        else if(Command == "vn"){}
        //Vertex texture command (for the winged edge structure, there is no need)
        else if(Command == "vt"){}      

        else{
            continue;
        }

        //Defining the left and right edges, preceding and succeeding
        for (int i = 0; i < ListEdge.size(); i++) {
            for (int j = 0; j < ListEdge.size(); j++) {
                if (j != i) {
                    if (ListEdge[j]->getVertexEnd() == ListEdge[i]->getVertexEnd()) {
                        ListEdge[i]->setLeftPre(ListEdge[j]);
                        break;
                    }
                }
            }

            for (int j = 0; j < ListEdge.size(); j++) {
                if (j != i) {
                    if (ListEdge[j]->getVertexIni() == ListEdge[i]->getVertexIni()) {
                        ListEdge[i]->setLeftSuc(ListEdge[j]);
                        break;
                    }
                }
            }

            for (int j = ListEdge.size() - 1; j >= 0; j--) {
                if (j != i) {
                    if (ListEdge[j]->getVertexEnd() == ListEdge[i]->getVertexIni()) {
                        ListEdge[i]->setRightPre(ListEdge[j]);
                        break;
                    }
                }
            }

            for (int j = ListEdge.size() - 1; j >= 0; j--) {
                if (j != i) {
                    if (ListEdge[j]->getVertexIni() == ListEdge[i]->getVertexEnd()) {
                        ListEdge[i]->setRightSuc(ListEdge[j]);
                        break;
                    }
                }
            }
        }
    }    

    File.close();
}

int main(int argc, char** argv){    

    CreateWingedEdge(argv[1]);
    ShowInformationsTotal();   

    return 0;
}