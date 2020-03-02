import java.util.concurrent.PriorityBlockingQueue;

public class MyTimerPool {
    private PriorityBlockingQueue<MyTimerTask> workQueue;
    private MyTimerThread[] threads;

    public MyTimerPool(int capacity, int size) {
        threads = new MyTimerThread[capacity];
        workQueue = new PriorityBlockingQueue<>(size);
        for (int i = 0; i < capacity; i++) {
            threads[i] = new MyTimerThread(workQueue);
            threads[i].start();
        }
    }
    //执行定时任务
    public void schedule(Runnable task,long delay,long period) {
        workQueue.put(new MyTimerTask(task,delay,period));
        synchronized (workQueue){
            workQueue.notifyAll();
        }
    }

    public static class MyTimerThread extends Thread {
        private PriorityBlockingQueue<MyTimerTask> workQueue;

        public  MyTimerThread(PriorityBlockingQueue<MyTimerTask> workQueue) {
            this.workQueue = workQueue;
        }

        @Override
        public void run() {
            try {
                while (true){
                        MyTimerTask myTimerTask = workQueue.take();
                        long current = System.currentTimeMillis();
                        long next = myTimerTask.next;
                        if(current < next) {
                            synchronized (workQueue){
                                workQueue.wait(next - current);
                                workQueue.put(myTimerTask);
                            }
                        }else {
                            myTimerTask.task.run();
                            if(myTimerTask.period > 0) {
                                myTimerTask.next += myTimerTask.period;
                                workQueue.put(myTimerTask);
                            }
                        }
                    }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        }


    public static class MyTimerTask implements Comparable<MyTimerTask>{
        private Runnable task;
        private long next;
        private long period;

        public MyTimerTask(Runnable task,long delay,long period) {
            this.task = task;
            this.next = delay + System.currentTimeMillis();
            this.period = period;
        }

        @Override
        public int compareTo(MyTimerTask o) {
            return Long.compare(next,o.next);
        }
    }

    public static void main(String[] args) {
        MyTimerPool pool = new MyTimerPool(3,1000);
        pool.schedule(new Runnable() {
            @Override
            public void run() {
                System.out.println("明天要答辩");
            }
        },0,1000);

        pool.schedule(new Runnable() {
            @Override
            public void run() {
                System.out.println("后天要放假");
            }
        },1500,3000);
    }
}
