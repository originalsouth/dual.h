/* https://github.com/originalsouth/dual.h */
/* By Dr. BC van Zuiden -- Amstelveen, June 2019 */
/* Probably very buggy USE AT OWN RISK this will brick everything you own */
/* NOBODY but YOU is liable for anything that happened in result of using this */
/* WARNING: DON'T RUN THIS PROGRAM THIS WILL DESTROY YOUR COMPUTER AND/OR HOUSE */
/* Any copyrighted piece of code within this code is NOT mine */
/* Inclusion of that code is forced upon me by a scary anonymous guy with a gun*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <limits>
#include "dual.h"

using namespace std;
using namespace dual;

template<class X,class Y> bool test(size_t counter,const char *label,X value,Y f,X x,X dx)
{
    const X qeps=sqrt(numeric_limits<X>::epsilon());
    const dual_t<X> y=f(dual_t<X>(value,1.0));
    const bool val=(fabs(x-y.x)<qeps);
    const bool deriv=(fabs(dx-y.dx)<qeps);
    bool retval;
    if((retval=val and deriv)) printf("TEST(%02zu) \"%s\" at \"%.17g\": OK\n",counter,label,value);
    else if(val and !deriv) fprintf(stderr,"TEST(%02zu) \"%s\" at \"%.17g\": FAILED derivative(%.17g!=%.17g)\n",counter,label,value,dx,y.dx);
    else if(!val and deriv) fprintf(stderr,"TEST(%02zu) \"%s\" at \"%.17g\": FAILED value(%.17g!=%.17g)\n",counter,label,value,x,y.x);
    else fprintf(stderr,"TEST(%02zu) \"%s\" at \"%.17g\": FAILED value(%.17g!=%.17g) and FAILED derivative(%.17g!=%.17g)\n",counter,label,value,x,y.x,dx,y.dx);
    return retval;
}

int main(int argc,char *argv[])
{
    size_t retval=0;
    auto argv_lookup=[=](int line)->bool{for(int i=1;i<argc;i++) if(line==atoi(argv[i])) return true;return false;};
#define TEST(EXP,VAL,X,DX) if(argc==1 or (argc>1 and argv_lookup(__LINE__))) if(!test(__LINE__,#EXP,VAL,[](dual_t<double> x)->dual_t<double>{return EXP;},X,DX)) retval++;
#include "test.cc"
#undef TEST
    if(retval) fprintf(stderr,"there %s %zu failed tests :(\n",retval==1?"is":"are",retval);
    return retval?EXIT_FAILURE:EXIT_SUCCESS;
}
