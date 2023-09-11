#include <iostream>
#include <vector>

class Aresta;
class Vertice;
class Face;

class Aresta{
    public:

    Vertice *Ini, *Fim;
    Face *Esq, *Dir;
    Aresta *EsqPre, *EsqSuc, *DirPre, *DirSuc;

    void setVertice(Vertice* Ini, Vertice* Fim){
        this->Ini = Ini;
        this->Fim = Fim;
    }

    void setFace(Face* Ini, Face* Fim){
        this->Esq = Ini;
        this->Dir = Fim;
    }

    void setAresta(Aresta* EsqPre, Aresta* EsqSuc, Aresta* DirPre, Aresta* DirSuc){
        this->EsqPre = EsqPre;
        this->EsqSuc = EsqSuc;
        this->DirPre = DirPre;
        this->DirSuc = DirSuc;
    }
};

class Vertice{
    public:

    std::vector<float> coords;
    Aresta *ArestaIncidente;
};

class Face{
    public:

    Aresta *ArestaFace;
};

int main(int argc, char** argv){
    FILE *obj;
    obj = fopen(argv[1], "rb");

    char Linha[20];
    char* Resultado;

    while(!feof(obj)){
        fgets(Linha, 100, obj);

        char Comando[2];

        Comando [0] = Linha[0];
        Comando [1] = Linha[1];
        std::cout << Comando << std::endl;
    }
 
    fclose(obj);

    return 0;
}