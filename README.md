# CCP6214 Algorithm Design and Analysis – Group Assignment

**Group ID:** TT1L_G01  
**Lecture Section:** TC1L  
**Tutorial Section:** TT1L  

**Members:**
- ANGELA WONG XIN YI (252UC254PP) 
- DAMIA IRDINA BINTI AZZUDDIN RIZAL (252UC254RQ)
- NUR AFIA BINTI FAHRUDEAN (252UC254Q5)
- THULASIE A/P GANESAN (252UC254Q4)

---

## Project Overview

This repository contains the full implementation of the group assignment for CCP6214. The project includes:

- **Dataset generator** – creates 10 CSV files with unique random 10‑digit integers and 5‑letter strings.
- **Radix Sort (LSD)** – sorts integers from the rightmost digit:
  - `radix_sort_step` – shows sorting steps for a given row range.
  - `radix_sort` – sorts the whole dataset, outputs sorted CSV and running time.
- **Heap Sort (Max‑Heap)** – sorts using a heap data structure.
- **Hash Table Search** – implements search with linear collision resolution, measures best/average/worst case times.

---

## How to run using Code::Blocks

### Step 1: Download / Clone the repository

- Download the ZIP from GitHub and extract it to your computer.
- Or use GitHub Desktop to clone the repository.

### Step 2: Open each `.cpp` file in Code::Blocks

Each team member will work on their own `.cpp` files. **Do not put all files in one project** and keep them separate for clarity.

#### For Radix Sort:

1. Open Code::Blocks.
2. **File → Open** → navigate to `src/radix_sort_step.cpp`
3. The file will open in the editor.
4. Click **Build and Run** (or press F9).

**What happens when you click Build and Run:**
- The program looks for a file named `config.txt` in the **same folder as the `.cpp` file**.
- The program reads that `config.txt` file (lines starting with `#` are ignored, the first non‑comment line contains the parameters).

### Step 3: Prepare the `config.txt` file

**Place `config.txt` in the same folder as your `.cpp` file** (not inside `configs/` folder – Code::Blocks runs from the source file's directory).

Example `config.txt` for `radix_sort_step.cpp`:
This is a comment
dataset_1000.csv 1 7


Example `config.txt` for `radix_sort.cpp`:
This is a comment
dataset_1000.csv


### Step 4: Make sure your CSV datasets are accessible

- You can either **copy all CSV files** into the same folder as your `.cpp` file, OR
- Use **full paths** in `config.txt`, e.g.:
../datasets/dataset_1000.csv 1 7


**Recommended for simplicity:** Copy the CSV file you need to the same folder as your `.cpp` when testing.

### Step 5: Run for different datasets

To test a different dataset:

1. Close Code::Blocks.
2. **Edit `config.txt`** with a new filename (e.g., `dataset_5000.csv 1 7`).
3. Reopen `radix_sort_step.cpp` in Code::Blocks.
4. Click **Build and Run** again.

**Alternative:** Create multiple config files (e.g., `config_1000.txt`, `config_5000.txt`) and rename the one you want to `config.txt` before running.

---

## Team Collaboration Workflow

### Each member should:

1. **Create their own Code::Blocks project** inside their assigned folder

2. **Keep their own datasets** – copy the required CSV files into their local folder when testing.

3. **Commit and push** only their `.cpp` files to GitHub (not CSV files or executables).
