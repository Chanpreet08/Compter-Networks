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

package lab5;

network ForwardingNetwork
{
    submodules:
        A: Node {
            id = 1;
            @display("p=98,92");
        }
        B: Node {
            id = 2;
            @display("p=464,78");
        }
        C: Node {
            id = 3;
            @display("p=264,160");
        }
        D: Node {
            id = 4;
            @display("p=112,234");
        }
        E: Node {
            id = 5;
            @display("p=464,209");
        }
    connections allowunconnected:
        A.out[0] --> B.in[0];
        B.out[0] --> A.in[0];
        A.out[1] --> C.in[0];
        C.out[0] --> A.in[1];
        A.out[2] --> D.in[0];
        D.out[0] --> A.in[2];
        C.out[1] --> B.in[1];
        B.out[1] --> C.in[1];
        E.out[0] --> C.in[2];
        C.out[2] --> E.in[0];
        E.out[1] --> B.in[2];
        B.out[2] --> E.in[1];
}
