#include "pocket_cube_BFS.h"

// 3 different ways to spin -3 different angles - 2 different sides Totally 18 different moves
void spin(int way, int cubicles[], int orientations[], int side, int degrees) {

  int temp, i, k, m;
  
  if (way == horizontally) {
    int index = side * 4;
    if (degrees == degrees_90) {
      temp = cubicles[index];
      cubicles[index] = cubicles[index + 1];
      cubicles[index + 1] = cubicles[index + 3];
      cubicles[index + 3] = cubicles[index + 2];
      cubicles[index + 2] = temp;
    } else if (degrees == degrees_180) {
      temp = cubicles[index];
      cubicles[index] = cubicles[index + 3];
      cubicles[index + 3] = temp;
      temp = cubicles[index + 1];
      cubicles[index + 1] = cubicles[index + 2];
      cubicles[index + 2] = temp;
    } else if (degrees == degrees_270) {
      temp = cubicles[index];
      cubicles[index] = cubicles[index + 2];
      cubicles[index + 2] = cubicles[index + 3];
      cubicles[index + 3] = cubicles[index + 1];
      cubicles[index + 1] = temp;
    }
    for (i = 0; i < 4; i++) {
      orientations[cubicles[index + i] - 1] = get_orient(orientations[cubicles[index + i] - 1], horizontally,
                                                            degrees);
    }
  } else if (way == vertically) {
    int index = side * 2;
    if (degrees == degrees_90) {
      temp = cubicles[index + 4];
      cubicles[index + 4] = cubicles[index];
      cubicles[index] = cubicles[index + 1];
      cubicles[index + 1] = cubicles[index + 5];
      cubicles[index + 5] = temp;
    } else if (degrees == degrees_180) {
      temp = cubicles[index];
      cubicles[index] = cubicles[index + 5];
      cubicles[index + 5] = temp;
      temp = cubicles[index + 1];
      cubicles[index + 1] = cubicles[index + 4];
      cubicles[index + 4] = temp;
    } else if (degrees == degrees_270) {
      temp = cubicles[index];
      cubicles[index] = cubicles[index + 4];
      cubicles[index + 4] = cubicles[index + 5];
      cubicles[index + 5] = cubicles[index + 1];
      cubicles[index + 1] = temp;
    }
    for (i = 0; i < 4; i++) {
      orientations[cubicles[index + vertical_spin_row[i]] - 1] = get_orient(
        orientations[cubicles[index + vertical_spin_row[i]] - 1], vertically, degrees);
    }
  } else if (way == sideways) {
    if (degrees == degrees_90) {
      temp = cubicles[side];
      cubicles[side] = cubicles[side + 4];
      cubicles[side + 4] = cubicles[side + 6];
      cubicles[side + 6] = cubicles[side + 2];
      cubicles[side + 2] = temp;
    } else if (degrees == degrees_180) {
      temp = cubicles[side];
      cubicles[side] = cubicles[side + 6];
      cubicles[side + 6] = temp;
      temp = cubicles[side + 4];
      cubicles[side + 4] = cubicles[side + 2];
      cubicles[side + 2] = temp;
    } else if (degrees == degrees_270) {
      temp = cubicles[side];
      cubicles[side] = cubicles[side + 2];
      cubicles[side + 2] = cubicles[side + 6];
      cubicles[side + 6] = cubicles[side + 4];
      cubicles[side + 4] = temp;
    }
    for (i = 0; i < 8; i += 2) {
      orientations[cubicles[side + i] - 1] = get_orient(orientations[cubicles[side + i] - 1], sideways, degrees);
    }
  }
}

