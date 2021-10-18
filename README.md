# Tello SDK (C based API) for TLW004 series Aircraft

![Tello](https://github.com/vismayp92/tello_drone/blob/master/references/tello_cover.jpg?raw=true)

This project implements Linux based C API and a test application to control Tello TLW004 series aircrafts, which could serve as a foundation for tello drone based embedded projects for hobbyists or professionals.

## Tello SDK References
Please visit tello's official website for `Tello SDK User Guide` and `Documentation` to get a detailed view of supported aircraft commands,
https://www.ryzerobotics.com
Furthermore, the PDFs are uploaded and available in this repository,
[Tello_SDK_Documentation_EN_1.3_1122.pdf](https://github.com/vismayp92/tello_drone/blob/master/references/Tello_SDK_Documentation_EN_1.3_1122.pdf)
[Tello_SDK_2.0_User_Guide.pdf](https://github.com/vismayp92/tello_drone/blob/master/references/Tello_SDK_2.0_User_Guide.pdf)

## Tello SDK C API
This project implements C based API functions to control Tello Aircraft. Currently, it is only compatible with Linux based systems.
(With a few changes, it can also be cross-compiled for arm/aarch64 - Linux/Android)

### Prerequisites
Linux OS with build-essential installed (build utilities - make, gcc)

### Build from the source
Simply build the project,
```
cd tello_drone
make
```
The executable(s) shall be available under `bin/`

### Run the app
Please make sure that `Tello TLW004` aircraft is turned ON and your Linux machine is connected to `Tello-xxxxx` wifi network.
Now, run the app,
```
cd tello_drone/bin
./tello_app
```
It will open a custom tello terminal, where user can insert the commands to control the aircraft.
For, the complete list of supported commands, please refer to the PDF files given under `references/` in this repository.
