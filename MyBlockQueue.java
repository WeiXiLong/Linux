public class MyBlockQueue<E>{
    private Object[] elements;

    private int putIndex;

    private int takeIndex;

    private int size;

    public MyBlockQueue(int capacity) {
        elements = new Object[capacity];
    }

    public synchronized void put(E element) throws InterruptedException {
        while (size == elements.length){
            wait();
        }
        elements[putIndex] = element;
        putIndex = (putIndex + 1) % elements.length;
        size++;
        notifyAll();
    }

    public synchronized E take() throws InterruptedException {
        while (size == 0){
            wait();
        }
        E element = (E) elements[takeIndex];
        takeIndex = (takeIndex + 1) % elements.length;
        notifyAll();
        size--;
        return element;
    }

    public static void main(String[] args) {
        MyBlockQueue<String> queue = new MyBlockQueue<>(20);
        for (int i = 0; i < 10; i++) {
            final int k = i;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        for (int j = 0; j < 3; j++) {
                            queue.put(String.valueOf(k) + "-" + j);
                        }
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }).start();
        }

        for (int i = 0; i < 100; i++) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        String e = queue.take();
                        System.out.println(e);
                    } catch (InterruptedException e1) {
                        e1.printStackTrace();
                    }
                }
            }).start();
        }
    }
}
