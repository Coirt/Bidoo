# Bidoo's plugins for [VCVRack](https://vcvrack.com)

<!-- Version and License Badges -->
![Version](https://img.shields.io/badge/version-0.6.19-green.svg?style=flat-square)
![License](https://img.shields.io/badge/license-BSD3-blue.svg?style=flat-square)
![Language](https://img.shields.io/badge/language-C++-yellow.svg?style=flat-square)

![pack](/images/pack.png?raw=true "pack")

## How to

You can find information on that plugins pack in the [wiki](https://github.com/sebastien-bouffier/Bidoo/wiki). When doing tests it happens that I record a video so you may find some ideas on how to use those modules [here](https://www.youtube.com/bidoo).

## Last changes

05/10/2018 => 0.6.19

*UPDATE* **dFUZE** as no shimmer param anymore, I was unsatisfied with the pitch shifting part of the plugins.

*UPDATE* **Garçon** is flagged as VISUAL.

*New* **HCTIP** is a pitch shifter, it is a test on fft pitch shifting technique.

23/09/2018 => 0.6.18

*NEW* **zOù MAï** sequencer first candidate. 8 patterns x 8 tracks x 64 steps with trim and probability/condition. Global swing per track is not implemented. For tracks and trigs select = left click and activate = right click. I will make a video asap in order to explain.

10/09/2018 => 0.6.17

*UPDATE* **dTrOY** and **bordL** fix quantization issue.

09/09/2018 => 0.6.16

*UPDATE* **lIMbO** cutoff frequency max value changed (calibration).

*UPDATE* **dTrOY** and **bordL** phase calculation now based on engine sample rate instead of clock() from ctime. V/Oct can't be synced with gates anymore it is continuous now. Quantization issue has been fixed. New input "Transpose" that comes after quantization (it is rescaled -4/+4 octaves on -10/+10V and sliced per 1/12 Volt). Copy/Paste is available in the UI => exit right click menu. "SHIFTS" allows you to move patterns left and right and pitch up and down.

*UPDATE* **LoURdE** threshold and factors displays are now yellow on black background.

## License

The license is a BSD 3-Clause with the addition that any commercial use requires explicit permission of the author. That applies for the source code.

For the image resources (all SVG files), any use requires explicit permission of the author.

## Donate

If you enjoy those modules you can support the development by making a donation. Here's the link: [DONATE](https://paypal.me/sebastienbouffier)
