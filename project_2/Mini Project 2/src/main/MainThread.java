package main;

import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainThread implements Runnable{
	Random r = new Random();
	public static void main(String[] args) {
		
		MainThread m = new MainThread();
		ExecutorService ex = Executors.newFixedThreadPool(5);
	}

	@Override
	public synchronized void run() {
		// TODO Auto-generated method stub
		while (true) {
			
			Main.addToQueue(this, new Request(5));
			
			try {
				Thread.sleep(r.nextInt(5000));
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		
	}
	
}
