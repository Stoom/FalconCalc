include_directories(.)

set(LIB_SOURCE falcon_calc.c)
set(HEADERS falcon_calc.h)

add_library(lib_falcon ${LIB_SOURCE} ${HEADERS})
