#include <iostream>
#include <memory>

class BinarySearchTree {
    struct TreeNode;
    // typedef std::unique_ptr<TreeNode> spTreeNode;
    using spTreeNode = std::unique_ptr<TreeNode>;
    struct TreeNode {
        int data;
        spTreeNode left;
        spTreeNode right;
        TreeNode(const int &value)
            : data(value), left(nullptr), right(nullptr) {}
    };

    spTreeNode root;
    bool insert(spTreeNode &node);
    void print(const spTreeNode &) const;

  public:
    BinarySearchTree();
    void insert(const int &node);
    void print() const;
};

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

void BinarySearchTree::insert(const int &ref) {
    auto node = std::make_unique<TreeNode>(ref);
    if (root == nullptr) {
        root = std::move(node);
    } else {
        TreeNode *temp = root.get();
        TreeNode *prev = root.get();
        while (temp != nullptr) {
            prev = temp;
            if (temp->data < ref)
                temp = temp->right.get();
            else
                temp = temp->left.get();
        }
        if (prev->data < ref)
            prev->right = std::move(node);
        else
            prev->left = std::move(node);
    }
}

void BinarySearchTree::print() const { print(root); }

void BinarySearchTree::print(const std::unique_ptr<TreeNode> &node) const {
    if (node == nullptr)
        return;
    print(node->left);
    std::cout << node->data << std::endl;
    print(node->right);
}

int main() {
    BinarySearchTree bst;
    bst.insert(13);
    bst.insert(3);
    bst.insert(5);
    bst.insert(31);
    bst.print();
    return 0;
}