public class MyTimer {
    public void schedule(Runnable task,long delay,long period) {
        new Thread(new MyTimerTask(task,delay,period)).start();
    }

    public static class MyTimerTask implements Runnable {
        private Runnable task;
        private long next;  //下次执行时间
        private long period;

        public MyTimerTask(Runnable task,long delay,long period) {
            this.task = task;
            this.next = delay + System.currentTimeMillis();
            this.period = period;
        }
        @Override
        public void run() {
            while (true){
                try {
                    long currentTime = System.currentTimeMillis();
                    if(currentTime < next) {
                        Thread.sleep(next - currentTime);
                    }
                    task.run();
                    if(period > 0) {
                        next += period;
                    }else {
                        break;
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        MyTimer myTimer = new MyTimer();
        myTimer.schedule(new Runnable() {
            @Override
            public void run() {
                System.out.println("myTimer");
            }
        },3000,1000);
    }
}
