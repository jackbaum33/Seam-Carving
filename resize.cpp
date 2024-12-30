#include <iostream>
#include <fstream>
#include "processing.hpp"
using namespace std;

int main(int argc,char* argv[])
{
if(argc!=4 && argc!=5)
{
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n";
    return 1;
}
string readFile=argv[1];
ifstream ins;
ins.open(readFile);
if(!ins.is_open())
{
    cout << "Error opening file: " << readFile << endl;
    return 1;
}
Image *img=  new Image;
Image_init(img,ins);
ins.close();
ofstream os;
string writeFile=argv[2];
os.open(writeFile);
if(!os.is_open())
{
    cout << "Error opening file: " << writeFile << endl;
    return 1;
}
int width=atoi(argv[3]);
if(width <0 || width> Image_width(img))
{
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1;
}
if(argc==5)
{
    int height =atoi(argv[4]);
    if(height <0 || height> Image_width(img))
{
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1;
}
seam_carve(img,width,height);
Image_print(img,os);
}
else
{
    seam_carve(img,width,Image_height(img));
    Image_print(img,os);
    
}

delete img;

    return 0;
}