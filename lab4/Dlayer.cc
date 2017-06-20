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
    sf=0;
    sn=0;
    rn=0;
    sfill=0;
    w=4;
    se=0;
    numSent =0;
    numReceived =0;
    pSender = new cMessage("Sender self message");
    timeOutEvent = new cMessage("timeOutEvent");
    WATCH(numSent);
    WATCH(numReceived);
}

void Dlayer::handleMessage(cMessage *msg)
{
    if(msg==timeOutEvent)
    {
        sn= sf;
        D_PDU * d = new D_PDU();
        d= buf[sn]->dup();
        send(d,"toPl");
        sn++;
        numSent++;
        scheduleAt(simTime()+1,timeOutEvent);
    }
    else if(strcmp(msg->getName(),"stop")==0)
    {
        numReceived++;
        event = true;
        D_PDU * d = new D_PDU();
        d = buf[sn]->dup();
        send(d,"toPl");
        sn++;
        numSent++;
        scheduleAt(simTime()+1,timeOutEvent);
    }
    else if(msg == pSender)
    {
               D_PDU * d = new D_PDU();
               d= buf[sn]->dup();
               send(d,"toPl");
               numSent++;
               scheduleAt(simTime()+1,timeOutEvent);
               sn++;
    }
    else
    {
        cancelEvent(timeOutEvent);
        cPacket *pkt = new cPacket();
        pkt = check_and_cast<cPacket*>(msg);
        if(strcmp(msg->getArrivalGate()->getName(),"fromAl")==0)
        {
            if(se-sf<w && getId()==5)
            {
                D_PDU * d= new D_PDU();
                d->encapsulate(pkt);
                d->setId(counter%3);
                d->setType("Data");
                buf.push_back(d);
                se++;
                counter++;
                sfill++;
                numSent++;
                request = new cMessage("request");
                send(request,"toAl");
            }
            else if(se-sf<w && getId()==14)
            {

                D_PDU * d = new D_PDU();
                d->encapsulate(pkt);
                d->setType("Data");
                send(d,"toPl");

            }
            else if(se-sf>=w)
            {
                D_PDU * d = new D_PDU();
                d->encapsulate(pkt);
                d->setId(counter%3);
                d->setType("Data");
                buf.push_back(d);
                sfill++;
                counter++;
                scheduleAt(simTime()+0,pSender);
            }

        }
        else if(strcmp(msg->getArrivalGate()->getName(),"fromPl")==0)
        {
            D_PDU * d= new D_PDU();
            d = check_and_cast<D_PDU*>(pkt);
            if(strcmp(d->getType(),"Data")==0)
            {
               if(d->getId()==(rn%3))
               {
                   numReceived++;
                   D_PDU * d1 = new D_PDU();
                   d1->setId(d->getId());
                   d1->setType("ACK");
                   send(d->decapsulate(),"toAl");
                   send(d1,"toPl");
                   rn++;
               }
               else if (d->getId()!=(rn%3))
               {
                   delete d;
               }

            }
            if(strcmp(d->getType(),"ACK")==0)
            {
                if(!event && d->getId()==sf%3)
                {
                    sf++;
                    se++;
                    delete msg;
                    request = new cMessage("request");
                    send(request,"toAl");
                    numSent++;
                }
                else if(event && sn-se!=0)
                {
                    scheduleAt(simTime()+0,pSender);
                }
            }

        }
    }
}
