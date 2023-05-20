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

    VInt& operator>>=(size_t x);
    VInt& operator<<=(size_t x);
    VInt operator>>(size_t x);
    VInt operator<<(size_t x);


    bool operator<(VInt& n);
    bool operator<(VInt&& n);

    bool operator>(VInt& n);
    bool operator>(VInt&& n);

    bool operator==(VInt& n);
    bool operator==(VInt&& n);

    bool operator<=(VInt n);
    bool operator>=(VInt n);

    operator bool() const{
        for (size_t i = 0; i < mData.size(); i ++){
            if (mData[i]){
                return true;
            }
        }
        return false;
    }
    operator unsigned int() const {
        return *reinterpret_cast<const int *>(mData.data());
    }
    operator long long() const {
        return *reinterpret_cast<const long long *>(mData.data());
    }

private:
    void negate();
    VInt maxVlaue();
};
