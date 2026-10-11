#include "manager.h"

//构造函数
Manager::Manager(int id, string name, int dId) {
	this->mId = id;
	this->mName = name;
	this->mDeptId = dId;
}

//显示员工信息
void Manager::showInfo() {
	cout << "职工编号：" << this->mDeptId << endl;
	cout << "职工姓名：" << this->mName << endl;
	cout << "职工部门：" << this->getDeptName() << endl;
	cout << "岗位职责：老板交给的任务。" << endl;
}

//获取员工岗位
string Manager::getDeptName() {
	return string("经理");
}