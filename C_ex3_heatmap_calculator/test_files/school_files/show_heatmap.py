import matplotlib.pyplot as plt
import csv

with open('ofek_output.csv') as file:
    reader = csv.reader(file, quoting=csv.QUOTE_NONNUMERIC)
    n=[]
    for row in reader:
        if len(row) > 1:
            n.append(row[:-1])
    fig = plt.figure()
    fig.suptitle("Heat map")
    ax = fig.add_subplot(111)
    ax.imshow(n)

    plt.show()
