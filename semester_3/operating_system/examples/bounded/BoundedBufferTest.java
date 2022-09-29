/*
 * bounded/BoundedBufferTest.java --
 *
 *      Bounded buffer (producer / consumer) problem solution with
 *      Java synchronized methods. This test driver uses synchronized
 *      expressions to generate an increasing sequence of numbers
 *      concurrently.
 */

import java.lang.Runnable;
import java.lang.Thread;
import java.lang.ThreadGroup;

public class BoundedBufferTest
{
    private static BoundedBuffer buffer = new BoundedBuffer(8);

    private static class Producer implements Runnable
    {
        private static Integer fake = 0;
        private static int next = 0;
        
        public void run()
        {
            while (true) {
                synchronized (fake) {
                    buffer.insert(next++);
                }
            }
        }
    }

    private static class Consumer implements Runnable
    {
        public void run()
        {
            while (true) {
                int val = buffer.remove();
                System.out.println(val);
            }
        }
    }

    public static void main(String[] args)
    {
        BoundedBufferTest test = new BoundedBufferTest();

        ThreadGroup producer = new ThreadGroup("producer");
        ThreadGroup consumer = new ThreadGroup("consumer");

        for (int i = 0; i < 5; i++) {
            Thread t = new Thread(producer, new Producer());
            t.start();
        }

        for (int i = 0; i < 2; i++) {
            Thread t = new Thread(consumer, new Consumer());
            t.start();
        }
    }
}
