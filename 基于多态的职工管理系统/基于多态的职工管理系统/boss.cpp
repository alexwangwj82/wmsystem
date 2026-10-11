#include "boss.h"

//构造函数
Boss::Boss(int id, string name, int dId) {
	this->mId = id;
	this->mName = name;
	this->mDeptId = dId;
}

//显示员工信息
void Boss::showInfo() {
	cout << "职工编号：" << this->mDeptId << endl;
	cout << "职工姓名：" << this->mName << endl;
	cout << "职工部门：" << this->getDeptName() << endl;
	cout << "岗位职责：领导公司发展。" << endl;
}

//获取员工岗位
string Boss::getDeptName() {
	return string("老板");
}