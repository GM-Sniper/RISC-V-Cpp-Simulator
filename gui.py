import tkinter as tk
from tkinter import filedialog
import subprocess

def launch_cpp_process():
    # Run the C++ executable
    process = subprocess.Popen(["./main.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return process

def get_cpp_output(process, input_str1, input_str2):
    # Send inputs to the C++ process and get output
    inputs = f"{input_str1}\n{input_str2}\n"  # Separate inputs by newline
    stdout, stderr = process.communicate(input=inputs)
    return stdout

def parse_input():
    input_str1 = input_entry1.get()
    input_str2 = input_entry2.get()
    process = launch_cpp_process()
    output = get_cpp_output(process, input_str1, input_str2)
    output_text.delete("1.0", tk.END)
    output_text.insert(tk.END, output)

root = tk.Tk()
root.title("Two-String Input GUI")

input_label1 = tk.Label(root, text="Enter first string:")
input_label1.pack()

input_entry1 = tk.Entry(root, width=60)
input_entry1.pack()

input_label2 = tk.Label(root, text="Enter second string:")
input_label2.pack()

input_entry2 = tk.Entry(root, width=60)
input_entry2.pack()

parse_button = tk.Button(root, text="Parse Input", command=parse_input)
parse_button.pack()

output_text = tk.Text(root, height=10, width=60)
output_text.pack()

root.mainloop()
