package main;

import java.util.Queue;
import java.util.concurrent.Executor;

//these threads aquire requests from the queue to process and sleep while waiting.
public class SlaveThread extends Thread {
	boolean running = false;
	static int SlaveID;
	int ID;
	QueueMonitor q;
	

	public SlaveThread(QueueMonitor queue) {
		this.q = queue;
		this.ID = SlaveThread.SlaveID++;
	}

	public void run() 
	{
		while (true) 
		{
			Request r = q.getNext();
			System.out.println("Slave thread "+ID+" is running ");
			r.run();
			
		}
	}

}
