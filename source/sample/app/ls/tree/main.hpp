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
#ifndef _SAMPLE_APP_LS_TREE_MAIN_HPP
#define _SAMPLE_APP_LS_TREE_MAIN_HPP

#include "sample/app/ls/main.hpp"
#include "sample/tree/branch.hpp"

namespace sample {
namespace app {
namespace ls {
namespace tree {

class branch;
typedef std::string string;
typedef ::sample::tree::branchest<branch> branches;
typedef ::sample::tree::brancht<branch, branches, string> branch_extends;
///////////////////////////////////////////////////////////////////////
///  Class: branch
///////////////////////////////////////////////////////////////////////
class branch: public branch_extends {
public:
    typedef branch_extends extends;
    branch() {}
    virtual ~branch() {}
    branch(const char* chars) { this->append(chars); }
};

///////////////////////////////////////////////////////////////////////
///  Class: finder
///////////////////////////////////////////////////////////////////////
class finder {
public:
    virtual void search(branch* root) {}
    virtual branch* found(branch* b) { return 0; }
};
typedef ::sample::tree::brancht<branch, branches, finder> searcher;

///////////////////////////////////////////////////////////////////////
///  Class: bfs
///////////////////////////////////////////////////////////////////////
class bfs: public searcher {
public:
    typedef searcher extends;
    bfs() {}
    bfs(branch* v) { this->search(v); }
    virtual void search(branch* v) {
        if (v) {
            do {
                if (found(v)) { break; }
                for (branches::iterator bi = v->branches().begin();
                     bi != v->branches().end(); ++bi) {
                    queue_branch(*(bi));
                }
            } while ((v = pop_branch()));
        }
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: dfs
///////////////////////////////////////////////////////////////////////
class dfs: public searcher {
public:
    typedef searcher extends;
    dfs() {}
    dfs(branch* v) { this->search(v); }
    virtual void search(branch* v) {
        if (v) {
            do {
                if (found(v)) { break; }
                for (branches::iterator bi = v->branches().end();
                     bi != v->branches().begin();) {
                    push_branch(*(--bi));
                }
            } while ((v = pop_branch()));
        }
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: ds
///////////////////////////////////////////////////////////////////////
class ds: public searcher {
public:
    typedef searcher extends;
    ds() {}
    ds(branch* v) { this->search(v); }
    virtual void search(branch* v) {
        if (v) {
            do {
                stack_.push_branch(v);
                for (branches::iterator bi = v->branches().begin();
                     bi != v->branches().end(); ++bi) {
                    push_branch(*(bi));
                }
            } while ((v = pop_branch()));
            while ((v = stack_.pop_branch())) {
                if (found(v)) { break; }
            }
        }
    }
protected:
    tree::branches stack_;
};

typedef ls::main_implement main_implement;
typedef ls::main main_extend;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class main: virtual public main_implement, public main_extend {
public:
    typedef main_implement Implements;
    typedef main_extend Extends;
    typedef main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main(): search_(0), branch_(0) {
    }
    virtual ~main() {
    }

protected:
    typedef void (Derives::*search)();
    ///////////////////////////////////////////////////////////////////////
    ///  Class: bfs
    ///////////////////////////////////////////////////////////////////////
    class bfs: public tree::bfs {
    public:
        typedef tree::bfs extends;
        bfs(Extends& main, branch* root): main_(main) { this->search(root); }
        virtual branch* found(branch* b) {
            main_.outln(b->c_str());
            return 0;
        }
    protected:
        Extends& main_;
    };
    ///////////////////////////////////////////////////////////////////////
    ///  Class: dfs
    ///////////////////////////////////////////////////////////////////////
    class dfs: public tree::dfs {
    public:
        typedef tree::dfs extends;
        dfs(Extends& main, branch* root): main_(main) { this->search(root); }
        virtual branch* found(branch* b) {
            main_.outln(b->c_str());
            return 0;
        }
    protected:
        Extends& main_;
    };
    ///////////////////////////////////////////////////////////////////////
    ///  Class: ds
    ///////////////////////////////////////////////////////////////////////
    class ds: public tree::ds {
    public:
        typedef tree::ds extends;
        ds(Extends& main, branch* root): main_(main) { this->search(root); }
        virtual branch* found(branch* b) {
            main_.outln(b->c_str());
            return 0;
        }
    protected:
        Extends& main_;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void bfs_search() {
        bfs search(*this, branch_);
        outln();
    }
    virtual void dfs_search() {
        dfs search(*this, branch_);
        outln();
    }
    virtual void ds_search() {
        ds search(*this, branch_);
        outln();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int before_run(int argc, char_t** argv, char_t** env) {
        branch_ = new branch();
        return 0;
    }
    virtual int after_run(int argc, char_t** argv, char_t** env) {
        if ((search_)) {
            (this->*search_)();
        } else {
            bfs_search();
            dfs_search();
            ds_search();
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_begin_directory_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        branch *b = 0;
        if ((branch_)) {
            if ((b = new branch(path))) {
                branch_->queue_branch(b);
                push_branch(branch_);
                branch_ = b;
                return 0;
            }
        }
        return 1;
    }
    virtual int on_end_directory_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        if ((branch_ = (pop_branch()))) {
            return 0;
        }
        return 1;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_begin_file_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = 0;
        return err;
    }
    virtual int on_end_file_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch* push_branch(branch* first) {
        branches_.push_front(first);
        return first;
    }
    virtual branch* pop_branch() {
        branch* first = 0;
        branches::iterator i = branches_.begin();
        if (i != (branches_.end())) {
            first = *i;
            branches_.pop_front();
        }
        return first;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    search search_;
    branches branches_;
    branch* branch_;
};

} // namespace tree 
} // namespace ls 
} // namespace app 
} // namespace sample 

#endif // _SAMPLE_APP_LS_TREE_MAIN_HPP 
