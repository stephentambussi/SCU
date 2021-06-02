class Person:
    def __init__(self, name, jobs, age=None):
        self.name=name
        self.jobs=jobs
        self.age=age

    def info(self):
        return(self.name, self.jobs)

rec1 = Person('Bob', ['dev', 'mgr'], 40.5)
rec2 = Person('Sue', ['dev', 'cto'])

print(rec1.jobs)
print(rec2.info())
