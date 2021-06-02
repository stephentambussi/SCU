class FirstClass:
    def setdata(self, value1, value2):
        self.data1=value1
        self.data2=value2
    def display(self):
        print(self.data1, '\n', self.data2, '\n')

class SecondClass(FirstClass):
    def adder(self, val1, val2):
        a=val1+val2
        print(a)

z=SecondClass()
z.setdata(10,20)
z.display()
z.adder(-5,-10)
