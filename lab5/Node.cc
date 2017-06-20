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

Define_Module(Node);

void Node::initialize()
{
    if(getId()==2)
    {
        table.clear();
        table[2]=-1;
        table[3]=0;
        table[4]=1;
        table[5]=2;
        table[6]=1;

    }
    else if (getId()==3)
    {
        table.clear();
        table[3]=-1;
        table[2]=0;
        table[4]=1;
        table[5]=0;
        table[6]=2;
    }
    else if (getId()==4)
    {
        table.clear();
        table[4]=-1;
        table[2]=0;
        table[3]=1;
        table[5]=0;
        table[6]=2;
    }
    else if (getId()==5)
    {
        table.clear();
        table[5]=-1;
        table[2]=0;
        table[3]=0;
        table[4]=0;
        table[6]=0;
    }
    else if (getId()==6)
    {
        table.clear();
        table[6]=-1;
        table[2]=0;
        table[3]=1;
        table[4]=0;
        table[5]=0;
    }
    counterEvent = new cMessage("counter");
    source= par("source");
    destination = par("destination");
    counter=par("counter");
    Packet *pkt = new Packet();
    pkt->setSource(source);
    pkt->setDestination(destination);
    gate = table[destination];
    EV<<gate<<endl;
    if(gate!=-1)
    {
       send(pkt,"out",gate);
       counter--;
       if(counter!=0)
       {
           scheduleAt(simTime()+0,counterEvent);
       }
    }

}

void Node::handleMessage(cMessage *msg)
{

    if(msg==counterEvent)
    {
        Packet *pkt = new Packet();
        pkt->setSource(source);
        pkt->setDestination(destination);
        gate = table[destination];
        if(gate!=-1)
        {
            if(uniform(0,2)<0.3)
            {
                delete pkt;
                EV<<"Losing Packet";
            }
            else{
                send(pkt,"out",gate);
                counter--;
                if(counter!=0)
                {
                    scheduleAt(simTime()+0,counterEvent);
                }
            }

        }
    }
    else{
        Packet * pkt = check_and_cast<Packet *>(msg);
        destination=pkt->getDestination();
        gate = table[destination];
        if(gate!=-1)
        {
            send(msg,"out",gate);
        }
    }

}
