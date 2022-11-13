#include <commands/add_cmd.h>

#include <cstddef>
#include <iostream>
#include <locale>
#include <memory>
#include <ostream>

#include "bmk_sys/bmk_element.h"
#include "bmk_sys/bookmark.h"
#include "bmk_sys/title.h"
#include "commands/command.h"

std::deque<AddHistoryInfo> AddCmd::history_{};
unsigned AddCmd::history_max_ = DEFAULT_ADD_HISTORY_MAX;
std::deque<AddCacheInfo> AddCmd::cache_{};

AddCmd::AddCmd(const AddCmd& addCmd) : add_info_(addCmd.add_info_) {}
AddCmd::AddCmd(AddInfo&& add_info) : add_info_(add_info) {}

auto AddCmd::excute() -> void {
  Title* title_;
  if (add_info_.name == "") {
    title_ = add_info_.root;
  } else {
    title_ = (Title*)add_info_.root->Find(add_info_.name, kTitle);
  }
  if (title_ == nullptr) return;
  history_.emplace_back(AddHistoryInfo{title_, title_->Add(add_info_.node)});
  // if (history_.size() > history_max_) {
  //   history_.pop_front();
  // }
}

auto AddCmd::undo() -> void {
  if (history_.empty()) return;
  auto& toUnode = history_.back();
  cache_.emplace_back(AddCacheInfo());
  cache_.back().title = toUnode.title;
  switch (toUnode.node->GetType()) {
    case kTitle:
      cache_.back().node = std::make_unique<Title>(*(Title*)toUnode.node);
      toUnode.title->Remove(toUnode.node->get_name(), kTitle);
      break;
    case kBookmark:
      cache_.back().node = std::make_unique<Bookmark>(*(Bookmark*)toUnode.node);
      toUnode.title->Remove(toUnode.node->get_name(), kBookmark);
      break;
    default:
      break;
  }
  if (cache_.size() > DEFAULT_CACHE_MAX) cache_.pop_front();
  // toUnode.title->Remove(toUnode.node->get_name(),kTitle);
  history_.pop_back();
}

auto AddCmd::redo() -> void {
  if (cache_.back().node == nullptr) {
    std::cout << "You can't redo now, because there're no undo command before."
              << std::endl;
    return;
  }
  cache_.back().title->Add(cache_.back().node.get());
  cache_.pop_back();
  // cache_ = {nullptr, nullptr};
}