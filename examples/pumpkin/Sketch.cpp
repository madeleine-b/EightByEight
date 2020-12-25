/** \file
 * LET'S DRAW A PUMPKIN FOR HALLOWEEN
 */

#include <Arduino.h>
#include "Sketch.h"
#include "Image.h"

Image board;

// CUSTOMIZE: Set the speed at which to cycle between the images
static int speed = 1;
// CUSTOMIZE: Set the colors and pixels here, in hex format (similar to coloring HTML.)
// or use preset colors defined in Image.
static uint32_t palette[] = {Image::BLACK, Image::WHITE,
  Image::RED, Image::ORANGE, Image::YELLOW, Image::GREEN, Image::BLUE, Image::PURPLE, Image::PINK,
  0xfd962c, // orange 9
  0xfdee39, // yellow 10
  0x266d0e, //dark green 11
  0x4b21e9, // bright purple 12
  0x2d108d, // dark purple 13
  0xf95272, // salmon 14
  0xD6D6D6, // light gray 15
  0x1d7cf9 // royal blue 16
  };
// This demo will cycle through the set of drawings in this array
static const int IMAGES = 6;
static int pixels[IMAGES][LED_ROWS][LED_COLS] = 
{
 { // jack o lantern facing right
 {0,0,0,0,11,11,0,0},
 {0,0,0,11,11,0,0,0},
 {0,0,9,9,9,9,0,0},
 {0,9,9,10,9,10,9,0},
 {0,9,9,9,9,9,9,0},
 {0,9,10,9,10,9,10,0},
 {0,9,9,10,9,10,9,0},
 {0,0,9,9,9,9,0,0},
 },
 { // jack o lantern facing left
 {0,0,0,0,11,11,0,0},
 {0,0,0,11,11,0,0,0},
 {0,0,9,9,9,9,0,0},
 {0,9,10,9,10,9,9,0},
 {0,9,9,9,9,9,9,0},
 {0,10,9,10,9,10,9,0},
 {0,9,10,9,10,9,9,0},
 {0,0,9,9,9,9,0,0},
 },
 { // bat (wings up)
 {0,0,13,0,0,13,0,0},
 {12,0,13,12,12,13,0,12},
 {12,0,12,12,12,12,0,12},
 {12,12,12,14,12,14,12,12},
 {13,12,12,12,14,12,12,13},
 {0,13,12,12,12,12,13,0},
 {0,0,13,12,12,13,0,0},
 {0,0,0,13,13,0,0,0}
 },
 { // bat (wings down)
 {0,0,13,0,0,13,0,0},
 {0,0,13,12,12,13,0,0},
 {0,0,12,12,12,12,0,0},
 {12,12,12,14,12,14,12,12},
 {12,12,12,12,14,12,12,12},
 {13,13,12,12,12,12,13,13},
 {13,0,13,12,12,13,0,13},
 {0,0,0,13,13,0,0,0}
 },
 { // ghost looking left
 {0,  0,  0,  15, 15, 0,  0,  0},
 {0,  0,  15, 15, 15, 15, 0,  0},
 {0,  15, 16, 15, 16, 15, 15, 0},
 {0,  15, 16, 15, 16, 15, 15, 0},
 {0,  15, 15, 15, 15, 15, 15, 0},
 {0,  15, 15, 16, 15, 15, 15, 0},
 {0,  15, 15, 15, 15, 15, 15, 0},
 {0,  15, 0,  15, 15, 0,  15, 0}
 },
 { // ghost looking right
 {0,  0,  0,  15, 15, 0,  0,  0},
 {0,  0,  15, 15, 15, 15, 0,  0},
 {0,  15, 15, 16, 15, 16, 15, 0},
 {0,  15, 15, 16, 15, 16, 15, 0},
 {0,  15, 15, 15, 15, 15, 15, 0},
 {0,  15, 15, 15, 16, 15, 15, 0},
 {0,  15, 15, 15, 15, 15, 15, 0},
 {0,  15, 0,  15, 15, 0,  15, 0}
 }
 };

/*
 {{0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0}} */

void Sketch::begin()
{
  image_index = 0;
}


/*bool Sketch::step(float nx, float ny, float nz)
{
  const uint32_t now = millis();
  if (now - last_time_change > (1000ul / speed)) {
    image_index +=1;
    if (image_index >= IMAGES) {
      image_index = 0;
    }
    board.setimage(palette, pixels[image_index]);
    last_time_change = now;
  }
  // never force redraw
  return false;
} */
bool Sketch::step(float nx, float ny, float nz)
{
  const uint32_t now = millis();
  //int image_choice[] = {0,1,0,1,2,3,2,3,4,5,4,5};
  if (now - last_time_change > (1000ul / speed)) {
    image_index +=1;
    if (image_index >= IMAGES) {
      image_index = 0;
    }
    //board.setimage(palette, pixels[image_choice[image_index]]);
    board.setimage(palette, pixels[image_index]);
    last_time_change = now;
  }
  // never force redraw
  return false;
}

void Sketch::draw(RGBMatrix &matrix)
{
  board.paint(matrix);
  
}
