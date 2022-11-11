#ifndef SHOWFILE_ADAPTER_H_
#define SHOWFILE_ADAPTER_H_

#include <ui_sys/show_tree.h>

#include <deque>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

class FileNode : public TreeNode {
 private:
  std::string path_;
  std::deque<std::unique_ptr<FileNode>> files;

 public:
  FileNode(std::string path);
  auto MakeFiletree() -> void;
  auto GetList() const -> std::deque<const TreeNode*>;
  auto HasChild() const -> bool;
  auto ShowStr() const -> std::string;
};

#endif