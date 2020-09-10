package com.roslib.ros;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class HardwareUDP implements Hardware {
    private final int SERVER_PORTNUM = 11316;
    private final int CLIENT_PORTNUM = 0;
    private DatagramSocket sock_fd_;
    private boolean connected_;
    private java.lang.String portName_ = "";

    public HardwareUDP() {
        this.sock_fd_ = null;
        this.connected_ = false;
        this.portName_ = "";
    }

    @Override
    public boolean init(String portName) {
        try {
            this.close();
            this.portName_ = portName;
            this.sock_fd_ = new DatagramSocket(CLIENT_PORTNUM);
            this.sock_fd_.setReuseAddress(true);
            this.connected_ = true;
        } catch (SocketException e) {
            e.printStackTrace();
            this.close();
            this.connected_ = false;
        }
        return this.connected_;
    }

    @Override
    public int read(byte[] data, int length) {
        int rv = -1;
        if (this.connected_) {
            try {
                DatagramPacket packet = new DatagramPacket(data, length);
                this.sock_fd_.receive(packet);
                rv = packet.getLength();
            } catch (IOException e) {
                e.printStackTrace();
                this.close();
                rv = -1;
            }
        }
        return rv;
    }

    @Override
    public boolean write(byte[] data, int length) {
        if (this.connected_) {
            try {
                InetAddress address= InetAddress.getByName(this.portName_);
                DatagramPacket packet = new DatagramPacket(data, length, address, SERVER_PORTNUM);
                this.sock_fd_.send(packet);
                return true;
            } catch (IOException e) {
                e.printStackTrace();
                this.close();
            }
        }
        return false;
    }

    @Override
    public boolean connected() {
        return this.connected_;
    }

    @Override
    public void close() {
        this.connected_ = false;
        if (this.sock_fd_ != null) {
            this.sock_fd_.close();
            this.sock_fd_ = null;
        }
    }
}

