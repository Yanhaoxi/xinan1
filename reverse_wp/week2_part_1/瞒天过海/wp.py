import dataclasses

@dataclasses.dataclass
class Data:
    value: str
    state: bool #True if visited, False if not

class Loop:
    feature:int
    loop:list[Data]
    length:int
    def __init__(self, feature:int=0, value:str=''):
        self.feature = feature
        self.length = len(value)
        self.loop = [Data(value[i], False) for i in range(self.length)]

    def __getitem__(self, index:int):
        return self.loop[index]
    
    def step_on(self,step):#到下一个
        step += 1
        tmp = self.loop[step % self.length]
        while tmp.state:
            step += 1
            step %= self.length
            tmp = self.loop[step % self.length]
            continue
        return step

    def josephus(self,step:int)->list[str]:
        vector:list[str]=[]
        step-=1
        while True:
            tmp = self.loop[step % self.length]
            vector.append(tmp.value)
            tmp.state = True
            if len(vector) >= self.length:
                break
            for i in range(self.feature):
                step=self.step_on(step)

        for i in self.loop:#reset state
            i.state = False
        return vector
    
    def print(self):
        print(''.join([i.value for i in self.loop]))

    def loop_return(self):
        return ''.join([i.value for i in self.loop])

    def feature_print(self):
        print(self.josephus(self.feature))

    def feature_return(self):
        return self.josephus(self.feature)

    def recover(self, vector:list[str])->None:
        step=self.feature-1
        self.length = len(vector)
        self.loop =[Data('',False) for i in range(self.length)]
        i=0
        while True:
            tmp = self.loop[step % self.length]
            tmp.value = vector[i]
            tmp.state = True
            i+=1
            if i>=self.length:
                break
            for _ in range(self.feature):
                step=self.step_on(step)

        for i in self.loop:#reset state
            i.state = False
        return None
    

loop_sis = Loop(16, 'soge5_ub}fal_d1ild40oaeqvg{nli_a6es6_ra')
loop_sis.feature_print()
loop_bro= Loop(13, '')
loop_bro.recover(loop_sis.feature_return())
assert loop_bro.feature_return()==loop_sis.feature_return()
loop_bro.print()
