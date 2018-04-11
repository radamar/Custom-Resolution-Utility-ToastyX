# Custom Resolution Utility (CRU)
Custom Resolution Utility (CRU) allows custom resolutions to be defined for both AMD/ATI and NVIDIA GPUs by creating EDID overrides directly in the registry without dealing with .inf files.

Requirements:

    Windows Vista or later (Windows XP does not support EDID overrides)
    AMD/ATI or NVIDIA GPU with appropriate driver installed (Microsoft Basic Display Adapter driver does not support EDID overrides)
    Some Intel GPUs and laptops with switchable graphics are supported with one of these drivers:
        6th/7th generation (Skylake/Kaby Lake): Intel Graphics Driver for Windows [15.45]
        4th/5th generation (Haswell/Broadwell): Intel Graphics Driver for Windows [15.40] (Previous: Intel Graphics Test Driver)
        4th generation (Haswell) for Windows 7/8.1: Intel Graphics Driver for Windows 7/8.1 [15.36]

Before doing anything, familiarize yourself with getting into safe mode in case you can't see the screen. If you don't have a recovery drive, press and hold the power button to shut off the computer while Windows is booting. Doing this twice should give you recovery options that you can use to get into safe mode: Troubleshoot > Advanced options > Startup Settings > Restart

Getting started:

    Run CRU.exe.
    Choose a monitor from the drop-down list.
        "(active)" means the monitor is connected and recognized by the graphics driver.
        "*" means changes were made and an override was saved in the registry.
    Edit the configuration as desired. Please read the sections below for more information.
    Repeat steps 2-3 for other monitors if required.
        The "Copy" and "Paste" buttons at the top can be used to copy the resolutions, extension blocks, and range limits if included. It will not copy the name or serial number, but it will copy the inclusion of these items using the monitor's own information. Import follows the same logic unless "Import complete EDID" is selected.
    Click "OK" to save the changes.
    Run restart.exe to restart the graphics driver.
        If the display does not return after 15 seconds, press F8 for recovery mode. This will temporarily unload all the EDID overrides without deleting them. Restart the driver again to reload any changes.
    Set the resolution in the Windows display settings. To set the refresh rate:
        Windows 10: right-click on the desktop > Display settings > Advanced display settings > Display adapter properties > Monitor tab
        Windows Vista/7/8/8.1: right-click on the desktop > Screen resolution > Advanced settings > Monitor tab

To reset a display back to the default configuration, use the "Delete" button at the top to delete the override from the registry and reboot. To reset all displays, run reset-all.exe and reboot. This can be done in safe mode if necessary.

Detailed resolutions:

    Detailed resolutions are the preferred way to add custom resolutions. More detailed resolutions can be added using extension blocks.
    The first detailed resolution is considered the preferred or native resolution. All other resolutions can be removed if they are not needed. The graphics driver will automatically add some common lower resolutions as scaled resolutions.
    Use the timing options to help fill in the values:
        "Manual" allows the timing parameters to be set manually. The dialog will always open in this mode.
        "Automatic - LCD standard" uses standard timing parameters commonly used with LCD monitors and HDTVs.
        "Automatic - LCD native" uses standard timing parameters for the native refresh rate. This may help when trying higher refresh rates.
        "Automatic - LCD reduced" adjusts the timing parameters for some resolutions to reduce the pixel clock. This may help when trying higher refresh rates.
        "Automatic - CRT standard" uses timing parameters compatible with CRT monitors.
    Pay attention to pixel clock limits:
        Single-link DVI is limited to 165 MHz and dual-link DVI is limited to 330 MHz unless the graphics driver is patched:
            AMD/ATI Pixel Clock Patcher
            NVIDIA Pixel Clock Patcher
        HDMI is treated as single-link DVI unless an HDMI support data block is defined in the first extension block.
        HDMI limits depend on the graphics card. AMD 7000-series and newer cards support up to 297 MHz. Older cards are limited to 165 MHz unless the driver is patched.
        AMD/ATI's driver also listens to the TMDS clock limit in the HDMI support data block. Make sure to override this and set it to 340 MHz.
        Passive DisplayPort to HDMI adapters are limited to 165 MHz unless the driver is patched.
        These DisplayPort to HDMI adapters support up to 300 MHz pixel clock without patching the driver:
            Accell B086B-003B UltraAV DisplayPort 1.1 to HDMI 1.4 Active Adapter
            Accell B086B-008B UltraAV Mini DisplayPort 1.1 to HDMI 1.4 Active Adapter
            Accell B086B-006B UltraAV DisplayPort 1.2 to HDMI 1.4 Active Adapter
            Accell B086B-007B UltraAV Mini DisplayPort 1.2 to HDMI 1.4 Active Adapter

