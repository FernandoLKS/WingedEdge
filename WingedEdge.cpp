#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cstdlib> 
#include "ClassesWingedEdge.h"

static std::vector<Vertex*> ListVertex;
static std::vector<Edge*> ListEdge;
static std::vector<Face*> ListFace;

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

        //Vertice comando
        if (Command == "v"){
            float x, y, z;
            LineStream >> x >> y >> z;      
            Vertex* V = new Vertex(GlobalVariables::VertexValue,x,y,z);     
            ListVertex.push_back(V);
        }       

        //Face comando      
        else if(Command == "f"){   
                  
            int vertex;
            char previousCharacter, Character;
            std::vector<int> FaceVertices;       

            LineStream.get(previousCharacter);            
        
            while (LineStream.get(Character)){
                //Lendo os vértices de uma face              
                if(Character != '/' and Character != ' '){
                    if(previousCharacter == ' '){                                       
                        vertex = Character - '0';
                        FaceVertices.push_back(vertex);
                    }                    
                }       
                previousCharacter = Character;
            }
            
            Face* F = new Face(GlobalVariables::FaceValue); 
            ListFace.push_back(F); 

            //Criando e adicionando arestas a lista     

            for(int i=0; i<FaceVertices.size(); i++){                
                Vertex *VertexA, *VertexB; 
                VertexA = ListVertex[FaceVertices[i]-1];

                if(i == FaceVertices.size() - 1)
                    VertexB = ListVertex[FaceVertices[0]-1];                   
                else
                    VertexB = ListVertex[FaceVertices[i+1]-1];  
                                              

                //Verificando se a aresta já foi criada         
                Edge *E = is_EdgeAlreadyCreated(VertexA, VertexB);

                if(E == nullptr){   
                    //Se não, cria uma nova aresta com sua vértice inicial e final
                    E = new Edge(GlobalVariables::EdgeValue);               
                    E->setVertex(VertexA, VertexB); 
                
                    //o vértice final terá esta aresta como um incidente
                    if(VertexB->getEdgeIncident() == nullptr) 
                        VertexB->setEdgeIncident(E);

                    //Se a aresta não existia antes, a face esquerda será a criada
                    if(E->getFaceLeft() == nullptr){
                        E->setFaceLeft(F);
                    }

                    ListEdge.push_back(E);
                }  
                else{
                    //Se a aresta já existir, a face direita será a criada
                    if(E->getFaceRight() == nullptr){
                        E->setFaceRight(F);
                    }
                }               
                
                //A face criada atribuirá a primeira aresta como aresta da face
                if(F->getEdgeFace() == nullptr)
                    F->setEdgeFace(E);                         
            }                 
        }              

        //Comando da normal do vértice (para a estrutura winged-edge, não há necessidade)
        else if(Command == "vn"){}
        //Comando de textura do vértice (para a estrutura winged-edge, não há necessidade)
        else if(Command == "vt"){}      

        else{
            continue;
        }

        //Definindo as bordas esquerda e direita, precessora e sucessora
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

void QueryTheFaces_Edge(int Id){
    if (Id > ListEdge.size()){
        std::cout << "Nenhuma aresta corresponde a esse ID";
        return;
    }    
    std::cout << "Faces que compartilham a aresta E" << Id << ':';
    std::cout << ' ' << 'F' << ListEdge[Id-1]->getFaceLeft()->getId() << ' ' << 'F' << ListEdge[Id-1]->getFaceRight()->getId();
}

void QueryTheEdges_Vertex(int Id){
    if (Id > ListVertex.size()){
        std::cout << "Nenhum vértice corresponde a esse ID";
        return;
    }
    std::cout << "Arestas que compartilham o vértice V" << Id << ':';
    for (int i=0; i<ListEdge.size(); i++){        
        if((ListEdge[i]->getVertexIni()->getId() == Id) or (ListEdge[i]->getVertexEnd()->getId() == Id)){
            std::cout << ' ' << 'E' << ListEdge[i]->getId();
        }
    }
}

void QueryTheVertice_Face(int Id){
    if (Id > ListFace.size()){
        std::cout << "Nenhuma face corresponde a esse ID";
        return;
    }
    std::vector<int> IdVerticesFace;
    bool is_alreadyIdintheVector = false;

    std::cout << "Vértices que compartilham a face F" << Id << ':';
    for (int i=0; i<ListEdge.size(); i++){
        if((ListEdge[i]->getFaceLeft()->getId() == Id) or (ListEdge[i]->getFaceRight()->getId() == Id)){
            for(int j=0; j<IdVerticesFace.size(); j++){
                if((ListEdge[i]->getVertexIni()->getId()) == IdVerticesFace[j])
                    is_alreadyIdintheVector = true;
            }
            if (is_alreadyIdintheVector == false){
                IdVerticesFace.push_back(ListEdge[i]->getVertexIni()->getId());
            }
            is_alreadyIdintheVector = false;

            for(int j=0; j<IdVerticesFace.size(); j++){
                if((ListEdge[i]->getVertexEnd()->getId()) == IdVerticesFace[j])
                    is_alreadyIdintheVector = true;
            }
            if (is_alreadyIdintheVector == false){
                IdVerticesFace.push_back(ListEdge[i]->getVertexEnd()->getId());
            }
            is_alreadyIdintheVector = false;
        }
    }

    for(int i=0; i<IdVerticesFace.size(); i++){
        std::cout << ' ' << 'V' << IdVerticesFace[i];
    }
}

int main(int argc, char** argv){    

    CreateWingedEdge(argv[1]);          

    int Input = -1, Id;    

    while(Input != 0){       

        std::cout << std::endl << "----------------------------------------------------------------" << std::endl;
        std::cout << "Seleciona uma operação:" << std::endl;
        std::cout << "0 - Sair" << std::endl;
        std::cout << "1 - Consultar as faces que compartilham um determinada aresta" << std::endl;
        std::cout << "2 - Consultar as arestas que compartilham um determinado vértice" << std::endl;
        std::cout << "3 - Consultar os vértices que compartilham uma determinada face" << std::endl;
        std::cout << "4 - Mostrar a estrutura completa Winged-Edge" << std::endl << std::endl;

        std::cin >> Input;        

        usleep(1000000);
        system("clear");
        
        switch(Input){
            case 0:
                break;
            case 1:
                std::cout << "Id da aresta: ";
                std::cin >> Id;
                QueryTheFaces_Edge(Id);
                break;
            case 2:
                std::cout << "Id do vértice: ";
                std::cin >> Id;
                QueryTheEdges_Vertex(Id);
                break;
            case 3:
                std::cout << "Id da face: ";
                std::cin >> Id;
                QueryTheVertice_Face(Id);
                break;
            case 4:
                ShowInformationsTotal(); 
                break;
            default:
                std::cout << "Comando inválido";
        }
        std::cout << std::endl;
    }

    return 0;
}