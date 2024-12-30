#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

//tests fill and fill_border for a negative value
TEST(test_fill_negative)
{
  Matrix* mat=new Matrix;
  Matrix_init(mat,5,5);
  Matrix_fill(mat,-4);
  for(int r = 0; r < 5; ++r){
    for(int c = 0; c < 5; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), -4);
    }
}
Matrix_fill_border(mat,-33);
ASSERT_EQUAL(*Matrix_at(mat,0,0),-33);
ASSERT_EQUAL(*Matrix_at(mat,4,4),-33);
ASSERT_EQUAL(*Matrix_at(mat,0,4),-33);
ASSERT_EQUAL(*Matrix_at(mat,4,0),-33);
delete mat;
}

//tests max for all negatives
TEST(test_max_negatives)
{
  Matrix* mat=new Matrix;
  Matrix_init(mat,3,3);
  Matrix_fill(mat,-300);
  Matrix_fill_border(mat,-32);
  ASSERT_EQUAL(Matrix_max(mat),-32);
  delete mat;
}
// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

//test fill with big positive number
TEST(test_Matrix_fill_border)
{
  Matrix *mat = new Matrix;

  const int fillValue = 23;
  Matrix_init(mat, 5, 10);
  Matrix_fill_border(mat, fillValue);
  for (int r = 0; r < Matrix_height(mat); ++r)
  {
    ASSERT_EQUAL(*Matrix_at(mat, r, 0), fillValue);
  }

  for (int c = 0; c < Matrix_width(mat); ++c)
  {
    ASSERT_EQUAL(*Matrix_at(mat, 0, c), fillValue);
  }

  for (int r = 0; r < Matrix_height(mat); ++r)
  {
    ASSERT_EQUAL(*Matrix_at(mat, r, Matrix_width(mat) - 1), fillValue);
  }

  for (int c = 0; c < Matrix_width(mat); ++c)
  {
    ASSERT_EQUAL(*Matrix_at(mat, Matrix_height(mat) - 1, c), fillValue);
  }

  delete mat;
}


//column of min value in row for all same value
TEST(min_same_value)
{
  Matrix* mat=new Matrix;
  Matrix_init(mat,4,4);
  Matrix_fill(mat,5);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,0,0,3),5);
  delete mat;
}

//column of min value in row for negative values
TEST(min_col_negatives)
{
   Matrix* mat=new Matrix;
   Matrix_init(mat,6,6);
  Matrix_fill(mat,-87);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,4,0,5),-87);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,4,0,5),0);
  delete mat;
}

//min value in row with only two columns
TEST(min_two_cols)
{
   Matrix* mat=new Matrix;
   Matrix_init(mat,2,2);
   Matrix_fill(mat,33);
   *Matrix_at(mat,0,0)=45;
   ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,0,0,1),0);
   delete mat;
}

//min row with only one row
TEST(min_one_row)
{
   Matrix* mat=new Matrix;
   Matrix_init(mat,1,3);
   Matrix_fill(mat,23);
   ASSERT_EQUAL(Matrix_min_value_in_row(mat,0,0,2),23);
   delete mat;
}

//row function with only one row
TEST(row_one_row)
{
   Matrix* mat=new Matrix;
   Matrix_init(mat,6,1);
   Matrix_fill(mat,-3);
   ASSERT_EQUAL(Matrix_height(mat),1);
   delete mat;
}

//fill border function with only one column
TEST(fill_border_one_col)
{
   Matrix* mat=new Matrix;
   Matrix_init(mat,5,1);
   Matrix_fill_border(mat,5);
   ASSERT_EQUAL(*Matrix_at(mat,0,4),5);
   delete mat;
}

//max size matrix
TEST(max_size_matrix)
{
   Matrix* mat=new Matrix;
  Matrix_init(mat,MAX_MATRIX_WIDTH,MAX_MATRIX_HEIGHT);
  ASSERT_EQUAL(Matrix_height(mat),500);
  Matrix_fill(mat,456);
  ASSERT_EQUAL(*Matrix_at(mat,499,499),456);
  delete mat;
  }

TEST(fill_with_one_matrix)
{
Matrix* mat=new Matrix;
  Matrix_init(mat,1,1);
  Matrix_fill(mat,27);
  ASSERT_EQUAL(*Matrix_at(mat,0,0),27);
  delete mat;
}

TEST(test_height)
{
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  int value = 4;
  Matrix_init(mat, 3, 56);
  Matrix_fill(mat, value);

  ASSERT_EQUAL(56, Matrix_height(mat));

  delete mat; // delete the Matrix
}

TEST(test_width)
{
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  int value = 112;
  Matrix_init(mat, 104, 104);
  Matrix_fill(mat, value);

  ASSERT_EQUAL(104, Matrix_width(mat));

  delete mat; // delete the Matrix
}


TEST(test_print)
{
  Matrix *mat = new Matrix;

  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 42);

  ostringstream expected;
  expected << "3 3\n"
           << "42 42 42 \n"
           << "42 42 42 \n"
           << "42 42 42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
