from lclib import register_driver, proxycall, proxydevice,ProxyDeviceError
from lclib.base import SocketDriverBase
from PDXC_COMMAND_LIB import *
ADDRESS = ('192.168.3.12',10001) #the IP of proxy Server which connects the controller
@register_driver
@proxydevice(address=ADDRESS) #register "pdxcdriver" to the global registry binding with ADDRESS IP
class PDXCDriver(SocketDriverBase): #driver_name=pdxcdriver
    """
    Socket driver example for a PDXC device.
    """
    def __init__(self, device_address):
        self.init_device()

    def init_device(self):
        """
        Device initialization.
        """
        self.device = pdxc()
        devs = pdxc.ListDevices()
        print(devs)
        if len(devs) <= 0:
            print('There is no devices connected')
            raise RuntimeError("device is not connected to the Server")
        device_info = devs[0]
        sn = device_info[0]
        print("connect ", sn)
        hdl = self.device.Open(sn, 115200, 3)
        if hdl < 0:
            print("open ", sn, " failed")
            exit()
        if self.device.IsOpen(sn) == 0:
            print("pdxcIsOpen failed")
            self.device.Close()
            raise RuntimeError("device is not open")
        result = self.device.SetDaisyChain(0)  # 0:Single Mode, 1:Main, 2 -12 : Secondary1 - Secondary11
        if result < 0:
            print("set daisy chain mode failed", result)
        else:
            print("set daisy chain mode: single mode")
        self.initialized = True
    @proxycall(admin=True, block=False)
    def move_forward(self, value):

        pul = value
        result = self.device.SetOpenLoopMoveForward(0, pul, 0)  # move forward in open loop mode of channel 0;
        # SMC[1,65535]; PD2/PD3[1,400000]
        """ Set Open Loop Move Forward
                Args:
                    secondary: index in daisy chain (0:Single Mode or Main, 1 -11 : Secondary1 - Secondary11)
                    pulses: pulses of move channel:SMC[1,65535]; PD2/PD3[1,400000]
                    channel: Move fordward channel (0 : channel 1, 1 : channel 2, others :both channels)
                Returns:
                    0: Success; negative number: failed.
        """
        if result < 0:
            print(f"set OpenLoopMoveForward {pul} failed", result)
        else:
            print(f"set OpenLoopMoveForward {pul}")
        time.sleep(1)

    @proxycall(admin=True, block=False)
    def move_back(self,value):
        pul = value
        result = self.device.SetOpenLoopMoveBack(0, pul, 0)
        """ Set Open Loop Move Forward
        Args:
            secondary: index in daisy chain (0:Single Mode or Main, 1 -11 : Secondary1 - Secondary11)
            pulses: pulses of move channel:SMC[1,65535]; PD2/PD3[1,400000]
            channel: Move fordward channel (0 : channel 1, 1 : channel 2, others :both channels)
        Returns:
            0: Success; negative number: failed.
        """
        if result < 0:
            print(f"set OpenLoopMoveForward {pul} failed", result)
        else:
            print(f"set OpenLoopMoveForward {pul}")
        time.sleep(1)

try:
    c = PDXCDriver.Client()# this script is used to start a client and connect to the registered driver(server)
    assert c.ask_admin()   # Check that client is admin by default
    print('ask admin pass')
    c.ask_admin(True)
    print('set as admin pass')
    # Customize the operations that the client wants to perform here. Here is an example for move control
    c.move_forward(5000)
    c.move_back(5000)
except Exception as e:
    print(f"an error occur :{e}")