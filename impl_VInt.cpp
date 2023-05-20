#include "VInt.h"
#include <limits>
using namespace std;

#ifdef WIN32
#define int128 size_t
#endif
#ifdef __unix__
#define int128 long double
#endif

VInt::VInt(unsigned int n) : mData(sizeof(int)){
    unsigned int *p = reinterpret_cast<unsigned int*>(mData.data());
    *p = n;
}


VInt::VInt(VInt& n){
    *this = n;
}

VInt::VInt(VInt&& n){
    *this = n;
}

VInt& VInt::operator=(VInt& n){
    mData = n.mData;
    return *this;
}
VInt& VInt::operator=(VInt&& n){
    mData = std::move(n.mData);
    return *this;
}


VInt& VInt::operator+=(VInt& n){
    unsigned short window{0};
    int i = 0;
    while (window || i < mData.size() || i < n.mData.size())
    {
        unsigned char a{0}, b{0};
        if (i < mData.size()){
            a = mData[i];
        }
        if (i < n.mData.size()){
            b = n.mData[i];
        }
        if (i >= mData.size()){
            mData.push_back(0);
        }
        window += a + b;
        mData[i] = static_cast<uchar>(window);
        window >>= sizeof(uchar)*8;
        i++;
    }
    
    return *this;
}
VInt& VInt::operator+=(VInt&& n){
    VInt ntmp(n);
    (*this) += ntmp;
    return *this;
}

VInt VInt::operator+(VInt& n){
    VInt res = *this;
    res += n;
    return res;
}
VInt VInt::operator+(VInt&& n){
    VInt res = *this;
    res += n;
    return res;
}


void VInt::negate(){
    VInt negative1 = maxVlaue();
    VInt res = *this + negative1;
    res.mData.resize(mData.size());
    for (int i = 0; i < mData.size(); i ++){
        negative1.mData[i] -= res.mData[i];
    }
    *this = negative1;
}
VInt VInt::maxVlaue(){
    VInt res;
    res.mData = std::vector<uchar>(mData.size(), -1);
    return res;
}


VInt& VInt::operator-= (VInt& n){
    VInt tmp(n);
    size_t s = mData.size();
    tmp.negate();
    *this += tmp;
    mData.resize(s);
    return *this;
    
}
VInt& VInt::operator-= (VInt&& n){
    VInt tmp(n);
    *this -= tmp;
    return *this;
}
VInt VInt::operator-(VInt& n){
    VInt res = *this;
    res -= n;
    return res;
}
VInt VInt::operator-(VInt&& n){
    VInt res = *this;
    res -= n;
    return res;
}


VInt& VInt::operator>>=(size_t x){
    int128 bitsCount = mData.size()*8;
    if (bitsCount == x){
        *this = 0;
    }else if (x > 0){
        size_t wholeBytesCount = x/8;
        if (wholeBytesCount){
            for (size_t i = wholeBytesCount; i < mData.size(); i++){
                mData[i-wholeBytesCount] = mData[i];
            }
        }
        if (x%8){
            for (size_t i = 0; i < mData.size()-1; i ++){
                unsigned short n = *reinterpret_cast<unsigned short*>(mData.data()+i);
                n >>= x%8;
                mData[i] = static_cast<uchar>(n);
            }
            mData[mData.size()-1] >>= x%8;
        }
    }
    return *this;
}
VInt& VInt::operator<<=(size_t x){
    int128 bitsCount = numeric_limits<size_t>::max()*8;
    if (bitsCount == x){
        *this = 0;
    }else if (x > 0){
        size_t wholeBytesCount = x/8;
        int n = mData.size(), reservedBytes = 0;
        if (wholeBytesCount){
            for (size_t i = n-1; i >= 0; i --){
                if (mData[i]){
                    break;
                }
                reservedBytes++;
                n--;
            }
            if (wholeBytesCount > reservedBytes){
                mData.resize(mData.size() + wholeBytesCount - reservedBytes+1);
            }
            for (size_t i = n-1; i >= 0 && i <= n-1; --i){
                mData[i+wholeBytesCount] = mData[i];
            }
            for (size_t i = 0; i < wholeBytesCount; i ++){
                mData[i] = 0;
            }
        }
        if (x%8){
            size_t vecSize = mData.size();
            unsigned short n = *reinterpret_cast<unsigned char*>(mData.data()+mData.size()-1);
            n = (n << (x%8)) >> 8;
            if (n){
                mData.push_back(n);
            }
            
            for (size_t i = vecSize-2; i >= 0 && i <= vecSize-1; i --){
                unsigned short n = *reinterpret_cast<unsigned short*>(mData.data()+i);
                n <<= x%8;
                mData[i+1] = static_cast<uchar>(n >> 8);
            }
            mData[0] <<= x%8;
        }
    }
    return *this;
}
VInt VInt::operator>>(size_t x){
    VInt res(*this);
    res >>= x;
    return res;
}
VInt VInt::operator<<(size_t x){
    VInt res(*this);
    res <<= x;
    return res;
}


bool VInt::operator<(VInt& n){
    if (mData.size() != n.mData.size()){
        if (mData.size() < n.mData.size()){
            for (size_t i = n.mData.size()-1; i > mData.size(); i --){
                if (n.mData[i]){
                    return true;
                }
            }
        }else{
            for (size_t i = mData.size()-1; i > n.mData.size(); i --){
                if (mData[i]){
                    return false;
                }
            }
        }
    }
    for (size_t i = mData.size()-1; i >= 0 && i < mData.size(); i --){
        if (n.mData[i] != mData[i]){
            return n.mData[i] > mData[i];
        }
    }
    return false;
}

bool VInt::operator<(VInt&& n){
    VInt tmp = n;
    return *this < tmp;
}

bool VInt::operator>(VInt& n){
    if (mData.size() != n.mData.size()){
        if (mData.size() < n.mData.size()){
            for (size_t i = n.mData.size()-1; i > mData.size(); i --){
                if (n.mData[i]){
                    return false;
                }
            }
        }else{
            for (size_t i = mData.size()-1; i > n.mData.size(); i --){
                if (mData[i]){
                    return true;
                }
            }
        }
    }
    for (size_t i = mData.size()-1; i >= 0 && i < mData.size(); i --){
        if (n.mData[i] != mData[i]){
            return n.mData[i] < mData[i];
        }
    }
    return false;
}
bool VInt::operator>(VInt&& n){
    VInt tmp = n;
    return *this > tmp;
}

bool VInt::operator==(VInt n){
    std::size_t maxS = max(n.mData.size(), mData.size());
    for (size_t i = 0; i < maxS-1; i ++){
        if (mData[i] != n.mData[i]){
            return false;
        }
    }
    if (mData.size() > n.mData.size()){
        for (size_t i = n.mData.size(); i < mData.size(); i ++){
            if (mData[i]){
                return false;
            }
        }
    }else if (mData.size() < n.mData.size()){
        for (size_t i = mData.size(); i < n.mData.size(); i ++){
            if (n.mData[i]){
                return false;
            }
        }
    }
    return true;
}

bool VInt::operator<=(VInt n){
    return *this == n || *this < n;
}
bool VInt::operator>=(VInt n){
    return *this == n || *this > n;
}
