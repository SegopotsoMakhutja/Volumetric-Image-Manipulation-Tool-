/**
 * VOLIMAGE_H h file
 */

#ifndef VOLIMAGE_H
#define VOLIMAGE_H
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <cstdlib>

namespace MKHSEG001{
    class Volimage{
        private: 
            int width, height;                      //width and height of image
            std::vector<unsigned char**> slices;    //data for each slice

        public:
            Volimage();     // default constructor
            ~Volimage();    // destructor
            bool readImages(std::string baseName);
            int numOfImages(void);
            int volImageSize(void);
            void diffmap(int sliceI, int sliceJ, std::string output_prefix);
            void extract(int sliceId, std::string output_prefix);
            void extractRow(int row, std::string output_prefix);}
    };
}

#endif