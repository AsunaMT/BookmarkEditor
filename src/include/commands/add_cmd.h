#ifndef ADD_CMD_H_
#define ADD_CMD_H_

#include "command.h"

class AddCmd {
 private:
  static std::deque<int> history;
  static const std::string ctype;

 public:
  AddCmd();
  auto excute() -> void {}
  auto undo() -> void;
  auto redo() -> void;
};

#endif