#include <iostream>
#include <string>

using ll = long long int;
using byte = unsigned char;
using uint128_t = __uint128_t;

#define tc(a) (char)((a) + '0')
#define rotl(var, shift) (((var) << (shift)) | ((var) >> (sizeof(var) * 8 - (shift))))
#define rotr(var, shift) (((var) >> (shift)) | ((var) << (sizeof(var) * 8 - (shift))))

template <typename tp>
extern tp set8bits(tp var, byte value, byte index);

template <typename tp>
extern uint8_t get8bits(tp var, byte index);

class Cube
{
private:
    char itof[6] = {'U', 'F', 'L', 'D', 'B', 'R'};
    int ftoi[200];
    uint128_t key;
    uint32_t face[6];
    uint64_t seq[3];  // D,B,R

    const byte fs[4] = {3, 2, 0, 1};                                                                      // gives the index of element in the variable.
    const byte ms[3][8] = {{0, 1, 2, 0, 3, 2, 1, 3}, {1, 0, 1, 0, 1, 0, 1, 0}, {3, 1, 3, 1, 3, 1, 0, 2}}; // elements in the sequence.
    const byte msf[3][4] = {{B, L, F, R}, {D, R, U, L}, {F, U, B, D}};                                    // faces of respective elements.

    void init_face();

    void init_seq();

    void read_face_to_seq(byte i);

    void write_seq_to_face(byte i);

    void rotate_face(byte index, bool clockwise);

    void rotate_seq(byte index, bool clockwise);

    void update_key();

    char rf(byte f, byte i);

public:
    enum fcs
    {
        U,
        F,
        L,
        D,
        B,
        R
    } faces;

    Cube();

    uint128_t get_key();

    void print_cube_flat();

    void rotate(byte face);

    void key_to_cube(uint128_t k);

    void key_to_cube(const char *key, ll n);

    std::string key_to_string(uint128_t k);
};
