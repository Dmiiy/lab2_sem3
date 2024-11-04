#ifndef TREE_SORTER_H
#define TREE_SORTER_H

#include <functional>
#include "ISorter.h"
#include <vector>

template <typename T>
class TreeSorter : public ISorter<T> {
private:
    struct TreeNode {
        T value;
        TreeNode *left;
        TreeNode *right;

        TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* root = nullptr;
    std::function<bool(const T&, const T&)> comparator;
    static HelpClass helpClass;

    void insert(TreeNode*& node, const T& value) {
        if (node == nullptr) {
            node = new TreeNode(value);
        } else if (comparator(value, node->value)) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }

    void inorderTraversal(TreeNode* node, ArraySequence<T>& result) {
        if (node != nullptr) {
            inorderTraversal(node->left, result);
            result.append(node->value);
            inorderTraversal(node->right, result);
        }
    }

public:
    TreeSorter(std::function<bool(const T&, const T&)> comp = helpClass.ascending)
            : comparator(comp) {}

    void sort(ArraySequence<T> *sequence) override {
        for (int i = 0; i < sequence->getLength(); ++i) {
            insert(root, (*sequence)[i]);
        }

        ArraySequence<T> sortedValues;
        inorderTraversal(root, sortedValues);

        for (int i = 0; i < sortedValues.getLength(); ++i) {
            (*sequence)[i] = sortedValues[i];
        }
    }

    void clear(TreeNode* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    ~TreeSorter() {
        clear(root);
    }
};

template <typename T>
HelpClass TreeSorter<T>::helpClass;

#endif // TREE_SORTER_H
