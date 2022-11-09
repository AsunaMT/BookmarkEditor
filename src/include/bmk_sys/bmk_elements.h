#ifndef BMK_ELEMENTS_H_
#define BMK_ELEMENTS_H_

#include <deque>
#include <iostream>
#include <memory>
#include <string>

#include "ui_sys/label_provider.h"
#include "ui_sys/show_tree.h"

using std::deque;
using std::string;

class BmkElements : TreeNode {
 private:
  string name_;

 public:
  string getName() const;
  void setName(string name);
  virtual void add(BmkElements* node) = 0;
  virtual void rename(string newname) = 0;
  virtual void remove(BmkElements* node) = 0;
  virtual BmkElements* enter() = 0;
  virtual BmkElements* GetNode(int index);
  void showName();
};

class Title : public BmkElements {
 private:
  class TitleLableProvider : public LabelProvider<Title> {
   public:
    virtual auto LableOf(const Title& title) -> std::string {
      return title.getName();
    }
  };
  static const TitleLableProvider label_provider_;
  deque<std::unique_ptr<BmkElements>> elements_;

 public:
  Title(std::string name);
  void add(BmkElements* node);
  void remove(BmkElements* node);
  void rename(string newName);
  BmkElements* enter();
  BmkElements* GetNode(int index);
};

class Bookmark : public BmkElements {
 private:
  string url_;
  bool dirty_;

 public:
  string getUrl();
  void setUrl(string name);
  Bookmark(string name);
  void add(BmkElements* node);
  void remove(BmkElements* node);
  void rename(string newName);
  BmkElements* enter();
};

#endif