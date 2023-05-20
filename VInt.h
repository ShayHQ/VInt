#include <vector>

typedef unsigned char uchar;

class VInt{
    std::vector<uchar> mData;
public:
    VInt() : mData(sizeof(int)){}
    VInt(int n);
    VInt(VInt& n);
    VInt(VInt&& n);

    VInt& operator=(VInt& n);
    VInt& operator=(VInt&& n);

    VInt& operator+=(VInt& n);
    VInt& operator+=(VInt&& n);
    VInt operator+(VInt& n);
    VInt operator+(VInt&& n);

    VInt& operator-= (VInt& n);
    VInt& operator-= (VInt&& n);
    VInt operator-(VInt& n);
    VInt operator-(VInt&& n);

private:
    void negate();
    VInt maxVlaue();
};
