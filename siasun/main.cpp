#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include<pthread.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

struct argument
{
    string m_dirname;
    string m_findname;
};

int FindFlag = 0;
vector<pthread_t> vePthead;
int i = 0;

//void *listAllFiles(string dirname,string findname)
void *listAllFiles(void* arg)
{

    string dirname = (( struct argument * )arg)->m_dirname;
    string findname =(( struct argument * )arg)->m_findname;
    cout<<"我来自线程，"<<i<<"传递给我的参数是"<< dirname<<"  "<<findname <<endl;
    i++;
    struct dirent *filename;//readdir 的返回类型
    DIR *dir;//血的教训阿，不要随便把变量就设成全局变量。。。。
    dir = opendir(dirname.c_str());
    if(dir == NULL)
    {
        cerr<<"error"<<dirname<<endl;
        exit(1);
    }
    while((filename = readdir(dir)) != NULL)
    {
        //目录结构下面问什么会有两个.和..的目录？ 跳过着两个目录
        if(!strcmp(filename->d_name,".")||!strcmp(filename->d_name,".."))
        {
            continue;
        }
        //非常好用的一个函数，比什么字符串拼接什么的来的快的多
        //sprintf(path,"%s/%s",dirname,filename->d_name);
        string path = dirname + filename->d_name;
        struct stat s;
        lstat(path.c_str(),&s); //读入到结构体中

        if(S_ISDIR(s.st_mode)) //如果是文件夹类型
        {

            pthread_t pthread1;
            argument  *arg = new argument;
            arg->m_dirname = path;
            arg->m_findname = findname;
            //pthread_create(&pthread1, NULL, thread1_func,NULL);
            pthread_create(&pthread1, NULL, listAllFiles, (void*)arg );
           // listAllFiles(path,findname);//递归调用
            vePthead.push_back(pthread1);
        }
        else
        {
            string Sfilename;
            Sfilename = filename->d_name;
            if(findname == Sfilename)
            {
                cout<<"找到文件路径为:"<<path<<endl;
               //cout<<path<<endl;
               FindFlag = 1;
              // pthread_exit(0);
           }

        }
    }
    closedir(dir);

}

int main(int argc, char **argv)
{

    if(argc != 3)
    {
        printf("one dir required!(for eample: ./a.out /home/myFolder)\n");
        exit(1);
    }
    argument  *arg = new argument;
    arg->m_dirname = argv[1];
    arg->m_findname = argv[2];
    pthread_t pthread1;

    pthread_create(&pthread1, NULL, listAllFiles, (void*)arg );

    sleep(1);
    for(auto ite = vePthead.begin();ite != vePthead.end();ite++)
    {
        cout<<"wait  "<<*ite<<endl;
        pthread_join(*ite, NULL);
    }
    if(FindFlag == 0)
    {
        cout<< "未找到该文件"<<endl;
    }
    return 0;
}