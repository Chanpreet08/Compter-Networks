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
        gateTable.clear();
        gateTable[2]=-1;
        gateTable[3]=0;
        gateTable[4]=1;
        gateTable[5]=2;
        gateTable[6]=-1;
        costTable.clear();
        costTable[2]=0;
        costTable[3]=5;
        costTable[4]=2;
        costTable[5]=3;
        costTable[6]=-1;

    }
    else if (getId()==3)
    {
        gateTable.clear();
        gateTable[3]=-1;
        gateTable[2]=0;
        gateTable[4]=1;
        gateTable[5]=-1;
        gateTable[6]=2;
        costTable.clear();
        costTable[2]=5;
        costTable[3]=0;
        costTable[4]=4;
        costTable[5]=-1;
        costTable[6]=3;
    }
    else if (getId()==4)
    {
        gateTable.clear();
        gateTable[2]=0;
        gateTable[3]=1;
        gateTable[4]=0;
        gateTable[5]=-1;
        gateTable[6]=2;
        costTable.clear();
        costTable[2]=2;
        costTable[3]=4;
        costTable[4]=0;
        costTable[5]=-1;
        costTable[6]=4;
    }
    else if (getId()==5)
    {
        gateTable.clear();
        gateTable[5]=-1;
        gateTable[2]=0;
        gateTable[3]=-1;
        gateTable[4]=-1;
        gateTable[6]=-1;
        costTable.clear();
        costTable[2]=3;
        costTable[3]=-1;
        costTable[4]=-1;
        costTable[5]=0;
        costTable[6]=-1;
    }
    else if (getId()==6)
    {
        gateTable.clear();
        gateTable[6]=-1;
        gateTable[2]=-1;
        gateTable[3]=1;
        gateTable[4]=0;
        gateTable[5]=-1;
        costTable.clear();
        costTable[2]=-1;
        costTable[3]=3;
        costTable[4]=4;
        costTable[5]=-1;
        costTable[6]=0;
    }
    event = new cMessage("initial");
    scheduleAt(simTime()+0,event);

}

void Node::handleMessage(cMessage *msg)
{
    if(msg==event)
    {
        R_PDU * r = new R_PDU();
        r->setDistanceVector(costTable);
        r->setSource(getId());
        for(int i=2;i<=6;i++)
        {
            gate=gateTable[i];
            if(gate!=-1)
            send(r->dup(),"out",gate);
        }
        delete r;
    }
    else{
        R_PDU * r = check_and_cast<R_PDU*>(msg);
        newCostTable= r->getDistanceVector();
        source=r->getSource();
        change=0;
        for(std::map<int, int>::iterator it=newCostTable.begin(); it != newCostTable.end() ; it++)
        {
            if(it->second!=-1)
            {
                it->second=it->second+costTable[source];
                if(costTable[it->first]==-1 && it->second!=-1)
                {
                    costTable[it->first]=it->second;
                    gateTable[it->first]=gateTable[source];
                    change=1;
                }
                else if(costTable[it->first]>it->second)
                {
                    costTable[it->first]=it->second;
                    gateTable[it->first]=gateTable[source];
                    change=1;
                }
            }
        }
        if(change==1)
        {
            R_PDU * r = new R_PDU();
            r->setDistanceVector(costTable);
            r->setSource(getId());
            for(int i=2;i<=6;i++)
            {
               gate=gateTable[i];
               if(gate!=-1)
               send(r->dup(),"out",gate);
            }
            delete r;
        }
    }

}

void Node::finish() {

    for(int i=2; i<=6; i++) {

            EV << "Node ID: " << getId() << " To ID: " << i << " Total Distance: " << costTable[i] << "\n";

    }
}
