#include "DSM.h"
#include <string>
#include <iostream>
#include <exception>
using namespace std;

Dsm::Dsm(int elementCount) {
    capacity = elementCount;
    this->elementCount = elementCount;
    this->elementNames = new string[elementCount]; //dynamisches Array
    this->adjazenzmatrix = new int*[elementCount]; //Liste von Zeigers

}

Dsm::Dsm(string* elementNames, int elementCount) {
    this->capacity=elementCount;
    this->elementNames = new string[elementCount]; //elementNames wird als dynamische Array initialisiert
    for(int i = 0; i<elementCount;i++){
        this->elementNames[i] = elementNames[i];
    }
    this->elementCount = elementCount;
    this->adjazenzmatrix = new int*[elementCount];
    //Die Matrix wird initialisiert. Fur jeden Pointer wird ein dynamischer Array von Typ int initialisiert
    for(int i=0; i<elementCount; i++){
        adjazenzmatrix[i] = new int[elementCount];
        for(int j=0; j<elementCount; j++){
            adjazenzmatrix[i][j] =0;
        }
    }

}

Dsm::Dsm(const Dsm &other){
    this->capacity=other.capacity;
    this->elementCount = other.elementCount;

    this->elementNames = new string[elementCount];
    for(int i = 0; i<elementCount;i++){
        this->elementNames[i] = other.elementNames[i];
    }
    this->adjazenzmatrix = new int*[elementCount]; //lista de pointere
    for(int i=0; i<elementCount; i++){
        adjazenzmatrix[i] = new int[elementCount];
        for(int j=0; j<elementCount; j++){
            this->adjazenzmatrix[i][j] = other.adjazenzmatrix[i][j];

        }
    }
}

Dsm::~Dsm() {
    for(int i=0; i<elementCount; i++){
        delete[] adjazenzmatrix[i];

    }
    delete[] adjazenzmatrix;
    delete[] elementNames;
}


int Dsm::size(){
    return elementCount;
}

string Dsm::getName(int index){
    if(index>0 or index< elementCount) {
        return elementNames[index];
    }
    else{
        throw logic_error("index out of range");
    }
}

void Dsm::setElementName(int index, string elementName){
    if(index>=0 and index<elementCount) {
        elementNames[index] = elementName;
    }
    else{
        throw logic_error("index out of range");
    }
}

void Dsm::resize(){
    if (capacity == elementCount) {
        capacity = capacity * 2;
        //resize vom Array
        string *newelements = new string[capacity]; //Speciher wird alloziert
        for (int i = 0; i < this->elementCount; i++) {
            newelements[i] = this->elementNames[i];
        }
        //alte Elemente loschen
        delete[] this->elementNames;
        this->elementNames = newelements;

        //Matrix verdoppeln
        int **newmatrix = new int *[capacity]; //Pointer, der auf ein Array von Typ Pointer zeigt
        for (int i = 0; i < this->elementCount; i++) {
            newmatrix[i] = this->adjazenzmatrix[i];
            //int *pointer = Ein Pointer vom Typ int
            //*pointer = die Adresse aus dem Pointer
        }
        delete[] this->adjazenzmatrix;
        this->adjazenzmatrix = newmatrix;

        //Kapazitat von Liste von Pointers verdoppeln:
        for (int i = 0; i < elementCount; i++) {
            int *newpointer = new int[capacity];
            for (int j = 0; j < elementCount; j++) {
                newpointer[j] = adjazenzmatrix[i][j];
            }
            delete[] adjazenzmatrix[i];
            this->adjazenzmatrix[i] = newpointer;
        }

    }
}

