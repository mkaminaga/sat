#!/bin/bash
# Author Mamoru Kaminaga
# Date 2017/09/08
# Shell script for release
# Copyright 2017 Mamoru Kaminaga

if [ "$1" = "" ]; then
  echo 'need args, 1->gcc, 2->cl'
  exit 1
fi

# Required: The latest version.
VERSION='v1.0.1'

# Output directory is created
OUTDIR="release"
mkdir -p ${OUTDIR}

if [ "$1" = "1" ]; then
  # Build test for Ubuntu.
  touch *.cc
  make
  if [ $? != 0 ]; then exit 1; fi

  touch *.cc
  make -f sat.mk
  if [ $? != 0 ]; then exit 1; fi

  # Output sub directory is created
  TARGET="${OUTDIR}/release_${VERSION}_ubuntu"
elif [ "$1" = "2" ]; then
  # Build test for Windows.
  touch *.cc
  nmake /f sat_windows.mk | iconv -f cp932 -t utf-8
  if [ $? != 0 ]; then exit 1; fi

  touch *.cc
  nmake /f makefile_windows.mk | iconv -f cp932 -t utf-8
  if [ $? != 0 ]; then exit 1; fi

  # Output sub directory is created
  TARGET="${OUTDIR}/release_${VERSION}_windows"
fi

mkdir -p ${TARGET}
rm -r ${TARGET}

mkdir -p ${TARGET}
cp *.md ${TARGET}  # descriptions
cp *.txt ${TARGET}  # descriptions
cp *.h ${TARGET}  # Header files
cp *.a ${TARGET}  # Library files for Ubuntu
cp *.lib ${TARGET}  # Library files for Windows

# Zip file is created.
zip -r ${TARGET}.zip ${TARGET}

exit 0
