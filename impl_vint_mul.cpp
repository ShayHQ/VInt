#include "VInt.h"
    
VInt VInt::operator*(VInt& n){
    VInt res = *this;
    res *= n;
    return res;
}
VInt VInt::operator*(VInt&& n){
    VInt res = *this;
    res *= n;
    return res;
}
VInt& VInt::operator*=(VInt n){
    VInt origin = *this;
    *this = 0;
    for (int i = 0; i < n.mData.size()*8; i ++){
        if (n.mData[0] & 1){
            *this += origin;
        }
        n >>= 1;
        origin <<= 1;
    }
    return *this;
}
