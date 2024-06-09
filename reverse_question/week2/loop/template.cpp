#include <iostream>
#include <vector>
#include <stdexcept>
#include<string>
###exec:
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
    
    def step_on(self,step):#到下一个活着的
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
    
import random
import time
random.seed(time.time())
sis_fea=random.choice(range(2, 20))
bro_fea=random.choice(range(2, 20))
while(abs(bro_fea-sis_fea)<2):
    bro_fea=random.choice(range(2, 20))
loop=Loop(bro_fea, flag)
loop_sis=Loop(sis_fea, '')
loop_sis.recover(loop.feature_return())
flag_list=loop_sis.loop_return()
flag_list='\"'+flag_list+'\"'
###
#define Data char
#define FLAG_LEN 39
#define SIS_TOY ###eval:flag_list###
#define SIS_FEA ###eval:sis_fea###
#define BRO_FEA ###eval:bro_fea###
class Loop {
private:
    struct Node {
        Data value;
        Node* next;
    };

    Node* head;
    int len;
    int feature;

public:

    Loop(int size,int featrue = 0, const std::vector<Data>& values = std::vector<Data>()) : len(size),feature(featrue){
        if (!values.empty() && values.size() < size) {
            throw std::invalid_argument("That's too short!");
        }
    
        head = new Node[size];
        for (int i = 0; i < size; ++i) {
            head[i].value = values[i];
            head[i].next = &head[(i + 1) % size];
        }
    }

    // Destructor
    ~Loop() {
        delete[] head;
    }

    // Solve the Josephus problem
    std::vector<Data> josephus(int step) {
        if (step < 1) {
            throw std::invalid_argument("Invalid parameters");
        }
    
        std::vector<Data> result;
        Node* current = &head[0];
        Node* prev = &head[len - 1];
        int tmp = len;
        while (tmp > 1) {
            for (int i = 0; i < step - 1; ++i) {
                prev = current;
                current = current->next;
            }
            result.push_back(current->value);
            prev->next = current->next;
            current = current->next;
            tmp--;
        }
        result.push_back(current->value);
        recover();
        return result;
    }

    void recover() {
        Node* current = &head[0];
        for (int i = 0; i < len; ++i) {
            current->next = &head[(i + 1) % len];
            current = current->next;
        }
    }

    void setFeature(int f) {
        feature = f;
    }

    int getFeature() {
        return feature;
    }

    void print() {
        Node* current = &head[0];
        for (int i = 0; i < len; ++i) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout<<" Feature"<< feature << std::endl;
    }

    void feature_print() {
        const std::vector<Data>& result = josephus(feature);
        for (const auto& value : result) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    bool operator==(Loop& other){
        return josephus(feature) == other.josephus(other.feature);
    }

};

std::string str = SIS_TOY;
std::vector<char> sis_result(str.begin(), str.end());
Loop loop_sis(FLAG_LEN, SIS_FEA, sis_result);

int main(){
    std::cout<<"Sister: Brother, look at my new toy! It's my favorite! It's has two states.\n"<<std::endl;
    std::cout << "Sister's toy:" << std::endl;
    loop_sis.print();
    std::cout << "Sister's toy after playing:" << std::endl;
    loop_sis.feature_print();
    std::cout << std::endl << "Brother: Let me try!" << std::endl;
    std::cout << "Narration :The toy is broken" << std::endl;

    std::string input;
    std::cout << "Brother : I think I can fix it , I should put in these data:";
    std::getline(std::cin, input);
    std::vector<char> bro_result(input.begin(), input.end());
    Loop loop_bro(FLAG_LEN, BRO_FEA, bro_result);
    if(loop_sis == loop_bro){
        std::cout << "Brother :Oh! It do work!" << std::endl;
    }
    else{
        std::cout << "Brother :Maybe I'll buy a new one" << std::endl;
    }
    return 0;
}