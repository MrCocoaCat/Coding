#include <iostream>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "ThreadPool.h"

/*
class TestItask:public Itask
{
public:
	TestItask(int a,int b)
	{
		m_a = a;
		m_b = b;
	}
private:
	int m_a;
	int m_b;
public:
	void RunItask()
	{
		int a=0;
		for(int i=0;i<65530;i++)
		{
			for(int j=0;j<65530;j++)
			{
				a++;
			}
		}

		cout << m_a << "+" << m_b << "=" << m_a + m_b << endl;
		sleep(1);
	}
};
 */
class TestItask:public Itask
{
public:
	TestItask(ThreadPool *arg)
	{
		m_p =arg;
	}
    ~TestItask()
    {
        m_p = nullptr;
    }
private:
	ThreadPool *m_p;
    DIR *dir;
    string dirname;
    struct dirent *filename;
    struct stat s;
public:
	void RunItask()
	{
        while(1)
        {
            m_p->m_PathLock->Lock();
            cout<< "m_qFindPath 队列个数为:" << m_p->m_qFindPath->size() <<endl;
            if(! m_p->m_qFindPath->empty())
            {
                dirname = m_p->m_qFindPath->front();
                dirname+="/";
                m_p->m_qFindPath->pop();
                m_p->m_PathLock->UnLock();
                cout<< "检测文件 :"<< dirname<<endl;
            }
            else
            {
                //无文件
                m_p->m_PathLock->UnLock();
                sleep(1);
                exit(0);
            }
            dir = opendir(dirname.c_str());
            if(dir == nullptr)
            {
                std::cout<< "打开文件夹失败,文件夹路径为:" << dirname << std::endl;
                exit(1);
            }
            while((filename = readdir(dir)) != nullptr)
            {
                if(!strcmp(filename->d_name,".")||!strcmp(filename->d_name,".."))
                {
                    continue;
                }
                string tempFileName = filename->d_name;
                string tempPath = dirname + tempFileName;
                cout<<"判断文件"<<tempPath <<endl;
                lstat(tempPath.c_str(),&s); //读入到结构体中
                if(S_ISDIR(s.st_mode)) //如果是文件夹类型
                {
                    //将文件夹路径放入容器
                    m_p->m_PathLock->Lock();
                    m_p->m_qFindPath->push(tempPath);
                    cout<<"m_qFindPath 队列个数为:" <<m_p->m_qFindPath->size() <<endl;
                    m_p->m_PathLock->UnLock();
                }
                else if(tempFileName ==  m_p->m_FindFile)
                {
                        cout<< "找到目标文件" << tempPath  <<endl;
                        m_p->SetFlag();
                }
            }
            closedir(dir);
        }


	}
};
int main(int argc, char **argv)
{

	if(argc != 3)
	{
		std::cout<<"亲输入两个参数"<<endl;
		exit(1);
	}
	Itask *pItask;
	string findPath=argv[1];
	string findFile=argv[2];
	ThreadPool tp;
	bool ret = tp.CreateThreadPool(1);
    if(false == ret)
    {
        std::cout<<"创建线程失败"<<std::endl;
    }
    ret = tp.SetFind(findPath,findFile); //赋值查找路径
    if(false == ret)
    {
        std::cout<<"路径初始化失败"<<std::endl;
    }
	for(int i = 0 ; i < 2 ; i++)
	{

		pItask = new TestItask(&tp); //将
		tp.PushItask(pItask);
	}
	tp.DestoryThreadPool();
    if(!tp.JudgeFlag())
    {
        cout<<"未找到该文件"<<endl;
    }
	return 0;
}