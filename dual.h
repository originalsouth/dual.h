/* https://github.com/originalsouth/dual.h */
/* By Dr. BC van Zuiden -- Amstelveen, June 2019 */
/* Probably very buggy USE AT OWN RISK this will brick everything you own */
/* NOBODY but YOU is liable for anything that happened in result of using this */
/* WARNING: DON'T RUN THIS PROGRAM THIS WILL DESTROY YOUR COMPUTER AND/OR HOUSE */
/* Any copyrighted piece of code within this code is NOT mine */
/* Inclusion of that code is forced upon me by a scary anonymous guy with a gun*/

#ifndef __dual_h__
#define __dual_h__
#include <cmath>

namespace dual
{
    template<class X> struct dual_t
    {
        X x,dx;
        dual_t(){}
        dual_t(X y,X dy=0) { x=y,dx=dy; }
        template<class Y> dual_t operator=(Y y) { return *this=dual_t(static_cast<X>(y)); }
        operator X() { return x; }
    };
#define OPERATOR(OP) template<class X> bool operator OP (const dual_t<X> &x,const dual_t<X> &y) { return x.x OP y.x; }
    OPERATOR(==)
    OPERATOR(!=)
    OPERATOR(<=)
    OPERATOR(>=)
    OPERATOR(>)
    OPERATOR(<)
#undef OPERATOR
#define OPERATOR(OP) template<class X,class Y> bool operator OP (const dual_t<X> &x,Y y) { return x.x OP static_cast<X>(y); }
    OPERATOR(==)
    OPERATOR(!=)
    OPERATOR(<=)
    OPERATOR(>=)
    OPERATOR(>)
    OPERATOR(<)
#undef OPERATOR
#define OPERATOR(OP) template<class X,class Y> bool operator OP (Y x,const dual_t<X> &y) { return static_cast<X>(x) OP y.x; }
    OPERATOR(==)
    OPERATOR(!=)
    OPERATOR(<=)
    OPERATOR(>=)
    OPERATOR(>)
    OPERATOR(<)
#undef OPERATOR
    template<class X> dual_t<X> operator-(const dual_t<X> &x) { return dual_t<X>(-x.x,-x.dx); }
#define OPERATOR(OP) template<class X,class Y> dual_t<X> operator OP (const dual_t<X> &x,Y y) { return dual_t<X>(x.x OP static_cast<X>(y),x.dx); }
    OPERATOR(+)
    OPERATOR(-)
#undef OPERATOR
#define OPERATOR(OP) template<class X,class Y> dual_t<X> operator OP (const dual_t<X> &x,Y y) { return dual_t<X>(x.x OP static_cast<X>(y),x.dx OP static_cast<X>(y)); }
    OPERATOR(*)
    OPERATOR(/)
#undef OPERATOR
    template<class X,class Y> dual_t<X> operator+(Y x,const dual_t<X> &y) { return dual_t<X>(static_cast<X>(x)+y.x,y.dx); }
    template<class X,class Y> dual_t<X> operator-(Y x,const dual_t<X> &y) { return dual_t<X>(static_cast<X>(x)-y.x,-y.dx); }
    template<class X,class Y> dual_t<X> operator*(Y x,const dual_t<X> &y) { return dual_t<X>(static_cast<X>(x)*y.x,static_cast<X>(x)*y.dx); }
    template<class X,class Y> dual_t<X> operator/(Y x,const dual_t<X> &y) { return dual_t<X>(static_cast<X>(x)/y.x,-static_cast<X>(x)*y.dx*std::pow(y.x,-2)); }
#define OPERATOR(OP) template<class X> dual_t<X> operator OP (const dual_t<X> &x,const dual_t<X> &y) { return dual_t<X>(x.x OP y.x,x.dx OP y.dx); }
    OPERATOR(+)
    OPERATOR(-)
#undef OPERATOR
#define OPERATOR(OP,OQ) template<class X> dual_t<X>& operator OP (dual_t<X> &x,X y) { return x=x OQ y; }
        OPERATOR(+=,+)
        OPERATOR(-=,-)
        OPERATOR(*=,*)
        OPERATOR(/=,/)
#undef OPERATOR
    template<class X> dual_t<X> operator*(const dual_t<X> &x,const dual_t<X> &y) { return dual_t<X>(x.x*y.x,x.x*y.dx+x.dx*y.x); }
    template<class X> dual_t<X> operator/(const dual_t<X> &x,const dual_t<X> &y) { return dual_t<X>(x.x/y.x,(x.dx*y.x-x.x*y.dx)*std::pow(y.x,-2)); }
#define OPERATOR(OP,OQ) template<class X> dual_t<X>& operator OP (dual_t<X> &x,const dual_t<X> &y) { return x=x OQ y; }
        OPERATOR(+=,+)
        OPERATOR(-=,-)
        OPERATOR(*=,*)
        OPERATOR(/=,/)
#undef OPERATOR
    template<class X> dual_t<X> sin(const dual_t<X> &x) { return dual_t<X>(std::sin(x.x),x.dx*std::cos(x.x)); }
    template<class X> dual_t<X> cos(const dual_t<X> &x) { return dual_t<X>(std::cos(x.x),-x.dx*std::sin(x.x)); }
    template<class X> dual_t<X> tan(const dual_t<X> &x)
    {
        const X tx=std::tan(x.x);
        return dual_t<X>(tx,x.dx*(1.0+std::pow(tx,2)));
    }
    template<class X> dual_t<X> asin(const dual_t<X> &x) { return dual_t<X>(std::asin(x.x),x.dx/std::sqrt(1.0-std::pow(x.x,2))); }
    template<class X> dual_t<X> acos(const dual_t<X> &x) { return dual_t<X>(std::acos(x.x),-x.dx/std::sqrt(1.0-std::pow(x.x,2))); }
    template<class X> dual_t<X> atan(const dual_t<X> &x) { return dual_t<X>(std::atan(x.x),x.dx/(1.0+std::pow(x.x,2))); }
    template<class X,class Y> dual_t<X> atan2(const dual_t<X> &x,Y y) { return dual_t<X>(std::atan2(x.x,static_cast<X>(y)),(x.dx*static_cast<X>(y))/(std::pow(x.x,2)+std::pow(static_cast<X>(y),2))); }
    template<class X,class Y> dual_t<X> atan2(Y x,const dual_t<X> &y) { return dual_t<X>(std::atan2(static_cast<X>(x),y.x),(-static_cast<X>(x)*y.dx)/(std::pow(static_cast<X>(x),2)+std::pow(y.x,2))); }
    template<class X> dual_t<X> atan2(const dual_t<X> &x,const dual_t<X> &y) { return dual_t<X>(std::atan2(x.x,y.y),(x.dx*y.x-x.x*y.dx)/(std::pow(x.x,2)+std::pow(y.x,2))); }
    template<class X> dual_t<X> sinh(const dual_t<X> &x) { return dual_t<X>(std::sinh(x.x),x.dx*std::cosh(x.x)); }
    template<class X> dual_t<X> cosh(const dual_t<X> &x) { return dual_t<X>(std::cosh(x.x),x.dx*std::sinh(x.x)); }
    template<class X> dual_t<X> tanh(const dual_t<X> &x) { return dual_t<X>(std::tanh(x.x),x.dx*std::pow(std::cosh(x.x),-2)); }
    template<class X> dual_t<X> asinh(const dual_t<X> &x) { return dual_t<X>(std::asinh(x.x),x.dx/std::sqrt(1.0+std::pow(x.x,2))); }
    template<class X> dual_t<X> acosh(const dual_t<X> &x) { return dual_t<X>(std::acosh(x.x),x.dx/std::sqrt(std::pow(x.x,2)-1.0)); }
    template<class X> dual_t<X> atanh(const dual_t<X> &x) { return dual_t<X>(std::atanh(x.x),x.dx/(1.0-std::pow(x.x,2))); }
    template<class X,class Y> dual_t<X> pow(const dual_t<X> &x,Y y) { return dual_t<X>(std::pow(x.x,y),x.dx*static_cast<X>(y)*std::pow(x.x,y-static_cast<Y>(1))); }
    template<class X,class Y> dual_t<X> pow(Y x,const dual_t<X> &y)
    {
        const X pxy=std::pow(x,y.x);
        return dual_t<X>(pxy,y.dx*std::log(x)*pxy);
    }
    template<class X> dual_t<X> pow(const dual_t<X> &x,const dual_t<X> &y) { return dual_t<X>(std::pow(x.x,y.x),std::pow(x.x,y.x-static_cast<X>(1))*(y.x*x.dx+x.x*log(x.x)*y.dx)); }
    template<class X> dual_t<X> sqrt(const dual_t<X> &x)
    {
        const X sqx=std::sqrt(x.x);
        return dual_t<X>(sqx,x.dx/(static_cast<X>(2)*sqx));
    }
    template<class X> dual_t<X> cbrt(const dual_t<X> &x)
    {
        const X cbx=std::cbrt(x.x);
        return dual_t<X>(cbx,x.dx/(static_cast<X>(3)*std::pow(cbx,2)));
    }
    template<class X,class Y> dual_t<X> hypot(const dual_t<X> &x,Y y)
    {
        const X hxy=std::hypot(x.x,y);
        return dual_t<X>(hxy,(x.x*x.dx)/hxy);
    }
    template<class X,class Y> dual_t<X> hypot(Y x,const dual_t<X> &y)
    {
        const X hxy=std::hypot(x,y.x);
        return dual_t<X>(hxy,(y.x*y.dx)/hxy);
    }
    template<class X> dual_t<X> hypot(const dual_t<X> &x,const dual_t<X> &y)
    {
        const X hxy=std::hypot(x.x,y.x);
        return dual_t<X>(hxy,(x.x*x.dx+y.x*y.dx)/hxy);
    }
    template<class X> dual_t<X> exp(const dual_t<X> &x)
    {
        const X ex=std::exp(x.x);
        return dual_t<X>(ex,x.dx*ex);
    }
    template<class X> dual_t<X> log(const dual_t<X> &x) { return dual_t<X>(std::log(x.x),x.dx/x.x); }
    template<class X> dual_t<X> log10(const dual_t<X> &x) { return dual_t<X>(std::log10(x.x),x.dx/(x.x*std::log(static_cast<X>(10)))); }
    template<class X> dual_t<X> erf(const dual_t<X> &x)
    {
        const X c=static_cast<X>(2)/std::sqrt(std::acos(static_cast<X>(-1)));
        return dual_t<X>(std::erf(x.x),x.dx*c*std::exp(-std::pow(x.x,2)));
    }
    template<class X> dual_t<X> erfc(const dual_t<X> &x)
    {
        const X c=-static_cast<X>(2)/std::sqrt(std::acos(static_cast<X>(-1)));
        return dual_t<X>(std::erfc(x.x),x.dx*c*std::exp(-std::pow(x.x,2)));
    }
    template<class X> dual_t<X> fabs(const dual_t<X> &x) { return dual_t<X>(std::fabs(x.x),x.dx*x.x/std::fabs(x.x)); }
}
#endif
