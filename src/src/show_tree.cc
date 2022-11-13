#include <ui_sys/show_tree.h>

ShowTree::ShowTree(TreeNode* root) : root_(root) {
  target = "";
  pathDeep = 0;
}

auto ShowTree::getTreeStr() -> std::string {
  getTreeStr(*root_);
  auto res = target;
  target.clear();
  return res;
}
auto ShowTree::getTreeStr(const TreeNode& node) -> void {
  auto obj_arr = node.GetList();
  pathDeep++;
  // 遍历每行时，将其分成两部分：行首和File部分。
  // 其中File部分要先判断是目录还是文件，再判断是否是当前目录最后的一个File，在Filename前打印出相应的符号

  for (int i = 0; i < obj_arr.size(); i++) {
    // 输出行首
    for (int j = 0; j < pathDeep - 1; j++) {
      // std::cout << target.append(str_list_[j]);
      target.append(str_list_[j]);
    }

    //判断当前文件是否是路径
    if (obj_arr[i]->HasChild()) {
      //判断是不是最后一个目录
      if (i == obj_arr.size() - 1) {
        //是最后一个目录时
        // std::cout << target.append("└─");
        target.append("└─");
        str_list_.emplace(str_list_.begin() + pathDeep - 1,
                          "  ");  // add(pathDeep - 1, "  ");
      } else {
        //非最后一个目录时
        str_list_.emplace(str_list_.begin() + pathDeep - 1,
                          "│ ");  // add(pathDeep - 1, "│ ");
        // std::cout << target.append("├─");
        target.append("├─");
      }
      //输出此时目录的名字
      // std::cout << target.append(obj_arr[i]->ShowStr() + "\n");
      target.append(obj_arr[i]->ShowStr() + "\n");
      //递归遍历
      getTreeStr(*obj_arr[i]);

      //如果不是目录而是文件
    } else {
      //先判断当前文件是不是最后一个文件
      if (i == obj_arr.size() - 1) {
        // std::cout << target.append("└─");
        target.append("└─");
      } else {
        // std::cout << target.append("├─");
        target.append("├─");
      }
      // std::cout << target.append(obj_arr[i]->ShowStr() + "\n");
      target.append(obj_arr[i]->ShowStr() + "\n");
    }
  }
  pathDeep--;
}