#ifndef BMK_ELEMENTS_H_
#define BMK_ELEMENTS_H_

#include <deque>
#include <iostream>
#include <memory>
#include <string>

#include "ui_sys/label_provider.h"
#include "ui_sys/show_tree.h"

enum BmkElementType { kTitle, kBookmark };

class BmkElements : public TreeNode {
 private:
  std::string name_;

 public:
  auto getName() const -> std::string;
  auto setName(std::string name) -> void;
  virtual auto GetType() const -> BmkElementType = 0;
  virtual auto Add(BmkElements* node) -> void = 0;
  virtual auto Remove(std::string name) -> void = 0;
  virtual auto GetLabel() const -> std::string = 0;
  // virtual BmkElements* Enter() = 0;
  // virtual BmkElements* GetNode(int index);
};

class Title : public BmkElements {
 private:
  std::deque<std::unique_ptr<BmkElements>> elements_;
  int bmk_start_index_;
  std::string name_;

 public:
  class TitleLableProvider : public LabelProvider<Title> {
   public:
    auto LableOf(const Title& title) -> std::string { return title.getName(); }
  };
  Title(std::string name);
  Title(const BmkElements& title);
  auto GetType() const -> BmkElementType;
  auto Add(BmkElements* node) -> void;
  auto Remove(std::string name) -> void;
  auto GetLabel() const -> std::string;
  auto GetList() const -> std::deque<TreeNode>;
  auto HasChild() const -> bool;
  auto ShowStr() const -> std::string;
};

class Bookmark : public BmkElements {
 private:
  std::string url_;
  bool dirty_;
  std::string name_;

 public:
  Bookmark(std::string name);
  Bookmark(const Title& bookmark);
  auto getUrl() const -> std::string;
  auto setUrl(std::string name) -> void;
  auto GetType() const -> BmkElementType;
  auto Add(BmkElements* node) -> void;
  auto Remove(std::string name) -> void;
  auto GetLabel() const -> std::string;
  auto GetList() const -> std::deque<TreeNode>;
  auto HasChild() const -> bool;
  auto ShowStr() const -> std::string;
};

#endif