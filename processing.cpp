#include <cassert>
#include "processing.hpp"
#include <cmath>

using namespace std;
const int MIN_INT = -2147483647;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  int biggestEnergy=MIN_INT;
  int width=Image_width(img);
  int height=Image_height(img);
  Matrix_init(energy,width,height);
  Matrix_fill(energy,0);
  for(int i=1; i<Matrix_height(energy)-1; i++)
  {
    for(int j=1; j<Matrix_width(energy)-1; j++)
    {
    int energyOfPixel;
    energyOfPixel=squared_difference(Image_get_pixel(img,i+1,j),
    Image_get_pixel(img,i-1,j));
    energyOfPixel+=squared_difference(Image_get_pixel(img,i,j-1),
    Image_get_pixel(img,i,j+1));
     *Matrix_at(energy,i,j)=energyOfPixel;
     if(energyOfPixel>biggestEnergy){
      Matrix_fill_border(energy,energyOfPixel);
      biggestEnergy=energyOfPixel;
     }
    }
  }

}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  int width=Matrix_width(energy);
  int height=Matrix_height(energy);
  Matrix_init(cost,width,height);

  for(int i=0; i<width; i++){
    int energyFirstRow = *Matrix_at(energy,0,i);
    *Matrix_at(cost,0,i)=energyFirstRow;
  }

for(int i=1; i<height; i++){
  for(int j=0; j<width; j++){
    if(j-1<0)
    {
      int costOfPixel=*Matrix_at(energy,i,j);
      costOfPixel+=Matrix_min_value_in_row(cost,i-1,j,j+2);
       *Matrix_at(cost,i,j)=costOfPixel;
    }
    else if(j+2>width)
    {
       int costOfPixel=*Matrix_at(energy,i,j);
       costOfPixel+=Matrix_min_value_in_row(cost,i-1,j-1,j+1);
        *Matrix_at(cost,i,j)=costOfPixel;
    }
    else
    {
      int costOfPixel=*Matrix_at(energy,i,j);
       costOfPixel+=Matrix_min_value_in_row(cost,i-1,j-1,j+2);
       *Matrix_at(cost,i,j)=costOfPixel;
    }
  }
}

}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
  int startingPixel;
  int height=Matrix_height(cost);
  startingPixel=Matrix_column_of_min_value_in_row(cost,
  Matrix_height(cost)-1,0,Matrix_width(cost));
  seam[height-1]=startingPixel;
  int currentColumn=startingPixel;
  int newColumn;
  for(int i=height-2; i>=0; i--){
    if(currentColumn==0)
    {
      newColumn=Matrix_column_of_min_value_in_row(cost,i-1,0,currentColumn+2);
      seam[i]=newColumn;
      currentColumn=newColumn;
      
    }
    else if(currentColumn==Matrix_width(cost)-1)
    {
      newColumn=Matrix_column_of_min_value_in_row(cost,i-1,
      currentColumn-1,currentColumn+1);
      seam[i]=newColumn;
      currentColumn=newColumn;
    }
    else
    {
      newColumn=Matrix_column_of_min_value_in_row(cost,i,
      currentColumn-1,currentColumn+2);
      seam[i]=newColumn;
      currentColumn=newColumn;
    }
  }

}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image *img, const int seam[]) {
  Image* temp= new Image;
  Image_init(temp,Image_width(img)-1,Image_height(img));
  for(int i=0; i< Image_height(img); i++)
  {
    int stoppingValue=seam[i];
        for(int j=0; j<stoppingValue; j++)
    {
      Image_set_pixel(temp,i,j,Image_get_pixel(img,i,j));
    }
    for(int k=stoppingValue+1; k<Image_width(img); k++)
    {
      Image_set_pixel(temp,i,k-1,Image_get_pixel(img,i,k));
    }
  }
  *img=*temp;
  delete temp;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
// NOTE:     The size of an array local variable must be a compile-time
//           constant. You can use MAX_MATRIX_HEIGHT as the constant,
//           since an image's height can be no larger than that.
void seam_carve_width(Image *img, int newWidth) {
  assert(newWidth >0 && newWidth <= Image_width(img));
  int width=Image_width(img);
  while(width>newWidth)
  {
  Matrix* energy=new Matrix;
  compute_energy_matrix(img,energy);
  Matrix* cost=new Matrix;
  compute_vertical_cost_matrix(energy,cost);
  delete energy;
  int seam[MAX_MATRIX_HEIGHT];
  find_minimal_vertical_seam(cost,seam);
  delete cost;
  remove_vertical_seam(img,seam);
  width=Image_width(img);
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
assert(newHeight>0 && newHeight <= Image_height(img));
rotate_left(img);
seam_carve_width(img,newHeight);
rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
assert(newWidth >0 && newWidth <= Image_width(img));
assert(newHeight>0 && newHeight <= Image_height(img));

seam_carve_width(img,newWidth);
seam_carve_height(img,newHeight);
}

