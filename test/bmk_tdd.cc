#include <limits.h>

#include <bmk>
#include <command>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ui>

#include "bmk_controller.h"
#include "bmk_sys/bmk_element.h"
#include "commands/add_cmd.h"
#include "commands/delete_cmd.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

// using ::testing::_;
// using ::testing::AtLeast;
// using ::testing::Exactly;
// using ::testing::Return;
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
  FileNode fileNode("src");
  fileNode.MakeFiletree();
  ShowTree tree(&fileNode);
  string val1 = tree.getTreeStr();
  // cout << val1 << endl;
  string val2 =
      "©À©¤include\n"
      "©¦ ©À©¤\"bmk\"\n"
      "©¦ ©À©¤\"bmk_controller.h\"\n"
      "©¦ ©À©¤bmk_sys\n"
      "©¦ ©¦ ©À©¤\"bmk_element.h\"\n"
      "©¦ ©¦ ©À©¤\"bookmark.h\"\n"
      "©¦ ©¦ ©¸©¤\"title.h\"\n"
      "©¦ ©À©¤\"command\"\n"
      "©¦ ©À©¤commands\n"
      "©¦ ©¦ ©À©¤\"add_cmd.h\"\n"
      "©¦ ©¦ ©À©¤\"command.h\"\n"
      "©¦ ©¦ ©¸©¤\"delete_cmd.h\"\n"
      "©¦ ©À©¤\"ui\"\n"
      "©¦ ©¸©¤ui_sys\n"
      "©¦   ©À©¤\"file_node.h\"\n"
      "©¦   ©À©¤\"label_decorator.h\"\n"
      "©¦   ©À©¤\"label_provider.h\"\n"
      "©¦   ©¸©¤\"show_tree.h\"\n"
      "©À©¤\"main.cc\"\n"
      "©¸©¤src\n"
      "  ©À©¤\"add_cmd.cc\"\n"
      "  ©À©¤\"bmk_controller.cc\"\n"
      "  ©À©¤\"bookmark.cc\"\n"
      "  ©À©¤\"delete_cmd.cc\"\n"
      "  ©À©¤\"file_node.cc\"\n"
      "  ©À©¤\"label_decorator.cc\"\n"
      "  ©À©¤\"show_tree.cc\"\n"
      "  ©¸©¤\"title.cc\"\n";
  EXPECT_EQ(val1, val2);
}

TEST(SHOW_TREE_TEST2, SHOW_BMK_TREE) {
  Title root("workspace", 0);
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
      "©À©¤\"ff\"\n"
      "©¸©¤title1\n"
      "  ©À©¤\"bb\"\n"
      "  ©À©¤\"*cc\"\n"
      "  ©À©¤\"dd\"\n"
      "  ©À©¤title2\n"
      "  ©¦ ©¸©¤\"aa\"\n"
      "  ©¸©¤title3\n";
  EXPECT_EQ(val1, val2);
}

TEST(ADD_TEST, ADD_BMK_TO_TITLE) {
  Title root("workspace", 0);
  Title t1("title1");
  Title t2("title2");
  Title t3("title3");
  // t1.Add(&t2);
  Bookmark b1("bmk1");
  root.Add(&t1);
  root.Add(&b1);
  // cout << ShowTree(&root).getTreeStr();
  auto val1 = root.GetInnerBmk("title1");
  auto val2 = root.GetInnerBmk("bmk1");
  auto val3 = root.GetInnerBmk("bmk2");
  t2.Add(&t3);
  val1->Add(&t2);
  auto val4 = root.Find("title2", kTitle);
  auto val5 = root.Find("title3", kTitle);
  ASSERT_NE(val1, nullptr);
  ASSERT_NE(val1, nullptr);
  EXPECT_EQ(val3, nullptr);
  EXPECT_EQ(val1->get_name(), "title1");
  EXPECT_EQ(val2->get_name(), "bmk1");
  EXPECT_EQ(val4->get_name(), "title2");
  EXPECT_EQ(val5->get_name(), "title3");
}

