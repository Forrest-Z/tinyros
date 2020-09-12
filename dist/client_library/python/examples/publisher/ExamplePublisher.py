import os
import sys
import time
print('Tinyros modules: %s' % os.path.abspath(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))))
sys.path.append(os.path.abspath(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))))
import tinyros
import tinyros_hello.msg.TinyrosHello

def main():
    tinyros.init("PyExamplePublisher", "127.0.0.1")
    pub = tinyros.Publisher("tinyros_hello", tinyros_hello.msg.TinyrosHello)

    if 1:
        tinyros.nh().advertise(pub)
    else:
        tinyros.udp().advertise(pub)

    count = 0
    while True:
        msg = tinyros_hello.msg.TinyrosHello()
        msg.hello = str(count) + ': PyHello, tiny-ros ^_^'
        pub.publish(msg)
        time.sleep(1)
        count += 1

if __name__ == '__main__':
    main()

