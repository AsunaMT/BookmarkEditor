#ifndef DELETE_CMD_H_
#define DELETE_CMD_H_

#include "command.h"

class DeleteCmd {
 protected:
  BmkElement* bmk_element_;

 public:
  auto excute() -> void;
  auto undo() -> void;
  auto redo() -> void;
};

#endif