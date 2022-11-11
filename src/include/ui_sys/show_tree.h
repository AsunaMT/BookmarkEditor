#ifndef SHOW_TREE_H_
#define SHOW_TREE_H_

#include <deque>
#include <iostream>
#include <string>
#include <vector>

class TreeNode {
 public:
  virtual auto GetList() const -> std::deque<const TreeNode*> = 0;
  virtual auto HasChild() const -> bool = 0;
  virtual auto ShowStr() const -> std::string = 0;
};

class ShowTree {
 private:
  TreeNode* root_;
  int pathDeep;
  std::string target;
  std::vector<std::string> str_list_;

 public:
  ShowTree(TreeNode* root);
  auto getTreeStr() -> std::string;
  auto getTreeStr(const TreeNode& node) -> void;
};

#endif