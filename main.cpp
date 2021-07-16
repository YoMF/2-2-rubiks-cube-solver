#include "cube/cube.h"
#include "bar.h"
#include <map>
#include <queue>
#include <fstream>
#include <cstring>
#include <algorithm>


static char itof[6] = {'U', 'F', 'L', 'D', 'B', 'R'}; // integer to face value


static void compliment(char *sol, ll n, char *comp) // inplace
{
    while (n--)
    {
        sol[n] = comp[sol[n]];
    }
}

static void strrev(char *seq, ll n) // inplace
{
    ll i = n / 2;
    while (i--)
    {
        std::swap(seq[i], seq[n - (i + 1)]);
    }
}




class Bfs
{
private:
    std::queue<uint128_t> queue;
    std::map<uint128_t, std::string> bst;

    Cube &cube;
    const ll MAX = 4e6;
    const ll TOTAL = 3674160;

public:
    Bfs(Cube &C) : cube(C)
    {
        ;
    }

    void run()
    {

        uint128_t key;
        key = cube.get_key();
        Bar b(50);

        queue.push(key);
        bst.insert(std::make_pair(key, std::string()));

        while (!queue.empty())
        {
            cube.key_to_cube(queue.front());
            std::string &csoln = bst[queue.front()];

            for (ll i = 0; i < 6; i++)
            {
                cube.rotate(i);

                key = cube.get_key();
                if (bst.count(key) == 0)
                {
                    queue.push(key);
                    csoln.push_back(itof[i]);
                    bst.insert(std::make_pair(key, csoln));
                    csoln.pop_back();
                }

                cube.rotate((i + 3) % 6);
            }

            queue.pop();

            float percent = ((float)bst.size() / TOTAL) * 100;
            b.update(percent);          
        }

        std::cout << std::endl;
    }

    void results()
    {
        std::cout << "\n----Results----\n";
        ll n = bst.size();
        std::cout << "Total:" << bst.size() << '\n';

        ll arr[15];
        memset(arr, 0, sizeof(arr));

        for (auto i : bst)
        {
            arr[i.second.size()]++;
        }

        for (auto i : arr)
            std::cout << i << '\n';
    }

    void write_to_disk()
    {
        char rev[200];
        rev['U'] = 'D';
        rev['D'] = 'U';
        rev['F'] = 'B';
        rev['B'] = 'F';
        rev['L'] = 'R';
        rev['R'] = 'L';

        std::cout << "Writing to Disk..\n";


        struct data
        {
            char state[25];
            char solution[15];
            char solution_length = 0;
        } wdata;

        char file[] = "wholedata.bin";
        std::ofstream OF;
        OF.open(file, std::ios::out | std::ios::binary | std::ios::trunc); // overwrites the file !!!

        int c = 0;
        for (auto i : bst)
        {
            strcpy(wdata.state, (cube.key_to_string(i.first)).c_str());
            strcpy(wdata.solution, i.second.c_str());
            wdata.solution_length = i.second.size();

            compliment(wdata.solution, wdata.solution_length, rev);
            strrev(wdata.solution, wdata.solution_length);
            OF.write((char *)&wdata, sizeof(wdata));
        }

        std::cout << '\n';

        OF.close();
    }
};


int main()
{
    Cube c;

    Bfs bfs(c);
    bfs.run();
    bfs.results();

    // bfs.write_to_disk(); // saves the solution in current working directory.
}