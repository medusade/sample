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
///   File: nodes.hpp
///
/// Author: $author$
///   Date: 2/10/2019
///////////////////////////////////////////////////////////////////////
#ifndef _GRAPH_NODES_HPP
#define _GRAPH_NODES_HPP

#include <string>
#include <list>

namespace graph {

template <class node, class extends = std::list<node*> >
class nodest: public extends {
public:
    virtual node* push_node(node* first) {
        if (first) { this->push_front(first); }
        return first;
    }
    virtual node* pop_node() {
        node* first = 0;
        if (!(this->empty())) {
            first = this->front();
            this->pop_front();
        }
        return first;
    }
    virtual node* queue_node(node* last) {
        if (last) { this->push_back(last); }
        return last;
    }
    virtual node* pull_node() {
        node* last = 0;
        if (!(this->empty())) {
            last = this->back();
            this->pop_back();
        }
        return last;
    }
}; /// class nodest

} /// namespace graph

#endif /// _GRAPH_NODES_HPP 
