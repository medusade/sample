///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: main.hpp
///
/// Author: $author$
///   Date: 8/16/2017
///////////////////////////////////////////////////////////////////////
#ifndef _SAMPLE_APP_FILTER_MAIN_HPP
#define _SAMPLE_APP_FILTER_MAIN_HPP

#include "xos/base/getopt/main.hpp"

namespace sample {
namespace app {
namespace filter {

typedef xos::base::getopt::main_implement main_implements;
typedef xos::base::getopt::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    /// Constructor: main
    ///////////////////////////////////////////////////////////////////////
    main() {
    }
    virtual ~main() {
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    /// Function: run
    ///////////////////////////////////////////////////////////////////////
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        /*
        Given a single digit number array, implement a function to move all
        the 9’s to the end. The order of all other array elements should
        remain the same. Example: input array {1, 3, 5, 9, 9, 0, 4, 6, 9}
        should result {1, 3, 5, 0, 4, 6, 9, 9, 9}.
        Expectation:
        - Code should be implemented in C++ or Java.
        - Space and time efficiency should be considered.
        */
        int a[9] = {1, 3, 5, 9, 9, 0, 4, 6, 9};
        int i = 0, j = 0, k = 0;

        for (i = 0, j = 0, k = 0; i < 9; ++i) {
            if (9 != a[i]) {
                if (j != i) {
                    a[j] = a[i];
                    a[i] = 9;
                }
                ++j;
            } else {
                ++k;
            }
        }
        out("{");
        for (int& i: a) {
            outf("%s%d", (&i != a)?(", "):(""), i);
        }
        outln("}");
        return err;
    }
};

} // namespace filter 
} // namespace app 
} // namespace sample 

#endif // _SAMPLE_APP_FILTER_MAIN_HPP 
