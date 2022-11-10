#include "bmk_sys/bmk_elements.h"

#include <cstddef>
#include <memory>

#include "ui_sys/label_decorator.h"

static Title::TitleLableProvider label_provider_;

auto BmkElements::getName() const -> std::string { return this->name_; }

auto BmkElements::setName(std::string name) -> void { this->name_ = name; }

Title::Title(std::string name) : name_(name) {}

Title::Title(const BmkElements& title) {
  name_ = title.getName();
  bmk_start_index_ = 0;
}

auto Title::GetType() const -> BmkElementType { return kTitle; }

auto Title::Add(BmkElements* node) -> void {
  switch (node->GetType()) {
    case kTitle:
      elements_.insert(elements_.begin() + bmk_start_index_,
                       std::make_unique<Title>(*node));
      bmk_start_index_++;
      break;
    case kBookmark:
      elements_.push_back(std::make_unique<Title>(*node));
      break;
    default:;
  }
}

auto Title::Remove(std::string name) -> void {
  for (int i = 0; i < elements_.size();) {
    if (elements_[i].get()->getName() == name) {
      elements_[i] = nullptr;
      elements_.erase(elements_.begin() + i);
    } else {
      i++;
    }
  }
}

auto Title::GetLabel() const -> std::string {
  return label_provider_.LableOf(*this);
}