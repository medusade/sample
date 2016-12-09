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
#include <list>

namespace sample {
namespace app {
namespace ls {
namespace tree {

class branch;
typedef std::list<branch*> branches;
class branch: public std::string {
friend class fs;
friend class bfs;
friend class dfs;
public:
    typedef std::string extends;
    branch() {}
    branch(const char* c_str): extends(c_str) {}
    virtual branch* queue_branch(branch* last) {
        branches_.push_back(last);
        return last;
    }
protected:
    branches branches_;
};

class fs {
public:
    fs(): branch_(0) {}
    virtual void search(branch* root) {
    }
    virtual branch* queue_branch(branch* last) {
        if (last) { branches_.push_back(last); }
        return last;
    }
    virtual branch* push_branch(branch* first) {
        if (first) { branches_.push_front(first); }
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
    virtual branch* pull_branch() {
        branch* last = 0;
        branches::iterator i = branches_.end();
        if (i != (branches_.begin())) {
            last = *(--i);
            branches_.pop_back();
        }
        return last;
    }
    virtual branch* visit_branch(branch* b) {
        return b;
    }
protected:
    branches branches_;
    branch* branch_;
};

class bfs: public fs {
public:
    typedef fs extends;
    bfs() {}
    bfs(branch* root) { this->search(root); }
    virtual void search(branch* root) {
        if (branch_ = (root)) {
            branch* b = 0;
            branches::iterator bi;
            do {
                visit_branch(branch_);
                for (bi = branch_->branches_.begin();
                     bi != branch_->branches_.end(); ++bi) {
                    if (b = *(bi)) {
                        queue_branch(b);
                    }
                }
            } while ((branch_ = pop_branch()));
        }
    }
};

class dfs: public fs {
public:
    typedef fs extends;
    dfs() {}
    dfs(branch* root) { this->search(root); }
    virtual void search(branch* root) {
        if (branch_ = (root)) {
            branch *b = 0;
            branches::iterator bi;
            push_branch(branch_);
            while ((branch_ = pop_branch())) {
                visit_branch(branch_);
                for (bi = branch_->branches_.end();
                     bi != branch_->branches_.begin();) {
                    if (b = *(--bi)) {
                        push_branch(b);
                    }
                }
            }
        }
    }
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
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main(): branch_(0) {
    }
    virtual ~main() {
    }
protected:
    class bfs: public tree::bfs {
    public:
        typedef tree::bfs extends;
        bfs(Extends& main, branch* root): main_(main) { this->search(root); }
        virtual branch* visit_branch(branch* b) {
            main_.outln(b->c_str());
            return b;
        }
    protected:
        Extends& main_;
    };
    class dfs: public tree::dfs {
    public:
        typedef tree::dfs extends;
        dfs(Extends& main, branch* root): main_(main) { this->search(root); }
        virtual branch* visit_branch(branch* b) {
            main_.outln(b->c_str());
            return b;
        }
    protected:
        Extends& main_;
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int before_run(int argc, char_t** argv, char_t** env) {
        branch_ = new branch();
        return 0;
    }
    virtual int after_run(int argc, char_t** argv, char_t** env) {
        bfs bsearch(*this, branch_);
        dfs dsearch(*this, branch_);
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_begin_directory_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = 0;
        branch *b = 0;
        if ((branch_) && (b = (new branch(path)))) {
            branch_->queue_branch(b);
            push_branch(branch_);
            branch_ = b;
        } else {
            return 1;
        }
        return err;
    }
    virtual int on_end_directory_entry_default
    (const xos::os::fs::entry& e, const char_t* path = 0) {
        int err = 0;
        if (!(branch_ = (pop_branch()))) {
            return 1;
        }
        return err;
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
    branches branches_;
    branch* branch_;
};

} // namespace tree 
} // namespace ls 
} // namespace app 
} // namespace sample 

#endif // _SAMPLE_APP_LS_TREE_MAIN_HPP 
        

