#include "bmk_controller.h"

#include <stdlib.h>

#include <algorithm>
#include <cstdio>
#include <deque>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "bmk_sys/bmk_element.h"
#include "bmk_sys/bookmark.h"
#include "bmk_sys/title.h"
#include "commands/add_cmd.h"
#include "commands/command.h"
#include "commands/delete_cmd.h"
#include "ui_sys/show_tree.h"

const std::unordered_map<std::string, OrderType> BmkController::orders_{
    {"add-title", kAddTitle},
    {"add-bookmark", kAddBookmark},
    {"delete-title", kDeleteTitle},
    {"delete-bookmark", kDeleteBookmark},
    {"open", kOpen},
    {"bookmark", kOpen},
    {"save", kSave},
    {"undo", kUndo},
    {"redo", kRedo},
    {"show-tree", kShowTree},
    {"ls-tree", kLsTree},
    {"read-bookmark", kReadBookmark}};

BmkController::BmkController() {
  root_ = std::make_unique<Title>("", 0);
  // orders_.insert({"add-title", kAddTitle});
  // orders_.insert({"add-bookmark", kAddBookmark});
  // orders_.insert({"delete-title", kDeleteTitle});
  // orders_.insert({"delete-bookmark", kDeleteBookmark});
  // orders_.insert({"open", kOpen});
  // orders_.insert({"bookmark", kOpen});
  // orders_.insert({"save", kSave});
  // orders_.insert({"undo", kUndo});
  // orders_.insert({"redo", kRedo});
  // orders_.insert({"show-tree", kShowTree});
  // orders_.insert({"ls-tree", kLsTree});
  // orders_.insert({"read-bookmark", kReadBookmark});
}

// BmkController::~BmkController() {}
auto RemoveQuote(std::string& str) {
  str.erase(str.begin());
  str.pop_back();
}

auto stringSplit(const std::string& str, char delim)
    -> std::vector<std::string> {
  std::vector<std::string> elems;
  auto lastPos = str.find_first_not_of(delim, 0);
  auto pos = str.find_first_of(delim, lastPos);
  while (pos != std::string::npos || lastPos != std::string::npos) {
    elems.push_back(str.substr(lastPos, pos - lastPos));
    lastPos = str.find_first_not_of(delim, pos);
    pos = str.find_first_of(delim, lastPos);
  }
  return elems;
}

auto BmkController::LoadInBmk(std::fstream& file) -> void {
  std::string line;
  std::deque<Title*> titlePath = {root_.get()};
  std::vector<std::string> items;
  while (std::getline(file, line)) {
    // std::cout << line << "\n";
    if (line.front() == '#') {
      items = stringSplit(line, ' ');
      // items.front().pop_back();
      unsigned level = items.front().size();
      unsigned deepth = titlePath.back()->get_level();
      if (level == deepth) {
        Title title(items.back());
        titlePath.pop_back();
        auto buff = titlePath.back()->Add(&title);
        titlePath.push_back((Title*)buff);
      } else {
        if (level < deepth) {
          for (int i = 0; i < deepth - level + 1; i++) titlePath.pop_back();
          Title t(items.back());
          titlePath.push_back((Title*)titlePath.back()->Add(&t));
        } else {
          Title t(items.back());
          titlePath.push_back((Title*)titlePath.back()->Add(&t));
        }
      }
    } else {
      items = stringSplit(line, ']');
      items.front().erase(items.front().begin());
      items.back().erase(items.back().begin());
      items.back().pop_back();
      Bookmark bookmark(items.front(), items.back());
      titlePath.back()->Add(&bookmark);
    }
    // std::cout << ShowTree(root_.get()).getTreeStr();
  }
}

auto BmkController::OpenBmk(std::string url) -> void {
  std::fstream inFile;
  inFile.open(url, std::ios::in);
  if (!inFile) {
    inFile.open(url, std::ios::out);
    inFile.close();
    inFile.open(url, std::ios::in);
  };
  workspace_url_ = url;
  // std::cout << workspace_url_ << std::endl;
  root_ = nullptr;
  root_ = std::make_unique<Title>("", 0);
  commands_.clear();
  LoadInBmk(inFile);
  inFile.close();
}

