//#include <iostream>
//#include <string>
//using namespace std;
// 
//class IUser
//{
//public:
//    virtual void getUser() = 0;
//    virtual void setUser() = 0;
//};
// 
//class SqlUser :public IUser
//{
//public:
//    void getUser()
//    {
//        cout << "在sql中返回user" << endl;
//    }
//    void setUser()
//    {
//        cout << "在sql中设置user" << endl;
//    }
//};
// 
//class AccessUser :public IUser
//{
//public:
//    void getUser()
//    {
//        cout << "在Access中返回user" << endl;
//    }
//    void setUser()
//    {
//        cout << "在Access中设置user" << endl;
//    }
//};
// 
// 
//class IDepartment
//{
//public:
//    virtual void getDepartment() = 0;
//    virtual void setDepartment() = 0;
//};
// 
//class SqlDepartment :public IDepartment
//{
//public:
//    void getDepartment()
//    {
//        cout << "在sql中返回Department" << endl;
//    }
//    void setDepartment()
//    {
//        cout << "在sql中设置Department" << endl;
//    }
//};
// 
//class AccessDepartment :public IDepartment
//{
//public:
//    void getDepartment()
//    {
//        cout << "在Access中返回Department" << endl;
//    }
//    void setDepartment()
//    {
//        cout << "在Access中设置Department" << endl;
//    }
//};
// 
//class IFactory
//{
//public:
//    virtual IUser *createUser() = 0;
//    virtual IDepartment *createDepartment() = 0;
//};
// 
//class SqlFactory :public IFactory
//{
//public:
//    IUser *createUser()
//    {
//        return new SqlUser();
//    }
//    IDepartment *createDepartment()
//    {
//        return new SqlDepartment();
//    }
//};
// 
//class AccessFactory :public IFactory
//{
//public:
//    IUser *createUser()
//    {
//        return new AccessUser();
//    }
//    IDepartment *createDepartment()
//    {
//        return new AccessDepartment();
//    }
//};
// 
///*************************************************************/
// 
//class DataAccess
//{
//private:
//    static string db;
//    //string db="access";
//public:
//    static IUser *createUser()
//    {
//        if (db == "access")
//        {
//            return new AccessUser();
//        }
//        else if (db == "sql")
//        {
//            return new SqlUser();
//        }
//    }
//    static IDepartment *createDepartment()
//    {
//        if (db == "access")
//        {
//            return new AccessDepartment();
//        }
//        else if (db == "sql")
//        {
//            return new SqlDepartment();
//        }
//    }
//};
//string DataAccess::db = "sql";
// 
///*************************************************************/
// 
//int main()
//{
//    //IFactory *factory=new SqlFactory();
//    IFactory *factory;
//    IUser *user;
//    IDepartment *department;
// 
//    factory = new AccessFactory();
//    user = factory->createUser();
//    department = factory->createDepartment();
// 
//    user->getUser();
//    user->setUser();
//    department->getDepartment();
//    department->setDepartment();
// 
//    user = DataAccess::createUser();
//    department = DataAccess::createDepartment();
// 
//    user->getUser();
//    user->setUser();
//    department->getDepartment();
//    department->setDepartment();
// 
//    return 0;
//} 