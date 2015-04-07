# Author: ZHONGYANG CANZENG


# NetID: zhongyang jaspardzc

# Date: 13 Nov 2014


set( CMAKE_CXX_FLAGS "-Wall -g -std=c++0x" )



file( GLOB SRCS *.cpp *.h )



add_executable( hlsyn ${SRCS} )

