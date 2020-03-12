#include "Texture2D.h"

Texture2D::Texture2D() {

}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &_ID);
}

bool Texture2D::LoadRAW(char* path, int width, int height) {
	char* tempTexData;
	int fileSize;
	ifstream infile;
	_width = width;
	_height = height;

	infile.open(path, ios::binary);
	if (!infile.good())
	{
		cerr << "Cant open texture file " << path << endl;
		return false;
	}

	infile.seekg(0, ios::end); // seek to the end of the file
	fileSize = (int)infile.tellg(); //gets the current position in the file, being the end, which gives the filesize
	tempTexData = new char[fileSize]; //create an array to stor the data
	infile.seekg(0, ios::beg); //seeks back to the start of the file
	infile.read(tempTexData, fileSize); //read all the data in one go
	infile.close();

	cout << path << "loaded" << endl;

	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID); //bind texture to id
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTexData);

	delete[] tempTexData;
	return true;
}

bool Texture2D::LoadBMP(char* path) {
	char header[54];
	char* data;
	int dataPos, width, height, imageSize;

	ifstream infile;
	infile.open(path, ios::binary);
	if (!infile.good())
	{
		cerr << "Cant open texture file " << path << endl;
		return false;
	}
	infile.read(header, 54);

	if (header[0] != 'B' || header[1] != 'M')
	{
		cerr << "Cant open texture file " << path << endl;
		return false;
	}

	dataPos = *(int*) & (header[0x0A]);
	imageSize = *(int*) & (header[0X22]);
	width = *(int*) & (header[0X12]);
	height = *(int*) & (header[0X16]);

	if (imageSize == 0)
	{
		imageSize = width * height * 3;
	}

	if (dataPos == 0)
	{
		dataPos = 54;
	}

	data = new char[imageSize];
	infile.seekg(dataPos);
	infile.read(data, imageSize);
	infile.close();

	cout << path << "loaded" << endl;

	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID); //bind texture to id
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

	return true;
}