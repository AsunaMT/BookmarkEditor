#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;
// int main(int argc, char **argv) {
//     int val1 = 10;
//     int val2 = 20;
//     cout << "before swap: val1=" << val1 << ", val2=" << val2 << endl;
//     swap(val1, val2);
//     cout << "after swap: val1=" << val1 << ", val2=" << val2 << endl;
//     return 0;
// }

class fileSystem {
 public:
  string name;
  virtual void add(fileSystem* node) = 0;
  virtual void rename(string newname) = 0;
  virtual void remove(fileSystem* node) = 0;
  virtual fileSystem* enter() = 0;
  virtual fileSystem* GetNode(int index) { return nullptr; }
  void showName() { cout << "文件名字:" << name << endl; }
};

class dir : public fileSystem {
 private:
  vector<fileSystem*> file;

 public:
  dir(string name) { this->name = name; }
  void add(fileSystem* node) { file.push_back(node); }
  void remove(fileSystem* node) {
    for (auto it = file.begin(); it != file.end(); it++) {
      if (*it == node) file.erase(it);
    }
  }
  void rename(string newName) { name = newName; }
  fileSystem* enter() {  //目录点击去就是显示里面有什么
    cout << "打开名叫" << name << "的目录" << endl;
    for (auto it = file.begin(); it != file.end(); it++) {
      cout << (*it)->name << endl;
    }
    return this;
  }
  fileSystem* GetNode(
      int index) {  //电脑会进行按键扫描返回是第几个文件也就是index
    return file[index];
  }
};

class cppfile : public fileSystem {
 public:
  cppfile(string name) { this->name = name; }
  void add(fileSystem* node) { cout << "不支持这个操作" << endl; }
  void remove(fileSystem* node) { cout << "不支持这个操作" << endl; }
  void rename(string newName) { name = newName; }
  fileSystem* enter() {  //文件就是打开
    cout << "打开名叫" << name << "的文件" << endl;
    return this;
  }
};

class txtfile : public fileSystem {
 public:
  txtfile(string name) { this->name = name; }
  void add(fileSystem* node) { cout << "不支持这个操作" << endl; }
  void remove(fileSystem* node) { cout << "不支持这个操作" << endl; }
  void rename(string newName) { name = newName; }
  fileSystem* enter() {  //文件就是打开
    cout << "打开名叫" << name << "的文件" << endl;
    return this;
  }
};

int main() {
  std::string path;
  cin >> path;
  for (const auto& entry : fs::directory_iterator(path)) {
    std::cout << entry.path().filename().string() << std::endl;
    if (fs::is_directory(entry.path())) {
      for (const auto& i : fs::directory_iterator(path))
        std::cout << "  " + i.path().filename().string() << std::endl;
    }
  }
  fileSystem* d = new dir("1dir");  //创建根目录1dir
  d->showName();
  d->add(new txtfile("2txt"));  //创建三个类型文件
  d->add(new cppfile("3cpp"));
  d->add(new dir("4dir"));
  d = d->enter();  //进入1dir目录，展示下面有哪些文件
  d = d->GetNode(2);  //按键扫描，表示接下来操作的是哪个位置上的文件
  d = d->enter();  //进入4dir目录，展示下面有哪些文件
  d->showName();
  d->add(new cppfile("5cpp"));  //创建5cpp
  d = d->GetNode(0);  //按键扫描，表示接下来操作的是哪个位置上的文件
  d = d->enter();
  d->showName();
  int a;
  cout << a;
  return 0;
}