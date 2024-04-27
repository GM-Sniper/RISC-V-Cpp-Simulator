import tkinter as tk
from tkinter import filedialog
import subprocess

def launch_cpp_process():
    # Run the C++ executable
    process = subprocess.Popen(["./RISCV_Instructions.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return process

def get_cpp_output(process, input_str1, input_str2, input_str3):
    # Send inputs to the C++ process and get output
    inputs = f"{input_str1}\n{input_str2}\n{input_str3}\n"  # Separate inputs by newline
    stdout, stderr = process.communicate(input=inputs)
    return stdout

def parse_input():
    input_str1 = input_entry1.get()
    input_str2 = input_entry2.get()
    input_str3 = input_entry3.get()
    process = launch_cpp_process()
    output = get_cpp_output(process, input_str1, input_str2, input_str3)
    output_text.delete("1.0", tk.END)
    output_text.insert(tk.END, output)

root = tk.Tk()
root.title("RISCV Simulator")

input_label1 = tk.Label(root, text="Enter the assembly code path in txt:")
input_label1.pack()

input_entry1 = tk.Entry(root, width=60)
input_entry1.pack()

input_label2 = tk.Label(root, text="Enter the data needed for the code (if no data needed just add an empty txt file):")
input_label2.pack()

input_entry2 = tk.Entry(root, width=60)
input_entry2.pack()

input_label3 = tk.Label(root, text="Enter the program counter for the instruction to start with:")
input_label3.pack()

input_entry3 = tk.Entry(root, width=60)
input_entry3.pack()

parse_button = tk.Button(root, text="Parse Input", command=parse_input)
parse_button.pack()

output_text = tk.Text(root, height=50, width=600)
output_text.pack()

root.mainloop()