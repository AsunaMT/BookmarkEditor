#ifndef DELETE_CMD_H_
#define DELETE_CMD_H_

#include "command.h"

class DeleteCmd {
 protected:
  BmkElements* bmk_elements_;

 public:
  auto excute() -> void;
  auto undo() -> void;
  auto redo() -> void;
};

#endif