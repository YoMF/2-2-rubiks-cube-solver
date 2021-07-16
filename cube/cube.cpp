#include "cube.h"

template <typename tp>
tp set8bits(tp var, byte value, byte index)
{
    tp assign = value;
    assign <<= 8 * index;

    tp mask = 0;                  // clear all bits;
    mask |= ((1 << 8) - 1);       // set last 8 bits;
    mask = rotl(mask, 8 * index); // rotate required amount
    mask = ~mask;                 // required bits will be 0 rest all 1;

    var &= mask;
    var |= assign;

    return var;
}

template <typename tp>
uint8_t get8bits(tp var, byte index)
{
    return (var >> 8 * index);
}


void Cube::init_face() //ok
{
    for (ll i = 0; i < 6; i++)
    {
        face[i] = set8bits(face[i], i + 1, 0);
        face[i] = set8bits(face[i], i + 1, 1);
        face[i] = set8bits(face[i], i + 1, 2);
        face[i] = set8bits(face[i], i + 1, 3);
    }
}

void Cube::init_seq() // ok
{
    for (ll i = 0; i < 3; i++)
    {
        for (ll j = 7; j >= 0; j--)
        {
            seq[i] = set8bits(seq[i], get8bits(face[msf[i][(7 - j) / 2]], fs[ms[i][7 - j]]), j);
        }
    }
}

void Cube::read_face_to_seq(byte i)
{
    for (ll j = 7; j >= 0; j--)
    {
        seq[i] = set8bits(seq[i], get8bits(face[msf[i][(7 - j) / 2]], fs[ms[i][7 - j]]), j);
    }
}

void Cube::write_seq_to_face(byte i) // ok
{
    for (ll j = 7; j >= 0; j--)
    {
        face[msf[i][(7 - j) / 2]] = set8bits(face[msf[i][(7 - j) / 2]], get8bits(seq[i], j), fs[ms[i][7 - j]]);
    }
}

void Cube::rotate_face(byte index, bool clockwise) //ok
{
    if (clockwise)
        face[index] = rotr(face[index], 8);
    else
        face[index] = rotl(face[index], 8);
}

void Cube::rotate_seq(byte index, bool clockwise) //ok
{
    read_face_to_seq(index);

    if (clockwise)
    {
        seq[index] = rotr(seq[index], 16);
    }
    else
    {
        seq[index] = rotl(seq[index], 16);
    }

    write_seq_to_face(index);
}

void Cube::update_key()
{
    this->key = 0;
    uint8_t mask = 0;
    for (ll i = 0; i < 6; i++)
    {
        for (ll j = 0; j < 4; j++)
        {
            this->key <<= 3;
            mask = get8bits(face[i], j);
            this->key |= mask;
        }
    }
}

char Cube::rf(byte f, byte i) { return tc(get8bits(face[f], fs[i])); } // ok


Cube::Cube()
{
    ftoi['U'] = 0;
    ftoi['F'] = 1;
    ftoi['L'] = 2;
    ftoi['D'] = 3;
    ftoi['B'] = 4;
    ftoi['R'] = 5;
    init_face();
    init_seq();
}

uint128_t Cube::get_key()
{
    update_key();
    return this->key;
}

void Cube::print_cube_flat()
{
    std::string line[6];

    line[0] += "        ";
    line[0] += rf(B, 0);
    line[0] += " ";
    line[0] += rf(B, 1);

    line[1] += "        ";
    line[1] += rf(B, 2);
    line[1] += " ";
    line[1] += rf(B, 3);

    line[2] += "    ";
    byte arr[4] = {L, U, R, D};
    for (auto i : arr)
    {
        line[2] += rf(i, 0);
        line[2] += " ";
        line[2] += rf(i, 1);
        line[2] += " ";
    }

    line[3] += "    ";
    for (auto i : arr)
    {
        line[3] += rf(i, 2);
        line[3] += " ";
        line[3] += rf(i, 3);
        line[3] += " ";
    }

    line[4] += "        ";
    line[4] += rf(F, 0);
    line[4] += " ";
    line[4] += rf(F, 1);

    line[5] += "        ";
    line[5] += rf(F, 2);
    line[5] += " ";
    line[5] += rf(F, 3);

    std::cout << "======= CUBE +++++++\n\n";
    for (auto i : line)
        std::cout << i << '\n';
    std::cout << "\n\n";
}

void Cube::rotate(byte face)
{
    switch (face)
    {
    case U: // ok
    {
        rotate_face(D, false);
        rotate_seq(0, false);
        break;
    }
    case F: // ok
    {
        rotate_face(B, false);
        rotate_seq(1, false);
        break;
    }
    case L: // ok
    {
        rotate_face(R, false);
        rotate_seq(2, false);
        break;
    }
    case D:
    {
        rotate_face(D, true);
        rotate_seq(0, true);
        break;
    }
    case B:
    {
        rotate_face(B, true);
        rotate_seq(1, true);
        break;
    }
    case R:
    {
        rotate_face(R, true);
        rotate_seq(2, true);
        break;
    }
    default:
    {
        std::cout << "Rotate Face value Error\n";
        break;
    }
    }
}

void Cube::key_to_cube(uint128_t k)
{
    uint8_t mask;
    for (ll i = 5; i >= 0; i--)
    {
        for (ll j = 3; j >= 0; j--)
        {
            mask = k & 7;
            face[i] = set8bits(face[i], mask, j);
            k >>= 3;
        }
    }
}

void Cube::key_to_cube(const char *key, ll n)
{
    uint128_t k = 0;
    uint8_t mask = 0;
    for (ll i = 0; i < n; i++)
    {
        k <<= 3;
        mask = (key[i] - '0');
        k |= mask;
    }
    key_to_cube(k);
}

std::string Cube::key_to_string(uint128_t key)
{
    char mask;
    std::string res;
    ll i = 24;
    while (i--)
    {
        mask = key & 7;
        mask = (char)(mask + '0');
        res += mask;
        key >>= 3;
    }
    std::reverse(res.begin(), res.end());
    return res;
}