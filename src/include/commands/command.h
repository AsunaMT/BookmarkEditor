#ifndef COMMAND_H_
#define COMMAND_H_

#include <bmk_sys/bmk_element.h>

enum CmdKey { kAdd, kDelete };

class Command {
 protected:
 public:
  // Command(BmkElement* bmk_element);
  virtual auto excute() -> void = 0;
  virtual auto undo() -> void = 0;
  virtual auto redo() -> void = 0;
};

#endif