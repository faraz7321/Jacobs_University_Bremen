/*
 * bounded/BoundedBuffer.java --
 *
 *      Bounded buffer (producer / consumer) problem solution with
 *      Java synchronized methods.
 */

import java.lang.Thread;

class BoundedBuffer
{
    private final int size;
    private int count = 0, out = 0, in = 0;
    private int[] buffer;

    public BoundedBuffer(int size) {
        this.in = 0;
        this.out = 0;
        this.count = 0;
        this.size = size;
        this.buffer = new int[this.size];
    }

    public synchronized void insert(int i)
    {
        try {
            while (count == size) {
                wait();
            }
            buffer[in] = i;
            in = (in + 1) % size;
            count++;
            notifyAll();    // wakeup all waiting threads
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public synchronized int remove()
    {
        try {
            while (count == 0) {
                wait();
            }
            int r = buffer[out];
            out = (out + 1) % size;
            count--;
            notifyAll();    // wakeup all waiting threads
            return r;
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return -1;
        }
    }
}
