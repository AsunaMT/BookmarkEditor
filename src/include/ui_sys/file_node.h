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
  FileNode(std::string path) : path_(path){};

  auto MakeFiletree() -> void {
    files.clear();
    if (std::filesystem::is_directory(path_)) {
      for (const auto& entry : std::filesystem::directory_iterator(path_)) {
        files.push_back(std::make_unique<FileNode>(entry.path().string()));
        files.back()->MakeFiletree();
      }
    }
  }

  auto GetList() const -> std::deque<const TreeNode*> {
    std::deque<const TreeNode*> target;
    for (const auto& file : files) {
      target.push_back(file.get());
    }
    return target;
  }

  auto HasChild() const -> bool {
    return std::filesystem::is_directory(path_);
  };

  auto ShowStr() const -> std::string {
    auto str =
        std::filesystem::directory_entry(path_).path().filename().string();
    return std::filesystem::is_directory(path_) ? str : "\"" + str + "\"";
  };
};

#endif