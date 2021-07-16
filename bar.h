#include <iostream>
#include <iomanip>

class Bar
{
private:
    int width;
    int bpos, npos;
    bool killed;

    void move_cursor(int pos) // moves cursor to a particlar position (1 indexed)
    {
        char code[10];
        sprintf(code, "\33[%dG", pos);
        std::cout << code;
    }

    void set_format()
    {
        std::cout << "\33[?25l"; // cursor invisibe
    }

    void reset_format()
    {
        std::cout << "\33[0m";   // reset any color/font styles
        std::cout << "\33[?25h"; // cursor visible
    }

public:
    Bar(int w)
    {
        width = ((w < 50) ? w : 50);
        bpos = 2;
        killed = false;

        std::cout << std::unitbuf << std::fixed << std::setprecision(4);

        set_format();
        std::cout << "\nProgress:\n";
        std::cout << "[";

        move_cursor(bpos + width);
        std::cout << "] ";
        npos = (bpos + width + 2);
        std::cout << "0%";
    }

    void update(float per)
    {
        if (killed)
            return;

        per = (per > 100) ? 100 : ((per < 0) ? 0 : per);

        int p = ((float)per) * (width) / 100;
        p = (p - (bpos - 2));

        move_cursor(bpos);

        while (p--)
        {
            std::cout << "=";
            bpos++;
        }

        move_cursor(npos);
        std::cout << per << "%";
    }

    void finish()
    {
        if (killed)
            return;

        killed = true;
        std::cout << "\n";
        std::cout << std::nounitbuf;
        std::cout.unsetf(std::cout.fixed); 
        std::cout << std::setprecision(16);
        std::cout << std::endl;
        reset_format();
    }

    ~Bar()
    {
        finish();
    }
};