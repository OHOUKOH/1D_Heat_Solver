# Compiler and flags
CXX=g++
CXXFLAGS=-O2 -Wall -std=c++11

# Directories
INCLUDE_DIR=./Include
SRC_DIR=./Src
SETUP_DIR=./Setup
DATA_DIR=./Output
BIN_DIR=./Bin

# Source and headers
SRC=$(SRC_DIR)/main.cpp
HEADERS=$(INCLUDE_DIR)/*.hh
EXEC=$(BIN_DIR)/heat_solver.exe

all: run_python

$(EXEC): $(SRC)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $(EXEC) $(SRC)

run_cpp: $(EXEC)
	$(EXEC)

run_python: run_cpp
	python python.py

clean:
	del /Q $(EXEC)
	del /Q $(DATA_DIR)\output_*.dat
