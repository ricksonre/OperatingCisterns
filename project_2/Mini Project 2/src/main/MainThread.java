package main;

import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainThread implements Runnable{
	Random r = new Random();
	ExecutorService ex = Executors.newFixedThreadPool(5);
	

	@Override
	public synchronized void run() {
		// TODO Auto-generated method stub
		int j = 10; 
		while (j-->0) {
			
			ex.execute(new Request(2000));
			
			try {
				System.out.println("Main sleeping after request "+(10-j));
				Thread.sleep(r.nextInt(1000));
				System.out.println("Main completed request "+(10-j));
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		
	}
	
}