Standard resolutions:

    Standard resolutions are mostly useful for CRT monitors and for adding lower resolutions with LCD monitors. Do not add the native resolution as a standard resolution.
    AMD/ATI only supports the resolutions in the drop-down list. Other resolutions will be ignored by the driver. These will be listed in gray.
    NVIDIA does not support more than 8 standard resolutions.
    Standard resolutions are limited to 60-123 Hz. Use detailed resolutions to add other refresh rates.

Extension blocks:

    CRU can now read extension blocks from connected monitors with AMD/ATI and NVIDIA. Workarounds are no longer required for NVIDIA. CRU will automatically add a blank extension block in the registry and .inf files if necessary to work around NVIDIA driver issues.
    Extension block types:
        Use CEA-861 unless you need more standard resolutions. Note: NVIDIA requires at least 2 bytes left for data blocks or the driver may crash or ignore the override.
        Use VTB-EXT to add more standard resolutions. Note: AMD/ATI only supports one VTB-EXT block, and it must be the last block in the list.
        Default extension blocks are provided for compatibility with existing overrides. Avoid using this option. To read extension blocks from connected monitors with AMD/ATI and NVIDIA, reset the display first. Extension blocks that can't be read will appear as default extension blocks.
    To manually add HDMI support, add an HDMI support data block, or import one of these extension block files:
        hdmi.dat (HDMI support only)
        hdmi-audio.dat (HDMI support with audio)
        hdmi-bitstream.dat (HDMI support with bitstreaming for A/V receiver)
    To manually add audio support, add an audio formats data block and add the LPCM audio format, or import one of these extension block files:
        hdmi-audio.dat (HDMI audio)
        hdmi-bitstream.dat (HDMI bitstreaming for A/V receiver)
        displayport-audio.dat (DisplayPort audio)

Editing FreeSync ranges:

    For DisplayPort monitors, use the "Edit..." button at the top to edit the range limits, and make sure "Include if slot available" is checked.
    For HDMI monitors, edit the FreeSync data block in the first extension block.

Notes:

    CRU adds monitor resolutions, not scaled resolutions. Lower resolutions will be scaled up if GPU scaling is enabled, but higher resolutions won't be scaled down by the GPU. Higher resolutions will only work if the monitor can handle them.
    The video card will not reduce clock speeds when idle if the vertical blanking/total is too low. Horizontal values can still be reduced if necessary.
        AMD/ATI cards require the "LCD standard" vertical blanking/total to reduce the memory clock when idle.
        NVIDIA cards can handle some lower values depending on the resolution and refresh rate.
    AMD/ATI cards have a design limitation that causes video acceleration to scramble the screen if the vertical blanking/total is below standard with the video card's memory overclocked or with multiple monitors connected. Skype is known to trigger this problem. Either don't overclock the video card's memory, or use the "LCD standard" vertical blanking/total.

Changes in 1.3.99-p1:

    Added support for DisplayID extension blocks:
        Added support for "Type I" detailed resolutions.
        Added support for tiled display topology data blocks.
    Display properties: added support for ID serial number in EDID header
    Detailed resolutions: added "Automatic - Old standard" timing option for GTF
    TV resolutions: added new resolutions from CTA-861-G (requires driver support)
    Colorimetry: added DCI-P3 standard from CTA-861-G

Changes in 1.3.1:

    Fixed .inf export for Windows 10 Creators Update
    Detailed resolutions: use CEA-861 timing parameters for 3840x2160 @ 60 Hz with "LCD standard" (use "LCD reduced" for old values)
    Detailed resolutions: allow 0 back porch
    TV resolutions: disable "Native format" for resolutions that don't support this option
    Do not add blank extension block if no extension blocks exist by default
    Allow invalid but possible product IDs when editing display properties
    Fixed '&' character in monitor name and serial number not displaying correctly in detailed resolutions list box
    Improved row spacing between UI elements with higher DPI settings

