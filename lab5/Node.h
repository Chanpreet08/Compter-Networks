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

#ifndef __LAB5_NODE_H_
#define __LAB5_NODE_H_

#include <omnetpp.h>
#include<map>
#include<packet_m.h>
using namespace std;
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule
{
private :
    map<int,int> table,table1,table2,table3,table4,table5;
    int source;
    int destination;
    int counter;
    int gate;
    cMessage * counterEvent;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
