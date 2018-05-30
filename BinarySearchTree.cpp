/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;


BinarySearchTree::BinarySearchTree()
{
        root = NULL;
}

BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
}

// purpose: delete all nodes in the tree starting with the left child, then
// 	    the right child, then the parent node
// args: node pointer
// rets: none
void BinarySearchTree::post_order_delete(Node *node)
{
        if (node == NULL){
        	return;
        }
        post_order_delete(node->left);
        post_order_delete(node->right);
        delete node;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
        // check for self-assignment
	if (this != &source){
		post_order_delete(root);
		root = pre_order_copy(source.root);
	}
	return *this;
}

// purpose: copy a tree first starting with the node, then the left child
//	    then the right child
// args: node pointer
// rets: node pointer
Node *BinarySearchTree::pre_order_copy(Node *node) const
{
	if (node == NULL){
                return NULL;
        }
        Node *new_node = new Node();
        if (node != NULL){
        	new_node->data = node->data;
        	new_node->count = node->count;
        	new_node->left = pre_order_copy (node->left);
        	new_node->right = pre_order_copy (node->right);
        }
        return new_node;

}

// purpose: find the minimum value in the tree
// args: none
// rets: int (minimum node data value)
int BinarySearchTree::find_min() const
{
        if (root == NULL)
                return INT_MIN;
        return find_min(root)->data;
}

// purpose: find the node with the minimum value in the tree
// args: node pointer
// rets: node pointer (minimum node)
Node *BinarySearchTree::find_min(Node *node) const
{
	if (node->left == NULL){
		return node;
	}
	else{
		return find_min(node->left);
	}
}

// purpose: find the maximum value in the tree
// args: none
// rets: int (maximum node data value)
int BinarySearchTree::find_max() const
{
	if (root == NULL){
		return INT_MAX;
	}
	Node *max = find_max(root);
	return max->data;
}

// purpose: find the node with the maximum value in the tree
// args: node pointer
// rets: node pointer (maximum node)
Node *BinarySearchTree::find_max(Node *node) const
{
	if (node->right == NULL){
		return node;
	}
	else{
		return find_max(node->right);
	}
}

// purpose: check if a tree contains a node with a certain value
// args: int (value being checked)
// rets: bool- true if tree contains, false otherwise
bool BinarySearchTree::contains(int value) const
{
	return contains(root, value);

}

// purpose: check if a tree contains a node with a certain value
// args: node pointers (for traversal), int (value being checked)
// rets: bool- true if tree contains, false otherwise
bool BinarySearchTree::contains(Node *node, int value) const
{
	if (node == NULL){
		return false;
	}
	if (node->data == value){
		return true;
	}
	else if(node->data < value){
		return contains(node->right, value);
	}
	else if(node->data > value){
		return contains(node->left, value);
	}
	return false;
}

// purpose: insert a value into the tree
// args: int (value to insert)
// rets: none
void BinarySearchTree::insert(int value)
{
        insert(root, NULL, value);
}

// purpose: insert a value into the tree
// args: int (value to insert), node pointer and pointer to parent node
//rets: node
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
        // insert at root if it is empty
	if (root == NULL){
		Node *new_node = new Node;
		root = new_node;
		insert_help(root, value);
	}
	else if (node == NULL){
		Node *new_node = new Node;
		node = new_node;
		insert_help(node, value);
		if (value > parent->data){
			parent->right = node;
		}
		if (value < parent->data){
			parent->left = node;
		}
	}
	else if (node->data > value){
		insert(node->left, node, value);
	}
	else if (node->data < value){
		insert(node->right, node, value);
	}
	else if (node->data == value){
		node->count++;
	}
}

// purpose: create a new node and assign data, count, left, right
// args: node pointer
// rets: none
void BinarySearchTree::insert_help(Node *node, int value)
{
	node->data = value;
	node->count = 1;
	node->left = NULL;
	node->right = NULL;
}
// purpose: remove a value from a tree
// args: int (value to remove)
// rets: bool (true if removed, false if not)
bool BinarySearchTree::remove(int value)
{
        return remove(root, NULL, value);
}

