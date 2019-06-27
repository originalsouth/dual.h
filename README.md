# dual.h
A small and simple header only dual number library (written in C++17):
```
/* https://github.com/originalsouth/dual.h */
/* By Dr. BC van Zuiden -- Amstelveen, June 2019 */
/* Probably very buggy USE AT OWN RISK this will brick everything you own */
/* NOBODY but YOU is liable for anything that happened in result of using this */
/* WARNING: DON'T RUN THIS PROGRAM THIS WILL DESTROY YOUR COMPUTER AND/OR HOUSE */
/* Any copyrighted piece of code within this code is NOT mine */
/* Inclusion of that code is forced upon me by a scary anonymous guy with a gun*/
```
Feel free to reuse and contribute, pull requests are very welcome!
This code is (and forever will be) a work in progress.

dual.h is a simple implementation of boiler plate dual numbers algebraically calculating first order derivatives in runtime: automatic differentatiation.
Nothing fancy smancy needed it just works -- hopefully.
Have fun!

### Roadmap
* Possibly add more (special) functions
* Improve help and documentation
* Improvements / Bug fixes / Stability / Maintenance (the usual)
* Your suggestion?

### Using dual.h
You can clone this repository as a submodule into your own repository and then include it as such:
```
#include "dual.h/dual.h"
```
or what ever you choose to be the appropriate directory

Alternatively, you can install by copying the header `dual.h` to your include path and include it using:
```
#include <dual.h>
```
Then take your doubles and convert them to dual_t types.
A minimal example to find the derivative of should be something like:
```
#include <cstdio>
#include <cstdlib>
#include "dual.h/dual.h"

using namespace std;
using namespace dual;

int main()
{
    dual_t<double> x(2.0,1.0); //dual number variable at x=2.0; the second parameter applies the chain rule (should mostly be one)
    dual_t<double> y=pow(x,2); //iterate in pow(x,2)
    printf("The evaluation of x^2 in x=2 is given by %.17g\n",y.x);
    printf("The derivative of x^2 in x=2 is given by %.17g\n",y.dx);
    return EXIT_SUCCESS;
}
```

### Building the example/test
To build run something like:
```
make
```

To test:
```
./dual
```

To clean run:
```
make clean
```
This will remove the compiled test binary.


### Acknowledgements
* Inspired by the work Dr. Tommy B.
