file_path = input()
with open(file_path, 'r') as file:
    times = [float(line.strip()) for line in file]

size = int(file_path.split("_")[-1].split(".")[0])
n = len(times)

avg = sum(times) / n

s_sq = 0
for i in range(n):
    s_sq += (times[i] - avg)**2
s_sq /= (n - 1)
s = s_sq ** 0.5

std_err = s / (n ** 0.5)
rse = std_err / avg * 100

print(rse)
