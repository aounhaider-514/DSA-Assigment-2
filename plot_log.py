



import re
import matplotlib.pyplot as plt

def parse_log(filename="log.txt"):
    """
    Parses the log file and extracts test numbers and durations.
    Returns two lists: test_numbers, durations (in microseconds).
    """
    test_numbers = []
    durations = []

    # Read with UTF-8 encoding to handle the micro sign (μ)
    with open(filename, 'r', encoding='utf-8') as f:
        content = f.read()

    # Pattern: Test # followed by digits, then any characters, then "Duration" followed by
    # optional spaces, an opening parenthesis, any characters, closing parenthesis,
    # colon, spaces, and finally the duration digits.
    pattern = r"Test #(\d+).*?Duration\s*\(.*?\)\s*:\s*(\d+)"
    matches = re.findall(pattern, content, re.DOTALL)

    for match in matches:
        test_num = int(match[0])
        dur = int(match[1])
        test_numbers.append(test_num)
        durations.append(dur)

    return test_numbers, durations

def plot_durations(test_numbers, durations):
    """
    Creates a bar chart of sorting duration vs test number.
    """
    plt.figure(figsize=(10, 6))
    plt.bar(test_numbers, durations, color='skyblue', edgecolor='black')
    plt.xlabel('Test Number')
    plt.ylabel('Duration (microseconds)')
    plt.title('QuickSort Performance on 10 Samples (100 elements each)')
    plt.xticks(test_numbers)
    plt.grid(axis='y', linestyle='--', alpha=0.7)

    # Add value labels on top of bars
    for i, (test, dur) in enumerate(zip(test_numbers, durations)):
        plt.text(test, dur + max(durations)*0.01, str(dur),
                 ha='center', va='bottom', fontsize=9)

    plt.tight_layout()
    plt.savefig('sorting_performance.png')
    plt.show()

if __name__ == "__main__":
    try:
        tests, durs = parse_log("log.txt")
        if not tests:
            print("No duration data found in log.txt. Please check the file format.")
        else:
            print(f"Found {len(tests)} tests:")
            for t, d in zip(tests, durs):
                print(f"Test {t}: {d} μs")
            plot_durations(tests, durs)
    except FileNotFoundError:
        print("log.txt not found in the current directory.")
    except Exception as e:
        print(f"An error occurred: {e}")