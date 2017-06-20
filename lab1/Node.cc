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

#include "Node.h"
#include<string.h>
Define_Module(Node);

void Node::initialize()
{

    if(getId()==2)
    {
    counter++;
    Pkt *p = new Pkt();
    p->setType("Data");
    p->setPkt_id(1);
    p->setSource(2);
    p->setDestination(3);
    send(p,"out");
    }

}

void Node::handleMessage(cMessage *msg)
{
    Pkt * p = (Pkt*) msg;
    if(strcmp(p->getType(),"Data")==0)
    {
        Pkt *pac = new Pkt();
        pac->setPkt_id(p->getPkt_id());
        pac->setType("Ack");
        pac->setSource(3);
        pac->setDestination(2);
        send(pac,"out");
    }
    if(strcmp(p->getType(),"Ack")==0)
    {
        if(counter<10){
        counter++;
        Pkt *pac = new Pkt();
        pac->setPkt_id(p->getPkt_id()+1);
        pac->setType("Data");
        pac->setSource(2);
        pac->setDestination(3);
        send(pac,"out");
        }
    }
}
