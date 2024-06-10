#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <ios>
#include <memory>

template <typename T>
class splay_tree
{
private:
    struct Node
    {
        T key;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        explicit Node(T k) : key(k), left(nullptr), right(nullptr) {}
    };

    std::shared_ptr<Node> root;

    std::shared_ptr<Node> rightRotate(std::shared_ptr<Node> node) // swaps with left child and parent
    {
        auto new_parent = node->left;
        node->left = new_parent->right;
        new_parent->right = node;
        return new_parent;
    }

    std::shared_ptr<Node> leftRotate(std::shared_ptr<Node>& node)
    {
        auto new_parent = node->right;
        node->right = new_parent->left;
        new_parent->left = node;
        return new_parent;
    }

    std::shared_ptr<Node> splay(std::shared_ptr<Node> node, T key)
    {
        if (!node || node->key == key)
        {
            return node;
        }
        if (key < node->key)
        {
            if (!node->left)
            {
                return node;
            }
            if (key < node->left->key)
            {
                node->left->left = splay(node->left->left, key);
                node = rightRotate(node);
            }
            else if (key > node->left->key)
            {
                node->left->right = splay(node->left->right, key);
                if (node->left->right)
                {
                    node->left = rightRotate(node);
                }
            }
            return node->left ? rightRotate(node) : node;
        }
        else
        {
            if (!node->right)
            {
                return node;
            }
            if (key > node->right->key)
            {
                node->right->right = splay(node->right->right, key);
                node = leftRotate(node);
            }
            else if (key < node->right->key)
            {
                node->right->left = splay(node->right->left, key);
                if (node->right->left)
                {
                    node->right = leftRotate(node);
                }
            }
            return node->right ? leftRotate(node) : node;
        }
    }
public:
    splay_tree() : root(nullptr) {}

    void insert(T key)
    {
        if (!root)
        {
            root = std::make_shared<Node>(key);
            return;
        }
        root = splay(root, key);
        if (root->key == key)
        {
            return;
        }
        auto new_node = std::make_shared<Node>(key);
        if (key < root->key)
        {
            new_node->right = root;
            new_node->left = root->left;
            root->left = nullptr;
        }
        else
        {
            new_node->left = root;
            new_node->right = root->right;
            root->right = nullptr;
        }
        root = new_node;
    }

    bool find(T key)
    {
        root = splay(root, key);
        return root && root->key == key;
    }

    void erase(T key)
    {
        if (!root)
        {
            return;
        }
        root = splay(root, key);
        if (root->key != key)
        {
            return;
        }
        if (!root->left)
        {
            root = root->right;
        }
        else
        {
            auto leftSubtree = root->left;
            auto rightSubtree = root->right;

            root->left = nullptr;
            root = splay(leftSubtree, key);
            root->right = rightSubtree;
        }
    }
};

#endif //SPLAY_TREE_H
