package examples.publisher;

import com.roslib.ros.Publisher;
import com.roslib.ros.Tinyros;
import com.roslib.tinyros_hello.TinyrosHello;

public class ExamplePublisher {

    public static void main(String[] args) throws InterruptedException {
        Tinyros.init("JavaExamplePublisher", "127.0.0.1");
        
        Publisher<TinyrosHello> pub = new Publisher<TinyrosHello>("tinyros_hello", new TinyrosHello());

        if (true) {
            Tinyros.nh().advertise(pub);
        } else {
            Tinyros.udp().advertise(pub);
        }

		int count = 0;
        while(true) {
            TinyrosHello msg = new TinyrosHello();
            msg.hello = (count++) + ": JavaHello, tiny-ros ^_^";
            pub.publish(msg);
            Thread.sleep(1000);
        }
    }
}
