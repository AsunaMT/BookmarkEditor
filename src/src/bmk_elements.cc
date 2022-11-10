#include "bmk_sys/bmk_elements.h"

#include <cstddef>
#include <memory>

#include "ui_sys/show_tree.h"

// Title::TitleLableProvider title_label_provider_;
// Bookmark::BookmarkLableProvider bookmark_label_provider_;

// auto BmkElements::get_name() const -> std::string { return this->name_; }

// auto BmkElements::set_name(const std::string& name) -> void { this->name_ =
// name; }

Title::Title(const std::string& name)
    : name_(name),
      parent_(nullptr),
      title_start_index_(INIT_TITLE_START_INDEX) {}

Title::Title(const BmkElements& title) {
  name_ = title.get_name();
  parent_ = nullptr;
  title_start_index_ = 0;
}

Title::Title(const Title& title) {
  name_ = title.get_name();
  parent_ = nullptr;
  title_start_index_ = 0;
  for (auto& bmk : title.elements_) {
    this->Add(bmk.get());
  }
}

auto Title::get_name() const -> std::string { return name_; }
auto Title::set_name(const std::string& name) -> void { name_ = name; }
auto Title::GetType() const -> BmkElementType { return kTitle; }

auto Title::Add(BmkElements* node) -> void {
  switch (node->GetType()) {
    case kTitle: {
      elements_.push_back(std::make_unique<Title>(*(Title*)node));
      break;
    }
    case kBookmark: {
      elements_.insert(elements_.begin() + title_start_index_,
                       std::make_unique<Bookmark>(*(Bookmark*)node));
      title_start_index_++;
      break;
    }
    default:;
  }
  // elements_.push_back(std::make_unique<Title>(*node));
}

auto Title::Remove(const std::string& name, const BmkElementType& type)
    -> void {
  for (int i = 0; i < elements_.size();) {
    if (elements_[i]->get_name() == name && elements_[i]->GetType() == type) {
      elements_[i] = nullptr;
      elements_.erase(elements_.begin() + i);
      if (type == kBookmark) title_start_index_--;
    } else {
      i++;
    }
  }
}

auto Title::GetLabel() const -> std::string {
  return title_label_provider_.LableOf(*this);
}

auto Title::GetList() const -> std::deque<const TreeNode*> {
  std::deque<const TreeNode*> target;
  for (auto& i : elements_) {
    target.push_back(i.get());
  }
  return target;
}
auto Title::HasChild() const -> bool { return true; }
auto Title::ShowStr() const -> std::string { return GetLabel(); }
auto Title::GetInnerBmk(const std::string& name) const -> BmkElements* {
  for (auto& bmk : elements_) {
    if (bmk->get_name() == name) {
      return bmk.get();
    }
  }
  return nullptr;
}

auto Title::Read() -> void {
  std::cout << "Warning: You can't do this operation(Read) on a title."
            << std::endl;
}

auto Title::Find(const std::string& name, const BmkElementType& type) const
    -> BmkElements* {
  for (auto& bmk : elements_) {
    const std::string& thisName = bmk->get_name();
    const BmkElementType& thisType = bmk->GetType();
    if (thisName == name && thisType == type) {
      return bmk.get();
    }
    if (thisType == kTitle) {
      auto tar = ((Title*)bmk.get())->Find(name, type);
      if (tar != nullptr) return tar;
    }
  }
  return nullptr;
}

auto Title::DeepRemove(const std::string& name, const BmkElementType& type)
    -> void {
  for (int i = 0; i < elements_.size();) {
    const std::string& thisName = elements_[i]->get_name();
    const BmkElementType& thisType = elements_[i]->GetType();
    if (thisName == name && thisType == type) {
      // std::cout << thisName << " " << thisType << std::endl;
      // std::cout << name << " " << type << std::endl;
      elements_[i] = nullptr;
      elements_.erase(elements_.begin() + i);
      if (type == kBookmark) title_start_index_--;
    } else {
      if (thisType == kTitle) {
        ((Title*)elements_[i].get())->DeepRemove(name, type);
      }
      i++;
    }
  }
}

Bookmark::Bookmark(const std::string& name, const std::string& url)
    : name_(name), parent_(nullptr), url_(url), dirty_(INIT_DIRTY) {}

Bookmark::Bookmark(const Bookmark& bookmark)
    : dirty_(INIT_DIRTY), parent_(nullptr) {
  name_ = bookmark.get_name();
  url_ = bookmark.get_url();
}

auto Bookmark::get_name() const -> std::string { return name_; }
auto Bookmark::set_name(const std::string& name) -> void { name_ = name; }
auto Bookmark::get_url() const -> std::string { return url_; }

auto Bookmark::set_url(const std::string& url) -> void { url_ = url; }

auto Bookmark::GetType() const -> BmkElementType { return kBookmark; }

auto Bookmark::Add(BmkElements* node) -> void {
  std::cout << "Warning: You can't do this operation(Add) on a bookmark."
            << std::endl;
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
        .LableOf(*this);
  } else {
    return QuoteLabelProvider<Bookmark>(bookmark_label_provider_)
        .LableOf(*this);
  }
}

auto Bookmark::GetList() const -> std::deque<const TreeNode*> {
  std::cout << "Warning: You can't do this operation(GetList) on a bookmark."
            << std::endl;
  return std::deque<const TreeNode*>(0, nullptr);
}

auto Bookmark::HasChild() const -> bool { return false; }

auto Bookmark::ShowStr() const -> std::string { return GetLabel(); }

auto Title::TitleLableProvider::LableOf(const Title& title) const
    -> std::string {
  return title.get_name();
}

auto Bookmark::BookmarkLableProvider::LableOf(const Bookmark& bookmark) const
    -> std::string {
  return bookmark.get_name();
}
auto Bookmark::Read() -> void { dirty_ = true; }

auto Bookmark::GetInnerBmk(const std::string& name) const -> BmkElements* {
  std::cout
      << "Warning: You can't do this operation(GetInnerBmk) on a bookmark."
      << std::endl;
  return nullptr;
}

auto Bookmark::Find(const std::string& name, const BmkElementType& type) const
    -> BmkElements* {
  std::cout << "Warning: You can't do this operation(Find) on a bookmark."
            << std::endl;
  return nullptr;
}