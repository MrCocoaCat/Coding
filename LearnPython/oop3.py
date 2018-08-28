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
    pass


c = C()

