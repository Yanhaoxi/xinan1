from collections import Counter
string="""7018543203343014811192845309202335863364671491621220673444992876860381071456658655770722055646113434223687525348833224089932434142670333728435329238195539680756468901496178333876407750676411078287468953985899683171227516859604091765268625546298376659471015715610512553134117330798150996049485863931680775299356894338447759576664868070180449540739473645487617331617890662796247292252674982651966935004390593835955052668949749193886173386997984943385052954297581680440829495556820131928805627596996251147917307642228214947704622993238550441180152717204627421672384530949690232265132668510365117134715515844502512168348880100763103652548730242937558020236669665012925681379715919554665871884610245029457252038987248347901132437693496934695333602455872925323096505422580935599192729040840672690799441352355641697206562434524765130289453002513055952267707625667979138758556794493013736627694726018997922924539207702252925494574426076424739987193251551795478339353026626990853827058193213003114182062628603"""
class Tree:
    def __init__(self, charecter ,value):
        self.charecter:str|None = charecter
        self.value:int = value
        self.left = None
        self.right = None

    def insert(self, tree:'Tree', direction):
        if direction == 'left':
            if self.left is None:
                self.left = tree
            else:
                raise('Left child already exists')
        elif direction == 'right':
            if self.right is None:
                self.right = tree
            else:
                raise('Right child already exists')

    def print_tree(self, prefix=""):
        if self.charecter is not None:
            print(prefix + str(self.charecter), self.value)
        else:
            print(prefix + "#")
        if self.left is not None:
            self.left.print_tree(prefix + "|-- L: ")
        if self.right is not None:
            self.right.print_tree(prefix + "|-- R: ")

    def __repr__(self):
        return f'{self.charecter} : {self.value}'
    
    def convert_to_dict(self, prefix=""):
        if self.charecter is not None:
            return {self.charecter: prefix}
        else:
            dict = {}
            if self.left is not None:
                dict.update(self.left.convert_to_dict(prefix + "0"))
            if self.right is not None:
                dict.update(self.right.convert_to_dict(prefix + "1"))
            return dict
        
    def process_string(self, string:str):
        node = self
        for i in string:
            if i == '0':
                node = node.left
            elif i == '1':
                node = node.right
            else:
                raise ValueError('Invalid string')
        if node.charecter is None:
            raise ValueError('String does not represent a character in the tree')
        return node.charecter
        
def create_huffman_tree(input_string):
    count_dict = Counter(input_string)
    # print(count_dict)
    fin_list = [Tree(key,value) for key, value in count_dict.items()]

    fin_list.sort(key=lambda x: (-x.value, -ord(x.charecter)))

    while(len(fin_list)>1):
        left = fin_list.pop()
        right = fin_list.pop()
        new_tree = Tree(None, left.value+right.value)
        new_tree.insert(left, 'left')
        new_tree.insert(right, 'right')
        fin_list.append(new_tree)
        fin_list.sort(key=lambda x:-x.value)
    
    return fin_list[0]  # 返回Huffman树的根节点

# import random

# def generate_random_string(length):
#     letters =[ str(i) for i in range(10)]
#     result_str = ''.join(random.choice(letters) for i in range(length))
#     return result_str

huffman_tree=create_huffman_tree(string)
dic=huffman_tree.convert_to_dict()
flag=''
for i in '932029468179920529368592457954839940996608815796608129361692416936129361667204889232993288823207':
    flag+=dic[i]
while len(flag)>8:
    print(chr(int('0b'+flag[:8],2)),end='')
    flag=flag[8:]
print('}',end='')
# flag{sleep_talking_interpreter_4f8cffd3}