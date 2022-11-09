#ifndef SHOW_TREE_H_
#define SHOW_TREE_H_

#include <deque>
#include <string>
#include <vector>

class TreeNode {
 public:
  virtual auto GetList() const -> std::deque<TreeNode> = 0;
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
  ShowTree(TreeNode* root) : root_(root) {
    target = "";
    str_list_.clear();
  }
  auto getTreeStr() -> std::string const {
    getTreeStr(*root_);
    return target;
  }
  auto getTreeStr(const TreeNode& node) -> void const {
    auto obj_arr = node.GetList();
    pathDeep++;
    // 遍历每行时，将其分成两部分：行首和File部分。
    // 其中File部分要先判断是目录还是文件，再判断是否是当前目录最后的一个File，在Filename前打印出相应的符号

    for (int i = 0; i < obj_arr.size(); i++) {
      // 输出行首
      for (int j = 0; j < pathDeep - 1; j++) {
        target.append(str_list_[j]);
      }

      //判断当前文件是否是路径
      if (obj_arr[i].HasChild()) {
        //判断是不是最后一个目录
        if (i == obj_arr.size() - 1) {
          //是最后一个目录时
          target.append("└─");
          str_list_.emplace(str_list_.begin() + pathDeep - 1,
                            "  ");  // add(pathDeep - 1, "  ");
        } else {
          //非最后一个目录时
          str_list_.emplace(str_list_.begin() + pathDeep - 1,
                            "│ ");  // add(pathDeep - 1, "│ ");
          target.append("├─");
        }
        //输出此时目录的名字
        target.append(obj_arr[i].ShowStr());
        //递归遍历
        getTreeStr(obj_arr[i]);

        //如果不是目录而是文件
      } else {
        //先判断当前文件是不是最后一个文件
        if (i == obj_arr.size() - 1) {
          target.append("└─");
        } else {
          target.append("├─");
        }
        target.append(obj_arr[i].ShowStr());
      }
    }
    pathDeep--;
  }
};

#endif