

#include <iostream>

using namespace std;

class Vertex{

public:

	// the final distance to this target
	int weight;

	int adjacent_vertex;

	// get some element used to compare this city with others
	int getCmp(){return weight;}

	// get the unique key associated with this city
	int getKey(){return adjacent_vertex;}
};

/**
 * @override
 * Output Operator <<
 */
ostream& operator<<(ostream& out, const Vertex *f) {

	out << "weight: " << f->weight << endl;
	out << "adj vert: " << f->adjacent_vertex << endl;

	return out;
}
