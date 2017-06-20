//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Alayer.h"

Define_Module(Alayer);

void Alayer::initialize()
{
    if(getId()==4)
    {
        A_PDU * a = new A_PDU();
        a->setId(1);
        a->setSource(2);
        a->setDestination(3);
        a->setType("Data");
        send(a,"toDl");
        counter++;
    }

}

void Alayer::handleMessage(cMessage *msg)
{
    A_PDU *a = (A_PDU*)msg;
    if(strcmp(a->getType(),"Data")==0)
    {
        A_PDU *a1 = new A_PDU();
        a1->setType("ACK");
        a1->setDestination(2);
        a1->setSource(3);
        a1->setId(a->getId());
        send(a1,"toDl");
    }
    else if(strcmp(a->getType(),"ACK")==0)
    {if(counter<10){
        A_PDU *a1 = new A_PDU();
        a1->setType("Data");
        a1->setDestination(3);
        a1->setSource(2);
        counter++;
        a1->setId(counter);
        send(a1,"toDl");
    }
    }
}
