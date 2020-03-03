package main;

import java.util.ArrayList;
import java.util.Queue;
import java.util.Random;
//Main Thread is in charge of creating slave threads stored in an array and the creation of the Monitor Queue

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
		//creation of new Request and insertion into the Monitor Queue
		while (true) 
		{
			
			queue.add(new Request(r.nextInt(max*1000)));
			System.out.println("me left ");
			try 
			{
				//Printing result and sleeping
				System.out.println("Main sleeping after request "+ Request.requestID);
				Thread.sleep(r.nextInt(max*1000));
				
			} catch (InterruptedException e) 
			{
				e.printStackTrace();
			}
			
		}
		
	}
	
}