//Calculate one symmetry at a time , calculating whether the instance
//has been already hashed under a different symmetry
void calc_symmetries(int cubicles[], int orientations[], int symmetry) {
  int m;
  //6 H90
  if (symmetry == 6) {
    spin(horizontally, cubicles, orientations, 0, degrees_90);
    spin(horizontally, cubicles, orientations, 1, degrees_90);
  }
    //9 H180
  else if (symmetry == 9) {
    spin(horizontally, cubicles, orientations, 0, degrees_180);
    spin(horizontally, cubicles, orientations, 1, degrees_180);
  }
    //3 H270
  else if (symmetry == 3) {
    spin(horizontally, cubicles, orientations, 0, degrees_270);
    spin(horizontally, cubicles, orientations, 1, degrees_270);
  }
    // 14 16 19 23 V90
  else if ((symmetry == 14) || (symmetry == 16) || (symmetry == 19) || (symmetry == 23)) {
    spin(vertically, cubicles, orientations, 0, degrees_90);
    spin(vertically, cubicles, orientations, 1, degrees_90);
    if (symmetry == 19) {
      spin(horizontally, cubicles, orientations, 0, degrees_90);
      spin(horizontally, cubicles, orientations, 1, degrees_90);
    } else if (symmetry == 23) {
      spin(horizontally, cubicles, orientations, 0, degrees_180);
      spin(horizontally, cubicles, orientations, 1, degrees_180);
    } else if (symmetry == 16) {
      spin(horizontally, cubicles, orientations, 0, degrees_270);
      spin(horizontally, cubicles, orientations, 1, degrees_270);
    }
  }
    // 12- 15 V180
  else if ((symmetry == 15) || (symmetry == 12)) {
    spin(vertically, cubicles, orientations, 0, degrees_180);
    spin(vertically, cubicles, orientations, 1, degrees_180);
    if (symmetry == 12) {
      spin(horizontally, cubicles, orientations, 0, degrees_90);
      spin(horizontally, cubicles, orientations, 1, degrees_90);
    }
  }
    //1-5-8-10 V270
  else if ((symmetry == 5) || (symmetry == 1) || (symmetry == 8) || (symmetry == 10)) {
    spin(vertically, cubicles, orientations, 0, degrees_270);
    spin(vertically, cubicles, orientations, 1, degrees_270);
    if (symmetry == 1) {
      spin(horizontally, cubicles, orientations, 0, degrees_90);
      spin(horizontally, cubicles, orientations, 1, degrees_90);
    } else if (symmetry == 8) {
      spin(horizontally, cubicles, orientations, 0, degrees_180);
      spin(horizontally, cubicles, orientations, 1, degrees_180);
    } else if (symmetry == 10) {
      spin(horizontally, cubicles, orientations, 0, degrees_270);
      spin(horizontally, cubicles, orientations, 1, degrees_270);
    }
  }
    // 2-4-7-11 S90
  else if ((symmetry == 7) || (symmetry == 2) || (symmetry == 4) || (symmetry == 11)) {
    spin(sideways, cubicles, orientations, 0, degrees_90);
    spin(sideways, cubicles, orientations, 1, degrees_90);
    if (symmetry == 11) {
      spin(horizontally, cubicles, orientations, 0, degrees_90);
      spin(horizontally, cubicles, orientations, 1, degrees_90);
    } else if (symmetry == 4) {
      spin(horizontally, cubicles, orientations, 0, degrees_180);
      spin(horizontally, cubicles, orientations, 1, degrees_180);
    } else if (symmetry == 2) {
      spin(horizontally, cubicles, orientations, 0, degrees_270);
      spin(horizontally, cubicles, orientations, 1, degrees_270);
    }
  }
    //18-21 S180
  else if ((symmetry == 18) || (symmetry == 21)) {
    spin(sideways, cubicles, orientations, 0, degrees_180);
    spin(sideways, cubicles, orientations, 1, degrees_180);
    if (symmetry == 21) {
      spin(horizontally, cubicles, orientations, 0, degrees_90);
      spin(horizontally, cubicles, orientations, 1, degrees_90);
    }
  }
    //13-17-20-22 S270
  else if ((symmetry == 13) || (symmetry == 17) || (symmetry == 20) || (symmetry == 22)) {
    spin(sideways, cubicles, orientations, 0, degrees_270);
    spin(sideways, cubicles, orientations, 1, degrees_270);
    if (symmetry == 20) {
      spin(horizontally, cubicles, orientations, 0, degrees_90);
      spin(horizontally, cubicles, orientations, 1, degrees_90);
    } else if (symmetry == 22) {
      spin(horizontally, cubicles, orientations, 0, degrees_180);
      spin(horizontally, cubicles, orientations, 1, degrees_180);
    } else if (symmetry == 17) {
      spin(horizontally, cubicles, orientations, 0, degrees_270);
      spin(horizontally, cubicles, orientations, 1, degrees_270);
    }
  }
}

