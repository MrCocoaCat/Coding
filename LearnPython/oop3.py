class A():
    def __init__(self):
        print("init A")
    pass


class B(A):
    def __init__(self):
        print("init B")
    pass

# 多继承，可以使用父类的功能
class C(B):
    age = "sf"
    pass


c = C()
print(C.__mro__)
# 多态
# 多态不是语法，是一种设计思想

# 检测是否为子类
print(issubclass(B, A))

# 检测是否未其实例
print(isinstance(c, C))

# 检测是否含有某个成员,检测aeg是否为c的成员
print(hasattr(c, "age"))

# 获取函数成员列表

print(dir(c))

# get　获取属性
# set　添加属性
# delete 删除属性

class Student():
    def __init__(self, name, age):
        self.name = name
        self.age = age
        self.setname(self.name)
    # 介绍自己
    def intro(self):
        print("Hi my name is {0}".format(self.name))

    def setname(self, name):
        self.name = name.upper()


s1 = Student("aa", 18)
s1.intro()

class Person():
    def fget(self):
        return self._name

    def fset(self, name):
        self._name = name.upper()

    name = property(fget, fset, "do pro")

p = Person()
p.name = "tulin"
print(p.name)


# __dict__ 以字典方式显示类的成员组成
# __doc__ 获取类的文档信息　
# __name__ 获取类的名称，如果在模块中使用，则获取模块名称
# __base__　获取某个类的所有父类

