#ifndef SHOWFILE_ADAPTER_H_
#define SHOWFILE_ADAPTER_H_

#include <corecrt_wstdio.h>

#include <deque>
#include <filesystem>
#include <iostream>
#include <string>

#include "ui_sys/show_tree.h"

class FileNode : TreeNode {
 private:
  std::string path_;

 public:
  FileNode(std::string path) : path_(path){};
  auto GetList() const -> std::deque<TreeNode> {
    std::deque<TreeNode> target;
    for (const auto& entry : std::filesystem::directory_iterator(path_))
      target.push_back(FileNode(entry.path().string()));
    return target;
  }
  auto HasChild() const -> bool {
    return std::filesystem::is_directory(path_);
  };
  auto ShowStr() const -> std::string {
    return std::filesystem::is_directory(path_) ? path_ : "\"" + path_ + "\"";
  };
};

#endif