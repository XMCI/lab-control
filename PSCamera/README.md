### Instructions
- The dir ```document``` includes document about **X-ray sCMOS 16MP Detector** designed by ***PHOTONIC SCIENCE***.
- Dir ```Configuration_files``` mainly includes some necessary config_files.
- The ```Camera_Big.7z``` is zipped by part for it's too large and need to be unzipped and install the driver program.
- You can modify the ```PSCameraServer``` according to the interfaces provided by ```PS_camera.dll```.
- some dlls need to be installed by driver ```".\Camera_Big\PSViewer_5.14.0_x64_win_10\Installer5.14.0x64_win10\PSViewer_Installer5.14.0x64_win10.exe"```
please unzip Camera_Big.7z first

### PS_camera.dll
## How to use this dll?
```
self.device = ctypes.CDLL("PS_camera.dll",winmode=0)#make sure all required dlls exist
```
Then we can use self.device to control the camera

We should provide the mac address and ip address of the detector for its initialization, then set the exposure time and then call Camera_Acquisition to save the image in different paths

```
Camera_Init(mac_str, ip_str)
Description:
Initializes the connection between the controller and the PS camera. This function sets up communication by calling the underlying DLL method AcquisitionInit with the device's MAC address and the controller's IP address.

Parameters:

mac_str (str): The MAC address of the PS camera (e.g., "00:11:22:33:44:55").

ip_str (str): The IP address of the controller. It must be in the same subnet as the camera but not identical.

Note:
This method should be called once before any image acquisition. Ensure the camera and controller are properly connected and network settings are correctly configured.

Camera_Configuration(ExposureTime)
Description:
Configures the camera's exposure time by calling the DLL method Configuration. The exposure time affects the brightness and clarity of the captured images.

Parameters:

ExposureTime (int): Exposure duration in microseconds (µs).

Note:
This should be set before starting acquisition to ensure proper exposure settings during image capture.

Camera_Acquisition(tif_path)
Description:
Starts the image acquisition process and saves the captured image as a .tif file. The function loops until the acquisition is complete by checking the return value of AcquisitionFetch.

Parameters:

tif_path (str): File path to save the acquired image (e.g., "D:/data/image001.tif").

Note:
This function is blocking and returns only after a successful acquisition. Ensure initialization and configuration are completed before calling this function.

Camera_Close()
Description:
Closes the camera connection and releases all associated resources by calling the DLL function AcquisitionClose.

Note:
This function should be called after all acquisitions are complete to properly shut down the device and free resources.
```


