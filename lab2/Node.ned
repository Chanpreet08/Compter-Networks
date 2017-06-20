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

package lab2new;

module Node
{
    parameters:
        int node_id;
        @display("bgb=195,339");
    gates:
        input in;
        output out;

    submodules:
        A: Alayer {
            id = 1;
            @display("p=85,36");
        }
        D: Dlayer {
            id = 1;
            @display("p=85,131");
        }
        P: Player {
            id = 1;
            @display("p=85,238");
        }

    connections:
        A.toDl -->{delay=100ms;}--> D.fromAl;
        D.toAl -->{delay=100ms;}--> A.fromDl;
        D.toPl -->{delay=100ms;}--> P.fromDl;
        P.toDl -->{delay=100ms;}--> D.fromPl;
        P.toIn -->{delay=100ms;}--> out;
        in -->{delay=100ms;}--> P.fromOut;
}
