add_library(serene_updater
  SHARED
    serene_updater.cpp
  )
target_link_libraries(serene_updater curl)
target_include_directories(serene_updater
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    )