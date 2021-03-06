#include <pocket_cube_BFS.h>


const int hash_height = 40320;
const int hash_width = 6561;

// 3 different ways to spin -3 different angles - 2 different sides Totally 18 different moves
void spin(int way, uint8_t *cubicles, uint8_t *orientations, int side, int degrees) {

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
void calc_symmetries(uint8_t *cubicles, uint8_t *orientations, int symmetry) {

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
int hash_cubis(const uint8_t *h_cubicles) {
  int i, j, sum_cubs = 0;
  int n = CUBICLES_NUM;
  int cubicles[CUBICLES_NUM];
  for (i = 0; i < CUBICLES_NUM; i++) {
    cubicles[i] = h_cubicles[i];
  }

  for (i = 0; i < n - 1; i++) {
    sum_cubs += (cubicles[i] - 1) * (factorials[(n - 1) - i]);
    for (j = i + 1; j < n - 1; j++) {
      if (cubicles[j] > cubicles[i])
       cubicles[j]--; // this is tricky because now we will returned a changed cubicles array.
    }
  }
  assert(sum_cubs < hash_height);
  return sum_cubs;
}

// Hash the orientation of each cubicle
int hash_orients(const uint8_t *orientations) {

  int i, sum_ors = 0;
  int n = CUBICLES_NUM;
  for (i = 0; i < n; i++) {
    sum_ors += (orientations[i] % 3) * (pow(3, i));
  }
  if (ENABLE_ASSERTS) assert(sum_ors < 6561);
  return sum_ors;

}

// Given the hashing code generate the instance of the cubicles and their orientations
void reverse_hash(uint8_t *cubicles, uint8_t *orientations, int code) {
  int sum_cubs, sum_ors, i, j, k, l, m, pos;
  int raising_positions[7] = {-1, -1, -1, -1, -1, -1, -1};
  bool found;
  sum_cubs = code / hash_width;
  sum_ors = code % hash_width;
  for (i = 0; i < CUBICLES_NUM; i++) {
    k = CUBICLES_NUM - 1 - i;
    cubicles[i] = (sum_cubs / factorials[k]) + 1;
    sum_cubs = sum_cubs - ((cubicles[i] - 1) * factorials[k]);
    pos = 0;
    for (m = 0; m < 7; m++) raising_positions[m] = -1;
    for (j = 0; j < i; j++) {
      for (l = 0; l < i; l++) {
        if (cubicles[i] >= cubicles[l]) {
          found = false;
          for (m = 0; m < 7; m++) { if (l == raising_positions[m]) { found = true; }}
          if (!found) {
            cubicles[i]++;
            raising_positions[pos] = l;
            pos++;
          }
        }
      }
    }
  }

  for (i = 0; i < CUBICLES_NUM; i++) {
    k = CUBICLES_NUM - 1 - i;
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

// There are 24 symmetries in the cube. For every symmetry only one instance should be hashed
// So, for every given instance we check whether it is already hashed
// Symmetry 0 refers to the move as is
bool is_a_symmetric_move_hashed(bool **hash_table,
                                const uint8_t *move_cubicles,
                                const uint8_t *move_orientations) {
    uint8_t sym_cubicles[CUBICLES_NUM], sym_orientations[CUBICLES_NUM];
    for (int sym_i = 0; sym_i < MAX_SYMMETRIES; ++sym_i) {
        memcpy(sym_cubicles, move_cubicles, CUBICLES_NUM);
        memcpy(sym_orientations, move_orientations, CUBICLES_NUM);
        calc_symmetries(sym_cubicles, sym_orientations, sym_i);
        uint32_t row = hash_cubis(sym_cubicles);
        uint32_t column = hash_orients(sym_orientations);
        if (hash_table[row][column])  {
            return true;
        }
    }
    return false;
}

//-----------------MOVE FUNCTION------------------------
bool move(bool **hash_table, const uint8_t *cubicles, const uint8_t *orientations, int *next_reverse, int *size) {
  int way, degrees, side;
  int test_fact = 1;
  bool hashed = false;
  uint8_t move_cubicles[CUBICLES_NUM], move_orientations[CUBICLES_NUM];
  //9 different kinds of moves vertical-sideways-horizontal for 90 180 and 270 degrees each
  for (way = 0; way <= horizontally; way++) {
    for (degrees = 0; degrees <= degrees_270; degrees++) {
      memcpy(move_cubicles, cubicles, CUBICLES_NUM);
      memcpy(move_orientations, orientations, CUBICLES_NUM);
      spin(way, move_cubicles, move_orientations, 0, degrees);
      //If neither the instance nor any of its symmetries is hashed then hash and save its code for reverse hashing
      if (!is_a_symmetric_move_hashed(hash_table, move_cubicles, move_orientations)) {
        int row = hash_cubis(move_cubicles);
        int column = hash_orients(move_orientations);
        debug(move_cubicles, move_orientations);
        hash_table[row][column] = true;
        hashed = true;
        (*size)++;
        next_reverse[(*size) - 1] = row * hash_width + column;
      }
    }
  }
  return hashed;
}



//initialize the hash table to all falses
//an array dynamically allocated would actually require to save the code
bool ** init_hash_table_and_factorials() {
  int i, k, j;
  bool **hash_table = (bool **) malloc(sizeof(bool *) * hash_height);
  for (i = 0; i < hash_height; i++) {
    hash_table[i] = (bool*) calloc(sizeof(bool), hash_width);
  }
  hash_table[0][0] = true;

  for (i = 0; i < CUBICLES_NUM; i++) {
    factorials[i] = factorial(i);
  }
  return hash_table;
}


int factorials[CUBICLES_NUM]; // keep them memoized to avoid calculating them repeatedly
//----------------MAIN FUNCTION----------------
int main(void)
//we begin hashing the init_hash_table_and_factorials starting position. We make 9 moves for each instance that was
//hashed in the last move. So in every move we explore for the last
//move's instances 9 moves thus the breadth first search. For example in move 1 we explore 1x9 instances hashing all 9
//while in move 2 we explore 9x9=81 instances hashing only 54. The reason why an instance may not be hashed is
//because it may be already hashed or a symmetric instance may already be hashed. The move returns a code for every hashed
//instance in a way that we can perform a reverse hash extracting each instance in order to explore the 9 possible moves for it.
//There are two reverse hash arrays one that saves the previous move's hashed instances and one that saves the current move's
//hashed instances. For example in move 1 we save 9 instances codes in array new_reverse then we copy those instances to the array reverse
//in order to feed the move function with instances and to save the codes for the 54 instances that get hashed in move 2.
{
  int i, j, size, new_size;
  uint8_t cubicles[CUBICLES_NUM] = {1, 2, 3, 4, 5, 6, 7, 8};
  uint8_t orientations[CUBICLES_NUM] = {0, 0, 0, 0, 3, 3, 3, 3};
  int *reverse = calloc(MAX_SIZE, sizeof(int));
  int *next_reverse = calloc(MAX_SIZE, sizeof(int));
  int moves = 0;
  bool hashed, any_hashed;
  bool **hash_table = init_hash_table_and_factorials();

  size = 1;
  // perform the BFS algorithm
  do {
    moves++;
    printf("MOVE = %d \n", moves);
    any_hashed = false;
    new_size = 0;
    printf("size = %d for move %d \n", size, moves);
    for (i = 0; i < size; i++) {

      reverse_hash(cubicles, orientations, reverse[i]);
      hashed = move(hash_table, cubicles, orientations, next_reverse, &new_size);

      if (hashed == true) any_hashed = true;

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
  for (i = 0; i < hash_height; i++) {
    for (j = 0; j < hash_width; j++) {
      if (hash_table[i][j] == true) {
        sum++;
      }
    }
  }
  printf("\n sum of hashed spots= %d", sum);
}
    