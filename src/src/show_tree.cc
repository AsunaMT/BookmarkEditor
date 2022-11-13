#include <ui_sys/show_tree.h>

ShowTree::ShowTree(TreeNode* root) : root_(root) {
  target = "";
  pathDeep = 0;
}

auto ShowTree::getTreeStr() -> std::string {
  getTreeStr(*root_);
  auto res = target;
  target.clear();
  return res;
}
auto ShowTree::getTreeStr(const TreeNode& node) -> void {
  auto obj_arr = node.GetList();
  pathDeep++;
  // ����ÿ��ʱ������ֳ������֣����׺�File���֡�
  // ����File����Ҫ���ж���Ŀ¼�����ļ������ж��Ƿ��ǵ�ǰĿ¼����һ��File����Filenameǰ��ӡ����Ӧ�ķ���

  for (int i = 0; i < obj_arr.size(); i++) {
    // �������
    for (int j = 0; j < pathDeep - 1; j++) {
      // std::cout << target.append(str_list_[j]);
      target.append(str_list_[j]);
    }

    //�жϵ�ǰ�ļ��Ƿ���·��
    if (obj_arr[i]->HasChild()) {
      //�ж��ǲ������һ��Ŀ¼
      if (i == obj_arr.size() - 1) {
        //�����һ��Ŀ¼ʱ
        // std::cout << target.append("����");
        target.append("����");
        str_list_.emplace(str_list_.begin() + pathDeep - 1,
                          "  ");  // add(pathDeep - 1, "  ");
      } else {
        //�����һ��Ŀ¼ʱ
        str_list_.emplace(str_list_.begin() + pathDeep - 1,
                          "�� ");  // add(pathDeep - 1, "�� ");
        // std::cout << target.append("����");
        target.append("����");
      }
      //�����ʱĿ¼������
      // std::cout << target.append(obj_arr[i]->ShowStr() + "\n");
      target.append(obj_arr[i]->ShowStr() + "\n");
      //�ݹ����
      getTreeStr(*obj_arr[i]);

      //�������Ŀ¼�����ļ�
    } else {
      //���жϵ�ǰ�ļ��ǲ������һ���ļ�
      if (i == obj_arr.size() - 1) {
        // std::cout << target.append("����");
        target.append("����");
      } else {
        // std::cout << target.append("����");
        target.append("����");
      }
      // std::cout << target.append(obj_arr[i]->ShowStr() + "\n");
      target.append(obj_arr[i]->ShowStr() + "\n");
    }
  }
  pathDeep--;
}