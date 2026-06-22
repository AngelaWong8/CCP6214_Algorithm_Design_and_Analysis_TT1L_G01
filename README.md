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
- **Hash Table Search** – implements search with separate chaining collision resolution, measures best/average/worst case times.

---

## How to run using Code::Blocks

### Step 1: Download / Clone the repository

- Download the ZIP from GitHub and extract it to your computer.
- Or use GitHub Desktop to clone the repository.

### Step 2: Open each `.cpp` file in Code::Blocks

Each team member will work on their own `.cpp` files. **Do not put all files in one project** and keep them separate for clarity.

---

### Remarks For Radix Sort:

1. Open Code::Blocks.
2. **File → Open** → navigate to `src/radix_sort_step.cpp`
3. The file will open in the editor.
4. Click **Build and Run** (or press F9).

**What happens when you click Build and Run:**
- The program looks for a file named `config.txt` in the **same folder as the `.cpp` file**.
- The program reads that `config.txt` file (lines starting with `#` are ignored, the first non‑comment line contains the parameters).

### **To test a dataset:**
1. Remove the `#` from the beginning of the line you want to use.
2. Make sure **only ONE line is uncommented**.
3. Save the file.

**Example** – to test `dataset_1000.csv` with rows 1-7 (for `radix_sort_step.cpp`):
dataset_1000.csv 1 7

**Example** – to test full sort on `dataset_5000.csv` (for `radix_sort.cpp`):
dataset_5000.csv

---

### Step 3: Build and Run

1. In Code::Blocks, click **Build → Build** (Ctrl+F9) to compile.
2. Click **Build → Run** (Ctrl+F10) to execute.
3. The output file will be created in the same folder.

### Step 4: Test another dataset

1. Comment out the previous line by adding `#` at the beginning.
2. Uncomment a different line.
3. Save `config.txt`.
4. Run again (Ctrl+F10) – no need to rebuild unless you changed the code.

### Step 5: Where to find outputs

| Program | Output file |
|---------|-------------|
| `radix_sort_step.cpp` | `dataset_<size>_radix_sorted_step_<start>_<end>.txt` |
| `radix_sort.cpp` | `dataset_<size>.radix_sorted_dataset_<size>.csv` + `radix_sort_time_<size>.txt` |

All output files are saved in the **same folder as your `.cpp` file**.

### Important Notes

- **Only uncomment ONE line at a time** – the program uses the first non‑commented line it finds.
- Make sure your CSV datasets are in the **same folder** as the `.cpp` file, or use a relative path like `../datasets/dataset_1000.csv`.

---

## Team Collaboration Workflow

### Each member should:

1. **Create their own Code::Blocks project** inside their assigned folder

2. **Keep their own datasets** – copy the required CSV files into their local folder when testing.

3. **Commit and push** only their `.cpp` files to GitHub (not CSV files or executables).

---

### Remarks for Hash Table Search
To run the hash_table_search codes, please ensure the datasets below is present in the same file as the hash_table_search.cpp for a smooth run, as demonstrated below:
```text
hash table/
│
├── hash_table_search.cpp     # Main source implementation
├── dataset_1000000.csv          # Generated database input arrays
├── dataset_5000000.csv
├── dataset_10000000.csv
├── dataset_15000000.csv
├── dataset_20000000.csv
├── dataset_25000000.csv
├── dataset_30000000.csv
├── dataset_35000000.csv
└── dataset_40000000.csv
└── dataset_50000000.csv
