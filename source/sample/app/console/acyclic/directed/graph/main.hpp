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
///   File: main.hpp
///
/// Author: $author$
///   Date: 2/10/2019
///////////////////////////////////////////////////////////////////////
#ifndef _APP_CONSOLE_ACYCLIC_DIRECTED_GRAPH_MAIN_HPP
#define _APP_CONSOLE_ACYCLIC_DIRECTED_GRAPH_MAIN_HPP

#include "graph/nodes.hpp"
#include "graph/node.hpp"
#include "graph/search.hpp"

#include <string>
#include <iostream>

namespace acyclic {
namespace directed {
namespace graph {

typedef ::std::string string;

class node;
typedef node* node_pointer;
typedef const node* const_node_pointer;

class nodes;
typedef nodes* nodes_pointer;
typedef const nodes* const_nodes_pointer;
typedef ::graph::nodest<node> nodes_extends;
class nodes: public nodes_extends {
public:
    typedef nodes_extends extends;
}; /// class nodes

typedef ::graph::nodet<node, nodes, string> node_extends;
class node: public node_extends {
public:
    typedef node_extends extends;
    const node* common;
    node(const string& s): common(0) {
        this->assign(s);
    }
    node(const node& copy) {
        this->assign(copy);
        this->common = copy.common;
    }
    node(): common(0) {
    }
    node& operator = (const node& copy) {
        this->assign(copy);
        this->common = copy.common;
        return *this;
    }
}; /// class node

///
/// searcher
///
typedef ::graph::nodet<node, nodes, ::graph::searchert<node> > searcher_extends;
class searcher: public searcher_extends {
public:
    virtual node* found(node* n) {
        node_.nodes().push_back(n);
        return 0; 
    }
    const node& found() const {
        return node_;
    }
protected:
    node node_;
}; /// class searcher
///
/// breadth_first_search
///
typedef ::graph::breadth_first_searcht<node, nodes, searcher> breadth_first_search;

///
/// a class representing an acyclic directed graph with a member function 
/// that takes as input an STL container of graphs that:
/// (1) finds the element with which the longest common prefix is shared.
/// (2) returns both the shared common prefix and the corresponding element. 
///
class graph;
typedef graph* graph_pointer;
typedef ::std::list<graph*> graphs;
typedef node graph_extends;
class graph: public graph_extends {
public:
    typedef graph_extends extends;

    graph(const string& s): extends(s) {}
    
    node longest_common_prefix(const graphs& g) const;
    node longest_common_prefix(const node& g) const;
    node longest_common_prefix(const node& a, const node& b) const;
    
    node_pointer new_node() const;
    void free_node(node_pointer) const;
    void free_nodes(node& n) const;
    
    void out(std::ostream& o, const directed::graph::nodes& n) const;
    void out(std::ostream& o, const node& n) const;
}; /// class graph

/// class graph
/// ... 
node graph::longest_common_prefix(const graphs& g) const {
    node x;
    graphs::const_iterator i;
    node_pointer p;
    size_t n;

    for (i = g.begin(); i != g.end(); ++i) {
        if ((p = new_node())) {
            breadth_first_search s(*i);

            out(std::cerr, s.found().nodes());
            *p = longest_common_prefix(s.found());
            if (0 < (p->length())) {
                out(std::cerr, *p);
                x.nodes().push_back(p);
            } else {
                free_node(p);
                free_nodes(x);
                return x;
            }
        }
    }
    if (1 < (n = x.nodes().size())) {
        out(std::cerr, x.nodes());
        x = longest_common_prefix(x);
    } else {
        if ((0 < (n)) && (p = x.nodes().front())) {
            x = *p;
        }
    }
    if (0 < (x.length())) {
        out(std::cerr, x);
    }
    free_nodes(x);
    return x;
}
node graph::longest_common_prefix(const node& g) const {
    node x;
    nodes::const_iterator i;

    if ((i = g.nodes().begin()) != g.nodes().end()) {
        x = *(*i);
        while (++i != g.nodes().end()) {
            x = longest_common_prefix(x, *(*i));
            if (1 > (x.length())) {
                return x;
            }
        }
    }
    return x;
}
node graph::longest_common_prefix(const node& a, const node& b) const {
    size_t n = std::min(a.length(), b.length());
    char c = 0;
    node x;

    for (size_t i = 0; i < n; i++) {
        if (((c = a[i]) != b[i])) {
            break;
        }
        x.push_back(c);
    }
    return x;
}
node_pointer graph::new_node() const {
    return new node;
}
void graph::free_node(node_pointer p) const {
    delete p;
}
void graph::free_nodes(node& n) const {
    for (nodes::const_iterator i = n.nodes().begin(); i != n.nodes().end(); ++i) {
        free_node(*i);
    }
    n.nodes().clear();
}
void graph::out(std::ostream& o, const directed::graph::nodes& n) const {
    if (1 < (n.size())) {
        o << "for";
        for (nodes::const_iterator i = n.begin(); i != n.end(); ++i) {
            o << " \"" << (*(*i)) << "\"";
        }
        o << "\n";
    }
}
void graph::out(std::ostream& o, const node& n) const{
    if (0 < (n.length())) {
        o << "largest common prefix is \"" << n << "\"\n";
    }
}
/// ...
/// class graph

} /// namespace graph
} /// namespace directed
} /// namespace acyclic

namespace app {
namespace console {
namespace acyclic {
namespace directed {
namespace graph {

class main {
public:
    virtual int operator()(int argc, char** argv, char** env) {
        ::acyclic::directed::graph::node_pointer n;
        ::acyclic::directed::graph::graph_pointer p;
        ::acyclic::directed::graph::graphs g;
        ::acyclic::directed::graph::node x;
        
        for (int j = 0; j < 10; ++j) {
            for (int i = 1; i < argc; ++i) {
                if (1 < i) {
                    n = new ::acyclic::directed::graph::node(argv[i]);
                    ::acyclic::directed::graph::node& back = *(g.back());
                    back.nodes().push_back(n);
                    if (1 > (j)) {
                        x.nodes().push_back(n);
                    }
                } else {
                    p = new ::acyclic::directed::graph::graph(argv[i]);
                    g.push_back(p);
                    if (1 > (j)) {
                        x.nodes().push_back(p);
                    }
                }
            }
        }
        if ((0 < (g.size())) && (p = g.front())) {
            if (2 < (argc)) {
                p->out(std::cout, x.nodes());
            }
            x = p->longest_common_prefix(g);
            if (0 < (x.length())) {
                p->out(std::cout, x);
            }
        }
        return 0;
    }
}; /// class main

} /// namespace graph
} /// namespace directed
} /// namespace acyclic
} /// namespace console
} /// namespace app

#endif /// _APP_CONSOLE_ACYCLIC_DIRECTED_GRAPH_MAIN_HPP 
