public class MyThreadPool {
    private  MyThread[] threads;
    private  MyBlockQueue<Runnable> workQueue;

    public MyThreadPool(int capacity,int size) {
        threads = new MyThread[capacity];
        workQueue = new MyBlockQueue<>(size);
        for (int i = 0; i < capacity; i++) {
            threads[i] = new MyThread(workQueue);
            threads[i].start();
        }
    }

    public void execute(Runnable task) {
        try {
            workQueue.put(task);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static class MyThread extends Thread{
        private MyBlockQueue<Runnable> workQueue;
        public MyThread(MyBlockQueue<Runnable> workQueue){
            this.workQueue = workQueue;
        }
        @Override
        public void run() {
            while (true){
                try {
                    Runnable task = workQueue.take();
                    task.run();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        MyThreadPool pool = new MyThreadPool(5,1000);
        Runnable task = new Runnable() {
            @Override
            public void run() {
                System.out.println("task");
            }
        };
        for (int i = 0; i < 10; i++) {
            pool.execute(task);
        }
    }
}
