
CXX=g++
DEBUG=yes
STATIC=yes

CIBLE=simu
EXE=$(CIBLE)
SRC_DIR=src
SRC_DIR_CIBLE=$(SRC_DIR)/$(CIBLE)
OBJ_DIR=build
INC_DIR=include
INC_DIR_CIBLE=$(INC_DIR)/$(CIBLE)
DBG_DIR=debug
REL_DIR=release

SRC=$(wildcard $(SRC_DIR)/*.cpp) 
SRC_CIBLE=$(wildcard $(SRC_DIR_CIBLE)/*.cpp) 
INC=$(wildcard $(INC_DIR)/*.hpp) 
INC_CIBLE=$(wildcard $(INC_DIR_CIBLE)/*.hpp)
OBJ=$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ_CIBLE=$(SRC_CIBLE:$(SRC_DIR_CIBLE)/%.cpp=$(OBJ_DIR)/%.o)

ifeq ($(DEBUG), yes)
  EXEC=$(EXE)
  CXXFLAGS= -W -Wall -I$(INC_DIR) -I$(INC_DIR_CIBLE) -g -std=c++0x 
ifeq ($(STATIC), yes)
  ifeq ($(CIBLE), simu)
    LDFLAGS= -L"libwin32" -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d
	 CXXFLAGS+= -DSIMULATION
  else
    LDFLAGS= 
  endif
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


build/%.o: $(SRC_DIR_CIBLE)/%.cpp $(INC_CIBLE) $(INC)
	@echo Compilation C++ $< to $@
	g++  -c $< -o $@ $(CXXFLAGS)

build/%.o: $(SRC_DIR)/%.cpp $(INC) $(INC_CIBLE)
	@echo Compilation C++ $< to $@
	g++  -c $< -o $@ $(CXXFLAGS)

$(EXEC):$(OBJ) $(OBJ_CIBLE)
	@echo -----LINKAGE-----
	$(CXX) -o $@ $(OBJ) $(OBJ_CIBLE) $(LDFLAGS)

.PHONY : clean run

run:
	$(EXEC)

clean:
	rm -rf $(OBJ_DIR)/*.o *.exe *~ */*~ $(CIBLE)