// purpose: remove a node containing a certain value from the tree, attending
//	    differences between if the node to be removed is a leaf, has one
//	    child, or has two children
// args: node pointer, parent pointer, value to be removed
// rets: bool (true if removed, false if not)
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
	if (root == NULL){
		return false;
	}
	if (contains(node, value) == false){
		return false;
	}
	if (node->data == value){
		if (node->count > 1){
			node->count --;
		}
		else if (node->left == NULL and node->right == NULL){
			no_children(node, parent);
		}
		else if (node->left == NULL and node->right != NULL){
			one_child(node, node->right, parent);
		}
		else if (node->left != NULL and node->right == NULL){
			one_child (node, node->left, parent);
		}
		else{
			two_children(node);
		}
		return true;
	}
	else if(node->data < value){
		return remove(node->right, node, value);
	}
	else if(node->data > value){
		return remove(node->left, node, value);
	}
	return false;
}

// purpose: helper function for the remove function for the no children case
// args: node pointer, pointer to parent node
// rets: none
void BinarySearchTree::no_children(Node *node, Node *parent)
{
	if (node == root){
		delete node;
		root = NULL;
	}
	else if (parent->data > node->data){
		delete node;
		parent->left = NULL;
	}
	else if (parent->data < node->data){
		delete node;
		parent->right = NULL;
	}
}
// purpose: helper function for the remove function for the one child case
// args: node pointer, pointer to parent of node, int value
// rets: none
void BinarySearchTree::one_child(Node *node, Node *child, Node *parent)
{
	if (node == root){
		delete node;
		root = child;
	}
	else if (parent->left == node){
		delete node;
		parent->left = child;
	}
	else if (parent->right == node){
		delete node;
		parent->right = child;
	}
}

// purpose: helper function for the remove function for the two children case
// args: node pointer
// rets: none
void BinarySearchTree::two_children(Node *node)
{
	Node *min = find_min(node->right);
	Node *parent = find_parent(node, min);
	node->data = min->data;
	node->count = min->count;
	if (min->left == NULL and min->right == NULL){
		if (parent->data > min->data){
			parent->left = NULL;
		}
		if (parent->data <= min->data){
			parent->right = NULL;
		}
		delete min;
	}
	else if (min->left == NULL and min->right != NULL){
		one_child(min, min->right, parent);
	}
	else if (min->left != NULL and min->right == NULL){
		one_child (min, min->left, parent);
	}
	//no case needed for if min has two children
}

// purpose: return the height of the tree- longest path to leaf from root
// args: none
// rets: int (height)
int BinarySearchTree::tree_height() const
{
        return tree_height(root) - 1;
}

// purpose: find the height of the tree- longest path to leaf from root
// args: node pointer
// rets: int (height)
int BinarySearchTree::tree_height(Node *node) const
{
	if (node == NULL){
		return 0;
	}
	int left = tree_height(node->left);
	int right = tree_height(node->right);
	if (left >= right){
		return left + 1;
	}
	else{
		return right + 1;
	}
}

// returns the total number of nodes
int BinarySearchTree::node_count() const
{
        return node_count(root);
}
// purpose: count all the nodes in a tree
// args: node pointer
// rets: int (number of nodes)
int BinarySearchTree::node_count(Node *node) const
{
	if (node == NULL){
		return 0;
	}
	else{
		return 1 + node_count(node->left) + node_count(node->right);
	}
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

// purpose: find the sum of all the nodes (accounting for duplicates
// args: node pointer
// rets: int (sum)
int BinarySearchTree::count_total(Node *node) const
{
	if (node == NULL){
		return 0;
	}
	else if (node->count > 0){
		return (node->data * node->count)+ count_total(node->left)
				+ count_total(node->right);
	}
	else{
		return count_total(node->left) + count_total(node->right);
	}
}
// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}

// purpose: find the parent of a certain child node
// args: pointer node and node pointing to child
// rets: node pointer (parent node)
Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
        if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left==child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}
