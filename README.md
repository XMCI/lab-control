# lab control supplement



## Contents
My main work is to add some devices' control example code.Now includes **PDXC controller** designed by Thorlab and **PSCamera** designed by photonic science.

Each device's remote control is achieved through the **lab-control-lib** library.More devices may be uploaded after.

## How to use
The remote control is based on **server-client** module.Thus each device's directory has a ```xxxxserver``` and ```xxxxclient``` file.

You need to **unzip the lab-control-lib first** and install necessary modules before controlling a device.

Run the server first and create a device's  object.
Then you can design your own control scripts using the functions provided by documents such as SDK Manual.

For a new device, a dll may need to be written.


## Demo
In the ```demo``` dir there is a demo for control the stepper and camera simultaneously.

There is also a **demo video** showing how to use the scripts.


## Tips
1. Make sure all the dll's dependences and dirver programs are installed.(such as opencv).Some of the necessaries have been put in the corresponding dir.
2. Make sure the environment PATH has been set correctly.
3. Make sure you close the server proceed **completely** before you use it again otherwise error will occur when initialize device.

## Contributions
- The basic project structure [lab-control-lib](https://github.com/optimato/lab-control-lib) is created by the team of ***prof. Pierre Thibault***
- The ```PS_camera.dll``` is written by ***Jincheng Lu***.The ```XXXXServer.py```, ```XXXXClient.py```is written by ***Haoyu Liu***.The ```demo``` is created by both of Lu and Liu.
- Our work is under the guidance of Associate Prof. ***Zhentian Wang***.

##### <p align="left">Copyright © -2025 </p>
##### <p align="right">XMCI Team of Radiation Imaging Laboratory, Department of Engineering Physics, Tsinghua University</p>