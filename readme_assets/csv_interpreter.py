import pandas as pd
import csv
from matplotlib import pyplot as plt


def plot_results(filename, headers, plotName, plot_iter=30):
    df = pd.read_csv(filename)

    for h in headers:
        df.iloc[0:plot_iter][h].plot(alpha=0.5)

    plt.title(plotName)
    plt.xlabel("Iterations")
    plt.ylabel("Weight (as a probability)")

    ax = plt.subplot()
    # Shrink current axis by 20%
    box = ax.get_position()
    ax.set_position([box.x0, box.y0, box.width * 0.8, box.height])

    # Put a legend to the right of the current axis
    ax.legend(loc='center left', bbox_to_anchor=(1, 0.5))

    plt.savefig(filename.replace('.', '_') + '.png')
    plt.show()


if __name__ == "__main__":
    plot_results('network1_out.csv',
                 ['Page_1', 'Page_2', 'Page_3', 'Page_4'],
                 "Network 1 Page Weights")
    plot_results('network2_out.csv',
                 ['Page_1', 'Page_2', 'Page_3', 'Page_4', 'Page_5', 'Page_6', 'Page_7', 'Page_8'],
                 "Network 2 Page Weights")
    plot_results('network3_out.csv',
                 ['Page_1', 'Page_2', 'Page_3', 'Page_4', 'Page_5', 'Page_6'],
                 "Network 3 Page Weights")
    plot_results('network4_out.csv',
                 ['Page_1', 'Page_2', 'Page_3', 'Page_4', 'Page_5', 'Page_6', 'Page_7', 'Page_8', 'Page_9', 'Page_10',
                  'Page_11'],
                 "Network 4 Page Weights",
                 plot_iter=50)
