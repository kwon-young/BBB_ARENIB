
CXX=g++
DEBUG=yes
STATIC=yes

CIBLE=simu
EXE=$(CIBLE)
SRC_DIR=src/$(CIBLE)
OBJ_DIR=build
INC_DIR=include/$(CIBLE)
DBG_DIR=debug
REL_DIR=release

SRC=$(wildcard $(SRC_DIR)/*.cpp) 
INC=$(wildcard $(INC_DIR)/*.hpp)
OBJ=$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) build/main.o

ifeq ($(DEBUG), yes)
  EXEC=$(EXE)
#  EXEC=$(DBG_DIR)/$(EXE)
  CXXFLAGS= -W -Wall -I$(INC_DIR) -g
ifeq ($(STATIC), yes)
  LDFLAGS= -L"libwin32" -D SFML_STATIC=1 -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d
else
  LDFLAGS= -L"libwin32" -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
endif
else
  EXEC=$(EXE)
#  EXEC=$(REL_DIR)/$(EXE)
  CXXFLAGS= -W -Wall -I$(INC_DIR)
ifeq ($(STATIC), yes)
  LDFLAGS= -L"libwin32" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s 
else
  LDFLAGS= -L"libwin32" -lsfml-graphics -lsfml-window -lsfml-system
endif
endif

all:$(EXEC)
ifeq ($(DEBUG), yes)
	@echo Generation en mode debug
else
	@echo Generation en mode release
endif


build/main.o : src/main.cpp $(INC)
	@echo Compilation main.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

build/%.o: $(SRC_DIR)/%.cpp $(INC)
	@echo Compilation C++ $< to $@
	g++  -c $< -o $@ $(CXXFLAGS)

$(EXEC):$(OBJ)
	@echo linkage allo $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

.PHONY : clean run

run:
	$(EXEC)

clean:
	rm -rf $(OBJ_DIR)/*.o */*.exe *~ */*~
