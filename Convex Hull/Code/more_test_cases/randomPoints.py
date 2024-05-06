import random

num_point = 5000

with open("random3.txt", "w") as f:
    f.write(str(num_point) + "\n")
    for i in range(num_point + 1):
        x = random.uniform(1, 499)
        y = random.uniform(1, 499)
        f.write(str(x) + " " + str(y))
        if i != num_point:
            f.write("\n")
