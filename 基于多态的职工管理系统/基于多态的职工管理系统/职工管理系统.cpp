#include <iostream>
using namespace std;
#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main() {

	WorkerManager wm;
	int userMenuChoice = 0;
	while (true) {
		wm.showMenu();
		cout << "请输入您的选择：" << endl;
		cin >> userMenuChoice;
		switch (userMenuChoice) {
		case 0: //退出管理程序
			wm.exitSystem();
			break;
		case 1: //增加职工信息
			wm.addEmployee();
			break;
		case 2: //显示职工信息
			wm.showEmp();
			break;
		case 3: //删除离职职工
			wm.delEmp();
			break;
		case 4: //修改职工信息
			wm.modifyEmp();
			break;
		case 5: //查找职工信息
			wm.findEmp();
			break;
		case 6: //按照编号排序
			break;
		case 7: //清空所有文档
			break;
		default:
			cout << "输入的选项不合理，请输入0-7之间的数字。" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}