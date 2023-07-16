#include <iostream>
#include "DSM.h"
#include <assert.h>
#include <string>
using namespace std;

int main() {
    string elementNames[] = {"Haus", "Waschbecken", "Schlafzimmer", "Wohnzimmer", "Badezimmer", "Sofa", "Kuche", "fenster"};

    Dsm Haus(elementNames, 8);
    assert(Haus.size() == 8);
    cout<<"Test size geschafft!"<<endl;
    assert(Haus.getName(0) == "Haus");
    assert(Haus.getName(1) == "Waschbecken");
    assert(Haus.getName(2) == "Schlafzimmer");
    cout<< "Test getName geschafft"<< endl;

    Haus.setElementName(7, "Fenster");
    assert(Haus.getName(7)=="Fenster");
    cout<< "Test setElementName geschafft"<< endl;

    Haus.addLink("Haus", "Waschbecken", 2);
    Haus.addLink("Haus", "Schlafzimmer", 1);
    Haus.addLink("Haus", "Wohnzimmer", 1);
    Haus.addLink("Haus", "Badezimmer", 1);
    Haus.addLink("Haus", "Sofa", 2);
    Haus.addLink("Haus", "Kuche", 1);
    Haus.addLink("Haus", "Fenster", 5);

    Haus.addLink("Badezimmer", "Waschbecken", 1);
    Haus.addLink("Badezimmer", "Fenster", 1);

    Haus.addLink("Schlafzimmer", "Sofa", 1);
    Haus.addLink("Schlafzimmer", "Fenster", 2);

    Haus.addLink("Wohnzimmer", "Sofa", 1);
    Haus.addLink("Wohnzimmer", "Fenster", 1);

    Haus.addLink("Kuche", "Waschbecken", 1);
    Haus.addLink("Kuche", "Fenster", 1);

    Dsm Haus2(Haus);
    assert(Haus2.size()==Haus.size());
    assert(Haus.getName(2)==Haus2.getName(2));
    cout<<"Test Konstruktor geschafft!"<<endl;

    assert(Haus.linkWeight("Haus", "Waschbecken")==2);
    assert(Haus.linkWeight("Haus", "Schlafzimmer")==1);
    cout<< "Test linkWeight geschafft!"<<endl;

    assert(Haus.countFromLinks("Haus")==7);
    cout<< "Test countFromLinks geschafft"<< endl;

    assert(Haus.countToLinks("Haus")==0);
    cout << "Test countToLinks geschafft"<< endl;

    assert(Haus.countAllLinks()==15);
    cout<< "Test countAllLinks geschafft"<<endl;

    assert(Haus.hasLink("Haus", "Badezimmer")==true);
    assert(Haus.hasLink("Fenster", "Badezimmer")==false);
    Haus.addLink("Haus", "Keller", 1);
    Haus.addLink("Dachboden", "Fenster", 1);
    assert(Haus.hasLink("Haus", "Keller")==true);
    assert(Haus.hasLink("Dachboden", "Fenster")==true);
    Haus.deleteLink("Haus", "Keller");
    assert(Haus.hasLink("Haus", "Keller")==false);
    cout<< "Test hasLink geschafft!"<<endl;
    cout<<"Test deleteLink geschafft!"<<endl;

    return 0;
}
