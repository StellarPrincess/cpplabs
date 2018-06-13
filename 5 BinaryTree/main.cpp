#include <iostream>
#include "BinaryTree.h"

int main() {
    BinaryTree tree = BinaryTree();

    tree.put(1, {});
    tree.put(2, {true});
    tree.put(3, {false});
    tree.put(4, {true, false});
    tree.put(5, {false, false});

    std::cout << "original tree: " << std::endl
              << tree << std::endl
              << "evenCount: " << tree.evenCount() << std::endl
              << "isAllPositive: " << (tree.isAllPositive() ? "true" : "false") << std::endl
              << "average: " << tree.average() << std::endl;
    std::vector<bool> way = tree.find(4);
    std::cout << "way to 4: " << std::endl;
    for (auto &&i : way) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    way = tree.find(3);
    std::cout << "way to 3: " << std::endl;
    for (auto &&i : way) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    way = tree.find(1);
    std::cout << "way to 1: " << std::endl;
    for (auto &&i : way) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "========================" << std::endl;

    BinaryTree nonPositiveTree = BinaryTree();
    nonPositiveTree.put(-5, {});
    nonPositiveTree.put(10, {false});
    nonPositiveTree.put(2, {false, true});
    std::cout << "original nonPositiveTree: " << std::endl
              << nonPositiveTree << std::endl
              << "evenCount: " << nonPositiveTree.evenCount() << std::endl
              << "isAllPositive: " << (nonPositiveTree.isAllPositive() ? "true" : "false") << std::endl
              << "========================" << std::endl;

    try {
        tree.put(9, {false, false, false, false});
    } catch (const char* e) {
        std::cout << e << std::endl
                  << "========================" << std::endl;
    }

    BinaryTree copyTree = BinaryTree(tree);
    std::cout << "copied tree: " << std::endl
              << copyTree << std::endl
              << "========================" << std::endl;

    copyTree.put(45, {true});
    copyTree.put(23, {false, false, true});
    std::cout << "original tree: " << std::endl
              << tree << std::endl;

    std::cout << "copied tree: " << std::endl
              << copyTree << std::endl
              << "========================" << std::endl;

    copyTree.clear();
    std::cout << "original tree: " << std::endl
              << tree << std::endl;
    std::cout << "cleared copied tree: " << std::endl
              << copyTree << std::endl
              << "========================" << std::endl;

    copyTree = tree;
    std::cout << "copied tree: " << std::endl
              << copyTree << std::endl
              << "========================" << std::endl;

    BinaryTree moveTree(std::move(tree));
    std::cout << "original tree after move: " << std::endl
              << tree << std::endl;

    std::cout << "copied tree: " << std::endl
              << copyTree << std::endl;

    std::cout << "moved tree: " << std::endl
              << moveTree << std::endl
              << "========================" << std::endl;

    moveTree.deleteAllLeafs();
    std::cout << "moved tree after deleting all leafs: " << std::endl
              << moveTree << std::endl
              << "========================" << std::endl;

    return 0;
}
