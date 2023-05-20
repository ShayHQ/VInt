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
VInt& VInt::operator*=(VInt& n){
    return *this;
}
VInt& VInt::operator*=(VInt&& n){
    VInt tmp = n;
    *this *= tmp;
    return *this;
}