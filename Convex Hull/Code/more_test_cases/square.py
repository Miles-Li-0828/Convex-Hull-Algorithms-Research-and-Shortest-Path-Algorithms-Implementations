import random

x_list = []
y_list = []

i = 0
num_point = 5000
while i < num_point - 4:
    x = random.uniform(1, 499)
    y = random.uniform(1, 499)
    if x not in x_list and y not in y_list:
        x_list.append(x)
        y_list.append(y)
        i += 1
with open("square3.txt", "w") as f:
    f.write(str(num_point) + "\n")
    f.write("0 0\n")
    f.write("1000 0\n")
    f.write("1000 1000\n")
    f.write("0 1000\n")
    for i in range(num_point - 4):
        f.write(str(x_list[i]) + " " + str(y_list[i]) + "\n")
