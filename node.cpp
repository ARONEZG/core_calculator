#include "node.h"
#include <utility>



OperationNode::OperationNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right, char op)
: _left(std::move(left)), _right(std::move(right)), _op(op) {
    type = Type::OPERATOR;
}