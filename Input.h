#ifndef INPUT_H
#define INPUT_H

struct Input {
    bool left;
    bool right;
    bool up;
    bool down;
    bool space, space_held;
    bool r;
};

void process_input(Input& in);

#endif