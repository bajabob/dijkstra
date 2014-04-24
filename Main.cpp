#include "PriorityQueue.h"
#include "Vertex.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

typedef vector<vector<pair<int,float> > > Graph;

void dijkstra(const Graph  &graph,const int &source,const int &destination,vector<int> &path)
{
	PriorityQueue<Vertex> pq;

	vector<float> d(graph.size());
	vector<int> parent(graph.size());

	for(unsigned int i = 0 ;i < graph.size(); i++)
	{
		d[i] = std::numeric_limits<float>::max();
		parent[i] = -1;
	}

	d[source] = 0.0f;

	Vertex *v = new Vertex();
	v->adjacent_vertex = source;
	v->weight = d[source];
	pq.insertItem(source, v);

	while(!pq.isEmpty())
	{
		int u = pq.minElement()->adjacent_vertex;
		if(u==destination) break;
		pq.removeMin();
		for(unsigned int i=0; i < graph[u].size(); i++)
		{
			int v= graph[u][i].first;
			float w = graph[u][i].second;
			if(d[v] > d[u]+w)
			{
				d[v] = d[u]+w;
				parent[v] = u;
				Vertex *vert = new Vertex();
				vert->adjacent_vertex = v;
				vert->weight = d[v];
				pq.insertItem(source, vert);
			}
		}
	}
	path.clear();
	int p = destination;
	path.push_back(destination);
	while(p!=source)
	{
		p = parent[p];
		path.push_back(p);
	}
}

int main()
{

    Graph graph;
    char file[50];

    string js_nodes, js_paths;

    cout << "Please enter the name of file to read: ";
    cin >> file;

    ifstream ifs (file);
    if(ifs.is_open())
    {
    	int vert_count;
    	ifs >> vert_count;
    	cout << "Number of Verts: " << vert_count << endl;
    	graph.resize(vert_count+1);

    	for(int i = 0; i < vert_count; ++i)
    	    js_nodes += string("{\"index\":"+to_string(i)+", \"value\":"+to_string(i+1)+", \"r\":20}\n");

		while(true)
		{
			int vert;
			ifs >> vert;
			if(vert == -1)
				break;
			cout << "-> Vert: " << vert << endl;
			while(true)
			{
				int adj_vert, weight;
				ifs >> adj_vert;
				if(adj_vert == -1)
					break;
				ifs >> weight;
				cout << "Adjacent Vert: " << adj_vert << endl;
				cout << "Weight: " << weight << endl;

				graph[vert].push_back(make_pair(adj_vert, weight));

				js_paths += string("{\"source\":"+to_string(vert-1)+", \"target\":"+to_string(adj_vert-1)+", \"distance\":"+to_string(weight*3)+"}\n");
			}

			if(ifs.eof()){ // EOF? Break.
				ifs.close();
				break;
			}
		}
    }


    int source, destination;
	cout << endl << "Please enter the source vertex: ";
	cin >> source;

	cout << endl << "Please enter the destination vertex: ";
	cin >> destination;

    ofstream html_index, txt_nodes, txt_paths;
    html_index.open ("index.html", ios::trunc);
    ifstream html_template ("template.html");

    if(html_template.is_open() && html_index.is_open())
	{
    	while(true)
    	{
    		string line;
    		getline( html_template, line );

    		size_t needle0 = line.find("@STYLE@");
    		size_t needle1 = line.find("@ROUTE@");

			if( needle0 != string::npos)
			{
				if(js_nodes.size() > 4000)
					html_index << "\t<link href=\"stylesheets/shortest-path-dense.css\" rel=\"stylesheet\" type=\"text/css\" />\n";
				else
					html_index << "\t<link href=\"stylesheets/shortest-path.css\" rel=\"stylesheet\" type=\"text/css\" />\n";
			}
			else if( needle1 != string::npos)
				html_index << string("\t\t\t\tvar route = sp1.findRoute("+to_string(source-1)+","+to_string(destination-1)+");\n");
			else
				html_index << line;
			html_index << endl;

			if(html_template.eof()){ // EOF? Break.
				html_template.close();
				html_index.close();
				break;
			}
    	}
	}else{
		cerr << "index.html or template.html could not be opened, exiting..." << endl;
		return 1;
	}

    txt_nodes.open ("nodes.txt", ios::trunc);
    txt_nodes << js_nodes.substr(0, js_nodes.size()-1);
    txt_nodes.close();

    txt_paths.open ("paths.txt", ios::trunc);
    txt_paths << js_paths.substr(0, js_paths.size()-1);
    txt_paths.close();

    cout << "Calculating shortest path..." << endl;

    vector<int> path;
    dijkstra(graph, source, destination, path);
    for(int i=path.size()-1;i>=0;i--)
        cout << "->" << path[i];
    cout << endl;

    return 0;
}
