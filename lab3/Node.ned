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

package lab3new;

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
        A.toDl --> D.fromAl;
        D.toAl --> A.fromDl;
        D.toPl --> P.fromDl;
        P.toDl --> D.fromPl;
        P.toIn --> out;
        in --> P.fromOut;
}
