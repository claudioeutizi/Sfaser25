cmake_minimum_required(VERSION 3.15)
project(minimal_plugin VERSION 0.0.1)
add_subdirectory(C:/JUCE ./JUCE) 

juce_add_plugin(Face90

    COMPANY_NAME Supremo # Specify the name of the plugin's author
    IS_SYNTH TRUE # Is this a synth or an effect?
    NEEDS_MIDI_INPUT TRUE # Does the plugin need midi input?
    # NEEDS_MIDI_OUTPUT TRUE/FALSE # Does the plugin need midi output?
    # IS_MIDI_EFFECT TRUE/FALSE # Is this plugin a MIDI effect?
    NEEDS_MIDI_OUTPUT TRUE
                        # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE CSMA # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Face # A unique four-character plugin id with exactly one upper-case character
                    # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "Face90") # The name of the final executable, which can differ from the target name
    juce_generate_juce_header(Face90)

target_sources(Face90
PRIVATE
src/PluginEditor.cpp
src/PluginProcessor.cpp)

target_compile_definitions(Face90
PUBLIC #
JUCE_ALSA=1
JUCE_DIRECTSOUND=1
JUCE_DISABLE_CAUTIOUS_PARAMETER_ID_CHECKING=1
JUCE_USE_OGGVORBIS=1
JUCE_WEB_BROWSER=0 # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
JUCE_USE_CURL=0 # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(Face90
PRIVATE
juce::juce_audio_utils
PUBLIC
juce::juce_recommended_config_flags
juce::juce_recommended_lto_flags
juce::juce_recommended_warning_flags)