#include <ui_sys/file_node.h>

#include <filesystem>

FileNode::FileNode(std::string path) : path_(path){};

auto FileNode::MakeFiletree() -> void {
  files.clear();
  if (std::filesystem::is_directory(path_)) {
    for (const auto& entry : std::filesystem::directory_iterator(path_)) {
      files.push_back(std::make_unique<FileNode>(entry.path().string()));
      files.back()->MakeFiletree();
    }
  }
}

auto FileNode::GetList() const -> std::deque<const TreeNode*> {
  std::deque<const TreeNode*> target;
  for (const auto& file : files) {
    target.push_back(file.get());
  }
  return target;
}

auto FileNode::HasChild() const -> bool {
  return std::filesystem::is_directory(path_);
};

auto FileNode::ShowStr() const -> std::string {
  auto str = std::filesystem::directory_entry(path_).path().filename().string();
  return std::filesystem::is_directory(path_) ? str : "\"" + str + "\"";
};