// Hash the positions of each cubicle
int hash_cubis(const int *h_cubicles) {
  int i, j, sum_cubs = 0;
  int n = cubicles_num;
  int cubicles[cubicles_num];
  for (i = 0; i < cubicles_num; i++) {
    cubicles[i] = h_cubicles[i];
  }

  for (i = 0; i < n - 1; i++) {
    sum_cubs += (cubicles[i] - 1) * (factorials[(n - 1) - i]);
    for (j = i + 1; j < n - 1; j++) {
      if (cubicles[j] > cubicles[i])
       cubicles[j]--; // this is tricky because now we will returned a changed cubicles array.
    }
  }
  assert(sum_cubs < 40320);
  return sum_cubs;
}

// Hash the orientation of each cubicle
int hash_orients(const int *orientations) {

  int i, k, j, sum_ors = 0;
  int n = cubicles_num;
  for (i = 0; i < n; i++) {
    sum_ors += (orientations[i] % 3) * (pow(3, i));
  }
  assert(sum_ors < 6561);
  return sum_ors;

}

// Given the hashing code generate the instance of the cubicles and their orientations
reverse_hash(int cubicles[], int orientations[], int code) {
  int sum_cubs, sum_ors, i, j, k, l, m, pos;
  int n = cubicles_num;
  int raising_positions[7] = {-1, -1, -1, -1, -1, -1, -1};
  bool found;
  sum_cubs = code / 6561;
  sum_ors = code % 6561;
  for (i = 0; i < n; i++) {
    k = n - 1 - i;
    cubicles[i] = (sum_cubs / factorials[k]) + 1;
    sum_cubs = sum_cubs - ((cubicles[i] - 1) * factorials[k]);
    pos = 0;
    for (m = 0; m < 7; m++) { raising_positions[m] = -1; }
    for (j = 0; j < i; j++) {
      for (l = 0; l < i; l++) {
        if (cubicles[i] >= cubicles[l]) {
          found = false;
          for (m = 0; m < 7; m++) { if (l == raising_positions[m]) { found = true; }}
          if (found == false) {
            cubicles[i]++;
            raising_positions[pos] = l;
            pos++;
          }
        }
      }
    }
  }

  for (i = 0; i < n; i++) {
    k = n - 1 - i;
    orientations[k] = (int) (sum_ors / (pow(3, k)));

    sum_ors = (int) (sum_ors - (orientations[k] * (pow(3, k))));
  }

  //make the orients range 0 to 5
  for (i = 0; i < 4; i++) {
    if (orientations[cubicles[back_cubes[i]] - 1] == front_or)  orientations[cubicles[back_cubes[i]] - 1] = back_or;
    if (orientations[cubicles[right_cubes[i]] - 1] == left_or)  orientations[cubicles[right_cubes[i]] - 1] = right_or;
    if (orientations[cubicles[bot_cubes[i]] - 1] == top_or)  orientations[cubicles[bot_cubes[i]] - 1] = bot_or;
  }

}


//-----------------MOVE FUNCTION------------------------
bool move(bool **hash_table, const int *cubicles, const int *orientations, int *next_reverse, int *size) {
  int i, j, k, m, row, collumn, way, symmetry, degrees, side;
  int test_fact = 1;
  bool hashed = false;
  bool instance_found = false;
  int move_cubicles[8], move_orientations[8], sym_cubicles[8], sym_orientations[8];
  //9 diferent kinds of moves vertical-sideways-horizontal for 90 180 and 270 degrees each
  for (way = 0; way <= horizontally; way++) {
    for (degrees = 0; degrees <= degrees_270; degrees++) {
      for (i = 0; i < 8; i++) {
        move_cubicles[i] = cubicles[i];
        move_orientations[i] = orientations[i];
      }
      spin(way, move_cubicles, move_orientations, 0, degrees);
      instance_found = false;
      symmetry = 0;
      // There are 24 symmetries in the cube. For every symmetry only one instance should be hashed
      // So for every given instance we check whether it is already hashed
      while ((symmetry < 24) && (instance_found == false)) {
        for (i = 0; i < 8; i++) {
          sym_cubicles[i] = move_cubicles[i];
          sym_orientations[i] = move_orientations[i];
        }
        calc_symmetries(sym_cubicles, sym_orientations, symmetry);
        row = hash_cubis(sym_cubicles);
        collumn = hash_orients(sym_orientations);
        if (hash_table[row][collumn] == true) { instance_found = true; }
        symmetry++;
      }
      //If neither the instance nor any of its symmetrics is hashed then hash and save its code for reverse hashing
      if (instance_found == false) {
        row = hash_cubis(move_cubicles);
        collumn = hash_orients(move_orientations);
        debug(move_cubicles, move_orientations);
        hash_table[row][collumn] = true;
        hashed = true;
        (*size)++;
        next_reverse[(*size) - 1] = row * 6561 + collumn;
      }
    }
  }
  return hashed;
}

