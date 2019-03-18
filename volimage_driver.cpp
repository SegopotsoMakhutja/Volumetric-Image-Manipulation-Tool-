#include "volimage.h"
#include <iostream>

using namespace MKHSEG001;
using namespace std;

// default const
Volimage::Volimage()
{
    width = 0; height = 0;
    vector<unsigned char**> slices;
}

// decons
Volimage::~Volimage()
{
    for (int i = 0; i < slices.size(); i++)
    {   
        for (int j = 0; j < height; j++)
        {
            delete [] slices[i][j];
            //delete [] slices[i];
        }
        delete [] slices[i];
    } 
}

int main(int argc, char* argv[])
{
    int number = argc;
    Volimage images;
    string imgName = string(argv[1]);

    if (number == 2)
    {
        cout << "you did not specify any operation." << endl;
        images.readImages(imgName);
        int numImg = images.numOfImages();
        int numBytes = images.volImageSize();
        cout << "the number of images read = " << numImg << endl;
        cout << "Number of bytes =  " << numBytes << endl;
    }

    switch(number)
    {
        case 5:
        {
            if(string(argv[2])=="-x")
            {
                int x;
                istringstream xx(argv[3]);
                xx >> x;
                if(xx.fail())
                {
                    cerr << "failed operation." << endl;
                    return 0;
                }
                images.readImages(imgName);
                images.extract(x, string(argv[4]));
            }
            else if(string(argv[2])=="-g")
            {
                int x;
                istringstream xx(argv[3]);
                xx >> x;
                if(xx.fail())
                {
                    cerr << "failed operation." << endl;
                    return 0;
                }
                images.readImages(imgName);
                images.extractRow(x, string(argv[4]));
            }
            break;
        }

        case 6:
        {
            if(string(argv[2])=="-d")
            {
                int x,y;
                istringstream i(argv[3]);
                istringstream j(argv[4]);
                i >> x;
                j >> y;
                
                if(i.fail() || j.fail())
                {
                    cerr << "failed operation, check formatting." << endl;
                    break;
                }
                images.readImages(imgName);
                images.diffmap(x,y,string(argv[5]));
            }
            break;
        }

        default:
        {
            cout << "\ninvoke operations as follows. " << "\n" 
            << "volimage <imageBase> [-d i j output_file_name] [-x i output_file_name] \n" << endl;
            cout << "the operation for -g, needs to be run separately." << endl;
             
            break;
        }
    }

    return 0; // safe and correct execution
}