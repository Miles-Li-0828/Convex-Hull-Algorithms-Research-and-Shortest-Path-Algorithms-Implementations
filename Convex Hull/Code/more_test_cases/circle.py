import math


def generate_circle_points(num_points, radius):
    points = []
    angle_increment = 2 * math.pi / num_points
    for i in range(num_points):
        angle = i * angle_increment
        x = radius * math.cos(angle)
        y = radius * math.sin(angle)
        points.append((x, y))
    return points


# Define the number of points and radius of the circle
num_points = 3000
radius = 10

# Generate the points
points = generate_circle_points(num_points, radius)

# Print the points
with open("circle2.txt", "w") as f:
    f.write(str(num_points) + "\n")
    for point in points:
        for i in range(len(point)):
            f.write(str(point[i]))
            if i != len(point) - 1:
                f.write(" ")
        f.write("\n")
