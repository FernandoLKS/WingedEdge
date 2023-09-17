#ifndef CLASSESWINGEDEDGE_H
#define CLASSESWINGEDEDGE_H

#include <iostream>
#include <vector>

class Edge;
class Vertex;
class Face;

class GlobalVariables {
public:
    static int EdgeValue;
    static int VertexValue;
    static int FaceValue;
};

class Edge {
private:
    int id;
    Vertex* Ini = nullptr;
    Vertex* End = nullptr;
    Face* Left = nullptr;
    Face* Right = nullptr;
    Edge* LeftPre = nullptr;
    Edge* LeftSuc = nullptr;
    Edge* RightPre = nullptr;
    Edge* RightSuc = nullptr;

public:
    Edge(int id);
    void setVertex(Vertex* Ini, Vertex* End);
    void setFaceLeft(Face* Left);
    void setFaceRight(Face* Right);
    void setLeftPre(Edge* LeftPre);
    void setLeftSuc(Edge* LeftSuc);
    void setRightPre(Edge* RightPre);
    void setRightSuc(Edge* RightSuc);

    Vertex* getVertexIni();
    Vertex* getVertexEnd();
    Face* getFaceLeft();
    Face* getFaceRight();
    Edge* getLeftPre();
    Edge* getLeftSuc();
    Edge* getRightPre();
    Edge* getRightSuc();
    int getId();
    void ShowInformations();
};

class Vertex {
private:
    int id;
    std::vector<float> Coord;
    Edge* EdgeIncident = nullptr;

public:
    Vertex(int id, float x, float y, float z);
    void setEdgeIncident(Edge* EdgeIncident);
    std::vector<float> getCoord();
    Edge* getEdgeIncident();
    int getId();
    void ShowInformations();
};

class Face {
private:
    int id;
    Edge* EdgeFace = nullptr;

public:
    Face(int id);
    void setEdgeFace(Edge* EdgeFace);
    Edge* getEdgeFace();
    int getId();
    void ShowInformations();
};

#endif // CLASSESWINGEDEDGE_H