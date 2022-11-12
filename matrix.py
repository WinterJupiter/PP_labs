import numpy as np

f_first = open("D:\\matrix1.txt", 'r')
f_second = open("D:\\matrix2.txt", 'r')
i = 0
j = 0
first = np.zeros((30, 30))
second = np.zeros((30, 30))
for line in f_first:
    first[i][j] = line
    j = j + 1
    if j == 30:
        i = i + 1
        j = 0
i = 0
j = 0
for line in f_second:
    second[i][j] = line
    j = j + 1
    if j == 30:
        i = i + 1
        j = 0
result = np.dot(first, second)
with open("D:\\result_py.txt", 'w', encoding='UTF-8') as file:
    file.write(str(result))

f_first.close()
f_second.close()
