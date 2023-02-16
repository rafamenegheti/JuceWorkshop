cmake_minimum_required(VERSION 3.15)

# Set project name and version
project(JUCE_INTRODUCTION VERSION 1.0.0)

# Enable nice source grouping for IDE projects
set_property(GLOBAL PROPERTY USE_FOLDERS YES)
option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Group module sources in IDE projects" ON)

# Include JUCE functionality
add_subdirectory(JUCE)

# Add individual projects
foreach(dir IN ITEMS workspace 01 02 03 04 05 06 07 08 09)
    string(SUBSTRING "${dir}" 0 2 trimmed_dir)

    # Create a plugin target with a name and code based on the directory name
    juce_add_plugin("${dir}_SimpleDelay"
        PLUGIN_MANUFACTURER_CODE    "Demo"
        PLUGIN_CODE                 "Sd${trimmed_dir}"
        FORMATS                     AU VST3 Standalone
        PRODUCT_NAME                "Simple Delay")

    # Create a JuceHeader.h for the plugin target
    juce_generate_juce_header("${dir}_SimpleDelay")

    # Add source files to the target. All files that you wish to build into
    # the plugin must be listed in the target_sources call.
    target_sources("${dir}_SimpleDelay"
        PRIVATE
            ${dir}/Source/PluginEditor.cpp         ${dir}/Source/PluginEditor.h
            ${dir}/Source/PluginProcessor.cpp      ${dir}/Source/PluginProcessor.h)

    # Set JUCE options. We'll just set some common defaults for now...
    target_compile_definitions("${dir}_SimpleDelay"
        PRIVATE
            JUCE_WEB_BROWSER=0
            JUCE_USE_CURL=0
            JUCE_VST3_CAN_REPLACE_VST2=0)

    # Add JUCE code to our plugin.
    target_link_libraries("${dir}_SimpleDelay"
        PRIVATE
            juce::juce_audio_utils
        PUBLIC
            juce::juce_recommended_config_flags
            juce::juce_recommended_warning_flags)
endforeach()
