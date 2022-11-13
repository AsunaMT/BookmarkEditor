#include "bmk_sys/bookmark.h"

#include "bmk_sys/bmk_element.h"

Bookmark::Bookmark(const std::string& name, const std::string& url)
    : name_(name), parent_(nullptr), url_(url), dirty_(DEFAULT_DIRTY) {}

Bookmark::Bookmark(const BmkElement& bookmark)
    : dirty_(DEFAULT_DIRTY), parent_(nullptr) {
  name_ = bookmark.get_name();
}

Bookmark::Bookmark(const Bookmark& bookmark)
    : dirty_(DEFAULT_DIRTY), parent_(nullptr) {
  name_ = bookmark.name_;
  url_ = bookmark.url_;
  parent_ = bookmark.parent_;
}

auto Bookmark::get_name() const -> std::string { return name_; }
auto Bookmark::set_name(const std::string& name) -> void { name_ = name; }
auto Bookmark::get_url() const -> std::string { return url_; }
auto Bookmark::set_url(const std::string& url) -> void { url_ = url; }

auto Bookmark::get_parent() const -> BmkElement* { return parent_; }
auto Bookmark::set_parent(BmkElement* bmk) -> void { parent_ = bmk; }

auto Bookmark::GetType() const -> BmkElementType { return kBookmark; }

auto Bookmark::Add(BmkElement* node) -> BmkElement* {
  std::cout << "Warning: You can't do this operation(Add) on a bookmark."
            << std::endl;
  return nullptr;
}
auto Bookmark::Remove(const std::string& name, const BmkElementType& type)
    -> void {
  std::cout << "Warning: You can't do this operation(Remove) on a bookmark."
            << std::endl;
}
auto Bookmark::GetLabel() const -> std::string {
  if (dirty_) {
    return QuoteLabelProvider<Bookmark>(
               DirtyLabelProvider<Bookmark>(bookmark_label_provider_))
        .LabelOf(*this);
  } else {
    return QuoteLabelProvider<Bookmark>(bookmark_label_provider_)
        .LabelOf(*this);
  }
}

auto Bookmark::GetList() const -> std::deque<const TreeNode*> {
  std::cout << "Warning: You can't do this operation(GetList) on a bookmark."
            << std::endl;
  return std::deque<const TreeNode*>(0, nullptr);
}

auto Bookmark::HasChild() const -> bool { return false; }

auto Bookmark::ShowStr() const -> std::string { return GetLabel(); }

auto Bookmark::BookmarkLableProvider::LabelOf(const Bookmark& bookmark) const
    -> std::string {
  return bookmark.get_name();
}
auto Bookmark::Read() -> void { dirty_ = true; }

auto Bookmark::GetInnerBmk(const std::string& name) const -> BmkElement* {
  std::cout
      << "Warning: You can't do this operation(GetInnerBmk) on a bookmark."
      << std::endl;
  return nullptr;
}

auto Bookmark::Find(const std::string& name, const BmkElementType& type) const
    -> BmkElement* {
  std::cout << "Warning: You can't do this operation(Find) on a bookmark."
            << std::endl;
  return nullptr;
}

auto Bookmark::set_level(const unsigned& level) -> void {}
auto Bookmark::get_level() const -> unsigned { return -1; }
auto Bookmark::ShowMdFormat() const -> std::string {
  static MdLinkLableProvider<Bookmark> provider(bookmark_label_provider_);
  return provider.LabelOf(*this);
}