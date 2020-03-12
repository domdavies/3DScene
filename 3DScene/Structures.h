#ifndef  _STRUCTURES_H
#define _STRUCTURES_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include <vector>
#include <string>
#include <iostream>

//struct to define position/coordinate on screen
struct Vector3 {
	float x, y, z;
};

struct Vector4 {
	float x, y, z, w;
};

//a struct for the lighting
struct Lighting {
	Vector4 ambient, diffuse, specular;
};

//struct for the material
struct Material {
	Vector4 ambient, diffuse, specular;
	GLfloat shininess;
};

//struct to define the camera object
struct Camera {
	Vector3 eye;
	Vector3 centre;
	Vector3 up;
};

//struct to set the color value

struct Color {
	float r;
	float g;
	float b;
};

//struct to define a vertex coord
struct Vertex {
	float x, y, z;
};

struct Texture {
	GLfloat u, v;
};

struct Normal {
	float x, y, z;
};

struct Mesh {
	Vertex* Vertices;
	Vertex* Normals;
	GLushort* Indices;
	Texture* TexCoords;
	int VertexCount, NormalCount, TexCount, IndexCount;

	std::vector <Vector3> vertices, out_vertices;
	std::vector <Texture> textures, out_textures;
	std::vector <Normal> normals, out_normals;

	std::vector <GLint> vertexIndex, normalIndex, textureIndex, faceIndex;
};
#endif // ! _STRUCTURES_H