Changes in 1.3:

    Added support for reading extension blocks from connected monitors with AMD/ATI and NVIDIA
    Automatically add blank extension block in registry and exported .inf files to work around NVIDIA driver issues
    Added support for multiple extension blocks
    Added support for importing other types of extension blocks
    Added support for VTB-EXT extension blocks (detailed/standard resolutions only)
    Changed default TMDS clock to 340 MHz for new HDMI data blocks
    Added support for HDMI 2.0 data blocks
    Added support for HDMI FreeSync data blocks
    Added BT.2020 formats in colorimetry data blocks
    Added text file export (outputs hex values)
    Improved UI scaling with higher DPI settings
    restart.exe/restart64.exe: fix Start menu, search box, and Radeon Settings not responding after restarting

Changes in 1.2.6:

    Fixed a bug affecting non-PnP monitors since 1.2.3 (invalid EDID version with new overrides)

Changes in 1.2.5:

    Include range limits by default if min/max horizontal values match and certain conditions are met (for FreeSync monitors)
    restart.exe/restart64.exe: restart Radeon Settings (cnext.exe)

Changes in 1.2.4:

    Made range limits compatible with FreeSync monitors

Changes in 1.2.3:

    Added basic support for range limits and serial number descriptors (use the "Edit..." button at the top)
    Show included descriptors in the detailed resolution list
    Added "Import complete EDID" option

Changes in 1.2.2:

    Detailed resolutions: added "LCD reduced" timing parameters for 2560x1440 @ 144 Hz and higher resolutions
    Extension block: added support for colorimetry and video capability data blocks
    Redesigned icon to scale better with Windows 10's broken taskbar scaling
    Fixed how disabled buttons appear with Windows 10

Changes in 1.2.1:

    Detailed resolutions: added "LCD native" option
    TV resolutions: added support for 4:2:0 resolutions
    HDMI support: added support for HDMI resolutions, latency information, and supported content types
    Fixed access violation in comctl32.dll message with higher DPI settings
    Fixed layout issues with higher DPI settings and enabled DPI awareness
    restart.exe/restart64.exe: implemented a better recovery mode

Changes in 1.2:

    Added custom extension block editing
    Added support for more than 8 standard resolutions (AMD/ATI only)
    Added support for other standard resolutions (NVIDIA only)
    Updated reset-all.exe to reset Windows resolution settings
    Include new version of restart.exe/restart64.exe

Changes in 1.1.2:

    Fixed HDMI audio not working with older AMD/ATI GPUs

Changes in 1.1.1:

    Fixed monitors with invalid signal type information not working with AMD/ATI GPUs
    Added "LCD standard" timing parameters for 3840x2160 @ 30 Hz and 1366x768 @ 60 Hz (use "LCD reduced" for old values)
    Automatically enable extension block when importing extension block files
    Show number of slots left

Changes in 1.1:

    Import extension block from files (editing coming later)
    Automatically fill in likely native resolution when adding a detailed resolution
    Disable controls when deleting a monitor

Changes in 1.0.1:

    Fixed .inf export
    Added support for non-PnP monitors
    Changed monitor list sorting

Older versions:

Using older versions is not recommended. Newer versions fix problems and add features. Please report any issues with newer versions that did not exist with older versions. Make sure to run reset-all.exe when testing different versions.

# Message from ToastyX
I need your help. Due to health issues and financial reasons, I'm having a hard time functioning. I have released all the source code in case I can't continue development. I would like to continue providing updates and work on new programs, but I need your support. If you can help, please join my Patreon: https://www.patreon.com/bePatron?c=1373167.
As an incentive, I've added a couple of goals:

    1000 patrons - CRU: Add basic support for DisplayID detailed resolutions. This is required to support resolutions greater than 4095x4095 and pixel clocks greater than 655.35 MHz. I have completed this and released it as CRU 1.4 Preview (1.3.99-p1) despite not meeting the goal.
    2000 patrons - Create a new program to force monitor resolutions using hotkeys. This will use new methods to change the available resolutions on the fly, making sure only the resolution you want is active.

Creating and maintaining software is a lot of work, and I have provided updates and support for free over the years. If everyone that used these programs donated $1 per month, I'd be able to work on new features and new ideas full time.
