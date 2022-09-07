#pragma once

#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
	Node() = default;
	T value;
	Node* next;
};

#endif
