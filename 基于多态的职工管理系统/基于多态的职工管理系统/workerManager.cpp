#include "workerManager.h"
using namespace std;

WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //读文件

	//1、如果文件不存在
	if (!ifs.is_open())			
	{
		cout << "文件不存在" << endl;
		//初始化属性
		this->mEmpNum = 0;
		this->mEmpArray = NULL;
		this->mFileIsEmpty = true;

		ifs.close();
		return;
	}

	//2、如果文件存在
	char ch;
	ifs >> ch;

	//如果文件为空
	if (ifs.eof()) {
		cout << "文件为空，无员工数据" << endl;

		//初始化属性
		this->mEmpNum = 0;
		this->mEmpArray = NULL;
		this->mFileIsEmpty = true;

		ifs.close();
		return;
	}
}

WorkerManager::~WorkerManager() {
	if (this->mEmpArray != NULL) {
		delete[] this->mEmpArray;
		this->mEmpArray = NULL;
	}
}

void WorkerManager::showMenu() {
	cout << "*******************************************" << endl;
	cout << "********** 欢迎使用职工管理系统！**********" << endl;
	cout << "************* 0.退出管理程序 **************" << endl;
	cout << "************* 1.增加职工信息 **************" << endl;
	cout << "************* 2.显示职工信息 **************" << endl;
	cout << "************* 3.删除离职职工 **************" << endl;
	cout << "************* 4.修改职工信息 **************" << endl;
	cout << "************* 5.查找职工信息 **************" << endl;
	cout << "************* 6.按照编号排序 **************" << endl;
	cout << "************* 7.清空所有文档 **************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::exitSystem() {
	cout << endl;
	cout << "退出系统，欢迎下次使用。" << endl;
	system("pause");
	exit(0);
}

//添加员工
void WorkerManager::addEmployee() {
	cout << "请输入要添加员工的数量" << endl;
	int addNum = 0; //保存添加员工的数量

	cin >> addNum;
	if (addNum > 0) {
		int newSize = this->mEmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker* [newSize];
		for (int i = 0; i < newSize; ++i) {
			newSpace[i] = nullptr;
		}

		//将原来空间下数据，拷贝到新空间下
		if (this->mEmpArray != NULL) {
			for (int i = 0; i < this->mEmpNum; i++) {
				newSpace[i] = this->mEmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++) {
			int id; //职工编号
			string name; //职工姓名
			int deptId; //部门编号
			Worker* worker = NULL;

			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新员工的姓名：" << endl;
			cin >> name;

			while (true) {
				cout << "请输入部门编号，1. 员工 2. 经理 3. 老板" << endl;
				cin >> deptId;

				switch (deptId) {
				case 1:
					worker = new Employee(id, name, deptId);
					break;
				case 2:
					worker = new Manager(id, name, deptId);
					break;
				case 3:
					worker = new Boss(id, name, deptId);
					break;
				default:
					cout << "输入数据有误，请输入1/2/3之间的整数" << endl;
					continue;
				}
				break;
			}
			
			//将创建职工指针，保存到数组中
			newSpace[this->mEmpNum + i] = worker;
		}

		//在所有新数据填充完成后，再释放原有空间并替换指针
		if (this->mEmpArray != NULL) {
			delete[] this->mEmpArray;
			this->mEmpArray = nullptr;
		}

		//更改新空间的指向
		this->mEmpArray = newSpace;

		//更新新的职工人数
		this->mEmpNum = newSize;

		//提示添加成功
		cout << "成功添加了" << addNum << "名新员工" << endl;
		cout << "现在共有" << mEmpNum << "名员工" << endl;

		//将数据保存到文件
		this->save();

		//更改标志状态，文件不为空
		this->mFileIsEmpty = false;
		
	}
	else
	{
		cout << "输入有误，请输入大于0的整数。" << endl;
	}
}

//保存文件
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//遍历数组，写入每个员工的id，姓名以及部门编号
	for (int i=0; i < this->mEmpNum ; i++) {
		ofs << this->mEmpArray[i]->mId << " "
			<< this->mEmpArray[i]->mName << " "
			<< this->mEmpArray[i]->mDeptId << endl;
	}
	//关闭文件
	ofs.close();
}