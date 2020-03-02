package main;

import java.util.ArrayList;
import java.util.Queue;
import java.util.Random;

public class MainThread extends Thread{
	Random r = new Random();
	QueueMonitor queue = new QueueMonitor(8);
	SlaveThread[] rq;
	
	public MainThread(int size) {
		rq= new SlaveThread[size];
		for(int i = 0; i<size;i++) {
			rq[i] = new SlaveThread(queue);
			rq[i].start();
		}
	}

	@Override
	public  void run() {
		
		// TODO Auto-generated method stub
		int j = 10; 
		while (j-->0) {
			
			queue.add(new Request(10000));
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
