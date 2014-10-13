
CXX=g++
DEBUG=yes
EXE=i2c_test

CIBLE=simu
SRC_DIR=src/$(CIBLE)
OBJ_DIR=build
INC_DIR=include/$(CIBLE)
DBG_DIR=debug
REL_DIR=release

SRC=$(wildcard $(SRC_DIR)/*.cpp)
INC=$(wildcard $(INC_DIR)/*.hpp)
OBJ=$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

ifeq ($(DEBUG), yes)
  EXEC=$(EXE)
#  EXEC=$(DBG_DIR)/$(EXE)
  CXXFLAGS= -W -Wall -I"include" -g
  LDFLAGS= -L"libwin32" -lsfml-graphics -lsfml-window -lsfml-system 
else
  EXEC=$(EXE)
#  EXEC=$(REL_DIR)/$(EXE)
  CXXFLAGS= -W -Wall -I"include"
  LDFLAGS= -L"libwin32" -lsfml-graphics -lsfml-window -lsfml-system 
endif

all:$(EXEC)
ifeq ($(DEBUG), yes)
	@echo Generation en mode debug
else
	@echo Generation en mode release
endif


build/%.o: $(SRC_DIR)/%.cpp $(INC)
	@echo Compilation C++ $< to $@
	g++  -c $< -o $@ $(CXXFLAGS)

$(EXEC):$(OBJ)
	@echo linkage
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

.PHONY : clean run

run:
	$(EXEC)

clean:
	rm -rf $(OBJ_DIR)/*.o */*.exe *~ */*~ $(EXEC)
