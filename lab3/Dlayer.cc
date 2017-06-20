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

#include "Dlayer.h"

Define_Module(Dlayer);

void Dlayer::initialize()
{
    numSent=0;
    numReceived=0;
    timeOutEvent = new cMessage();
    senderDelay = new cMessage("Delay");
    receiverDelay = new cMessage("Delay");
    buf = new D_PDU();
    copy = new D_PDU();
    timeOut=1;
    WATCH(numSent);
    WATCH(numReceived);
}

void Dlayer::handleMessage(cMessage *msg)
{
    if(msg==timeOutEvent)
    {
        D_PDU *d = new D_PDU();
        d = buf->dup();
        send(d,"toPl");
        numSent++;
        scheduleAt(simTime()+timeOut,timeOutEvent);
    }
    else if(msg == senderDelay)
    {
        D_PDU * d= new D_PDU();
        d= buf->dup();
        send(d,"toPl");
        numSent++;
        scheduleAt(simTime()+timeOut,timeOutEvent);
    }
    else if (msg ==receiverDelay)
    {
        D_PDU * d= new D_PDU();
        D_PDU * d1 = new D_PDU();
        d1= buf->dup();
        d = copy->dup();
        numSent++;
        send(d1,"toPl");
        send(d->decapsulate(),"toAl");
    }
    else
    {
        cancelEvent(timeOutEvent);
        numReceived++;
        cPacket *pkt = new cPacket();
        pkt = check_and_cast<cPacket*>(msg);
        if(strcmp(msg->getArrivalGate()->getName(),"fromAl")==0){
            D_PDU *d = new D_PDU();
            d->encapsulate(pkt);
            d->setType("Data");
            buf =d;
            if(uniform(0,1)<0.3)
                scheduleAt(simTime()+0.2,senderDelay);
            else
                scheduleAt(simTime()+0.1,senderDelay);
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
                buf = d1;
                copy =d;
                if(uniform(0,1)<0.4)
                    scheduleAt(simTime()+0.2,receiverDelay);
                else
                    scheduleAt(simTime()+0.1,receiverDelay);
            }
            if(strcmp(d->getType(),"ACK")==0)
            {
                delete msg;

            }

        }
    }
}
