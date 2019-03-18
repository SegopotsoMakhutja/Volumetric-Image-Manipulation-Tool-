#include "volimage"
#include <iostream>

using namespace MKHSEG001;
using namespace std;

// default const
volimage::Volimage()
{
    width = 0; height = 0;
    vector<unsigned char**> slices;
}

// decons
volimage::~Volimage()
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

int main()
{
    int number = argc;
    volimage images;
    string imgName = string(argv[1]);

    if (number == 2)
    {
        cout << "you did not specify any operation." << endl;
        images.readImages(imgName);
        int numImg = images.numOfImages();
        int numBytes = images.volImageSize();
        cout << "Number of Images: " << numImg << endl;
        cout << "Number of bytes: " << numBytes << endl;
    }

    switch(number)
    {
        default:
        {
            cout << "incorrect input format" << endl; 
            break;
        }

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

        case 6;
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
    }

    return 0; // safe and correct execution
}