/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   dry_wet_knob_png;
    const int            dry_wet_knob_pngSize = 671917;

    extern const char*   onoffledoff_png;
    const int            onoffledoff_pngSize = 107064;

    extern const char*   onoffledon_png;
    const int            onoffledon_pngSize = 106405;

    extern const char*   onoffledstrip_png;
    const int            onoffledstrip_pngSize = 88590;

    extern const char*   onoffswitchdown_png;
    const int            onoffswitchdown_pngSize = 136438;

    extern const char*   onoffswitchstrip_png;
    const int            onoffswitchstrip_pngSize = 214674;

    extern const char*   onoffswitchup_png;
    const int            onoffswitchup_pngSize = 136143;

    extern const char*   pedal_full_res_2k_cropped_scaled_png;
    const int            pedal_full_res_2k_cropped_scaled_pngSize = 1438549;

    extern const char*   speedknobstrip_png;
    const int            speedknobstrip_pngSize = 2339836;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 9;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
