import tkinter as tk
from tkinter import filedialog
import subprocess

import os

def parse_file():
    file_path = file_entry.get()
    if not os.path.exists(file_path):
        output_text.delete("1.0", tk.END)
        output_text.insert(tk.END, "File not found.")
        return
    if file_path.endswith(".txt"):
        process = subprocess.Popen(["./parser.exe", file_path], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate()
        output_text.delete("1.0", tk.END)
        output_text.insert(tk.END, stdout)
    else:
        output_text.delete("1.0", tk.END)
        output_text.insert(tk.END, "Invalid file format. Please select a .txt file.")


def browse_file():
    file_path = filedialog.askopenfilename(filetypes=[("Text files", "*.txt")])
    if file_path:
        file_entry.delete(0, tk.END)
        file_entry.insert(tk.END, file_path)

root = tk.Tk()
root.title("C++ Parser GUI")

file_label = tk.Label(root, text="Enter file path or browse:")
file_label.pack()

file_entry = tk.Entry(root, width=50)
file_entry.pack()

browse_button = tk.Button(root, text="Browse", command=browse_file)
browse_button.pack()

parse_button = tk.Button(root, text="Parse File", command=parse_file)
parse_button.pack()

output_text = tk.Text(root, height=10, width=50)
output_text.pack()

root.mainloop()
