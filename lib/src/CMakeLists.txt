add_library(serene_updater
  SHARED
    serene_updater.cpp
  )
target_include_directories(serene_updater
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    )