#include <cassert>
#include "Image.hpp"
#include <string>
using namespace std;

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  // assert(width>0);
  // assert(width <= MAX_MATRIX_WIDTH);
  // assert(height>0);
  // assert(height <= MAX_MATRIX_HEIGHT);
  img->width=width;
  img->height=height;
  Matrix_init(&img->red_channel,width,height);
  Matrix_init(&img->green_channel,width,height);
  Matrix_init(&img->blue_channel,width,height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
  string junkString;
  int width;
  int height;
  is>>junkString;

  is>>width>>height>>junkString;
  Image_init(img,width,height);
  


  for(int i=0; i<height; i++){
    for(int j=0;j<width;j++){
      int red;
      int green;
      int blue;
      is>>red>>green>>blue;
      *Matrix_at(&img->red_channel,i,j)=red;
      *Matrix_at(&img->green_channel,i,j)=green;
      *Matrix_at(&img->blue_channel,i,j)=blue;
    }

  }




}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  os<<"P3"<<endl;
  os<<Image_width(img)<<" "<<Image_height(img)<<endl;
  os<<"255"<<endl;
  for(int i=0; i<Image_height(img);i++){
    for(int j=0; j<Image_width(img); j++){
      Pixel p=Image_get_pixel(img,i,j);
      os<<p.r<<" "<<p.g<<" "<<p.b << " ";
    }
    os<<endl;
  }

}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  // assert(row >=0);
  // assert(row < Image_height(img));
  // assert(column>=0);
  // assert(column < Image_width(img));
  Pixel p;
 const Matrix* redVal=&img->red_channel;
 const Matrix* greenVal=&img->green_channel;
 const Matrix* blueVal=&img->blue_channel;
  p.r=*Matrix_at(redVal,row,column);
  p.g=*Matrix_at(greenVal,row,column);
  p.b=*Matrix_at(blueVal,row,column);
  return p;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  // assert(row >=0);
  // assert(row < Image_height(img));
  // assert(column>=0);
  // assert(column < Image_width(img));
  Matrix* redVal=&img->red_channel;
  Matrix* greenVal=&img->green_channel;
  Matrix* blueVal=&img->blue_channel;
  *Matrix_at(redVal,row,column)=color.r;
  *Matrix_at(greenVal,row,column)=color.g;
  *Matrix_at(blueVal,row,column)=color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  int rows=Image_height(img);
  int cols=Image_width(img);
  for(int i=0; i<rows; i++){
    for(int j=0;j<cols;j++){
      Image_set_pixel(img,i,j,color);
    }
  }
}