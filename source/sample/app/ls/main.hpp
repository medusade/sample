///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 12/7/2016
///////////////////////////////////////////////////////////////////////
#ifndef _SAMPLE_APP_LS_MAIN_HPP
#define _SAMPLE_APP_LS_MAIN_HPP

#include "xos/base/getopt/main.hpp"
#include "xos/os/fs/directory/path.hpp"
#include "xos/os/fs/directory/entry.hpp"
#include "xos/os/fs/entry.hpp"
#include <list>

namespace sample {
namespace app {
namespace ls {

typedef xos::base::getopt::main_implement main_implement;
typedef xos::base::getopt::main main_extend;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implement, public main_extend {
public:
    typedef main_implement Implements;
    typedef main_extend Extends;
    typedef main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main(): on_entry_(0) {
    }
    virtual ~main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;

        if ((1 < (argc))) {
            const char_t* path = 0;
            xos::fs::entry_type type = xos::fs::entry_type_none;
            xos::os::fs::entry e;

            for (int arg = optind; arg < argc; ++arg) {
                if (((path = argv[arg])) && ((path[0]))) {
                    if (xos::fs::entry_type_none != (type = e.exists(path))) {
                        if ((err = on_entry(e, path))) {
                            break;
                        }
                    } else {
                        outl("Unable to find \"", path, "\"", 0);
                        outln();
                    }
                }
            }
        } else {
            err = usage(argc, argv, env);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_entry
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        if ((on_entry_)) {
            return (this->*on_entry_)(e, path);
        }
        return on_entry_default(e, path);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = 0;
        xos::fs::entry_type type = xos::fs::entry_type_none;
        if (xos::fs::entry_type_directory != (xos::fs::entry_type_directory & (type = e.type()))) {
            err = on_file_entry_default(e, path);
        } else {
            err = on_directory_entry_default(e, path);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_directory_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = 0;
        if (!(err = on_begin_directory_entry_default(e, path))) {
            xos::os::fs::directory::path d;

            if ((d.open(path))) {
                xos::os::fs::directory::entry* de = 0;

                if ((de = d.get_first_entry())) {
                    do {
                        if (!(de->is_circular())) {
                            const char_t* dpath = 0;
                            string_t dp(path);

                            dp.appendl("/", de->name(), NULL);
                            if ((dpath = dp.has_chars())) {
                                if ((err = on_entry_default(*de, dpath))) {
                                    break;
                                }
                            }
                        }
                    } while ((de = d.get_next_entry()));
                }
            }
            if (!(err)) {
                err = on_end_directory_entry_default(e, path);
            }
        }
        return err;
    }
    virtual int on_begin_directory_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = on_begin_entry_default(e, path);
        return err;
    }
    virtual int on_end_directory_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = on_end_entry_default(e, path);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_file_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = 0;
        if (!(err = on_begin_file_entry_default(e, path))) {
            err = on_end_file_entry_default(e, path);
        }
        return err;
    }
    virtual int on_begin_file_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = on_begin_entry_default(e, path);
        return err;
    }
    virtual int on_end_file_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = on_end_entry_default(e, path);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_begin_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        const xos::fs::time* tm = 0;
        outl("name = ", path, 0);
        outln();
        out("type =");
        for (xos::fs::entry_type_which t = xos::fs::first_entry_type; t < xos::fs::next_entry_type; t <<= 1) {
            if ((t & (e.type()))) {
                string_t name(xos::fs::entry_type::name(t));
                outl(" ", name.chars(), 0);
            }
        }
        outln();
        outf("size = %lu", e.size());
        outln();
        for (xos::fs::time_when_which t = xos::fs::first_time_when; t < xos::fs::next_time_when; t <<= 1) {
            if ((t & e.times()) && (tm = e.time_which(t))) {
                outl(xos::fs::time_when::name(t), " = ", 0);
                outf("%d/%d/%d", tm->month(), tm->day(), tm->year());
                outln();
            }
        }
        return 0;
    }
    virtual int on_end_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef int (Derives::*on_entry_t)
    (const xos::os::fs::entry& e, const char_t* path);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    on_entry_t on_entry_;
};

} // namespace ls
} // namespace app 
} // namespace sample 

#endif // _SAMPLE_APP_LS_MAIN_HPP 
