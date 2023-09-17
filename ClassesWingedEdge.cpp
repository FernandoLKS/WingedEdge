#include <iostream>
#include <vector>
#include "ClassesWingedEdge.h"

int GlobalVariables::EdgeValue = 1;
int GlobalVariables::VertexValue = 1;
int GlobalVariables::FaceValue = 1;

// Implementação da classe Aresta

Edge::Edge(int id){
    this->id = id;
    GlobalVariables::EdgeValue++;
}

void Edge::setVertex(Vertex* Ini, Vertex* End){
    this->Ini = Ini;
    this->End = End;
}

void Edge::setFaceLeft(Face* Left){
    this->Left = Left;
}

void Edge::setFaceRight(Face* Right){
    this->Right = Right;
}

void Edge::setLeftPre(Edge* LeftPre){
    this->LeftPre = LeftPre;
}

void Edge::setLeftSuc(Edge* LeftSuc){
    this->LeftSuc = LeftSuc;
}

void Edge::setRightPre(Edge* RightPre){
    this->RightPre = RightPre;
}

void Edge::setRightSuc(Edge* RightSuc){
    this->RightSuc = RightSuc;
}

Vertex* Edge::getVertexIni(){
    return this->Ini;
}

Vertex* Edge::getVertexEnd(){
    return this->End;
}

Face* Edge::getFaceLeft(){
    return this->Left;
}

Face* Edge::getFaceRight(){
    return this->Right;
}

Edge* Edge::getLeftPre(){
    return this->LeftPre;
}

Edge* Edge::getLeftSuc(){
    return this->LeftSuc;
}

Edge* Edge::getRightPre(){
    return this->RightPre;
}

Edge* Edge::getRightSuc(){
    return this->RightSuc;
}

int Edge::getId(){
    return this->id;
}

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

// Implementação da classe Vértice

Vertex::Vertex(int id, float x, float y, float z) : Coord(3){
    this->id = id;
    this->Coord[0] = x;
    this->Coord[1] = y;
    this->Coord[2] = z;
    GlobalVariables::VertexValue++;
}

void Vertex::setEdgeIncident(Edge* EdgeIncident){
    this->EdgeIncident = EdgeIncident;
}

std::vector<float> Vertex::getCoord(){
    return this->Coord;
}

Edge* Vertex::getEdgeIncident(){
    return this->EdgeIncident;
}

int Vertex::getId(){
    return this->id;
}

void Vertex::ShowInformations() {
    std::cout << "V" << this->id << " / ";
    if (this->EdgeIncident != nullptr) {
        std::cout << "E" << this->EdgeIncident->getId() << std::endl;
    } else {
        std::cout << "E-N/A" << std::endl;
    }
}

//Implementação da classe Face

Face::Face(int id){
    this->id = id;
    GlobalVariables::FaceValue++;
}

void Face::setEdgeFace(Edge* EdgeFace){
    this->EdgeFace = EdgeFace;
}

Edge* Face::getEdgeFace(){
    return this->EdgeFace;
}

int Face::getId(){
    return this->id;
}

void Face::ShowInformations() {
    std::cout << "F" << this->id << " / ";
    if (this->EdgeFace != nullptr) {
        std::cout << "E" << this->EdgeFace->getId() << std::endl;
    } else {
        std::cout << "E-N/A" << std::endl;
    }
}