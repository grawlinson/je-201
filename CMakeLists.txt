cmake_minimum_required(VERSION 3.22)

# split up cmake into easier-to-parse snippets
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# set some sane CMake specific defaults
include(defaults)
# set some platform specific hacks/fixes (Linux/macOS/Windows)
include(platform-specific)

# JUCE & dependencies
add_subdirectory(libs/JUCE)
add_subdirectory(libs/clap-juce-extensions)
juce_add_module(libs/foleys_gui_magic/modules/foleys_gui_magic)

# RE-201 model
add_subdirectory(src/model)

# metadata
set(COMPANY_NAME "grawlinson")
set(PROJECT_NAME "JE-201")
set(PLUGIN_ID "com.${COMPANY_NAME}.${PROJECT_NAME}")
project(${PROJECT_NAME} VERSION 1.0.1 LANGUAGES CXX)

# setup JUCE
juce_add_plugin(${PROJECT_NAME}
  COMPANY_NAME ${COMPANY_NAME}
  COMPANY_WEBSITE "https://github.com/grawlinson/je201"
  BUNDLE_ID ${PLUGIN_ID}
  DESCRIPTION "Digital model of the Roland RE-201"
  PLUGIN_MANUFACTURER_CODE GRAW
  PLUGIN_CODE J201
  FORMATS Standalone VST3 AU AUv3 LV2
  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT FALSE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE
  EDITOR_WANTS_KEYBOARD_FOCUS FALSE
  COPY_PLUGIN_AFTER_BUILD FALSE
  VST3_CATEGORIES Fx Delay Reverb
  AU_MAIN_TYPE kAudioUnitType_Effect
)

# setup CLAP plugin
clap_juce_extensions_plugin(TARGET ${PROJECT_NAME}
  CLAP_ID ${PLUGIN_ID}
  CLAP_FEATURES "audio-effect" "delay" "reverb"
)

juce_add_binary_data(${PROJECT_NAME}_data
  SOURCES resources/magic.xml
)

target_sources(${PROJECT_NAME} PRIVATE
  src/PluginProcessor.cpp
  src/PluginProcessor.h
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    RE201Model
    ${PROJECT_NAME}_data
    juce_audio_basics
    juce_audio_devices
    juce_audio_formats
    juce_audio_plugin_client
    juce_audio_processors
    juce_audio_utils
    juce_core
    juce_data_structures
    juce_dsp
    juce_events
    juce_graphics
    juce_gui_basics
    juce_gui_extra
    juce_cryptography
    foleys_gui_magic
  PUBLIC
    juce::juce_recommended_warning_flags
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
)

target_compile_definitions(${PROJECT_NAME}
  PUBLIC
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0
  JUCE_VST3_CAN_REPLACE_VST2=0
  JUCE_DISPLAY_SPLASH_SCREEN=0
  JUCE_REPORT_APP_USAGE=0
  FOLEYS_SHOW_GUI_EDITOR_PALLETTE=0
  FOLEYS_ENABLE_BINARY_DATA=1
  FOLEYS_SAVE_EDITED_GUI_IN_PLUGIN_STATE=0
)
