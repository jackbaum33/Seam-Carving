#include <cassert>
#include "Matrix.hpp"
using namespace std;
const int MIN_INT = -2147483647;
const int MAX_INT=2147483647;
// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  // assert(width>0);
  // assert(width<=MAX_MATRIX_WIDTH); 
  // assert(height>0);
  // assert(height<=MAX_MATRIX_HEIGHT); 
  mat->width=width;
  mat->height=height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
 os<<Matrix_width(mat)<<" "<<Matrix_height(mat)<<endl;
 for(int i=0; i<Matrix_height(mat); i++){
  for(int j=0;j<Matrix_width(mat); j++){
   os<<*Matrix_at(mat,i,j)<<" ";
  }
  os<<endl;
}
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return mat->width; 
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
int pos=(ptr-mat->data);
int row=pos/(Matrix_width(mat));
  return row;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  int pos=(ptr-mat->data);
  int column=pos%Matrix_width(mat);
  return column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  // assert(row>=0);
  // assert(row < Matrix_height(mat));
  // assert(column>=0);
  // assert(column < Matrix_width(mat));
  int truePos= (row * mat->width)+column;
  int* ptr= &(mat->data[truePos]);
  return ptr;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  // assert(row>=0);
  // assert(row < Matrix_height(mat));
  // assert(column>=0);
  // assert(column < Matrix_width(mat));
  int truePos= (row * mat->width)+column;
  const int* ptr= &mat->data[truePos];
  return ptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  int width=Matrix_width(mat);
  int height=Matrix_height(mat);
  int totalSpaces=width*height;
  for(int i=0; i<totalSpaces; i++) 
  {
    mat->data[i]=value;
  }
  }

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  int startTopRow=0;
  int endTopRow=Matrix_width(mat)-1;
  for(int i=startTopRow; i<=endTopRow;i++) mat->data[i]=value;
  int startBottomRow=(Matrix_height(mat)-1)*Matrix_width(mat);
  int endBottomRow=(Matrix_height(mat) * Matrix_width(mat))-1;
  for(int i=startBottomRow; i<=endBottomRow;i++) mat->data[i]=value;

  int startFirstCol=0;
  int endFirstCol=((Matrix_height(mat))-1)*Matrix_width(mat);
  for(int i=startFirstCol; i<endFirstCol; i+=Matrix_width(mat)) mat->data[i]=value;
  int startLastCol=Matrix_width(mat)-1;
  int endLastCol=Matrix_width(mat) * Matrix_height(mat);
  for(int i=startLastCol; i<endLastCol; i+=Matrix_width(mat)) mat->data[i]=value;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int biggest=MIN_INT;
  for(int i=0; i<Matrix_height(mat); i++){
  for(int j=0;j<Matrix_width(mat); j++){
    int currVal=*Matrix_at(mat,i,j);
    if(currVal>biggest) biggest=currVal;
  }
  }
  return biggest;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
//  assert(row>=0);
//  assert(row < Matrix_height(mat));
//  assert(column_start>=0);
//  assert(column_start < Matrix_width(mat));
//  assert(column_start < column_end);
 int smallestCol=MAX_INT;
 int smallestVal=MAX_INT;
 for(int i=column_start; i<column_end; i++)
 {
  int currVal=*Matrix_at(mat,row,i);
  if(currVal<smallestVal)
  {
    smallestCol=i;
    smallestVal=currVal;

  } 
 }
 return smallestCol;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
//  assert( 0 <= row && row < Matrix_height(mat));
//  assert(0 <= column_start && column_end <= Matrix_width(mat));
//  assert(column_start < column_end);

int smallestNum=MAX_INT;
 for(int i=column_start; i<column_end; i++){
  int currVal=*Matrix_at(mat,row,i);
  if(currVal<smallestNum) smallestNum=currVal;
 }
 return smallestNum;
}
