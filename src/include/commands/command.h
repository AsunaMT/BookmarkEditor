#ifndef COMMAND_H_
#define COMMAND_H_

#include "bmk_sys/bmk_elements.h"

enum CmdKey { kAdd, kDelete };

class Command {
 protected:
  BmkElements* bmk_elements_;

 public:
  Command(BmkElements* bmk_elements);
  virtual void excute() = 0;
  virtual void undo() = 0;
  virtual void redo() = 0;
};

#endif