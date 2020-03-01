package main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main implements Runnable{
	static ExecutorService pool;   
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int threadCount = 9;
		
		pool = Executors.newFixedThreadPool(threadCount);   
		
		Main ma = new Main();
		ma.run();
		
	}
	
	public Main () {
		
		
		
		
	}
	

	
	

	@Override
	public void run() {
		// TODO Auto-generated method stub
		int i = 9;
		while (i-- > 0) {
			
			pool.execute(new Request(500));
			
			try {
				System.out.println("Runing Thread" + i);
				Thread.sleep((long) (Math.random()*10000));
				System.out.println("Runing Wake up i");
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			
		}
		
	}

}
