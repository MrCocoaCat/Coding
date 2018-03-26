//双方接到是字节流，无法知道对方发的具体是什么消息，在每个协议相同的位置，放一个标明协议类型的字段
//为防止结构体中的类型赋值错误，所以定义一个公共基类，将协议字段放入公共基类进行保护继承
//协议中出现的字符数组性成员，必须有对应长度，只发有效长度
//防止两端的对其方式不同，导致发送错位，保留每段默认对其方式，采用将数据填充到一个字符串中，保证两端数据一致
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;
#define STR_LOGINTYPE 1
#define MAXPASSWORDLEN 10
struct STR_BASE
{
	STR_BASE(int nType):m_wProtoType(nType)
	{
	};
	virtual long Serialize(char szBuf[],long lBufLen) = 0;
	virtual bool UnSerialize(const char szBuf[],long lBufLen) = 0;
protected:
	int m_wProtoType;
};

struct STR_login:public STR_BASE
{
		STR_login();
		static int m_MinLen;
		long Serialize(char szBuf[],long lBufLen);
		bool UnSerialize(const char szBuf[],long lBufLen);
	public:
		int m_Id;
		int m_PasswordLen;
		char m_Password[MAXPASSWORDLEN];
};
int STR_login::m_MinLen = 12; //buf最小长度，如果小于这个值，那么一定错误

STR_login::STR_login():STR_BASE(STR_LOGINTYPE) //调用父类带参数构造
{
		m_Id=0;
		m_PasswordLen=0;
}
//序列化
long  STR_login::Serialize(char szBuf[],long lBufLen)
{
	//检查长度是否满足长度
	if( STR_login::m_MinLen > lBufLen)
	{
		return 0;
	}
	//协议类型
	*(int *)szBuf = m_wProtoType;
	szBuf += sizeof(m_wProtoType);
	//ID
	*(int *)szBuf = m_Id;
	szBuf += sizeof(m_Id);
	//密码长度
	*(int *)szBuf = m_PasswordLen;
	szBuf += sizeof(m_PasswordLen); 
	//判断
	lBufLen -= STR_login::m_MinLen;
	if(lBufLen < m_PasswordLen)
	{
		return 0;
	}
	memcpy(szBuf,m_Password,m_PasswordLen);
	szBuf += m_PasswordLen; 
	return (STR_login::m_MinLen + m_PasswordLen);

}
//反序列化
bool STR_login::UnSerialize(const char szBuf[],long lBufLen)
{
	if( STR_login::m_MinLen > lBufLen)
	{
		return 0;
	}
	//协议类型
	m_wProtoType = *(int *)szBuf ;
	szBuf += sizeof(m_wProtoType);
	//ID
	m_Id = *(int *)szBuf ;
	szBuf += sizeof(m_Id);
	//密码长度
	m_PasswordLen = *(int *)szBuf ;
	szBuf += sizeof(m_PasswordLen); 

	//检查密码有效长度
	lBufLen -= STR_login::m_MinLen;
	if(lBufLen < m_PasswordLen)
	{
		return false;
	}
	memcpy(m_Password,szBuf,m_PasswordLen);
	szBuf += m_PasswordLen; 
	return true;
	
}
int main()
{
	STR_login stru_temp;
	stru_temp.m_Id =12345;
	stru_temp.m_PasswordLen = 6;
	memcpy(stru_temp.m_Password,"admin",stru_temp.m_PasswordLen);
	cout<<"结构体大小为： "<<sizeof(stru_temp)<<endl;

	char szBuf[100]; //存放缓存的buf
	long selen = stru_temp.Serialize(szBuf,100);

	cout<<"序列化后大小为： "<<selen<<endl;
	/*******************************************/

	char szRet[100];
	memcpy(szRet,szBuf,selen); //收到数据的buf

	/*******************************************/
	STR_login stru_rec;
	stru_rec.UnSerialize(szRet,100);
	cout<<"接受后结果:  "<<endl;
	cout<<stru_rec.m_Id<<endl;
	cout<<stru_rec.m_PasswordLen<<endl;
	cout<<stru_rec.m_Password<<endl;
	//system("pause");
	
}

