from lclib import register_driver, proxycall, proxydevice,ProxyDeviceError
from lclib.base import SocketDriverBase
import ctypes
from config import config # a dict including config parameters
ADDRESS = ('192.168.3.69',10003)  #the IP of proxy Server which connects the controller
DEVICE_ADDRESS = ('192.168.3.69', 10003)   #the IP of proxy Server which connects the controller
mac_str = config['mac_str']
mac_ip = config['mac_ip']
data_path = config['data_path']
exposure_time = config['exposure_time']
@register_driver
@proxydevice(address=ADDRESS)
class PSCameraDriver(SocketDriverBase): #driver_name=PSCameradriver
    """
    Socket driver example for a PS detector.
    """
    DEFAULT_DEVICE_ADDRESS = DEVICE_ADDRESS
    def __init__(self, device_address=None):
        self.device = ctypes.CDLL("PS_camera.dll",winmode=0)#make sure all required dlls exist
        print('PS initialization success!')
    @proxycall(admin=True, block=False)
    def Camera_Init(self, mac_str, ip_str):
        mac = ctypes.c_char_p(mac_str.encode())   #physical IP address of the device
        ip = ctypes.c_char_p(ip_str.encode())  # the IP of controller should be in the same network segment as the camera, rather than the same IP.
        self.device.AcquisitionInit(mac, ip)
    @proxycall(admin=True, block=False)
    def Camera_Acquisition(self, tif_path): #tif_path : the path to save the image
        print(tif_path)
        tif_path = tif_path.encode()
        while 1:
            if self.device.AcquisitionFetch(tif_path) == 1:
                break
    @proxycall(admin=True, block=False)
    def Camera_Configuration(self, ExposureTime): #configure exposuretime(us)
        ExposureTime = ctypes.c_int(ExposureTime)
        self.device.Configuration(ExposureTime)
    @proxycall(admin=True, block=False)
    def Camera_Close(self):
        self.device.AcquisitionClose()
c = PSCameraDriver.Client()
    # Check that client is admin by default

try:
    assert c.ask_admin()
    print('ask_admin pass')
    c.ask_admin(True)
    print('set as admin pass')
    """
    Simulate an acquisition process
    When collecting multiple times, the camera only needs to be initialized once and closed at the end.
    """
    c.Camera_Init(mac_str,mac_ip)
    print('Camera_Init pass')
    c.Camera_Configuration(exposure_time)#(self,exposetime)
    print('Camera_Configuration pass')
    c.Camera_Acquisition(data_path)#(self, tif_path):
    print('Camera_Acquisition pass')
    c.Camera_Close()
    print('Camera_Close pass')
except Exception as e:
    print(f"an error occur: {e}")