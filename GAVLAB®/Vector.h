#ifndef VECTOR_h
#define VECTOR_h
#include<cmath>
#include<iostream>
using namespace std;

template<class T>  class Vector;
typedef Vector<float> vector3f;
typedef Vector<double> vector3d;

template<class T >
Vector<T> operator+(const  Vector<T>& u,const  Vector<T> &v);

template<class T >
Vector<T> operator-(const Vector<T> &u, const Vector<T> &v);

template<class T > // cross production
Vector<T> operator^(const Vector<T> &u, const Vector<T> &v);

template<class T >
T operator*(const Vector<T> &u, const Vector<T> &v);

template<class T >
Vector<T> operator*(T s, const Vector<T> &u);

template<class T >
Vector<T> operator*(const Vector<T> &u,T s);

template<class T >
Vector<T> operator/(const Vector<T> &u, T s);

template<class T >
ostream& operator<<(ostream &out,const Vector<T> &u);


template<class T>
class Vector
{
public:
    explicit Vector(T a=0,T b=0,T c=0):x{a},y{b},z{c}{};
    Vector(const Vector<T>& u)=default;
    Vector(Vector<T> && u)=default;
    Vector<T>& operator=(const Vector<T> &u)=default;
    Vector<T>& operator=(Vector<T> &&u)=default;
    T Magnitude(void);
    Vector<T>  Normalize(void);
    Vector<T>  Reverse(void);
    Vector<T>& operator+=(const Vector<T> &u);	// vector addition
    Vector<T>& operator-=(const Vector<T> &u);	// vector subtraction
    Vector<T>& operator*=(T s);	// scalar multiply
    Vector<T>& operator/=(T s);	// scalar divide
    bool operator ==(const Vector<T> &u);
    bool operator !=(const Vector<T> &u);
    inline T X()const{return x;}
    inline T Y()const{return y;}
    inline T Z()const{return z;}
    friend  Vector<T> operator+<>(const  Vector<T>& u,const  Vector<T> &v);
    friend  Vector<T> operator-<>(const  Vector<T>& u,const  Vector<T> &v);
    friend	Vector<T> operator^<>(const  Vector<T>& u,const  Vector<T> &v);
    friend	T operator*<>(const  Vector<T>& u,const  Vector<T> &v);
    friend	Vector<T> operator*<>(T s, const  Vector<T>& u);
    friend	Vector<T> operator*<>(const  Vector<T>& u, T s);
    friend	Vector<T> operator/<>(const  Vector<T>& u, T s);
    friend	ostream& operator<< <>(ostream &out,const  Vector<T>& u);
    
private:
    T x,y,z;
    
};
template<class T >
T Vector<T>::Magnitude(void)
{
    return sqrt(x*x+y*y+z*z);
}
template<class T >
Vector<T> Vector<T>::Normalize(void)
{
    T length=Magnitude();
    Vector<T> temp(*this);
    if(length!=0)
        temp/=length;
    return temp;
}

template<class T >
Vector<T>  Vector<T>::Reverse(void)
{
    Vector<T> temp=-1*(*this);
    return temp;
}
template<class T >
Vector<T>& Vector<T>::operator+=(const  Vector<T>& u)
{
    x+=u.x;y+=u.y;z+=u.z;
    return *this;
}
template<class T >
Vector<T>& Vector<T>::operator-=(const  Vector<T>& u)
{
    x-=u.x;y-=u.y;z-=u.z;
    return *this;
}
template<class T >
Vector<T>& Vector<T>::operator*=(T s)
{
    x*=s;y*=s;z*=s;
    return *this;
}
template<class T >
Vector<T>& Vector<T>::operator/=(T s)
{
    x/=s;y/=s;z/=s;
    return *this;
}
template<class T >
Vector<T> operator+(const  Vector<T>& u,const  Vector<T> &v)
{
    Vector<T> temp;
    temp.x=u.x+v.x;
    temp.y=u.y+v.y;
    temp.z=u.z+v.z;
    return temp;
}
template<class T >
Vector<T> operator-(const  Vector<T>& u,const  Vector<T> &v)
{
    Vector<T> temp;
    temp.x=u.x-v.x;
    temp.y=u.y-v.y;
    temp.z=u.z-v.z;
    return temp;
}

template<class T >
Vector<T> operator^(const  Vector<T>& u,const  Vector<T> &v)
{
    Vector<T> temp;
    temp.x=u.y*v.z-u.z*v.y;
    temp.y=u.z*v.y-u.y*v.z;
    temp.z=u.x*v.y-u.y*v.x;
    return temp;
    
}

// Vector dot product
template<class T >
T operator*(const  Vector<T>& u,const  Vector<T> &v)
{
    
    return u.x*v.x+u.y*v.y+u.z*v.z;
}

template<class T >
Vector<T> operator*(T s,const  Vector<T>& u)
{
    Vector<T> temp;
    temp.x=u.x*s;
    temp.y=u.y*s;
    temp.z=u.z*s;
    return temp;
}
template<class T >
Vector<T> operator*(const  Vector<T>& u, T s)
{
    return s*u;
}
template<class T >
Vector<T> operator/(const  Vector<T>& u, T s)
{
    Vector<T> temp;
    temp.x=u.x/s;
    temp.y=u.y/s;
    temp.z=u.z/s;
    return temp;
}
template<class T >
ostream& operator<<(ostream &out,const  Vector<T>& u)
{
    out<<"("<<u.x<<","<<u.y<<","<<u.z<<")";
    return out;
}
template<class T >
bool Vector<T>::operator==(const  Vector<T>& u)
{
    return (*this-u).Magnitude()==0;
}
template<class T >
bool Vector<T>::operator!=(const  Vector<T>& u)
{
    return (*this-u).Magnitude()!=0;
}


#endif // VECTOR_H_INCLUDED
