import sys
import socket

class HardwareUdp(object):
    __slots__ = ['sock_', 'server_port_', 'client_port_', 'connected_']
    
    def __init__(self):
        self.sock_ = None
        self.connected_ = False

    def init(self, ip):
        try:
            self.close()
            self.server_port_ = (ip, 11316)
            self.client_port_ = ('', 0)
            self.sock_ = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
            self.sock_.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.sock_.bind(self.client_port_)
            self.connected_ = True
        except Exception as ex: 
            print('HardwareUdp::init %s' % str(ex))
            self.connected_ = False
        return self.connected_
  
    def read(self, length):
        if self.connected_ == True:
            try:
                _x, _addr = self.sock_.recvfrom(length)
                size = len(_x)
                return _x, size
            except Exception as ex: 
                print('HardwareUdp::read %s' % str(ex))
                self.close()
                return '', 0
        else:
            return '', 0

    def write(self, buff): 
        if self.connected_ == True:
            try:
                _x = buff
                size = len(_x)
                self.sock_.sendto(_x, self.server_port_)
                return size
            except Exception as ex: 
                print('HardwareUdp::write %s' % str(ex))
                self.close()
                return -1
        else:
            return -1
    
    def connected(self):
        return self.connected_

    def close(self):
        self.connected_ = False
        if self.sock_ != None:
            self.sock_.close()
            self.sock_ = None

