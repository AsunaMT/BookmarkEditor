#ifndef BMK_SYS_TITLE_H_
#define BMK_SYS_TITLE_H_

#include <fstream>

#include "bmk_element.h"
#include "bmk_sys/bookmark.h"

const bool DEFAULT_TITLE_START_INDEX = 0;
const unsigned DEFAULT_TITLE_LEVEL = 1;

class Title : public BmkElement {
 private:
  unsigned level_;
  std::deque<std::unique_ptr<BmkElement>> elements_;
  unsigned title_start_index_;
  std::string name_;
  BmkElement* parent_;
  class TitleLableProvider : public LabelProvider<Title> {
   public:
    auto LabelOf(const Title& title) const -> std::string;
  };
  constexpr static const TitleLableProvider title_label_provider_ =
      TitleLableProvider();

  auto set_level(const unsigned& level) -> void;

 protected:
 public:
  Title(const std::string& name, const unsigned& level = DEFAULT_TITLE_LEVEL);
  Title(const BmkElement& title);
  Title(const Title& title);
  auto get_name() const -> std::string;
  auto set_name(const std::string& name) -> void;
  auto get_parent() const -> BmkElement*;
  auto set_parent(BmkElement* bmk) -> void;
  auto GetType() const -> BmkElementType;
  auto Add(BmkElement* node) -> BmkElement*;
  auto Remove(const std::string& name, const BmkElementType& type) -> void;
  auto GetLabel() const -> std::string;
  auto GetList() const -> std::deque<const TreeNode*>;
  auto HasChild() const -> bool;
  auto ShowStr() const -> std::string;
  auto GetInnerBmk(const std::string& name) const -> BmkElement*;
  auto Read() -> void;
  auto Find(const std::string& name, const BmkElementType& type) const
      -> BmkElement*;
  auto ExactRemove(BmkElement* bmk) -> void;
  auto DeepRemove(const std::string& name, const BmkElementType& type) -> bool;
  auto get_level() const -> unsigned;
  auto ShowMdFormat() const -> std::string;
  auto GenerateBmk(std::ofstream& out) const -> void;
};

#endif