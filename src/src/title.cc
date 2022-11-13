#include "bmk_sys/title.h"

#include <fstream>
#include <iterator>
#include <string>

#include "bmk_sys/bmk_element.h"
#include "bmk_sys/bookmark.h"

// Title::TitleLableProvider title_label_provider_;
// Bookmark::BookmarkLableProvider bookmark_label_provider_;

// auto BmkElement::get_name() const -> std::string { return this->name_; }

// auto BmkElement::set_name(const std::string& name) -> void { this->name_ =
// name; }

Title::Title(const std::string& name, const unsigned& level)
    : level_(level),
      name_(name),
      parent_(nullptr),
      title_start_index_(DEFAULT_TITLE_START_INDEX) {}

Title::Title(const BmkElement& title) {
  level_ = title.get_level();
  name_ = title.get_name();
  parent_ = nullptr;
  title_start_index_ = 0;
}

Title::Title(const Title& title) {
  level_ = title.get_level();
  name_ = title.get_name();
  parent_ = title.parent_;
  title_start_index_ = 0;
  for (auto& bmk : title.elements_) {
    this->Add(bmk.get());
  }
}

auto Title::get_name() const -> std::string { return name_; }
auto Title::set_name(const std::string& name) -> void { name_ = name; }
auto Title::set_level(const unsigned& level) -> void {
  level_ = level;
  for (auto& bmk : elements_) {
    if (bmk->GetType() == kTitle) {
      auto child = (Title*)(bmk.get());
      child->set_level(level + 1);
    }
  }
}
auto Title::get_level() const -> unsigned { return level_; }
auto Title::get_parent() const -> BmkElement* { return parent_; }
auto Title::set_parent(BmkElement* bmk) -> void {
  if (bmk->GetType() != kTitle) {
    std::cout << "Warning: Bookmark can't be a home directory ." << std::endl;
    return;
  }
  parent_ = bmk;
  auto parent = (Title*)bmk;
  // std::cout << parent->get_level() + 1 << std::endl;
  set_level(parent->get_level() + 1);
}
auto Title::GetType() const -> BmkElementType { return kTitle; }

auto Title::Add(BmkElement* node) -> BmkElement* {
  switch (node->GetType()) {
    case kTitle: {
      node->set_parent(this);
      elements_.emplace_back(std::make_unique<Title>(*(Title*)node));
      return elements_.back().get();
      break;
    }
    case kBookmark: {
      node->set_parent(this);
      elements_.emplace(elements_.begin() + title_start_index_,
                        std::make_unique<Bookmark>(*(Bookmark*)node));
      title_start_index_++;
      return elements_[title_start_index_ - 1].get();
    }
    default:;
  }
  return nullptr;
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
  return title_label_provider_.LabelOf(*this);
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
auto Title::GetInnerBmk(const std::string& name) const -> BmkElement* {
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
    -> BmkElement* {
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
    -> bool {
  for (int i = 0; i < elements_.size();) {
    const std::string& thisName = elements_[i]->get_name();
    const BmkElementType& thisType = elements_[i]->GetType();
    if (thisName == name && thisType == type) {
      // std::cout << thisName << " " << thisType << std::endl;
      // std::cout << name << " " << type << std::endl;
      elements_[i] = nullptr;
      elements_.erase(elements_.begin() + i);
      if (type == kBookmark) title_start_index_--;
      return true;
    } else {
      if (thisType == kTitle) {
        if (((Title*)elements_[i].get())->DeepRemove(name, type)) return true;
        //(Title*)elements_[i].get())->DeepRemove(name, type);
      }
      i++;
    }
  }
  return false;
}

auto Title::ShowMdFormat() const -> std::string {
  return MdTitleLableProvider<Title>(title_label_provider_).LabelOf(*this);
}

auto Title::GenerateBmk(std::ofstream& out) const -> void {
  std::string target;
  for (auto& i : elements_) {
    out << i->ShowMdFormat() << std::endl;
    if (i->GetType() == kTitle) {
      ((Title*)i.get())->GenerateBmk(out);
    }
  }
}

auto Title::TitleLableProvider::LabelOf(const Title& title) const
    -> std::string {
  return title.get_name();
}

auto Title::ExactRemove(BmkElement* bmk) -> void {
  for (int i = 0; i < elements_.size(); i++) {
    if (elements_[i].get() == bmk) {
      elements_.erase(elements_.begin() + i);
      break;
    }
  }
}