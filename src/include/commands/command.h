#ifndef COMMAND_H_
#define COMMAND_H_

#include <bmk_sys/bmk_elements.h>

enum CmdKey { kAdd, kDelete };

class Command {
 protected:
  BmkElements* bmk_elements_;

 public:
  Command(BmkElements* bmk_elements);
  virtual auto excute() -> void = 0;
  virtual auto undo() -> void = 0;
  virtual auto redo() -> void = 0;
};

#endif