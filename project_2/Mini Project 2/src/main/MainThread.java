package main;

import java.util.ArrayList;
import java.util.Queue;
import java.util.Random;

public class MainThread extends Thread
{
	Random r = new Random();
	QueueMonitor queue;
	SlaveThread[] rq;
	int max;
	
	public MainThread(int size, int max) 
	{
		this.max = max;
		queue = new QueueMonitor(max);
		rq= new SlaveThread[size];
		for(int i = 0; i<size;i++) 
		{
			rq[i] = new SlaveThread(queue);
			rq[i].start();
		}
		
	}

	@Override
	public  void run() 
	{
		
		while (true) 
		{
			queue.add(new Request(r.nextInt(max*1000)));
			System.out.println("me left ");
			try 
			{
				System.out.println("Main sleeping after request "+ Request.requestID);
				Thread.sleep(r.nextInt(max*1000));
				
			} catch (InterruptedException e) 
			{
				e.printStackTrace();
			}
			
		}
		
	}
	
}
