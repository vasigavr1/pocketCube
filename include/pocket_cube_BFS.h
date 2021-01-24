#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <stdint.h>


#define MAX_SIZE 1887748
#define ENABLE_ASSERTS 0


//degrees of spin
#define degrees_90 0
#define degrees_180 1
#define degrees_270 2
//
#define CUBICLES_NUM 8
#define MAX_SYMMETRIES 24
// spin way
#define vertically 0
#define sideways 1
#define horizontally 2
// orientations
#define top_or 0
#define front_or 1
#define left_or 2
#define bot_or 3
#define back_or 4
#define right_or 5
#define MAX(x,y) ((x) > (y) ? (x) : (y))


const int vertical_row[4] = {0, 1, 3, 4};//top-front-bot-back etc.
const int sideways_row[4] = {0, 5, 3, 2};
const int horizontal_row[4] = {1, 5, 4, 2};

const int top_cubes[4] = {0, 1, 2, 3}; //0
const int front_cubes[4] = {0, 2, 4, 6}; //1
const int left_cubes[4] = {0, 1, 4, 5}; //2
const int bot_cubes[4] = {4, 5, 6, 7};  //3
const int back_cubes[4] = {1, 3, 5, 7}; //4
const int right_cubes[4] = {2, 3, 6, 7};//5
extern int factorials[CUBICLES_NUM];


//
const int vertical_spin_row[4] = {0, 1, 4, 5};


int get_orient(int orient, int way, int degrees) {
  int i;
  bool found = false;
  if (way == vertically) {
    for (i = 0; i < 4; i++) {
      if ((orient == vertical_row[i]) && (found == false)) {
        orient = vertical_row[(i + 1 + degrees) % 4];
        found = true;
      }
    }
  } else if (way == sideways) {
    for (i = 0; i < 4; i++) {
      if ((orient == sideways_row[i]) && (found == false)) {
        orient = sideways_row[(i + 1 + degrees) % 4];
        found = true;
      }
    }
  } else if (way == horizontally) {
    for (i = 0; i < 4; i++) {
      if ((orient == horizontal_row[i]) && (found == false)) {
        orient = horizontal_row[(i + 1 + degrees) % 4];
        found = true;
      }
    }
  }
  return orient;
}


int factorial(int n) {
  assert(n < 8);
  int result = 1;
  for (int i = 1; i <= n; i++) { result = result * i; }
  return result;
}


//DEBUGGING FUNCTION
void debug(const uint8_t *cubicles, const uint8_t *orientations) {
    if (ENABLE_ASSERTS) {
        assert(orientations[cubicles[0] - 1] < 3);//cube 0  ors 0 1 2
        assert(((orientations[cubicles[1] - 1] == 0) || (orientations[cubicles[1] - 1] == 2) ||
                (orientations[cubicles[1] - 1] == 4)));//cube 1 ors 0 2 4
        assert(((orientations[cubicles[2] - 1] == 0) || (orientations[cubicles[2] - 1] == 1) ||
                (orientations[cubicles[2] - 1] == 5)));//cube 2 ors 0 1 5
        assert(((orientations[cubicles[3] - 1] == 0) || (orientations[cubicles[3] - 1] == 4) ||
                (orientations[cubicles[3] - 1] == 5)));//cube 3 ors 0 4 5
        assert(((orientations[cubicles[4] - 1] == 1) || (orientations[cubicles[4] - 1] == 2) ||
                (orientations[cubicles[4] - 1] == 3)));//cube 4 ors 1 2 3
        assert(((orientations[cubicles[5] - 1] == 2) || (orientations[cubicles[5] - 1] == 3) ||
                (orientations[cubicles[5] - 1] == 4)));//cube 5 ors 2 3 4
        assert(((orientations[cubicles[6] - 1] == 1) || (orientations[cubicles[6] - 1] == 3) ||
                (orientations[cubicles[6] - 1] == 5)));//cube 6 ors 1 3 5
        assert(orientations[cubicles[7] - 1] > 2);//cube 7 ors 3 4 5
    }
}

#endif
