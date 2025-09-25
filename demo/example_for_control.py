from PDXCServer import PDXCDriver
from PSCameraServer import PSCameraDriver
from config import *
import os
def init_device():
    global c_PSCamera,c_PDXC
    c_PSCamera = PSCameraDriver.Client()
    c_PSCamera.ask_admin(True)
    print('set as admin pass')
    c_PDXC = PDXCDriver.Client()
    c_PDXC.ask_admin(True)
    print('set as admin pass')
    c_PSCamera.Camera_Init(config["mac_str"], config["mac_ip"])  #initialize once
    print('Camera_Init pass')
    c_PSCamera.Camera_Configuration(config["exposure_time"])
    print('Camera_Configuration pass')

def acqui(index):
    base_path = config.get("data_path")
    if not base_path.endswith(('/', '\\')):
        base_path += os.path.sep
    file_name = f"test{index + 1}.tif"
    full_path = os.path.join(base_path, file_name)
    os.makedirs(os.path.dirname(full_path), exist_ok=True)
    c_PSCamera.Camera_Acquisition(full_path)
    print('Camera_Acquisition pass')
def step_and_acqui():
    #step and acquire images
    for i in range (0,5):# step 5 times
        c_PDXC.move_forward(config["step_size"])#STEP_PULSE=5000
        acqui(i)
def close_device():
    c_PSCamera.Camera_Close()
    print('Camera_Close pass')
if __name__ == "__main__":
    try :
        init_device()
        step_and_acqui()
        close_device()
    except Exception as e:
        print(f"an error occur:{e}")

