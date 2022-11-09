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

 public:
  BmkController();
  ~BmkController();
  void AddBookmark();
  void AddTitle();
  void DeleteBookmark();
  void DeleteTitle();
  void Save();
  void Undo();
  void Redo();
  void ShowTree();
  void LsTree();
  void Read(std::string name);
};

#endif