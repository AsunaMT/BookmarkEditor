#ifndef BMK_CONTROLLER_H_
#define BMK_CONTROLLER_H_

#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "bmk_sys/bmk_element.h"
#include "bmk_sys/title.h"
#include "commands/command.h"

enum OrderType {
  kAddTitle,
  kAddBookmark,
  kDeleteTitle,
  kDeleteBookmark,
  kOpen,
  kSave,
  kUndo,
  kRedo,
  kShowTree,
  kLsTree,
  kReadBookmark
};

class BmkController {
 private:
  std::string workspace_url_;
  std::deque<std::unique_ptr<Command>> commands_;
  std::deque<Command*> undo_cache_;

  // std::deque<Command*> commands_;
  // std::deque<Command*> undo_cache_;
  std::unique_ptr<Title> root_;
  static const std::unordered_map<std::string, OrderType> orders_;
  auto OpenBmk(std::string url) -> void;
  auto LoadInBmk(std::fstream& file) -> void;
  auto AddBookmark(const std::string& name, const std::string& url,
                   const std::string& titleName) -> void;
  auto AddTitle(const std::string& name, const std::string& titleName) -> void;
  auto DeleteBookmark(const std::string& name) -> void;
  auto DeleteTitle(const std::string& name) -> void;
  auto Save() -> void;
  auto Undo() -> void;
  auto Redo() -> void;
  auto ShowBmkTree() -> void;
  auto LsFileTree() -> void;
  auto ReadBookmark(std::string name) -> void;

 public:
  BmkController();
  //~BmkController();
  auto Launch() -> void;
};

auto stringSplit(const std::string& str, char delim)
    -> std::vector<std::string>;
#endif