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
/*
 * Created by CC
 * */

#include "Alayer.h"

Define_Module(Alayer);

void Alayer::initialize()
{

    counter =0;
    msg_data=65;
    numSent=0;
    numReceived=0;
    if(getId()==4)
    {
        cMessage * self = new cMessage();
        scheduleAt(simTime()+0,self);
        /**/
    }
    WATCH(counter);
    WATCH(numSent);
    WATCH(numReceived);

}

void Alayer::handleMessage(cMessage *msg)
{
    A_PDU *a = (A_PDU*)msg;
    if(msg->isSelfMessage())
    {
        A_PDU * a = new A_PDU();
        char ch = (char)msg_data;
        a->setId(1);
        a->setSource(2);
        a->setDestination(3);
        a->setType("Data");
        a->setData(ch);
        send(a,"toDl");
        msg_data++;
        counter++;
        numSent++;
    }
    else if(strcmp(a->getType(),"Data")==0)
    {
        A_PDU *a1 = new A_PDU();
        a1->setType("ACK");
        a1->setDestination(2);
        a1->setSource(3);
        a1->setId(a->getId());
        send(a1,"toDl");
        numSent++;
    }
    else if(strcmp(a->getType(),"ACK")==0)
    {if(counter<26){
        A_PDU *a1 = new A_PDU();
        char ch = (char)msg_data;
        a1->setType("Data");
        a1->setDestination(3);
        a1->setSource(2);
        a1->setData(ch);
        counter++;
        msg_data++;
        a1->setId(counter);
        send(a1,"toDl");
    }
    }
}
