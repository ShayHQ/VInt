#include <vector>

typedef unsigned char uchar;

class VInt{
    std::vector<uchar> mData;
public:
    VInt() : mData(sizeof(int)){}
    VInt(unsigned int n);
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

    VInt& operator&=(VInt n);
    VInt operator&(VInt n);

    VInt& operator|=(VInt n);
    VInt operator|(VInt n);

    VInt& operator^=(VInt n);
    VInt operator^(VInt n);
    

    VInt operator*(VInt& n);
    VInt operator*(VInt&& n);
    VInt& operator*=(VInt n);

    bool operator<(VInt& n);
    bool operator<(VInt&& n);

    bool operator>(VInt& n);
    bool operator>(VInt&& n);

    bool operator==(VInt n);

    bool operator<=(VInt n);
    bool operator>=(VInt n);

    explicit operator bool() const{
        for (size_t i = 0; i < mData.size(); i ++){
            if (mData[i]){
                return true;
            }
        }
        return false;
    }
    explicit operator unsigned int() const {
        return *reinterpret_cast<const unsigned int *>(mData.data());
    }
    explicit operator int() const {
        return *reinterpret_cast<const int *>(mData.data());
    }
    explicit operator unsigned long long() const {
        unsigned char res[sizeof( unsigned long long)] = {0};
        size_t c = sizeof( unsigned long long);

        for (size_t i = 0; i < std::min(mData.size(), c); i ++){
            res[i] = mData[i];
        }
        return * reinterpret_cast<const unsigned long long*>(res);
    }

private:
    void negate();
    VInt maxVlaue();
};
