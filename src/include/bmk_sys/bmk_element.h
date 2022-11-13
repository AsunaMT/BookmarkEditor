#ifndef BMK_SYS_bmk_element_H_
#define BMK_SYS_bmk_element_H_

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <ui>

enum BmkElementType { kTitle, kBookmark, kRoot };

class BmkElement : public TreeNode {
 private:
  std::string name_;
  BmkElement* parent_;

  virtual auto set_level(const unsigned& level) -> void = 0;

 protected:
 public:
  virtual auto get_name() const -> std::string = 0;
  virtual auto set_name(const std::string& name) -> void = 0;
  virtual auto get_parent() const -> BmkElement* = 0;
  virtual auto set_parent(BmkElement* bmk) -> void = 0;
  virtual auto GetType() const -> BmkElementType = 0;
  virtual auto Add(BmkElement* node) -> BmkElement* = 0;
  virtual auto Remove(const std::string& name, const BmkElementType& type)
      -> void = 0;
  virtual auto GetLabel() const -> std::string = 0;
  virtual auto GetInnerBmk(const std::string& name) const -> BmkElement* = 0;
  virtual auto Read() -> void = 0;
  virtual auto Find(const std::string& name, const BmkElementType& type) const
      -> BmkElement* = 0;
  virtual auto get_level() const -> unsigned = 0;
  virtual auto ShowMdFormat() const -> std::string = 0;
  // virtual BmkElement* Enter() = 0;
  // virtual BmkElement* GetNode(int index);
};

#endif