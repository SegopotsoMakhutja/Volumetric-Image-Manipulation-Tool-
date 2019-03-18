/**
 * method implementation file for
 * methods defined in the h file
 */
#include "volimage.h"
#include <iostream>

using namespace MKHSEG001;
using namespace std;

/**
 * populate the object with images in stack and
 * set member variables define in .cpp
 */
bool Volimage::readImages(std::string baseName)
{
	string fldr = baseName + "/" + baseName;
	string filename = fldr + ".data";
	ifstream infile(filename.c_str());
	if(!infile)
	{
		cout << "File open failed." << endl;
	}

	string line;
	getline(infile, line);
	stringstream ss(line);
  	vector<int> fields;
	string temp;
	int number;

	while(getline(ss, temp, ' '))
	{
		istringstream ( temp ) >> number;
		fields.push_back(number);
	}

		width = fields[0];
			height = fields[1];
			int number_images = fields[2];

			infile.close();

			unsigned char **images = nullptr;

		for(int image = 0; image< number_images; image++){

			ifstream myimage (fldr+to_string(image)+".raw", ios::binary);

			images = new unsigned char*[height];

				for(int j = 0; j< height; j++){
				images[j] = new unsigned char[width];
				myimage.read((char*)images[j],width);
			}
			slices.push_back(images);
			myimage.close();
			}
	cout<<"\nReading images succesful"<<endl;
}

/**
 * number of bytes uses to store image data bytes
 * and pointers (ignore vector<> container, dims etc)
 */
int Volimage::volImageSize(void)
{
	unsigned int size = width * height * slices.size();
	return size;
}

/**
* number of images stored in a volume
*/
int Volimage::numOfImages(void)
{
	int num = slices.size();
	return num;
}

/**
* compute difference map and write out;
*/
void Volimage::diffmap(int sliceI, int sliceJ, std::string output_prefix)
{
	ofstream difference_image (output_prefix+".raw",ios::out | ios::binary);
	unsigned char** data = new unsigned char*[height];
	int r=0;
	while(r<height)
	{
		data[r] = new unsigned char[width];
		for(int c = 0; c<width; c++)
		{
			data[r][c] = (unsigned char)(fabs((float)slices[sliceI][r][c] - (float)slices[sliceJ][r][c])/2);
		}
	
		difference_image.write((char*)data[r],width); r++;
	}

		difference_image.close();

		ofstream diff(output_prefix+".data");

		int val[] = {width, height, 1};
		//int j = 0;
		//while(j<3){
		for(int j = 0; j<3; j++)
		{
			diff<< *(val+j);
			diff<< " ";
			//j++;
		}
		cout<<"Diffmap complete"<<endl;
		diff.close();
}

/**
* extract slice sliceId and write to output
*/
void Volimage::extract(int sliceId, std::string output_prefix)
{
	ofstream image_extract (output_prefix+".raw",ios::out | ios::binary);
	unsigned char **sliced = slices[sliceId];
	for(int i = 0; i<height;i++)
	{
		image_extract.write((char*)sliced[i],width);
	}

	image_extract.close();
	ofstream header(output_prefix+".data");

	int myarray[] = {width, height, 1};
    for(int j = 0; j<3; j++)
	{	
		header<< *(myarray+j);
		header<< " ";
	}
	header.close();

}

/**
* extract row across all slices and write to output
*/
void Volimage::extractRow(int row, std::string output_prefix)
{	
	ofstream row_extract (output_prefix+".raw",ios::out | ios::binary);
	int DEPTH = slices.size(); 
	unsigned char **file = new unsigned char*[DEPTH];
	//for(int i = 0; i<slices.size(); i++){
	int i=0;
	while (i<slices.size())
	{
		file[i] = new unsigned char[width];
		file[i] = slices[i][row]; 
		row_extract.write((char*)file[i],width);
		i++;
	}
	row_extract.close();
	
	ofstream row_header(output_prefix+".data");
	int myarr[] = {width, DEPTH, 1};

    for(int j = 0; j<3; j++)
	{	
		row_header<< *(myarr+j);
		row_header<< " ";
	}

	row_header.close();
}
