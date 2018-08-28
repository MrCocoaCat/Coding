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
