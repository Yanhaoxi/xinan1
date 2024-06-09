#include <stdio.h>
#include <stdlib.h>
#include <string.h>
###exec:
from collections import Counter
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

import random

def generate_random_string(length):
    letters =[ str(i) for i in range(10)]
    result_str = ''.join(random.choice(letters) for i in range(length))
    return result_str

random_string = generate_random_string(1000)
huffman_tree = create_huffman_tree(random_string)

binary_flag = ''.join(format(ord(c), '08b') for c in flag)
str_dict=huffman_tree.convert_to_dict()
# print(str_dict)
num_dict = {v:k for k,v in str_dict.items()}
# print(num_dict)

result = ''
tmp=''
for i in range(len(binary_flag)):
    tmp += binary_flag[i]
    if tmp in num_dict:#由于是前缀码，所以不需要考虑最长匹配
        result+=num_dict[tmp]
        tmp=''
# print(result)
result='\"'+result+'\"'
random_string = '\"'+random_string+'\"'
###
#define CHAR_SIZE 128  // ASCII表的大小
#define FLAG_LEN 40  // 输入字符串的最大长度
// Huffman树的节点结构
typedef struct HuffmanTreeNode {
    char value;  // 字符值，非叶子节点为'\0'
    struct HuffmanTreeNode *left, *right;
} HuffmanTreeNode;

// 链表节点结构
typedef struct ListNode {
    HuffmanTreeNode *treeNode;
    int freq;
    struct ListNode *next;
} ListNode;

// 创建新的Huffman树节点
HuffmanTreeNode* createHuffmanTreeNode(char value) {
    HuffmanTreeNode* node = (HuffmanTreeNode*)malloc(sizeof(HuffmanTreeNode));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

// 插入排序将字符构成树节点并按频次排序到链表（保持从小到大的稳定排序）
void sortedInsert(ListNode **headRef, HuffmanTreeNode *newTreeNode, int freq) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->treeNode = newTreeNode;
    newNode->next = NULL;
    newNode->freq = freq;

    // 如果链表为空或新节点应该放在首位
    if (*headRef == NULL || (*headRef)->freq > newNode->freq) {
        newNode->next = *headRef;
        *headRef = newNode;
    } else {
        // 找到新节点应该插入的位置
        ListNode *current = *headRef;
        while (current->next != NULL && current->next->freq <= newNode->freq) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int mergeTwoSmallest(ListNode **headRef) {
    // 如果链表为空或只有一个节点，无法合并
    if (*headRef == NULL || (*headRef)->next == NULL) {
        return 0;
    }

    // 取出频率最小的两个节点
    ListNode *firstNode = *headRef;
    ListNode *secondNode = firstNode->next;

    // 从链表中移除这两个节点
    *headRef = secondNode->next;

    // 创建一个新的Huffman树节点，这两个节点作为子节点
    HuffmanTreeNode *newTreeNode = createHuffmanTreeNode('\0');
    newTreeNode->left = firstNode->treeNode;
    newTreeNode->right = secondNode->treeNode;

    // 计算新节点的频率
    int newFreq = firstNode->freq + secondNode->freq;

    // 将新节点插入到链表中
    sortedInsert(headRef, newTreeNode, newFreq);

    // 释放原来的两个链表节点
    free(firstNode);
    free(secondNode);
    return 1;
}
// 销毁霍夫曼树
void destroyHuffmanTree(HuffmanTreeNode *root) {
    if (root == NULL) {
        return;
    }

    destroyHuffmanTree(root->left);
    destroyHuffmanTree(root->right);

    free(root);
}

// 解码霍夫曼树至字符串
int decodeHuffmanTree(HuffmanTreeNode *root, const char *code, char *output, int outputSize) {
    HuffmanTreeNode *current = root;
    int outputIndex = 0;
    for (int i = 0; code[i] != '\0' && outputIndex < outputSize - 1; i++) {
        if (code[i] == '0') {
            current = current->left;
        } else if (code[i] == '1') {
            current = current->right;
        }

        if (current->left == NULL && current->right == NULL) {
            output[outputIndex++] = current->value;
            current = root;
        }
    }
    output[outputIndex] = '\0';  // 添加字符串结束符
    return 1;
}
// 将字符串转化为二进制的01字符串
void stringToBinary(char *input, char *output, int outputSize) {
    int outputIndex = 0;

    for (int i = 0; input[i] != '\0' && outputIndex < outputSize - 8; i++) {
        char c = input[i];
        for (int j = 7; j >= 0; j--) {
            output[outputIndex++] = ((c >> j) & 1) ? '1' : '0';
        }
    }
    output[outputIndex] = '\0';  // 添加字符串结束符
}

// 主函数
int main() {
    char random_string[] = ###eval:random_string###;  // 示例输入字符串
    printf("sleep talking: %s\n", random_string);
    int freq[CHAR_SIZE] = {0};
    int length = strlen(random_string);

    // 统计字符频次
    for (int i = 0; i < length; i++) {
        if (random_string[i] >= 0 && random_string[i] < CHAR_SIZE) {
            freq[random_string[i]]++;
        }
    }

    // 创建排序链表
    ListNode *sortedList = NULL;
    for (int i = 0; i < CHAR_SIZE; i++) {
        if (freq[i] > 0) {
            HuffmanTreeNode *newNode = createHuffmanTreeNode((char)i);
            sortedInsert(&sortedList, newNode, freq[i]);
        }
    }

    // 构建Huffman树
    while (mergeTwoSmallest(&sortedList));
    HuffmanTreeNode* root= sortedList->treeNode;
    free(sortedList);
    char input[64];  // 用户输入的字符串
    printf("You can say what I said yesterterday , I will tell you whether you are right.\n");
    fgets(input, FLAG_LEN+1, stdin);
    int end=strcspn(input, "\n");
    if (end != FLAG_LEN && input[end-1] != '}') {
        printf("No , that's not what I want to say\n");
        return 0;
    }
    input[strcspn(input, "\n")] = '\0';
    // 将输入字符串转化为01序列
    char binary[8*FLAG_LEN+1];
    stringToBinary(input, binary, sizeof(binary));
    // 解码01序列
    decodeHuffmanTree(root, binary, binary, sizeof(binary));
    char tmp_meaning[8*FLAG_LEN+1] =###eval:result###;
    if(strlen(binary) == strlen(tmp_meaning)) {
        if(!strcmp(tmp_meaning, binary)){
            printf("you must possess magic!!!!!\n");
            return 1;
        }
        else{
            printf("No , that's not what I want to say\n");
        }
    }
    destroyHuffmanTree(root);
    return 0;
}
