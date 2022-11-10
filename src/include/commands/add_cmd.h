#ifndef ADD_CMD_H_
#define ADD_CMD_H_

#include "bmk_sys/bmk_elements.h"
#include "command.h"

class AddCmd {
 private:
  static std::deque<int> history;
  static const std::string ctype;

 public:
  AddCmd();
  virtual void excute();
  virtual void undo();
  virtual void redo();
};

#endif