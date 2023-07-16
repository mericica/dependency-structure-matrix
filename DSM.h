

#pragma once
using namespace std;
#include <string>


class Dsm{
private:
    int elementCount;
    string* elementNames;
    int** adjazenzmatrix;
    int capacity;


public:

    Dsm(int elementCount);

    Dsm(string* elementNames, int elementCount);

    virtual ~Dsm();

    Dsm(const Dsm &other);

    int size();

    string getName(int index);

    void setElementName(int index, string elementName);

    void addLink(string fromElement,  string  toElement, int weight);

    void deleteLink(string fromElement, string toElement);

    bool hasLink(string fromElement, string toElement);

    int linkWeight(string fromElement, string toElement);

    int countToLinks(string elementName);

    int countFromLinks(string elementName);

    int countAllLinks();

    void resize();

    void findElement(string fromElement, string toElement);



};