void Dsm::addLink(string fromElement,  string  toElement, int weight){
    bool gefunden = false;
    //sucht ob Element schon im elementNames ist
    for(int i=0; i<elementCount; i++){
        if(fromElement == elementNames[i]){
            gefunden = true;
        }
    }
    //falls nicht, wird es zur array hinzugefugt
    if(!gefunden){
        //wenn der array voll ist, muss die Kapazitat verdoppelt werden und die Elemente kopiert.
        resize();
        elementNames[elementCount] = fromElement;
        adjazenzmatrix[elementCount] = new int[capacity];
        for(int i=0; i<elementCount+1; i++){
            adjazenzmatrix[elementCount][i] =0;
        }
        elementCount++;
        for(int i=0; i<elementCount-1; i++){
            adjazenzmatrix[i][elementCount-1] =0;
        }
    }
    //dasselbe, aber fur toElement
    gefunden = false;
    for(int i=0; i<elementCount; i++){
        if(toElement == elementNames[i]){
            gefunden = true;
        }
    }
    if(!gefunden) {
        resize();
        elementNames[elementCount] = toElement;
        adjazenzmatrix[elementCount] = new int[capacity];
        for (int i = 0; i < elementCount + 1; i++) {
            adjazenzmatrix[elementCount][i] = 0;
        }
        elementCount++;
        for (int i = 0; i < elementCount - 1; i++) {
            adjazenzmatrix[i][elementCount - 1] = 0;
        }
    }
    //suche index fromElement
    int indexfromElement;
    for(int i=0; i<elementCount; i++){
        if(fromElement==elementNames[i]){
            indexfromElement=i;
        }
    }
    int indextoElement;
    for(int i=0; i<elementCount; i++){
        if(toElement==elementNames[i]){
            indextoElement=i;
        }
    }
    adjazenzmatrix[indexfromElement][indextoElement] = weight;

}
void Dsm::deleteLink(string fromElement, string toElement){
    int indexfromElement;
    for(int i=0; i<elementCount; i++){
        if(fromElement==elementNames[i]){
            indexfromElement=i;
        }
    }
    int indextoElement;
    for(int i=0; i<elementCount; i++){
        if(toElement==elementNames[i]){
            indextoElement=i;
        }
    }
    adjazenzmatrix[indexfromElement][indextoElement] = 0;


}
bool Dsm::hasLink(string fromElement, string toElement){
    int indexfromElement;
    for(int i=0; i<elementCount; i++){
        if(fromElement==elementNames[i]){
            indexfromElement=i;
        }
    }
    int indextoElement;
    for(int i=0; i<elementCount; i++){
        if(toElement==elementNames[i]){
            indextoElement=i;
        }
    }
    if(adjazenzmatrix[indexfromElement][indextoElement] == 0){
        return false;
    }
    else{
        return true;
    }
}

int Dsm::linkWeight(string fromElement, string toElement){
    int indexfromElement;
    for(int i=0; i<elementCount; i++){
        if(fromElement==elementNames[i]){
            indexfromElement=i;
        }
    }
    int indextoElement;
    for(int i=0; i<elementCount; i++){
        if(toElement==elementNames[i]){
            indextoElement=i;
        }
    }
    return adjazenzmatrix[indexfromElement][indextoElement];

}
int Dsm::countFromLinks(string elementName){
    int count=0;
    int indexelemname;
    for(int i=0; i<elementCount; i++){
        if(elementName==elementNames[i]){
            indexelemname=i;
        }
    }
    for(int i=0; i<elementCount; i++){
        if(adjazenzmatrix[indexelemname][i]!=0){
            count++;
        }
    }
    return count;
}

int Dsm::countToLinks(string elementName){
    int count=0;
    int indexelemname;
    for(int i=0; i<elementCount; i++){
        if(elementName==elementNames[i]){
            indexelemname=i;
        }
    }
    for(int i=0; i<elementCount; i++){
        if(adjazenzmatrix[i][indexelemname]!=0){
            count++;
        }
    }
    return count;
}
int Dsm::countAllLinks(){
    int count=0;
    for(int i=0; i<elementCount; i++){
        for(int j=0; j<elementCount; j++){
            if(adjazenzmatrix[i][j]!=0){
                count++;
            }
        }
    }
    return count;
}