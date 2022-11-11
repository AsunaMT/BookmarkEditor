#ifndef BMK_ELEMENTS_H_
#define BMK_ELEMENTS_H_

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <ui>

const bool DEFAULT_DIRTY = false;
const bool DEFAULT_TITLE_START_INDEX = 0;
const unsigned DEFAULT_TITLE_LEVEL = 1;

enum BmkElementType { kTitle, kBookmark };

class BmkElements : public TreeNode {
 private:
  std::string name_;
  BmkElements* parent_;

  virtual auto set_level(const unsigned& level) -> void = 0;

 protected:
 public:
  virtual auto get_name() const -> std::string = 0;
  virtual auto set_name(const std::string& name) -> void = 0;
  virtual auto get_parent() const -> BmkElements* = 0;
  virtual auto set_parent(BmkElements* bmk) -> void = 0;
  virtual auto GetType() const -> BmkElementType = 0;
  virtual auto Add(BmkElements* node) -> void = 0;
  virtual auto Remove(const std::string& name, const BmkElementType& type)
      -> void = 0;
  virtual auto GetLabel() const -> std::string = 0;
  virtual auto GetInnerBmk(const std::string& name) const -> BmkElements* = 0;
  virtual auto Read() -> void = 0;
  virtual auto Find(const std::string& name, const BmkElementType& type) const
      -> BmkElements* = 0;
  virtual auto get_level() const -> unsigned = 0;
  virtual auto ShowMdFormat() const -> std::string = 0;
  // virtual BmkElements* Enter() = 0;
  // virtual BmkElements* GetNode(int index);
};

class Title : public BmkElements {
 private:
  unsigned level_;
  std::deque<std::unique_ptr<BmkElements>> elements_;
  unsigned title_start_index_;
  std::string name_;
  BmkElements* parent_;
  class TitleLableProvider : public LabelProvider<Title> {
   public:
    auto LableOf(const Title& title) const -> std::string;
  };
  constexpr static const TitleLableProvider title_label_provider_ =
      TitleLableProvider();

  auto set_level(const unsigned& level) -> void;

 protected:
 public:
  Title(const std::string& name, const unsigned& level = DEFAULT_TITLE_LEVEL);
  Title(const BmkElements& title);
  Title(const Title& title);
  auto get_name() const -> std::string;
  auto set_name(const std::string& name) -> void;
  auto get_parent() const -> BmkElements*;
  auto set_parent(BmkElements* bmk) -> void;
  auto GetType() const -> BmkElementType;
  auto Add(BmkElements* node) -> void;
  auto Remove(const std::string& name, const BmkElementType& type) -> void;
  auto GetLabel() const -> std::string;
  auto GetList() const -> std::deque<const TreeNode*>;
  auto HasChild() const -> bool;
  auto ShowStr() const -> std::string;
  auto GetInnerBmk(const std::string& name) const -> BmkElements*;
  auto Read() -> void;
  auto Find(const std::string& name, const BmkElementType& type) const
      -> BmkElements*;
  auto DeepRemove(const std::string& name, const BmkElementType& type) -> void;
  auto get_level() const -> unsigned;
  auto ShowMdFormat() const -> std::string;
};

class Bookmark : public BmkElements {
 private:
  std::string name_;
  BmkElements* parent_;
  std::string url_;
  bool dirty_;
  class BookmarkLableProvider : public LabelProvider<Bookmark> {
   public:
    auto LableOf(const Bookmark& bookmark) const -> std::string;
  };
  constexpr static const BookmarkLableProvider bookmark_label_provider_ =
      BookmarkLableProvider();

  auto set_level(const unsigned& level) -> void;

 protected:
 public:
  Bookmark(const std::string& name, const std::string& url = "");
  Bookmark(const Bookmark& bookmark);
  auto get_name() const -> std::string;
  auto set_name(const std::string& name) -> void;
  auto get_parent() const -> BmkElements*;
  auto set_parent(BmkElements* bmk) -> void;
  auto get_url() const -> std::string;
  auto set_url(const std::string& url) -> void;
  auto GetType() const -> BmkElementType;
  auto Add(BmkElements* node) -> void;
  auto Remove(const std::string& name, const BmkElementType& type) -> void;
  auto GetLabel() const -> std::string;
  auto GetList() const -> std::deque<const TreeNode*>;
  auto HasChild() const -> bool;
  auto ShowStr() const -> std::string;
  auto Read() -> void;
  auto GetInnerBmk(const std::string& name) const -> BmkElements*;
  auto Find(const std::string& name, const BmkElementType& type) const
      -> BmkElements*;
  auto get_level() const -> unsigned;
  auto ShowMdFormat() const -> std::string;
};

#endif