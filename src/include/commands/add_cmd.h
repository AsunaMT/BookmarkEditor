#ifndef ADD_CMD_H_
#define ADD_CMD_H_

#include <memory>
#include <type_traits>

#include "bmk_sys/bmk_element.h"
#include "bmk_sys/bookmark.h"
#include "bmk_sys/title.h"
#include "command.h"

constexpr static const unsigned DEFAULT_ADD_HISTORY_MAX = 10;
constexpr static const unsigned DEFAULT_CACHE_MAX = 1;
struct AddInfo {
  std::string name;
  Title* root;
  BmkElement* node;
};

struct AddHistoryInfo {
  Title* title;
  BmkElement* node;
};

struct AddCacheInfo {
  Title* title;
  std::unique_ptr<BmkElement> node;
};

class AddCmd : public Command {
 private:
  AddInfo add_info_;
  static std::deque<AddHistoryInfo> history_;
  static std::deque<AddCacheInfo> cache_;
  static unsigned history_max_;
  constexpr static const CmdKey ctype_ = kAdd;

 public:
  AddCmd(const AddCmd& addCmd);
  AddCmd(AddInfo&& add_info);
  auto excute() -> void;
  auto undo() -> void;
  auto redo() -> void;
};

#endif