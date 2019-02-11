///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   File: search.hpp
///
/// Author: $author$
///   Date: 2/10/2019
///////////////////////////////////////////////////////////////////////
#ifndef _GRAPH_SEARCH_HPP
#define _GRAPH_SEARCH_HPP

#include "graph/node.hpp"

namespace graph {

///
/// searchert
///
template <class TNode>
class searchert {
public:
    typedef TNode node;

    searchert() {}
    virtual ~searchert() {}

    virtual void search(node* root) {}
    virtual node* found(node* n) { return 0; }
}; /// class searchert

///
/// breadth_first_searcht
///
template <class TNode, class TNodes, class TExtends>
class breadth_first_searcht: public TExtends {
public:
    typedef TExtends extends;
    typedef TNodes nodes;
    typedef TNode node;

    breadth_first_searcht() {}
    breadth_first_searcht(node* v) { this->search(v); }

    virtual void search(node* v) {
        if (v) {
            do {
                if (this->found(v)) { break; }
                for (typename nodes::iterator 
                     bi = v->nodes().begin(); bi != v->nodes().end();) {
                    this->queue_node(*(bi++)); }
            } while ((v = this->pop_node()));
        }
    }
}; /// class breadth_first_searcht

///
/// depth_first_searcht
///
template <class TNode, class TNodes, class TExtends>
class depth_first_searcht: public TExtends {
public:
    typedef TExtends extends;
    typedef TNodes nodes;
    typedef TNode node;

    depth_first_searcht() {}
    depth_first_searcht(node* v) { this->search(v); }

    virtual void search(node* v) {
        if (v) {
            do {
                if (this->found(v)) { break; }
                for (typename nodes::iterator 
                     bi = v->nodes().end(); bi != v->nodes().begin();) {
                    this->push_node(*(--bi)); }
            } while ((v = this->pop_node()));
        }
    }
}; /// class depth_first_searcht

} /// namespace graph

#endif /// _GRAPH_SEARCH_HPP 
