#ifndef DELETE_CMD_H_
#define DELETE_CMD_H_

#include "command.h"

class DeleteCmd {
 protected:
  BmkElements* bmk_elements_;

 public:
  virtual void excute() = 0;
  virtual void undo() = 0;
  virtual void redo() = 0;
};

#endif