import os

os.makedirs('./prepdata', exist_ok=True)

for dirs in os.listdir('./data'):
    os.makedirs(f'./prepdata/{dirs}', exist_ok=True)
    for file_name in os.listdir(f'data/{dirs}'):
        with open(f'./data/{dirs}/{file_name}', 'r') as file:
            data = [float(line.strip()) for line in file]

        minimum = data[0]
        maximum = data[0]
        mean = 0
        count = 0
        for i in range(len(data)):
            minimum = min(minimum, data[i])
            maximum = max(maximum, data[i])
            mean += data[i]
            count += 1
        mean /= count
        first_quart = data[count//4]
        second_quart = data[count//2]
        third_quart = data[(3 * count)//4]

        with open(f'./prepdata/{dirs}/{file_name}', 'w') as file:
            file.write(f'Среднее арифметическое:{mean:.6f}\n')
            file.write(f'Минимум:{minimum}\n')
            file.write(f'Максимум:{maximum}\n')
            file.write(f'Первый квартиль:{first_quart}\n')
            file.write(f'Второй квартиль:{second_quart}\n')
            file.write(f'Третий квартиль:{third_quart}\n')
            file.write(f'Количество итераций:{count}\n')
