CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(itkBinShirnkDoc NONE)

INCLUDE(UseLATEX.cmake)

set(src_files
  )
file(COPY ${src_files} DESTINATION ${CMAKE_BINARY_DIR})

ADD_LATEX_DOCUMENT(BinShrink.tex
  IMAGE_DIRS images
  BIBFILES BinShrink.bib
  DEPENDS ${src_files}
  DEFAULT_PDF
  )
