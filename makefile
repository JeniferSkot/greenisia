NAME=game
VERSION_MAJOR=0
VERSION_MINOR=0

CXX=g++
LDXX=ldd

CONFIG = \
	-D QUICK_QUIT \
	-D DEBUG_GRID \
	-D USE_ESDF \
	-D LEVEL_EDITOR \
	#

__CXXFLAGS=-Og -g -std=c++17 \
	-Wall -Wextra -pedantic \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	# -pthread \
	#

IDIR=src
SDIR=src
BDIR=bin
ODIR=obj
DDIR=dep
ASSETS_DIR=assets

_CXXFLAGS = ${__CXXFLAGS} ${CONFIG} -I${IDIR} -I${ODIR}/${IDIR} ${CXXFLAGS}
SRC = $(shell find ${SDIR} -type f -name '*.cpp' -o -name ".backup" -prune -type f)
OBJ = $(patsubst ${SDIR}/%.cpp,${ODIR}/%.o,${SRC})
DEP = $(patsubst ${SDIR}/%.cpp,${DDIR}/%.dep,${SRC})
ASSETS = $(shell find ${ASSETS_DIR} -type f -not -name "*.map" -o -name ".backup" -prune -type f)
#NEW_ASSETS = $(patsubst %,${BDIR}/%, ${ASSETS})


ifndef VERBOSE
.SILENT:
endif

build: depend ${SRC} ${BDIR}/${NAME} assets # ctags

${DEP}: ${DDIR}/%.dep: ${SDIR}/%.cpp
	mkdir -p ${DDIR}
	echo "Calculating dependencies for $<"
	mkdir -p $$(dirname $@)
	${CXX} ${_CXXFLAGS} $< -MM -MP -MT $(patsubst ${SDIR}/%.cpp,${ODIR}/%.o,$<) > $@

depend: ${DEP}
include ${DEP}

${OBJ}: ${ODIR}/%.o: ${SDIR}/%.cpp makefile
	# mkdir -p ${ODIR}
	echo "Compiling $@"
	mkdir -p $$(dirname $@)
	${CXX} -c -o $@ $< ${_CXXFLAGS}

${BDIR}/${NAME}: ${OBJ}
	mkdir -p ${BDIR}
	echo "Linking ${NAME}"
	$(CXX) -o $@ ${OBJ} ${_CXXFLAGS}

clean:
	echo "Cleaning build files"
	rm -r ${ODIR} ${DDIR}
	# rm tags

run: build
	echo "Running ${NAME}"
	cd ${BDIR} && ./${NAME} $(ARGS)
	if [ -f "${BDIR}/${ASSETS_DIR}/post_run.sh" ]; then \
		echo "Executing post_run.sh"; \
		cd ${BDIR} && ./${ASSETS_DIR}/post_run.sh; \
	fi

ctags: ${SRC}
	echo "Generating ctags"
	ctags -R ${IDIR} ${SDIR}

assets: ${BDIR}/${ASSETS_DIR}/STAMP

${BDIR}/${ASSETS_DIR}/STAMP: ${ASSETS}
	if [ -d "${BDIR}/${ASSETS_DIR}" ]; then \
		rm -r "${BDIR}/${ASSETS_DIR}"; \
	fi
	mkdir -p "${BDIR}"
	cp -r "${ASSETS_DIR}" "${BDIR}/${ASSETS_DIR}"
	echo "Preparing assets"
	cd ${BDIR}/${ASSETS_DIR}
	if [ -f "${BDIR}/${ASSETS_DIR}/prepare.sh" ]; then \
		${BDIR}/${ASSETS_DIR}/prepare.sh; \
	fi
	touch $@


CFG_FILES = $(shell find ${IDIR} -type f -name '*.hpp.in' -o -name ".backup" -prune -type f)
CFG_PARSED = $(patsubst ${IDIR}/%.hpp.in,${ODIR}/${IDIR}/%.hpp,${CFG_FILES})

config: ${CFG_PARSED}

${CFG_PARSED}: ${ODIR}/${IDIR}/%.hpp : ${IDIR}/%.hpp.in
	mkdir -p ${ODIR}/${IDIR}
	mkdir -p $$(dirname $@)
	echo "Creating empty $@"
	touch $@ -d "$$(stat -c %y $<)"

