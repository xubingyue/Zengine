# Locate SDL_net library
#
# This module defines: 
#
# ::
#
#   SDL_NET_LIBRARY, the name of the library to link against
#   SDL_NET_INCLUDE_DIR, where to find the headers
#   SDL_NET_FOUND, if false, do not try to link against
#   SDL_NET_VERSION_STRING - human-readable string containing the version of SDL_net
#
#
#
# For backward compatiblity the following variables are also set:
#
# ::
#
#   SDLNET_LIBRARY (same value as SDL_NET_LIBRARY)
#   SDLNET_INCLUDE_DIR (same value as SDL_NET_INCLUDE_DIR)
#   SDLNET_FOUND (same value as SDL_NET_FOUND)
#
#
#
# $SDLDIR is an environment variable that would correspond to the
# ./configure --prefix=$SDLDIR used in building SDL.
#
# Created by Eric Wing, modified by Chris Zehr.  This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
# Copyright 2012 Benjamin Eikel
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

message("Running FindSDL2_NET.cmake ...")

find_path(SDL2_NET_INCLUDE_DIR SDL_net.h
  HINTS
    ENV SDL2NETDIR
    ENV SDL2DIR
  PATH_SUFFIXES SDL2
                # path suffixes to search inside ENV{SDLDIR}
                include/SDL2 include
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

find_library(SDL2_NET_LIBRARY
  NAMES SDL2_net
  HINTS
    ENV SDL2NETDIR
    ENV SDL2DIR
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
)

if(SDL2_NET_INCLUDE_DIR AND EXISTS "${SDL2_NET_INCLUDE_DIR}/SDL_net.h")
  file(STRINGS "${SDL2_NET_INCLUDE_DIR}/SDL_net.h" SDL_NET_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_NET_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_NET_INCLUDE_DIR}/SDL_net.h" SDL2_NET_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL2_NET_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_NET_INCLUDE_DIR}/SDL_net.h" SDL2_NET_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL2_NET_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL2_NET_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_NET_VERSION_MAJOR "${SDL2_NET_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL2_NET_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_NET_VERSION_MINOR "${SDL2_NET_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL2_NET_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_NET_VERSION_PATCH "${SDL2_NET_VERSION_PATCH_LINE}")
  set(SDL2_NET_VERSION_STRING ${SDL2_NET_VERSION_MAJOR}.${SDL2_NET_VERSION_MINOR}.${SDL2_NET_VERSION_PATCH})
  unset(SDL2_NET_VERSION_MAJOR_LINE)
  unset(SDL2_NET_VERSION_MINOR_LINE)
  unset(SDL2_NET_VERSION_PATCH_LINE)
  unset(SDL2_NET_VERSION_MAJOR)
  unset(SDL2_NET_VERSION_MINOR)
  unset(SDL2_NET_VERSION_PATCH)
endif()

set(SDL2_NET_LIBRARIES ${SDL2_NET_LIBRARY})
set(SDL2_NET_INCLUDE_DIRS ${SDL2_NET_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_net
                                  REQUIRED_VARS SDL2_NET_LIBRARIES SDL2_NET_INCLUDE_DIRS
                                  VERSION_VAR SDL2_NET_VERSION_STRING)

# for backward compatiblity
#set(SDLNET_LIBRARY ${SDL_NET_LIBRARY})
#set(SDLNET_INCLUDE_DIR ${SDL_NET_INCLUDE_DIR})
#set(SDLNET_FOUND ${SDL_NET_FOUND})

mark_as_advanced(SDL2_NET_LIBRARY SDL2_NET_INCLUDE_DIR)

message("FindSDL2_NET.cmake finished.")