## CPP09 / ex00 – Bitcoin Exchange

The goal of this project is to **calculate the value in USD of a Bitcoin portfolio** using a historical exchange rate database.


### 🧠 Technical Skills
- C++98
- File parsing with std::ifstream
- Input/output using iostream and stringstream
- Data storage and lookup with std::map
- Error handling and input validation
- Date comparison and nearest-value search

### ⚙️ Compilation in bash

make
./btc input.csv





## 🗂️ Project Structure
.
├── Makefile           # Build rules for the project
├── main.cpp           # Entry point: reads input, handles output
├── BitcoinExchange.cpp # Core logic for data parsing and value computation
├── BitcoinExchange.hpp # Class definition and helper function prototypes
├── data.csv           # Bitcoin exchange rate database
└── input.csv          # Example input file





## 🧠 Project Overview

- Read a database containing Bitcoin exchange rates.  
- Read an input file containing dates and values.  
- For each entry, display the corresponding value in USD according to the closest known exchange rate.

---