//DEBUGGING FUNCTION
void debug(const int *cubicles, const int *orientations) {
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

//initialize the hash table to all falses
//an array dynamically allocated would actually require to save the code
void initial(bool ***hash_table) {
  int i, k, j;
  *hash_table = (bool **) malloc(sizeof(bool *) * 40320);
  for (i = 0; i < 40320; i++) {
    (*hash_table)[i] = (bool *) malloc(sizeof(bool) * 6561);
  }
  for (i = 0; i < 40320; i++) {
    for (j = 0; j < 6561; j++) {
      (*hash_table)[i][j] = false;
    }
  }
  (*hash_table)[0][0] = true;

  for (i = 0; i < cubicles_num; i++) {
    factorials[i] = factorial(i);
  }
}


int factorials[cubicles_num]; // keep them memoized to avoid calculating them repeatedly
//----------------MAIN FUNCTION----------------
int main(void)
//we begin hashing the initial starting position. we make 9 moves for each instance that has been
//hashed the last move starting with 1 instance in move 0. So in every move we explore for the last
//move's instances 9 moves thus the breadth first search. For example in move 1 we explore 1x9 instances hashing all 9
//while in move 2 we explore 9x9=81 instances hashing only 54. The reason why an instance may not be hashed is
//because it may be already hashed or a symmetric instance may allready be hashed. The move returns a code for every hashed
//instance in a way that we can perform a reverse hash extracting each instance in order to explore the 9 possible moves for it.
//There are to reverse hash arrays one that saves the previous move's hashed instances and one that saves the current move's
//hashed instances.For example in move 1 we save 9 instances codes in array new_reverse then we copy those instances to the array reverse
//in order to feed the move function with instances and to save the codes for the 54 instances that get hashed in move 2.
{
  int i, j, size, new_size;
  int cubicles[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int orientations[8] = {0, 0, 0, 0, 3, 3, 3, 3};
  bool **hash_table;//[40320][6561];
  int *reverse = calloc(MAX_SIZE, sizeof(int));
  int *next_reverse = calloc(MAX_SIZE, sizeof(int));
  int moves = 0;
  bool hashed, any_hashed;
  initial(&hash_table);

  size = 1;
  // perform the BFS algorithm
  do {
    moves++;
    printf("MOVE = %d \n", moves);
    any_hashed = false;
    new_size = 0;
    for (i = 0; i < size; i++) {
      if (i == 0) printf("size = %d for move %d \n", size, moves);
      reverse_hash(cubicles, orientations, reverse[i]);
      hashed = move(hash_table, cubicles, orientations, next_reverse, &new_size);
      if (hashed == true) { any_hashed = true; }
      if (moves > 5) {
        for (j = 1; j < 8; j++) {
          if (i == ((j * size) / 8)) {
            printf("%d/%d size = %d\n", j, 8, new_size);
          }
        }
      }
    }
    //"copy" the new reverse array
    reverse = next_reverse;
    size = new_size;
    //if (any_hashed == true){printf("Hashed something in the move %d\n",moves);}
  } while (any_hashed == true);
  printf("THE GODS NUMBER IS %d \n", moves - 1);
  int sum = 0;
  for (i = 0; i < 40320; i++) {
    for (j = 0; j < 6561; j++) {
      if (hash_table[i][j] == true) {
        sum++;
      }
    }
  }
  printf("\n sum of hashed spots= %d", sum);
}
    