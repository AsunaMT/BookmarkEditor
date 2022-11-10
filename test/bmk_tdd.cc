#include <limits.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <ui>

#include "bmk_sys/bmk_elements.h"
#include "command"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "ui_sys/show_tree.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Return;
using namespace testing;
using namespace std;

TEST(LABEL_TEST, SHOW_BMK_LABEL) {
  Title t("title2");
  Bookmark b("aa");
  string val1 = t.GetLabel(), val2 = b.GetLabel();
  // cout << val1 << endl;
  // cout << val2 << endl;
  EXPECT_EQ(val1, "title2");
  EXPECT_EQ(val2, "\"aa\"");
}

TEST(DIRTY_LABEL_TEST, SHOW_DIRTY_LABE) {
  Bookmark b("bookmark");
  b.Read();
  string val1 = b.GetLabel();
  // cout << val1 << endl;
  EXPECT_EQ(val1, "\"*bookmark\"");
}

TEST(SHOW_TREE_TEST1, SHOW_FILE_TREE) {
  FileNode fileNode(".\\src");
  fileNode.MakeFiletree();
  ShowTree tree(&fileNode);
  string val1 = tree.getTreeStr();
  // cout << val1 << endl;
  string val2 =
      "├─include\n"
      "│ ├─\"bmk_controller.h\"\n"
      "│ ├─bmk_sys\n"
      "│ │ └─\"bmk_elements.h\"\n"
      "│ ├─\"command\"\n"
      "│ ├─commands\n"
      "│ │ ├─\"add_cmd.h\"\n"
      "│ │ ├─\"command.h\"\n"
      "│ │ └─\"delete_cmd.h\"\n"
      "│ ├─\"ui\"\n"
      "│ └─ui_sys\n"
      "│   ├─\"file_node.h\"\n"
      "│   ├─\"label_decorator.h\"\n"
      "│   ├─\"label_provider.h\"\n"
      "│   └─\"show_tree.h\"\n"
      "├─\"main.cc\"\n"
      "└─src\n"
      "  ├─\"bmk_controller.cc\"\n"
      "  ├─\"bmk_elements.cc\"\n"
      "  └─\"label_decorator.cc\"\n";
  EXPECT_EQ(val1, val2);
}

TEST(SHOW_TREE_TEST2, SHOW_BMK_TREE) {
  Title root("workspace");
  Title t1("title1");
  Title t2("title2");
  Title t3("title3");
  Bookmark b1("aa"), b2("bb"), b3("cc"), b4("dd"), b5("ff");
  t2.Add(&b1);

  root.Add(&t1);
  auto tt1 = root.GetInnerBmk("title1");
  tt1->Add(&t2);
  // tt1->GetInnerBmk("title2")->Add(&b1);
  tt1->Add(&b2);
  tt1->Add(&t3);
  tt1->Add(&b3);
  tt1->GetInnerBmk("cc")->Read();
  tt1->Add(&b4);
  root.Add(&b5);
  ShowTree tree(&root);
  string val1 = tree.getTreeStr();
  // cout << val1;
  string val2 =
      "├─\"ff\"\n"
      "└─title1\n"
      "  ├─\"bb\"\n"
      "  ├─\"*cc\"\n"
      "  ├─\"dd\"\n"
      "  ├─title2\n"
      "  │ └─\"aa\"\n"
      "  └─title3\n";
  EXPECT_EQ(val1, val2);
}

TEST(ADD_TEST, ADD_BMK_TO_TITLE) {
  Title root("workspace");
  Title t1("title1");
  Bookmark b1("bmk1");
  root.Add(&t1);
  root.Add(&b1);
  auto val1 = root.GetInnerBmk("title1");
  auto val2 = root.GetInnerBmk("bmk1");
  auto val3 = root.GetInnerBmk("bmk2");
  ASSERT_NE(val1, nullptr);
  ASSERT_NE(val1, nullptr);
  EXPECT_EQ(val3, nullptr);
  EXPECT_EQ(val1->get_name(), "title1");
  EXPECT_EQ(val2->get_name(), "bmk1");
}

TEST(REMOVE_TEST, REMOVE_BMK_IN_TITLE) {
  Title root("workspace");
  Title t1("title1");
  Bookmark b1("bmk1");
  root.Add(&t1);
  root.Add(&b1);
  auto val1 = root.GetInnerBmk("title1");
  auto val2 = root.GetInnerBmk("bmk1");
  EXPECT_NE(val1, nullptr);
  EXPECT_NE(val2, nullptr);
  root.Remove("title1", kTitle);
  root.Remove("bmk1", kBookmark);
  val1 = root.GetInnerBmk("title1");
  val2 = root.GetInnerBmk("bmk1");
  EXPECT_EQ(val1, nullptr);
  EXPECT_EQ(val2, nullptr);
}

TEST(DEEPREMOVE_TEST, DEEPREMOVE_BMK_IN_TITLE) {
  Title root("workspace");
  Title t1("title1");
  Bookmark b1("bmk1");
  t1.Add(&b1);
  root.Add(&t1);
  root.Add(&b1);
  auto val1 = root.GetInnerBmk("title1")->GetInnerBmk("bmk1");
  auto val2 = root.GetInnerBmk("bmk1");
  EXPECT_NE(val1, nullptr);
  EXPECT_NE(val2, nullptr);
  root.DeepRemove("bmk1", kBookmark);
  val1 = root.GetInnerBmk("title1")->GetInnerBmk("bmk1");
  val2 = root.GetInnerBmk("bmk1");
  EXPECT_EQ(val1, nullptr);
  EXPECT_EQ(val2, nullptr);
}