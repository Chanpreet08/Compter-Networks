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

#include "Dlayer.h"

Define_Module(Dlayer);

void Dlayer::initialize()
{
    // TODO - Generated method body
}

void Dlayer::handleMessage(cMessage *msg)
{
    cPacket *pkt = new cPacket();
    pkt = check_and_cast<cPacket*>(msg);
    if(strcmp(msg->getArrivalGate()->getName(),"fromAl")==0){
        D_PDU *d = new D_PDU();
        d->encapsulate(pkt);
        d->setType("Data");
        send(d,"toPl");
    }
    else if(strcmp(msg->getArrivalGate()->getName(),"fromPl")==0)
    {
        D_PDU * d= new D_PDU();
        d = check_and_cast<D_PDU*>(pkt);
        if(strcmp(d->getType(),"Data")==0)
        {
            D_PDU * d1 = new D_PDU();
            d1->setId(d->getId());
            d1->setType("ACK");
            send(d1,"toPl");
            send(d->decapsulate(),"toAl");
        }
        if(strcmp(d->getType(),"ACK")==0)
        {
            delete msg;
        }

    }
}
