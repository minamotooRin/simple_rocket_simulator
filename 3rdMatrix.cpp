#include "3rdMatrix.h" 
#include <cstring>

matrix3d::matrix3d()
{
    memset(data, 0, sizeof(data));
    data[0][0] = 1 ;
    data[1][1] = 1 ;
    data[2][2] = 1 ; 
}

vector3d matrix3d::operator * (vector3d v)
{
    vector3d ans ; 
    ans[0] = data[0][0] * v[0] +  data[0][1] * v[1] + data[0][2] * v[2]  ;
    ans[1] = data[1][0] * v[0] +  data[1][1] * v[1] + data[1][2] * v[2]  ;
    ans[2] = data[2][0] * v[0] +  data[2][1] * v[1] + data[2][2] * v[2]  ;
    return ans;
}

vector3d& matrix3d::operator [] (unsigned long i)
{
    return data[i];
}

vector3d::vector3d()
{
    memset(data, 0, sizeof(data));
}

vector3d::vector3d(FLOAT a, FLOAT b, FLOAT c)
{
    data[0] = a;
    data[1] = b;
    data[2] = c;
}

vector3d vector3d::operator + (vector3d e) 
{
    return vector3d( data[0]+e[0] , data[1]+e[1] , data[2]+e[2] ) ;
}

vector3d vector3d::operator * (FLOAT d)
{
    return vector3d(data[0]*d , data[1]*d , data[2]*d) ; 
}

FLOAT& vector3d::operator [] (size_t i)
{
    return data[i];
}