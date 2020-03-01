package main;

import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainThread implements Runnable{
	Random r = new Random();
	ThreadPool ex = new ThreadPool(6);
	

	@Override
	public  void run() {
		// TODO Auto-generated method stub
		int j = 10; 
		while (j-->0) {
			
			ex.execute(new Request(10000));
			ex.execute(new Request(10000));
			try {
				System.out.println("Main sleeping after request "+(10-j));
				Thread.sleep(r.nextInt(1000));
				
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		
	}
	
}
