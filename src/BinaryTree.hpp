#pragma once

#include <utility>
#include <memory>

template<typename T>
class BinaryTree
{
public:
    struct Node
    {
        using NodePtr = std::unique_ptr<Node>;
        using Children = std::pair<NodePtr, NodePtr>;

        Node(T& val) : 
            children{ {nullptr, nullptr} },
            val(val)
        {}

        T& val;
        Children children;

        Children& getChildren() { return children; }

        operator T&() { return val; }
        operator const T&() const { return val; }
    };

    BinaryTree(T& root) :
        Node(root)
    {}

    template<typename Iter>
    void addRange(Iter first, Iter end, Node& subRoot)
    {
        auto size = std::distance(first, end);
        auto halfIt = first;
        std::advance(first, ceil(size / 2.0));

        subRoot.children.first = std::make_unique<Node>(*first);
    }

private:
    Node root;
};
