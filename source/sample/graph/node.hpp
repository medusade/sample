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
///   File: node.hpp
///
/// Author: $author$
///   Date: 2/10/2019
///////////////////////////////////////////////////////////////////////
#ifndef _GRAPH_NODE_HPP
#define _GRAPH_NODE_HPP

#include "graph/nodes.hpp"

namespace graph {

template <class node, class tnodes, class extends>
class nodet: public extends {
public:
    virtual node* push_node(node* first) {
        return nodes_.push_node(first);
    }
    virtual node* pop_node() {
        return nodes_.pop_node();
    }
    virtual node* queue_node(node* last) {
        return nodes_.queue_node(last);
    }
    virtual node* pull_node() {
        return nodes_.pull_node();
    }
    virtual tnodes& nodes() const {
        return (tnodes&)nodes_;
    }
protected:
    tnodes nodes_;
}; /// class nodet

} /// namespace graph

#endif /// _GRAPH_NODE_HPP 
