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
///   File: searcher.hpp
///
/// Author: $author$
///   Date: 3/25/2017
///////////////////////////////////////////////////////////////////////
#ifndef _SAMPLE_TREE_SEARCHER_HPP
#define _SAMPLE_TREE_SEARCHER_HPP

#include "branch.hpp"

namespace sample {
namespace tree {

///////////////////////////////////////////////////////////////////////
///  Class: searchert
///////////////////////////////////////////////////////////////////////
template <class TBranch>
class searchert {
public:
    typedef TBranch branch;

    searchert() {}
    virtual ~searchert() {}

    virtual void search(branch* root) {}
    virtual branch* found(branch* b) { return 0; }
};

///////////////////////////////////////////////////////////////////////
///  Class: bfst
///////////////////////////////////////////////////////////////////////
template <class TBranch, class TBranches, class TExtends>
class bfst: public TExtends {
public:
    typedef TExtends extends;
    typedef TBranches branches;
    typedef TBranch branch;

    bfst() {}
    bfst(branch* v) { this->search(v); }

    virtual void search(branch* v) {
        if (v) {
            do {
                if (this->found(v)) { break; }
                for (typename branches::iterator bi = v->branches().begin();
                     bi != v->branches().end(); ++bi) {
                    this->queue_branch(*(bi));
                }
            } while ((v = this->pop_branch()));
        }
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: dfst
///////////////////////////////////////////////////////////////////////
template <class TBranch, class TBranches, class TExtends>
class dfst: public TExtends {
public:
    typedef TExtends extends;
    typedef TBranches branches;
    typedef TBranch branch;

    dfst() {}
    dfst(branch* v) { this->search(v); }

    virtual void search(branch* v) {
        if (v) {
            do {
                if (this->found(v)) { break; }
                for (typename branches::iterator bi = v->branches().end();
                     bi != v->branches().begin();) {
                    this->push_branch(*(--bi));
                }
            } while ((v = this->pop_branch()));
        }
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: dst
///////////////////////////////////////////////////////////////////////
template <class TBranch, class TBranches, class TExtends>
class dst: public TExtends {
public:
    typedef TExtends extends;
    typedef TBranches branches;
    typedef TBranch branch;

    dst() {}
    dst(branch* v) { this->search(v); }

    virtual void search(branch* v) {
        if (v) {
            do {
                stack_.push_branch(v);
                for (typename branches::iterator bi = v->branches().begin();
                     bi != v->branches().end(); ++bi) {
                    this->push_branch(*(bi));
                }
            } while ((v = this->pop_branch()));
            while ((v = stack_.pop_branch())) {
                if (this->found(v)) { break; }
            }
        }
    }
protected:
    branches stack_;
};

} // namespace tree
} // namespace sample 

#endif // _SAMPLE_TREE_SEARCHER_HPP 
