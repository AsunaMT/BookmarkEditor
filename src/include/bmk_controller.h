#ifndef BMK_CONTROLLER_H_
#define BMK_CONTROLLER_H_

#include <map>
#include <memory>
#include <vector>

#include "bmk_sys/bmk_elements.h"
#include "commands/command.h"

class BmkController {
 private:
  std::string workspace_url_;
  std::map<CmdKey, std::unique_ptr<Command>> commands_;
  std::vector<std::unique_ptr<BmkElements>> roots_;
  auto AddBookmark() -> void;
  auto AddTitle() -> void;
  auto DeleteBookmark() -> void;
  auto DeleteTitle() -> void;
  auto Save() -> void;
  auto Undo() -> void;
  auto Redo() -> void;
  auto ShowTree() -> void;
  auto LsTree() -> void;
  auto Read(std::string name) -> void;

 public:
  BmkController();
  ~BmkController();
  auto Launch() -> void;
};

#endif