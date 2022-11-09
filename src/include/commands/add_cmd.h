#ifndef ADD_CMD_H_
#define ADD_CMD_H_

#include "bmk_sys/bmk_elements.h"
#include "command.h"

class AddCmd {
 private:
  static deque<int> history;
  static const string ctype;

 public:
  AddCmd();
  virtual void excute() = 0;
  virtual void undo() = 0;
  virtual void redo() = 0;
};

#endif