TEST(ADD_COMMAND_TEST, ADD_BMK_TO_TITLE) {
  Title root("workspace", 0);
  Title t1("title1");
  Title t2("title2");
  Title t3("title3");
  Bookmark b1("bmk1"), b2("bmk2");
  root.Add(&b1);
  AddCmd add1(AddInfo{"", &root, &t1});
  add1.excute();
  auto val1 = root.GetInnerBmk("title1");
  ASSERT_NE(val1, nullptr);
  EXPECT_EQ(val1->get_name(), "title1");
  add1.undo();
  val1 = root.GetInnerBmk("title1");
  ASSERT_EQ(val1, nullptr);
  add1.redo();
  val1 = root.GetInnerBmk("title1");
  ASSERT_NE(val1, nullptr);
  EXPECT_EQ(val1->get_name(), "title1");
  t2.Add(&t3);
  AddCmd add2(AddInfo{"title1", &root, &t2});
  add2.excute();
  auto val2 = root.Find("title2", kTitle);
  ASSERT_NE(val2, nullptr);
  EXPECT_EQ(val2->get_name(), "title2");
  add2.undo();
  val2 = root.Find("title2", kTitle);
  ASSERT_EQ(val2, nullptr);
  add2.redo();
  val2 = root.Find("title2", kTitle);
  ASSERT_NE(val2, nullptr);
  EXPECT_EQ(val2->get_name(), "title2");
  AddCmd add3(AddInfo{"", &root, &b2});
  add3.excute();
  auto val3 = root.GetInnerBmk("bmk2");
  ASSERT_NE(val3, nullptr);
  EXPECT_EQ(val3->get_name(), "bmk2");
  add3.undo();
  val3 = root.GetInnerBmk("bmk2");
  ASSERT_EQ(val3, nullptr);
  add3.redo();
  val3 = root.GetInnerBmk("bmk2");
  ASSERT_NE(val3, nullptr);
  EXPECT_EQ(val3->get_name(), "bmk2");
}

TEST(REMOVE_TEST, REMOVE_BMK_IN_TITLE) {
  Title root("workspace", 0);
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
  Title root("workspace", 0);
  Title t1("title1");
  Bookmark b1("bmk1");
  ShowTree tree(&root);
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
  EXPECT_NE(val1, nullptr);
  EXPECT_EQ(val2, nullptr);
  root.DeepRemove("bmk1", kBookmark);
  val1 = root.GetInnerBmk("title1")->GetInnerBmk("bmk1");
  EXPECT_EQ(val1, nullptr);
}

TEST(DELETE_COMMAND_TEST, DELETE_BMK_IN_TITLE) {
  Title root("workspace", 0);
  Title t1("title1");
  Bookmark b1("bmk1");
  t1.Add(&b1);
  root.Add(&t1);
  root.Add(&b1);
  ShowTree tree(&root);
  auto val1 = root.GetInnerBmk("title1")->GetInnerBmk("bmk1");
  auto val2 = root.GetInnerBmk("bmk1");
  EXPECT_NE(val1, nullptr);
  EXPECT_NE(val2, nullptr);
  DeleteCmd de1(DeleteInfo{&root, "bmk1", kBookmark});
  // cout << tree.getTreeStr() << endl;
  de1.excute();
  // cout << tree.getTreeStr() << endl;
  val1 = root.GetInnerBmk("title1")->GetInnerBmk("bmk1");
  val2 = root.GetInnerBmk("bmk1");
  EXPECT_EQ(val1, nullptr);
  EXPECT_EQ(val2, nullptr);
  de1.undo();
  // cout << tree.getTreeStr() << endl;
  val1 = root.GetInnerBmk("title1")->GetInnerBmk("bmk1");
  val2 = root.GetInnerBmk("bmk1");
  EXPECT_NE(val1, nullptr);
  EXPECT_NE(val2, nullptr);
}

TEST(TITLE_LEVEL_TEST, SHOW_TITLE_LEVEL) {
  Title root("workspace");
  Title t1("title1"), t2("title2"), t3("title3");
  t1.Add(&t2);
  auto val1 = t1.GetInnerBmk("title2")->get_level();
  EXPECT_EQ(val1, 2);
  root.Add(&t1);
  auto val2 = root.Find("title2", kTitle)->get_level();
  // auto val2 = root.GetInnerBmk("title1")->GetInnerBmk("title2")->get_level();
  EXPECT_EQ(val2, 3);
}
//[elearning](https://elearning.fudan.edu.cn/courses)

TEST(MD_FORMAT_TEST, SHOW_MAD_FORMAT) {
  Title root("workspace", 0);
  Title t1("title1"), t2("title2");
  t1.Add(&t2);
  root.Add(&t1);
  Bookmark b1("elearning", "https://elearning.fudan.edu.cn/courses");
  // cout << b1.ShowMdFormat() << endl;
  root.Add(&b1);
  auto val1 = root.Find("title1", kTitle)->ShowMdFormat();
  auto val2 = root.Find("title2", kTitle)->ShowMdFormat();
  auto val3 = root.Find("elearning", kBookmark)->ShowMdFormat();
  EXPECT_EQ(val1, "# title1");
  EXPECT_EQ(val2, "## title2");
  EXPECT_EQ(val3, "[elearning](https://elearning.fudan.edu.cn/courses)");
}
