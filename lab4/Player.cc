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

#include "Player.h"

Define_Module(Player);

void Player::initialize()
{
    // TODO - Generated method body
}

void Player::handleMessage(cMessage *msg)
{
    cPacket* pkt = new cPacket();
        pkt = check_and_cast<cPacket*> (msg);

    if(strcmp(msg->getArrivalGate()->getName(),"fromDl")==0)
    {
        if(uniform(0,1)<0.1 && getId()==6)
        {

            EV<<"losing packet";
            bubble("Packet Lost");
            delete msg;
        }
        else
        {
            numSent++;
            P_PDU * p1 = new P_PDU();
            p1->encapsulate(pkt);
            send(p1,"toIn");
            numSent++;
        }
    }
    else if(strcmp(msg->getArrivalGate()->getName(),"fromOut")==0)
    {

        if (uniform(0,1)<0.15 && getId()==9)
        {
            EV<<"losing packet";
            bubble("Packet Lost");
            delete msg;
        }
        else
        {
            numReceived++;
            P_PDU * p2 = new P_PDU();
            p2 = check_and_cast<P_PDU *>(pkt);
            send(p2->decapsulate(),"toDl");
            numReceived;
        }

    }
}
