include(FetchContent)

if(PARSER_BUILD_TESTS)
  FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929 # release-1.11.0
  )
  FetchContent_MakeAvailable(gtest)
endif() # PARSER_BUILD_TESTS
