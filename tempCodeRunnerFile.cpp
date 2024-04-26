            // Check if the line contains a label
            if (line.find(':') != string::npos)
            {
                line.erase(remove(line.begin(), line.end(), ' '), line.end());
                int position = -1;
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == ':')
                    {
                        position = i;
                    }
                }
                // if (line.at(position + 1) == '\n' || line.at(position + 1) == '\t')
                // {
                // cerr << "Cannot write Insturction after Label, please rewrite the syntex error" << endl;
                // exit(51);
                //}
                // Extract label and its memory address
                istringstream lineStream(line);
                string label;
                getline(lineStream, label, ':');
                if (isdigit(label[0]))
                {
                    cerr << "First character of label cannot be a digit " << label << endl;
                    return;
                }
                // Store label and its memory address
                labelMap[label] = pc + 4;
            }
        }
        pc += 4;
    }
    file.close();
}
void RISCV_Instructions::execute(vector<Instruction> &instruction)
{
    int programCounterNew = instruction[instruction.size() - 1].pc;
    cout << "Program Counter New: " << programCounterNew << endl;
    cout << "Program Counter: " << programCounter << endl;