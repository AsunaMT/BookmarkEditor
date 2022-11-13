#include "commands/delete_cmd.h"

#include <memory>
#include <ostream>
#include <utility>

#include "bmk_sys/bmk_element.h"
#include "bmk_sys/bookmark.h"
#include "bmk_sys/title.h"

std::deque<DeleteHistoryInfo> DeleteCmd::history_{};
unsigned DeleteCmd::history_max_ = DEFAULT_DELETE_HISTORY_MAX;
DeleteCacheInfo DeleteCmd::cache_ = {0};

DeleteCmd::DeleteCmd(const DeleteCmd& deleteCmd)
    : delete_info_(deleteCmd.delete_info_) {}
DeleteCmd::DeleteCmd(DeleteInfo&& delete_info) : delete_info_(delete_info) {}

auto DeleteCmd::excute() -> void {
  BmkElement* node;
  history_.push_back(DeleteHistoryInfo());
  while (
      (node = delete_info_.root->Find(delete_info_.name, delete_info_.type))) {
    // if (((Title*)node)->get_parent() == nullptr)
    //   std::cout << "12312" << std::endl;
    history_.back().titles.emplace_back((Title*)node->get_parent());
    if (delete_info_.type == kTitle)
      history_.back().nodes.emplace_back(
          std::make_unique<Title>(*(Title*)node));
    else {
      history_.back().nodes.emplace_back(
          std::make_unique<Bookmark>(*(Bookmark*)node));
    }
    delete_info_.root->DeepRemove(delete_info_.name, delete_info_.type);
  }
}

auto DeleteCmd::undo() -> void {
  auto& buff = history_.back();
  while (buff.titles.size() > 0) {
    // if (buff.titles.back() == nullptr) std::cout << "111" << std::endl;
    // if (buff.nodes.back() == nullptr) std::cout << "222" << std::endl;
    buff.titles.back()->Add(buff.nodes.back().get());
    buff.titles.pop_back();
    buff.nodes.pop_back();
  }
}

auto DeleteCmd::redo() -> void {}
