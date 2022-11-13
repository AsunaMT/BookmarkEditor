#ifndef BMK_SYS_BOOKMARK_H_
#define BMK_SYS_BOOKMARK_H_

#include "bmk_element.h"

const bool DEFAULT_DIRTY = false;
class Bookmark : public BmkElement {
 private:
  std::string name_;
  BmkElement* parent_;
  std::string url_;
  bool dirty_;
  class BookmarkLableProvider : public LabelProvider<Bookmark> {
   public:
    auto LabelOf(const Bookmark& bookmark) const -> std::string;
  };
  constexpr static const BookmarkLableProvider bookmark_label_provider_ =
      BookmarkLableProvider();

  auto set_level(const unsigned& level) -> void;

 protected:
 public:
  Bookmark(const std::string& name, const std::string& url = "");
  Bookmark(const BmkElement& bookmark);
  Bookmark(const Bookmark& bookmark);
  auto get_name() const -> std::string;
  auto set_name(const std::string& name) -> void;
  auto get_parent() const -> BmkElement*;
  auto set_parent(BmkElement* bmk) -> void;
  auto get_url() const -> std::string;
  auto set_url(const std::string& url) -> void;
  auto GetType() const -> BmkElementType;
  auto Add(BmkElement* node) -> BmkElement*;
  auto Remove(const std::string& name, const BmkElementType& type) -> void;
  auto GetLabel() const -> std::string;
  auto GetList() const -> std::deque<const TreeNode*>;
  auto HasChild() const -> bool;
  auto ShowStr() const -> std::string;
  auto Read() -> void;
  auto GetInnerBmk(const std::string& name) const -> BmkElement*;
  auto Find(const std::string& name, const BmkElementType& type) const
      -> BmkElement*;
  auto get_level() const -> unsigned;
  auto ShowMdFormat() const -> std::string;
};

#endif