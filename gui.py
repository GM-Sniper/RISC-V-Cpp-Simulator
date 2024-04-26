import tkinter as tk
import subprocess

def parse_code():
    code = code_entry.get()
    # Start the C++ executable as a separate process
    process = subprocess.Popen(["./parser.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate(input=code)
    output_text.delete("1.0", tk.END)  # Clear previous content
    output_text.insert(tk.END, stdout)

root = tk.Tk()
root.title("C++ Parser GUI")

label = tk.Label(root, text="Enter code:")
label.pack()

code_entry = tk.Entry(root, width=50)
code_entry.pack()

parse_button = tk.Button(root, text="Parse", command=parse_code)
parse_button.pack()

output_text = tk.Text(root, height=10, width=50)
output_text.pack()

root.mainloop()
