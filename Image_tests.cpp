#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

//tests fill function
TEST(test_image_height) {
  Image *img = new Image;
  Image_init(img, MAX_MATRIX_WIDTH, 120);
  ASSERT_EQUAL(120, Image_height(img));
  delete img;
}


TEST(test_image_get_pixel) {
  Image *img = new Image;
  Image_init(img, 27, 13);
   Pixel black = {0, 0, 0};
   Pixel blue = {0, 0, 255};
  Image_fill(img, black);
  Image_set_pixel(img, 6, 3, blue);
  ASSERT_TRUE(Pixel_equal(blue, Image_get_pixel(img, 6, 3)));
delete img;
}

TEST(test_fill)
{
  Image* img=new Image;
  Image_init(img,4,5);
  Pixel reddishBlue={127,0,128};
  Image_fill(img,reddishBlue);
  for(int i=0; i<4; i++)
  {
    for(int j=0; j<5; j++)
    {
     assert(Pixel_equal(Image_get_pixel(img,i,j),reddishBlue)); 
    }
  }
  delete img;
}

TEST(test_image_height_max) {
  Image *img = new Image;
  
  Image_init(img, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
  int height=Image_height(img);
  ASSERT_EQUAL(MAX_MATRIX_HEIGHT, height);
  delete img;
}

//tests set_pixel after filling image
TEST(set_pixel_center)
{
  Image* img=new Image;
  Pixel testPix={6,7,8};
  Image_init(img,7,7);
  Image_fill(img,{3,4,5});
  Image_set_pixel(img,3,3,testPix);
  assert(Pixel_equal(Image_get_pixel(img,3,3),testPix));
  delete img;
}

TEST(set_pixel_corner)
{
   Image* img=new Image;
  Pixel testPix={6,7,8};
  Image_init(img,7,7);
  Image_fill(img,{3,4,5});
Image_set_pixel(img,0,0,testPix);
assert(Pixel_equal(Image_get_pixel(img,0,0),testPix));
delete img;
}

TEST(pixel_max_val)
{
  Image* img=new Image;
  Image_init(img,7,7);
  Image_fill(img,{255,255,255});
  assert(Pixel_equal(Image_get_pixel(img,3,3),{255,255,255}));
  assert(Pixel_equal(Image_get_pixel(img,6,6),{255,255,255}));
  delete img;
}

TEST(pixel_min_val)
{
  Image* img=new Image;
  Image_init(img,7,7);
  Image_fill(img,{0,0,0});
  assert(Pixel_equal(Image_get_pixel(img,3,3),{0,0,0}));
  assert(Pixel_equal(Image_get_pixel(img,6,0),{0,0,0}));
  delete img;
}


TEST (test_image_print) {
  Image *img = new Image;
  //create input file stream using filename and then passing it as a paremter
  //NEED TO FIX WHITE SPACE
  // to amke more image print tests look at spec
  string input = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);
  ostringstream ss_output;
  Image_print(img, ss_output);
  ASSERT_EQUAL(ss_input.str(), ss_output.str());
  delete img;
}

TEST(test_image_width) {
  Image *img = new Image;
  Image_init(img, 2, 2);
  ASSERT_EQUAL(2, Image_width(img));
  delete img;
}

TEST(test_image_width2) {
  Image *img = new Image;
  Image_init(img, 1, 100);
  ASSERT_EQUAL(1, Image_width(img));
  delete img;
}


TEST(test_image_height3) {
  Image *img = new Image;
  Image_init(img, 10, 1);
  ASSERT_EQUAL(1, Image_height(img));
  delete img;
}


TEST(test_image_get_pixel3) {
  Image *img = new Image;
  Image_init(img, 100, 100);
   Pixel greenish = {5, 200, 50};
   Pixel yellowish = {100, 100, 50};
  Image_fill(img, greenish);
  Image_set_pixel(img, 99, 1, yellowish);

  ASSERT_TRUE(Pixel_equal(yellowish, Image_get_pixel(img, 99, 1)));
  delete img;
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
