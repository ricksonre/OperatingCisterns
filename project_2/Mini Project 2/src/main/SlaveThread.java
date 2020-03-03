package main;

import java.util.Queue;
import java.util.concurrent.Executor;

//these threads aquire requests from the queue to process and sleep while waiting.
public class SlaveThread extends Thread {
	boolean running = false;
	static int SlaveID;
	int ID;
	QueueMonitor q;//initialize variables
	

	public SlaveThread(QueueMonitor queue) {//constructor
		this.q = queue;
		this.ID = SlaveThread.SlaveID++;//set var values to passed and corresponding slave #
	}

	public void run() //running code
	{
		while (true) //run forever
		{
			Request r = q.getNext();//get the next request
			System.out.println("Slave thread "+ID+" is running ");
			r.run();//print that it is running and then call the request run function
			
		}
	}

}
