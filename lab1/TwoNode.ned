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

package lab1;

network TwoNode
{
    @display("bgb=468,177");
    submodules:
        N1: Node {
            id = 1;
             @display("i=,cyan");
            @display("p=32,87");
        }
        N2: Node {
            id = 2;
             @display("i=,gold");
            @display("p=303,87");
        }
    connections:
        N1.out --> {delay= 100ms;}-->N2.in;
        N2.out --> {delay= 100ms;}-->N1.in;
}
