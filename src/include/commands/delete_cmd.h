#ifndef DELETE_CMD_H_
#define DELETE_CMD_H_

#include <vector>

#include "bmk_sys/bmk_element.h"
#include "bmk_sys/title.h"
#include "command.h"

constexpr static const unsigned DEFAULT_DELETE_HISTORY_MAX = 10;
struct DeleteInfo {
  Title* root;
  std::string name;
  BmkElementType type;
};

struct DeleteHistoryInfo {
  std::vector<Title*> titles;
  std::vector<std::unique_ptr<BmkElement>> nodes;
};

struct DeleteCacheInfo {
  Title* title;
  std::string name;
  BmkElementType type;
};

class DeleteCmd : public Command {
 private:
  DeleteInfo delete_info_;
  static std::deque<DeleteHistoryInfo> history_;
  static DeleteCacheInfo cache_;
  static unsigned history_max_;
  constexpr static const CmdKey ctype_ = kAdd;

 public:
  DeleteCmd(const DeleteCmd& deleteCmd);
  DeleteCmd(DeleteInfo&& delete_info);
  auto excute() -> void;
  auto undo() -> void;
  auto redo() -> void;
};

#endif