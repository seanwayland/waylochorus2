cmake_minimum_required(VERSION 3.22)

include(FetchContent)

set(WAYLO2_SOURCE_DIR "" CACHE STRING "Path to Waylo repo source directory")

if ("${WAYLO2_SOURCE_DIR}" STREQUAL "")
    message(FATAL_ERROR "WAYLO2_SOURCE_DIR has not been set, use cmake -DWAYLO2_SOURCE_DIR=\"PathToWayloRepoSourceDir\"")
endif()

set(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY  git@github.com:juce-framework/JUCE.git
    GIT_TAG         8.0.4
    GIT_SHALLOW     ON
)

FetchContent_GetProperties(JUCE)
if (NOT juce_POPULATED)
    FetchContent_Populate(JUCE)
    add_subdirectory(${juce_SOURCE_DIR} ${juce_BINARY_DIR})
endif()

project(waylochorus2 VERSION 1.0)
juce_add_plugin(${PROJECT_NAME}
    PRODUCT_NAME                    "WayloChorus2"
    VERSION                         "1.1.0"
    BUNDLE_ID                       "com.waylo.waylo"
    PLUGIN_NAME                     "WayloChorus2"
    PLUGIN_CODE                     "Wch2"
    PLUGIN_MANUFACTURER_CODE        "Unk1"
    LV2URI                          "urn:waylo.waylo"

    IS_SYNTH                        False
    VST3_CATEGORIES                 Fx
    AU_MAIN_TYPE                    kAudioUnitType_Effect
    FORMATS                         Standalone VST3 LV2

    COPY_PLUGIN_AFTER_BUILD FALSE   FALSE
    NEEDS_CURL                      TRUE    # You might not need this
    NEEDS_WEB_BROWSER               FALSE   # Ineffective??
)

juce_generate_juce_header(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        ${WAYLO2_SOURCE_DIR}/Source/PluginEditor.cpp
        ${WAYLO2_SOURCE_DIR}/Source/PluginProcessor.cpp
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        "JUCE_WEB_BROWSER=0"
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${WAYLO2_SOURCE_DIR}/Source
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_devices
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
        juce::juce_recommended_lto_flags
)
