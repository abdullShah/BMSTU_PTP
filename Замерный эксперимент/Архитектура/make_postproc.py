import os
import matplotlib.pyplot as pyplot

os.makedirs("graphs", exist_ok=True)
for dirs in os.listdir('prepdata'):
    os.makedirs(f'graphs/{dirs}', exist_ok=True)
    time = []
    size = []
    maximum = []
    minimum = []
    first_quart = []
    second_quart = []
    third_quart = []
    for file_name in os.listdir(f'prepdata/{dirs}'):
        with open(f'prepdata/{dirs}/{file_name}', "r") as file:
            cur_size = os.path.basename(file_name).split(".")[0].split("_")[-1]
            size.append(float(cur_size))
            time_line = file.readline().rstrip("\n")
            time.append(float(time_line.split(":")[1]))
            minimum_line = file.readline().rstrip("\n")
            minimum.append(float(minimum_line.split(":")[1]))
            maximum_line = file.readline().rstrip("\n")
            maximum.append(float(maximum_line.split(":")[1]))
            first_quart_line = file.readline().rstrip("\n")
            first_quart.append(float(first_quart_line.split(":")[1]))
            second_quart_line = file.readline().rstrip("\n")
            second_quart.append(float(second_quart_line.split(":")[1]))
            third_quart_line = file.readline().rstrip("\n")
            third_quart.append(float(third_quart_line.split(":")[1]))

    sorted_arrays = sorted(zip(size, time, minimum, maximum, first_quart, second_quart, third_quart))
    size = [size for size, _, _, _, _, _, _ in sorted_arrays]
    time = [time for _, time, _, _, _, _, _ in sorted_arrays]
    err = [[time - err_min for _, time, err_min, _, _, _, _ in sorted_arrays],
            [err_max - time for _, time, _, err_max, _, _, _ in sorted_arrays]]

    data = []
    for i in range(len(sorted_arrays)):
        data.append([sorted_arrays[i][2], sorted_arrays[i][4], sorted_arrays[i][5], sorted_arrays[i][6], sorted_arrays[i][3]])

    pyplot.subplots(figsize=(10, 8))
    pyplot.plot(size, time, marker='o')
    pyplot.xlabel('Число элементов массива, N')
    if "tsc" in dirs:
        pyplot.ylabel('Время выполнения, число тактов')
    else:
        pyplot.ylabel('Время выполнения, мс')
    pyplot.title('Кусочно-линейный график')
    pyplot.grid(True)
    pyplot.savefig(f'graphs/{dirs}/segmented.svg', format='svg')

    pyplot.title('Кусочно-линейный график с ошибкой')
    pyplot.errorbar(size, time, yerr=err, fmt='-o', capsize=4)
    pyplot.savefig(f'graphs/{dirs}/error.svg', format='svg')

    if (len(size) != 0):
        pyplot.boxplot(data, positions=size, patch_artist=True, showfliers=False, widths=50)
    pyplot.title('Кусочно-линейный график с усами')
    pyplot.xticks(rotation=90)
    pyplot.savefig(f'graphs/{dirs}/moustache.svg', format='svg')
    pyplot.cla()
