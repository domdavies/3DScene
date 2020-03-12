#include "objLoader.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace OBJMeshLoader
{
	Mesh* OBJMeshLoader::LoadOBJ(char* path) {
		Mesh* mesh = new Mesh();
		ifstream readfile;
		readfile.open(path);

		if (!readfile.good())
		{
			cerr << "Cant open file";
			return false;
		}
		string line;
		while (readfile >> line)
		{
			//checks to see if the line starts with "v "
			//if so then store the information as vertex data
			if (line == "v")
			{
				Vector3 v;
				readfile >> v.x >> v.y >> v.z;
				//cout << v.x << " " << v.y  << " " << v.z << endl;
				//add the vertex coordinated to the list
				mesh->vertices.push_back(v);
			}
			//checks to see if the line starts with "vt"
			//if so then store the information as vertex texture data
			if (line == "vt")
			{
				Texture t;
				readfile >> t.u >> t.v;
				mesh->textures.push_back(t);
				//cout << t.u  << " " << t.v << endl;
			}
			//checks to see if the line starts with "vn"
			//if so then store the information as vertex normal data
			if (line == "vn")
			{
				Normal n;
				readfile >> n.x >> n.y >> n.z;
				mesh->normals.push_back(n);
				//cout << n.x << " " << n.y << " " << n.z << endl;
			}
			//checks to see if the line starts with "f "
			//if so then store the information as face data
			if (line == "f")
			{
				int f1, f2, f3; //store the vertices index data (f1, f2, f3)
				int t1, t2, t3; //store texture index data (t1, t2, t3)
				int n1, n2, n3; //store normal index data (n1, n2, n3)
				const char* faceLine = line.c_str();
				// read the line and pass each value to be stored
				//e.g. 12/1/2 2/32/4 3/21/5  = f1/t1/n1 f2/t2/n2 f3/t3/n3 
				readfile >> f1;
				if (readfile.peek() == '/')
				{
					readfile.ignore(1);
				}
				readfile >> t1;
				if (readfile.peek() == '/')
				{
					readfile.ignore(1);
				}
				readfile >> n1;
				readfile >> f2;
				if (readfile.peek() == '/')
				{
					readfile.ignore(1);
				}
				readfile >> t2;
				if (readfile.peek() == '/')
				{
					readfile.ignore(1);
				}
				readfile >> n2;
				readfile >> f3;
				if (readfile.peek() == '/')
				{
					readfile.ignore(1);
				}
				readfile >> t3;
				if (readfile.peek() == '/')
				{
					readfile.ignore(1);
				}
				readfile >> n3;
				//sscanf_s(faceLine, "f %i/%i/%i %i/%i/%i %i/%i/%i", &f1, &t1, &n1, &f2, &t2, &n2, &f3, &t3, &n3);
				//cout << f1 << " " << t1 << " " << n1 << ", " << f2 << " " << t2 << " " << n2 << ", " << f3 << " " << t3 << " " << n3 << endl;

				// creates a list of indexed vertices
				//puts the first value, stored, as the first vertex coord to be used
				//same for normals and textures
				mesh->vertexIndex.push_back(f1); mesh->textureIndex.push_back(t1); mesh->normalIndex.push_back(n1);
				mesh->vertexIndex.push_back(f2); mesh->textureIndex.push_back(t2); mesh->normalIndex.push_back(n2);
				mesh->vertexIndex.push_back(f3); mesh->textureIndex.push_back(t3); mesh->normalIndex.push_back(n3);
			}
		}
		readfile.close();

		for (int i = 0; i < mesh->vertexIndex.size(); i++)
		{
			//sets the vertex data, dependant on the face data.
			//so if face =12/9/34 etc then we would use the 12th vertex first 
			//c++ lists start at 0, obj files star at 1
			//so we takeaway 1 to start from 0
			int f = mesh->vertexIndex[i];
			Vector3 vertex = mesh->vertices[f - 1];
			mesh->out_vertices.push_back(vertex);
			//cout << mesh->out_vertices[i].x;.0
		}

		for (int i = 0; i < mesh->textureIndex.size(); i++)
		{
			int f = mesh->textureIndex[i];
			Texture texture = mesh->textures[f - 1];
			mesh->out_textures.push_back(texture);
			//cout << mesh->out_textures[i].u;
		}

		for (int i = 0; i < mesh->normalIndex.size(); i++)
		{
			int f = mesh->normalIndex[i];
			Normal normal = mesh->normals[f - 1];
			mesh->out_normals.push_back(normal);
			//cout << mesh->out_normals[i].x;
		}
		return mesh;
	}
}