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
	int max;//initialize variables
	
	public MainThread(int size, int max) //constructor
	{
		this.max = max;
		queue = new QueueMonitor(max);
		rq= new SlaveThread[size];//declare values from passed vals
		for(int i = 0; i<size;i++) 
		{
			rq[i] = new SlaveThread(queue);//create a slave thread for each size count
			rq[i].start();//start each slave
		}
		
	}

	@Override
	public  void run() //main running function for the master thread
	{
		//creation of new Request and insertion into the Monitor Queue
		while (true) 
		{
			
			queue.add(new Request(r.nextInt(max*1000)));//add a random length request to the queue
			try 
			{
				//Printing result and sleeping
				System.out.println("Main sleeping after request "+ Request.requestID + " at time " + System.currentTimeMillis());
				Thread.sleep(r.nextInt(max*1000));
				
			} catch (InterruptedException e) 
			{
				e.printStackTrace();
			}
			
		}
		
	}
	
}