auto BmkController::Launch() -> void {
  std::string order;
  std::vector<std::string> para;
  // while (std::getline(std::cin, order)) {
  //   para = stringSplit(order, ' ');
  //   if (para.front() == "bookmark" || para.front() == "open") break;
  // }
  // workspace_url_ = para.back();
  // workspace_url_.erase(workspace_url_.begin());
  // workspace_url_.pop_back();
  // OpenBmk(workspace_url_);
  // std::cout << ShowTree(root_.get()).getTreeStr();
  while (std::getline(std::cin, order)) {
    para = stringSplit(order, ' ');
    const OrderType type = orders_.find(para.front())->second;
    // std::cout << type << std::endl;
    switch (type) {
      case kAddTitle: {
        std::string name = para[1];
        std::string where;
        if (para.size() == 4) {
          where = para.back();
          RemoveQuote(where);
        } else {
          where = "";
        }
        RemoveQuote(name);

        // std::cout << name << " " << where << std::endl;
        AddTitle(name, where);
        break;
      }
      case kAddBookmark: {
        auto sstr = stringSplit(para[1], '@');
        auto name = sstr.front();
        auto url = sstr.back();
        std::string where;
        if (para.size() == 4) {
          where = para.back();
          RemoveQuote(where);
        } else {
          where = "";
        }
        RemoveQuote(name);
        RemoveQuote(url);
        // std::cout << name << " " << where << std::endl;
        AddBookmark(name, url, where);
        break;
      }
      case kDeleteTitle: {
        auto name = para.back();
        RemoveQuote(name);
        DeleteTitle(name);
        break;
      }
      case kDeleteBookmark: {
        auto name = para.back();
        RemoveQuote(name);
        DeleteBookmark(name);
        break;
      }
      case kOpen: {
        auto url = para.back();
        RemoveQuote(url);
        OpenBmk(url);
        break;
      }
      case kSave:
        Save();
        break;
      case kUndo:
        Undo();
        break;
      case kRedo:
        Redo();
        break;
      case kShowTree:
        ShowBmkTree();
        break;
      case kLsTree:
        LsFileTree();
        break;
      case kReadBookmark: {
        auto name = para.back();
        RemoveQuote(name);
        ReadBookmark(name);
        break;
      }
      default:
        break;
    }
  }
}

auto BmkController::AddBookmark(const std::string& name, const std::string& url,
                                const std::string& titleName) -> void {
  Bookmark bookmark(name, url);
  // AddCmd a(AddInfo{titleName, root_.get(), &bookmark});
  commands_.emplace_back(std::make_unique<AddCmd>(
      AddCmd(AddInfo{titleName, root_.get(), &bookmark})));
  commands_.back()->excute();
}

auto BmkController::AddTitle(const std::string& name,
                             const std::string& titleName) -> void {
  Title title(name);
  // AddCmd a(AddInfo{titleName, root_.get(), &title});
  commands_.emplace_back(std::make_unique<AddCmd>(
      AddCmd(AddInfo{titleName, root_.get(), &title})));
  commands_.back()->excute();
}

auto BmkController::DeleteBookmark(const std::string& name) -> void {
  // DeleteCmd d(DeleteInfo{root_.get(), name, kBookmark});
  commands_.emplace_back(std::make_unique<DeleteCmd>(
      DeleteCmd(DeleteInfo{root_.get(), name, kBookmark})));
  commands_.back()->excute();
}

auto BmkController::DeleteTitle(const std::string& name) -> void {
  // DeleteCmd d(DeleteInfo{root_.get(), name, kTitle});
  commands_.emplace_back(std::make_unique<DeleteCmd>(
      DeleteCmd(DeleteInfo{root_.get(), name, kTitle})));
  commands_.back()->excute();
}

auto BmkController::Save() -> void {
  std::ofstream out;
  out.open(workspace_url_, std::ios::out);
  root_->GenerateBmk(out);
  out.close();
}

auto BmkController::Undo() -> void {
  if (commands_.size()) {
    commands_.back()->undo();
    auto undoCmd = commands_.back().release();
    commands_.pop_back();
    if (undo_cache_.size() > DEFAULT_CACHE_MAX) undo_cache_.pop_back();
    undo_cache_.emplace_back(undoCmd);
  }
}

auto BmkController::Redo() -> void {
  if (undo_cache_.size()) {
    undo_cache_.back()->redo();
    undo_cache_.pop_back();
  }
}

auto BmkController::ShowBmkTree() -> void {
  std::cout << ShowTree(root_.get()).getTreeStr();
}

auto BmkController::LsFileTree() -> void {
  std::string path = workspace_url_;
  while ((!path.empty()) && path.back() != '/') {
    path.pop_back();
  }
  if (!path.empty()) path.pop_back();
  if (path == "." || path == "") {
    path = "./";
  }
  FileNode ls(path);
  ls.MakeFiletree();
  std::cout << ShowTree(&ls).getTreeStr();
}

auto BmkController::ReadBookmark(std::string name) -> void {
  root_->Find(name, kBookmark)->Read();
}